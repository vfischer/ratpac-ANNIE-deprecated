////////////////////////////////////////////////////////
// ANNIE detector geometry for Phase 2 
// 
// Config 1: - 60 SK PMTs (8inch) at bottom (same as in Run1)
//	     - 7 rows of 10 PMTs on the sides (2 rows of 10inch LUX, 2 rows of 11" ETEL, 3 rows of 10inch Watchboy)
//           - Nothing on top  
//
// Author: V. Fischer <vfischer@ucdavis.edu>
//
// Revisions:
//  2016-09-13 : Only the tank is present so far (no veto nor MRD)
//  12-02-2016: Geometry NOT UPDATED ANYMORE (pmt height or inner structure not updated or not present)
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

///////////////////////// Tank volumes //////////////////////////////
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

{
name: "GEO",
index: "detector_fiducial",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 1200.0,
size_z: 1500.0,
position: [0.0, 0.0, 0.0],
material: "water_gdS_0p2",
color: [0.1, 0.4, 0.6, 0.9],
drawstyle: "solid"
}


///////////////////////// PMT arrays //////////////////////////////
// PMTS: 60 r5912 (phase 1 bottom), 20 11" d784kflb (LBNE), 20 10" r7081 (LUX), 30 10" r7081 (Watchboy)

// Bottom array (same as phase 1), 60 8" R5912
{ 
name: "GEO", 
index: "bottom_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r5912_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_run1_bottomgrid", //generated on the fly
start_idx: 0, //index of first inner pmt
end_idx: 59, //index of last inner pmt
orientation: "manual",
} 

// Side ring 1 (lower), 10 10" r7081
{ 
name: "GEO", 
index: "side_ring_1_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 69, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, -1097.7],
orient_point: [0.0, 0.0, -133.3] 
} 

// Side ring 2 (lower), 10 10" r7081
{ 
name: "GEO", 
index: "side_ring_2_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_2", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, -648.7],
orient_point: [0.0, 0.0, -133.3] 
} 

// Side ring 3 (lower), 10 11" d784kflb
{ 
name: "GEO", 
index: "side_ring_3_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "d784kflb",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_3", //generated on the fly
// start_idx: 80, //index of first inner pmt
// end_idx: 89, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, -198.7],
orient_point: [0.0, 0.0, -133.3]  
} 

// Side ring 4 (lower), 10 11" d784kflb
{ 
name: "GEO", 
index: "side_ring_4_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "d784kflb",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_4", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, 249.3],
orient_point: [0.0, 0.0, -133.3] 
} 

// Side ring 5 (lower), 10 10" HQE r7081
{ 
name: "GEO", 
index: "side_ring_5_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_5", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, 699.3],
orient_point: [0.0, 0.0, -133.3] 
} 

// Side ring 6 (lower), 10 10" HQE r7081
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
pos_table: "PMTINFO_config1_side_ring_6", //generated on the fly
// start_idx: 110, //index of first inner pmt
// end_idx: 119, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, 1148.3],
orient_point: [0.0, 0.0, -133.3] 
} 

// Side ring 7 (lower), 10 10" HQE r7081
{ 
name: "GEO", 
index: "side_ring_7_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_ANNIE",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config1_side_ring_7", //generated on the fly
// start_idx: 120, //index of first inner pmt
// end_idx: 129, //index of last inner pmt
orientation: "point",
// orient_point: [0.0, 0.0, 1598.3],
orient_point: [0.0, 0.0, -133.3] 
} 
