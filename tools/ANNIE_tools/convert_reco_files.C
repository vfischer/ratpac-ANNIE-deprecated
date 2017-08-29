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

void convert_reco_files(const char* filename) {
  
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
  
  std::clock_t start;
  double duration;
  
  ULong64_t NbEntries;
  
  TVector3 init_pos;
  TVector3 fin_pos;
  Double_t init_time, fin_time;
  TString nucl_cap_pdg_code;
  
  Bool_t muon_found;
  Int_t muon_number = 0;
  
  ROOT::Math::XYZTVector digit_vect(0.,0.,0.,0.);
  
  // Starts the timer
  start = clock();
  
  // Output file
  TFile f_output("output_reco-readable.root","RECREATE");
  // Tree and branches
  TTree *vertexTree = new TTree("vertexTree","All True Tank QE Events");
  
  TLorentzVector filemuonstartvertex(0.,0.,0.,0.);     
  TLorentzVector filemuonstopvertex(0.,0.,0.,0.);     
  TVector3 filemuondirectionvector(0.,0.,0.);
  std::vector<Double_t> digitcharges;
  std::vector<Int_t> digitwhichdet;
  std::vector<ROOT::Math::XYZTVector>  filedigitvertices;     
  std::vector<ROOT::Math::XYZTVector>* filedigitverticesp = &filedigitvertices;     
  
  TBranch* MuonStartBranch = vertexTree->Branch("MuonStartVertex",&filemuonstartvertex);     
  TBranch* MuonStopBranch = vertexTree->Branch("MuonStopVertex", &filemuonstopvertex);     
  TBranch* MuonDirectionBranch = vertexTree->Branch("MuonDirection", &filemuondirectionvector);     
  TBranch* DigitVertexBranch = vertexTree->Branch("DigitVertices", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &filedigitverticesp);
  TBranch* DigitChargesBranch = vertexTree->Branch("DigitCharges", &digitcharges); 
  TBranch* DigitWhichDetBranch = vertexTree->Branch("DigitWhichDet", &digitwhichdet); 
  
  //   vector<double> DigitCharges, DigitWhichDet; 
  //   DigitCharges.clear(), DigitWhichDet.clear();
  //   
  //   TClonesArray *StartVertex = new TClonesArray("TLorentzVector");
  //   TClonesArray &StartVertex_p = *StartVertex;
  //   TClonesArray *StopVertex = new TClonesArray("TLorentzVector");
  //   TClonesArray &StopVertex_p = *StopVertex;
  //   TClonesArray *Direction = new TClonesArray("TVector3");
  //   TClonesArray &Direction_p = *Direction;
  //   TClonesArray *DigitVertices = new TClonesArray("TLorentzVector");
  //   TClonesArray &DigitVertices_p = *DigitVertices;
  //  
  //   vertexTree->Branch("StartVertex",&StartVertex); 
  //   vertexTree->Branch("StopVertex",&StopVertex); 
  //   vertexTree->Branch("Direction",&Direction); 
  //   vertexTree->Branch("DigitVertices",&DigitVertices);
  //   vertexTree->Branch("DigitCharges",&DigitCharges,"DigitCharges/D");
  //   vertexTree->Branch("DigitWhichDet",&DigitWhichDet,"DigitWhichDet/D");
  
  // Load the files
  dsReader = new RAT::DSReader(filename);
  NbEntries = dsReader->GetTotal();
  
  tri = new TChain("T");
  runtri = new TChain("runT");
  cout << "aa\n";
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
  
  cout << "bb\n";
  RAT::DS::Root *branchDS = new RAT::DS::Root();
  tri->SetBranchAddress("ds", &branchDS);
  RAT::DS::RunStore::GetRun(branchDS);
  
  //   // Test if phase number (1 or 2) is correct
  //   if (phase != 1 && phase != 2) {
  //     cout << "Wrong ANNIE Phase! Only 1 or 2 accepted so far. Aborting... ****\n" << endl;
  //     return;
  //   }
  
  TH1::SetDefaultSumw2(kTRUE);
  
  // Analysis loop over all the events
  for (ULong64_t entry=0; entry<NbEntries; ++entry) {
    ds = dsReader->GetEvent(entry);
    
    muon_found = false;
    
    // kind of progress bar...
    if (NbEntries > 10) {
      if ( entry%(NbEntries/10) == 0 ) { 
	cout << "Evt " << entry << " out of " << NbEntries << " events ===> " << Floor(Double_t(entry)/Double_t(NbEntries)*100.) << " %\n";
      }
    }
    
    nav = new RAT::TrackNav(ds);
    cursor = new RAT::TrackCursor(nav->RAT::TrackNav::Cursor(false));  //toggle human readable cursor
    
    // Find track length and duration of ALL parent (initial) particles
    if(cursor->ChildCount()){
      for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParticleCount(); iCh++){ // Loop on all particles in that event
	if(ds->GetMC()->GetMCParticle(iCh)->GetParticleName() == "mu-" || ds->GetMC()->GetMCParticle(iCh)->GetParticleName() == "mu+")  {
	  
	  muon_found = true;
	  
	  // go to particle start
	  cursor->GoChild(iCh); // go to particle
	  node = cursor->Here(); // "attach" node to this particle
	  
	  filemuonstartvertex.SetPxPyPzE(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  filemuondirectionvector.SetXYZ(node->GetMomentum().X()/node->GetMomentum().Mag(),node->GetMomentum().Y()/node->GetMomentum().Mag(),node->GetMomentum().Z()/node->GetMomentum().Mag());
	  //       new(StartVertex_p[muon_number]) TLorentzVector(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  //       new(Direction_p[muon_number]) TVector3(node->GetMomentum().X()/node->GetMomentum().Mag(),node->GetMomentum().Y()/node->GetMomentum().Mag(),node->GetMomentum().Z()/node->GetMomentum().Mag());
	  
	  // go to particle end
	  node->Clear();
	  node = cursor->TrackEnd();
	  
	  filemuonstopvertex.SetPxPyPzE(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  //       new(StopVertex_p[muon_number]) TLorentzVector(node->GetEndpoint().X(),node->GetEndpoint().Y(),node->GetEndpoint().Z(),node->GetKE());
	  
	  cursor->GoParent();
	  muon_number++;
	}
      }
    }
    
    run = RAT::DS::RunStore::Get()->GetRun(ds);
    
    pmtInfo = run->GetPMTInfo();
    
    //PMT loop
    for( size_t iPMT = 0; iPMT < ds->GetMC()->GetMCPMTCount(); iPMT++ ){
      for(size_t iPhot = 0; iPhot < ds->GetMC()->GetMCPMT(iPMT)->GetMCPhotonCount(); iPhot++){
	// 	new(DigitVertices_p[muon_number]) TLorentzVector(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z(),ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetHitTime());
	
	
	// 	cout << "Pos POMT " << ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X()<< " " <<
	// 	ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y() << " " <<
	// 			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z() << endl;
	// 	cout << "Pos glob " << ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X() << " " <<
	// 			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y()<< " " <<
	// 			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z()<< endl;
	
	digit_vect.SetXYZT(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().X() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).X(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Y() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Y(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetPosition().Z() + pmtInfo->GetPosition(ds->GetMC()->GetMCPMT(iPMT)->GetID()).Z(),
			   ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetHitTime());
	filedigitverticesp->push_back(digit_vect);
	digitcharges.push_back(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhoton(iPhot)->GetCharge());
	digitwhichdet.push_back(1);
	
      }
    }
    
    if (muon_found){
      vertexTree->Fill();
    }
    
    // Cleaning to avoid memory leak (because of the nav size)
    if (muon_found){ node->Clear();}
    delete cursor;
    //     nav->Clear(); 
    delete nav;
  }
  
  
  f_output.Write();
  
  delete run, pmtInfo;
  delete tri, runtri, branchDS;
  delete dsReader;
  f_output.Close();
  
  // Ends the timer
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << duration << " seconds\n";
  
}