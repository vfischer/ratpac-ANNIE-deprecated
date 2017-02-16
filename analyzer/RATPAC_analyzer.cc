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
  
  // track test (test if the track corresponds to this particle)
  TrackTest_neutron = new RAT::TrackTest_Particle("neutron");
  TrackTest_gamma = new RAT::TrackTest_Particle("gamma");
  TrackTest_notelectron = new RAT::TrackTest_NotParticle("e-");
  
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
  hDist_nCap_muTrack = new TH1F("hDist_nCap_muTrack","Distance between neutron capture and muon track (mm)",100,0,5000); 
  hTime_nCap_muTrack = new TH1F("hTime_nCap_muTrack","Time between neutron capture and muon track (ns)",1000,0,1000000);
  hTrackLength_mu = new TH1F("hTrackLength_mu","Muon track lenght (mm)",100,0,5000);
  hEdep_muTrack = new TH1F("hEdep_muTrack","Muon track deposited energy (MeV)",500,0,5000);
  hEdep_muTrack_nCap = new TH1F("hEdep_muTrack_nCap","Neutron capture (after muon track) deposited energy (MeV)",2000,0,20);
  hNCaptures_perevt = new TH1F("hNCaptures_perevt","Nb of neutron capture (after muon track) per muon track",20,0,20);
  hNpCaptures_perevt = new TH1F("hNpCaptures_perevt","Nb of primary neutron capture (after muon track) per muon track",20,0,20);
  hNCaptures_perEnu = new TH1F("hNCaptures_perEnu","Nb of neutron capture (after muon track) per muon track wrt Enu",500,0,5000);
  hNpCaptures_perEnu = new TH1F("hNpCaptures_perEnu","Nb of primary neutron capture (after muon track) per muon track wrt Enu",500,0,5000);
  
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
  broken_pmt_vec.clear(); ncv_pmt_vec.clear(), interest_volumes.clear();
  Npneutrons = 0, Nmuons = 0, Nneutrons_cap_cut = 0, Npneutrons_cap_cut = 0, Nmuons_cut = 0;
  Npcaptures = 0, Npcaptures_h = 0, Npcaptures_gd = 0, Npcaptures_c = 0,Npcaptures_si = 0,Npcaptures_fe = 0, Npinelastic = 0, Npdecay = 0, NbNoCaptures = 0;
  Nneutrons_track_tot = 0, Nmuons_tot = 0, Nmuons_track = 0; test_counter = 0;
  Ninteractions_tot = 0;
  Ek_nu = 0;
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
  
  interest_volumes.push_back("detector");
  interest_volumes.push_back("detector_fiducial");
  interest_volumes.push_back("ncv_detector");
  
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
    charge_tot = 0, Ncaptures_perevt = 0, Npcaptures_perevt = 0, parenttrackID = 0, Edep_capture = 0;;
    is_nGd = false, is_nH = false, is_mu_tag = false;
    vMuTrack.clear(), vMuTrack_Edep.clear(), pparticles_trackID.clear();
    
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
    
    hTrackLength->Fill(disp);
    
    //     cout << ds->GetMC()->GetMCSummary()->GetEnergyLossByVolume("detector") << endl;
    
