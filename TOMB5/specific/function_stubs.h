#pragma once
#include "../global/vars.h"

void inject_funcStubs(bool replace);

void* game_malloc(int size, int type);

#define Log	( (void(__cdecl*)(ulong, const char*, ...)) 0x004DEB10 )
