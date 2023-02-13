#include "../tomb5/pch.h"
#include "LoadSave.h"
#include "../game/text.h"
#include "../game/gameflow.h"
#include "../game/sound.h"
#include "audio.h"
#include "dxsound.h"
#include "input.h"
#include "function_table.h"
#include "drawroom.h"
#include "polyinsert.h"
#include "winmain.h"
#include "output.h"
#include "dxshell.h"
#include "texture.h"
#include "function_stubs.h"
#include "../game/savegame.h"
#include "gamemain.h"
#include "specificfx.h"
#include "time.h"
#include "file.h"
#include "fmv.h"
#include "../game/newinv2.h"
#include "../game/control.h"
#include "3dmath.h"
#include "../game/lara.h"
#include "../tomb5/troyestuff.h"
#include "../tomb5/tomb5.h"

long sfx_frequencies[3] = { 11025, 22050, 44100 };
long SoundQuality = 1;
long MusicVolume = 40;
long SFXVolume = 80;
long ControlMethod;

MONOSCREEN_STRUCT MonoScreen[5];
char MonoScreenOn;

long loadbar_on;
static float loadbar_steps;
static float loadbar_pos;
static long loadbar_maxpos;
static long SpecialFeaturesNum = -1;
static long NumSpecialFeatures;

static LPDIRECTDRAWSURFACE4 screen_surface;
static SAVEFILE_INFO SaveGames[15];
static char SpecialFeaturesPage[5];

static const char* screen_paths[5] =
{
	"SCREENS\\STORY1.STR",
	"SCREENS\\NXG.STR",
	"SCREENS\\STORY2.STR",
	"SCREENS\\GALLERY.STR",
	"SCREENS\\SCREENS.STR"
};

static GouraudBarColourSet healthBarColourSet =
{
	{ 64, 96, 128, 96, 64 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 128, 192, 255, 192, 128 },
	{ 0, 0, 0, 0, 0 }
};

static GouraudBarColourSet poisonBarColourSet =
{
	{ 64, 96, 128, 96, 64 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 64, 96, 128, 96, 64 },
	{ 0, 0, 0, 0, 0 },
	{ 128, 192, 255, 192, 128 }
};

static GouraudBarColourSet airBarColourSet =
{
	{ 0, 0, 0, 0, 0 },
	{ 113, 146, 113, 93, 74 },
	{ 123, 154, 123, 107, 91 },
	{ 0, 0, 0, 0, 0 },
	{ 113, 146, 113, 93, 74 },
	{ 0, 0, 0, 0, 0 }
};

static GouraudBarColourSet dashBarColourSet =
{
	{ 144, 192, 240, 192, 144 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 144, 192, 240, 192, 144 },
	{ 144, 192, 240, 192, 144 },
	{ 0, 0, 0, 0, 0 }
};

static GouraudBarColourSet loadBarColourSet =
{
	{ 48, 96, 127, 80, 32 },
	{ 0, 0, 0, 0, 0 },
	{ 48, 96, 127, 80, 32 },
	{ 0, 0, 0, 0, 0 },
	{ 48, 96, 127, 80, 32 },
	{ 48, 96, 127, 80, 32 }
};

static GouraudBarColourSet enemyBarColourSet =
{
	{ 128, 192, 255, 192, 128 },
	{ 64, 96, 128, 96, 64 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 123, 154, 123, 107, 91 },
	{ 0, 0, 0, 0, 0 }
};

static void S_DrawGouraudBar(long x, long y, long width, long height, long value, GouraudBarColourSet* colour)
{
	D3DTLVERTEX v[4];
	TEXTURESTRUCT tex;
	float fx, fx2, fy, fy2, fvalue;
	long r, g, b;

	clipflags[0] = 0;
	clipflags[1] = 0;
	clipflags[2] = 0;
	clipflags[3] = 0;
	nPolyType = 4;
	tex.drawtype = 0;
	tex.tpage = 0;
	fx = phd_winxmax * 0.0015625F;
	fy = phd_winymax * 0.0020833334F;
	fvalue = 0.0099999998F * value;
	fx2 = width * fvalue;
	fy2 = height * 0.1666666716F;
	v[0].specular = 0xFF000000;
	v[1].specular = 0xFF000000;
	v[2].specular = 0xFF000000;
	v[3].specular = 0xFF000000;
	v[0].sx = x * fx;
	v[1].sx = x * fx + fx2 * fx;
	v[2].sx = x * fx;
	v[3].sx = x * fx + fx2 * fx;
	v[0].sy = y * fy - fy2 * fy;
	v[1].sy = y * fy - fy2 * fy;
	v[2].sy = y * fy;
	v[3].sy = y * fy;
	v[0].sz = f_mznear;
	v[1].sz = f_mznear;
	v[2].sz = f_mznear;
	v[3].sz = f_mznear;
	v[0].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[1].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[2].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[3].rhw = f_mpersp / f_mznear * f_moneopersp;

	v[0].sy += fy2 * fy;
	v[1].sy += fy2 * fy;
	v[2].sy += fy2 * fy;
	v[3].sy += fy2 * fy;

	v[0].color = 0xFF000000;
	v[1].color = 0xFF000000;

	r = colour->abLeftRed[0];
	g = colour->abLeftGreen[0];
	b = colour->abLeftBlue[0];
	r -= r >> 2;
	g -= g >> 2;
	b -= b >> 2;
	v[2].color = RGBONLY(r, g, b);

	r = (long)((1 - fvalue) * colour->abLeftRed[0] + fvalue * colour->abRightRed[0]);
	g = (long)((1 - fvalue) * colour->abLeftGreen[0] + fvalue * colour->abRightGreen[0]);
	b = (long)((1 - fvalue) * colour->abLeftBlue[0] + fvalue * colour->abRightBlue[0]);
	r -= r >> 2;
	g -= g >> 2;
	b -= b >> 2;
	v[3].color = RGBONLY(r, g, b);

	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);

	for (int i = 0; i < 4; i++)
	{
		v[0].sy += fy2 * fy;
		v[1].sy += fy2 * fy;
		v[2].sy += fy2 * fy;
		v[3].sy += fy2 * fy;
		v[0].color = RGBONLY(colour->abLeftRed[i], colour->abLeftGreen[i], colour->abLeftBlue[i]);
		r = (long)((1 - fvalue) * colour->abLeftRed[i] + fvalue * colour->abRightRed[i]);
		g = (long)((1 - fvalue) * colour->abLeftGreen[i] + fvalue * colour->abRightGreen[i]);
		b = (long)((1 - fvalue) * colour->abLeftBlue[i] + fvalue * colour->abRightBlue[i]);
		v[1].color = RGBONLY(r, g, b);
		v[2].color = RGBONLY(colour->abLeftRed[i + 1], colour->abLeftGreen[i + 1], colour->abLeftBlue[i + 1]);
		r = (long)((1 - fvalue) * colour->abLeftRed[i + 1] + fvalue * colour->abRightRed[i + 1]);
		g = (long)((1 - fvalue) * colour->abLeftGreen[i + 1] + fvalue * colour->abRightGreen[i + 1]);
		b = (long)((1 - fvalue) * colour->abLeftBlue[i + 1] + fvalue * colour->abRightBlue[i + 1]);
		v[3].color = RGBONLY(r, g, b);
		AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);
	}

	v[0].sy += fy2 * fy;
	v[1].sy += fy2 * fy;
	v[2].sy += fy2 * fy;
	v[3].sy += fy2 * fy;

	r = colour->abLeftRed[4];
	g = colour->abLeftGreen[4];
	b = colour->abLeftBlue[4];
	r -= r >> 2;
	g -= g >> 2;
	b -= b >> 2;
	v[0].color = RGBONLY(r, g, b);

	r = (long)((1 - fvalue) * colour->abLeftRed[4] + fvalue * colour->abRightRed[4]);
	g = (long)((1 - fvalue) * colour->abLeftGreen[4] + fvalue * colour->abRightGreen[4]);
	b = (long)((1 - fvalue) * colour->abLeftBlue[4] + fvalue * colour->abRightBlue[4]);
	r -= r >> 2;
	g -= g >> 2;
	b -= b >> 2;
	v[1].color = RGBONLY(r, g, b);

	v[2].color = 0xFF000000;
	v[3].color = 0xFF000000;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);

	v[0].sx = x * fx - 2;
	v[1].sx = x * fx + width * fx + 2;
	v[2].sx = x * fx - 2;
	v[3].sx = x * fx + width * fx + 2;
	v[0].sy = y * fy;
	v[1].sy = y * fy;
	v[2].sy = y * fy + height * fy;
	v[3].sy = y * fy + height * fy;
	v[0].sz = f_mznear + 1;
	v[1].sz = f_mznear + 1;
	v[2].sz = f_mznear + 1;
	v[3].sz = f_mznear + 1;
	v[0].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[1].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[2].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[3].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[0].color = 0;
	v[1].color = 0;
	v[2].color = 0;
	v[3].color = 0;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);	//black background

	v[0].sx = x * fx - 3;
	v[1].sx = x * fx + width * fx + 3;
	v[2].sx = x * fx - 3;
	v[3].sx = x * fx + width * fx + 3;
	v[0].sy = y * fy - 1;
	v[1].sy = y * fy - 1;
	v[2].sy = y * fy + height * fy + 1;
	v[3].sy = y * fy + height * fy + 1;
	v[0].sz = f_mznear + 2;
	v[1].sz = f_mznear + 2;
	v[2].sz = f_mznear + 2;
	v[3].sz = f_mznear + 2;
	v[0].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[1].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[2].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[3].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[0].color = 0xFFFFFFFF;
	v[1].color = 0xFFFFFFFF;
	v[2].color = 0xFFFFFFFF;
	v[3].color = 0xFFFFFFFF;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);	//white border
}