//     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParentCount(); iCh++){ // loop on parents to get neutrino energy
//       if (Abs(ds->GetMC()->GetMCParent(iCh)->GetPDGCode()) == 12 || // if parent is a (anti-) neutrino
// 	  Abs(ds->GetMC()->GetMCParent(iCh)->GetPDGCode()) == 14 ||
// 	  Abs(ds->GetMC()->GetMCParent(iCh)->GetPDGCode()) == 16 ) {
// 	Ek_nu = ds->GetMC()->GetMCParent(iCh)->GetKE();
//         break;
//       }
//     }
    
    nav = new RAT::TrackNav(ds);
    cursor = new RAT::TrackCursor(nav->RAT::TrackNav::Cursor(false));  //toggle human readable cursor
    
    //     cout << "Parents = " << ds->GetMC()->GetMCParentCount() << endl;
    //     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParentCount(); iCh++){ cout << ds->GetMC()->GetMCParent(iCh)->GetParticleName() << endl;}
    //     cout << "Particles = " << ds->GetMC()->GetMCParticleCount() << endl;
    //     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParticleCount(); iCh++){ cout << ds->GetMC()->GetMCParticle(iCh)->GetParticleName() << endl;}
    //     cout << "Tracks = " << ds->GetMC()->GetMCTrackCount() << endl;
    //     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCTrackCount(); iCh++){ cout << ds->GetMC()->GetMCTrack(iCh)->GetPDGCode() << endl;}
    
    /*
     *   // Find track length and duration of ALL parent (initial) particles
     *   if(cursor->ChildCount()){
     *         cursor->GoChild(0);
     *         node = cursor->Here();
     *         init_pos  = node->GetEndpoint();
     *         init_time = node->GetGlobalTime();
     *         
     *    //       cout << "INITIAL: position = " << init_pos.x() << " " <<  init_pos.y() << " " << init_pos.z() << ", time = " << init_time << ", energy = " << node->GetKE() << endl;
     *    //       cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
     *    //       cout << node->GetTrackID() << " " << node->GetStepID() << endl;
     *    
     *    for(size_t iCh = 1; iCh<cursor->StepCount()-1; iCh++){
     *      node->Clear();
     *      node = cursor->GoStep(iCh);
     *      fin_pos   = node->GetEndpoint();	
     *      fin_time = node->GetGlobalTime();
     *      
     *      // 	cout << "INTERMED: position = " << fin_pos.x() << " " <<  fin_pos.y() << " " << fin_pos.z() << ", time = " << fin_time << ", energy = " << node->GetKE() << endl;
     *      // 	cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
     *      // 	cout << node->GetTrackID() << " " << node->GetStepID() << endl << endl;
  }
  
  node->Clear();
  node = cursor->TrackEnd();
  fin_pos   = node->GetEndpoint();	
  fin_time = node->GetGlobalTime();
  
  //       cout << "FINAL: position = " << fin_pos.x() << " " <<  fin_pos.y() << " " << fin_pos.z() << ", time = " << fin_time << ", energy = " << node->GetKE() << endl;
  //       cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetParticleName() << endl;
  //       cout << node->GetTrackID() << " " << node->GetStepID() << endl;
  //      
  
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
      //       cout << " ===>  n-H !!\n\n";
  } 
  if (TPMERegexp("100064[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
    //  cout << " ===>  n-Gd !!\n\n";
  }    
  cursor->GoParent();
  } else {
    //   cout << " ===========================================  THAT WAS NOT A CAPTURE !!!! ===========================================\n";
    NbNoCaptures++;
  }
  
  
  disp = (fin_pos - init_pos).Mag();
  deltat = fin_time - init_time;
  // 	cout << disp << " " << deltat << endl;
  hTrackDuration->Fill(deltat);
  cursor->GoParent();
  }
  */ 
    //     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCTrackCount(); iCh++){
    //       cursor->FindNextTrack();
    //       node = cursor->Here();
    //       cout << "Global: " << node->GetGlobalTime() << endl;
    //       cout << "Local: " << node->GetLocalTime() << endl;
    //       cout << "Proper: " << node->GetProperTime() << endl;
    //       hTrackDuration->Fill(node->GetGlobalTime());
    //     }
    
    
    ////////////////////////////////////////////////////////
    //************ Primary muon search loop **************//
    ////////////////////////////////////////////////////////
