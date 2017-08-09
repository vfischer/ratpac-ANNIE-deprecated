///////////  Reads a RAT-PAC output files with PE information and generates a 3-D map (position,PE) ////////
///////////  PMTs of interest depends on the phase number (1 or 2) ////////
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
#include <RAT/DSReader.hh>
#include <RAT/TrackNav.hh>
#include <RAT/TrackCursor.hh>
#include <RAT/TrackNode.hh>

using namespace std;
using namespace TMath;

void get_Ncap_PE_map(const char* filename, Int_t phase) {
  
  // Load RAT libraries (for dsReader)
  gSystem->Load("$(RATPAC_PATH)/lib/libRATEvent.so");
  
  // Initialization
  RAT::DSReader *dsReader;
  RAT::DS::Root *ds;
  RAT::TrackNav *nav;
  RAT::TrackCursor *cursor;
  RAT::TrackNode *node;
  
  std::clock_t start;
  double duration;
  
  ULong64_t NbEntries;
  
  TVector3 init_pos;
  TVector3 fin_pos;
  Double_t init_time, fin_time;
  TString nucl_cap_pdg_code;
  
  // Histos
  TH3F *hNeutron_start_point_3D;
  TH3F *hNeutron_cap_point_3D, *hNeutron_cap_point_nH_3D, *hNeutron_cap_point_nGd_3D; 
  TH3F *hNeutron_cap_point_PE_3D, *hNeutron_cap_point_nH_PE_3D, *hNeutron_cap_point_nGd_PE_3D; 
  hNeutron_start_point_3D = new TH3F("hNeutron_start_point_3D","3D plot of the neutron start points; Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_3D = new TH3F("hNeutron_cap_point_3D","3D plot of the neutron capture points; Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_nH_3D = new TH3F("hNeutron_cap_point_nH_3D","3D plot of the neutron capture points (nH; Z [mm]; X [mm]; Y [mm])",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_nGd_3D = new TH3F("hNeutron_cap_point_nGd_3D","3D plot of the neutron capture points (nGd); Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_PE_3D = new TH3F("hNeutron_cap_point_PE_3D","3D plot of PE deposition; Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_nH_PE_3D = new TH3F("hNeutron_cap_point_nH_PE_3D","3D plot of PE deposition (nH); Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  hNeutron_cap_point_nGd_PE_3D = new TH3F("hNeutron_cap_point_nGd_PE_3D","3D plot of PE deposition (nGd); Z [mm]; X [mm]; Y [mm]",25,0,5000,30,-3000,3000,30,-3000,3000);
  
  // Starts the timer
  start = clock();
  
  // Output file
  TFile f_output("Ncap_PE_map.root","RECREATE");
  
  // Load the files
  dsReader = new RAT::DSReader(filename);
  NbEntries = dsReader->GetTotal();
  
  // Test if phase number (1 or 2) is correct
  if (phase != 1 && phase != 2) {
    cout << "Wrong ANNIE Phase! Only 1 or 2 accepted so far. Aborting... ****\n" << endl;
    return;
  }
  
  TH1::SetDefaultSumw2(kTRUE);
  
  // Analysis loop over all the events
  for (ULong64_t entry=0; entry<NbEntries; ++entry) {
    ds = dsReader->GetEvent(entry);
    
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
      cursor->GoChild(0);
      node = cursor->Here();
      init_pos  = node->GetEndpoint();
      init_time = node->GetGlobalTime();
      
//       cout << "INITIAL: position = " << init_pos.x() << " " <<  init_pos.y() << " " << init_pos.z() << ", time = " << init_time << ", energy = " << node->GetKE() << endl;
//       cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
//       cout << node->GetTrackID() << " " << node->GetStepID() << endl;
      
      node->Clear();
      node = cursor->TrackEnd();
      fin_pos   = node->GetEndpoint();	
      fin_time = node->GetGlobalTime();
      
//       cout << "FINAL: position = " << fin_pos.x() << " " <<  fin_pos.y() << " " << fin_pos.z() << ", time = " << fin_time << ", energy = " << node->GetKE() << endl;
//       cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
//       cout << node->GetTrackID() << " " << node->GetStepID() << endl;
      
      
      hNeutron_start_point_3D->Fill(init_pos.z(),init_pos.x(),init_pos.y());
      
      
      if(node->GetProcess() == "nCapture"){
	cursor->GoTrackEnd(); // Last interaction of primary part.
	node = cursor->Here();
	cursor->GoChild(cursor->ChildCount()-1);
	cursor->GoTrackStart();
	node = cursor->Here();
	//  	    cout << node->GetVolume() << endl;
	// 	    cout << "Primary -- " << node->GetPDGCode() << endl;
	nucl_cap_pdg_code = to_string(node->GetPDGCode());
	if (TPMERegexp("100001[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	  hNeutron_cap_point_nH_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y());
	  hNeutron_cap_point_nH_PE_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y(),ds->GetMC()->GetNumPE());
// 	  cout << " ===>  n-H !!\n\n";
	} 
	if (TPMERegexp("100064[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	  hNeutron_cap_point_nGd_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y());
	  hNeutron_cap_point_nGd_PE_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y(),ds->GetMC()->GetNumPE());
// 	  cout << " ===>  n-Gd !!\n\n";
	}
	hNeutron_cap_point_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y());
	hNeutron_cap_point_PE_3D->Fill(fin_pos.z(),fin_pos.x(),fin_pos.y(),ds->GetMC()->GetNumPE());
	cursor->GoParent();
      }
      
      cursor->GoParent();
    }
    
    // Cleaning to avoid memory leak (because of the nav size)
    node->Clear();
    delete cursor;
    nav->Clear(); delete nav;
  }
  // ******************* End of loop ******************* //
  
  // Divides the PE maps by the number of events in each bin (to normatlize them)
  hNeutron_cap_point_PE_3D->Divide(hNeutron_cap_point_PE_3D, hNeutron_cap_point_3D);
  hNeutron_cap_point_nGd_PE_3D->Divide(hNeutron_cap_point_nGd_PE_3D, hNeutron_cap_point_nGd_3D);
  hNeutron_cap_point_nH_PE_3D->Divide(hNeutron_cap_point_nH_PE_3D, hNeutron_cap_point_nH_3D);
  
  // Some graphical options
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat("");
  gStyle->SetLabelFont(62,"");
  gStyle->SetLabelSize(0.047,"");
  gStyle->SetLabelFont(62,"xyz");
  gStyle->SetLabelSize(0.042,"xyz");
  gStyle->SetTitleFont(62,"xyz");
  gStyle->SetTitleFontSize(0.045);
  gStyle->SetTitleFont(62);
  gStyle->SetTitleSize(0.044,"xyz");
  gStyle->SetTitleOffset(1.0,"x");
  gStyle->SetTitleOffset(1.5,"y");
  gStyle->SetLabelOffset(0.0001,"x");
  gStyle->SetStripDecimals(kFALSE);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetOptFit(1111);
  gStyle->SetStatW(0.35);
  gStyle->SetStatH(0.25);
  //gStyle->SetPadTickX(kTRUE);  	
  //gStyle->SetPadTickY(kTRUE);  	
  gStyle->SetPalette(1);
  gStyle->SetNumberContours(99);
  
  hNeutron_start_point_3D->Write();
  hNeutron_cap_point_nH_3D->Write();
  hNeutron_cap_point_nH_PE_3D->Write();
  hNeutron_cap_point_nGd_3D->Write();
  hNeutron_cap_point_nGd_PE_3D->Write();
  hNeutron_cap_point_3D->Write();
  hNeutron_cap_point_PE_3D->Write();
  
  f_output.Write();
  
  delete dsReader;
  f_output.Close();
  
  // Ends the timer
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << duration << " seconds\n";
  
}