void S_DoTR4Bar(long x, long y, long width, long height, long pos, long clr1, long clr2)
{
	D3DTLVERTEX v[4];
	TEXTURESTRUCT tex;
	static float wat = 0;
	long x2, sx, sy;

	nPolyType = 4;
	wat += 0.0099999998F;

	if (wat > 0.99000001F)
		wat = 0;

	clipflags[0] = 0;
	clipflags[1] = 0;
	clipflags[2] = 0;
	clipflags[3] = 0;

	x2 = (long)(x * phd_winxmax * 0.0015625F);
	sx = (long(width * phd_winxmax * 0.0015625F) * pos) / 100;
	sy = (long)((height >> 1) * phd_winymax * 0.0020833334F);

	v[0].sx = (float)x2;
	v[0].sy = (float)y;
	v[0].color = clr1;

	v[1].sx = (float)(x2 + sx);
	v[1].sy = (float)y;
	v[1].color = clr1;

	v[2].sx = (float)(x2 + sx);
	v[2].sy = (float)(y + sy);
	v[2].color = clr2;

	v[3].sx = (float)x2;
	v[3].sy = (float)(y + sy);
	v[3].color = clr2;

	for (int i = 0; i < 4; i++)
	{
		v[i].specular = 0xFF000000;
		v[i].sz = f_mznear - 6;
		v[i].rhw = f_moneoznear - 2;
		v[i].tu = 0;
		v[i].tv = 0;
	}

	tex.drawtype = 0;
	tex.flag = 0;
	tex.tpage = 0;
	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	v[0].sx = (float)x2;
	v[0].sy = (float)(y + sy);
	v[0].color = clr2;

	v[1].sx = (float)(x2 + sx);
	v[1].sy = (float)(y + sy);
	v[1].color = clr2;

	v[2].sx = (float)(x2 + sx);
	v[2].sy = (float)(y + 2 * sy);
	v[2].color = clr1;

	v[3].sx = (float)x2;
	v[3].sy = (float)(y + 2 * sy);
	v[3].color = clr1;

	for (int i = 0; i < 4; i++)
	{
		v[i].specular = 0xFF000000;
		v[i].sz = f_mznear - 6;
		v[i].rhw = f_moneoznear - 2;
		v[i].tu = 0;
		v[i].tv = 0;
	}

	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	x2 = (long)(x * phd_winxmax * 0.0015625F);
	sx = (long)(width * phd_winxmax * 0.0015625F);
	sy = (long)((height >> 1) * phd_winymax * 0.0020833334F);

	v[0].sx = (float)(x2 - 1);
	v[0].sy = (float)(y - 1);

	v[1].sx = (float)(x2 + sx + 1);
	v[1].sy = (float)(y - 1);

	v[2].sx = (float)(x2 + sx + 1);
	v[2].sy = (float)(y + 2 * sy + 1);

	v[3].sx = (float)(x2 - 1);
	v[3].sy = (float)(y + 2 * sy + 1);

	for (int i = 0; i < 4; i++)
	{
		v[i].color = 0xFFFFFFFF;
		v[i].specular = 0xFF000000;
		v[i].sz = f_mznear - 3;
		v[i].rhw = f_moneoznear - 4;
		v[i].tu = 0;
		v[i].tv = 0;
	}

	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	v[0].sx = (float)x2;
	v[0].sy = (float)y;

	v[1].sx = (float)(x2 + sx);
	v[1].sy = (float)y;

	v[2].sx = (float)(x2 + sx);
	v[2].sy = (float)(y + 2 * sy);

	v[3].sx = (float)x2;
	v[3].sy = (float)(y + 2 * sy);

	for (int i = 0; i < 4; i++)
	{
		v[i].color = 0xFF000000;
		v[i].specular = 0xFF000000;
		v[i].sz = f_mznear - 4;
		v[i].rhw = f_moneoznear - 3;
		v[i].tu = 0;
		v[i].tv = 0;
	}

	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);
}

void CheckKeyConflicts()
{
	short key;

	for (int i = 0; i < 18; i++)
	{
		key = layout[0][i];

		conflict[i] = 0;

		for (int j = 0; j < 18; j++)
		{
			if (key == layout[1][j])
			{
				conflict[i] = 1;
				break;
			}
		}
	}
}

#pragma warning(push)
#pragma warning(disable : 4244)
void DisplayStatsUCunt()
{
	ushort ypos;
	short Days, Hours, Min, Sec;
	char buffer[40];
	long seconds;

	ypos = phd_centery - 4 * font_height;
	PrintString(phd_centerx, ypos, 6, SCRIPT_TEXT(TXT_Statistics), FF_CENTER);
	PrintString(phd_centerx, ypos + 2 * font_height, 2, SCRIPT_TEXT(gfLevelNames[gfCurrentLevel]), FF_CENTER);
	PrintString(phd_centerx >> 2, ypos + 3 * font_height, 2, SCRIPT_TEXT(TXT_Time_Taken), 0);
	PrintString(phd_centerx >> 2, ypos + 4 * font_height, 2, SCRIPT_TEXT(TXT_Distance_Travelled), 0);
	PrintString(phd_centerx >> 2, ypos + 5 * font_height, 2, SCRIPT_TEXT(TXT_Ammo_Used), 0);
	PrintString(phd_centerx >> 2, ypos + 6 * font_height, 2, SCRIPT_TEXT(TXT_Health_Packs_Used), 0);
	PrintString(phd_centerx >> 2, ypos + 7 * font_height, 2, SCRIPT_TEXT(TXT_Secrets_Found), 0);

	seconds = GameTimer / 30;
	Days = seconds / (24 * 60 * 60);
	Hours = (seconds % (24 * 60 * 60)) / (60 * 60);
	Min = (seconds / 60) % 60;
	Sec = (seconds % 60);

	sprintf(buffer, "%02d:%02d:%02d", (Days * 24) + Hours, Min, Sec);
	PrintString(phd_centerx + (phd_centerx >> 2), ypos + 3 * font_height, 6, buffer, 0);
	sprintf(buffer, "%dm", savegame.Game.Distance / 419);
	PrintString(phd_centerx + (phd_centerx >> 2), ypos + 4 * font_height, 6, buffer, 0);
	sprintf(buffer, "%d", savegame.Game.AmmoUsed);
	PrintString(phd_centerx + (phd_centerx >> 2), ypos + 5 * font_height, 6, buffer, 0);
	sprintf(buffer, "%d", savegame.Game.HealthUsed);
	PrintString(phd_centerx + (phd_centerx >> 2), ypos + 6 * font_height, 6, buffer, 0);
	sprintf(buffer, "%d / 36", savegame.Game.Secrets);
	PrintString(phd_centerx + (phd_centerx >> 2), ypos + 7 * font_height, 6, buffer, 0);
}
#pragma warning(pop)

void S_DrawAirBar(long pos)
{
	long x, y;

	if (gfCurrentLevel != LVL5_TITLE)
	{
		if (tomb5.bars_pos == 1)//original
		{
			x = 490 - (font_height >> 2);

			if (tomb5.bar_mode == 2)
				y = (font_height >> 2) + (2 * font_height / 3);
			else
				y = (font_height >> 1) + (font_height >> 2) + 32;
		}
		else if (tomb5.bars_pos == 2)//improved
		{
			x = 490 - (font_height >> 2);
			y = font_height >> 2;
		}
		else//PSX
		{
			x = 470 - (font_height >> 2);

			if (tomb5.bar_mode == 2)
				y = (font_height >> 2) + (2 * font_height / 3);
			else
				y = (font_height >> 1) + (font_height >> 2);
		}

		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(x, y, 150, 12, pos, &airBarColourSet);
		else if (tomb5.bar_mode == 2)
			S_DoTR4Bar(x, y, 150, 12, pos, 0xFF000000, 0xFF0000FF);
		else
			DoBar(x, y, 150, 12, pos, 0x0000A0, 0x0050A0);
	}
}

void S_DrawHealthBar(long pos)
{
	long color;
	long x, y;

	if (gfCurrentLevel != LVL5_TITLE)
	{
		if (lara.poisoned || lara.Gassed)
			color = 0xA0A000;//yellowish poison, rgb 160, 160, 0
		else
			color = 0x00A000;//green, rgb 0, 160, 0

		if (tomb5.bars_pos == 1)//original
		{
			x = font_height >> 2;

			if (tomb5.bar_mode == 2)
				y = font_height >> 2;
			else
				y = (font_height >> 2) + 32;
}
		else if (tomb5.bars_pos == 2)//improved
		{
			x = font_height >> 2;
			y = font_height >> 2;
		}
		else//PSX
		{
			x = 470 - (font_height >> 2);
			y = font_height >> 2;
		}

		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(x, y, 150, 12, pos, lara.poisoned || lara.Gassed ? &poisonBarColourSet : &healthBarColourSet);
		else if (tomb5.bar_mode == 2)
		{
			if (lara.poisoned || lara.Gassed)
				S_DoTR4Bar(x, y, 150, 12, pos, 0xFF000000, 0xFFFFFF00);
			else
				S_DoTR4Bar(x, y, 150, 12, pos, 0xFF000000, 0xFFFF0000);
		}
		else
			DoBar(x, y, 150, 12, pos, 0xA00000, color);
	}
}

void S_DrawHealthBar2(long pos)//same as above just different screen position
{
	long color;

	if (gfCurrentLevel != LVL5_TITLE)
	{
		if (lara.poisoned || lara.Gassed)
			color = 0xA0A000;
		else
			color = 0xA000;

		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(245, (font_height >> 1) + 32, 150, 12, pos, lara.poisoned || lara.Gassed ? &poisonBarColourSet : &healthBarColourSet);
		else if (tomb5.bar_mode == 2)
		{
			if (lara.poisoned || lara.Gassed)
				S_DoTR4Bar(245, font_height + 48, 150, 12, pos, 0xFF000000, 0xFFFFFF00);
			else
				S_DoTR4Bar(245, font_height + 48, 150, 12, pos, 0xFF000000, 0xFFFF0000);
		}
		else
			DoBar(245, (font_height >> 1) + 32, 150, 12, pos, 0xA00000, color);
	}
}

