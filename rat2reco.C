#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TF2.h>
#include <TRegexp.h>
#include <TPRegexp.h>
#include <TMath.h>
#include <TLeaf.h>
#include <Rtypes.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TPad.h>
#include <TVector3.h>
#include <TString.h>
#include <TObject.h>
#include <TChain.h>
#include <THStack.h>
#include <TPad.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TText.h>
#include <TLine.h>
#include <TLegendEntry.h>
#include <TVectorF.h>
#include <TKey.h>
#include <TSpectrum.h>
#include <TVirtualFFT.h>
#include <TMultiGraph.h>
#include <TSystem.h>

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <map>
#include <utility>

// Header file for the classes stored in the TTree if any.
#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/Calib.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DSReader.hh>
#include <RAT/TrackNav.hh>
#include <RAT/TrackCursor.hh>
#include <RAT/TrackNode.hh>

using namespace std;

int rat2reco(char *filename) {
  
  // Load RAT libraries (for dsReader)
  gSystem->Load("$(RATPAC_PATH)/lib/libRATEvent.so");
  
  // create a random number generator
  gRandom = new TRandom3();
  
  // Load the files
  TFile inputfile(filename,"READ"); 
  RAT::DSReader *dsReader;
  RAT::DS::Root   *ds;
  dsReader = new RAT::DSReader(inputfile.GetName());
  ULong64_t NbEntries = dsReader->GetTotal();
  
  // Initialize stuff
  TGraph *gWave;    
  TCanvas *c1;
  
  // some values about your waveform
  Float_t sigma_noise = 1.*0.001; // in V
  Float_t mean_noise = 0.0*0.001; // in V
  Float_t pulse_shape[25] = {0.3*0.001,0.6*0.001,0.9*0.001,1.2*0.001,1.5*0.001,1.8*0.001,2.1*0.001,2.4*0.001,2.7*0.001,3.0*0.001,2.8*0.001,2.6*0.001,2.4*0.001,2.2*0.001,2.0*0.001,1.8*0.001,1.6*0.001,1.4*0.001,1.2*0.001,1.0*0.001,0.8*0.001,0.6*0.001,0.4*0.001,0.2*0.001,0.}; //each point is one sample (2 ns)
  const Int_t nb_samples = 40000; // nb points in your waveform
  Int_t trigger_offset = 100; // amount of samples you want to keep free at the beginning of your window 
  
  Float_t waveform[nb_samples], waveform_samples[nb_samples];
  
  // Create output file
  TFile outputfile(Form("rat2reco_%s", inputfile.GetName() ),"RECREATE");
  
  // Tree and branches
  TTree *PMTData = new TTree("PMTData","PMT Data tree");
  long LastSync ,StartCount, TriggerCount;
  Int_t SequenceID, StartTimeSec, StartTimeNSec, TriggerNumber, CardID, Channel, BufferSize, Trigger, PMTID, PMTx, PMTy, PMTz, PMTf;
  int Rate;
  Float_t Data[nb_samples];
  PMTData->Branch("LastSync",&LastSync,"LastSync/l");// no idea, set to 0
  PMTData->Branch("SequenceID",&SequenceID,"SequenceID/I");// no idea, set to 0
  PMTData->Branch("StartTimeSec",&StartTimeSec,"StartTimeSec/I");// no idea, set to 0
  PMTData->Branch("StartTimeNSec",&StartTimeNSec,"StartTimeNSec/I");// no idea, set to 0
  PMTData->Branch("StartCount",&StartCount,"StartCount/l");// no idea, set to 0
  PMTData->Branch("TriggerNumber",&TriggerNumber,"TriggerNumber/I");// no idea, set to 1
  PMTData->Branch("TriggerCount",&TriggerCount,"TriggerCount/l");// no idea, set to 0
  PMTData->Branch("CardID",&CardID,"CardID/I");
  PMTData->Branch("Channel",&Channel,"Channel/I");
  PMTData->Branch("Rate",&Rate,"Rate/i"); // no idea, set to 0
  PMTData->Branch("BufferSize",&BufferSize,"BufferSize/I");
  PMTData->Branch("Trigger",&Trigger,"Trigger/I"); //event number
  PMTData->Branch("Data",Data,"Data[BufferSize]/F");
  PMTData->Branch("PMTID",&PMTID,"PMTID/I");
  PMTData->Branch("PMTf",&PMTf,"PMTf/I");
  PMTData->Branch("PMTx",&PMTx,"PMTx/I");
  PMTData->Branch("PMTy",&PMTy,"PMTy/I");
  PMTData->Branch("PMTz",&PMTz,"PMTz/I");
  
  
  // Variables
  Bool_t broken_tube = false;
  vector<Int_t> hitPMT;
  Bool_t ncv_hit;
  
  for(Int_t i = 0; i < nb_samples; ++i) {
    waveform_samples[i] = i;
  }
  
  // PMT grid coordinates (not in ratpac x,y,z)
  int pmt_x_array_run1[] = {0,0,0,1,2,3,4,5,6,7,7,7,1,2,2,1,3,4,4,3,5,6,6,5,1,2,2,1,3,4,4,3,5,6,6,5,1,2,2,1,3,4,4,3,5,6,6,5,0,0,0,1,2,3,4,5,6,7,7,7};
  int pmt_z_array_run1[] = {3,2,1,0,0,0,0,0,0,1,2,3,1,1,2,2,1,1,2,2,1,1,2,2,3,3,4,4,3,3,4,4,3,3,4,4,5,5,6,6,5,5,6,6,5,5,6,6,4,5,6,7,7,7,7,7,7,6,5,4};
  int pmt_card_array_run1[] = {3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,13,13,13,13,14,14,14,14,15,15,15,15,16,16,16,16,18,18,18,18,19,19,19,19,20,20,20,20};
  int pmt_channel_array_run1[] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
  
  for(ULong64_t entry=0; entry<10; ++entry){
    ds = dsReader->GetEvent(entry);
    
    // Some initilizations
    broken_tube = false; hitPMT.clear(); ncv_hit = false;
    
    cout << "================================" << endl;
    cout << "========= New evt -- ===========" << endl;
    
    for( Int_t jPMT = 0; jPMT < ds->GetMC()->GetMCPMTCount(); ++jPMT ){
     	if (ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 61 || ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 62){
	 ncv_hit = true;
	 break;
	} 
    }
    
    if(ncv_hit) {
    for( Int_t jPMT = 0; jPMT < ds->GetMC()->GetMCPMTCount(); ++jPMT ){
       
      if (ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 6 ||
	ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 49 ||
	ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 19 ||
	ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 37) { 
	continue;
	}
	
      cout << "****==== ID(-1) of PMT Hit: " << ds->GetMC()->GetMCPMT(jPMT)->GetID() << " ====****\n";
	
      BufferSize = nb_samples;
      LastSync = 0;
      StartCount = 0;
      StartTimeSec = 0;
      StartTimeNSec = 0;
      TriggerNumber = 0;
      TriggerCount = 0;
      Rate = 0;
      Trigger = entry;
      SequenceID = entry; 
      
      if (ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 61){
// 	 		cout << " NCV" << endl;
	PMTID = 6;
	PMTx = pmt_x_array_run1[5];
	PMTz = pmt_z_array_run1[5];
	CardID = pmt_card_array_run1[5]; 
	Channel = pmt_channel_array_run1[5];
      } else if (ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 62){
// 	 		cout << " NCV" << endl;
	PMTID = 49;
	PMTx = pmt_x_array_run1[48];
	PMTz = pmt_z_array_run1[48];
	CardID = pmt_card_array_run1[48]; 
	Channel = pmt_channel_array_run1[48];
      } else {
	PMTID = ds->GetMC()->GetMCPMT(jPMT)->GetID()+1;
	PMTx = pmt_x_array_run1[ds->GetMC()->GetMCPMT(jPMT)->GetID()];
	PMTz = pmt_z_array_run1[ds->GetMC()->GetMCPMT(jPMT)->GetID()];
	CardID = pmt_card_array_run1[ds->GetMC()->GetMCPMT(jPMT)->GetID()]; 
	Channel = pmt_channel_array_run1[ds->GetMC()->GetMCPMT(jPMT)->GetID()];
      }
      
      hitPMT.push_back(PMTID-1);
      
      for(Int_t i = 0; i < nb_samples; ++i) {
	Data[i] = gRandom->Gaus(mean_noise,sigma_noise);
      }
      
      
      for( Int_t iPhot = 0; iPhot < ds->GetMC()->GetMCPMT(jPMT)->GetMCPhotonCount(); ++iPhot ){ // loop on photons that generated a PE		
// 	cout << "Sample: " << ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetHitTime()*0.5 << endl;
// 	cout << "Charge: " << ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetCharge() << endl;
	if (TMath::FloorNint(ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetHitTime()*0.5)  < nb_samples-trigger_offset) {
	  for(Int_t i = 0; i < 25; ++i) {
	    Data[trigger_offset + TMath::FloorNint(ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetHitTime()*0.5)] += pulse_shape[i]*ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetCharge();
// 	    cout << pulse_shape[i]*ds->GetMC()->GetMCPMT(jPMT)->GetMCPhoton(iPhot)->GetCharge() << endl;
	  }
	}
 	if (ds->GetMC()->GetMCPMT(jPMT)->GetID()+1 == 61) {gWave = new TGraph(nb_samples,waveform_samples,Data);}
	
	
      }
      PMTData->Fill();
    }
    
    // PMT loop
    for( Int_t iPMT = 0; iPMT < 64; ++iPMT ){
      if(!ncv_hit) { break;}
      if (find(hitPMT.begin(), hitPMT.end(), iPMT) == hitPMT.end()) {
// 	 	cout << "No hit: " << iPMT << endl;
	for(Int_t i = 0; i < nb_samples; ++i) {
	  Data[i] = gRandom->Gaus(mean_noise,sigma_noise);
	}
	if (iPMT >= 60) {
	  PMTID = 100;
	  PMTx = -10;
	  PMTz = -10; 
	  PMTy = -10; 
	  if (iPMT == 60) {
	    CardID = 21;
	    Channel = 0;
	  }
	  if (iPMT == 61) {
	    CardID = 21;
	    Channel = 1;
	  }
	  if (iPMT == 62) {
	    CardID = 21;
	    Channel = 2;
	  }
	  if (iPMT == 63) {
	    CardID = 21;
	    Channel = 3;
	  }
	} else {
	  PMTID = iPMT+1;
	  PMTx = pmt_x_array_run1[iPMT];
	  PMTz = pmt_z_array_run1[iPMT]; 
	  CardID = pmt_card_array_run1[iPMT]; 
	  Channel = pmt_channel_array_run1[iPMT]; 
	  PMTy = 0; 
	} 
	PMTf = 0;
	
	PMTData->Fill();
      }  
      
    }
    }
    
  }
  
  c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  gWave->Draw("AL");
  
  outputfile.Write();
  outputfile.Close();
  inputfile.Close();
  
  
}
