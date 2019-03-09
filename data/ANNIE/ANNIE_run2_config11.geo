////////////////////////////////////////////////////////
// ANNIE detector geometry for Phase 2 
// 
// Config 10: - 20 LUX 10inch PMTs at bottom (long bases)
//	     - 45 10inch Watchboy, 40 8inch hqe
//           - 22 11 inch ETEL PMT on top (not waterproof)
//
// Author: V. Fischer <vfischer@ucdavis.edu>
//
// Revisions:
//  2016-09-13 : Only the tank is present so far (no veto nor MRD)
//  2016- 2018 : Lots of revisions
//  2018-02-27 : Config 10 (45 Watchboy r7081 + 40 new r5912 hqe on side) added
////////////////////////////////////////////////////////

{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [30000.0, 30000.0, 30000.0], // mm, half-length
material: "rock",
invisible: 1,
}

{
name: "GEO",
index: "hall",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world", 
type: "box",
size: [3505.2, 6172.2, 2438.4], // mm, half-length
position: [-431.8, 4038.6, 2438.4],
color: [0.5, 1.0, 0.0, 0.1],
material: "air",
}

/////////////////////////////////////////////////////////////////////
///////////////********** Tank volumes ***********///////////////////
/////////////////////////////////////////////////////////////////////
{
name: "GEO",
index: "tank",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "tube",
r_max: 1524.0,
size_z: 1981.2,
position: [431.8, -4038.6, -714.4,],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
rotation: [90.0, 0.0, 90.0],
}

{
name: "GEO",
index: "liner",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
type: "tube",
r_max: 1523.0,
size_z: 1980.2,
position: [0.0, 0.0, 0.0],
material: "acrylic_black",
color: [1.0, 0.5, 0.5, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "detector",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "liner",
type: "tube",
r_max: 1522.0,
size_z: 1979.2,
position: [0.0, 0.0, 0.0],
material: "water_gdS_0p2",
color: [0.4, 0.4, 0.6, 0.3],
drawstyle: "solid"
}

// {
// name: "GEO",
// index: "detector_fiducial",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "tube",
// //r_max: 1150.0,
// r_max: 500.0,
// //size_z: 1500.0,
// size_z: 500.0,
// position: [0.0, 0.0, 0.0],
// material: "water_gdS_0p2",
// color: [0.1, 0.4, 0.6, 0.9],
// drawstyle: "solid"
// }

// {
// name: "GEO",
// index: "detector_fiducial_muon",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "box",
// size: [1000.0, 600.0, 500], // mm
// position: [600.0, 0.0, 0.0],
// material: "water_gdS_0p2",
// color: [0.6, 0.4, 0.6, 0.5],
// drawstyle: "solid",
// rotation: [0.0, 90.0, 0.0],
// }
/////////////////////////////////////////////////////////////////////
///////////********** End of tank volumes ***********////////////////
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
///////////////********** MRD volumes ***********////////////////////
/////////////////////////////////////////////////////////////////////
{
name: "GEO",
index: "mrd_iron_layer_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [1525.0, 1370.0, 24.4], // mm
position: [431.8, -4038.6, 1209.6],
rotation: [0.0, 0.0, -90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "mrd_scint_hori_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [1550.0, 1300.0, 3.0], // mm
position: [431.8, -4038.6, 1238],
rotation: [0.0, 0.0, -90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "plastic_scint",
color: [1.0, 0.5, 0.2, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "mrd_iron_layer_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [1525.0, 1370.0, 24.4], // mm
position: [431.8, -4038.6, 1266.4],
rotation: [0.0, 0.0, -90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "mrd_scint_vert_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [1500.0, 1380.0, 3.0], // mm
position: [431.8, -4038.6, 1294.8],
rotation: [0.0, 0.0, -90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "plastic_scint",
color: [1.0, 0.5, 0.2, 0.1],
drawstyle: "solid",
}
/////////////////////////////////////////////////////////////////////
///////////********** End of MRD volumes  ***********////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
///////////////********** PMT arrays ***********/////////////////////
/////////////////////////////////////////////////////////////////////

{ 
name: "GEO", 
index: "bottom_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE", // LUX 10inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_bottomgrid", //generated on the fly
// start_idx: 0, //index of first inner pmt
// end_idx: 19, //index of last inner pmt
orientation: "manual",
} 

{ 
name: "GEO", 
index: "top_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "d784kflb", //ETEL 11inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_topgrid", //generated on the fly
// start_idx: 20, //index of first inner pmt
// end_idx: 41, //index of last inner pmt
orientation: "manual",
} 

// Side ring 1 (lower)
{ 
name: "GEO", 
index: "side_ring_1_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE", // Watchboy 10 inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 69, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -1069.4],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 2-1
{ 
name: "GEO", 
index: "side_ring_2_1_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_hqe_ANNIE", 
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_2_1", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -661.9],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 2-2
{ 
name: "GEO", 
index: "side_ring_2_2_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE", 
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_2_2", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -661.9],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 3 
{ 
name: "GEO", 
index: "side_ring_3_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_hqe_ANNIE", 
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_3", //generated on the fly
// start_idx: 80, //index of first inner pmt
// end_idx: 89, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -254.5],
// orient_point: [0.0, 0.0, -133.3],   
} 

// Side ring 4-1
{ 
name: "GEO", 
index: "side_ring_4_1_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_hqe_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_4_1", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 153.0],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 4-2
{ 
name: "GEO", 
index: "side_ring_4_2_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_4_2", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 153.0],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 5
{ 
name: "GEO", 
index: "side_ring_5_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_hqe_ANNIE", 
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_5", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 560.5],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 6
{ 
name: "GEO", 
index: "side_ring_6_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config11_side_ring_6", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 967.9],
// orient_point: [0.0, 0.0, -133.3],  
} 

/////////////////////////////////////////////////////////////////////
///////////********** End of PMT arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
///////////********** LAPPD arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////

// Side ring 1 (lower)
{ 
name: "GEO", 
index: "side_ring_1_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 69, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -1069.4],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 2
{ 
name: "GEO", 
index: "side_ring_2_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_2", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -661.9],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 3 
{ 
name: "GEO", 
index: "side_ring_3_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_3", //generated on the fly
// start_idx: 80, //index of first inner pmt
// end_idx: 89, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -254.5],
// orient_point: [0.0, 0.0, -133.3],   
} 

// Side ring 4
{ 
name: "GEO", 
index: "side_ring_4_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_4", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 153.0],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 5
{ 
name: "GEO", 
index: "side_ring_5_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_5", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 560.5],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 6
{ 
name: "GEO", 
index: "side_ring_6_lappds", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "lappdarray", 
lappd_model: "lappd_basic", 
lappd_detector_type: "idlappd",
sensitive_detector: "/mydet/pmt/inner_lappd", 
efficiency_correction: 1.000,  
pos_table: "LAPPDINFO_config11_side_ring_6", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 967.9],
// orient_point: [0.0, 0.0, -133.3],  
} 

/////////////////////////////////////////////////////////////////////
///////////********** End of LAPPD arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////
