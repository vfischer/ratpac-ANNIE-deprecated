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

{
name: "GEO",
index: "detector_virtual",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "sphere",
r_max: 1500.0,
position: [0.0, 0.0, -133.3],
material: "water",
color: [0.4, 0.4, 0.6, 0.3],
drawstyle: "solid"
}
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
type: "tube",
r_max: 38.1, //3" OD SS tube
r_min: 34.9, //1/8" thickness probably ?
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
///////////////********** NCV volumes ***********////////////////////
/////////////////////////////////////////////////////////////////////
{
name: "GEO",
index: "ncv_vessel",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
size_z: 254.0,
r_max: 254.0,
r_min: 250.25,
// low_norm: [0.0, 0.0, -1.0],
// high_norm: [0.0, 0.0, 1.0],
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1609.7],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_vessel_topcap",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [254.0, 254.0, 12.7], // mm
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1876.4],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_vessel_botcap",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [254.0, 254.0, 12.7], // mm
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1343.0],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_liquid",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 250.25,
size_z: 254.0,
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1609.7],
material: "ej335",
color: [0.2, 0.1, 0.4, 0.3],
drawstyle: "solid", 
enable: 1,
}

// First NCV PMT
{
name: "GEO",
index: "ncv_pmt_vessel_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 38.7,
size_z: 150.0,
position: [893.7, 0.0, 2039.1],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_pmt_vessel_blacksheet_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
size_z: 150.0,
r_max: 38.71, // 10 microns thick (about right)
r_min: 38.7,
// low_norm: [0.0, 0.0, -1.0],
// high_norm: [0.0, 0.0, 1.0],
//position: [0.0, 0.0, 0.0],
position: [893.7, 0.0, 2039.1],
material: "acrylic_black", //not true but black 
color: [1.0, 0.2, 0.6, 1.0],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_pmt_vessel_air_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_pmt_vessel_1",
type: "tube",
r_max: 38.2,
size_z: 148.0,
position: [0.0, 0.0, 0.0],
material: "air",
color: [0.2, 0.1, 0.4, 0.3],
drawstyle: "solid", 
enable: 1,
}

// Second NCV PMT
{
name: "GEO",
index: "ncv_pmt_vessel_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 38.7,
size_z: 150.0,
position: [693.7, 0.0, 2039.1],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_pmt_vessel_blacksheet_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
size_z: 150.0,
r_max: 38.71, // 10 microns thick (about right)
r_min: 38.7,
// low_norm: [0.0, 0.0, -1.0],
// high_norm: [0.0, 0.0, 1.0],
//position: [0.0, 0.0, 0.0],
position: [693.7, 0.0, 2039.1],
material: "acrylic_black", //not true but black 
color: [1.0, 0.2, 0.6, 1.0],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_pmt_vessel_air_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_pmt_vessel_2",
type: "tube",
r_max: 38.2,
size_z: 148.0,
position: [0.0, 0.0, 0.0],
material: "air",
color: [0.2, 0.1, 0.4, 0.3],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 190.13, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -190.13, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -207.83, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 207.83, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_top1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 190.13, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid", 
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_top2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -190.13, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_top3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -207.83, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_top4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 207.83, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_ballast1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 19.05,
size_z: 187.63,
position: [603.57, 0.0, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
rotation: [90.0, 0.0, 0.0]
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_ballast2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 19.05,
size_z: 187.63,
position: [983.83, 0.0, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
rotation: [90.0, 0.0, 0.0]
enable: 1,
}

{
name: "GEO",
index: "ncv_basket_metalplate_topcenter",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "box",
size: [2.5, 187.63, 25.4], // mm
position: [793.7, 0.0, 1914.5],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_bridal_bar1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [981.33, 187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_bridal_bar2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [981.33, -187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_bridal_bar3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [606.07, 187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}

{
name: "GEO",
index: "ncv_bridal_bar4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [606.07, -187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
enable: 1,
}
/////////////////////////////////////////////////////////////////////
////////////********** End of NCV volumes ***********////////////////
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
///////////////********** NCV factory ***********/////////////////////
/////////////////////////////////////////////////////////////////////
{
name: "GEO",
index: "NCV",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_virtual",
enable_ncv: 1,
// ncv_center: [793.7, 0.0, 1609.7], // top upstream position (May 2016 to 06-02-2017) (in dd-mm-yyyy system)
//ncv_center: [1117.55, 0.0, -562.0], // bottom upstream position (06-02-2017 to 27-02-2017)
// ncv_center: [-146.1, 0.0, 1597.18], // position 1 (top center) (27-02-2017 to 14-04-2017) 
// ncv_center: [-146.1, 0.0, 276.38], // position 2 (center center) (14-04-2017 to 24-05-2017)
ncv_center: [0.0, 0.0, 0.0], // position 2 (center center) (14-04-2017 to 24-05-2017)
//  ncv_center: [793.7, 0.0, 276.38], // position 3 (center upstream) (24-05-2017 to 08-06-2017)
// ncv_center: [-146.1, 0.0, 1292.33], // position 4 (top center minus 1 foot) (08-06-2017 to 23-06-2017)
// ncv_center: [-146.1, 0.0, 987.53], // position 5 (top center minus 2 feet) (23-06-2017 to 30-06-2017)
// ncv_center: [-146.1, 0.0, 1444.78], // position 6 (top center minus 1/2 feet) (30-06-2017 to 03-07-2017)
// ncv_center: [311.1, 0.0, 276.38], // position 7 (between 2 and 3) (03-07-2017 to 19-07-2017)
// ncv_center: [311.1, 0.0, 1597.18], // position 8 (height of 1, horizontal same as 7) (19-07-2017 to ??)
type: "annieNCV", //see the geo factory
}
/////////////////////////////////////////////////////////////////////
/////////********** End of NCV factory ***********/////////////
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

{ 
name: "GEO", 
index: "ncv_pmt_1",
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "ncv_pmt_vessel_air_1", 
type: "pmtarray", 
pmt_model: "b76d01",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_run1_ncvpmt_1", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 1, //index of last inner pmt
orientation: "manual",
enable: 1,
} 

{ 
name: "GEO", 
index: "ncv_pmt_2",
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "ncv_pmt_vessel_air_2", 
type: "pmtarray", 
pmt_model: "b76d01",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_run1_ncvpmt_2", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 1, //index of last inner pmt
orientation: "manual",
enable: 1,
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