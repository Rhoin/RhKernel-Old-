/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>

uint16_t *g_pVidTextMem;
int32_t g_crsx, g_crsy;
UBYTE g_attribute;
int32_t g_Xmax, g_Ymax;
UBYTE g_backColor;
UBYTE g_foreColor;
void vid_init()
{
	rhkbool color = detectColorSupport();
	if(color)
	{
		g_pVidTextMem = VID_COLOR_MEM; //Our video text memory adress
	}
	else
	{
		g_pVidTextMem = VID_MONO_MEM; //Our video text memory adress
	}
	g_Xmax = 80;
	g_Ymax = 25;
	setTextColor(BLACK, WHITE);
	clearScr();
	printf("RhKernel v%i.%i.%i (C) Sefer \"Rhoin\" Ergun",RHK_MAJOR_VER, RHK_MINOR_VER, RHK_REVISION_VER);
	printStatusMessage("Detecting video card color support...",color == TRUE ? STATUS_DONE : STATUS_FAILED);
	if(color)
	{
		//printf("Your video card supports color!",NULL);
	}
	printStatusMessage("Video is setting up...", STATUS_DONE);
}

void setTextColor(UBYTE _backColor, UBYTE _foreColor)
{
	g_backColor = _backColor;
	g_foreColor = _foreColor;
	g_attribute = (_backColor << 4) | (_foreColor & 0x0F);
}

void scroll()
{
	uint16_t blank = 0x20 | (g_attribute << 8);
	
	if(g_crsy >= 25)
	{
		int i;
		for(i = 0;i < 24*80;i++)
		{
			g_pVidTextMem[i] = g_pVidTextMem[i + 80];
		}
		
		for(i = 24*80;i < 25*80;i++)
		{
			g_pVidTextMem[i] = blank;
		}
		g_crsy = 24;
	}
}

void updateCursor()
{
	uint32_t temp = g_crsy * g_Xmax + g_crsx;
	
	outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void putch(uint8_t _ch)
{
	uint16_t att = g_attribute << 8;
	uint16_t *loc;
	
	if( _ch == 0x08 && g_crsx)
	{
		g_crsx--;
	}
	else if( _ch == 0x09)
	{
		g_crsx = ( g_crsx + 8) & ~(8 - 1);
	}
	else if( _ch == '\n')
	{
		g_crsx = 0;
		g_crsy++;
	}
	else if( _ch == '\r')
	{
		g_crsx = 0;
	}
	else if( _ch >= ' ')
	{
		loc = g_pVidTextMem + (g_crsy * g_Xmax + g_crsx);
		*loc = _ch | att;
		g_crsx++;
	}
	
	if(g_crsx == g_Xmax)
	{
		g_crsx = 0;
		g_crsy++;
	}
	
	scroll();
	updateCursor();
}

int32_t getCurX()
{
	return g_crsx;
}

int32_t getCurY()
{
	return g_crsy;
}

int32_t getCurXMax()
{
	return g_Xmax;
}

int32_t getCurYMax()
{
	return g_Ymax;
}

void moveCur(int32_t x, int32_t y)
{
	g_crsx = x;
	g_crsy = y;
	scroll();
	updateCursor();
}

void clearScr()
{
	uint16_t blank = 0x20 | (g_attribute << 8);
	int i;
	for(i = 0; i < 80*25;i++)
	{
		g_pVidTextMem[i] = blank;
	}
}

void printStatusMessage(const char *message, int status)
{
	UBYTE tempForeColor = g_foreColor;
	int32_t curX = g_crsx;
	
	if(g_crsx > 0)
	{
		putch('\n');
	}
	
	if(status == STATUS_DONE)
	{
		setTextColor(g_backColor, STATUS_DONE_COLOR);
		putch('*');
		int32_t cury = g_crsy;
		moveCur(80 - strlen(STATUS_DONE_TEXT), cury);
		puts(STATUS_DONE_TEXT);
		moveCur(1,cury);
		setTextColor(g_backColor, tempForeColor);
		puts(message);
		moveCur(0,cury + 1);
	}
	else if(status == STATUS_FAILED)
	{
		setTextColor(g_backColor, STATUS_FAILED_COLOR);
		putch('*');
		int32_t cury = g_crsy;
		moveCur(80 - strlen(STATUS_FAILED_TEXT), cury);
		puts(STATUS_FAILED_TEXT);
		moveCur(1,cury);
		setTextColor(g_backColor, tempForeColor);
		puts(message);
		moveCur(0,cury + 1);
	}
}

rhkbool detectColorSupport()
{
	char temp = (* (volatile uint16_t*) 0x410) & 0x30;
	if(temp == 0x30)
	{
		return FALSE;
	}
	else if(temp == 0x20 || 0x00)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

UBYTE getBackColor()
{
	return g_backColor;
}

UBYTE getForeColor()
{
	return g_foreColor;
}
