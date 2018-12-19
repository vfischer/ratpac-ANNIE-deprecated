///////////  Reads a RAT-PAC output files with PE information and converts it to a file readable by the reconstruction software (Jingbo and Ashley) ////////
/////////// Author: Vincent FISCHER  ///////

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLeaf.h>
#include <Rtypes.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TH2.h>
#include <TH3.h>
#include <TPad.h>
#include <TVector3.h>
#include <TString.h>
#include <TPRegexp.h>
#include <TGraph.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include "Math/Vector4D.h"
#include <TClonesArray.h>


#ifdef __MAKECINT__ 
#pragma link C++ class std::vector<TLorentzVector>+; 
#pragma link C++ class std::vector<TVector3>+; 
#endif

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

// Header file for the classes stored in the TTree if any.
#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/Calib.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DS/PMTInfo.hh>
#include <RAT/DS/RunStore.hh>
#include <RAT/DS/Run.hh>
#include <RAT/DSReader.hh>
#include <RAT/TrackNav.hh>
#include <RAT/TrackCursor.hh>
#include <RAT/TrackNode.hh>
#include <RAT/DB.hh>

using namespace std;
using namespace TMath;

void convert_reco_files(const char* filename_ratpac, const char* filename_genie_gst) {
  
  // Load RAT libraries (for dsReader)
  gSystem->Load("$(RATPAC_PATH)/lib/libRATEvent.so");
  
  // Initialization
  RAT::DSReader *dsReader;
  RAT::DS::Root *ds;
  RAT::TrackNav *nav;
  RAT::TrackCursor *cursor;
  RAT::TrackNode *node;
  TChain* tri;
  TChain* runtri;
  
  RAT::DS::Run* run;
  RAT::DS::PMTInfo* pmtInfo;
  RAT::DS::LAPPDInfo* lappdInfo;
  
  std::clock_t start;
  double duration;
  
  ULong64_t NbEntries;
  
  TVector3 muon_momentum;
  TVector3 unit_vect(0.,0.,1.);
  
  TVector3 init_pos;
  TVector3 fin_pos;
  Double_t init_time, fin_time;
  TString nucl_cap_pdg_code;
  
  Bool_t muon_found;
  Int_t muon_number = 0;
  
  ROOT::Math::XYZTVector digit_vect(0.,0.,0.,0.);
  
  // Starts the timer
  start = clock();
  
    // open and load the genie gst tree
  TFile f_GENIEFile(filename_genie_gst,"READ");
  TTree *gst_tree= (TTree*)f_GENIEFile.Get("gst");
  
  Int_t i_ev = 0;
  Int_t code_n = 0;
  Double_t E_nu = 0.;
  Double_t mom_trans = 0.;
  Double_t E_l = 0.;
  Double_t Px_l = 0.;
  Double_t Py_l = 0.;
  Double_t Pz_l = 0.;
  Bool_t is_cc = false;
  Bool_t is_res = false;
  Bool_t is_qel = false;
  Bool_t is_mec = false;
  Bool_t is_dis = false;
  
  TBranch * iev;
  TBranch * neu;
  TBranch * Ev;
  TBranch * Q2;
  TBranch * El;
  TBranch * pxl;
  TBranch * pyl;
  TBranch * pzl;
  TBranch * cc;
  TBranch * qel;
  TBranch * res;
  TBranch * mec;
  TBranch * dis;
  
  gst_tree->SetMakeClass(1);
  gst_tree->SetBranchAddress("iev", &i_ev, &iev);
  gst_tree->SetBranchAddress("neu", &code_n, &neu);
  gst_tree->SetBranchAddress("Ev", &E_nu, &Ev);
  gst_tree->SetBranchAddress("Q2", &mom_trans, &Q2);
  gst_tree->SetBranchAddress("El", &E_l, &El);
  gst_tree->SetBranchAddress("pxl", &Px_l, &pxl);
  gst_tree->SetBranchAddress("pyl", &Py_l, &pyl);
  gst_tree->SetBranchAddress("pzl", &Pz_l, &pzl);
  gst_tree->SetBranchAddress("cc", &is_cc, &cc);
  gst_tree->SetBranchAddress("qel", &is_qel, &qel);
  gst_tree->SetBranchAddress("res", &is_res, &res);
  gst_tree->SetBranchAddress("mec", &is_mec, &mec);
  gst_tree->SetBranchAddress("dis", &is_dis, &dis);
  
  
    
  // Output file
  TFile f_output("Reco_output_readable.root","RECREATE");
  // Tree and branches
  TTree *vertexTree = new TTree("vertexTree","All True Tank QE Events");
  
  Int_t event_num;
  Double_t neutrino_energy;
  TString interaction_type;
  Int_t neut_code;
  Double_t momentum_transfer;
  Double_t muon_energy;
  Double_t muon_angle;
  Double_t total_track_length;
  Double_t tracklength_in_water;
  Double_t tracklength_in_mrd;
  Double_t energyloss_in_mrd;
  Double_t digit_time_smear;
  Double_t digit_pmt_id;
  TLorentzVector filemuonstartvertex(0.,0.,0.,0.);     
  TLorentzVector filemuonstopvertex(0.,0.,0.,0.);     
  TVector3 filemuondirectionvector(0.,0.,0.);
  std::vector<Double_t> digitcharges;
  std::vector<Int_t> digitwhichdet;
  std::vector<ROOT::Math::XYZTVector>  filedigitvertices;     
  std::vector<ROOT::Math::XYZTVector>* filedigitverticesp = &filedigitvertices;     
  
  TBranch* EventNum = vertexTree->Branch("EventNum",&event_num); 
  TBranch* NeutrinoEnergy = vertexTree->Branch("NeutrinoEnergy",&neutrino_energy); 
  TBranch* InteractionType = vertexTree->Branch("InteractionType",&interaction_type); 
  TBranch* NeutCode = vertexTree->Branch("NeutCode",&neut_code); 
  TBranch* MomentumTransfer = vertexTree->Branch("MomentumTransfer",&momentum_transfer); 
  TBranch* MuonEnergy = vertexTree->Branch("MuonEnergy",&muon_energy); 
  TBranch* MuonAngle = vertexTree->Branch("MuonAngle",&muon_angle); 
  TBranch* TotalTrackLength = vertexTree->Branch("TotalTrackLength",&total_track_length); 
  TBranch* TrackLengthInWater = vertexTree->Branch("TrackLengthInWater",&tracklength_in_water); 
  TBranch* TrackLengthInMrd = vertexTree->Branch("TrackLengthInMrd",&tracklength_in_mrd); 
  TBranch* EnergyLossInMrd = vertexTree->Branch("EnergyLossInMrd",&energyloss_in_mrd); 
  TBranch* MuonStartBranch = vertexTree->Branch("MuonStartVertex",&filemuonstartvertex);     
  TBranch* MuonStopBranch = vertexTree->Branch("MuonStopVertex", &filemuonstopvertex);     
  TBranch* MuonDirectionBranch = vertexTree->Branch("MuonDirection", &filemuondirectionvector);     
  TBranch* DigitVertexBranch = vertexTree->Branch("DigitVertices", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &filedigitverticesp);
  TBranch* DigitChargesBranch = vertexTree->Branch("DigitCharges", &digitcharges); 
  TBranch* DigitWhichDetBranch = vertexTree->Branch("DigitWhichDet", &digitwhichdet); 
  TBranch* DigitTimeSmear = vertexTree->Branch("DigitTimeSmear", &digit_time_smear); 
  TBranch* DigitPmtId = vertexTree->Branch("DigitPmtId", &digit_pmt_id); 
  
  //Only used in the code
  TVector3 sensor_position; sensor_position.SetXYZ(0.,0.,0.);
  TVector3 hit_position; hit_position.SetXYZ(0.,0.,0.);
  TVector3 sensor_direction; sensor_direction.SetXYZ(0.,0.,0.);
  
  // Load the files
  dsReader = new RAT::DSReader(filename_ratpac);
  NbEntries = dsReader->GetTotal();
  
  
  // Load the trees 
  // load the ratpac trees and DS
  tri = new TChain("T");
  runtri = new TChain("runT");

  if (TString(filename_ratpac).MaybeWildcard()) {
    // Assume there is a runT in all files
    runtri->Add(filename_ratpac);
    RAT::DS::RunStore::SetReadTree(runtri);
  } else {
    // In single file case, we can check
    TFile *ftemp = TFile::Open(filename_ratpac);
    if (ftemp->Get("runT")) {
      runtri->Add(filename_ratpac);
      RAT::DS::RunStore::SetReadTree(runtri);
    } // else, no runT, so don't register runtri with RunStore
    
    delete ftemp;
  }
  
  RAT::DS::Root *branchDS = new RAT::DS::Root();
  tri->SetBranchAddress("ds", &branchDS);
  RAT::DS::RunStore::GetRun(branchDS);
  
  
  TH1::SetDefaultSumw2(kTRUE);
  
  // Analysis loop over all the events
  for (ULong64_t entry=0; entry<NbEntries; ++entry) {
    ds = dsReader->GetEvent(entry);
    
    event_num = entry;
    
    muon_found = false;
    
    // kind of progress bar...
    if (NbEntries > 10) {
      if ( entry%(NbEntries/10) == 0 ) { 
	cout << "Evt " << entry << " out of " << NbEntries << " events ===> " << Floor(Double_t(entry)/Double_t(NbEntries)*100.) << " %\n";
      }
    }
    
    // find GENIE info
    gst_tree->GetEntry(entry);
    
    event_num = i_ev;
    neut_code = code_n;
    neutrino_energy = E_nu; 
    momentum_transfer = mom_trans;
    muon_energy = E_l;
    muon_momentum.SetXYZ(Px_l,Py_l,Pz_l);
    muon_angle = muon_momentum.Angle(unit_vect);
    
    
    if (!is_cc) { interaction_type = "NC";}
    else {
     if (is_qel) { interaction_type = "QES - Weak[CC]";}
     if (is_res) { interaction_type = "RES - Weak[CC]";}
     if (is_mec) { interaction_type = "1Kaon - Weak[CC]";}
     if (is_dis) { interaction_type = "DIS - Weak[CC]";}
    }
    
    nav = new RAT::TrackNav(ds);
    cursor = new RAT::TrackCursor(nav->RAT::TrackNav::Cursor(false));  //toggle human readable cursor
    
    
    
    // Make sure the ratpac event and the GENIE event are the same (from muon energy) and direction 
    for(long iPart = 0; iPart<ds->GetMC()->GetMCParticleCount(); iPart++){ // Loop on all parents in that event
      if ( ds->GetMC()->GetMCParticle(iPart)->GetParticleName() == "mu-" || ds->GetMC()->GetMCParticle(iPart)->GetParticleName() == "mu+") {
	cout << "Lepton energy: " << muon_energy*1e3 << " MeV in GENIE and " << ds->GetMC()->GetMCParticle(iPart)->GetKE()+105.658 << " MeV in ratpac (KE+m_mu)\n";
      }
    }
    
    
    // Find track length and duration of ALL parent (initial) particles
    if(cursor->ChildCount()){
      for(long iCh = 0; iCh<ds->GetMC()->GetMCParticleCount(); iCh++){ // Loop on all particles in that event
	if(ds->GetMC()->GetMCParticle(iCh)->GetParticleName() == "mu-" || ds->GetMC()->GetMCParticle(iCh)->GetParticleName() == "mu+")  {
	  
	  muon_found = true;
	  
	  // go to particle start
	  cursor->GoChild(iCh); // go to particle
	  node = cursor->Here(); // "attach" node to this particle
	  
	  filemuonstartvertex.SetPxPyPzE(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  filemuondirectionvector.SetXYZ(node->GetMomentum().X()/node->GetMomentum().Mag(),node->GetMomentum().Y()/node->GetMomentum().Mag(),node->GetMomentum().Z()/node->GetMomentum().Mag());
	  
	  // go to particle end
	  node->Clear();
	  node = cursor->TrackEnd();
	  
	  filemuonstopvertex.SetPxPyPzE(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  
	  cursor->GoParent();
	  muon_number++;
	}
      }
    }
    
    run = RAT::DS::RunStore::Get()->GetRun(ds);
    
    pmtInfo = run->GetPMTInfo();
    lappdInfo = run->GetLAPPDInfo();
    
    //PMT loop (WhichDet is 1)
    for( long iPMT = 0; iPMT < ds->GetMC()->GetMCPMTCount(); iPMT++ ){
      for(long iPhot = 0; iPhot < ds->GetMC()->GetMCPMT(iPMT)->GetMCPhotonCount(); iPhot++){
	// 	new(DigitVertices_p[muon_number]) TLorentzVector(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetHitTime());
	
	hit_position.SetXYZ(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X() + 1724.0);
	sensor_position.SetXYZ(pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y(), 
			       pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z(), 
			       pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X() + 1724.0);
	sensor_direction.SetXYZ(pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y(), 
				pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z(), 
				pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X());
	
	hit_position.RotateUz(sensor_direction);
	
	digit_vect.SetXYZT(hit_position.X() + sensor_position.X(),
			   hit_position.Y() + sensor_position.Y(),
			   hit_position.Z() + sensor_position.Z(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetHitTime());
	filedigitverticesp->push_back(digit_vect);
	digitcharges.push_back(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetCharge());
	digitwhichdet.push_back(1);
	
      }
    }
    
    //LAPPD loop (WhichDet is 2)
    for( long iLAPPD = 0; iLAPPD < ds->GetMC()->GetMCLAPPDCount(); iLAPPD++ ){
      for(long iPhot = 0; iPhot < ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhotonCount(); iPhot++){
	// 	new(DigitVertices_p[muon_number]) TLorentzVector(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().X(),ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Y(),ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Z(),ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetHitTime());
	
	hit_position.SetXYZ(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Y(),
			   ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Z(),
			   ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().X() + 1724.0);
	sensor_position.SetXYZ(lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Y(), 
			       lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Z(), 
			       lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).X() + 1724.0);
	sensor_direction.SetXYZ(lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Y(), 
				lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Z(), 
				lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).X());
	
	hit_position.RotateUz(sensor_direction);
	
	digit_vect.SetXYZT(hit_position.X() + sensor_position.X(), 
			   hit_position.Y() + sensor_position.Y(),
			   hit_position.Z() + sensor_position.Z(),
			   ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetHitTime());
	filedigitverticesp->push_back(digit_vect);
	digitcharges.push_back(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetCharge());
	digitwhichdet.push_back(2);
      }
    }
    
    digit_time_smear = 0.;
    digit_pmt_id = 0.;
    
    if (muon_found){
      vertexTree->Fill();
    }
    
    // Cleaning to avoid memory leak (because of the nav size)
    if (muon_found){ node->Clear();}
    delete cursor;
    //     nav->Clear(); 
    delete nav;
  }
  
  f_GENIEFile.Close();
  delete run, pmtInfo, lappdInfo;
  delete tri, runtri, branchDS;
  delete dsReader;
  
  f_output.Write();
   
  f_output.Close();
  
  // Ends the timer
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << duration << " seconds\n";
  
}