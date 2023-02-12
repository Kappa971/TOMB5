#pragma once
#include "../global/vars.h"

void inject_input(bool replace);

long Key(long number);
long S_UpdateInput();
long ReadJoystick(long& x, long& y);
void IncreaseScreenSize();
void DecreaseScreenSize();

extern const char* KeyboardButtons[272];
extern const char* GermanKeyboard[272];
extern const char* JoyStickButtons[16];
extern long jLayout[32];
extern long defaultJLayout[32];

extern short layout[2][18];
extern long conflict[18];
extern long input;
extern long dbinput;
extern long inputBusy;
extern long joystick_read;
extern long joystick_read_x;
extern long joystick_read_y;
extern long joystick_read_fire;

#ifdef GENERAL_FIXES
extern short ammo_change_timer;
extern char ammo_change_buf[12];
#endif
