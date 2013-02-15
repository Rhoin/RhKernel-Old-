/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 * 
 * Solved backspace bug
 */
#include <rhKernel/cmd.h>
#include <rhKernel/console_cmds.h>
#include <rhKernel/keyboard.h>
cmd_func_t *funcs[128];


void register_cmd(cmd_func_t fnc,int id)
{
	funcs[id] = fnc;
}

cmd_func_t call_cmd(int id)
{
	return funcs[id];
}

void getCmd(char *buff, int n)
{
	setTextColor(getBackColor(),WHITE);
	printf(">");
	setTextColor(getBackColor(),CYAN);
	rhkbool write = TRUE;
	int a = 1;
	int16_t key;
	char c;
	int i;
	for(i = 0; i < n;write = TRUE)
	{
		key = getch();
		
		if(key == KEY_RETURN)
		{
			break;
		}
		else if(key == KEY_BACKSPACE)
		{
			if(i > 0)
			{
				putch('\b');
				putch(' ');
				putch('\b');
				i--;
				write = FALSE;
			}
		}
		
		if(write == TRUE)
		{
			c = getLastPressedKeyAscii();
			if(c != NULL)
			{
				putch(c);
				buff[i++] = c;
			}
		}
	}
	buff[i] = '\0';
	putch('\n');
	setTextColor(getBackColor(),WHITE);
}

rhkbool parseCmd(char *buff)
{
	cmd_func_t fnc;
	if(strcmp(buff,"clear") == NULL)
	{
		fnc = CALL_CMD(CONSOLE_CMD_ID_CLEAR);
		fnc(buff);
	}
	else if(strcmp(buff,"help") == NULL)
	{
		fnc = CALL_CMD(CONSOLE_CMD_ID_HELP);
		fnc(buff);
	}
	else if(strcmp(buff,"version") == NULL)
	{
		fnc = CALL_CMD(CONSOLE_CMD_ID_VERSION);
		fnc(buff);
	}
	else if(strcmp(buff,"exit") == NULL)
	{
		fnc = CALL_CMD(CONSOLE_CMD_ID_EXIT);
		fnc(buff);
	}
	else if(strcmp(buff,"memmap") == NULL)
	{
		 fnc = CALL_CMD(CONSOLE_CMD_ID_MEMMAP);
		fnc(buff);
	}
	else if(buff[0] == 'e' && buff[1] == 'c' && buff[2] == 'h' && buff[3] == 'o')
	{
		fnc = CALL_CMD(CONSOLE_CMD_ID_ECHO);
		fnc(buff);
	}
	else if(strcmp(buff,"reboot") == NULL)
	{
		printf("System is going to reboot!\n");
		reboot();
	}
	else
	{
		printf("Unknown Command %s\n",buff);
	}
	return FALSE;
}