//     cout << "New event --->\n";
    if(cursor->ChildCount()){ // if particles associated to parents
      for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParticleCount(); iCh++){ // Loop on all particles in that event
	cursor->GoChild(iCh); // go to particle
	node = cursor->Here(); // "attach" node to this particle
	if( std::find(interest_volumes.begin(), interest_volumes.end(), node->GetVolume()) != interest_volumes.end() ) { // only interaction in volumes of interest
	  if(iCh == 0) { Ninteractions_tot++;} // only fill this once per event
	  if (node->GetParticleName() == "mu-" || node->GetParticleName() == "mu+") { // if muon
	    Nmuons_tot++;
	    for(size_t jCh = 0; jCh<cursor->StepCount(); jCh++){ //loop on each step
	      node = cursor->GoStep(jCh); // go to step
	      if ( std::find(interest_volumes.begin(), interest_volumes.end(), node->GetVolume()) != interest_volumes.end() ) { // is node is in the volume you want
		vMuTrack.push_back(node->GetEndpoint()); // fills the vectors of node position (front() and back() are first and last node in volumes (track) )
		vMuTrack_Edep.push_back(node->GetKE()); // record current KE of muon at each step of the track
	      }
	    }
	    if (vMuTrack.size() != 0){
	      Nmuons_track++;
	      muTrack_start = vMuTrack.front();
	      muTrack_end = vMuTrack.back();
	      hTrackLength_mu->Fill((muTrack_end - muTrack_start).Mag());
	      hEdep_muTrack->Fill(vMuTrack_Edep.front() - vMuTrack_Edep.back()); // deposited Edep of track if KEfinal-KEinitial
	      // 	cout << "Muon track length: " << (muTrack_end - muTrack_start).Mag() << endl;
	      if ((muTrack_end - muTrack_start).Mag() > 500){ //muon track length cut
		Nmuons_cut++; is_mu_tag = true;
	      }
	    } else {
	      // 	  cout << "No muon track in this volume\n";
	    }
	  }
	  
	}
	if (node->GetParticleName() == "neutron") {
	  pparticles_trackID.push_back(node->GetTrackID());	
	}
	cursor->GoParent(); // "detach" node
      }
    }
    
    
    /////////////////////////////////////////////////////////
    //********** Secondary neutron search loop ************//
    /////////////////////////////////////////////////////////
    //     for(size_t iCh = 0; iCh<ds->GetMC()->GetMCTrackCount(); ++iCh){ // Loop on all tracks in that event
    while(node != 0){
      node = cursor->FindNextTrack(); // go to the track
      if(node == NULL){break;} // break the loop if no more non-electron tracks
      
      //       cout << ds->GetMC()->GetMCTrack(iCh)->GetParticleName() << " " << ds->GetMC()->GetMCTrack(iCh)->GetLastMCTrackStep()->GetProcess()  << endl;
      //       if (ds->GetMC()->GetMCTrack(iCh)->GetPDGCode() == 2112){ //look for neutrons, all neutrons
      // 	Nneutrons_tot++;
      // 	if (ds->GetMC()->GetMCTrack(iCh)->GetLastMCTrackStep()->GetProcess() == "nCapture" /*&& 
      // 	  std::find(interest_volumes.begin(), interest_volumes.end(), ds->GetMC()->GetMCTrack(iCh)->GetLastMCTrackStep()->GetVolume()) != interest_volumes.end() &&
      // 	  is_mu_tag*/) {
      // 	  cout << ds->GetMC()->GetMCTrack(iCh+1)->GetPDGCode() << " " << ds->GetMC()->GetMCTrack(iCh+1)->GetLastMCTrackStep()->GetProcess() << endl;
      // 	  Nneutrons_cut++;
      // 	  NCaptures_perevt++; // nb of ncaptures after muon
      // 	  nCapture_pos = ds->GetMC()->GetMCTrack(iCh)->GetLastMCTrackStep()->GetEndpoint();
      // 	// 	    cout << "Neutron capture at " << nCapture_pos.x() << " " <<  nCapture_pos.y() << " " << nCapture_pos.z() << endl;
      // 	  distance_nCap_muTrack = ((nCapture_pos - muTrack_start).Cross(nCapture_pos - muTrack_end)).Mag()/(muTrack_end - muTrack_start).Mag();
      // 	// 	    cout << "Distance nCapture to MuonTrack = " << distance_nCap_muTrack << endl;
      // 	  hDist_nCap_muTrack->Fill(distance_nCap_muTrack);
      // 	  }
      // 	  if (ds->GetMC()->GetMCTrack(iCh)->GetLastMCTrackStep()->GetProcess() == "neutronInelastic") {
      // // 	    N_inelastic++;
      // 	  }
      //       }
      if (node->GetParticleName() == "neutron"){ // loop on all neutron tracks
	Nneutrons_track_tot++;
      }
      
//           cout << node->GetParticleName() << " " << node->GetPDGCode() << " " << node->GetVolume() << " " << node->GetProcess() << " " << node->GetKE() << " " << is_mu_tag << endl; 
      if (node->GetProcess() == "nCapture" && // capture	    
	std::find(interest_volumes.begin(), interest_volumes.end(), node->GetVolume()) != interest_volumes.end() && // in the good volumes
	is_mu_tag) { // look for neutron captures and their secondaries
	  
	  if (parenttrackID != cursor->Parent()->GetTrackID() ) {
	    if (/*Edep_capture != 0. && */is_nGd) { // if next neutron as parent, fill info related to this neutron
	      parenttrackID = cursor->Parent()->GetTrackID();
	      hEdep_muTrack_nCap->Fill(Edep_capture);
// 	      cout << "fill edep a: " << Edep_capture << endl;
	      Edep_capture = 0; is_nGd = false;
	    } else {
	      Edep_capture = 0; is_nGd = false;
	    }
	  }
	  
	  if (TPMERegexp("1000[0-9][0-9][0-9][0-9][0-9][0-9]").Match(Form("%d",node->GetPDGCode()))) { // capture on an atom (no gammas from nCapture))
	    is_nGd = false; is_nH = false;
//  	    cout << "atom: " << node->GetPDGCode() << " " << node->GetTrackID() << endl;
// 	    cout << "atom parent: " << cursor->Parent()->GetPDGCode() << " " << cursor->Parent()->GetTrackID() << endl;
	     if (TPMERegexp("100064[0-9][0-9][0-9][0-9]").Match(Form("%d",node->GetPDGCode()))) { // PDGCode (Int) casted as a TString, look for Gd
	      is_nGd = true;
	      if(std::find(pparticles_trackID.begin(), pparticles_trackID.end(), cursor->Parent()->GetTrackID()) != pparticles_trackID.end()) { // if the parent neutron is a primary particle
		Npneutrons_cap_cut++;
		Npcaptures_perevt++; // nb of primary ncaptures after muon 
	      }
	      nCapture_pos = node->GetEndpoint();
	      distance_nCap_muTrack = ((nCapture_pos-muTrack_start).Cross(nCapture_pos-muTrack_end)).Mag()/(muTrack_end - muTrack_start).Mag();
	      hDist_nCap_muTrack->Fill(distance_nCap_muTrack);
	      hTime_nCap_muTrack->Fill(node->GetGlobalTime());
	      Nneutrons_cap_cut++;
	      Ncaptures_perevt++; // nb of ncaptures after muon  
	    } else if (TPMERegexp("100001[0-9][0-9][0-9][0-9]").Match(Form("%d",node->GetPDGCode()))) { //  look for H
	      is_nH = true;
	      // for now do nothing if n-H
	    } else {
	      // nothing either
	    }
	  } else if (node->GetParticleName() == "gamma"){
//  	    cout << "gamma: " << node->GetPDGCode() << " " << node->GetTrackID() << " " << node->GetKE() << endl;
// 	    cout << "gamma parent: " << cursor->Parent()->GetPDGCode() << " " << cursor->Parent()->GetTrackID() << endl;
	    for( Int_t iStep = 1; iStep < cursor->StepCount(); iStep++ ){
	      if(std::find(interest_volumes.begin(), interest_volumes.end(), cursor->Step(iStep)->GetVolume()) != interest_volumes.end()){
		Edep_capture += cursor->Step(iStep-1)->GetKE() - cursor->Step(iStep)->GetKE();
		// 		cout << "stepE: " << cursor->Step(iStep-1)->GetKE() - cursor->Step(iStep)->GetKE() << endl;
	      }
	    }
	    
	  }
	  parenttrackID = cursor->Parent()->GetTrackID();
	}	
    }
    if (/*Edep_capture != 0. &&*/ is_nGd) { // fills the last Edep_capture information or the only one if only 1 gamma
      hEdep_muTrack_nCap->Fill(Edep_capture);
//       cout << "fill edep b: " << Edep_capture << endl;
      Edep_capture = 0; is_nGd = false;
    }
    if (is_mu_tag) { // fills this only in case of a muon track
      hNCaptures_perevt->Fill(Ncaptures_perevt);
      hNpCaptures_perevt->Fill(Npcaptures_perevt);
    }
    
    
    ///////////////////////////////////////////////////////
    //********** Primary neutron search loop ************//
    ///////////////////////////////////////////////////////
    cursor->GoParent(); cursor->GoParent(); // because apparently I moved down two levels on the track tree before..
    node = cursor->Here();
    // Find track length and duration of primary (in MCParticle) neutrons 
    if(cursor->ChildCount()){ // if particles associated to parents
      for(size_t iCh = 0; iCh<ds->GetMC()->GetMCParticleCount(); iCh++){ // Loop on all particles in that event
	cursor->GoChild(iCh); // go to particle
	node = cursor->Here(); // "attach" node to this particle
	if(node->GetPDGCode() == 2112){ // only for neutrons, beginning of tracking loop
	  node = cursor->GoStep(cursor->StepCount()-1); // go to last step (the only one we care about here)
	  if(node->GetProcess() == "nCapture"){
	    cursor->GoTrackEnd(); // Last interaction of primary part
	    // 	     	  cout << node->GetPDGCode() << " " << node->GetProcess() << " " << node->GetStepID() << endl;
	    cursor->GoChild(cursor->ChildCount()-1);
	    cursor->GoTrackStart();
	    node = cursor->Here();
	    //  	    cout << node->GetVolume() << endl;
	    // 	    cout << "Primary -- " << node->GetPDGCode() << endl;
	    nucl_cap_pdg_code = to_string(node->GetPDGCode());
	    if (TPMERegexp("100001[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      Npcaptures_h++;
	      hTrackDuration_nH->Fill(node->GetGlobalTime());
	      hTrackLength_nH->Fill(ds->GetMC()->GetMCSummary()->GetEnergyCentroid().Mag());
	    } 
	    if (TPMERegexp("100064[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      Npcaptures_gd++;
	      hTrackDuration_nGd->Fill(node->GetGlobalTime()); 
	      hTrackLength_nGd->Fill(ds->GetMC()->GetMCSummary()->GetEnergyCentroid().Mag());
	    }   
	    if (TPMERegexp("100006[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      Npcaptures_c++;
	    }
	    if (TPMERegexp("100014[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      Npcaptures_si++;
	    }
	    if (TPMERegexp("100026[0-9][0-9][0-9][0-9]").Match(nucl_cap_pdg_code)) {
	      Npcaptures_fe++;
	    }
	    cursor->GoParent();
	    Npcaptures++;
	  } else if (node->GetProcess() == "neutronInelastic") { // look for inelastic that would cause the tracking to lose the neutron (dumm GEANT4..)
	    Npinelastic++;
	  } else if (node->GetProcess() == "Decay") { // look for neutron decays (wander around for too long)
	    Npdecay++;
	  }
	    else { // you don't need to fill this, this will display a few "Decay" as last process
	    	      cout << node->GetProcess() << endl;
	  }
	  
	  // 	  for(size_t jCh = 0; jCh<cursor->ChildCount()-1; jCh++){ //Secondary Particle Tracks
	  // 	      cursor->GoChild(jCh);
	  // 	      node = cursor->Here();
	  // // 	      cout << "Secondary -- " << node->GetPDGCode() << " " << node->GetVolume() << " " <<  << endl;	      
	  // 	      cursor->GoParent();
	  // 	    }
	  
	  // 	  cursor->GoTrackStart();
	  // 	  cursor->GoParent();
	  Npneutrons++; 
	  //       cout << ds->GetMC()->GetMCSummary()->GetEnergyLossByVolume("ncv_liquid") << endl;
	  //       cout << ds->GetMC()->GetMCTrack(0)->GetMCTrackStep(0)->GetVolume() << endl;
	  
	  
	} // end of tracking loop
	cursor->GoParent();
      }
    }
    
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
  
  cout << test_counter << endl;
  cout << "\n";
  cout << "=========== Muon Analysis ==========\n";
  cout << "Interactions in the volumes of interest: " << Ninteractions_tot << endl;
  cout << "Muons created in the volumes of interest: " << Nmuons_tot << endl;
  cout << "Muons tracks in detector after cut: " << Nmuons_cut << endl;
  cout << "Neutron tracks total: " << Nneutrons_track_tot << endl;
  cout << "Neutrons captures after muons after cuts: " << Nneutrons_cap_cut << " --> including " << Npneutrons_cap_cut << " primary neutrons" << endl;
  cout << "====================================\n\n";
  cout << "=========== Neutron (primary) Analysis ==========\n";
  cout << "Out of " << Npneutrons << " total neutrons: \n";
  cout << "Out of " << Npcaptures << " neutron captures: \n";
  cout << "\t -> " << Npcaptures_gd << " occurred on Gd.\n";
  cout << "\t -> " << Npcaptures_h << " occurred on H.\n";
  cout << "\t -> " << Npcaptures_c << ", " << Npcaptures_si << ", " << Npcaptures_fe << " occurred on C, Si, Fe.\n";
  cout << "\t -> " << Npinelastic << " did undergo neutronInelastic.\n";
  cout << "\t -> " << Npdecay << " did decay.\n";
  cout << "====================================\n\n";
  
  f_output_txt << "\n";
  f_output_txt << "=========== Muon Analysis ==========\n";
  f_output_txt << "Interactions in the volumes of interest: " << Ninteractions_tot << endl;
  f_output_txt << "Muons created in the volumes of interest: " << Nmuons_tot << endl;
  f_output_txt << "Muons tracks in detector after cut: " << Nmuons_cut << endl;
  f_output_txt << "Neutron tracks total: " << Nneutrons_track_tot << endl;
  f_output_txt << "Neutrons captures after muons after cuts: " << Nneutrons_cap_cut << " --> including " << Npneutrons_cap_cut << " primary neutrons" << endl;
  f_output_txt << "====================================\n\n";
  f_output_txt << "=========== Neutron (primary) Analysis ==========\n";
  f_output_txt << "Out of " << Npneutrons << " total neutrons: \n";
  f_output_txt << "Out of " << Npcaptures << " neutron captures: \n";
  f_output_txt << "\t -> " << Npcaptures_gd << " occurred on Gd.\n";
  f_output_txt << "\t -> " << Npcaptures_h << " occurred on H.\n";
  f_output_txt << "\t -> " << Npcaptures_c << ", " << Npcaptures_si << ", " << Npcaptures_fe << " occurred on C, Si, Fe.\n";
  f_output_txt << "\t -> " << Npinelastic << " did undergo neutronInelastic.\n";
  f_output_txt << "\t -> " << Npdecay << " did decay.\n";
  f_output_txt << "====================================\n\n";
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
  dsReader = new RAT::DSReader(InFiles.front()); // cuz stupid dsReader needs to be initialize with a filename..
  
  for (vector<TString>::iterator it = InFiles.begin(); it != InFiles.end(); ++it) {
    file = new TFile((*it),"READ");
    if(file->GetName() != InFiles.front()){ // adds the next file to the dsReader only if its not the first file (already added)
      dsReader->Add(*it);
    }
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
  delete dsReader;
  
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