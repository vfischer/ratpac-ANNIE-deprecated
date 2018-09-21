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

/////////////////////////////////////////////////////////////////////
///////////********** End of tank volumes ***********////////////////
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
sensitive_detector: "/mydet/pmt/inner_pmt", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_run2_topgrid", //generated on the fly
start_idx: 0, //index of first inner pmt
end_idx: 21, //index of last inner pmt
orientation: "manual",
} 

// Side ring 7
// { 
// name: "GEO", 
// index: "side_ring_7_lappd", 
// enable: 1,
// valid_begin: [0, 0], 
// valid_end: [0, 0], 
// mother: "detector", 
// type: "lappdarray", 
// lappd_model: "lappd_test", 
// lappd_detector_type: "idlappd",
// sensitive_detector: "/mydet/pmt/inner_lappd", 
// efficiency_correction: 1.000,  
// pos_table: "LAPPDINFO_test", //generated on the fly
// start_idx: 0, //index of first inner pmt
// end_idx: 8, //index of last inner pmt
// orientation: "point",
// orient_point: [0.0, 0.0, 1375.4],
// // orient_point: [0.0, 0.0, -133.3],  
// } 

/////////////////////////////////////////////////////////////////////
///////////********** End of PMT arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////
