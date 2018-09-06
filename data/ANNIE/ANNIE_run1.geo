////////////////////////////////////////////////////////
// ANNIE detector geometry for Phase 1 
// 
// 60 PMTs on the grid at the bottom of the tank
// NCV in the top position
// 
// Author: V. Fischer <vfischer@ucdavis.edu>
//
// Revisions:
//  2016-09-13 : Only the tank is present so far (no veto nor MRD)
//  2017-01-26 : NCV is fully parametrized (in a factory) and can be enable/disable and easily moved by user
//  2017-01-27 : Geometry frame changed (beam-like frame), z is beam axis, y is vertical, tank subvolmes are unchanged since they are daughters of the tank 
//               This is an awkward situation since the hall and tank use the new frame but not the rest. And the macros have to use the new frame as well... (RAT is not made for beam exp.)
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
material: "pvc",
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
material: "water",
color: [0.4, 0.4, 0.6, 0.3],
drawstyle: "solid"
}

// {
// name: "GEO",
// index: "detector_virtual",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "sphere",
// r_max: 500.0,
// position: [-146.1, 0.0, 276.38],
// material: "water",
// color: [0.4, 0.4, 0.6, 0.3],
// drawstyle: "solid"
// }
/////////////////////////////////////////////////////////////////////
///////////********** End of tank volumes ***********////////////////
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
///////////********** Tank hatch volumes ***********/////////////////
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
////////********** End of tank hatch volumes ***********/////////////
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
///////////////********** Hefty run ***********//////////////////////
/////////////////////////////////////////////////////////////////////
// {
// name: "GEO",
// index: "ncv_hefty_bottom_reflective_tyvek",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "box",
// size: [254.0, 254.0, 0.1], // mm
// //position: [0.0, 0.0, 0.0],
// position: [793.7, 0.0, 1292.2],
// material: "tyvek",
// color: [0.1, 0.4, 0.6, 0.3],
// drawstyle: "solid"
// enable: 1,
// }
// 
// {
// name: "GEO",
// index: "ncv_hefty_side_reflective_tyvek",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "tube",
// size_z: 254.0,
// r_max: 254.1,
// r_min: 254.0,
// // low_norm: [0.0, 0.0, -1.0],
// // high_norm: [0.0, 0.0, 1.0],
// //position: [0.0, 0.0, 0.0],
// position: [793.7, 0.0, 1609.7],
// material: "tyvek",
// color: [0.1, 0.4, 0.6, 0.3],
// drawstyle: "solid"
// enable: 1,
// }
// 
// {
// name: "GEO",
// index: "ncv_hefty_side_black_bag",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "tube",
// size_z: 448.7,
// r_max: 360.0,
// r_min: 359.9,
// // low_norm: [0.0, 0.0, -1.0],
// // high_norm: [0.0, 0.0, 1.0],
// //position: [0.0, 0.0, 0.0],
// position: [793.7, 0.0, 1609.7],
// material: "acrylic_black",
// color: [0.2, 0.4, 0.6, 0.9],
// drawstyle: "solid"
// enable: 1,
// }

// {
// name: "GEO",
// index: "ncv_hefty_top_black_bag",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "hall", //depends on the NCV location (can be "detector" or "airgap"), there's probably a better way to do this..
// type: "tube",
// size_z: 0.1,
// r_max: 360.0,
// r_min: 0.0,
// //position: [0.0, 0.0, 0.0],
// position: [793.7, 0.0, 1292.2],
// material: "acrylic_black",
// color: [0.2, 0.4, 0.6, 0.9],
// drawstyle: "solid"
// enable: 1,
// }

// {
// name: "GEO",
// index: "ncv_hefty_bottom_black_bag",
// valid_begin: [0, 0],
// valid_end: [0, 0],
// mother: "detector",
// type: "tube",
// size_z: 0.1,
// r_max: 360.0,
// r_min: 0.0,
// //position: [0.0, 0.0, 0.0],
// position: [793.7, 0.0, 1292.2],
// material: "acrylic_black",
// color: [0.2, 0.4, 0.6, 0.9],
// drawstyle: "solid"
// enable: 1,
// }
/////////////////////////////////////////////////////////////////////
/////////********** End of Hefty run volumes ***********/////////////
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
///////////////********** PMT arrays ***********/////////////////////
/////////////////////////////////////////////////////////////////////
{ 
name: "GEO", 
index: "inner_pmts", 
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
 
/////////////////////////////////////////////////////////////////////
///////////********** End of PMT arrays ***********//////////////////
/////////////////////////////////////////////////////////////////////

///////////////////////// "Fake" volume for neutron generation //////////////////////////////

/*{
name: "GEO",
index: "dirt_box",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world",
type: "box",
size: [150.0, 150.0, 150.0], // mm
position: [0.0, 0.0, 0.0,],
material: "air",
color: [1.0, 0.5, 0.9, 0.2],
drawstyle: "solid",
enable: 0,
}*/