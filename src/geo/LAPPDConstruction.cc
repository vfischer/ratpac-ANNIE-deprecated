#include <algorithm>
#include <RAT/Log.hh>
#include <RAT/Materials.hh>
#include <RAT/GLG4PMTOpticalModel.hh>
#include <RAT/LAPPDConstruction.hh>
#include <G4Box.hh>
#include <G4Region.hh>
#include <G4VisAttributes.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>

using namespace std;

namespace RAT {

 LAPPDConstruction::LAPPDConstruction(const LAPPDConstructionParams &params) : fParams(params)
  {
    assert(fParams.glass);
    assert(fParams.vacuum);
    assert(fParams.photocathode);
    assert(fParams.glassThickness);
    assert(fParams.width);
    assert(fParams.photocathodeWidth);
    assert(fParams.thick);
    // Do not assert fParams.detector.  If detector==0, then do not associate LAPPD
    // with sensitive volume
    //assert(fParams.detector);
  }
  
  
  G4LogicalVolume *LAPPDConstruction::NewLAPPD(const std::string &prefix, bool simpleVis)
  {
    
//     if (log_lappd) return log_lappd;
                                        
    // Glass body
    G4Box* body_solid  = (G4Box*)BuildSolid(prefix+"_body_solid");
        
    // Construct inners
    const double vacuumWidth = fParams.width - fParams.glassThickness;
    const double vacuumThick = fParams.thick - fParams.glassThickness;
    G4Box* vacuum_solid = new G4Box( prefix + "_vacuum_solid", vacuumWidth, vacuumWidth, vacuumThick);

    // ------------ Logical Volumes -------------
    G4LogicalVolume *body_log, *vacuum_log;
    
    body_log = new G4LogicalVolume( body_solid, fParams.glass, prefix + "_body_logic" );
    vacuum_log = new G4LogicalVolume( vacuum_solid, fParams.vacuum, prefix + "_vacuum_logic" );

    // ------------ Physical Volumes -------------
    G4ThreeVector noTranslation(0., 0., 0.);
    
    // Place the inner solids in the glass solid to produce the physical volumes
    vacuum_phys= new G4PVPlacement
      ( 0,                   // no rotation
	noTranslation,       // must share the same origin than the mother volume
	                     // if we want the LAPPD optical model working properly
	vacuum_log,          // the logical volume
	prefix+"_vacuum_phys",         // a name for this physical volume
	body_log,           // the mother volume
	false,               // no boolean ops
	0 );                 // copy number

    // Go ahead and place the cathode optical surface---this can always be done at this point
     body_phys=0;
//      G4LogicalBorderSurface *pc_log_surface = 
//             new G4LogicalBorderSurface(prefix+"_photocathode_logsurf1",
//                                vacuum_phys, body_phys,
//                                fParams.photocathode);
    // ------------ FastSimulationModel -------------
    // 28-Jul-2006 WGS: Must define a G4Region for Fast Simulations
    // (change from Geant 4.7 to Geant 4.8).
//      G4Region* body_region = new G4Region(prefix+"_GLG4_PMTOpticalRegion");
//      body_region->AddRootLogicalVolume(body_log);
//      new GLG4PMTOpticalModel(prefix+"_optical_model", body_region, body_log,
// 			    pc_log_surface, fParams.efficiencyCorrection,
// 			     0.0, 0.0, 0.0 /*prepusling handled after absorption*/);
     
    // ------------ Vis Attributes -------------
     G4VisAttributes * visAtt;
     if (fParams.invisible) {
       visAtt = new G4VisAttributes(G4Color(0.0,1.0,1.0,0.05));
       body_log->SetVisAttributes(  G4VisAttributes::Invisible );
       vacuum_log->SetVisAttributes(G4VisAttributes::Invisible);
     } else {
       // LAPPD glass
       visAtt= new G4VisAttributes(G4Color(0.0,1.0,1.0,0.05));
       body_log->SetVisAttributes( visAtt );
       // (surface of) interior vacuum is clear orangish gray on top (PC),
       // silvery blue on bottom (mirror)
       visAtt= new G4VisAttributes(G4Color(0.7,0.5,0.3,0.27));
       vacuum_log->SetVisAttributes (visAtt);
     }
    
    log_lappd = body_log;
     
     return log_lappd;
  }
  

  
  G4VSolid* LAPPDConstruction::BuildSolid(const string &name) {
    G4Box* body = new G4Box(name, fParams.width, fParams.width, fParams.thick);
    return body;
  }

  G4PVPlacement* LAPPDConstruction::PlaceLAPPD(
            G4RotationMatrix *lappdrot, 
            G4ThreeVector lappdpos, 
            const std::string &name, 
            G4LogicalVolume *logi_lappd, 
            G4VPhysicalVolume *mother_phys, 
            bool booleanSolid, int copyNo) {

    body_phys = new G4PVPlacement(lappdrot, lappdpos, name, logi_lappd, mother_phys,  booleanSolid, copyNo);

    // photocathode surface
    new G4LogicalBorderSurface(name+"_photocathode_logsurf1", vacuum_phys, body_phys, fParams.photocathode);

         G4LogicalBorderSurface *pc_log_surface = 
            new G4LogicalBorderSurface(name+"_photocathode_logsurf1",
                               vacuum_phys, body_phys,
                               fParams.photocathode);
     G4Region* body_region = new G4Region(name+"_GLG4_PMTOpticalRegion");
     body_region->AddRootLogicalVolume(body_phys->GetLogicalVolume());
     new GLG4PMTOpticalModel(name+"_optical_model", body_region, body_phys->GetLogicalVolume(),
			    pc_log_surface, fParams.efficiencyCorrection,
			     0.0, 0.0, 0.0 /*prepusling handled after absorption*/);
     
    return body_phys;

  }
  
} //namespace RAT