void S_DrawDashBar(long pos)
{
	long x, y;

	if (tomb5.bars_pos == 1)//original
	{
		x = 490 - (font_height >> 2);

		if (tomb5.bar_mode == 2)
			y = font_height >> 2;
		else
			y = (font_height >> 2) + 32;
}
	else if (tomb5.bars_pos == 2)//improved
	{
		x = 490 - (font_height >> 2);

		if (tomb5.bar_mode == 2)
			y = (font_height >> 2) + (2 * font_height / 3);
		else
			y = (font_height >> 1) + (font_height >> 2);
	}
	else//PSX
	{
		x = 470 - (font_height >> 2);

		if (tomb5.bar_mode == 2)
			y = (font_height >> 2) + (2 * font_height / 3) + (2 * font_height / 3);
		else
			y = (font_height >> 2) + (font_height >> 2) + 32;
	}

	if (gfCurrentLevel != LVL5_TITLE)
	{
		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(x, y, 150, 12, pos, &dashBarColourSet);
		else if (tomb5.bar_mode == 2)
			S_DoTR4Bar(x, y, 150, 12, pos, 0xFF000000, 0xFF00FF00);
		else
			DoBar(x, y, 150, 12, pos, 0xA0A000, 0x00A000);
	}
}

void S_DrawEnemyBar(long pos)
{
	long x, y;

	if (tomb5.bars_pos == 1)//original
	{
		x = font_height >> 2;

		if (tomb5.bar_mode == 2)
			y = (font_height >> 2) + (2 * font_height / 3);
		else
			y = (font_height >> 1) + (font_height >> 2) + 32;
	}
	else if (tomb5.bars_pos == 2)//improved
	{
		x = font_height >> 2;

		if (tomb5.bar_mode == 2)
			y = (font_height >> 2) + (2 * font_height / 3);
		else
			y = (font_height >> 1) + (font_height >> 2);
	}
	else//PSX
	{
		x = 470 - (font_height >> 2);

		if (tomb5.bar_mode == 2)
			y = (font_height >> 2) + (2 * font_height / 3) + (2 * font_height / 3) + (2 * font_height / 3);
		else
			y = (font_height >> 1) + (font_height >> 2) + (font_height >> 2) + 32;
	}

	if (tomb5.bar_mode == 3)
		S_DrawGouraudBar(x, y, 150, 12, pos, &enemyBarColourSet);
	else if (tomb5.bar_mode == 2)
		S_DoTR4Bar(x, y, 150, 12, pos, 0xFF000000, 0xFFFFA000);
	else
		DoBar(x, y, 150, 12, pos, 0xA00000, 0xA0A000);
}

#pragma warning(push)
#pragma warning(disable : 4244)
long DoLoadSave(long LoadSave)
{
	SAVEFILE_INFO* pSave;
	static long selection;
	long txt, color, l;
	char string[80];
	char name[41];

	if (LoadSave & IN_SAVE)
		txt = TXT_Save_Game;
	else
		txt = TXT_Load_Game;

	PrintString(phd_centerx, font_height, 6, SCRIPT_TEXT(txt), FF_CENTER);

	for (int i = 0; i < 15; i++)
	{
		pSave = &SaveGames[i];
		color = 2;

		if (i == selection)
			color = 1;

		memset(name, ' ', 40);
		l = strlen(pSave->name);

		if (l > 40)
			l = 40;

		strncpy(name, pSave->name, l);
		name[40] = 0;
		small_font = 1;

		if (pSave->valid)
		{
			wsprintf(string, "%03d", pSave->num);
			PrintString(phd_centerx - long((float)phd_winwidth / 640.0F * 310.0F), font_height + font_height * (i + 2), color, string, 0);
			PrintString(phd_centerx - long((float)phd_winwidth / 640.0F * 270.0F), font_height + font_height * (i + 2), color, name, 0);
			wsprintf(string, "%d %s %02d:%02d:%02d", pSave->days, SCRIPT_TEXT(TXT_days), pSave->hours, pSave->minutes, pSave->seconds);
			PrintString(phd_centerx - long((float)phd_winwidth / 640.0F * -135.0F), font_height + font_height * (i + 2), color, string, 0);
		}
		else
		{
			wsprintf(string, "%s", pSave->name);
			PrintString(phd_centerx, font_height + font_height * (i + 2), color, string, FF_CENTER);
		}

		small_font = 0;
	}

	if (dbinput & IN_FORWARD)
	{
		selection--;
		SoundEffect(SFX_MENU_CHOOSE, 0, SFX_DEFAULT);
	}

	if (dbinput & IN_BACK)
	{
		selection++;
		SoundEffect(SFX_MENU_CHOOSE, 0, SFX_DEFAULT);
	}

	if (selection < 0)
		selection = 0;

	if (selection > 14)
		selection = 14;

	if (dbinput & IN_SELECT)
	{
		if (SaveGames[selection].valid || LoadSave == IN_SAVE)
			return selection;
		else
			SoundEffect(SFX_LARA_NO, 0, SFX_DEFAULT);
	}

	return -1;
}
#pragma warning (pop)

long GetCampaignCheatValue()
{
	static long counter = 0;
	static long timer;
	long jump;

	if (timer)
		timer--;
	else
		counter = 0;

	jump = 0;

	switch (counter)
	{
	case 0:

		if (keymap[DIK_F])
		{
			timer = 450;
			counter = 1;
		}

		break;

	case 1:
		if (keymap[DIK_I])
			counter = 2;

		break;

	case 2:
		if (keymap[DIK_L])
			counter = 3;

		break;

	case 3:
		if (keymap[DIK_T])
			counter = 4;

		break;

	case 4:
		if (keymap[DIK_H])
			counter = 5;

		break;

	case 5:
		if (keymap[DIK_Y])
			counter = 6;

		break;

	case 6:
		if (keymap[DIK_1])
			jump = LVL5_STREETS_OF_ROME;

		if (keymap[DIK_2])
			jump = LVL5_BASE;

		if (keymap[DIK_3])
			jump = LVL5_GALLOWS_TREE;

		if (keymap[DIK_4])
			jump = LVL5_THIRTEENTH_FLOOR;

		if (jump)
		{
			counter = 0;
			timer = 0;
		}

		break;
	}

	return jump;
}

