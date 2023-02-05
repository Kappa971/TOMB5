#pragma once
#include "../global/vars.h"


void inject_gameflow(bool replace);

void DoGameflow();
long TitleOptions();
void DoTitle(uchar name, uchar audio);
void do_dels_cutseq_selector();
void DoLevel(uchar name, uchar audio);
void LoadGameflow();

enum gf_languages
{
	LNG_ENGLISH,
	LNG_FRENCH,
	LNG_GERMAN,
	LNG_ITALIAN,
	LNG_SPANISH,
	LNG_US,
	LNG_JAPAN,
	LNG_DUTCH,
	NUM_GF_LANGUAGES
};

enum gf_commands
{
	CMD_FMV = 0x80,
	CMD_LEVEL,
	CMD_TITLE,
	CMD_ENDSEQ,
	CMD_PLAYCUT,
	CMD_CUT1,
	CMD_CUT2,
	CMD_CUT3,
	CMD_CUT4,
	CMD_LAYER1,
	CMD_LAYER2,
	CMD_UVROT,
	CMD_LEGEND,
	CMD_LENSFLARE,
	CMD_MIRROR,
	CMD_FOG,
	CMD_ANIMATINGMIP,
	CMD_RESETHUB,

	CMD_KEY1,
	CMD_KEY2,
	CMD_KEY3,
	CMD_KEY4,
	CMD_KEY5,
	CMD_KEY6,
	CMD_KEY7,
	CMD_KEY8,
	CMD_KEY9,
	CMD_KEY10,
	CMD_KEY11,
	CMD_KEY12,

	CMD_PUZZLE1,
	CMD_PUZZLE2,
	CMD_PUZZLE3,
	CMD_PUZZLE4,
	CMD_PUZZLE5,
	CMD_PUZZLE6,
	CMD_PUZZLE7,
	CMD_PUZZLE8,
	CMD_PUZZLE9,
	CMD_PUZZLE10,
	CMD_PUZZLE11,
	CMD_PUZZLE12,

	CMD_PICKUP1,
	CMD_PICKUP2,
	CMD_PICKUP3,
	CMD_PICKUP4,

	CMD_EXAMINE1,
	CMD_EXAMINE2,
	CMD_EXAMINE3,

	CMD_KEYCOMBO1_1,
	CMD_KEYCOMBO1_2,
	CMD_KEYCOMBO2_1,
	CMD_KEYCOMBO2_2,
	CMD_KEYCOMBO3_1,
	CMD_KEYCOMBO3_2,
	CMD_KEYCOMBO4_1,
	CMD_KEYCOMBO4_2,
	CMD_KEYCOMBO5_1,
	CMD_KEYCOMBO5_2,
	CMD_KEYCOMBO6_1,
	CMD_KEYCOMBO6_2,
	CMD_KEYCOMBO7_1,
	CMD_KEYCOMBO7_2,
	CMD_KEYCOMBO8_1,
	CMD_KEYCOMBO8_2,

	CMD_PUZZLECOMBO1_1,
	CMD_PUZZLECOMBO1_2,
	CMD_PUZZLECOMBO2_1,
	CMD_PUZZLECOMBO2_2,
	CMD_PUZZLECOMBO3_1,
	CMD_PUZZLECOMBO3_2,
	CMD_PUZZLECOMBO4_1,
	CMD_PUZZLECOMBO4_2,
	CMD_PUZZLECOMBO5_1,
	CMD_PUZZLECOMBO5_2,
	CMD_PUZZLECOMBO6_1,
	CMD_PUZZLECOMBO6_2,
	CMD_PUZZLECOMBO7_1,
	CMD_PUZZLECOMBO7_2,
	CMD_PUZZLECOMBO8_1,
	CMD_PUZZLECOMBO8_2,

	CMD_PICKUPCOMBO1_1,
	CMD_PICKUPCOMBO1_2,
	CMD_PICKUPCOMBO2_1,
	CMD_PICKUPCOMBO2_2,
	CMD_PICKUPCOMBO3_1,
	CMD_PICKUPCOMBO3_2,
	CMD_PICKUPCOMBO4_1,
	CMD_PICKUPCOMBO4_2,

	CMD_GIVEOBJ,
	CMD_TAKEOBJ,
};

