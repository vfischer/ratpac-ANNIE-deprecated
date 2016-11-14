////////////////////////////////////////////////////////
// ANNIE detector geometry for Phase 2 
// 
// Config 2: - 20 LUX 10inch PMTs at bottom (long bases)
//	     - 5 rows 9 PMTs on the sides (45 10inch HQE Watchboy)
//           - 22 11 inch ETEL PMT on top (not waterproof)
//
// Author: V. Fischer <vfischer@ucdavis.edu>
//
// Revisions:
//  2016-09-13 : Only the tank is present so far (no veto nor MRD)
//  2016-11-30 : Config 2 (45 Watchboy PMT on side) added
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
size: [3000.0, 3000.0, 4000.0], // mm, half-length
position: [-1276.0, 0.0, 2018.8],
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
position: [1276.0, 0.0, -2018.8],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
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
index: "airgap",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "liner",
type: "tube",
r_max: 1522.0,
size_z: 1979.2,
position: [0.0, 0.0, 0.0],
material: "air",
color: [0.1, 0.2, 0.7, 0.4],
drawstyle: "solid"
}

{
name: "GEO",
index: "detector",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "airgap",
type: "tube",
r_max: 1522.0,
size_z: 1914.5,
position: [0.0, 0.0, -133.3],
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


{ 
name: "GEO", 
index: "bottom_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081", // LUX 10inch
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

// Side ring 1 (lower), r7081 HQE
{ 
name: "GEO", 
index: "side_ring_1_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_hqe", // Watchboy
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config2_side_ring_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 69, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -987.4],
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
pmt_model: "r7081_hqe",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config2_side_ring_2", //generated on the fly
// start_idx: 70, //index of first inner pmt
// end_idx: 79, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, -427.1],
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
pmt_model: "r7081_hqe",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config2_side_ring_3", //generated on the fly
// start_idx: 80, //index of first inner pmt
// end_idx: 89, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 133.2],
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
pmt_model: "r7081_hqe",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config2_side_ring_4", //generated on the fly
// start_idx: 90, //index of first inner pmt
// end_idx: 99, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 693.5],
// orient_point: [0.0, 0.0, -133.3],  
} 

// Side ring 5 (higher)
{ 
name: "GEO", 
index: "side_ring_5_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "detector", 
type: "pmtarray", 
pmt_model: "r7081_hqe",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_config2_side_ring_5", //generated on the fly
// start_idx: 100, //index of first inner pmt
// end_idx: 109, //index of last inner pmt
orientation: "point",
orient_point: [0.0, 0.0, 1253.8],
// orient_point: [0.0, 0.0, -133.3],  
} 