#pragma warning(push)
#pragma warning(disable : 4244)
void DoOptions()
{
	const char** keyboard_buttons;
	static long menu;	//0: options, 1: controls, 100: special features
	static ulong selection = 1;	//selection
	static ulong selection_bak;
	static ulong controls_selection;	//selection for when mapping keys
	static long music_volume_bar_shade = 0xFF3F3F3F;
	static long sfx_volume_bar_shade = 0xFF3F3F3F;
	static long sfx_bak;	//backup sfx volume
	static long sfx_quality_bak;	//backup sfx quality
	static long sfx_breath_db = -1;
	long textY, textY2, special_features_available, joystick, joystick_x, joystick_y, joy1, joy2, joy3;
	const char* text;
	uchar clr, num, num2;
	char quality_buffer[256];
	char quality_text[80];
	static char sfx_backup_flag;	//have we backed sfx stuff up?
	static bool waiting_for_key = 0;

	if (!(sfx_backup_flag & 1))
	{
		sfx_backup_flag |= 1;
		sfx_bak = SFXVolume;
	}

	if (!(sfx_backup_flag & 2))
	{
		sfx_backup_flag |= 2;
		sfx_quality_bak = SoundQuality;
	}

	textY = font_height - 4;

	if (menu == 1)	//controls menu
	{
		if (Gameflow->Language == 2)
			keyboard_buttons = GermanKeyboard;
		else
			keyboard_buttons = KeyboardButtons;

		if (ControlMethod)
			num = 11;
		else
			num = 17;

		PrintString(phd_centerx >> 2, font_height, selection & 1 ? 1 : 2, SCRIPT_TEXT(TXT_Control_Method), 0);
		textY = font_height;
		font_height = (long)((float)phd_winymax * 0.050000001F);
		big_char_height = 10;
		textY2 = font_height + (font_height + (font_height >> 1));

		if (!ControlMethod)
		{
			PrintString(phd_centerx >> 2, ushort(textY2 + 1 * font_height), selection & 2 ? 1 : 2, "\x18", 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 2 * font_height), selection & 4 ? 1 : 2, "\x1A", 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 3 * font_height), selection & 8 ? 1 : 2, "\x19", 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 4 * font_height), selection & 0x10 ? 1 : 2, "\x1B", 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 5 * font_height),  selection & 0x20 ? 1 : 2, SCRIPT_TEXT(TXT_Duck), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 6 * font_height), selection & 0x40 ? 1 : 2, SCRIPT_TEXT(TXT_Dash), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 7 * font_height), selection & 0x80 ? 1 : 2, SCRIPT_TEXT(TXT_Walk), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 8 * font_height), selection & 0x100 ? 1 : 2, SCRIPT_TEXT(TXT_Jump), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 9 * font_height), selection & 0x200 ? 1 : 2, SCRIPT_TEXT(TXT_Action), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 10 * font_height), selection & 0x400 ? 1 : 2, SCRIPT_TEXT(TXT_Draw_Weapon), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 11 * font_height), selection & 0x800 ? 1 : 2, SCRIPT_TEXT(TXT_Use_Flare), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 12 * font_height), selection & 0x1000 ? 1 : 2, SCRIPT_TEXT(TXT_Look), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 13 * font_height), selection & 0x2000 ? 1 : 2, SCRIPT_TEXT(TXT_Roll), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 14 * font_height), selection & 0x4000 ? 1 : 2, SCRIPT_TEXT(TXT_Inventory), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 15 * font_height), selection & 0x8000 ? 1 : 2, SCRIPT_TEXT(TXT_Step_Left), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 16 * font_height), selection & 0x10000 ? 1 : 2, SCRIPT_TEXT(TXT_Step_Right), 0);
			text = (waiting_for_key && (controls_selection & 2)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][0]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + font_height), controls_selection & 2 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 4)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][1]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 2 * font_height), controls_selection & 4 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 8)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][2]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 3 * font_height), (controls_selection & 8) != 0 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x10)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][3]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 4 * font_height), controls_selection & 0x10 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x20)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][4]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 5 * font_height), controls_selection & 0x20 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x40)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][5]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 6 * font_height), controls_selection & 0x40 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x80)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][6]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 7 * font_height), controls_selection & 0x80 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x100)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][7]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 8 * font_height), controls_selection & 0x100 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x200)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][8]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 9 * font_height), controls_selection & 0x200 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x400)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][9]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 10 * font_height), controls_selection & 0x400 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x800)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][10]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 11 * font_height), controls_selection & 0x800 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x1000)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][11]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 12 * font_height), controls_selection & 0x1000 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x2000)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][12]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 13 * font_height), controls_selection & 0x2000 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x4000)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][13]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 14 * font_height), controls_selection & 0x4000 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x8000)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][14]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 15 * font_height), controls_selection & 0x8000 ? 1 : 6, text, 0);
			text = (waiting_for_key && (controls_selection & 0x10000)) ? SCRIPT_TEXT(TXT_Waiting) : keyboard_buttons[layout[1][15]];
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 16 * font_height), controls_selection & 0x10000 ? 1 : 6, text, 0);
		}

		if (ControlMethod == 1)
		{
			PrintString(phd_centerx >> 2, ushort(textY2 + 5 * font_height), selection & 2 ? 1 : 2, SCRIPT_TEXT(TXT_Duck), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 6 * font_height), selection & 4 ? 1 : 2, SCRIPT_TEXT(TXT_Dash), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 7 * font_height), selection & 8 ? 1 : 2, SCRIPT_TEXT(TXT_Walk), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 8 * font_height), selection & 0x10 ? 1 : 2, SCRIPT_TEXT(TXT_Jump), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 9 * font_height), selection & 0x20 ? 1 : 2, SCRIPT_TEXT(TXT_Action), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 10 * font_height), selection & 0x40 ? 1 : 2, SCRIPT_TEXT(TXT_Draw_Weapon), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 11 * font_height), selection & 0x80 ? 1 : 2, SCRIPT_TEXT(TXT_Use_Flare), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 12 * font_height), selection & 0x100 ? 1 : 2, SCRIPT_TEXT(TXT_Look), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 13 * font_height), selection & 0x200 ? 1 : 2, SCRIPT_TEXT(TXT_Roll), 0);
			PrintString(phd_centerx >> 2, ushort(textY2 + 14 * font_height), selection & 0x400 ? 1 : 2, SCRIPT_TEXT(TXT_Inventory), 0);

			for (int i = 0; i < 10; i++)
			{
				sprintf(quality_buffer, "(%s)", keyboard_buttons[layout[1][i + 4]]);
				PrintString((phd_centerx >> 3) + phd_centerx + (phd_centerx >> 1), ushort(textY2 + font_height * (i + 5)), 5, quality_buffer, 0);
			}

			text = (waiting_for_key && (controls_selection & 2)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[0]];
			clr = (waiting_for_key && (selection & 2)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 5 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 4)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[1]];
			clr = (waiting_for_key && (selection & 4)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 6 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 8)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[2]];
			clr = (waiting_for_key && (selection & 8)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 7 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x10)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[3]];
			clr = (waiting_for_key && (selection & 0x10)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 8 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x20)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[4]];
			clr = (waiting_for_key && (selection & 0x20)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 9 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x40)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[5]];
			clr = (waiting_for_key && (selection & 0x40)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 10 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x80)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[6]];
			clr = (waiting_for_key && (selection & 0x80)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 11 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x100)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[7]];
			clr = (waiting_for_key && (selection & 0x100)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 12 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x200)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[8]];
			clr = (waiting_for_key && (selection & 0x200)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 13 * font_height), clr, text, 0);
			text = (waiting_for_key && (controls_selection & 0x400)) ? SCRIPT_TEXT(TXT_Waiting) : JoyStickButtons[jLayout[9]];
			clr = (waiting_for_key && (selection & 0x400)) ? 1 : 6;
			PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY2 + 14 * font_height), clr, text, 0);
		}

		font_height = default_font_height;
		big_char_height = 6;

		if (!ControlMethod)
			PrintString(phd_centerx + (phd_centerx >> 2), (ushort)textY, controls_selection & 1 ? 1 : 6, SCRIPT_TEXT(TXT_Keyboard), 0);
		else if (ControlMethod == 1)
			PrintString(phd_centerx + (phd_centerx >> 2), (ushort)textY, controls_selection & 1 ? 1 : 6, SCRIPT_TEXT(TXT_Joystick), 0);
		else if (ControlMethod == 2)
			PrintString(phd_centerx + (phd_centerx >> 2), (ushort)textY, controls_selection & 1 ? 1 : 6, SCRIPT_TEXT(TXT_Reset), 0);

		if (ControlMethod < 2 && !waiting_for_key)
		{
			if (dbinput & IN_FORWARD)
			{
				SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
				selection >>= 1;
			}

			if (dbinput & IN_BACK)
			{
				SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
				selection <<= 1;
			}
		}

		if (waiting_for_key)
		{
			num2 = 0;

			if (keymap[DIK_ESCAPE])
			{
				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
				controls_selection = 0;
				dbinput = 0;
				waiting_for_key = 0;
				return;
			}

			if (!ControlMethod)
			{
				for (int i = 0; i < 255; i++)
				{
					if (keymap[i] && keyboard_buttons[i])
					{
						if (i != DIK_RETURN && i != DIK_LEFT && i != DIK_RIGHT && i != DIK_UP && i != DIK_DOWN)
						{
							waiting_for_key = 0;

							for (int j = controls_selection >> 2; j; num2++)
								j >>= 1;

							controls_selection = 0;
							layout[1][num2] = i;
						}
					}
				}
			}

			if (ControlMethod == 1)
			{
				joystick = ReadJoystick(joystick_x, joystick_y);

				if (joystick)
				{
					joy1 = selection >> 2;
					joy2 = 0;
					joy3 = 0;

					while (joy1)
					{
						joy1 >>= 1;
						joy2++;
					}

					joy1 = joystick >> 1;

					while (joy1)
					{
						joy1 >>= 1;
						joy3++;
					}

					jLayout[joy2] = joy3;
					waiting_for_key = 0;
				}
			}

			CheckKeyConflicts();
			dbinput = 0;
		}

		if (dbinput & IN_SELECT && selection > 1 && ControlMethod < 2)
		{
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			controls_selection = selection;
			waiting_for_key = 1;
			memset(keymap, 0, sizeof(keymap));
		}

		if (dbinput & IN_SELECT && ControlMethod == 2)
		{
			SoundEffect(SFX_MENU_SELECT, 0, 2);
			memcpy(layout[1], layout, 72);
			ControlMethod = 0;
			memcpy(jLayout, defaultJLayout, 32);
		}

		if (selection & 1)
		{
			if (dbinput & IN_LEFT)
			{
				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
				ControlMethod--;
			}

			if (dbinput & IN_RIGHT)
			{
				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
				ControlMethod++;
			}

			if (ControlMethod > 2)
				ControlMethod = 2;

			if (ControlMethod < 0)
				ControlMethod = 0;

			if (ControlMethod == 1 && !joystick_read)
			{
				if (dbinput & IN_LEFT)
					ControlMethod = 0;

				if (dbinput & IN_RIGHT)
					ControlMethod = 2;
			}
		}

		if (!selection)
			selection = 1;

		if (selection > (ulong)(1 << (num - 1)))
			selection = 1 << (num - 1);

		if (dbinput & IN_DESELECT)
		{
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);

			if (ControlMethod < 2)
				menu = 0;

			dbinput = 0;
			selection = 1;
		}
	}
	else if (menu == 100)	//special features
	{
		PrintString(phd_centerx, ushort(textY + 3 * font_height), 6, SCRIPT_TEXT(TXT_Special_Features), FF_CENTER);

		if (SpecialFeaturesPage[0])
			clr = selection & 1 ? 1 : 2;
		else
			clr = 3;

		PrintString(phd_centerx, ushort(textY + 5 * font_height), clr, SCRIPT_TEXT(TXT_Storyboards_Part_1), FF_CENTER);

		if (SpecialFeaturesPage[1])
			clr = selection & 2 ? 1 : 2;
		else
			clr = 3;

		PrintString(phd_centerx, ushort(textY + 6 * font_height), clr, SCRIPT_TEXT(TXT_Next_Generation_Concept), FF_CENTER);

		if (SpecialFeaturesPage[2])
			clr = selection & 4 ? 1 : 2;
		else
			clr = 3;

		PrintString(phd_centerx, ushort(textY + 7 * font_height), clr, SCRIPT_TEXT(TXT_Storyboards_Part_2), FF_CENTER);

		if (SpecialFeaturesPage[3])
			clr = selection & 8 ? 1 : 2;
		else
			clr = 3;

		PrintString(phd_centerx, ushort(textY + 8 * font_height), clr, "Gallery", FF_CENTER);

		if (NumSpecialFeatures)
		{
			if (dbinput & IN_FORWARD)
			{
				SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
				selection = FindSFCursor(1, selection);
			}

			if (dbinput & IN_BACK)
			{
				SoundEffect(SFX_MENU_CHOOSE, 0, 2);
				selection = FindSFCursor(2, selection);
			}

			if (!selection)
				selection = 1;
			else if (selection > 8)
				selection = 8;

			if (dbinput & IN_SELECT)
			{
				if (selection & 1)
					SpecialFeaturesNum = 0;

				if (selection & 2)
					SpecialFeaturesNum = 1;

				if (selection & 4)
					SpecialFeaturesNum = 2;

				if (selection & 8)
					SpecialFeaturesNum = 3;

				if (selection & 16)
					SpecialFeaturesNum = 4;
			}
		}

		if (dbinput & IN_DESELECT)
		{
			menu = 0;	//go back to main options menu
			selection = selection_bak;	//go back to selection
			dbinput &= ~IN_DESELECT;	//don't deselect twice
		}
	}
	else if (menu == 0)	//main options menu
	{
		textY= 3 * font_height;
		num = 6;
		PrintString(phd_centerx, 3 * font_height, 6, SCRIPT_TEXT(TXT_Options), FF_CENTER);
		PrintString(phd_centerx, ushort(textY + font_height + (font_height >> 1)), selection & 1 ? 1 : 2, SCRIPT_TEXT(TXT_Control_Configuration), FF_CENTER);
		PrintString(phd_centerx >> 2, ushort(textY + 3 * font_height), selection & 2 ? 1 : 2, SCRIPT_TEXT(TXT_Music_Volume), 0);
		PrintString(phd_centerx >> 2, ushort(textY + 4 * font_height), selection & 4 ? 1 : 2, SCRIPT_TEXT(TXT_SFX_Volume), 0);
		PrintString(phd_centerx >> 2, ushort(textY + 5 * font_height), selection & 8 ? 1 : 2, SCRIPT_TEXT(TXT_Sound_Quality), 0);
		PrintString(phd_centerx >> 2, ushort(textY + 6 * font_height), selection & 0x10 ? 1 : 2, SCRIPT_TEXT(TXT_Targeting), 0);
		DoSlider(400, 3 * font_height - (font_height >> 1) + textY + 4, 200, 16, MusicVolume, 0xFF1F1F1F, 0xFF3F3FFF, music_volume_bar_shade);
		DoSlider(400, textY + 4 * font_height + 4 - (font_height >> 1), 200, 16, SFXVolume, 0xFF1F1F1F, 0xFF3F3FFF, sfx_volume_bar_shade);

		switch (SoundQuality)
		{
		case 0:
			strcpy(quality_text, SCRIPT_TEXT(TXT_Low));
			break;

		case 1:
			strcpy(quality_text, SCRIPT_TEXT(TXT_Medium));
			break;

		case 2:
			strcpy(quality_text, SCRIPT_TEXT(TXT_High));
			break;
		}

		PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY + 5 * font_height), selection & 8 ? 1 : 6, quality_text, 0);

		if (App.AutoTarget)
			strcpy(quality_text, SCRIPT_TEXT(TXT_Automatic));
		else
			strcpy(quality_text, SCRIPT_TEXT(TXT_Manual));

		PrintString(phd_centerx + (phd_centerx >> 2), ushort(textY + 6 * font_height), selection & 0x10 ? 1 : 6, quality_text, 0);
		special_features_available = 0x20;	//not the most accurate name

		if (gfGameMode == 1)
		{
			num = 7;
			PrintString(phd_centerx, ushort((font_height >> 1) + textY + 7 * font_height), selection & 0x20 ? 1 : 2, SCRIPT_TEXT(TXT_Special_Features), FF_CENTER);
		}
		else
			special_features_available = 0;

		if (special_features_available)
			PrintString(phd_centerx, ushort((font_height >> 1) + textY + 8 * font_height), selection & 0x40 ? 1 : 2, "tomb5 options", FF_CENTER);
		else
			PrintString(phd_centerx, ushort((font_height >> 1) + textY + 7 * font_height), selection & 0x20 ? 1 : 2, "tomb5 options", FF_CENTER);

		if (dbinput & IN_FORWARD)
		{
			SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
			selection >>= 1;
		}

		if (dbinput & IN_BACK)
		{
			SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
			selection <<= 1;
		}

		if (dbinput & IN_SELECT && selection & 1)
		{
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			menu = 1;
		}

		num2 = !special_features_available ? 0x20 : 0x40;

		if (dbinput & IN_SELECT && selection & num2)
		{
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			selection_bak = selection;
			selection = 1;
			menu = 200;
		}

		if (!selection)
			selection = 1;

		if (selection > (ulong)(1 << (num - 1)))
			selection = 1 << (num - 1);

		music_volume_bar_shade = 0xFF3F3F3F;
		sfx_volume_bar_shade = 0xFF3F3F3F;

		if (selection & 2)
		{
			sfx_bak = SFXVolume;

			if (input & IN_LEFT || keymap[DIK_LEFT])
				MusicVolume--;

			if (input & IN_RIGHT || keymap[DIK_RIGHT])
				MusicVolume++;

			if (MusicVolume > 100)
				MusicVolume = 100;

			if (MusicVolume < 0)
				MusicVolume = 0;

			sfx_volume_bar_shade = 0xFF3F3F3F;
			music_volume_bar_shade = 0xFF7F7F7F;
			ACMSetVolume();
		}
		else if (selection & 4)
		{
			if (input & IN_LEFT || keymap[DIK_LEFT])
				SFXVolume--;

			if (input & IN_RIGHT || keymap[DIK_RIGHT])
				SFXVolume++;

			if (SFXVolume > 100)
				SFXVolume = 100;

			if (SFXVolume < 0)
				SFXVolume = 0;

			if (SFXVolume != sfx_bak)
			{
				if (sfx_breath_db == -1 || !DSIsChannelPlaying(0))
				{
					S_SoundStopAllSamples();
					sfx_bak = SFXVolume;
					sfx_breath_db = SoundEffect(SFX_LARA_BREATH, 0, SFX_DEFAULT);
					DSChangeVolume(0, -100 * (long(100 - SFXVolume) >> 1));
				}
				else if (sfx_breath_db != -1 && DSIsChannelPlaying(0))
					DSChangeVolume(0, -100 * ((100 - SFXVolume) >> 1));
			}

			music_volume_bar_shade = 0xFF3F3F3F;
			sfx_volume_bar_shade = 0xFF7F7F7F;
		}
		else if (selection & 8)
		{
			sfx_bak = SFXVolume;
			
			if (dbinput & IN_LEFT)
				SoundQuality--;

			if (dbinput & IN_RIGHT)
				SoundQuality++;

			if (SoundQuality > 2)
				SoundQuality = 2;

			if (SoundQuality < 0)
				SoundQuality = 0;

			if (SoundQuality != sfx_quality_bak)
			{
				S_SoundStopAllSamples();
				DXChangeOutputFormat(sfx_frequencies[SoundQuality], 0);
				sfx_quality_bak = SoundQuality;
				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			}
		}
		else if (selection & 16)
		{
			if (dbinput & IN_LEFT)
			{
				if (App.AutoTarget)
					App.AutoTarget = 0;

				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			}

			if (dbinput & IN_RIGHT)
			{
				if (!App.AutoTarget)
					App.AutoTarget = 1;

				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
			}

			savegame.AutoTarget = (uchar)App.AutoTarget;
		}
		else if (selection & special_features_available && dbinput & IN_SELECT)
		{
			CalculateNumSpecialFeatures();
			selection_bak = selection;
			selection = 1;
			menu = 100;
		}
	}
	else if (menu == 200)
		TroyeMenu(textY, menu, selection, selection_bak);
}
#pragma warning (pop)

