#pragma once
#include "../global/vars.h"

void inject_time(bool replace);

long Sync();
void TIME_Reset();
bool TIME_Init();

extern __int64 t_frequency;
