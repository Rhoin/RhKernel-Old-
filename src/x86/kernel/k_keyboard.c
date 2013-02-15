/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>

uint8_t gScanCode;
rhkbool isNumLckEnabled, isScrLckEnabled, isCapsLckEnabled;
uint32_t gPressedKeys,gReleasedKeys;
uint8_t gCurCode;
uint8_t gLastKey;
rhkbool isFirstTime = TRUE;

uint8_t scancodes[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', 0,	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i','o', 'p', '[', ']', 0,	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

uint8_t kcode_array[] = 
{ 	
	'1','2','3','4','5','6','7','8','9',' ',
	'a','b','c','d','e','f','g','h','i','j','k','l',
	'm','n','o','p','r','s','t','u','v','w','x','y','z',
	',','.','\'','\"','\\','/',':',';','+','-','*','!','?','=',
	'#','%','&','_','(',')','[',']','{','}','$','£','$','<','>',
	'|','`','~','@','^','\b','\r','\t'
};

uint32_t kcode_scancode[] =
{
	KEY_UNKNOWN,
	KEY_ESCAPE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_LEFTBRACKET,
	KEY_RIGHTBRACKET,
	KEY_RETURN,
	KEY_LCTRL,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_QUOTE,
	KEY_GRAVE,
	KEY_LSHIFT,
	KEY_BACKSLASH,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_COMMA,
	KEY_DOT,
	KEY_SLASH,
	KEY_RSHIFT,
	KEY_KP_ASTERISK,
	KEY_RALT,
	KEY_SPACE,
	KEY_CAPSLOCK,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_NUMLOCK,
	KEY_SCRLOCK,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_MINUS,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_PLUS,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_0,
	KEY_KP_DECIMAL,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_F11,
	KEY_F12,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	/*//For released ones
	KEY_UNKNOWN,
	KEY_ESCAPE, //93
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_LEFTBRACKET,
	KEY_RIGHTBRACKET,
	KEY_RETURN,
	KEY_LCTRL,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_QUOTE,
	KEY_GRAVE,
	KEY_LSHIFT,
	KEY_BACKSLASH,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_COMMA,
	KEY_DOT,
	KEY_SLASH,
	KEY_RSHIFT,
	KEY_KP_ASTERISK,
	KEY_RALT,
	KEY_SPACE,
	KEY_CAPSLOCK,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_NUMLOCK,
	KEY_SCRLOCK,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_MINUS,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_PLUS,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_0,
	KEY_KP_DECIMAL,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_F11,
	KEY_F12,
	KEY_UNKNOWN,
	KEY_UNKNOWN,
	KEY_UNKNOWN*/
};
void PushPressedKey(uint16_t key);
void PopPressedKey(uint16_t key);
void PushReleasedKey(uint16_t key);
void PopReleasedKey(uint16_t key);

void keyboard_handle(regs_t r)
{
	//uint16_t buff;
	uint8_t code = KYBRD_GETBUFFER();

	if(code <= 81)
	{
		gCurCode = code;
		gLastKey = code;
	}
	else
	{
		gCurCode = 0;
		gLastKey = 0;
	}		
	/*if((code > 0x80) || (code < 0xD9))
	{
		buff = kcode_scancode[KYBRD_GETBUFFER() - 26];
		switch(buff)
		{
			/*case KEY_KP_DEMICAL:
			if(isNumLckEnabled)
			{
				
			}*//*
			default:
			PushReleasedKey(buff);
			break;
		}
	}
	else if((code >= 0x1) || (code < 0x58) )
	{
		buff = kcode_scancode[KYBRD_GETBUFFER()];
		
		switch(buff)
		{
			default:
			PushPressedKey(buff);
			break;
		}
	}*/
}

rhkbool keyboard_init()
{
	irq_install_handler(1, keyboard_handle);
	
	if(!selfTest())
	{
		printStatusMessage("Loading Keyboard...",STATUS_FAILED);
		printf("Keyboard self test is failed!");
		return FALSE;
	}
		
	isNumLckEnabled = TRUE;
	isScrLckEnabled = FALSE;
	isCapsLckEnabled = FALSE;
	KYBRD_SETLEDS(isScrLckEnabled, isNumLckEnabled, isCapsLckEnabled);
	
	
	printStatusMessage("Loading Keyboard...",STATUS_DONE);
	return TRUE;
}

void keyboard_sendcmd_controller(uint8_t cmd)
{
	while(1)
	{
		if((KYBRD_GETSTATUS() & KYBRD_CTRL_STATS_IN_BUF) == 0)
		{
			break;
		}
	}
	outportb(KYBRD_CTRL_PRT,cmd);
}

void keyboard_sendcmd_encoder(uint8_t cmd)
{
	while(1)
	{
		if((KYBRD_GETSTATUS() & KYBRD_CTRL_STATS_IN_BUF) == 0)
		{
			break;
		}
	}
	outportb(KYBRD_ENCODER_PRT,cmd);
}

uint8_t keyboard_read_status()
{
	return inportb(KYBRD_CTRL_PRT);
}

uint8_t keyboard_read_buffer()
{
	return inportb(KYBRD_ENCODER_PRT);
}

void keyboard_enable()
{
	KYBRD_ENCMD(KYBRD_EN_CMD_ENABLE_KYBRD);
}

void keyboard_disable()
{
	KYBRD_ENCMD(KYBRD_EN_CMD_DISABLE_KYBRD);
}

void keyboard_set_leds(rhkbool scrlck, rhkbool numlck, rhkbool capslck)
{
	uint8_t leds;
	
	leds = (scrlck) ? (leds | 0x1) : (leds & 0x6);
	leds = (numlck) ? (leds | 0x2) : (leds & 0x5);
	leds = (capslck) ? (leds | 0x4) : (leds & 0x3);
	
	KYBRD_ENCMD(KYBRD_EN_CMD_SETLEDS);
	KYBRD_ENCMD(leds);
}

rhkbool selfTest()
{
	KYBRD_CTRLCMD(0xAA);
	
	while(1)
	{
		if((KYBRD_GETSTATUS() & KYBRD_CTRL_STATS_OUT_BUF) == 0)
		{
			break;
		}
	}
	
	rhkbool passed;
	
	
	passed = (KYBRD_GETBUFFER() == 0x55)? TRUE : FALSE;
	return passed;
}

uint8_t getch()
{
	uint8_t code = kcode_scancode[gCurCode];
	gCurCode = 0;
	return code;
}

void PushPressedKey(uint16_t key)
{
	gPressedKeys |= key;
	PopReleasedKey(key);
}
void PopPressedKey(uint16_t key)
{
	gPressedKeys &= ~key;
}

void PushReleasedKey(uint16_t key)
{
	gReleasedKeys |= key;
	PopPressedKey(key);
}
void PopReleasedKey(uint16_t key)
{
	gReleasedKeys &= ~key;
}

uint8_t getLastPressedKeyAscii()
{
	uint8_t code = scancodes[gLastKey];
	gLastKey = NULL;
	return code;
}