void DoBar(long x, long y, long width, long height, long pos, long clr1, long clr2)
{
	D3DTLVERTEX v[4];
	TEXTURESTRUCT tex;
	float fx, fx2, fy, fw, fh, r1, g1, b1, r2, g2, b2, r, g, b, mul;
	long lr, lg, lb, clr_11, clr_12, clr_21, clr_22;

	clipflags[0] = 0;
	clipflags[1] = 0;
	clipflags[2] = 0;
	clipflags[3] = 0;
	nPolyType = 4;
	tex.drawtype = 0;
	tex.tpage = 0;
	fx = (float)phd_winxmax * 0.0015625F;
	fy = (float)phd_winymax * 0.0020833334F;
	fw = (float)width;
	fh = (float)(height >> 1);
	fx2 = (fw * fx) * 0.0099999998F * (float)pos;
	v[0].specular = 0xFF000000;
	v[1].specular = 0xFF000000;
	v[2].specular = 0xFF000000;
	v[3].specular = 0xFF000000;
	v[0].sx = (float)x * fx;
	v[1].sx = ((float)x * fx) + fx2;
	v[2].sx = (float)x * fx;
	v[3].sx = ((float)x * fx) + fx2;
	v[0].sy = (float)y * fy;
	v[1].sy = (float)y * fy;
	v[2].sy = ((float)y * fy) + (fh * fy);
	v[3].sy = ((float)y * fy) + (fh * fy);
	v[0].sz = f_mznear;
	v[1].sz = f_mznear;
	v[2].sz = f_mznear;
	v[3].sz = f_mznear;
	v[0].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[1].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[2].rhw = f_mpersp / f_mznear * f_moneopersp;
	v[3].rhw = f_mpersp / f_mznear * f_moneopersp;

	r1 = (float)CLRR(clr1);		//get rgbs
	g1 = (float)CLRG(clr1);
	b1 = (float)CLRB(clr1);
	r2 = (float)CLRR(clr2);
	g2 = (float)CLRG(clr2);
	b2 = (float)CLRB(clr2);

	mul = fx2 / (fw * fx);		//mix
	r = r1 + ((r2 - r1) * mul);
	g = g1 + ((g2 - g1) * mul);
	b = b1 + ((b2 - b1) * mul);

	lr = (long)r1;
	lg = (long)g1;
	lb = (long)b1;
	clr_11 = RGBONLY(lr >> 1, lg >> 1, lb >> 1);
	clr_12 = RGBONLY(lr, lg, lb);

	lr = (long)r;
	lg = (long)g;
	lb = (long)b;
	clr_21 = RGBONLY(lr >> 1, lg >> 1, lb >> 1);
	clr_22 = RGBONLY(lr, lg, lb);

	v[0].color = clr_11;
	v[1].color = clr_21;
	v[2].color = clr_12;
	v[3].color = clr_22;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);	//top half

	v[0].color = clr_12;
	v[1].color = clr_22;
	v[2].color = clr_11;
	v[3].color = clr_21;
	v[0].sy = ((float)y * fy) + (fh * fy);
	v[1].sy = ((float)y * fy) + (fh * fy);
	v[2].sy = (fh * fy) + (fh * fy) + ((float)y * fy);
	v[3].sy = (fh * fy) + (fh * fy) + ((float)y * fy);
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);		//bottom half

	v[0].sx = (float)x * fx;
	v[1].sx = (fw * fx) + ((float)x * fx);
	v[2].sx = (float)x * fx;
	v[3].sx = (fw * fx) + ((float)x * fx);
	v[0].sy = (float)y * fy;
	v[1].sy = (float)y * fy;
	v[2].sy = (fh * fy) + (fh * fy) + ((float)y * fy);
	v[3].sy = (fh * fy) + (fh * fy) + ((float)y * fy);
	v[0].sz = f_mznear + 1;
	v[1].sz = f_mznear + 1;
	v[2].sz = f_mznear + 1;
	v[3].sz = f_mznear + 1;
	v[0].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[1].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[2].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[3].rhw = f_mpersp / (f_mznear + 1) * f_moneopersp;
	v[0].color = 0;
	v[1].color = 0;
	v[2].color = 0;
	v[3].color = 0;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);	//black background

	v[0].sx = ((float)x * fx) - 1;
	v[1].sx = (fw * fx) + ((float)x * fx) + 1;
	v[2].sx = ((float)x * fx) - 1;
	v[3].sx = (fw * fx) + ((float)x * fx) + 1;
	v[0].sy = ((float)y * fy) - 1;
	v[1].sy = ((float)y * fy) - 1;
	v[2].sy = (fh * fy) + (fh * fy) + ((float)y * fy) + 1;
	v[3].sy = (fh * fy) + (fh * fy) + ((float)y * fy) + 1;
	v[0].sz = f_mznear + 2;
	v[1].sz = f_mznear + 2;
	v[2].sz = f_mznear + 2;
	v[3].sz = f_mznear + 2;
	v[0].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[1].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[2].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[3].rhw = f_mpersp / (f_mznear + 2) * f_moneopersp;
	v[0].color = 0xFFFFFFFF;
	v[1].color = 0xFFFFFFFF;
	v[2].color = 0xFFFFFFFF;
	v[3].color = 0xFFFFFFFF;
	AddQuadSorted(v, 0, 1, 3, 2, &tex, 1);	//white border
}

