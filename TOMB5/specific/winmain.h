#pragma once
#include "../global/vars.h"

void inject_winmain(bool replace);

void ClearSurfaces();

#define RestoreFPCW	( (void(__cdecl*)(short)) 0x004D3150 )
#define MungeFPCW	( (long(__cdecl*)(short*)) 0x004D30E0 )
