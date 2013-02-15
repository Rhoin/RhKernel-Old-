/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define NULL 				0
#define RHAPI extern
#define RHK_MAJOR_VER 		0
#define RHK_MINOR_VER 		0
#define RHK_REVISION_VER 	4
//------------------------
//Video Specified Globals
//------------------------
#define VID_COLOR_MEM 		0xB8000
#define VID_MONO_MEM 		0xB0000

#define BLACK 				0x0
#define BLUE 				0x1
#define GREEN 				0x2
#define CYAN 				0x3
#define RED 				0x4
#define MAGNETA 			0x5
#define BROWN 				0x6
#define LGREY 				0x7
#define DGREY 				0x8
#define LBLUE 				0x9
#define LGREEN 				0xA
#define LCYAN 				0xB
#define LRED 				0xC
#define LMAGNETA 			0xD
#define LBROWN 				0xE
#define WHITE 				0xF

#define STATUS_DONE 			0xAA
#define STATUS_DONE_COLOR 		GREEN
#define STATUS_DONE_TEXT 		"[DONE]"
#define STATUS_FAILED 			0xAB
#define STATUS_FAILED_COLOR 	RED
#define STATUS_FAILED_TEXT 		"[FAILED]"
//------------------------

#define KERNEL_BASE 		0xC0000000

#endif /*_GLOBALS_H_*/
