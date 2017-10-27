#include <RAT/GeoLAPPDParser.hh>

#include <string>
#include <G4Material.hh>
#include <G4SDManager.hh>
#include <RAT/GLG4PMTSD.hh>
#include <RAT/Materials.hh>
#include <RAT/GeoFactory.hh>
#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Units/SystemOfUnits.h>

using namespace std;

namespace RAT {

  GeoLAPPDParser::GeoLAPPDParser(DBLinkPtr table, bool useSD)
  {  
    string volume_name = table->GetIndex();

    // Find mother
    string mother_name = table->GetS("mother");
    G4LogicalVolume *mother = GeoFactory::FindMother(mother_name);
    if (mother == 0)
      Log::Die("Unable to find mother volume " + mother_name + " for "
	       + volume_name);

    //////////// Read LAPPD positions

    string pos_table_name = table->GetS("pos_table");
    DBLinkPtr lpos_table = DB::Get()->GetLink(pos_table_name);
    const vector<double> &lappd_x = lpos_table->GetDArray("x");
    const vector<double> &lappd_y = lpos_table->GetDArray("y");
    const vector<double> &lappd_z = lpos_table->GetDArray("z");
 
    // read max number of lappds to use
    int max_lappds = lappd_x.size(); // default to read all
    try { max_lappds = table->GetI("max_lappds"); }
    catch (DBNotFoundError &e) { }
    if (max_lappds > (int) lappd_x.size())
	max_lappds = lappd_x.size();
  
    // Optionally can rescale LAPPD radius from mother volume center for
    // case where LAPPDs have spherical layout symmetry
    bool rescale_radius = false;
    G4double new_radius = 1.0;
    try {
      new_radius = table->GetD("rescale_radius");
      rescale_radius = true;
    } catch (DBNotFoundError &e) { }

    // Load lappd positions as three vectors
    fPos.resize(max_lappds);
    for (int i = 0; i < max_lappds; i++) {
      fPos[i] = G4ThreeVector(lappd_x[i], lappd_y[i], lappd_z[i]);
      if (rescale_radius) fPos[i].setMag(new_radius);
    }

    //////////// Orientation of LAPPDs

    bool orient_manual = false;
    try { 
      string orient_str = table->GetS("orientation");
      if (orient_str == "manual")
	orient_manual = true;
      else if (orient_str == "point")
	orient_manual = false;
      else 
	Log::Die("GeoBuilder error: Unknown LAPPD orientation " 
		 + orient_str);
    } catch (DBNotFoundError &e) { }
    
    vector<double> orient_point_array;
    G4ThreeVector orient_point;

    fDir.resize(max_lappds);
    if (orient_manual) {
      const vector<double> &dirx = lpos_table->GetDArray("dir_x");
      const vector<double> &diry = lpos_table->GetDArray("dir_y");
      const vector<double> &dirz = lpos_table->GetDArray("dir_z");

      for (int i = 0; i < max_lappds; i++)
	fDir[i] = G4ThreeVector(dirx[i], diry[i], dirz[i]).unit();
    } else {
      // compute radially inward pointing 
      orient_point_array = table->GetDArray("orient_point");
      if (orient_point_array.size() != 3)
	Log::Die("GeoBuilder error: orient_point must have 3 values");
      orient_point.set(orient_point_array[0], orient_point_array[1],
		       orient_point_array[2]);

      for (int i = 0; i < max_lappds; i++)
	fDir[i] = (orient_point - fPos[i]).unit();
    }
  
    //////////// Read LAPPD dimensions
    string lappd_model = table->GetS("lappd_model");
    DBLinkPtr llappd = DB::Get()->GetLink("PMT", lappd_model);
    
  fParam.glassThickness = llappd->GetD("glassThickness");
  fParam.width = llappd->GetD("width");
  fParam.photocathodeWidth = llappd->GetD("photocathodeWidth");
  fParam.thick = llappd->GetD("thick");

    //////////// LAPPD Materials
    fParam.glass = G4Material::GetMaterial(llappd->GetS("glass_material"));
    fParam.vacuum = G4Material::GetMaterial(llappd->GetS("lappd_vacuum_material"));
    string pc_surface_name = llappd->GetS("photocathode_surface");
    fParam.photocathode = Materials::optical_surface[pc_surface_name];

    // LAPPD sensitive detector
    if (useSD) {
      string sensitive_detector_name = table->GetS("sensitive_detector");
      G4SDManager* sdman = G4SDManager::GetSDMpointer();
      GLG4PMTSD* lappdSD = new GLG4PMTSD(sensitive_detector_name, max_lappds, 0, 10);
      sdman->AddNewDetector(lappdSD);
      fParam.detector = lappdSD;
    } else
      fParam.detector = 0;


//     fParam.useEnvelope = false; // disable the use of envelope volume for now
    fConstruction = new LAPPDConstruction(fParam);
  }
   
  G4RotationMatrix GeoLAPPDParser::GetLAPPDRotation(int i) const
  {
    G4RotationMatrix rot;
    const G4ThreeVector &dir = fDir[i];

    double angle_y = (-1.0)*atan2(dir.x(), dir.z());
    double angle_x = atan2(dir.y(), sqrt(dir.x()*dir.x()+dir.z()*dir.z()));
    
    rot.rotateY(angle_y);
    rot.rotateX(angle_x);

    return rot;
  }

} // namespace RAT
