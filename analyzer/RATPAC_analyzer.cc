//=================================================================//
// -------------- Preliminary RATPAC analyzer --------------------- //
//=================================================================//

#include "RATPAC_analyzer.hh"

#include <TPRegexp.h>
#include <TEnv.h>

using namespace TMath;
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ============================================  INITIALIZATION ===================================
void Analyzer::Initialization(){
  
  // Starts the timer
  start = clock();
  
  // Debug mode
  debug = false;
  
  // Capture nuclei PDG codes
//   pdg_nucl("1000[0-9][0-9][0-9][0-9][0-9]");
//   pdg_gd("100064[0-9][0-9][0-9]");
//   pdg_h("100001[0-9][0-9][0-9]");
  
  // Histo time !
  hCharge = new TH1F("hCharge","Charge in all PMTs for one event (perPMT)",100,0,10);
  hCharge_tot = new TH1F("hCharge_tot","Charge in all PMTs for one event (total)",1000,0,1000);
  hCharge_XZ = new TH2F("hCharge_XZ","XZ distributions of charges",10,-1,9,10,-1,9);
  
  // PMT infos
  hPMTx = new TH1F("hPMTx","PMT in x",20,-10,10);
  hPMTy = new TH1F("hPMTy","PMT in y",20,-10,10);
  hPMTz = new TH1F("hPMTz","PMT in z",20,-10,10);
  hPMTcard = new TH1F("hPMTcard","PMT card (as in data)",20,2,22);
  hPMTchannel = new TH1F("hPMTchannel","PMT channel (as in data)",3,0,3);
  if (job_run1) {
    hPMTID = new TH1F("hPMTID","PMT ID",100,0,100); 
  }
  if (job_run2) {
    hPMTID = new TH1F("hPMTID","PMT ID",200,0,200);
  }
  
  // Track infos
  hTrackDuration = new TH1F("hTrackDuration","Track duration of the primary particle (ns)",1000,0,1000000);
  hTrackDuration_nGd = new TH1F("hTrackDuration_nGd","Track duration of the primary particle (ns) - nGd",1000,0,1000000);
  hTrackDuration_nH = new TH1F("hTrackDuration_nH","Track duration of the primary particle (ns) - nH",1000,0,1000000);
  hTrackLength = new TH1F("hTrackLength","Displacement between creation and detection (mm)",200,0,2000);
  hTrackLength_nGd = new TH1F("hTrackLength_nGd","Displacement between creation and detection (mm) - nGd",200,0,2000);
  hTrackLength_nH = new TH1F("hTrackLength_nH","Displacement between creation and detection (mm) - nH",200,0,2000);
  
  // Energy infos
  hNumPE  = new TH1F("hNumPE","Num of PE (PMT summed)",1000,0,1000);
  hNHit = new TH1F("hNHit","Num of hits (summed)", 1000,0,1000);
  if (job_run1) {
    hNbPMThit = new TH1F("hNbPMThit","Number of PMTs hit per events",100,0,100);
  }
  if (job_run2) {
    hNbPMThit = new TH1F("hNbPMThit","Number of PMTs hit per events",200,0,200);
  }
  hScintEdep  = new TH1F("hScintEdep","Scintillation deposited energy",1000,0,100);
  hScintEdepQuen  = new TH1F("hScintEdepQuen","Scintillation deposited energy (quenched)",1000,0,100);
  hScintEdep_x  = new TH1F("hScintEdep_x","Scintillation deposited energy - X position",4000,-2000,2000);
  hScintEdep_y  = new TH1F("hScintEdep_y","Scintillation deposited energy - Y position",4000,-2000,2000);
  hScintEdep_z  = new TH1F("hScintEdep_z","Scintillation deposited energy - Z position",4000,-2000,2000);
  hEdep_x  = new TH1F("hEdep_x","Deposited energy - X position",4000,-2000,2000);
  hEdep_y  = new TH1F("hEdep_y","Deposited energy - Y position",4000,-2000,2000);
  hEdep_z  = new TH1F("hEdep_z","Deposited energy - Z position",4000,-2000,2000);
  
  if (job_run1) {
    for(Int_t i=0; i<NbPMT_run1; i++) {
      hCharge_perPMT_run1[i] = new TH1F(Form("hCharge_perPMT_run1[%i]",i+1),Form("Charge in the %i channel",i+1), 100,0,10);
    }
  }
  if (job_run2) {
    for(Int_t i=0; i<NbPMT_run2; i++) {
      hCharge_perPMT_run2[i] = new TH1F(Form("hCharge_perPMT_run2[%i]",i+1),Form("Charge in the %i channel",i+1), 100,0,10);
    }
  }
  
  // Initialization time   
  broken_pmt_vec.clear(); ncv_pmt_vec.clear();
  Nneutrons = 0, Ncaptures = 0, Ncaptures_h = 0, Ncaptures_gd = 0;
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ============================================  LOOP ===================================
void Analyzer::Loop() {
  
  // PMT grid coordinates (not in ratpac x,y,z)
    int pmt_x_array_run1[] = {0,0,0,1,2,3,4,5,6,7,7,7,1,2,2,1,3,4,4,3,5,6,6,5,1,2,2,1,3,4,4,3,5,6,6,5,1,2,2,1,3,4,4,3,5,6,6,5,0,0,0,1,2,3,4,5,6,7,7,7};
    int pmt_z_array_run1[] = {3,2,1,0,0,0,0,0,0,1,2,3,1,1,2,2,1,1,2,2,1,1,2,2,3,3,4,4,3,3,4,4,3,3,4,4,5,5,6,6,5,5,6,6,5,5,6,6,4,5,6,7,7,7,7,7,7,6,5,4};
    int pmt_card_array_run1[] = {4,4,4,4,5,5,5,5,6,6,6,6,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,13,13,13,13,14,14,14,14,15,15,15,15,16,16,16,16,18,18,18,18,20,20,20,20};
    int pmt_channel_array_run1[] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
  
  if (job_run1){ 
    broken_pmt_vec.push_back(6); broken_pmt_vec.push_back(19);broken_pmt_vec.push_back(37); broken_pmt_vec.push_back(49);
    ncv_pmt_vec.push_back(6); ncv_pmt_vec.push_back(49);
  }
  
  TH1::SetDefaultSumw2(kTRUE);
  entry = chain->LoadTree(0); 
  
  Int_t current_tree = chain->GetTreeNumber();
  cout << "First file: " << chain->GetFile()->GetName() << endl;
  f_output_txt << "\nFirst file: " << chain->GetFile()->GetName() << endl;
  
  
  // Analysis loop over all the events
  for (ULong64_t entry=0; entry<NbEntries; entry++) {
    if (current_tree != chain->GetTreeNumber()) {
      current_tree = chain->GetTreeNumber();
      cout << "--- evt " << entry << " out of " << NbEntries << " => Next file: " << chain->GetFile()->GetName() << "\n";
      f_output_txt << "--- evt " << entry << " out of " << NbEntries << " => Next file: " << chain->GetFile()->GetName() << "\n";
    }
    //     chain->GetEntry(entry);
    
    ds = dsReader->GetEvent(entry);
    
    // kind of progress bar...
    if (NbEntries > 10) {
      if ( entry%(NbEntries/10) == 0 ) { 
	cout << "Evt " << entry << " out of " << NbEntries << " events ===> " << Floor(Double_t(entry)/Double_t(NbEntries)*100.) << " %\n";
	f_output_txt << "Evt " << entry << " out of " << NbEntries << " events ===> " << Floor(Double_t(entry)/Double_t(NbEntries)*100.) << " %\n";
      }
    }
    
    // reset some counters
    charge_tot=0;
    is_nGd = false; is_nH = false;
    
    // Analysis part
    //     cout << entry << " " << ds->GetMC()->GetMCSummary()->GetTotalScintEdep()  << " " << ds->GetMC()->GetNumPE() <<  endl;
    
    //PMT loop
    for( size_t iPMT = 0; iPMT < ds->GetMC()->GetMCPMTCount(); iPMT++ ){
      if (!binary_search(broken_pmt_vec.begin(), broken_pmt_vec.end(), ds->GetMC()->GetMCPMT(iPMT)->GetID()+1)){
	if (job_run1 && ds->GetMC()->GetMCPMT(iPMT)->GetID()+1 == 61 && ds->GetMC()->GetMCPMT(iPMT)->GetID()+1 == 62) { continue;}
	
	hPMTID->Fill(ds->GetMC()->GetMCPMT(iPMT)->GetID()+1);
	
	if (job_run1){ 
	  hPMTx->Fill(pmt_x_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]);
	  hPMTy->Fill(0); 
	  hPMTz->Fill(pmt_z_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]); 
	  hPMTcard->Fill(pmt_card_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]); 
	  hPMTchannel->Fill(pmt_channel_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]); 
	  hCharge_XZ->Fill(pmt_x_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()],pmt_z_array_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]);
	  hCharge_perPMT_run1[ds->GetMC()->GetMCPMT(iPMT)->GetID()]->Fill(ds->GetMC()->GetMCPMT(iPMT)->GetCharge());
	}
	
	if (job_run2){ 
	  hCharge_perPMT_run2[ds->GetMC()->GetMCPMT(iPMT)->GetID()]->Fill(ds->GetMC()->GetMCPMT(iPMT)->GetCharge());
	}
	
	hCharge->Fill(ds->GetMC()->GetMCPMT(iPMT)->GetCharge());
	charge_tot += ds->GetMC()->GetMCPMT(iPMT)->GetCharge();
	
	hNHit->Fill(ds->GetMC()->GetMCPMT(iPMT)->GetMCPhotonCount());
      }   
    }
    
    hNbPMThit->Fill(ds->GetMC()->GetMCPMTCount());
    hNumPE->Fill(ds->GetMC()->GetNumPE());
    
    hCharge_tot->Fill(charge_tot);
    hScintEdep->Fill(ds->GetMC()->GetMCSummary()->GetTotalScintEdep());
    hScintEdepQuen->Fill(ds->GetMC()->GetMCSummary()->GetTotalScintEdepQuenched());
    hScintEdep_x->Fill(ds->GetMC()->GetMCSummary()->GetTotalScintCentroid().x());
    hScintEdep_y->Fill(ds->GetMC()->GetMCSummary()->GetTotalScintCentroid().y());
    hScintEdep_z->Fill(ds->GetMC()->GetMCSummary()->GetTotalScintCentroid().z());
    hEdep_x->Fill(ds->GetMC()->GetMCSummary()->GetEnergyCentroid().x());
    hEdep_y->Fill(ds->GetMC()->GetMCSummary()->GetEnergyCentroid().y());
    hEdep_z->Fill(ds->GetMC()->GetMCSummary()->GetEnergyCentroid().z());
    
    hTrackLength->Fill((ds->GetMC()->GetMCSummary()->GetEnergyCentroid() - ds->GetMC()->GetMCParticle(0)->GetPosition()).Mag());
    