void CreateMonoScreen()
{
	MonoScreenOn = 1;
	ConvertSurfaceToTextures(App.dx.lpBackBuffer);
}

void S_InitLoadBar(long max)
{
	loadbar_steps = 0;
	loadbar_maxpos = max;
	loadbar_pos = 0;
	loadbar_on = 1;
}

void S_UpdateLoadBar()
{
	loadbar_steps = 100.0F / loadbar_maxpos + loadbar_steps;
}

long S_DrawLoadBar()
{
	_BeginScene();
	InitBuckets();
	InitialiseSortList();
	App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 0);

	if (tomb5.tr4_loadbar)
	{
		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(20, 480 - (font_height >> 1), 600, 15, (long)loadbar_pos, &loadBarColourSet);
		else if (tomb5.bar_mode == 2)
			S_DoTR4Bar(20, phd_winymax - font_height, 600, 15, (long)loadbar_pos, 0xFF000000, 0xFF9F1F80);
		else
			DoBar(20, 480 - (font_height >> 1), 600, 15, (long)loadbar_pos, 0xFF7F007F, 0xFF007F7F);
	}
	else
	{
		if (tomb5.bar_mode == 3)
			S_DrawGouraudBar(170, 480 - font_height, 300, 10, (long)loadbar_pos, &loadBarColourSet);
		else if (tomb5.bar_mode == 2)
			S_DoTR4Bar(170, phd_winymax- (font_height << 1), 300, 10, (long)loadbar_pos, 0xFF000000, 0xFF9F1F80);
		else
			DoBar(170, 480 - font_height, 300, 10, (long)loadbar_pos, 0xA0, 0xF0);
	}

	SortPolyList(SortCount, SortList);
	DrawSortList();
	S_DumpScreenFrame();

	if (loadbar_pos >= loadbar_steps)
		return loadbar_maxpos <= loadbar_steps;

	loadbar_pos += 2;
	return 0;
}

void S_LoadBar()
{
	S_UpdateLoadBar();
}

void RGBM_Mono(uchar* r, uchar* g, uchar* b)
{
	uchar c;

	if (MonoScreenOn == 2)
		return;

	if (tomb5.inv_bg_mode == 3)
		return;

	c = (*r + *b) >> 1;
	*r = c;
	*g = c;
	*b = c;
}

static void BitMaskGetNumberOfBits(ulong bitMask, ulong* bitDepth, ulong* bitOffset)
{
	long i;

	if (!bitMask)
	{
		*bitOffset = 0;
		*bitDepth = 0;
		return;
	}

	for (i = 0; !(bitMask & 1); i++)
		bitMask >>= 1;

	*bitOffset = i;

	for (i = 0; bitMask != 0; i++)
		bitMask >>= 1;

	*bitDepth = i;
}

static void WinVidGetColorBitMasks(COLOR_BIT_MASKS* bm, LPDDPIXELFORMAT pixelFormat)
{
	bm->dwRBitMask = pixelFormat->dwRBitMask;
	bm->dwGBitMask = pixelFormat->dwGBitMask;
	bm->dwBBitMask = pixelFormat->dwBBitMask;
	bm->dwRGBAlphaBitMask = pixelFormat->dwRGBAlphaBitMask;

	BitMaskGetNumberOfBits(bm->dwRBitMask, &bm->dwRBitDepth, &bm->dwRBitOffset);
	BitMaskGetNumberOfBits(bm->dwGBitMask, &bm->dwGBitDepth, &bm->dwGBitOffset);
	BitMaskGetNumberOfBits(bm->dwBBitMask, &bm->dwBBitDepth, &bm->dwBBitOffset);
	BitMaskGetNumberOfBits(bm->dwRGBAlphaBitMask, &bm->dwRGBAlphaBitDepth, &bm->dwRGBAlphaBitOffset);
}

static void CustomBlt(DDSURFACEDESC2* dst, ulong dstX, ulong dstY, DDSURFACEDESC2* src, LPRECT srcRect)
{
	COLOR_BIT_MASKS srcMask, dstMask;
	uchar* srcLine;
	uchar* dstLine;
	uchar* srcPtr;
	uchar* dstPtr;
	ulong srcX, srcY, width, height, srcBpp, dstBpp, color, high, low, r, g, b;

	srcX = srcRect->left;
	srcY = srcRect->top;
	width = srcRect->right - srcRect->left;
	height = srcRect->bottom - srcRect->top;
	srcBpp = src->ddpfPixelFormat.dwRGBBitCount / 8;
	dstBpp = dst->ddpfPixelFormat.dwRGBBitCount / 8;
	WinVidGetColorBitMasks(&srcMask, &src->ddpfPixelFormat);
	WinVidGetColorBitMasks(&dstMask, &dst->ddpfPixelFormat);
	srcLine = (uchar*)src->lpSurface + srcY * src->lPitch + srcX * srcBpp;
	dstLine = (uchar*)dst->lpSurface + dstY * dst->lPitch + dstX * dstBpp;

	for (ulong j = 0; j < height; j++)
	{
		srcPtr = srcLine;
		dstPtr = dstLine;

		for (ulong i = 0; i < width; i++)
		{
			color = 0;
			memcpy(&color, srcPtr, srcBpp);
			r = ((color & srcMask.dwRBitMask) >> srcMask.dwRBitOffset);
			g = ((color & srcMask.dwGBitMask) >> srcMask.dwGBitOffset);
			b = ((color & srcMask.dwBBitMask) >> srcMask.dwBBitOffset);

			if (srcMask.dwRBitDepth < dstMask.dwRBitDepth)
			{
				high = dstMask.dwRBitDepth - srcMask.dwRBitDepth;
				low = (srcMask.dwRBitDepth > high) ? srcMask.dwRBitDepth - high : 0;
				r = (r << high) | (r >> low);
			}
			else if (srcMask.dwRBitDepth > dstMask.dwRBitDepth)
				r >>= srcMask.dwRBitDepth - dstMask.dwRBitDepth;

			if (srcMask.dwGBitDepth < dstMask.dwGBitDepth)
			{
				high = dstMask.dwGBitDepth - srcMask.dwGBitDepth;
				low = (srcMask.dwGBitDepth > high) ? srcMask.dwGBitDepth - high : 0;
				g = (g << high) | (g >> low);
			}
			else if (srcMask.dwGBitDepth > dstMask.dwGBitDepth)
				g >>= srcMask.dwGBitDepth - dstMask.dwGBitDepth;


			if (srcMask.dwBBitDepth < dstMask.dwBBitDepth)
			{
				high = dstMask.dwBBitDepth - srcMask.dwBBitDepth;
				low = (srcMask.dwBBitDepth > high) ? srcMask.dwBBitDepth - high : 0;
				b = (b << high) | (b >> low);
			}
			else if (srcMask.dwBBitDepth > dstMask.dwBBitDepth)
				b >>= srcMask.dwBBitDepth - dstMask.dwBBitDepth;

			RGBM_Mono((uchar*)&r, (uchar*)&g, (uchar*)&b);
			color = dst->ddpfPixelFormat.dwRGBAlphaBitMask; // destination is opaque
			color |= r << dstMask.dwRBitOffset;
			color |= g << dstMask.dwGBitOffset;
			color |= b << dstMask.dwBBitOffset;
			memcpy(dstPtr, &color, dstBpp);
			srcPtr += srcBpp;
			dstPtr += dstBpp;
		}

		srcLine += src->lPitch;
		dstLine += dst->lPitch;
	}
}

void ConvertSurfaceToTextures(LPDIRECTDRAWSURFACE4 surface)
{
	DDSURFACEDESC2 tSurf;
	DDSURFACEDESC2 uSurf;
	RECT r;
	ushort* pTexture;
	ushort* pSrc;

	memset(&tSurf, 0, sizeof(tSurf));
	tSurf.dwSize = sizeof(DDSURFACEDESC2);
	surface->Lock(0, &tSurf, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, 0);
	pSrc = (ushort*)tSurf.lpSurface;
	MonoScreen[0].surface = CreateTexturePage(tSurf.dwWidth, tSurf.dwHeight, 0, NULL, RGBM_Mono, -1);

	memset(&uSurf, 0, sizeof(uSurf));
	uSurf.dwSize = sizeof(DDSURFACEDESC2);
	MonoScreen[0].surface->Lock(0, &uSurf, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, 0);
	pTexture = (ushort*)uSurf.lpSurface;

	r.left = 0;
	r.top = 0;
	r.right = tSurf.dwWidth;
	r.bottom = tSurf.dwHeight;
	CustomBlt(&uSurf, 0, 0, &tSurf, &r);

	MonoScreen[0].surface->Unlock(0);
	DXAttempt(MonoScreen[0].surface->QueryInterface(IID_IDirect3DTexture2, (void**)&MonoScreen[0].tex));
	surface->Unlock(0);
}

void FreeMonoScreen()
{
	if (MonoScreenOn == 1)
	{
		if (MonoScreen[0].surface)
		{
			Log(4, "Released %s @ %x - RefCnt = %d", "Mono Screen Surface", MonoScreen[0].surface, MonoScreen[0].surface->Release());
			MonoScreen[0].surface = 0;
		}
		else
			Log(1, "%s Attempt To Release NULL Ptr", "Mono Screen Surface");

		if (MonoScreen[0].tex)
		{
			Log(4, "Released %s @ %x - RefCnt = %d", "Mono Screen Texture", MonoScreen[0].tex, MonoScreen[0].tex->Release());
			MonoScreen[0].tex = 0;
		}
		else
			Log(1, "%s Attempt To Release NULL Ptr", "Mono Screen Texture");
	}

	MonoScreenOn = 0;
}

