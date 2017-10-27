#include <RAT/GeoLAPPDFactoryBase.hh>
#include <RAT/DB.hh>
#include <RAT/Log.hh>

#include <G4SDManager.hh>
#include <G4PVPlacement.hh>
#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include <RAT/Materials.hh>
#include <RAT/GLG4PMTSD.hh>
#include <G4LogicalBorderSurface.hh>
#include <RAT/DetectorConstruction.hh>
#include <RAT/LAPPDConstruction.hh>
#include <RAT/WaveguideFactory.hh>
#include <RAT/Factory.hh>
#include <vector>
#include <algorithm>

#include "G4FastSimulationManager.hh"
#include "G4VFastSimulationModel.hh"
#include "RAT/GLG4PMTOpticalModel.hh"
#include "G4PhysicsOrderedFreeVector.hh"

#include "G4RandomDirection.hh"

#include "iostream"

using namespace std;

namespace RAT {

DS::PMTInfo GeoLAPPDFactoryBase::lappdinfo;

G4VPhysicalVolume *GeoLAPPDFactoryBase::ConstructLAPPDs(DBLinkPtr table, 
                       std::vector<double> lappd_x, std::vector<double> lappd_y, std::vector<double> lappd_z)
{
  // ------------------ Extra LAPPD settings --------------------
  string volume_name = table->GetIndex();
  string sensitive_detector_name = table->GetS("sensitive_detector");
  
  int start_idx, end_idx;
  try {
    start_idx = table->GetI("start_idx"); //position in this array to start building lappds
  } catch (DBNotFoundError &e) {
    start_idx = 0; // defaults to beginning
  }
  try {
    end_idx = table->GetI("end_idx"); //id of the last lappd to build in this array
  } catch (DBNotFoundError &e) {
    end_idx = lappd_x.size()-1; // defaults to whole array
  }

  string pos_table_name = table->GetS("pos_table");
  DBLinkPtr lpos_table = DB::Get()->GetLink(pos_table_name);
  
  vector<int> lappd_type;
  try {
    lappd_type = lpos_table->GetIArray("type"); // functional type (e.g. inner, veto, etc. - arbitrary integers)
  } catch (DBNotFoundError &e) {
    lappd_type.resize(lappd_x.size());
    fill(lappd_type.begin(),lappd_type.end(),-1); //defaults to type -1 if unspecified
  }

  // read lappd_detector_type
  string lappd_detector_type = table->GetS("lappd_detector_type");

  // flip lappds to face outwards e.g. for use in a veto
  int flip = 0;
  try {  flip = table->GetI("flip"); }
  catch (DBNotFoundError &e) { }
  
  // Find mother
  string mother_name = table->GetS("mother");
  G4LogicalVolume *mother = FindMother(mother_name);
  if (mother == 0)
    Log::Die("Unable to find mother volume " + mother_name + " for "
		+ volume_name);
 
  string lappd_model = table->GetS("lappd_model"); // the form factor of the LAPPD (physical properties)
  DBLinkPtr llappd = DB::Get()->GetLink("PMT", lappd_model);

  LAPPDConstructionParams lappdParam;

  lappdParam.glassThickness = llappd->GetD("glassThickness");
  lappdParam.width = llappd->GetD("width");
  lappdParam.photocathodeWidth = llappd->GetD("photocathodeWidth");
  lappdParam.thick = llappd->GetD("thick");

  // Materials
  lappdParam.glass = G4Material::GetMaterial(llappd->GetS("glass_material"));
  lappdParam.vacuum = G4Material::GetMaterial(llappd->GetS("lappd_vacuum_material")); 
  string pc_surface_name = llappd->GetS("photocathode_surface");
  lappdParam.photocathode = Materials::optical_surface[pc_surface_name];
  
  if (lappdParam.photocathode == 0)
    Log::Die("GeoLAPPDFactoryBase error: Photocathode surface \""
		+ pc_surface_name + "\" not found");

  // Simplified LAPPD drawing for faster visualization
  bool vis_simple = false;
  try {
    vis_simple = table->GetI("vis_simple") != 0;
  } catch (DBNotFoundError &e) { }

  // Orientation of LAPPDs
  bool orient_manual = false;
  try { 
    string orient_str = table->GetS("orientation");
    if (orient_str == "manual")
      orient_manual = true;
    else if (orient_str == "point")
      orient_manual = false;
    else 
      Log::Die("GeoLAPPDFactoryBase error: Unknown LAPPD orientation " 
		  + orient_str);
  } catch (DBNotFoundError &e) { }

  vector<double> dir_x, dir_y, dir_z;
  vector<double> orient_point_array;
  G4ThreeVector orient_point;
  bool rescale_radius = false;
  double new_radius = 1.0;
  if (orient_manual) {
    dir_x = lpos_table->GetDArray("dir_x");
    dir_y = lpos_table->GetDArray("dir_y");
    dir_z = lpos_table->GetDArray("dir_z");
  } else {
    //fill with dummy values needed for lappdinfo.AddLAPPD. They will be redirected towards
    //the proper point afterwards
    dir_x.push_back(9999.);
    dir_y.push_back(9999.);
    dir_z.push_back(9999.);
    orient_point_array = table->GetDArray("orient_point");
    if (orient_point_array.size() != 3)
      Log::Die("GeoLAPPDFactoryBase error: orient_point must have 3 values");
    orient_point.set(orient_point_array[0], orient_point_array[1],
		     orient_point_array[2]);    
  }

  // Optionally can rescale LAPPD radius from mother volume center for
  // case where LAPPDs have spherical layout symmetry
  try {
    new_radius = table->GetD("rescale_radius");
    rescale_radius = true;
  } catch (DBNotFoundError &e) { }
  

  // get pointer to physical mother volume
  G4VPhysicalVolume* phys_mother = FindPhysMother(mother_name);
  if (phys_mother == 0)
    Log::Die("GeoLAPPDFactoryBase error: LAPPD mother physical volume " + mother_name
		+" not found");


  // --------------- Start building LAPPD geometry ------------------

//   // LAPPD sensitive detector
  G4SDManager* fSDman = G4SDManager::GetSDMpointer();  
  GLG4PMTSD* lappdSDInner= new GLG4PMTSD(sensitive_detector_name, end_idx-start_idx+1, lappdinfo.GetPMTCount(), -1 /* evidently unused? */);
  fSDman->AddNewDetector(lappdSDInner);
  lappdParam.detector = lappdSDInner;
  

  // Set new efficiency correction if requested
  try {
    float efficiency_correction = table->GetD("efficiency_correction");
    lappdParam.efficiencyCorrection = efficiency_correction;
  } catch (DBNotFoundError &e) { }
  
  // Build LAPPD
  LAPPDConstruction lappdConstruct(lappdParam);
    
  G4LogicalVolume *logiLAPPD = lappdConstruct.NewLAPPD(volume_name, vis_simple);
     
//preparing to calculate magnetic efficiency corrections for all LAPPDs, if requested
  int BFieldOn=0;
  try{BFieldOn=DB::Get()->GetLink("BField")->GetI("b_field_on");}
  catch (DBNotFoundError &e){}
  string BFieldTableName="";
  string BEffiTableName="";
  string dynorfilename="";
  string BEffiModel="multiplicative";
  vector<pair<int,double> > BEfficiencyCorrection;
  DBLinkPtr BEffiTable;
//  G4PhysicsOrderedFreeVector Bepsix,Bepsiy;
  vector<G4PhysicsOrderedFreeVector> Bepsix,Bepsiy;
  vector<G4ThreeVector> Bpos,Bf;
  vector<G4ThreeVector> Dpos,Dorie;//dynode position&orient

//Force B efficiency<= 1 by default, whatever the input from BEffiTable.
//If we start believing that B may actually help the LAPPD response, change default to false
  bool CorrBEpsiInput=true;
  int nocorr=0;
  try{nocorr=DB::Get()->GetLink("BField")->GetI("no_b_efficiency_table_correction");}
  catch (DBNotFoundError &e){}
  if(nocorr) CorrBEpsiInput=false;
  else cout<<"Forcing B efficiency<= 1\n";
  bool HaveDynoData=false;

  if(BFieldOn){
    try{BFieldTableName=DB::Get()->GetLink("BField")->GetS("b_field_file");}
    catch (DBNotFoundError &e){}
    try{BEffiTableName=DB::Get()->GetLink("BField")->GetS("b_efficiency_table");}
    catch (DBNotFoundError &e){}
    try{dynorfilename=DB::Get()->GetLink("dynorfile")->GetS("dynorfilename");}
    catch(DBNotFoundError &e){}
    //check if we can calculate B field effect
    if(BFieldTableName=="" || BEffiTableName==""){
      G4cout<<"B field is on, but either B data or B LAPPD efficiency correction missing.\n"
        <<"Turning B field off.\n";
      BFieldOn=0;
      BEffiTable=NULL;
    }
    else{
      string ExpSubdir=DB::Get()->GetLink("DETECTOR")->GetS("experiment");
      string BFieldTableName1=string(getenv("GLG4DATA"))+"/"+ExpSubdir+"/"+BFieldTableName;//add the experiment subdir
      ifstream Bdata(BFieldTableName1.data());
      if(!Bdata.is_open()){
        BFieldTableName=string(getenv("GLG4DATA"))+"/"+BFieldTableName;
        cout<<"file "<<BFieldTableName1<<" not found, trying "<<BFieldTableName<<"\n";
        Bdata.close();
        Bdata.open(BFieldTableName.data());
        if(!Bdata.is_open()){
          BFieldOn=false;
          BEffiTable=NULL;
          cout<<"also file "<<BFieldTableName<<" not found, magnetic efficiency correction turned off\n";
        }
        if(!Bdata.good())
          Bdata.clear();//for backwards compatibility: g++ 3.4 requires to manually reset the error state flags on opening a new file with the same stream
      }
      string header;
      getline(Bdata,header);
      double xr,yr,zr,bxr,byr,bzr;
      cout<<"about to load B field from file "<<BFieldTableName<<"\n";
      G4ThreeVector posi,field;
      while(!Bdata.rdstate()){
        Bdata>>xr>>yr>>zr>>bxr>>byr>>bzr;
        posi.set(xr,yr,zr);
        field.set(bxr,byr,bzr);
        Bpos.push_back(posi);
        Bf.push_back(field);
      }
      BEffiTable=DB::Get()->GetLink(BEffiTableName);
      vector<double> blappd;
      vector<double> epsix,epsiy;
      blappd=BEffiTable->GetDArray("b");
      epsix=BEffiTable->GetDArray("deltax");
      epsiy=BEffiTable->GetDArray("deltay");
      G4PhysicsOrderedFreeVector* QBepsix;G4PhysicsOrderedFreeVector* QBepsiy;
      QBepsix=new G4PhysicsOrderedFreeVector();QBepsiy=new G4PhysicsOrderedFreeVector();
      for(int i=0;i<int(blappd.size());i++){
          QBepsix->InsertValues(blappd[i],epsix[i]);
          QBepsiy->InsertValues(blappd[i],epsiy[i]);
      }
      Bepsix.push_back(*QBepsix);
      Bepsiy.push_back(*QBepsiy);
      //no. of datasheets transcribed in the db table of the same LAPPD model
      int nsheets=0;
      try{nsheets=BEffiTable->GetI("nsheets");}
      catch (DBNotFoundError &e){}
      if(nsheets>1){
        char c[12];
        string name;
        for(int is=1;is<nsheets;is++){
          sprintf(c,"%i",is);
          name=string("deltax")+c;
          epsix=BEffiTable->GetDArray(name);
          name=string("deltay")+c;
          epsiy=BEffiTable->GetDArray(name);
          delete QBepsix;
          delete QBepsiy;
          QBepsix=new G4PhysicsOrderedFreeVector();
          QBepsiy=new G4PhysicsOrderedFreeVector();
          for(int i=0;i<int(blappd.size());i++){
            QBepsix->InsertValues(blappd[i],epsix[i]);
            QBepsiy->InsertValues(blappd[i],epsiy[i]);
          }
          Bepsix.push_back(*QBepsix);
          Bepsiy.push_back(*QBepsiy);
        }
      }

  //try to load LAPPD orientation table from file
      dynorfilename=string(getenv("GLG4DATA"))+"/"+ExpSubdir+"/"+dynorfilename;
      ifstream dynorfile(dynorfilename.data());
      if(!dynorfile.is_open()){
        cout<<"Failed to open "<<dynorfilename.data()<<", will assume random dynode orientations\n";
        dynorfile.close();
      }
      else{
        getline(dynorfile,header);
        double xd,yd,zd,dynox,dynoy,dynoz;
        G4ThreeVector dor;
        while(!dynorfile.rdstate()){
          dynorfile>>xd>>yd>>zd>>dynox>>dynoy>>dynoz;
          posi.set(xd,yd,zd);
          dor.set(dynox,dynoy,dynoz);
          Dpos.push_back(posi);
          Dorie.push_back(dor);
        }
      }
      Bdata.close();
      dynorfile.close();
      if(!Dorie.empty() && Dorie.size()==Dpos.size())
        HaveDynoData=true;
      else
        cout<<"No dynode orientation datafile or error in the data, randomizing dynode orientations\n";
    }
    try{BEffiModel=DB::Get()->GetLink("BField")->GetS("b_efficiency_model");}
    catch(DBNotFoundError &e){}
    cout<<"\nSelected "<<BEffiModel.data()<<" B Efficiency Model\n";
  }
  else
    BEffiTable=NULL;
  
  //LAPPDINFO is always in global coordinates - so calculate the local offset first
  G4ThreeVector offset = G4ThreeVector(0.0,0.0,0.0);
  for (string parent_name = mother_name; parent_name != ""; ) {
     G4VPhysicalVolume *parent_phys = FindPhysMother(parent_name);
     offset += parent_phys->GetFrameTranslation();
     cout << "LAPPDINFO: Offset of physical volume " << parent_phys->GetName() << " is " << offset << endl;
     DBLinkPtr parent_table = DB::Get()->GetLink("GEO",parent_name);
     parent_name = parent_table->GetS("mother");
  }
  
  // Place physical LAPPDs
  // idx - the element of the particular set of arrays we are reading
  // id - the nth lappd that GeoLAPPDFactoryBase has built
  for (int idx = start_idx, id = lappdinfo.GetPMTCount(); idx <= end_idx; idx++, id++) {

    string lappdname = volume_name + ::to_string(id); //internally LAPPDs are represented by the nth lappd built, not lappdid
    
    // position
    G4ThreeVector lappdpos(lappd_x[idx], lappd_y[idx], lappd_z[idx]);
    lappdpos += offset;
    if (rescale_radius)
      lappdpos.setMag(new_radius);

    // direction
    G4ThreeVector lappddir;
    if (orient_manual)
      lappddir.set(dir_x[idx], dir_y[idx], dir_z[idx]);
    else
      lappddir = orient_point - lappdpos;
    lappddir = lappddir.unit();
    if (flip == 1) lappddir = -lappddir; 

    // Write the real (perhaps calculated) LAPPD positions and directions.
    // This goes into the DS by way of Gsim
    lappdinfo.AddPMT(
        TVector3(lappdpos.x(), lappdpos.y(), lappdpos.z()),
        TVector3(lappddir.x(), lappddir.y(), lappddir.z()),
        lappd_type[idx],
        lappd_model);

    // if requested, generates the magnetic efficiency corrections as the LAPPDs are created
    if(BFieldOn){
      //finds the point of the B grid closest to the current LAPPD, and attributes it that Bfield
      double MinDist=DBL_MAX;
      int imin=-1;
      for(int i=0;i<int(Bpos.size());i++){
        if(MinDist>(lappdpos-Bpos[i]).mag()){
          MinDist=(lappdpos-Bpos[i]).mag();
          imin=i;
        }
      }
      if(imin<0)
        cout<<"can't find a point close to the "<<id<<"-th lappd; MinDist is "<<MinDist<<"\n";
      else{
        G4ThreeVector bfield=Bf[imin].perpPart(lappddir);
        G4ThreeVector dynorient;
        if(HaveDynoData){
          int mini=-1;
          double MinDiff=DBL_MAX;
          for(int i=0;i<int(Dorie.size());i++)
            if((lappdpos.unit()-Dpos[i].unit()).mag()<MinDiff){
              MinDiff=(lappdpos.unit()-Dpos[i].unit()).mag();
              mini=i;
            }
          if(mini<0){
            cout<<"can't find the orientation of the "<<id<<"-th lappd's dynode; MinDiff is "<<MinDiff<<"\n"
              <<"Throwing a random dynode orientation\n";
            dynorient=G4RandomDirection();
            dynorient=dynorient.perpPart(lappddir);
          }
          else
            dynorient=Dorie[mini];
        }
        else{
//random dynode orientation
          dynorient=G4RandomDirection();
      //dynode orthogonal to LAPPD axis
          dynorient=dynorient.perpPart(lappddir);
        }
        if(dynorient.mag()==0){
          for(int di=0;di<100 && dynorient.mag()==0;di++){
            dynorient=G4RandomDirection();
            dynorient=dynorient.perpPart(lappddir);
          }
          if(dynorient.mag()==0)
            cout<<"Warning: tried 100 times to generate a random dynode orientation for "<<id<<"-th LAPPD and failed. dynorient "<<dynorient(0)<<","<<dynorient(1)<<","<<dynorient(2)<<"\n";
        }
        dynorient=dynorient.unit();
    //build BEfficiencyCorrection table. LAPPD x axis is dynorient
        bool isOutRange;//just a flag, not really used in the G4 code
        double BeffiComp;
        int sheetno=0;
        if(Bepsix.size()>1){
          double chooser=G4UniformRand();
          if(chooser<1./3) sheetno=0;
          else if(chooser<2./3) sheetno=1;
          else sheetno=2;
        }
        if(BEffiModel=="multiplicative"){
          BeffiComp=Bepsix[sheetno].GetValue(bfield*dynorient,isOutRange)*Bepsiy[sheetno].GetValue(bfield*(lappddir.cross(dynorient)).unit(),isOutRange);
          if(CorrBEpsiInput && BeffiComp>1)
            BEfficiencyCorrection.push_back(pair<int,double>(id,1));
          else
            BEfficiencyCorrection.push_back(pair<int,double>(id,BeffiComp));
        }
        else
          if(BEffiModel=="additive"){
            BeffiComp=Bepsix[sheetno].GetValue(bfield*dynorient,isOutRange)+Bepsiy[sheetno].GetValue(bfield*(lappddir.cross(dynorient)).unit(),isOutRange)-1.;
          if(CorrBEpsiInput && BeffiComp>1)
            BEfficiencyCorrection.push_back(pair<int,double>(id,1));
          else
            BEfficiencyCorrection.push_back(pair<int,double>(id,BeffiComp));
          }
          else
            cout<<"\nError: undefined B Efficiency Model\n";
      }
    }
    
    // rotation required to point in direction of lappddir
    double angle_y = (-1.0)*atan2(lappddir.x(), lappddir.z());
    double angle_x = atan2(lappddir.y(),
			   sqrt(lappddir.x()*lappddir.x()+lappddir.z()*lappddir.z()));
    
    G4RotationMatrix* lappdrot = new G4RotationMatrix();
    lappdrot->rotateY(angle_y);
    lappdrot->rotateX(angle_x);
    // ****************************************************************
    // * Use the constructor that specifies the PHYSICAL mother, since
    // * each LAPPD occurs only once in one physical volume.  This saves
    // * the GeometryManager some work. -GHS.
    // ****************************************************************
//     G4PVPlacement* thisPhysLAPPD = new G4PVPlacement(lappdrot,
//                       lappdpos,
//                       lappdname,
//                       logiLAPPD,
//                       phys_mother,
//                       false,
//                       id);
//       if (!lappdParam.useEnvelope) {
//       // If not using envelope volume, the PMT optical surfaces have NOT been set
//       // and we must do so NOW.
//       lappdConstruct.SetPMTOpticalSurfaces(thisPhysLAPPD,lappdname);
//     }

    lappdConstruct.PlaceLAPPD(lappdrot, lappdpos, lappdname, logiLAPPD, phys_mother, false, id);
    
  } // end loop over id

//finally pass the lookup table to GLG4PMTOpticalModel
  if(BFieldOn){
    const G4String modname(volume_name+"_optical_model");
//    G4cout<<"Setting B Efficiency Correction Table for LAPPD optical model "<<modname<<"\n";
    
    if(logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[0]->GetName()==modname)
      ((GLG4PMTOpticalModel *)logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[0])->SetBEfficiencyCorrection(BEfficiencyCorrection);
    else{
      for(int i=0;i<int(logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList().size());i++)
        if(logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[i]->GetName()==modname){
          ((GLG4PMTOpticalModel *)logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[i])->SetBEfficiencyCorrection(BEfficiencyCorrection);
          G4cout<<"trying to set B efficiency for "<<((GLG4PMTOpticalModel *)logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[i])->GetName()<<"\n";
          break;
        }
    }
/*    for(int i=0;i<int(logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList().size());i++)
      ((GLG4PMTOpticalModel *)logiLAPPD->GetFastSimulationManager()->GetFastSimulationModelList()[i])->DumpBEfficiencyCorrectionTable();*/
  }
  
  return 0; // There is no specific physical volume to return
}

} // namespace RAT
