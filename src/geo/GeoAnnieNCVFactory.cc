#include <RAT/GeoAnnieNCVFactory.hh>
#include <RAT/Materials.hh>
#include <RAT/DB.hh>
#include <RAT/Log.hh>

#include <G4VSolid.hh>
#include <G4PVPlacement.hh>
#include <G4SubtractionSolid.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Polyhedra.hh>
#include <G4Material.hh>
#include <G4Ellipsoid.hh>
#include <G4VPhysicalVolume.hh>
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>
#include <CLHEP/Units/SystemOfUnits.h>

#include <vector>

using namespace std;

namespace RAT {

G4VPhysicalVolume *GeoAnnieNCVFactory::Construct(DBLinkPtr table) {
    string volumeName = table->GetIndex();

    // Get references to the mother volume
//     G4LogicalVolume *motherLog = FindMother(table->GetS("mother"));
//     G4VPhysicalVolume *motherPhys = FindPhysMother(table->GetS("mother"));
    
    // Get NCV information
    DBLinkPtr NCVinfo = DB::Get()->GetLink("GEO","NCV");
    vector<G4double> ncv_center = NCVinfo->GetDArray("ncv_center"); // NCV center
    G4double ncv_center_x = ncv_center[0]; 
    G4double ncv_center_y = ncv_center[1];
    G4double ncv_center_z = ncv_center[2];

//     G4Material *frameMaterial = G4Material::GetMaterial(NCVinfo->GetS("frame_material")); // frame material
//     G4Material *ncvMaterial = G4Material::GetMaterial(NCVinfo->GetS("ncv_material")); // ncv material
//     G4Material *liquidMaterial = G4Material::GetMaterial(NCVinfo->GetS("liquid_material")); // liquid material
    
//     DBLinkPtr OPTICSinfo = DB::Get()->GetLink("GEO","NCV");
//     G4OpticalSurface *transparent_surf = GetSurface(OPTICSinfo->GetS("transparent_surface"));
//     G4OpticalSurface *opaque_surf = GetSurface(OPTICSinfo->GetS("opaque_surface"));
//     G4OpticalSurface *reflective_surf = GetSurface(OPTICSinfo->GetS("reflective_surface"));
//     G4OpticalSurface *metal_surf = GetSurface(OPTICSinfo->GetS("metal_surface"));
    
    //------------ NCV size information ------------//
    // All lengths are in fact half-radii, half-height, half-lengths and are in mm
    // NCV vessel and liquid
//     G4double radius_liquid = 250.25;
//     G4double zsize_liquid = 254.0;
//     G4double thickness_vessel = 3.75;
//     G4double zsize_vessel = 254.0;
//     
//     // NCV caps top and bottom
//     G4double zsize_caps = 12.7;
//     G4double side_caps = 254.0;
//     
//     // Basket metal plates, ballast and bridal bars
//     G4double zsize_basket_metalplate = 19.05;
//     G4double length_basket_metalplate = 190.0;
//     G4double width_basket_metalplate = 2.5;
//     
//     G4double zsize_basket_centermetalplate = 25.4;
//     G4double length_basket_centermetalplate = 187.63;
//     G4double width_basket_centermetalplate = 2.5;
//     
//     G4double radius_basket_ballast = 19.05;
//     G4double zsize_basket_ballast = 187.63;
//     
//     G4double radius_bridalbar = 6.35;
//     G4double zsize_bridalbar = 254.0;
//     
//     // NCV PMT cases
//     G4double radius_pmtcase = 38.7;
//     G4double zsize_pmtcase = 150.0;
//     G4double radius_pmtcase_inside = 38.2;
//     G4double zsize_pmtcase_inside = 148.0;
//     G4double thickness_pmtcase_blacksheet = 0.01;
    
    //------------ NCV position information ------------//
    // Relative to the NCV center
    G4double zpos_topcap = ncv_center_z + 266.7;
    G4double zpos_botcap = ncv_center_z - 266.7;
    
    G4double zpos_metalplate_top = ncv_center_z + 298.45;
    G4double zpos_metalplate_topcenter = ncv_center_z + 304.8;
    G4double zpos_metalplate_bot = ncv_center_z - 298.45;
    
    G4double ypos_metalplate_1 = ncv_center_y + 190.13;
    G4double ypos_metalplate_2 = ncv_center_y + 207.83;
    G4double ypos_metalplate_3 = ncv_center_y - 190.13;
    G4double ypos_metalplate_4 = ncv_center_y - 207.83;
    
    G4double xpos_ballast_1 = ncv_center_x + 190.13;
    G4double xpos_ballast_2 = ncv_center_x - 190.13;
     
    G4double rotation_radius_bridalbar = 265.34;
    
    G4double zpos_pmtcase = ncv_center_z + 429.4;
    G4double zpos_ncvpmt = ncv_center_z + 152.12; //different cux PMT are in GLOBAL coordinates not wrt to mother volume
    G4double xpos_pmtcase_1 = ncv_center_x + 100;
    G4double xpos_pmtcase_2 = ncv_center_x - 100;
    
    G4double zpos_hefty_bottom_reflective_mylar = ncv_center_z - 317.5;
    
    
    vector<G4double> xpos_ncv_pmt_1; xpos_ncv_pmt_1.clear(); xpos_ncv_pmt_1.push_back(xpos_pmtcase_1);
    vector<G4double> ypos_ncv_pmt_1; ypos_ncv_pmt_1.clear(); ypos_ncv_pmt_1.push_back(ncv_center_y);
    vector<G4double> zpos_ncv_pmt_1; zpos_ncv_pmt_1.clear(); zpos_ncv_pmt_1.push_back(zpos_ncvpmt);
    vector<G4double> xpos_ncv_pmt_2; xpos_ncv_pmt_2.clear(); xpos_ncv_pmt_2.push_back(xpos_pmtcase_2);
    vector<G4double> ypos_ncv_pmt_2; ypos_ncv_pmt_2.clear(); ypos_ncv_pmt_2.push_back(ncv_center_y);
    vector<G4double> zpos_ncv_pmt_2; zpos_ncv_pmt_2.clear(); zpos_ncv_pmt_2.push_back(zpos_ncvpmt);
      
    /*
    //========== Building the NCV volumes ==========//
    // Vessel and liquid
    G4Tubs *ncv_vessel = new G4Tubs("ncv_vessel",radius_liquid*CLHEP::mm, (radius_liquid+thickness_vessel)*CLHEP::mm,zsize_vessel*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_vessel_log = new G4LogicalVolume(ncv_vessel,ncvMaterial,"ncv_vessel_log");
    G4VPhysicalVolume *ncv_vessel_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ncv_center_y,ncv_center_z),ncv_vessel_log,"ncv_vessel_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_vessel_phys,transparent_surf);
    
    G4Tubs *ncv_liquid = new G4Tubs("ncv_vessel",0.0*CLHEP::mm, radius_liquid*CLHEP::mm,zsize_liquid*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_liquid_log = new G4LogicalVolume(ncv_liquid,liquidMaterial,"ncv_vessel_log");
    G4VPhysicalVolume *ncv_liquid_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ncv_center_y,ncv_center_z),ncv_liquid_log,"ncv_liquid_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_liquid_phys,transparent_surf);
    
    G4Box *ncv_vessel_topcap = new G4Box("ncv_vessel_topcap",side_caps* CLHEP::mm,side_caps* CLHEP::mm,zsize_caps* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_vessel_topcap_log = new G4LogicalVolume(ncv_vessel_topcap,ncvMaterial,"ncv_vessel_topcap_log");
    G4VPhysicalVolume *ncv_vessel_topcap_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ncv_center_y,zpos_topcap),ncv_vessel_topcap_log,"ncv_vessel_topcap_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_vessel_topcap_phys,transparent_surf);
    
    G4Box *ncv_vessel_botcap = new G4Box("ncv_vessel_botcap",side_caps* CLHEP::mm,side_caps* CLHEP::mm,zsize_caps* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_vessel_botcap_log = new G4LogicalVolume(ncv_vessel_botcap,ncvMaterial,"ncv_vessel_botcap_log");
    G4VPhysicalVolume *ncv_vessel_botcap_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ncv_center_y,zpos_botcap),ncv_vessel_botcap_log,"ncv_vessel_botcap_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_vessel_botcap_phys,transparent_surf);
    
    
    // Basket
    G4Box *ncv_basket_metalplate_bot1 = new G4Box("ncv_basket_metalplate_bot1",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_bot1_log = new G4LogicalVolume(ncv_basket_metalplate_bot1,frameMaterial,"ncv_basket_metalplate_bot1_log");
    G4VPhysicalVolume *ncv_basket_metalplate_bot1_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_1,zpos_metalplate_bot),ncv_basket_metalplate_bot1_log,"ncv_basket_metalplate_bot1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_bot1_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_bot2 = new G4Box("ncv_basket_metalplate_bot2",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_bot2_log = new G4LogicalVolume(ncv_basket_metalplate_bot2,frameMaterial,"ncv_basket_metalplate_bot2_log");
    G4VPhysicalVolume *ncv_basket_metalplate_bot2_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_2,zpos_metalplate_bot),ncv_basket_metalplate_bot2_log,"ncv_basket_metalplate_bot2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_bot2_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_bot3 = new G4Box("ncv_basket_metalplate_bot3",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_bot3_log = new G4LogicalVolume(ncv_basket_metalplate_bot3,frameMaterial,"ncv_basket_metalplate_bot3_log");
    G4VPhysicalVolume *ncv_basket_metalplate_bot3_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_3,zpos_metalplate_bot),ncv_basket_metalplate_bot3_log,"ncv_basket_metalplate_bot3_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_bot3_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_bot4 = new G4Box("ncv_basket_metalplate_bot4",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_bot4_log = new G4LogicalVolume(ncv_basket_metalplate_bot4,frameMaterial,"ncv_basket_metalplate_bot4_log");
    G4VPhysicalVolume *ncv_basket_metalplate_bot4_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_4,zpos_metalplate_bot),ncv_basket_metalplate_bot4_log,"ncv_basket_metalplate_bot4_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_bot4_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_top1 = new G4Box("ncv_basket_metalplate_top1",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_top1_log = new G4LogicalVolume(ncv_basket_metalplate_top1,frameMaterial,"ncv_basket_metalplate_top1_log");
    G4VPhysicalVolume *ncv_basket_metalplate_top1_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_1,zpos_metalplate_top),ncv_basket_metalplate_top1_log,"ncv_basket_metalplate_top1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_top1_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_top2 = new G4Box("ncv_basket_metalplate_top2",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_top2_log = new G4LogicalVolume(ncv_basket_metalplate_top2,frameMaterial,"ncv_basket_metalplate_top2_log");
    G4VPhysicalVolume *ncv_basket_metalplate_top2_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_2,zpos_metalplate_top),ncv_basket_metalplate_top2_log,"ncv_basket_metalplate_top2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_top2_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_top3 = new G4Box("ncv_basket_metalplate_top3",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_top3_log = new G4LogicalVolume(ncv_basket_metalplate_top3,frameMaterial,"ncv_basket_metalplate_top3_log");
    G4VPhysicalVolume *ncv_basket_metalplate_top3_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_3,zpos_metalplate_top),ncv_basket_metalplate_top3_log,"ncv_basket_metalplate_top3_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_top3_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_top4 = new G4Box("ncv_basket_metalplate_top4",length_basket_metalplate* CLHEP::mm,width_basket_metalplate* CLHEP::mm,zsize_basket_metalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_top4_log = new G4LogicalVolume(ncv_basket_metalplate_top4,frameMaterial,"ncv_basket_metalplate_top4_log");
    G4VPhysicalVolume *ncv_basket_metalplate_top4_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ypos_metalplate_4,zpos_metalplate_top),ncv_basket_metalplate_top4_log,"ncv_basket_metalplate_top4_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_top4_phys, metal_surf);
    
    G4Box *ncv_basket_metalplate_topcenter = new G4Box("ncv_basket_metalplate_topcenter",length_basket_centermetalplate* CLHEP::mm,width_basket_centermetalplate* CLHEP::mm,zsize_basket_centermetalplate* CLHEP::mm); //name,x,y,z
    G4LogicalVolume *ncv_basket_metalplate_topcenter_log = new G4LogicalVolume(ncv_basket_metalplate_topcenter,frameMaterial,"ncv_basket_metalplate_topcenter_log");
    G4VPhysicalVolume *ncv_basket_metalplate_topcenter_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x,ncv_center_y,zpos_metalplate_topcenter),ncv_basket_metalplate_topcenter_log,"ncv_basket_metalplate_topcenter_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_metalplate_topcenter_phys, metal_surf);
    
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90. * CLHEP::deg);
    
    G4Tubs *ncv_basket_ballast1 = new G4Tubs("ncv_basket_ballast1",0.0*CLHEP::mm, radius_basket_ballast*CLHEP::mm,zsize_basket_ballast*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_basket_ballast1_log = new G4LogicalVolume(ncv_basket_ballast1,frameMaterial,"ncv_basket_ballast1_log");
    G4VPhysicalVolume *ncv_basket_ballast1_phys = new G4PVPlacement(rot,G4ThreeVector(xpos_ballast_1,ncv_center_y,zpos_metalplate_bot),ncv_basket_ballast1_log,"ncv_basket_ballast1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_ballast1_phys, metal_surf);
    
    G4Tubs *ncv_basket_ballast2 = new G4Tubs("ncv_basket_ballast2",0.0*CLHEP::mm, radius_basket_ballast*CLHEP::mm,zsize_basket_ballast*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_basket_ballast2_log = new G4LogicalVolume(ncv_basket_ballast2,frameMaterial,"ncv_basket_ballast2_log");
    G4VPhysicalVolume *ncv_basket_ballast2_phys = new G4PVPlacement(rot,G4ThreeVector(xpos_ballast_2,ncv_center_y,zpos_metalplate_bot),ncv_basket_ballast2_log,"ncv_basket_ballast2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_basket_ballast2_phys, metal_surf);
    
    G4Tubs *ncv_bridal_bar1 = new G4Tubs("ncv_bridal_bar1",0.0*CLHEP::mm, radius_bridalbar*CLHEP::mm,zsize_bridalbar*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_bridal_bar1_log = new G4LogicalVolume(ncv_bridal_bar1,frameMaterial,"ncv_bridal_bar1_log");
    G4VPhysicalVolume *ncv_bridal_bar1_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x+rotation_radius_bridalbar*cos(CLHEP::pi/4.),ncv_center_y+rotation_radius_bridalbar*sin(CLHEP::pi/4.),ncv_center_z),ncv_bridal_bar1_log,"ncv_bridal_bar1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_bridal_bar1_phys, metal_surf);
    
    G4Tubs *ncv_bridal_bar2 = new G4Tubs("ncv_bridal_bar2",0.0*CLHEP::mm, radius_bridalbar*CLHEP::mm,zsize_bridalbar*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_bridal_bar2_log = new G4LogicalVolume(ncv_bridal_bar2,frameMaterial,"ncv_bridal_bar2_log");
    G4VPhysicalVolume *ncv_bridal_bar2_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x-rotation_radius_bridalbar*cos(CLHEP::pi/4.),ncv_center_y+rotation_radius_bridalbar*sin(CLHEP::pi/4.),ncv_center_z),ncv_bridal_bar2_log,"ncv_bridal_bar2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_bridal_bar2_phys, metal_surf);
    
    G4Tubs *ncv_bridal_bar3 = new G4Tubs("ncv_bridal_bar3",0.0*CLHEP::mm, radius_bridalbar*CLHEP::mm,zsize_bridalbar*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_bridal_bar3_log = new G4LogicalVolume(ncv_bridal_bar3,frameMaterial,"ncv_bridal_bar3_log");
    G4VPhysicalVolume *ncv_bridal_bar3_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x+rotation_radius_bridalbar*cos(CLHEP::pi/4.),ncv_center_y-rotation_radius_bridalbar*sin(CLHEP::pi/4.),ncv_center_z),ncv_bridal_bar3_log,"ncv_bridal_bar3_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_bridal_bar3_phys, metal_surf);
    
    G4Tubs *ncv_bridal_bar4 = new G4Tubs("ncv_bridal_bar4",0.0*CLHEP::mm, radius_bridalbar*CLHEP::mm,zsize_bridalbar*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_bridal_bar4_log = new G4LogicalVolume(ncv_bridal_bar4,frameMaterial,"ncv_bridal_bar4_log");
    G4VPhysicalVolume *ncv_bridal_bar4_phys = new G4PVPlacement(NULL,G4ThreeVector(ncv_center_x-rotation_radius_bridalbar*cos(CLHEP::pi/4.),ncv_center_y-rotation_radius_bridalbar*sin(CLHEP::pi/4.),ncv_center_z),ncv_bridal_bar4_log,"ncv_bridal_bar4_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_bridal_bar4_phys, metal_surf);
    
    
    // PMT cases
    G4Tubs *ncv_pmt_vessel_1 = new G4Tubs("ncv_pmt_vessel_1",0.0*CLHEP::mm, radius_pmtcase*CLHEP::mm,zsize_pmtcase*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_1_log = new G4LogicalVolume(ncv_pmt_vessel_1,ncvMaterial,"ncv_pmt_vessel_1_log");
    G4VPhysicalVolume *ncv_pmt_vessel_1_phys = new G4PVPlacement(NULL,G4ThreeVector(xpos_pmtcase_1,ncv_center_y,zpos_pmtcase),ncv_pmt_vessel_1_log,"ncv_pmt_vessel_1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_pmt_vessel_1_phys, transparent_surf);
    
    G4Tubs *ncv_pmt_vessel_air_1 = new G4Tubs("ncv_pmt_vessel_air_1",0.0*CLHEP::mm, radius_pmtcase_inside*CLHEP::mm,zsize_pmtcase_inside*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_air_1_log = new G4LogicalVolume(ncv_pmt_vessel_air_1,G4Material::GetMaterial("air"),"ncv_pmt_vessel_air_1_log");
    G4VPhysicalVolume *ncv_pmt_vessel_air_1_phys = new G4PVPlacement(NULL,G4ThreeVector(0.,0.,0.),ncv_pmt_vessel_air_1_log,"ncv_pmt_vessel_air_1_phys",ncv_pmt_vessel_1_log,false,0);
    new G4LogicalBorderSurface("border", ncv_pmt_vessel_1_phys, ncv_pmt_vessel_air_1_phys, transparent_surf);
    
    G4Tubs *ncv_pmt_vessel_blacksheet_1 = new G4Tubs("ncv_pmt_vessel_blacksheet_1",radius_pmtcase*CLHEP::mm, (radius_pmtcase+thickness_pmtcase_blacksheet)*CLHEP::mm,zsize_pmtcase*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_blacksheet_1_log = new G4LogicalVolume(ncv_pmt_vessel_blacksheet_1,G4Material::GetMaterial("acrylic_black"),"ncv_pmt_vessel_blacksheet_1_log");
    G4VPhysicalVolume *ncv_pmt_vessel_blacksheet_1_phys = new G4PVPlacement(NULL,G4ThreeVector(xpos_pmtcase_1,ncv_center_y,zpos_pmtcase),ncv_pmt_vessel_blacksheet_1_log,"ncv_pmt_vessel_blacksheet_1_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_pmt_vessel_blacksheet_1_phys, opaque_surf);
    
    G4Tubs *ncv_pmt_vessel_2 = new G4Tubs("ncv_pmt_vessel_2",0.0*CLHEP::mm, radius_pmtcase*CLHEP::mm,zsize_pmtcase*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_2_log = new G4LogicalVolume(ncv_pmt_vessel_2,ncvMaterial,"ncv_pmt_vessel_2_log");
    G4VPhysicalVolume *ncv_pmt_vessel_2_phys = new G4PVPlacement(NULL,G4ThreeVector(xpos_pmtcase_2,ncv_center_y,zpos_pmtcase),ncv_pmt_vessel_2_log,"ncv_pmt_vessel_2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_pmt_vessel_2_phys, transparent_surf);
    
    G4Tubs *ncv_pmt_vessel_air_2 = new G4Tubs("ncv_pmt_vessel_air_2",0.0*CLHEP::mm, radius_pmtcase_inside*CLHEP::mm,zsize_pmtcase_inside*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_air_2_log = new G4LogicalVolume(ncv_pmt_vessel_air_2,G4Material::GetMaterial("air"),"ncv_pmt_vessel_air_2_log");
    G4VPhysicalVolume *ncv_pmt_vessel_air_2_phys = new G4PVPlacement(NULL,G4ThreeVector(0.,0.,0.),ncv_pmt_vessel_air_2_log,"ncv_pmt_vessel_air_2_phys",ncv_pmt_vessel_2_log,false,0);
    new G4LogicalBorderSurface("border", ncv_pmt_vessel_2_phys, ncv_pmt_vessel_air_2_phys, transparent_surf);
    
    G4Tubs *ncv_pmt_vessel_blacksheet_2 = new G4Tubs("ncv_pmt_vessel_blacksheet_2",radius_pmtcase*CLHEP::mm, (radius_pmtcase+thickness_pmtcase_blacksheet)*CLHEP::mm,zsize_pmtcase*CLHEP::mm,0,2.*CLHEP::pi); //name,rmin,rmax,z,phi0,phimax
    G4LogicalVolume *ncv_pmt_vessel_blacksheet_2_log = new G4LogicalVolume(ncv_pmt_vessel_blacksheet_2,G4Material::GetMaterial("acrylic_black"),"ncv_pmt_vessel_blacksheet_2_log");
    G4VPhysicalVolume *ncv_pmt_vessel_blacksheet_2_phys = new G4PVPlacement(NULL,G4ThreeVector(xpos_pmtcase_2,ncv_center_y,zpos_pmtcase),ncv_pmt_vessel_blacksheet_2_log,"ncv_pmt_vessel_blacksheet_2_phys",motherLog,false,0);
    new G4LogicalBorderSurface("border", motherPhys, ncv_pmt_vessel_blacksheet_2_phys, opaque_surf);
    */
    
    vector<double> volume_position(3);
    
    info << "Override default NCV information...\n";
    DB *db = DB::Get();
    volume_position[0] = ncv_center_x; volume_position[1] = ncv_center_y; volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_vessel","position",volume_position);
    volume_position[2] = zpos_topcap;
    db->SetDArray("GEO","ncv_vessel_topcap","position",volume_position);
    volume_position[2] = zpos_botcap;
    db->SetDArray("GEO","ncv_vessel_botcap","position",volume_position);
    volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_liquid","position",volume_position);
    
    volume_position[0] = ncv_center_x; volume_position[1] = ypos_metalplate_1; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_metalplate_bot1","position",volume_position);
    volume_position[1] = ypos_metalplate_2; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_metalplate_bot2","position",volume_position);
    volume_position[1] = ypos_metalplate_3; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_metalplate_bot3","position",volume_position);
    volume_position[1] = ypos_metalplate_4; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_metalplate_bot4","position",volume_position);
    volume_position[1] = ypos_metalplate_1; volume_position[2] = zpos_metalplate_top;
    db->SetDArray("GEO","ncv_basket_metalplate_top1","position",volume_position);
    volume_position[1] = ypos_metalplate_2; volume_position[2] = zpos_metalplate_top;
    db->SetDArray("GEO","ncv_basket_metalplate_top2","position",volume_position);
    volume_position[1] = ypos_metalplate_3; volume_position[2] = zpos_metalplate_top;
    db->SetDArray("GEO","ncv_basket_metalplate_top3","position",volume_position);
    volume_position[1] = ypos_metalplate_4; volume_position[2] = zpos_metalplate_top;
    db->SetDArray("GEO","ncv_basket_metalplate_top4","position",volume_position);
    volume_position[1] = ncv_center_y; volume_position[2] = zpos_metalplate_topcenter;
    db->SetDArray("GEO","ncv_basket_metalplate_topcenter","position",volume_position);
    volume_position[0] = xpos_ballast_1; volume_position[1] = ncv_center_y; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_ballast1","position",volume_position);
    volume_position[0] = xpos_ballast_2; volume_position[1] = ncv_center_y; volume_position[2] = zpos_metalplate_bot;
    db->SetDArray("GEO","ncv_basket_ballast2","position",volume_position);
    volume_position[0] = ncv_center_x+rotation_radius_bridalbar*cos(CLHEP::pi/4.); volume_position[1] = ncv_center_y+rotation_radius_bridalbar*sin(CLHEP::pi/4.); volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_bridal_bar1","position",volume_position);
    volume_position[0] = ncv_center_x-rotation_radius_bridalbar*cos(CLHEP::pi/4.); volume_position[1] = ncv_center_y+rotation_radius_bridalbar*sin(CLHEP::pi/4.); volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_bridal_bar2","position",volume_position);
    volume_position[0] = ncv_center_x+rotation_radius_bridalbar*cos(CLHEP::pi/4.); volume_position[1] = ncv_center_y-rotation_radius_bridalbar*sin(CLHEP::pi/4.); volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_bridal_bar3","position",volume_position);
    volume_position[0] = ncv_center_x-rotation_radius_bridalbar*cos(CLHEP::pi/4.); volume_position[1] = ncv_center_y-rotation_radius_bridalbar*sin(CLHEP::pi/4.); volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_bridal_bar4","position",volume_position);

    volume_position[0] = xpos_pmtcase_1; volume_position[1] = ncv_center_y; volume_position[2] = zpos_pmtcase;
    db->SetDArray("GEO","ncv_pmt_vessel_1","position",volume_position);
    volume_position[0] = 0.0; volume_position[1] = 0.0; volume_position[2] = 0.0;
    db->SetDArray("GEO","ncv_pmt_vessel_air_1","position",volume_position);
    volume_position[0] = xpos_pmtcase_1; volume_position[1] = ncv_center_y; volume_position[2] = zpos_pmtcase;
    db->SetDArray("GEO","ncv_pmt_vessel_blacksheet_1","position",volume_position);
    volume_position[0] = xpos_pmtcase_2; volume_position[1] = ncv_center_y; volume_position[2] = zpos_pmtcase;
    db->SetDArray("GEO","ncv_pmt_vessel_2","position",volume_position);
    volume_position[0] = 0.0; volume_position[1] = 0.0; volume_position[2] = 0.0;
    db->SetDArray("GEO","ncv_pmt_vessel_air_2","position",volume_position);
    volume_position[0] = xpos_pmtcase_2; volume_position[1] = ncv_center_y; volume_position[2] = zpos_pmtcase;
    db->SetDArray("GEO","ncv_pmt_vessel_blacksheet_2","position",volume_position);
    
    db->SetDArray("PMTINFO_run1_ncvpmt_1","x",xpos_ncv_pmt_1);
    db->SetDArray("PMTINFO_run1_ncvpmt_1","y",ypos_ncv_pmt_1);
    db->SetDArray("PMTINFO_run1_ncvpmt_1","z",zpos_ncv_pmt_1);
    db->SetDArray("PMTINFO_run1_ncvpmt_2","x",xpos_ncv_pmt_2);
    db->SetDArray("PMTINFO_run1_ncvpmt_2","y",ypos_ncv_pmt_2);
    db->SetDArray("PMTINFO_run1_ncvpmt_2","z",zpos_ncv_pmt_2);
    
    volume_position[0] = ncv_center_x; volume_position[1] = ncv_center_y; volume_position[2] = zpos_hefty_bottom_reflective_mylar;
    db->SetDArray("GEO","ncv_hefty_bottom_reflective_mylar","position",volume_position);
    volume_position[0] = ncv_center_x; volume_position[1] = ncv_center_y; volume_position[2] = ncv_center_z;
    db->SetDArray("GEO","ncv_hefty_side_reflective_tyvek","position",volume_position);
    
    return NULL; //Unsure about returning NULL here but it seems not to break anything.
}

G4OpticalSurface *GeoAnnieNCVFactory::GetSurface(string surface_name) {
    if (Materials::optical_surface.count(surface_name) == 0)
        Log::Die("error: surface "+ surface_name + " does not exist");
    return Materials::optical_surface[surface_name];
}

G4VisAttributes *GeoAnnieNCVFactory::GetVisAttributes(DBLinkPtr table) {
    try {
        int invisible = table->GetI("invisible");
        if (invisible) return new G4VisAttributes(G4VisAttributes::Invisible);
    } catch (DBNotFoundError &e) { };
    
    G4VisAttributes *vis = new G4VisAttributes();
    
    try {
        const vector<double> &color = table->GetDArray("color");
        if (color.size() == 3) // RGB
            vis->SetColour(G4Colour(color[0], color[1], color[2]));
        else if (color.size() == 4) // RGBA
            vis->SetColour(G4Colour(color[0], color[1], color[2], color[3]));
        else
            warn << "error: " << table->GetName()  << "[" << table->GetIndex() << "].color must have 3 or 4 components" << newline;
    } catch (DBNotFoundError &e) { };
    
    try {
        string drawstyle = table->GetS("drawstyle");
        if (drawstyle == "wireframe")
            vis->SetForceWireframe(true);
        else if (drawstyle == "solid")
            vis->SetForceSolid(true);
        else
            warn << "error: " << table->GetName() << "[" << table->GetIndex() << "].drawstyle must be either \"wireframe\" or \"solid\".";
    } catch (DBNotFoundError &e) { };
    
    try {
        int force_auxedge = table->GetI("force_auxedge");
        vis->SetForceAuxEdgeVisible(force_auxedge == 1);
    } catch (DBNotFoundError &e) { };

    return vis;
}

} // namespace RAT
