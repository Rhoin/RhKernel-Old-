/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
#ifndef _CONSOLE_CMDS_H_
#define _CONSOLE_CMDS_H_

#include <rhKernel/cmd.h>

#define CONSOLE_CMD_ID_EXIT 		0
#define CONSOLE_CMD_ID_VERSION 		1
#define CONSOLE_CMD_ID_HELP 		2
#define CONSOLE_CMD_ID_CLEAR 		3
#define CONSOLE_CMD_ID_MEMMAP 		4
#define CONSOLE_CMD_ID_ECHO 		5

RHAPI void console_cmd_install_cmds();
#endif /*_CONSOLE_CMDS_H_*/