void S_DrawTile(long x, long y, long w, long h, IDirect3DTexture2* t, long tU, long tV, long tW, long tH, long c0, long c1, long c2, long c3)
{
	D3DTLBUMPVERTEX v[4];
	D3DTLBUMPVERTEX tri[3];
	float u1, v1, u2, v2;

	u1 = float(tU * (1.0F / 256.0F));
	v1 = float(tV * (1.0F / 256.0F));
	u2 = float((tW + tU) * (1.0F / 256.0F));
	v2 = float((tH + tV) * (1.0F / 256.0F));

	v[0].sx = (float)x;
	v[0].sy = (float)y;
	v[0].sz = 0.995F;
	v[0].tu = u1;
	v[0].tv = v1;
	v[0].rhw = 1;
	v[0].color = c0;
	v[0].specular = 0xFF000000;

	v[1].sx = float(w + x);
	v[1].sy = (float)y;
	v[1].sz = 0.995F;
	v[1].tu = u2;
	v[1].tv = v1;
	v[1].rhw = 1;
	v[1].color = c1;
	v[1].specular = 0xFF000000;

	v[2].sx = float(w + x);
	v[2].sy = float(h + y);
	v[2].sz = 0.995F;
	v[2].tu = u2;
	v[2].tv = v2;
	v[2].rhw = 1;
	v[2].color = c3;
	v[2].specular = 0xFF000000;

	v[3].sx = (float)x;
	v[3].sy = float(h + y);
	v[3].sz = 0.995F;
	v[3].tu = u1;
	v[3].tv = v2;
	v[3].rhw = 1;
	v[3].color = c2;
	v[3].specular = 0xFF000000;

	App.dx.lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
	App.dx.lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_POINT);
	App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, 0);
	DXAttempt(App.dx.lpD3DDevice->SetTexture(0, t));
	tri[0] = v[0];
	tri[1] = v[2];
	tri[2] = v[3];
	App.dx.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, v, 3, D3DDP_DONOTCLIP | D3DDP_DONOTUPDATEEXTENTS);
	App.dx.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, tri, 3, D3DDP_DONOTCLIP | D3DDP_DONOTUPDATEEXTENTS);
	App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, 1);

	if (App.Filtering)
	{
		App.dx.lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		App.dx.lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_LINEAR);
	}
}

void S_DisplayMonoScreen()
{
	long x[4];
	long y[4];
	ulong col;

	if (MonoScreenOn == 1 || MonoScreenOn == 2)
	{
		x[0] = phd_winxmin;
		y[0] = phd_winymin;
		x[1] = phd_winxmin + phd_winwidth;
		y[1] = phd_winymin + phd_winheight;

		if (MonoScreenOn == 2)	//pictures always the same!!
			col = 0xFFFFFFFF;
		else
		{
			if (tomb5.inv_bg_mode == 2 || tomb5.inv_bg_mode == 3)
				col = 0xFFFFFFFF;
			else
				col = 0xFFFFFF80;
		}

		S_DrawTile(x[0], y[0], x[1] - x[0], y[1] - y[0], MonoScreen[0].tex, 0, 0, 256, 256, col, col, col, col);
	}
}

long S_LoadSave(long load_or_save, long mono, long inv_active)
{
	long fade, ret;

	fade = 0;

	if (!mono)
		CreateMonoScreen();

	GetSaveLoadFiles();

	if (!inv_active)
		InventoryActive = 1;

	while (1)
	{
		S_InitialisePolyList();

		if (fade)
			dbinput = 0;
		else
			S_UpdateInput();

		SetDebounce = 1;
		S_DisplayMonoScreen();
		ret = DoLoadSave(load_or_save);
		UpdatePulseColour();
		S_OutputPolyList();
		S_DumpScreen();

		if (ret >= 0)
		{
			if (load_or_save & IN_SAVE)
			{
				sgSaveGame();
				S_SaveGame(ret);
				GetSaveLoadFiles();
				break;
			}

			fade = ret + 1;
			S_LoadGame(ret);
			SetFade(0, 255);
			ret = -1;
		}

		if (fade && DoFade == 2)
		{
			ret = fade - 1;
			break;
		}

		if (input & IN_OPTION)
		{
			ret = -1;
			break;
		}

		if (MainThread.ended)
			break;
	}

	TIME_Init();

	if (!mono)
		FreeMonoScreen();

	if (!inv_active)
		InventoryActive = 0;

	return ret;
}

void LoadScreen(long screen, long pathNum)
{
	FILE* file;
	DDPIXELFORMAT pixel_format;
	DDSURFACEDESC2 surf;
	void* pic;
	ushort* pSrc;
	ushort* pDst;
	ushort col, r, g, b;

	memset(&surf, 0, sizeof(surf));
	memset(&pixel_format, 0, sizeof(pixel_format));
	surf.dwSize = sizeof(DDSURFACEDESC2);
	surf.dwWidth = 640;
	surf.dwHeight = 480;
	pixel_format.dwSize = sizeof(DDPIXELFORMAT);
	pixel_format.dwFlags = DDPF_RGB;
	pixel_format.dwRGBBitCount = 16;
	pixel_format.dwRBitMask = 0xF800;
	pixel_format.dwGBitMask = 0x7E0;
	pixel_format.dwBBitMask = 0x1F;
	pixel_format.dwRGBAlphaBitMask = 0;
	memcpy(&surf.ddpfPixelFormat, &pixel_format, sizeof(surf.ddpfPixelFormat));
	surf.dwFlags = DDSD_PIXELFORMAT | DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
	surf.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	file = FileOpen(screen_paths[pathNum]);

	if (DXCreateSurface(G_dxptr->lpDD, &surf, &screen_surface) && file)
	{
		pic = malloc(0x96000);
		fseek(file, 0x96000 * screen, SEEK_SET);
		fread(pic, 0x96000, 1, file);
		fclose(file);
		memset(&surf, 0, sizeof(surf));
		surf.dwSize = sizeof(DDSURFACEDESC2);
		screen_surface->Lock(0, &surf, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, 0);
		pDst = (ushort*)surf.lpSurface;
		pSrc = (ushort*)pic;
		
		for (int i = 0; i < 0x4B000; i++, pSrc++, pDst++)
		{
			col = *pSrc;
			r = (col >> 10) & 0x1F;
			g = (col >> 5) & 0x1F;
			b = col & 0x1F;
			*pDst = (r << 11) | (g << 6) | b;
		}

		screen_surface->Unlock(0);
		free(pic);
		MonoScreenOn = 2;
		ConvertSurfaceToTextures(screen_surface);
	}
	else
		Log(0, "WHORE!");
}

void ReleaseScreen()
{
	MonoScreenOn = 0;

	if (screen_surface)
	{
		Log(4, "Released %s @ %x - RefCnt = %d", "Picture Surface", screen_surface, screen_surface->Release());
		screen_surface = 0;
	}
	else
		Log(1, "%s Attempt To Release NULL Ptr", "Picture Surface");

	FreeMonoScreen();
}

void DrawLoadingScreen()
{
	S_DisplayMonoScreen();
}

long GetSaveLoadFiles()
{
	FILE* file;
	SAVEFILE_INFO* pSave;
	SAVEGAME_INFO save_info;
	static long nSaves;
	char name[75];

	SaveCounter = 0;

	for (int i = 0; i < 15; i++)
	{
		pSave = &SaveGames[i];
		wsprintf(name, "savegame.%d", i);
		file = fopen(name, "rb");
		Log(0, "Attempting to open %s", name);

		if (!file)
		{
			pSave->valid = 0;
			strcpy(pSave->name, SCRIPT_TEXT(TXT_Empty_Slot));
			continue;
		}

		Log(0, "Opened OK");
		fread(&pSave->name, sizeof(char), 75, file);
		fread(&pSave->num, sizeof(long), 1, file);
		fread(&pSave->days, sizeof(short), 1, file);
		fread(&pSave->hours, sizeof(short), 1, file);
		fread(&pSave->minutes, sizeof(short), 1, file);
		fread(&pSave->seconds, sizeof(short), 1, file);
		fread(&save_info, 1, sizeof(SAVEGAME_INFO), file);
		fclose(file);

		if (pSave->num > SaveCounter)
			SaveCounter = pSave->num;

		pSave->valid = 1;
		nSaves++;
		Log(0, "Validated savegame");
	}

	SaveCounter++;
	return nSaves;
}

