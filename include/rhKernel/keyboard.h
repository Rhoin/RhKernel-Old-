/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include <rhKernel/system.h>

typedef enum
{
	KEY_1 	= 	0x1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_SPACE,
	
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	
	KEY_COMMA,
	KEY_DOT,
	KEY_QUOTE,
	KEY_QUOTEDOUBLE,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_COLON,
	KEY_SEMICOLON,
	KEY_PLUS,
	KEY_MINUS,
	KEY_ASTERISK,
	KEY_EXCLAMATION,
	KEY_QUESTION,
	KEY_EQUAL,
	KEY_HASH,
	KEY_PERCENT,
	KEY_AMPERSAND,
	KEY_UNDERSCORE,
	KEY_LEFTPARENTHESIS,
	KEY_RIGHTPARENTHESIS,
	KEY_LEFTBRACKET,
	KEY_RIGHTBRACKET,
	KEY_LEFTCURL,
	KEY_RIGHTCURL,
	KEY_DOLLAR,
	KEY_POUND,
	KEY_EURO,
	KEY_LESS,
	KEY_GREATER,
	KEY_BAR,
	KEY_GRAVE,
	KEY_TILDE,
	KEY_AT,
	KEY_CARRET,
	
	KEY_BACKSPACE,
	KEY_RETURN,
	KEY_TAB,
	
	
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
	KEY_F11,
	KEY_F12,
	
	KEY_LALT,
	KEY_RALT,
	KEY_LCTRL,
	KEY_RCTRL,
	KEY_LSHIFT,
	KEY_RSHIFT,
	
	KEY_ESCAPE,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_SCRLOCK,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,
	KEY_HOME,
	KEY_DELETE,
	
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_0,
	KEY_KP_DOT,
	KEY_KP_PLUS,
	KEY_KP_ASTERISK,
	KEY_KP_ENTER,
	KEY_KP_DECIMAL,
	
	KEY_UNKNOWN
	
}KEY_CODES;
#define KYBRD_CTRL_PRT 0x64
#define KYBRD_ENCODER_PRT 0x60

//Encoder Commands
#define KYBRD_EN_CMD_SETLEDS 0xED
#define KYBRD_EN_CMD_ECHO 0xEE
#define KYBRD_EN_CMD_GETSET_SCANCODE 0xF0 //Get/Set current scan code set
#define KYBRD_EN_CMD_GETKYBRD_ID 0xF2 
#define KYBRD_EN_CMD_SETRATE_DELAY 0xF3
#define KYBRD_EN_CMD_DISABLE_KYBRD 0xF4
#define KYBRD_EN_CMD_ENABLE_KYBRD 0xF5
#define KYBRD_EN_CMD_RESET_DEFAULT 0xF6
#define KYBRD_EN_CMD_SETKEYS_AUTOREPEAT 0xF7
#define KYBRD_EN_CMD_SETKEYS_MAKE_RELEASE 0xF8
#define KYBRD_EN_CMD_SETKEYS_MAKE_ONLY 0xF9
#define KYBRD_EN_CMD_SETKEY_RPTRLSMK 0xFA //AutoRepeat/Release/Make
#define KYBRD_EN_CMD_SETKEY_AUTOREPEAT 0xFB
#define KYBRD_EN_CMD_SETKEY_MAKE_RELEASE 0xFC
#define KYBRD_EN_CMD_SETKEY_MAKEONLY 0xFD
#define KYBRD_EN_CMD_RESEND_LASTBYTE 0xFE
#define KYBRD_EN_CMD_SELFTEST 0xFF

//Encoder Return Codes (read from GETBUFFER)
#define KYBRD_EN_BUFFER_ECHO 0xEE
#define KYBRD_EN_BUFFER_ACK 0xFA
#define KYBRD_EN_BUFFER_RESEND 0xFE
#define KYBRD_EN_BUFFER_SELFTEST_PASSED 0xAA
#define KYBRD_EN_BUFFER_SELFTEST_FAILED 0xFC
#define KYBRD_EN_BUFFER_SELFTEST_FAILED2 0xFD

//CTRL status codes
#define KYBRD_CTRL_STATS_OUT_BUF	1
#define KYBRD_CTRL_STATS_IN_BUF	2
#define KYBRD_CTRL_STATS_SYSTEM	4
#define KYBRD_CTRL_STATS_CMD_DATA	8
#define KYBRD_CTRL_STATS_LOCKED	0x10
#define KYBRD_CTRL_STATS_AUX_BUF	0x20
#define KYBRD_CTRL_STATS_TIMEOUT	0x40
#define KYBRD_CTRL_STATS_PARITY	0x80	
	
#define KYBRD_CTRLCMD(x) keyboard_sendcmd_controller(x)
#define KYBRD_ENCMD(x) keyboard_sendcmd_encoder(x)
#define KYBRD_SETLEDS(scrlck, numlck, capslck) keyboard_set_leds(scrlck, numlck, capslck)
#define KYBRD_ENBALE() keyboard_enable()
#define KYBRD_DISABLE() keyboard_disable()
#define KYBRD_GETSTATUS() keyboard_read_status()
#define KYBRD_GETBUFFER() keyboard_read_buffer()

RHAPI rhkbool keyboard_init();
RHAPI void keyboard_enable();
RHAPI void keyboard_disable();
RHAPI void keyboard_sendcmd_encoder(uint8_t cmd);
RHAPI void keyboard_sendcmd_controller(uint8_t cmd);
RHAPI uint8_t keyboard_read_status();
RHAPI uint8_t keyboard_read_buffer();
RHAPI void keyboard_set_leds(rhkbool scrlck, rhkbool numlck, rhkbool capslck);
RHAPI rhkbool selfTest();
RHAPI uint8_t getch();
RHAPI uint8_t getLastPressedKeyAscii();
#endif /*_KEYBOARD_H_*/

