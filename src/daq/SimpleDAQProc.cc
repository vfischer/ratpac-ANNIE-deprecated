#include <vector>
#include <RAT/SimpleDAQProc.hh>
#include <RAT/DB.hh>
#include <G4ThreeVector.hh>
#include <RAT/DetectorConstruction.hh>

using namespace std;

namespace RAT {

SimpleDAQProc::SimpleDAQProc() : Processor("simpledaq") {
  //DBLinkPtr ldaq = DB::Get()->GetLink("DAQ");
  //fSPECharge = ldaq->GetDArray("SPE_charge"); // convert pC to gain-normalized units
  fEventCounter = 0;
}

Processor::Result SimpleDAQProc::DSEvent(DS::Root *ds) {
  // This simple simulation assumes only tubes hit by a photon register
  // a hit, and that every MC event corresponds to one triggered event
  // The time of the PMT hit is that of the first photon.

  DS::MC *mc = ds->GetMC();
  if(ds->ExistEV()) {  // there is already a EV branch present 
    ds->PruneEV();     // remove it, otherwise we'll have multiple detector events
                       // in this physics event
                       // we really should warn the user what is taking place		    
  }
  DS::EV *ev = ds->AddNewEV();
  
  ev->SetID(fEventCounter);
  fEventCounter++;

  double totalQ = 0.0;
//   double calibQ = 0.0;
  
  for (int imcpmt=0; imcpmt < mc->GetMCPMTCount(); imcpmt++) {
      DS::MCPMT *mcpmt = mc->GetMCPMT(imcpmt);
      int pmtID = mcpmt->GetID();

      if (mcpmt->GetMCPhotonCount() > 0) {
      //Get PMT construction type
      DBLinkPtr lpmt = DB::Get()->GetLink("PMT",mcpmt->GetModelName());
      std::string constructionType = lpmt->GetS("construction");
      
      // Create one sample, hit time is determined by first hit,
      // "infinite" charge integration time
      // WARNING: gets multiphoton effect right, but not walk correction
      // Write directly to calibrated waveform branch
      
      // Need at least one photon to trigger

	DS::PMT* pmt = ev->AddNewPMT();
	pmt->SetID(pmtID);
	
	double time = mcpmt->GetMCPhoton(0)->GetHitTime();
	double charge = 0;

	for (int i=0; i < mcpmt->GetMCPhotonCount(); i++)  {
	  if (time > mcpmt->GetMCPhoton(i)->GetHitTime())
	    time = mcpmt->GetMCPhoton(i)->GetHitTime();
	  charge += mcpmt->GetMCPhoton(i)->GetCharge();
	}
	
	totalQ += charge;
	
	pmt->SetTime(time);
	pmt->SetCharge(charge);
      }
  }
  
  for (int imclappd=0; imclappd < mc->GetMCLAPPDCount(); imclappd++) {
      DS::MCLAPPD *mclappd = mc->GetMCLAPPD(imclappd);
      int lappdID = mclappd->GetID();

      if (mclappd->GetMCPhotonCount() > 0) {
      //Get PMT construction type
      DBLinkPtr llappd = DB::Get()->GetLink("PMT",mclappd->GetModelName());
      std::string constructionType = llappd->GetS("construction");
      
      // Create one sample, hit time is determined by first hit,
      // "infinite" charge integration time
      // WARNING: gets multiphoton effect right, but not walk correction
      // Write directly to calibrated waveform branch
      
      // Need at least one photon to trigger

	DS::LAPPD* lappd = ev->AddNewLAPPD();
	lappd->SetID(lappdID);
	
	double time = mclappd->GetMCPhoton(0)->GetHitTime();
	double charge = 0;

	for (int i=0; i < mclappd->GetMCPhotonCount(); i++)  {
	  if (time > mclappd->GetMCPhoton(i)->GetHitTime())
	    time = mclappd->GetMCPhoton(i)->GetHitTime();
	  charge += mclappd->GetMCPhoton(i)->GetCharge();
	}
	
	totalQ += charge;
	
	lappd->SetTotalTime(time);
	lappd->SetTotalCharge(charge);
      }
  }

  ev->SetTotalCharge(totalQ);
  //ev->SetCalibQ(calibQ);
  
  return Processor::OK;
}

} // namespace RAT