void DoSlider(long x, long y, long width, long height, long pos, long c1, long c2, long c3)
{
	D3DTLVERTEX v[4];
	TEXTURESTRUCT tex;
	float x2, sx, sy;
	static float V;

	nPolyType = 4;
	V += 0.0099999998F;

	if (V > 0.99000001F)
		V = 0;

	clipflags[0] = 0;
	clipflags[1] = 0;
	clipflags[2] = 0;
	clipflags[3] = 0;
	x2 = (float)phd_winxmax / 640.0F;
	sx = width * x2;
	sy = ((float)phd_winymax / 480.0F) * (height >> 1);
	x2 *= x;

	v[0].sx = x2;
	v[0].sy = (float)y;
	v[0].sz = f_mznear;
	v[0].rhw = f_moneoznear - 2.0F;
	v[0].color = c1;
	v[0].specular = 0xFF000000;

	v[1].sx = sx + x2;
	v[1].sy = (float)y;
	v[1].sz = f_mznear;
	v[1].rhw = f_moneoznear - 2.0F;
	v[1].color = c1;
	v[1].specular = 0xFF000000;

	v[2].sx = sx + x2;
	v[2].sy = (float)y + sy;
	v[2].sz = f_mznear;
	v[2].rhw = f_moneoznear - 2.0F;
	v[2].color = c2;
	v[2].specular = 0xFF000000;

	v[3].sx = x2;
	v[3].sy = (float)y + sy;
	v[3].sz = f_mznear;
	v[3].rhw = f_moneoznear - 2.0F;
	v[3].color = c2;
	v[3].specular = 0xFF000000;

	tex.tpage = ushort(nTextures - 1);
	tex.drawtype = 0;
	tex.flag = 0;
	tex.u1 = 0;
	tex.v1 = V;
	tex.u2 = 1;
	tex.v2 = V;
	tex.u3 = 1;
	tex.v3 = V + 0.0099999998F;
	tex.u4 = 0;
	tex.v4 = V + 0.0099999998F;
	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	v[0].sx = x2;
	v[0].sy = (float)y + sy;
	v[0].sz = f_mznear;
	v[0].rhw = f_moneoznear - 2.0F;
	v[0].color = c2;
	v[0].specular = 0xFF000000;

	v[1].sx = sx + x2;
	v[1].sy = (float)y + sy;
	v[1].sz = f_mznear;
	v[1].rhw = f_moneoznear - 2.0F;
	v[1].color = c2;
	v[1].specular = 0xFF000000;


	v[2].sx = sx + x2;
	v[2].sy = (float)y + 2 * sy;
	v[2].sz = f_mznear;
	v[2].rhw = f_moneoznear - 2.0F;
	v[2].color = c1;
	v[2].specular = 0xFF000000;

	v[3].sx = x2;
	v[3].sy = (float)y + 2 * sy;
	v[3].sz = f_moneoznear - 2.0F;
	v[3].rhw = v[0].rhw;
	v[3].color = c1;
	v[3].specular = 0xFF000000;
	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	v[0].sx = x2 - 1;
	v[0].sy = float(y - 1);
	v[0].sz = f_mznear + 2.0F;
	v[0].rhw = f_moneoznear - 3.0F;
	v[0].color = 0xFFFFFFFF;
	v[0].specular = 0xFF000000;

	v[1].sx = sx + x2 + 1;
	v[1].sy = float(y - 1);
	v[1].sz = f_mznear + 2.0F;
	v[1].rhw = f_moneoznear - 3.0F;
	v[1].color = 0xFFFFFFFF;
	v[1].specular = 0xFF000000;

	v[2].sx = sx + x2 + 1;
	v[2].sy = ((float)y + 2 * sy) + 1;
	v[2].sz = f_mznear + 2.0F;
	v[2].rhw = f_moneoznear - 3.0F;
	v[2].color = 0xFFFFFFFF;
	v[2].specular = 0xFF000000;

	v[3].sx = x2 - 1;
	v[3].sy = ((float)y + 2 * sy) + 1;
	v[3].sz = f_mznear + 2.0F;
	v[3].rhw = f_moneoznear - 3.0F;
	v[3].color = 0xFFFFFFFF;
	v[3].specular = 0xFF000000;
	tex.tpage = 0;
	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);

	sx = pos * sx / 100 + x2;

	v[0].sx = x2;
	v[0].sy = (float)y;
	v[0].sz = f_mznear - 1.0F;
	v[0].rhw = f_moneoznear - 1.0F;
	v[0].color = c3;
	v[0].specular = 0xFF000000;

	v[1].sx = sx + 1;
	v[1].sy = (float)y;
	v[1].sz = f_mznear - 1.0F;
	v[1].rhw = f_moneoznear - 1.0F;
	v[1].color = c3;
	v[1].specular = 0xFF000000;

	v[2].sx = sx;
	v[2].sy = (float)y + 2 * sy;
	v[2].sz = f_mznear - 1.0F;
	v[2].rhw = f_moneoznear - 1.0F;
	v[2].color = c3;
	v[2].specular = 0xFF000000;

	v[3].sx = x2 - 1;
	v[3].sy = (float)y + 2 * sy;
	v[3].sz = f_mznear - 1.0F;
	v[3].rhw = f_moneoznear - 1.0F;
	v[3].color = c3;
	v[3].specular = 0xFF000000;

	tex.tpage = 0;
	tex.drawtype = 2;
	AddQuadSorted(v, 0, 1, 2, 3, &tex, 0);
}

#pragma warning(push)
#pragma warning(disable : 4244)
long S_DisplayPauseMenu(long reset)
{
	static long menu, selection = 1;
	long y;

	if (!menu)
	{
		if (reset)
		{
			selection = reset;
			menu = 0;
		}
		else
		{
			y = phd_centery - font_height;
			PrintString(phd_centerx, y - ((3 * font_height) >> 1), 6, SCRIPT_TEXT(TXT_Paused), FF_CENTER);
			PrintString(phd_centerx, y, selection & 1 ? 1 : 2, SCRIPT_TEXT(TXT_Statistics), FF_CENTER);
			PrintString(phd_centerx, y + font_height, selection & 2 ? 1 : 2, SCRIPT_TEXT(TXT_Options), FF_CENTER);
			PrintString(phd_centerx, y + 2 * font_height, selection & 4 ? 1 : 2, SCRIPT_TEXT(TXT_Exit_to_Title), FF_CENTER);

			if (dbinput & IN_FORWARD)
			{
				if (selection > 1)
					selection >>= 1;

				SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
			}

			if (dbinput & IN_BACK)
			{
				if (selection < 4)
					selection <<= 1;

				SoundEffect(SFX_MENU_CHOOSE, 0, SFX_ALWAYS);
			}

			if (dbinput & IN_DESELECT)
			{
				SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
				return 1;
			}

			if (dbinput & IN_SELECT && !keymap[DIK_LALT])
			{
				SoundEffect(SFX_MENU_SELECT, 0, SFX_DEFAULT);

				if (selection & 1)
					menu = 2;
				else if (selection & 2)
					menu = 1;
				else if (selection & 4)
					return 8;
			}
		}
	}
	else if (menu == 1)
	{
		DoOptions();

		if (dbinput & IN_DESELECT)
		{
			menu = 0;
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
		}
	}
	else if (menu == 2)
	{
		DisplayStatsUCunt();

		if (dbinput & IN_DESELECT)
		{
			menu = 0;
			SoundEffect(SFX_MENU_SELECT, 0, SFX_ALWAYS);
		}
	}

	return 0;
}
#pragma warning (pop)

long S_PauseMenu()
{
	long fade, ret;

	fade = 0;
	CreateMonoScreen();
	S_DisplayPauseMenu(1);
	InventoryActive = 1;

	do
	{
		S_InitialisePolyList();

		if (fade)
			dbinput = 0;
		else
			S_UpdateInput();

		SetDebounce = 1;
		S_DisplayMonoScreen();
		ret = S_DisplayPauseMenu(0);
		UpdatePulseColour();
		S_OutputPolyList();
		S_DumpScreen();

		if (ret == 1)
			break;

		if (ret == 8)
		{
			fade = 8;
			ret = 0;
			SetFade(0, 255);
		}

		if (fade && DoFade == 2)
		{
			ret = fade;
			break;
		}

	} while (!MainThread.ended);

	TIME_Init();
	FreeMonoScreen();
	InventoryActive = 0;
	return ret;
}

void DoFrontEndOneShotStuff()
{
	static long done;

	if (!done)
	{
		PlayFmvNow(0, 0);
		PlayFmvNow(1, 0);
		done = 1;
	}
}

long FindSFCursor(long in, long selection)
{
	long num, bak;

	num = 0;

	while (selection != 1)
	{
		selection >>= 1;
		num++;
	}

	bak = num;

	if (in & IN_FORWARD && num)
		do num--; while (num && !SpecialFeaturesPage[num]);

	if (in & IN_BACK && num < 4)
		do num++; while (num < 4 && !SpecialFeaturesPage[num]);

	if (!SpecialFeaturesPage[num])
		num = bak;

	return 1 << num;
}

void CalculateNumSpecialFeatures()
{
	SpecialFeaturesPage[0] = 0;
	SpecialFeaturesPage[1] = 0;
	SpecialFeaturesPage[2] = 0;
	SpecialFeaturesPage[3] = 0;
	SpecialFeaturesPage[4] = 0;
	NumSpecialFeatures = 0;

	for (int i = 0; i < 4; i++)
	{
		if (savegame.CampaignSecrets[i] >= 9)
		{
			SpecialFeaturesPage[i] = 1;
			NumSpecialFeatures++;
		}
	}
}

#pragma warning(push)
#pragma warning(disable : 4244)
void SpecialFeaturesDisplayScreens(long num)
{
	static long start[4] = { 0, 0, 0, 0 };
	static long nPics[4] = { 12, 15, 12, 23 };
	long first, max, pos, count;

	first = start[num];
	max = nPics[num];
	pos = 0;
	count = 0;
	LoadScreen(first, num);

	while (!MainThread.ended && !(dbinput & IN_DESELECT))
	{
		_BeginScene();
		InitBuckets();
		InitialiseSortList();
		S_UpdateInput();
		SetDebounce = 1;

		if (count < 2)
		{
			count++;
			DrawLoadingScreen();
		}
		else if (count == 2)
		{
			count = 3;
			ReleaseScreen();
		}

		if (!pos)
			PrintString(font_height, phd_winymax - font_height, 6, "Next \x1B", 0);
		else if (pos < max)
			PrintString(font_height, phd_winymax - font_height, 6, "\x19 Previous / Next \x1b", 0);
		else
			PrintString(font_height, phd_winymax - font_height, 6, "\x19 Previous", 0);

		UpdatePulseColour();
		S_OutputPolyList();
		S_DumpScreen();

		if (dbinput & IN_LEFT && pos)
		{
			pos--;
			LoadScreen(pos + first, num);
			count = 0;
		}
		if (dbinput & IN_RIGHT && pos < max)
		{
			pos++;
			LoadScreen(pos + first, num);
			count = 0;
		}
	}

	dbinput &= ~IN_DESELECT;
	ReleaseScreen();
}
#pragma warning (pop)

void DoSpecialFeaturesServer()
{
	switch (SpecialFeaturesNum)
	{
	case 0:
		SpecialFeaturesDisplayScreens(0);
		break;

	case 1:
		SpecialFeaturesDisplayScreens(1);
		break;

	case 2:
		SpecialFeaturesDisplayScreens(2);
		break;

	case 3:
		SpecialFeaturesDisplayScreens(3);
		break;
	}

	SpecialFeaturesNum = -1;
}