enum gf_level_options
{
	GF_YOUNGLARA = (1 << 0),
	GF_WEATHER = (1 << 1),
	GF_HORIZON = (1 << 2),
	GF_LAYER1 = (1 << 3),
	GF_LAYER2 = (1 << 4),
	GF_STARFIELD = (1 << 5),
	GF_LIGHTNING = (1 << 6),
	GF_OFFICE = (1 << 7),
	GF_PULSE = (1 << 8),
	GF_HORIZONCOLADD = (1 << 9),
	GF_RESETHUB = (1 << 10),
	GF_LENSFLARE = (1 << 11),
	GF_TIMER = (1 << 12),
	GF_MIRROR = (1 << 13),
	GF_REMOVEAMULET = (1 << 14),
	GF_NOLEVEL = (1 << 15)
};

enum gf_tr5_levels
{
	LVL5_TITLE,
	LVL5_STREETS_OF_ROME,
	LVL5_TRAJAN_MARKETS,
	LVL5_COLOSSEUM,
	LVL5_BASE,
	LVL5_SUBMARINE,
	LVL5_DEEPSEA_DIVE,
	LVL5_SINKING_SUBMARINE,
	LVL5_GALLOWS_TREE,
	LVL5_LABYRINTH,
	LVL5_OLD_MILL,
	LVL5_THIRTEENTH_FLOOR,
	LVL5_ESCAPE_WITH_THE_IRIS,
	LVL5_SECURITY_BREACH,
	LVL5_RED_ALERT,
	LVL5_GIBBY_LEVEL,
	LVL5_DEL_LEVEL,
	LVL5_TOM_LEVEL,

	NUM_TR5_LEVELS
};

