///////////  Reads a RAT-PAC output files with PE information and creates a SK-like event display (function to choose event) ////////
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

void PlotEvent(ULong64_t entry){
  
  
}

void simple_event_display(const char* filename, ULong64_t entry) {
  
  // Load RAT libraries (for dsReader)
  gSystem->Load("$(RATPAC_PATH)/lib/libRATEvent.so");
  gStyle->SetPalette(54);
  
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
  
  TVector3 init_pos;
  TVector3 fin_pos;
  Double_t init_time, fin_time;
  
  Bool_t muon_found;
  Int_t muon_number = 0;
  
  TH2D *h_BarrelView_sensor, *h_BarrelView_hits;
  TH2D *h_TopView_sensor, *h_TopView_hits;
  TH2D *h_BottomView_sensor, *h_BottomView_hits;
  
  h_BarrelView_sensor = new TH2D("h_BarrelView_sensor","h_BarrelView_sensor",50,-TMath::Pi(),TMath::Pi(),50,-2000,2000);
  h_TopView_sensor = new TH2D("h_TopView_sensor","h_TopView_sensor",20,-1500,1500,20,-1500,1500);
  h_BottomView_sensor = new TH2D("h_BottomView_sensor","h_BottomView_sensor",20,-1500,1500,20,-1500,1500);
  
  h_BarrelView_hits = new TH2D("h_BarrelView_hits","h_BarrelView_hits",500,-TMath::Pi(),TMath::Pi(),500,-2000,2000);
  h_TopView_hits = new TH2D("h_TopView_hits","h_TopView_hits",200,-1500,1500,200,-1500,1500);
  h_BottomView_hits = new TH2D("h_BottomView_hits","h_BottomView_hits",200,-1500,1500,200,-1500,1500);
  
  
  // Starts the timer
  start = clock();
  
  //Only used in the code
  TVector3 ANNIE_center(0.0, -133.3, 1724.0);
  TVector3 sensor_position; sensor_position.SetXYZ(0.,0.,0.);
  TVector3 hit_position; hit_position.SetXYZ(0.,0.,0.);
  TVector3 hit_position_global; hit_position_global.SetXYZ(0.,0.,0.);
  TVector3 sensor_direction; sensor_direction.SetXYZ(0.,0.,0.);
  
  // Load the files
  dsReader = new RAT::DSReader(filename);
  NbEntries = dsReader->GetTotal();
  
  tri = new TChain("T");
  runtri = new TChain("runT");
  
  if (TString(filename).MaybeWildcard()) {
    // Assume there is a runT in all files
    runtri->Add(filename);
    RAT::DS::RunStore::SetReadTree(runtri);
  } else {
    // In single file case, we can check
    TFile *ftemp = TFile::Open(filename);
    if (ftemp->Get("runT")) {
      runtri->Add(filename);
      RAT::DS::RunStore::SetReadTree(runtri);
    } // else, no runT, so don't register runtri with RunStore
    
    delete ftemp;
  }
  
  RAT::DS::Root *branchDS = new RAT::DS::Root();
  tri->SetBranchAddress("ds", &branchDS);
  RAT::DS::RunStore::GetRun(branchDS);
  
  TH1::SetDefaultSumw2(kTRUE);
  
  
  ds = dsReader->GetEvent(entry);
  
  run = RAT::DS::RunStore::Get()->GetRun(ds);
  
  pmtInfo = run->GetPMTInfo();
  lappdInfo = run->GetLAPPDInfo();
  
  // Loop to find the max/min height of the PMTs (top/bottom). I know it's ugly but I ain't no programmer...
  Double_t max_PMTheight = 0.,min_PMTheight = 0.;
  for( Int_t iPMT = 0; iPMT < ds->GetMC()->GetMCPMTCount(); iPMT++ ){
    if (pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z() > max_PMTheight){
      max_PMTheight = pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z();
    }
    if (pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z() < min_PMTheight){
      min_PMTheight = pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z();
    }
  }
  
  //PMT loop (WhichDet is 1)
  for( Int_t iPMT = 0; iPMT < ds->GetMC()->GetMCPMTCount(); iPMT++ ){
    for(Int_t iPhot = 0; iPhot < ds->GetMC()->GetMCPMT(iPMT)->GetMCPhotonCount(); iPhot++){
      
      hit_position.SetXYZ(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X(),
			  ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y(),
			  ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z());
      sensor_position.SetXYZ(pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X(), 
			     pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y(), 
			     pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z());
      sensor_direction.SetXYZ(pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X(), 
			      pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y(), 
			      pmtInfo->GetDirection(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z());	
      hit_position.RotateUz(sensor_direction);	
      hit_position_global.SetXYZ(hit_position.X() + sensor_position.X(),
				 hit_position.Y() + sensor_position.Y(),
				 hit_position.Z() + sensor_position.Z());
      
      
      if (sensor_position.Z() < max_PMTheight + 50. && sensor_position.Z() > max_PMTheight - 50.){ // some kind of tolerance
	h_TopView_sensor->Fill(sensor_position.X(), sensor_position.Y());
	h_TopView_hits->Fill(hit_position_global.X(), hit_position_global.Y());
      } else if (sensor_position.Z() < min_PMTheight + 50. && sensor_position.Z() > min_PMTheight - 50.){ // some kind of tolerance
	h_BottomView_sensor->Fill(sensor_position.X(), sensor_position.Y());
	h_BottomView_hits->Fill(hit_position_global.X(), hit_position_global.Y());
      } else {
	    h_BarrelView_sensor->Fill(sensor_position.Phi(), sensor_position.Z());
	    h_BarrelView_hits->Fill(hit_position_global.Phi(), hit_position_global.Z());
      }
    }
  }
  
  //LAPPD loop (WhichDet is 2)
  for( Int_t iLAPPD = 0; iLAPPD < ds->GetMC()->GetMCLAPPDCount(); iLAPPD++ ){
    for(Int_t iPhot = 0; iPhot < ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhotonCount(); iPhot++){
      
      hit_position.SetXYZ(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().X() - ANNIE_center.X(),
			  ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Y() - ANNIE_center.Y(),
			  ds->GetMC()->GetMCLAPPD(iLAPPD)->GetMCPhoton(iPhot)->GetPosition().Z() - ANNIE_center.Z());
      sensor_position.SetXYZ(lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).X() - ANNIE_center.X(), 
			     lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Y() - ANNIE_center.Y(), 
			     lappdInfo->GetPosition(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Z() - ANNIE_center.Z());
      sensor_direction.SetXYZ(lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).X(), 
			      lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Y(), 
			      lappdInfo->GetDirection(ds->GetMC()->GetMCLAPPD(iLAPPD)->GetID()).Z());
      hit_position.RotateUz(sensor_direction);
      hit_position_global.SetXYZ(hit_position.X() + sensor_position.X(), 
				 hit_position.Y() + sensor_position.Y(),
				 hit_position.Z() + sensor_position.Z());
      
      if (sensor_position.Z() < max_PMTheight + 50. && sensor_position.Z() > max_PMTheight - 50.){ // some kind of tolerance
	h_TopView_sensor->Fill(sensor_position.X(), sensor_position.Y());
	h_TopView_hits->Fill(hit_position_global.X(), hit_position_global.Y());
      } else if (sensor_position.Z() < min_PMTheight + 50. && sensor_position.Z() > min_PMTheight - 50.){ // some kind of tolerance
	h_BottomView_sensor->Fill(sensor_position.X(), sensor_position.Y());
	h_BottomView_hits->Fill(hit_position_global.X(), hit_position_global.Y());
      } else {
	    h_BarrelView_sensor->Fill(sensor_position.Phi(), sensor_position.Z());
	    h_BarrelView_hits->Fill(hit_position_global.Phi(), hit_position_global.Z());
      }
    }
  }
  
  
  // Draw the histograms
  TCanvas* c1= new TCanvas("c1", "Blabla", 0,0, 1200, 1000);
  c1->Divide(2,3);
  c1->cd(1);
  h_TopView_sensor->DrawCopy("COLZ");
  c1->cd(2);
  h_TopView_hits->DrawCopy("COLZ");
  c1->cd(3);
  h_BarrelView_sensor->DrawCopy("COLZ");
  c1->cd(4);
  h_BarrelView_hits->DrawCopy("COLZ");
  c1->cd(5);
  h_BottomView_sensor->DrawCopy("COLZ");
  c1->cd(6);
  h_BottomView_hits->DrawCopy("COLZ");
  
  
//   delete run, pmtInfo, lappdInfo;
//   delete tri, runtri, branchDS;
//   delete dsReader;
  delete h_BarrelView_sensor; delete h_BarrelView_hits; delete h_TopView_sensor; delete h_TopView_hits; delete h_BottomView_sensor; delete h_BottomView_hits;
  
  // Ends the timer
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << duration << " seconds\n";
  
}