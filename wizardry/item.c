#include "item.h"
ItemData ITEM_MST[101] = {
{0,11,"BROKEN ITEM",11,"BROKEN ITEM",0x06,0x07,0,255,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
{1,5,"SWORD",10,"LONG SWORD",0x00,0x07,0,255,0,0,25,255,255,225,0,0,4,0,{1,8,0},0,0,0,0},
{2,5,"SWORD",11,"SHORT SWORD",0x00,0x07,0,255,0,0,15,255,255,233,0,0,3,0,{1,6,0},0,0,0,0},
{3,5,"STICK",13,"ANOINTED MACE",0x00,0x07,0,255,0,0,30,255,255,245,0,0,2,0,{2,3,0},0,0,0,0},
{4,5,"STICK",14,"ANOINTED FLAIL",0x00,0x07,0,255,0,0,150,255,255,229,0,0,3,0,{1,7,0},0,0,0,0},
{5,5,"STICK",5,"STAFF",0x00,0x07,0,255,0,0,10,255,255,255,0,0,0,0,{1,5,0},0,0,0,0},
{6,6,"DAGGER",6,"DAGGER",0x00,0x07,0,255,0,0,5,255,255,235,0,0,1,0,{1,4,0},0,0,0,0},
{7,6,"SHIELD",12,"SMALL SHIELD",0x02,0x07,0,255,0,0,20,255,255,253,0,-2,0,0,{0,0,0},0,0,0,0},
{8,6,"SHIELD",12,"LARGE SHIELD",0x02,0x07,0,255,0,0,40,255,255,229,0,-3,0,0,{0,0,0},0,0,0,0},
{9,4,"ROBE",5,"ROBES",0x01,0x07,0,255,0,0,15,255,255,255,0,-1,0,0,{0,0,0},0,0,0,0},
{10,5,"ARMOR",13,"LEATHER ARMOR",0x01,0x07,0,255,0,0,50,255,255,253,0,-2,0,0,{0,0,0},0,0,0,0},
{11,5,"ARMOR",10,"CHAIN MAIL",0x01,0x07,0,255,0,0,90,255,255,229,0,-3,0,0,{0,0,0},0,0,0,0},
{12,5,"ARMOR",12,"BREAST PLATE",0x01,0x07,0,255,0,0,200,255,255,229,0,-4,0,0,{0,0,0},0,0,0,0},
{13,5,"ARMOR",10,"PLATE MAIL",0x01,0x07,0,255,0,0,750,255,255,225,0,-5,0,0,{0,0,0},0,0,0,0},
{14,4,"HELM",4,"HELM",0x03,0x07,0,255,0,0,100,255,255,225,0,-1,0,0,{0,0,0},0,0,0,0},
{15,7,"PORTION",9,"PofCURING",0x05,0x07,0,255,255,0,500,255,22,255,0,0,0,0,{0,0,0},0,0,0,0},
{16,7,"PORTION",15,"PofNEUTRALIZING",0x05,0x07,0,255,255,0,300,255,36,255,0,0,0,0,{0,0,0},0,0,0,0},
{17,5,"SWORD",14,"SWORDofSLICING",0x00,0x07,0,255,0,0,10000,0,255,225,0,0,5,2,{1,8,1},0,0,0,0},
{18,5,"SWORD",13,"BLADEofBITING",0x00,0x07,0,255,0,0,15000,2,255,233,0,0,4,2,{1,6,1},0,0,0,0},
{19,5,"STICK",14,"MACEofPOUNDING",0x00,0x07,0,255,0,0,12500,0,255,245,0,0,3,2,{2,4,1},0,0,0,0},
{20,3,"ROD",9,"RODofIRON",0x00,0x07,0,255,64,0,3000,1,1,18,0,0,1,0,{1,6,0},0,0,0,0},
{21,6,"SCROLL",9,"SCofSLEEP",0x05,0x07,0,255,255,0,500,1,2,255,0,0,0,0,{0,0,0},0,0,0,0},
{22,5,"ARMOR",14,"PADDED LEATHER",0x01,0x07,0,255,0,0,1500,255,255,253,0,-3,0,0,{0,0,0},0,0,0,0},
{23,5,"ARMOR",11,"SHINY CHAIN",0x01,0x07,0,255,0,0,1500,255,255,229,0,-4,0,0,{0,0,0},0,0,0,0},
{24,5,"ARMOR",12,"STURDY PLATE",0x01,0x07,0,255,0,0,1500,1,255,225,0,-6,0,0,{0,0,0},0,0,0,0},
{25,6,"SHIELD",11,"IRON SHIELD",0x02,0x07,0,255,0,0,1500,255,255,237,0,-4,0,0,{0,0,0},0,0,0,0},
{26,5,"ARMOR",10,"BODY ARMOR",0x01,0x07,0,255,0,0,1500,255,255,229,0,-5,0,0,{0,0,0},0,0,0,0},
{27,6,"SCROLL",8,"SCofPAIN",0x05,0x07,0,0x00,64,0,500,255,23,255,0,0,0,0,{0,1,0},0,0,0,0},
{28,6,"SCROLL",8,"SCofFIRE",0x05,0x07,0,255,255,0,500,25,0,255,0,0,0,0,{0,0,0},0,0,0,0},
{29,5,"SWORD",14,"SWORDofSWISHES",0x00,0x07,255,255,0,0,1000,0,255,225,0,0,-1,0,{1,8,0},0,0,0,0},
{30,5,"SWORD",12,"EPEEofDISMAY",0x00,0x07,255,255,0,0,1000,2,255,233,0,0,-1,1,{1,6,0},0,0,0,0},
{31,5,"STICK",16,"MACEofMISFORTUNE",0x00,0x07,255,255,0,0,1000,0,255,245,0,0,-1,1,{2,3,0},0,0,0,0},
{32,5,"STICK",12,"STUDLY STAFF",0x00,0x07,0,255,0,0,2500,255,255,255,0,0,2,1,{1,4,2},0,0,0,0},
{33,5,"SWORD",15,"SLAYERofDRAGONS",0x00,0x07,0,255,0,0,10000,0,255,225,0,0,1,1,{1,10,1},0,32768,0,32768},
{34,4,"HELM",15,"HELMofHARDINESS",0x03,0x07,0,255,0,0,3000,0,255,225,0,-2,0,0,{0,0,0},0,0,0,0},
{35,5,"ARMOR",14,"ROTTEN LEATHER",0x01,0x07,255,255,0,0,1500,0,255,125,0,-1,0,0,{0,0,0},0,0,0,0},
{36,5,"ARMOR",14,"CORRODED CHAIN",0x01,0x07,255,255,0,0,1500,0,255,229,0,-2,0,0,{0,0,0},0,0,0,0},
{37,5,"ARMOR",14,"BROKEN B-PLATE",0x01,0x07,255,255,0,0,1500,0,255,229,0,-3,0,0,{0,0,0},0,0,0,0},
{38,6,"SHIELD",13,"SCREWY SHIELD",0x02,0x07,0,255,0,0,1500,0,255,109,0,1,0,0,{0,0,0},0,0,0,0},
{39,4,"RING",12,"RINGofJEWELS",0x06,0x07,0,255,0,0,5000,0,3,255,0,0,0,0,{0,0,0},0,0,0,0},
{40,6,"SCROLL",9,"SCofAGONY",0x05,0x07,0,0x00,255,0,500,0,23,255,0,0,0,0,{0,1,0},0,0,0,0},
{41,7,"PORTION",8,"PofGLASS",0x05,0x07,0,255,255,0,1500,1,5,255,0,0,0,0,{0,0,0},0,0,0,0},
{42,5,"SWORD",15,"SWORDofSLASHING",0x00,0x07,0,255,0,0,4000,0,255,225,0,0,6,3,{1,10,2},0,0,0,0},
{43,5,"SWORD",16,"EPEEofEXCELLENCE",0x00,0x07,0,255,0,0,4000,0,255,233,0,0,5,3,{1,6,2},0,0,0,0},
{44,5,"STICK",11,"MACEofPOWER",0x00,0x07,0,255,0,0,4000,0,255,245,0,0,4,2,{1,8,2},0,0,0,0},
{45,6,"SCROLL",14,"SCofBRIGHTNESS",0x05,0x07,0,255,0,0,2500,0,30,255,0,0,0,0,{0,0,0},0,0,0,0},
{46,6,"SCROLL",12,"SCofDARKNESS",0x05,0x07,0,255,0,0,2500,0,4,255,0,0,0,0,{0,0,0},0,0,0,0},
{47,6,"GLOVES",14,"GLOVESofCOPPER",0x04,0x07,0,255,0,0,6000,255,255,225,0,-1,0,0,{0,0,0},0,0,0,0},
{48,5,"ARMOR",15,"TREATED LEATHER",0x01,0x07,0,255,0,0,6000,0,255,253,0,-4,0,0,{0,0,0},0,0,0,0},
{49,5,"ARMOR",11,"ELVEN CHAIN",0x01,0x07,0,255,0,0,6000,0,255,229,0,-5,0,0,{0,0,0},0,0,0,0},
{50,5,"ARMOR",15,"1ST CLASS PLATE",0x01,0x07,0,255,0,0,6000,0,255,229,0,-7,0,0,{0,0,0},0,0,0,0},
{51,6,"SHIELD",15,"SHIELDofSUPPORT",0x02,0x07,0,255,0,0,7000,0,255,237,0,-5,0,0,{0,0,0},0,0,0,0},
{52,4,"HELM",10,"HELMofEVIL",0x03,0x04,0,255,0,0,8000,0,23,225,0,-3,0,0,{0,0,0},0,0,0,0},
{53,7,"PORTION",10,"PofHEALING",0x05,0x07,0,255,255,0,5000,0,34,255,0,0,0,0,{0,1,0},0,0,0,0},
{54,4,"RING",15,"RINGofSHIELDING",0x06,0x07,0,255,13,0,10000,0,25,255,0,0,0,0,{0,0,0},0,0,0,0},
{55,5,"SWORD",10,"WERESLAYER",0x00,0x07,0,255,0,0,10000,0,255,225,0,0,5,2,{1,10,1},0,2,0,2},
{56,5,"SWORD",13,"MASHERofMAGES",0x00,0x07,0,255,0,0,10000,0,255,233,0,0,5,2,{1,6,1},0,512,0,512},
{57,5,"STICK",12,"MACEofSNAKES",0x00,0x07,0,255,0,0,10000,0,255,245,0,0,3,2,{1,8,0},0,4096,16,0},
{58,3,"ROD",12,"RODofSILENCE",0x00,0x07,0,255,26,5,15000,0,29,255,0,0,1,1,{1,5,1},0,0,0,0},
{59,5,"SWORD",15,"BLADE CUSINART ",0x00,0x07,0,255,0,0,15000,0,255,225,0,0,6,4,{1,3,9},0,0,0,0},
{60,4,"RING",14,"RINGofRIGIDITY",0x06,0x07,0,255,26,0,15000,0,28,4,0,0,0,0,{0,0,0},0,0,0,0},
{61,3,"ROD",10,"RODofFLAME",0x06,0x07,0,255,26,0,25000,0,6,50,0,0,0,0,{0,0,0},0,0,0,0},
{62,5,"ARMOR",11,"CHAINofEVIL",0x01,0x04,0,255,0,0,8000,0,255,229,0,-5,0,0,{0,0,0},0,0,0,0},
{63,5,"ARMOR",13,"NEUTRAL PLATE",0x01,0x02,0,255,0,0,8000,0,255,229,0,-7,0,0,{0,0,0},0,0,0,0},
{64,6,"SHIELD",12,"SHIELDofEVIL",0x02,0x04,0,255,0,0,25000,0,255,237,0,-5,0,0,{0,0,0},0,0,0,0},
{65,4,"RING",16,"RNGofSUFFOCATION",0x06,0x07,0,255,13,0,20000,0,12,255,0,0,0,0,{0,0,0},0,0,0,0},
{66,4,"RING",14,"RINGofMOVEMENT",0x03,0x07,0,0x00,255,14,25000,0,18,255,0,-2,0,0,{0,0,0},0,0,0,0},
{67,6,"SCROLL",14,"SCofAFFLICTION",0x05,0x07,0,255,255,0,8000,0,35,255,0,0,0,0,{0,0,0},0,0,0,0},
{68,5,"SWORD",14,"EPEEofDISASTER",0x00,0x07,255,255,0,0,8000,0,255,233,0,0,1,1,{1,6,0},0,0,0,0},
{69,6,"DAGGER",16,"DAGGERofSLICING ",0x00,0x07,0,255,0,0,8000,0,255,235,0,0,3,2,{1,4,2},0,0,0,0},
{70,5,"STICK",11,"MORBID MACE",0x00,0x07,255,255,0,0,8000,0,255,245,0,0,0,0,{1,8,0},0,0,0,0},
{71,5,"STICK",10,"BENT STAFF",0x00,0x07,255,255,0,0,8000,0,255,255,0,0,-2,1,{1,4,0},0,0,0,0},
{72,6,"DAGGER",13,"DAGGERofSPEED",0x00,0x07,0,255,0,0,30000,0,255,130,0,3,-1,7,{1,4,0},0,0,0,0},
{73,4,"ROBE",12,"ROBEofCURSES",0x01,0x07,255,255,0,0,8000,0,255,255,0,2,-2,0,{0,0,0},0,0,0,0},
{74,5,"ARMOR",13,"LEATHERofLOSS",0x01,0x07,255,255,0,0,8000,0,255,253,0,0,0,0,{0,0,0},0,0,0,0},
{75,5,"ARMOR",13,"CHAINofCURSES",0x01,0x07,255,255,0,0,8000,0,255,229,0,-1,0,0,{0,0,0},0,0,0,0},
{76,5,"ARMOR",15,"B-PLATEofFIENDS",0x01,0x07,255,255,0,0,8000,0,255,229,0,-2,0,0,{0,0,0},0,0,0,0},
{77,6,"SHIELD",15,"SHIELDofNOTHING",0x02,0x07,255,255,0,0,8000,0,255,237,0,0,0,0,{0,0,0},0,0,0,0},
{78,4,"HELM",15,"HELMofHANGOVERS",0x03,0x07,255,255,0,0,50000,0,255,225,0,2,-2,0,{0,0,0},0,0,0,0},
{79,5,"ARMOR",14,"B-PLATEofBOONS",0x01,0x07,0,255,0,0,10000,0,255,229,0,-6,0,0,{0,1,0},0,0,0,0},
{80,6,"GLOVES",14,"GLOVESofSILVER",0x04,0x07,0,255,0,0,60000,0,255,225,0,-3,0,0,{0,0,0},0,0,0,0},
{81,5,"SWORD",11,"SABERofEVIL",0x00,0x04,0,255,0,0,50000,0,255,225,0,0,7,4,{1,10,3},0,0,0,0},
{82,5,"SWORD",14,"SOUL SLAYER   ",0x00,0x04,0,255,0,0,50000,0,255,233,0,0,6,4,{1,6,0},0,0,0,0},
{83,6,"DAGGER",15,"DAGGERofTHIEVES",0x00,0x07,0,0x11,255,0,50000,0,255,136,0,0,5,4,{1,6,0},0,0,0,0},
{84,5,"ARMOR",13,"ARMORofHEROES",0x01,0x07,0,255,0,0,100000,0,255,229,0,-7,0,0,{0,0,0},0,0,0,0},
{85,5,"ARMOR",12,"ARMORofLORDS",0x01,0x07,0,0x17,128,0,1000000,0,255,64,1,-10,0,0,{0,0,0},255,49152,0,3584},
{86,6,"WEAPON",14,"MURAMASA BLADE",0x00,0x07,0,0x01,128,0,1000000,0,255,32,0,0,8,3,{10,5},0,0,0,0},
{87,6,"WEAPON",8,"SHURIKEN",0x00,0x04,0,0x16,128,0,50000,0,255,128,0,0,7,3,{1,5,10},255,0,0,0},
{88,5,"ARMOR",12,"ARMORofFREON",0x01,0x07,0,255,0,0,150000,0,255,229,0,-6,0,0,{0,0,0},0,0,0,0},
{89,5,"ARMOR",11,"ARMORofEVIL",0x01,0x04,0,255,0,0,150000,0,255,229,0,-9,0,0,{0,0,0},0,0,0,0},
{90,6,"SHIELD",15,"SHIELDofDEFENSE",0x02,0x07,0,255,0,0,250000,0,255,237,0,-6,0,0,{0,0,0},0,0,0,0},
{91,4,"RING",13,"RINGofHEALING",0x06,0x07,0,255,0,0,300000,0,255,255,1,0,0,0,{0,0,0},0,0,0,0},
{92,4,"RING",16,"RINGofDISPELLING",0x06,0x07,0,0x00,0,0,500000,0,255,255,0,0,0,0,{0,1,0},0,1024,0,0},
{93,4,"RING",11,"RINGofDEATH",0x06,0x07,255,255,0,0,500000,0,255,255,-3,0,0,0,{0,0,0},0,0,0,0},
{94,6,"AMULET",15,"WERDNA'S AMULET",0x06,0x04,255,0x17,0,0,999999999,0,18,255,5,-10,0,0,{0,0,0},0,8191,126,0},
{95,6,"STATUE",12,"STATUEofBEAR",0x05,0x07,0,0x00,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
{96,6,"STATUE",12,"STATUEofFROG",0x05,0x07,0,0x00,0,0,0,0,255,0,0,-2,0,0,{0,0,0},0,0,0,0},
{97,3,"KEY",11,"KEYofBRONZE",0x05,0x07,0,0x00,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
{98,3,"KEY",11,"KEYofSILVER",0x05,0x07,0,0x00,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
{99,3,"KEY",9,"KEYofGOLD",0x05,0x07,0,0x00,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
{100,6,"RIBBON",11,"BLUE RIBBON",0x05,0x07,0,0x00,0,0,0,0,255,0,0,0,0,0,{0,0,0},0,0,0,0},
};

ItemGroup ITEM_GRP_MST[30] = {
{{},{0},{{}},{20,100},0},
{{},{0},{{}},{40,200},0},
{{},{0},{{}},{60,300},0},
{{},{0},{{}},{100,500},0},
{{},{0},{{}},{120,600},0},
{{},{0},{{}},{100,1000},0},
{{},{0},{{}},{100,2000},0},
{{},{0},{{}},{100,4000},0},
{{},{0},{{}},{100,8000},0},
{{25},{16},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}},{20,100},0},
{{51,25},{16,16},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}},{40,200},0},
{{76,38},{16,16},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}},{60,300},0},
{{102,51},{16,16},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}},{80,400},0},
{{128,76,25},{16,16,18},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32},{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50}},{100,500},0},
{{255,128,51},{16,16,18},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32},{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50}},{120,600},0},
{{179,64,25},{16,18,26},{{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32},{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50},{52,53,54,55,56,57,58,59,60,61,62,63,64,65,67,68,69,70,71,72,73,74,75,76,77,78}},{100,1000},0},
{{255,128,38},{16,18,26},{{17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32},{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50},{52,53,54,55,56,57,58,59,60,61,62,63,64,65,67,68,69,70,71,72,73,74,75,76,77,78}},{100,2000},0},
{{179,64,12},{18,26,14},{{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50},{52,53,54,55,56,57,58,59,60,61,62,63,64,65,67,68,69,70,71,72,73,74,75,76,77,78},{79,80,81,82,83,84,85,86,87,88,89,90,91,92}},{100,4000},0},
{{255,128,25},{18,26,15},{{33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50},{52,53,54,55,56,57,58,59,60,61,62,63,64,65,67,68,69,70,71,72,73,74,75,76,77,78},{78,79,80,81,82,83,84,85,86,87,88,89,90,91,92}},{100,8000},0},
{{255},{1},{{94}},{0,0},0},
{{255,255,255},{1,1,1},{{16},{93},{61}},{0,0},0},
{{153,51},{25,26},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},{26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51}},{400,1200},0},
{{76,76},{25,26},{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},{26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51}},{120,600},0},
};