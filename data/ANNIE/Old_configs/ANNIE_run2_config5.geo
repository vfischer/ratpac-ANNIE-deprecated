////////////////////////////////////////////////////////
// ANNIE detector geometry for Phase 2 
// 
// Config 2: - 20 LUX 10inch PMTs at bottom (long bases)
//	     - 9 rows 12 PMTs on the sides (45 10inch Watchboy, 60 8inch SK)
//           - 22 11 inch ETEL PMT on top (not waterproof)
//
// Author: V. Fischer <vfischer@ucdavis.edu>
//
// Revisions:
//  2016-09-13 : Only the tank is present so far (no veto nor MRD)
//  2016-11-30 : Config 3 (45 Watchboy + 60 SK PMT on side) added, but no mixing (only row by row)
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
rotation: [90.0, 0.0, -90.0],
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
// r_max: 1200.0,
// size_z: 1500.0,
// position: [0.0, 0.0, 100.0],
// material: "water_gdS_0p2",
// color: [0.1, 0.4, 0.6, 0.9],
// drawstyle: "solid"
// }
/////////////////////////////////////////////////////////////////////
///////////********** End of tank volumes ***********////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
/////////////********** Inner structure ***********//////////////////
/////////////////////////////////////////////////////////////////////

{
name: "GEO",
index: "inner_structure_verticalrod_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [517.54, -1249.45, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [1249.45, -517.54, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [1249.45, 517.54, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [517.54, 1249.45, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_5",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [-517.54, 1249.45, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_6",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [-517.54, -1249.45, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_7",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [-1249.45, -517.54, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_8",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1920.9,
position: [-1249.45, 517.54, 133.3],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [1249.45, 0.0, -1441.5],
rotation: [0.0, 0.0, 0.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-1249.45, 0.0, -1441.5],
rotation: [0.0, 0.0, 0.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [0.0, 1249.45, -1441.5],
rotation: [0.0, 0.0, 90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [0.0, -1249.45, -1441.5],
rotation: [0.0, 0.0, 90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_5",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [883.495, 883.495, -1441.5],
rotation: [0.0, 0.0, -45.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_6",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-883.495, 883.495, -1441.5],
rotation: [0.0, 0.0, -135.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_7",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [883.495, -883.495, -1441.5],
rotation: [0.0, 0.0, -135.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_bot_8",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-883.495, -883.495, -1441.5],
rotation: [0.0, 0.0, -45.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [1249.45, 0.0, 1802.1],
rotation: [0.0, 0.0, 0.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-1249.45, 0.0, 1802.1],
rotation: [0.0, 0.0, 0.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [0.0, 1249.45, 1802.1],
rotation: [0.0, 0.0, 90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [0.0, -1249.45, 1802.1],
rotation: [0.0, 0.0, 90.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_5",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [883.495, 883.495, 1802.1],
rotation: [0.0, 0.0, -45.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_6",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-883.495, 883.495, 1802.1],
rotation: [0.0, 0.0, -135.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_7",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [883.495, -883.495, 1802.1],
rotation: [0.0, 0.0, -135.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_structure_octobeam_top_8",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [25.4, 518.3, 25.4], // mm
position: [-883.495, -883.495, 1802.1],
rotation: [0.0, 0.0, -45.0], // X, Y, Z axis rotations (deg) of element about its center. Rotations are applied in X, Y, Z order
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid",
}
/////////////////////////////////////////////////////////////////////
//////////********** End of inner structure ***********//////////////
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
pos_table: "PMTINFO_run2_bottomgrid", //generated on the fly
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
pos_table: "PMTINFO_run2_topgrid", //generated on the fly
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
pmt_model: "r5912_ANNIE", // SK 8inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 69, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -1069.4],
// orient_point: [0.0, 0.0, -133.3], 
} 

// Side ring 2 
{ 
name: "GEO", 
index: "side_ring_2_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE", // Watchboy 10 inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_2", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -763.8],
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
pmt_model: "r5912_ANNIE", // SK 8inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_3", //generated on the fly
// start_idx: 80, //index of first inner pmt
// end_idx: 89, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -458.2],
// orient_point: [0.0, 0.0, -133.3],   
} 

// Side ring 4 
{ 
name: "GEO", 
index: "side_ring_4_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_4", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -152.6],
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
pmt_model: "r5912_ANNIE", // SK 8inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_5", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 153.0],
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
pos_table: "PMTINFO_config5_side_ring_6", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 458.6],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 7
{ 
name: "GEO", 
index: "side_ring_7_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_ANNIE", // SK 8inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_7", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 764.2],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 8
{ 
name: "GEO", 
index: "side_ring_8_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_8", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 1069.8],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 9 (higher)
{ 
name: "GEO", 
index: "side_ring_9_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_ANNIE", // SK 8inch
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config5_side_ring_9", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 1375.4],
// orient_point: [0.0, 0.0, -133.3],  
} 
/////////////////////////////////////////////////////////////////////
///////////********** End of PMT arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////
