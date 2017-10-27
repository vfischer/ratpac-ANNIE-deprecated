#ifndef __RAT_LAPPDConstruction__
#define __RAT_LAPPDConstruction__

#include <string>
#include <vector>
#include <RAT/DB.hh>
#include <G4Material.hh>
#include <RAT/GLG4TorusStack.hh>
#include <G4OpticalSurface.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <RAT/WaveguideFactory.hh>
#include <RAT/Factory.hh>

namespace RAT {
  

struct LAPPDConstructionParams {
  LAPPDConstructionParams () { 
    efficiencyCorrection = 1.0;
    invisible = false;
  };
  
  bool invisible;
  bool useEnvelope;
  
  // Body
  double glassThickness; // mm
  double width; // mm
  double photocathodeWidth; // mm
  double thick; // mm
  
  G4Material *glass;
  G4Material *vacuum;
  
  G4OpticalSurface *photocathode;
  
  G4VSensitiveDetector *detector;
  
  double efficiencyCorrection; // default to 1.0 for no correction

};

class LAPPDConstruction {
public:
  LAPPDConstruction(DBLinkPtr params, G4LogicalVolume *mother);
  virtual ~LAPPDConstruction() { }
  
  LAPPDConstruction (const LAPPDConstructionParams &params);
  G4LogicalVolume *NewLAPPD(const std::string &prefix, bool simpleVis=false);
  G4VSolid *BuildSolid(const std::string &name);
  virtual G4PVPlacement* PlaceLAPPD(G4RotationMatrix *pmtrot, 
				  G4ThreeVector pmtpos, 
				  const std::string &name, 
				  G4LogicalVolume *logi_pmt, 
				  G4VPhysicalVolume *mother_phys, 
				  bool booleanSolid, int copyNo);
  
  // physical volumes
  G4PVPlacement* body_phys;
  G4PVPlacement* glass_phys;
  G4PVPlacement* vacuum_phys;
  
  G4LogicalVolume *log_lappd;
  LAPPDConstructionParams fParams;

};


} // namespace RAT

#endif
