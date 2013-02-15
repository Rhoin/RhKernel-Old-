#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <rhKernel/system.h>

RHAPI void vid_init();
RHAPI void putch(uint8_t _ch);
RHAPI void scroll();
RHAPI void updateCursor();
RHAPI void clearScr();
RHAPI void setTextColor(UBYTE _backColor, UBYTE _foreColor);
RHAPI int32_t getCurX();
RHAPI int32_t getCurY();
RHAPI int32_t getCurXMax();
RHAPI int32_t getCurYMax();
RHAPI UBYTE getBackColor();
RHAPI UBYTE getForeColor();
RHAPI void moveCur(int32_t x, int32_t y);

//It prints status message
//Ex: *status    [DONE/FAILED]
RHAPI void printStatusMessage(const char *message, int status);

//It return true if your video card support colors
RHAPI rhkbool detectColorSupport();

#endif /*_VIDEO_H_*/
