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
index: "ncv_detector",
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

///////////////////////// Inner structure (vertical) //////////////////////////////
{
name: "GEO",
index: "inner_structure_verticalrod_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [517.54, -1249.45, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [1249.45, -517.54, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [1249.45, 517.54, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [517.54, 1249.45, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_5",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [-517.54, 1249.45, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_6",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [-517.54, -1249.45, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_7",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [-1249.45, -517.54, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "inner_structure_verticalrod_8",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "cut_tube",
r_max: 38.1, //3" OD SS tube
r_hole: 34.9, //1/8" thickness probably ?
size_z: 1678.0,
position: [-1249.45, 517.54, 436.5],
material: "stainless_steel",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}

///////////////////////// NCV volumes //////////////////////////////
{
name: "GEO",
index: "ncv_vessel",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
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
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_vessel_topcap",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [254.0, 254.0, 12.7], // mm
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1876.4],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_vessel_botcap",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [254.0, 254.0, 12.7], // mm
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1343.0],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_liquid",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 250.25,
size_z: 154.0,
//position: [0.0, 0.0, 0.0],
position: [793.7, 0.0, 1609.7],
material: "ej335",
color: [0.2, 0.1, 0.4, 0.3],
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_pmt_vessel",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 38.7,
size_z: 150.0,
position: [893.7, 0.0, 2039.1],
material: "acrylic_uva_McMaster",
color: [0.1, 0.4, 0.6, 0.3],
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_pmt_vessel_blacksheet",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
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
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_pmt_vessel_air",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_pmt_vessel",
type: "tube",
r_max: 38.2,
size_z: 148.0,
position: [0.0, 0.0, 0.0],
material: "air",
color: [0.2, 0.1, 0.4, 0.3],
drawstyle: "solid"
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 190.13, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -190.13, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -207.83, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_bot4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 207.83, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_top1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 190.13, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_top2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -190.13, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_top3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, -207.83, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_metalplate_top4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [190.0, 2.5, 19.05], // mm
position: [793.7, 207.83, 1908.15],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_basket_ballast1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 19.05,
size_z: 187.63,
position: [603.57, 0.0, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
rotation: [90.0, 0.0, 0.0]
}

{
name: "GEO",
index: "ncv_basket_ballast2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 19.05,
size_z: 187.63,
position: [983.83, 0.0, 1311.25],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
rotation: [90.0, 0.0, 0.0]
}

{
name: "GEO",
index: "ncv_basket_metalplate_topcenter",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "box",
size: [2.5, 187.63, 25.4], // mm
position: [793.7, 0.0, 1914.5],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_bridal_bar1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [981.33, 187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_bridal_bar2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [981.33, -187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_bridal_bar3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [606.07, 187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}

{
name: "GEO",
index: "ncv_bridal_bar4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ncv_detector",
type: "tube",
r_max: 6.35,
size_z: 254.0,
position: [606.07, -187.63, 1609.7],
material: "stainless_steel",
color: [0.1, 0.4, 0.1, 0.8],
drawstyle: "solid",
}


///////////////////////// PMT arrays //////////////////////////////
{ 
name: "GEO", 
index: "inner_pmts", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "ncv_detector", 
type: "pmtarray", 
pmt_model: "r5912",
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
index: "ncv_pmt", 
enable: 1,
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "ncv_pmt_vessel_air", 
type: "pmtarray", 
pmt_model: "b76d01",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.000,  
pos_table: "PMTINFO_run1_ncvpmt", //generated on the fly
// start_idx: 60, //index of first inner pmt
// end_idx: 1, //index of last inner pmt
orientation: "manual",
} 


///////////////////////// "Fake" volume for neutron generation //////////////////////////////

{
name: "GEO",
index: "dirt_box",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [0.5, 150.0, 150.0], // mm
position: [2900.0, 0.0, -2018.8],
material: "air",
color: [1.0, 0.0, 0.0, 0.1],
drawstyle: "solid"
}