//     cout << ds->GetMC()->GetMCSummary()->GetEnergyLossByVolume("detector") << endl;
    
    nav = new RAT::TrackNav(ds);
    cursor = new RAT::TrackCursor(nav->RAT::TrackNav::Cursor(false));  //toggle human readable cursor
    
    if(cursor->ChildCount()){
      cursor->GoChild(0);
      node = cursor->Here();
      init_pos  = node->GetMomentum();
      init_time = node->GetGlobalTime();
      
      node = cursor->TrackEnd();
      fin_pos   = node->GetMomentum();	
      fin_time = node->GetGlobalTime();
//       	cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
      
      disp = (fin_pos - init_pos).Mag();
      deltat = fin_time - init_time;
      // 	cout << disp << " " << deltat << endl;
      hTrackDuration->Fill(deltat);
      cursor->GoParent();
    }
    
    if(ds->GetMC()->GetMCParticle(0)->GetPDGCode() == 2112){ // only for neutrons, beginning of tracking loop
      if(cursor->ChildCount()){
	node = cursor->Here();
	for(size_t iCh = 0; iCh<cursor->ChildCount(); iCh++){ //Primary Particle Tracks
	  cursor->GoChild(iCh);
	  cursor->GoTrackEnd(); // Last interaction of primary part.
	  node = cursor->Here();
//  	  cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetStepID() << endl;
	  if(node->GetProcess() == "nCapture"){
	    cursor->GoChild(cursor->ChildCount()-1);
	    cursor->GoTrackStart();
	    node = cursor->Here();
//  	    cout << node->GetVolume() << endl;
// 	    cout << "Primary -- " << node->GetPDGCode() << endl;
	    nucl_cap_pdg_code = to_string(node->GetPDGCode());
	    if (TPMERegexp("100001[0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      is_nH = true;
	      Ncaptures_h++;
	      hTrackDuration_nH->Fill(deltat);
	      hTrackLength_nH->Fill((ds->GetMC()->GetMCSummary()->GetEnergyCentroid() - ds->GetMC()->GetMCParticle(0)->GetPosition()).Mag());
	    } 
	    if (TPMERegexp("100064[0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      is_nGd = true;
	      Ncaptures_gd++;
	      hTrackDuration_nGd->Fill(deltat); 
	      hTrackLength_nGd->Fill((ds->GetMC()->GetMCSummary()->GetEnergyCentroid() - ds->GetMC()->GetMCParticle(0)->GetPosition()).Mag());
	    }    
	    cursor->GoParent();
	    Ncaptures++;
	  }
	  
// 	  for(size_t jCh = 0; jCh<cursor->ChildCount()-1; jCh++){ //Secondary Particle Tracks
// 	      cursor->GoChild(jCh);
// 	      node = cursor->Here();
// // 	      cout << "Secondary -- " << node->GetPDGCode() << " " << node->GetVolume() << " " <<  << endl;	      
// 	      cursor->GoParent();
// 	    }
	    
	  cursor->GoTrackStart();
	  cursor->GoParent();
		
      Nneutrons++; 
//       cout << ds->GetMC()->GetMCSummary()->GetEnergyLossByVolume("ncv_liquid") << endl;
//       cout << ds->GetMC()->GetMCTrack(0)->GetMCTrackStep(0)->GetVolume() << endl;
	} // end of primary particle track
      }
    } // end of tracking loop
    
    // Cleaning to avoid memory leak (because of the nav size)
    node->Clear();
  delete cursor;
  nav->Clear(); delete nav;
  
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ============================================  FINALIZATION ===================================
void Analyzer::Finalize(){
  
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
  
  // Plotting  
  c1 = new TCanvas("c1", "Charge and amp infos", 0,0, 1200, 1000);
  c1->Divide(2,2);
  c1->cd(1);
  hCharge->DrawCopy();
  c1->Write(); 
  delete c1;
  
  c2 = new TCanvas("c2", "PMT infos", 0,0, 1200, 1000);
  c2->Divide(3,2);
  c2->cd(1);
  hPMTx->DrawCopy();
  c2->cd(2);
  hPMTy->DrawCopy();
  c2->cd(3);
  hPMTz->DrawCopy();
  c2->cd(4);
  hPMTID->DrawCopy();
  c2->Write(); 
  delete c2;
  
  f_output->Write();
  
  cout << "Neutrons created: " << Nneutrons << endl;
  cout << "Out of " << Ncaptures << " neutron captures: \n";
  cout << "\t -> " << Ncaptures_gd << " occurred on Gd.\n";
  cout << "\t -> " << Ncaptures_h << " occurred on H.\n";
  f_output_txt << "Neutrons created: " << Nneutrons << endl;
  f_output_txt << "Out of " << Ncaptures << " neutron captures: \n";
  f_output_txt << "\t -> " << Ncaptures_gd << " occurred on Gd\n";
  f_output_txt << "\t -> " << Ncaptures_h << " occurred on H\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes the saved output files (root and log)
Bool_t Analyzer::SetSaveFile() {
  
  save = InputFiles.front();
  
  if (TPMERegexp("\\*").Match(save)) { TPMERegexp("\\*.*").Substitute(save,"STAR.root");}
  else if (InputFiles.size()>1) {
    TPMERegexp Last("(\\d+)\\.root$"); 
    Last.Match(InputFiles.back());
    //     if (Last.NMatches()>1) { Last.Substitute(save,"$1-"+Last[1]+".root"); cout << TString(Last[1]) << endl; cout << TString(Last[0]) << endl;}
  }
  
  TString opt = job;
  TPMERegexp("\\W","g").Substitute(opt,"_");
  if (opt != "") { opt += "_"; }
  
  TPMERegexp FileName("([^/]+)$");
  if (FileName.Match(save)) { save = "Analyzer_" + opt + FileName[0];}
  else {
    cerr << "***Error Analyzer::SetSaveFile2: Can not catch save file name from this input file name: " << save
    << "\nCheck the output path ?\n";
    return false;
  }
  
  f_output = new TFile(output_dir + save,"RECREATE");
  if (!f_output->IsOpen()) {
    cerr << "***Error SetSaveFile: Can not open this TFile: " << output_dir + save
    << "\nCheck the output path ?\n";
    return false;
  }
  
  log = save;
  TPMERegexp("\\.root$").Substitute(log,"_LOG.txt");
  f_output_txt.open(output_dir + log, ios::out );
  
  cout << "Creating ROOT file: " << save << endl;
  f_output_txt << "Creating ROOT file: " << save << endl;
  
  cout << "Creating LOG file: " << log << endl;
  f_output_txt << "Creating LOG file: " << log << endl;
  
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//constructor
Analyzer::Analyzer(vector<TString> InFiles, const TString jobtype, const TString outputdir):
InputFiles(InFiles), job(jobtype), output_dir(outputdir)
{
  
  job_simu = false;
  
  if ( job == "run1" ){
    job_run1 = true; 
  } else  if ( job == "run1_hefty" ){
    job_run1_hefty = true;
  } else if ( job == "run2" ){
      job_run2 = true; 
    } else {
      cout << " *** Unknown job type, stopping now ... ***" << endl;
      abort();
    }
    
    chain = new TChain("T");
  
  for (vector<TString>::iterator it = InFiles.begin(); it != InFiles.end(); ++it) {
    file = new TFile((*it),"READ");
    
    dsReader = new RAT::DSReader(file->GetName());
    
    chain->Add(*it);
    
    //     chain->SetMakeClass(1);
    //     chain->SetBranchAddress("fUniqueID", &fUniqueID, &b_ds_fUniqueID);
    //     chain->SetBranchAddress("fBits", &fBits, &b_ds_fBits);
    //     chain->SetBranchAddress("runID", &runID, &b_ds_runID);
    //     chain->SetBranchAddress("ratVersion", &ratVersion, &b_ds_ratVersion);
    //     chain->SetBranchAddress("procResult", &procResult_, &b_ds_procResult_);
    //     chain->SetBranchAddress("procResult.first", procResult_first, &b_procResult_first);
    //     chain->SetBranchAddress("procResult.second", procResult_second, &b_procResult_second);
    //     chain->SetBranchAddress("mc", &mc_, &b_ds_mc_);
    //     chain->SetBranchAddress("mc.fUniqueID", mc_fUniqueID, &b_mc_fUniqueID);
    //     chain->SetBranchAddress("mc.fBits", mc_fBits, &b_mc_fBits);
    //     chain->SetBranchAddress("mc.id", mc_id, &b_mc_id);
    //     chain->SetBranchAddress("mc.numPE", mc_numPE, &b_mc_numPE);
    //     chain->SetBranchAddress("mc.numDarkHits", mc_numDarkHits, &b_mc_numDarkHits);
    //     chain->SetBranchAddress("mc.utc.fSec", mc_utc_fSec, &b_mc_utc_fSec);
    //     chain->SetBranchAddress("mc.utc.fNanoSec", mc_utc_fNanoSec, &b_mc_utc_fNanoSec);
    //     chain->SetBranchAddress("mc.particle", mc_particle, &b_mc_particle);
    //     chain->SetBranchAddress("mc.parent", mc_parent, &b_mc_parent);
    //     chain->SetBranchAddress("mc.track", mc_track, &b_mc_track);
    //     chain->SetBranchAddress("mc.pmt", mc_pmt, &b_mc_pmt);
    //     chain->SetBranchAddress("calib", &calib_, &b_ds_calib_);
    //     chain->SetBranchAddress("calib.fUniqueID", &calib_fUniqueID, &b_calib_fUniqueID);
    //     chain->SetBranchAddress("calib.fBits", &calib_fBits, &b_calib_fBits);
    //     chain->SetBranchAddress("calib.id", &calib_id, &b_calib_id);
    //     chain->SetBranchAddress("calib.mode", &calib_mode, &b_calib_mode);
    //     chain->SetBranchAddress("calib.intensity", &calib_intensity, &b_calib_intensity);
    //     chain->SetBranchAddress("calib.name", &calib_name, &b_calib_name);
    //     chain->SetBranchAddress("calib.utc.fSec", &calib_utc_fSec, &b_calib_utc_fSec);
    //     chain->SetBranchAddress("calib.utc.fNanoSec", &calib_utc_fNanoSec, &b_calib_utc_fNanoSec);
    //     chain->SetBranchAddress("calib.pos.fUniqueID", &calib_pos_fUniqueID, &b_calib_pos_fUniqueID);
    //     chain->SetBranchAddress("calib.pos.fBits", &calib_pos_fBits, &b_calib_pos_fBits);
    //     chain->SetBranchAddress("calib.pos.fX", &calib_pos_fX, &b_calib_pos_fX);
    //     chain->SetBranchAddress("calib.pos.fY", &calib_pos_fY, &b_calib_pos_fY);
    //     chain->SetBranchAddress("calib.pos.fZ", &calib_pos_fZ, &b_calib_pos_fZ);
    //     chain->SetBranchAddress("ev", &ev_, &b_ds_ev_);
    //     chain->SetBranchAddress("ev.fUniqueID", ev_fUniqueID, &b_ev_fUniqueID);
    //     chain->SetBranchAddress("ev.fBits", ev_fBits, &b_ev_fBits);
    //     chain->SetBranchAddress("ev.id", ev_id, &b_ev_id);
    //     chain->SetBranchAddress("ev.qTotal", ev_qTotal, &b_ev_qTotal);
    //     chain->SetBranchAddress("ev.calibratedTriggerTime", ev_calibratedTriggerTime, &b_ev_calibratedTriggerTime);
    //     chain->SetBranchAddress("ev.deltat", ev_deltat, &b_ev_deltat);
    //     chain->SetBranchAddress("ev.utc.fSec", ev_utc_fSec, &b_ev_utc_fSec);
    //     chain->SetBranchAddress("ev.utc.fNanoSec", ev_utc_fNanoSec, &b_ev_utc_fNanoSec);
    //     chain->SetBranchAddress("ev.pmt", ev_pmt, &b_ev_pmt);
    //     chain->SetBranchAddress("user", &user, &b_ds_user);
    //     
    //     chain->SetCacheSize(200000000);
    //     chain->AddBranchToCache("*",kTRUE);
    //     #if ROOT_VERSION_CODE >= ROOT_VERSION(5,32,00)  
    //     gEnv->SetValue("TFile.AsyncPrefetching", 1);
    //     #endif
  }
  
  // Set the number of events
  //   NbEntries = chain->GetEntries();
  NbEntries = dsReader->GetTotal();
  
  // Save (root + log) files and abort if issue
  if (!SetSaveFile()) { cerr << "Aborting...\n"; abort(); }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//destructor
Analyzer::~Analyzer() {
  
  cout << "Path where outputs have been created:\n"
  << output_dir << "\nOutput data ROOT file: " << save
  << "\nOutput log text file: " << log << endl;
  f_output_txt << "Path where outputs have been created:\n"
  << output_dir << "\nOutput data ROOT file: " << save
  << "\nOutput log text file: " << log << endl;
  
  InputFiles.clear();
  output_dir.Clear();
  save.Clear();
  log.Clear();
  
  delete chain;
  
  delete hCharge;
  delete  hPMTx, hPMTy, hPMTz, hPMTID;
  
  if(job_run1) {
    for(Int_t i=0; i<NbPMT_run1; i++) {
      delete hCharge_perPMT_run1[i];
    }
  }
  if(job_run2) {
    for(Int_t i=0; i<NbPMT_run2; i++) {
      delete hCharge_perPMT_run2[i];
    }
  }
  
  file->Close();
  delete file;
  
  f_output->Close();
  f_output_txt.close();
  
  // Ends the timer
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << duration << " seconds\n";
  f_output_txt << "Execution time: " << duration << " seconds\n";
  
}