enum gf_tr5_strings
{
	STR_SEVERAL_HOURS_LATER,
	STR_GIBBYS_LEVEL,
	STR_DELS_LEVEL,
	STR_TOMS_LEVEL,
	STR_THE_13TH_FLOOR,
	STR_ESCAPE_WITH_THE_IRIS,
	STR_SECURITY_BREACH,
	STR_RED_ALERT,
	STR_THE_BASE,
	STR_THE_SUBMARINE,
	STR_DEEPSEA_DIVE,
	STR_SINKING_SUBMARINE,
	STR_STREETS_OF_ROME,
	STR_TRAJANS_MARKETS,
	STR_THE_COLOSSEUM,
	STR_GALLOWS_TREE,
	STR_LABYRINTH,
	STR_OLD_MILL,
	STR_SELECT_CUTSCENE,
	STR_JOBY_CRANE_CUT,
	STR_RICH_CUT_2,
	STR_JOBY_CUT_2,
	STR_RICH_CUT_1,
	STR_RICH_CUT_3,
	STR_JOBY_CUT_3,
	STR_ANDY1,
	STR_RICH1,
	STR_ANDY2,
	STR_JOBY4,
	STR_ANDREA1,
	STR_ANDREA2,
	STR_JOBY5,
	STR_ANDY3,
	STR_JOBY9,
	STR_JOBY10,
	STR_RICHCUT4,
	STR_ANDY4,
	STR_ANDY4B,
	STR_ANDREA3,
	STR_ANDREA3B,
	STR_ANDY5,
	STR_JOBY6,
	STR_JOBY8,
	STR_ANDY6,
	STR_ANDYPEW,
	STR_ANDY7,
	STR_COSSACK,
	STR_ANDY9,
	STR_ANDY8,
	STR_ANDY10,
	STR_JOBY7,
	STR_ANDREA4,
	STR_MONK2,
	STR_SWAMPY,
	STR_ANDY11,
	STR_ENTER_COMBINATION,
	STR_UNLIMITED,
	STR_USE,
	STR_CHOOSE_AMMO,
	STR_CHOOSE_WEAPON_MODE,
	STR_COMBINE,
	STR_SEPARATE,
	STR_EQUIP,
	STR_COMBINE_WITH,
	STR_LOAD_GAME,
	STR_SAVE_GAME,
	STR_EXAMINE,
	STR_MORE,
	STR_SELECT_AMMO,
	STR_SELECT_OPTION,
	STR_COMBINE_BIS,
	STR_PUSH_KEYPAD,
	STR_MOVEMENT,
	STR_PREVIOUS_NEXT_BACK,
	STR_GRAPPLING_GUN,
	STR_GRAPPLING_GUN_AMMO,
	STR_CHLOROFORM_SOAKED_CLOTH,
	STR_CLOTH,
	STR_BOTTLE_OF_CHLOROFORM,
	STR_UZI,
	STR_PISTOLS,
	STR_SHOTGUN,
	STR_REVOLVER,
	STR_REVOLVER_LASERSIGHT,
	STR_DESERTEAGLE,
	STR_DESERTEAGLE_LASERSIGHT,
	STR_DESERTEAGLE_AMMO,
	STR_HK,
	STR_HK_SILENCED,
	STR_SHOTGUN_NORMAL_AMMO,
	STR_SHOTGUN_WIDESHOT_AMMO,
	STR_HK_SNIPER_MODE,
	STR_HK_BURST_MODE,
	STR_HK_RAPID_MODE,
	STR_HK_AMMO,
	STR_REVOLVER_AMMO,
	STR_UZI_AMMO,
	STR_PISTOL_AMMO,
	STR_LASERSIGHT,
	STR_SILENCER,
	STR_LARGE_MEDIPACK,
	STR_SMALL_MEDIPACK,
	STR_BINOCULARS,
	STR_HEADSET,
	STR_FLARES,
	STR_TIMEX_TMX,
	STR_LOAD,
	STR_SAVE,
	STR_CROWBAR,
	STR_GARDEN_KEY,
	STR_SATURN_SYMBOL,
	STR_GOLDEN_KEY_1,
	STR_GOLDEN_KEY_2,
	STR_MERCURY_STONE,
	STR_TELEPORTER_DISC,
	STR_FUSE,
	STR_SILVER_KEY,
	STR_BRONZE_KEY,
	STR_SWIPE_CARD,
	STR_HAMMER,
	STR_ACCESS_CODE_DISC,
	STR_IRIS_LAB_ACCESS,
	STR_HIGH_LEVEL_ACCESS_CARD,
	STR_ID_ACCESS_CARD,
	STR_IRIS_ARTEFACT,
	STR_LOW_LEVEL_ACCESS_CARD,
	STR_RESTROOM_ACCESS_CARD,
	STR_HELIPAD_ACCESS_KEY,
	STR_KEY_BIT_LEFT,
	STR_KEY_BIT_RIGHT,
	STR_VALVE_WHEEL,
	STR_GOLDEN_COIN,
	STR_MARS_SYMBOL,
	STR_VENUS_SYMBOL,
	STR_GEMSTONE,
	STR_PHILOSOPHERS_STONE,
	STR_COLOSSEUM_KEY_1,
	STR_COLOSSEUM_KEY_2,
	STR_GEMSTONE_PIECE,
	STR_SPEAR_OF_DESTINY,
	STR_HEART,
	STR_CATAPULT,
	STR_IRON_CLAPPER,
	STR_RUBBER_TUBE,
	STR_PITCHFORK,
	STR_BONE_DUST,
	STR_BESTIARY,
	STR_CHALK,
	STR_SILVER_COIN,
	STR_SUIT_CONSOLE,
	STR_SUIT_BATTERY,
	STR_AQUALUNG,
	STR_SUIT_CONSOLE_BIS,
	STR_BATTERY_PLUS,
	STR_BATTERY_MINUS,
	STR_CHAFF_FLARES,
	STR_NITROGEN_CANISTER,
	STR_OXYGEN_CANISTER,
	STR_YES,
	STR_NO,
	STR_LOAD_GAME_BIS,
	STR_SAVE_GAME_BIS,
	STR_PAUSED,
	STR_SELECT_GAME_TO_LOAD,
	STR_SELECT_GAME_TO_SAVE,
	STR_SPECIAL_FEATURES,
	STR_MOVIE_TRAILER,
	STR_STORYBOARDS_PART_1,
	STR_NEXT_GENERATION_CONCEPT_ART,
	STR_STORYBOARDS_PART_2,
	STR_NEXT_GENERATION_PREVIEW,
	STR_GAME_OVER,
	STR_SAVE_GAME_BIS_BIS,
	STR_EXIT_TO_TITLE,
	STR_DEMO_MODE,
	STR_CURRENT_LOCATION,
	STR_STATISTICS,
	STR_DISTANCE_TRAVELLED,
	STR_AMMO_USED,
	STR_SECRETS_FOUND,
	STR_LOCATION,
	STR_HEALTH_PACKS_USED,
	STR_TIME_TAKEN,
	STR_DAYS,
	STR_OF,
	STR_SECRETS_NUM,
	STR_ACTION,
	STR_DRAW_WEAPON,
	STR_JUMP,
	STR_ROLL,
	STR_WALK,
	STR_LOOK,
	STR_DUCK,
	STR_DASH,
	STR_INVENTORY,
	STR_SELECT,
	STR_CANCEL,
	STR_BACK,
	STR_OK,
	STR_CANCEL_BIS,
	STR_PSX_GAME_ID, // BESLES-03331 (IT, UK), BASLUS-01311 (US), BESLES-03334 (DE), BESLES-03333 (FR), BESLES-03336 (ES)
	STR_INSERT_MEMCARD_INTO_SLOT_1,
	STR_CHECKING_MEMORY_CARD,
	STR_MEMCARD_UNFORMATTED_FORMAT_IT,
	STR_LOADING_DATA_DO_NOT_REMOVE,
	STR_SAVING_DATA_DO_NOT_REMOVE,
	STR_FORMATTING_MEMCARD_DO_NOT_REMOVE,
	STR_OVERWRITE_ON_MEMCARD,
	STR_MEMCARD_IS_UNFORMATTED_INSERT_FORMATTED,
	STR_MEMCARD_INSUFFICIENT_FREE_BLOCKS, // + INSERT MEMCARD WITH AT LEAST 2 FREE BLOCKS
	STR_THERE_ARE_NO_SAVEGAMES,
	STR_LOADING,
	STR_LOAD_OK,
	STR_SAVED_OK,
	STR_FORMAT_OK,
	STR_LOAD_FAILED,
	STR_SAVE_FAILED,
	STR_FORMAT_FAILED,
	STR_EMPTY,
	STR_CONTROLLER_REMOVED,
	STR_RESUME,
	STR_QUIT,
	STR_GAME_SETTINGS,
	STR_CONTROL_OPTIONS,
	STR_CONFIRM_QUIT,
	STR_SCREEN_ADJUST,
	STR_SFX_VOLUME,
	STR_MUSIC_VOLUME,
	STR_USE_DIRECTIONAL_BUTTONS,
	STR_CONFIGURE_CONTROLS,
	STR_CONFIGURATION,
	STR_VIBRATION_ON,
	STR_VIBRATION_OFF,
	STR_MANUAL_TARGETING,
	STR_AUTOMATIC_TARGETING,
	STR_ELLIPSIS,
	STR_ELLIPSIS_BIS,
	STR_PROGRAMMERS,
	STR_ADDITIONAL_PROGRAMMERS,
	STR_AI_PROGRAMMERS,
	STR_ANIMATORS,
	STR_LEVEL_DESIGNERS,
	STR_FMV_SEQUENCES,
	STR_MUSIC_AND_SOUND_FX,
	STR_ORIGINAL_STORY,
	STR_SCRIPT,
	STR_PRODUCER,
	STR_QA,
	STR_EXECUTIVE_PRODUCERS,
	STR_ADDITIONAL_SOUND_FX,
	STR_RUBBISH,
	STR_PC_PROGRAMMER,
	STR_PROGRAMMERS_BIS,
	STR_ADDITIONAL_PROGRAMMING,
	STR_RESUME_BIS,
	STR_OPTIONS,
	STR_EMPTY_SLOT,
	STR_MUSIC_VOLUME_BIS,
	STR_SFX_VOLUME_BIS,
	STR_SOUND_QUALITY,
	STR_LOW,
	STR_MEDIUM,
	STR_HIGH,
	STR_TARGETING,
	STR_MANUAL,
	STR_AUTOMATIC,
	STR_GRAPHICS_ADAPTER,
	STR_OUTPUT_SETTINGS,
	STR_OUTPUT_RESOLUTION,
	STR_TEXTURE_BIT_DEPTH,
	STR_OK_BIS,
	STR_CANCEL_BIS_BIS,
	STR_HARDWARE_ACCELERATION,
	STR_SOFTWARE_MODE,
	STR_VOLUMETRIC_FX,
	STR_BILINEAR_FILTERING,
	STR_BUMP_MAPPING,
	STR_LOW_RESOLUTION_TEXTURES,
	STR_LOW_RESOLUTION_BUMP_MAPS,
	STR_SOUND_DEVICE,
	STR_DISABLE,
	STR_BIT,
	STR_FULL_SCREEN,
	STR_WINDOWED,
	STR_RENDER_OPTIONS,
	STR_NO_SOUND_CARD_INSTALLED,
	STR_FAILED_TO_SETUP_DIRECTX,
	STR_EXIT,
	STR_CONTROL_CONFIGURATION,
	STR_USE_FLARE,
	STR_CONTROL_METHOD,
	STR_MOUSE,
	STR_KEYBOARD,
	STR_JOYSTICK,
	STR_WAITING,
	STR_RESET,
	STR_SAVE_SETTINGS,
	STR_SAVED_OK_BIS,
	STR_STEP_LEFT,
	STR_STEP_RIGHT,
	STR_PLAY,
	STR_SETUP,
	STR_INSTALL,
	STR_UNINSTALL,
	STR_README,
	STR_DEMO_MODE_ESC_TO_EXIT,
	STR_SELECT_LEVEL,
	STR_NO_FMV,
	STR_LAST_STRING_ENTRY,

	NUM_STRING_ENTRIES
};

