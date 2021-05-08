#pragma once
#include "types.h"

// Variable macros
#define VAR_U_(address, type)			(*(type*)(address)) // uninitialized variable
#define VAR_I_(address, type, value)	(*(type*)(address)) // initialized variable (value is just for info)
#define ARRAY_(address, type, length)	(*(type(*)length)(address)) // array (can be multidimensional)

//vars
#define input VAR_U_(0x00878D98, int)
#define dbinput   VAR_U_(0x00878DAC, int)
#define mycoll   VAR_U_(0x00E5BC20, COLL_INFO*)
#define lara    VAR_U_(0x00E5BD60, LARA_INFO)
#define lara_item    VAR_U_(0x00E5BF08, ITEM_INFO*)
#define DashTimer VAR_U_(0x00E5BF04, unsigned short)
#define anims	VAR_U_(0x00875158, ANIM_STRUCT*)
#define items	VAR_U_(0x00EEEFF0, ITEM_INFO*)
#define effects	VAR_U_(0x00E5C5E0, FX_INFO*)
#define room	VAR_U_(0x00875154, room_info*)
#define	meshes	VAR_U_(0x00875170, short**)
#define bones	VAR_U_(0x00875178, long*)
#define height_type VAR_U_(0x00EEEFF4, int)
#define trigger_index VAR_U_(0x00EEEF9C, short*)
#define xfront VAR_U_(0x00EEf928, long)
#define zfront VAR_U_(0x00EEf92C, long)
#define GLOBAL_cutseq_frame VAR_U_(0x00E7F024, int)
#define old_lara_holster VAR_U_(0x00E7EFE0, unsigned short)
#define actor_chat_cnt VAR_U_(0x0051CAB6, char)
#define lara_chat_cnt	VAR_U_(0x0051CAB5, char)
#define gfCurrentLevel VAR_U_(0x00E5C2D0, int)
#define gfLevelComplete VAR_U_(0x00E5C2F0, int)
#define gfLevelFlags	VAR_U_(0x00E5C2A0, short)
#define gfGameMode	VAR_U_(0x005082C0, unsigned char)
#define cutseq_num	VAR_U_(0x0051CAA8, int)
#define cutseq_trig	VAR_U_(0x0051CAAC, int)
#define cutseq_busy_timeout	VAR_U_(0x0051CAB4, char)
#define bTrackCamInit	VAR_U_(0x0051D010, int)
#define bUseSpotCam	VAR_U_(0x0051D018, int)
#define SetDebounce	VAR_U_(0x00EEEA38, int)
#define framecount	VAR_U_(0x0051CA78, int)
#define GlobalCounter	VAR_U_(0x0051CA58, unsigned short)
#define cdtrack	VAR_U_(0x00506C64, short)
#define bDisableLaraControl	VAR_U_(0x0051D01C, int)
#define GLOBAL_enterinventory	VAR_U_(0x00508E18, int)
#define GLOBAL_playing_cutseq	VAR_U_(0x0051CAB0, int)
#define GLOBAL_inventoryitemchosen	VAR_U_(0x00508E1C, int)
#define reset_flag	VAR_U_(0x0051CA6C, int)
#define FadeScreenHeight	VAR_U_(0x0051D074, short)
#define thread_started	VAR_U_(0x00876C48, bool)
#define SniperCamActive	VAR_U_(0x0051CA1D, char)
#define BinocularRange	VAR_U_(0x0051CA30, long)
#define BinocularOn	VAR_U_(0x0051CA34, long)
#define BinocularOldCamera	VAR_U_(0x0051CA38, camera_type)
#define LaserSight	VAR_U_(0x0051CA3C, long)
#define InfraRed	VAR_U_(0x0051CA40, long)
#define inputBusy	VAR_U_(0x00878C94, int)
#define GotLaraSpheres	VAR_U_(0x00E51F2E, char)
#define InItemControlLoop	VAR_U_(0x0051CA53, unsigned char)
#define next_item_active	VAR_U_(0x00E5BF22, short)
#define next_fx_active	VAR_U_(0x00E5C5FC, short)
#define KillEverythingFlag	VAR_U_(0x0051CDF4, long)
#define SmokeCountL	VAR_U_(0x00E6C9E8, long)
#define SmokeCountR	VAR_U_(0x00E6C9EC, long)
#define SplashCount	VAR_U_(0x0051CDF8, long)
#define WeaponDelay	VAR_U_(0x0051CA52, unsigned char)
#define wibble	VAR_U_(0x0051CDF0, long)
#define XSoff1	VAR_U_(0x0055D200, short)
#define XSoff2	VAR_U_(0x0055D1FC, short)
#define YSoff1	VAR_U_(0x0055D210, short)
#define YSoff2	VAR_U_(0x0055D214, short)
#define	ZSoff1	VAR_U_(0x0055D244, short)
#define ZSoff2	VAR_U_(0x0055D248, short)
#define PoisonFlag	VAR_U_(0x00E5BF3E, char)
#define LaraDrawType	VAR_U_(0x00EEEAD0, char)
#define CamRot	VAR_U_(0x00E4B0E0, SVECTOR)
#define SmashedMeshCount	VAR_U_(0x0051CA5C, short)
#define health_bar_timer	VAR_U_(0x0051CEA8, int)
#define GameTimer	VAR_U_(0x00E5C27C, unsigned long)
#define Gameflow	VAR_U_(0x00E5C2BC, GAMEFLOW*)
#define camera	VAR_U_(0x00EEF940, CAMERA_INFO)
#define CamOldPos	VAR_U_(0x00EEFB00, PHD_VECTOR)
#define savegame	VAR_U_(0x00E52EB3, savegame_info)
#define NumRPickups	VAR_U_(0x00E5970C, unsigned char)
#define waterfallY	VAR_U_(0x0051CF54, int)
#define next_blood	VAR_U_(0x0051D088, long)
#define floor_data	VAR_U_(0x00875168, short*)
#define rand_1	VAR_U_(0x00516A38, long)
#define	rand_2	VAR_U_(0x00516A3C, long)
#define	last_target	VAR_U_(0x00EEFA30, GAME_VECTOR)
#define	last_ideal	VAR_U_(0x00EEFA40, GAME_VECTOR)
#define UseForcedFixedCamera	VAR_U_(0x00EEFA50, char)
#define	InGameCnt	VAR_U_(0x00E5BF0C, unsigned char)
#define	cheat_hit_points	VAR_U_(0x00E5BBF8, short)
#define	gfNumPickups	VAR_U_(0x0051CE38, unsigned char)
#define gfNumTakeaways	VAR_U_(0x0051CE39, unsigned char)
#define	disable_horizon	VAR_U_(0x0051CAA4, unsigned char)
#define	level_items	VAR_U_(0x0051CEB8, int)
#define	cutseq_num	VAR_U_(0x0051CAA8, int)
#define	cutseq_trig	VAR_U_(0x0051CAAC, int)
#define	numnailed	VAR_U_(0x00E6E4E4, int)
#define	GLOBAL_cutme	VAR_U_(0x00E711B0, NEW_CUTSCENE*)
#define	dels_cutseq_player	VAR_U_(0x0051CE2C, unsigned short)
#define	GLOBAL_oldcamtype	VAR_U_(0x00E711AC, camera_type)
#define	CurrentAtmosphere	VAR_U_(0x00EEEB90, unsigned char)
#define	IsAtmospherePlaying	VAR_U_(0x00EEEFFC, unsigned char)
#define gfRequiredStartPos	VAR_U_(0x00E5C2B4, unsigned char)
#define	ScreenFade	VAR_U_(0x0051D068, short)
#define	dScreenFade	VAR_U_(0x0051D06A, short)
#define	ScreenFadeBack	VAR_U_(0x0051D06C, short)
#define ScreenFadeSpeed	VAR_U_(0x0050A178, short)
#define	ScreenFadedOut	VAR_U_(0x0051D06E, short)
#define ScreenFading	VAR_U_(0x0051D070, short)
#define	cut_seethrough	VAR_U_(0x00506D9C, int)
#define	cutrot	VAR_U_(0x0051CAA0, int)
#define bDoCredits	VAR_U_(0x0051CE35, unsigned char)
#define num_fmvs	VAR_U_(0x0051CE25, char)
#define gfScriptWad	VAR_U_(0x0051CE20, unsigned char*)
#define	gfStringWad	VAR_U_(0x00E5C310, char*)
#define	gfFilenameWad	VAR_U_(0x00E5C2CC, char*)
#define gfScriptOffset	VAR_U_(0x0051CE10, unsigned short*)
#define	gfStringOffset	VAR_U_(0x00E5C2AC, unsigned short*)
#define gfStringOffset_bis	VAR_U_(0x00E5C2B8, unsigned short*)
#define gfStatus	VAR_U_(0x00E5C2B0, int)
#define gfLegend	VAR_U_(0x00E5C348, unsigned char)
#define gfLegendTime	VAR_U_(0x0051CE34, unsigned char)
#define gfUVRotate	VAR_U_(0x00E5C349, char)
#define gfNumMips	VAR_U_(0x0051CE37, unsigned char)
#define gfMirrorRoom	VAR_U_(0x00E5C24C, unsigned char)
#define gfMirrorZPlane	VAR_U_(0x00E6D748, long)
#define gfInitialiseGame	VAR_U_(0x005082C1, unsigned char)	
#define	gfLayer1Col	VAR_U_(0x00E5C2A4, CVECTOR)
#define gfLayer2Col	VAR_U_(0x00E5C280, CVECTOR)
#define	gfLayer1Vel	VAR_U_(0x00E5C276, char)
#define	gfLayer2Vel	VAR_U_(0x00E5C275, char)	
#define gfLensFlare	VAR_U_(0x00E5C2E0, PHD_VECTOR)
#define gfLensFlareColour	VAR_U_(0x00E5C2F4, CVECTOR)
#define gfResetHubDest	VAR_U_(0x00E5C2C8, unsigned char)
#define gfCutNumber	VAR_U_(0x0051CE36, unsigned char)
#define	changes	VAR_U_(0x0087515C, CHANGE_STRUCT*)
#define ranges	VAR_U_(0x00875160, RANGE_STRUCT*)
#define commands	VAR_U_(0x0087517C, short*)
#define	FXType	VAR_U_(0x00EEF900, short)
#define flipeffect	VAR_U_(0x00506C60, int)
#define	KeyTriggerActive	VAR_U_(0x0051CA56, unsigned char)
#define TriggerTimer	VAR_U_(0x0051CA5A, char)
#define OnObject	VAR_U_(0x00EEEAC8, int)
#define FootPrintNum	VAR_U_(0x00E5C350, int)
#define	number_dynamics	VAR_U_(0x00E6D82C, int)
#define	tiltyoff	VAR_U_(0x00EEEADC, int)
#define	tiltxoff	VAR_U_(0x00EEEAD4, int)
#define	baddie_slots	VAR_U_(0x00E5B834, creature_info*)
#define stats_mode	VAR_U_(0x0051CF26, short)
#define go_select	VAR_U_(0x00E59E2A, unsigned char)
#define	go_deselect	VAR_U_(0x00E5992C, unsigned char)
#define go_right	VAR_U_(0x00E5989C, unsigned char)
#define	go_left	VAR_U_(0x00E59899, unsigned char)
#define go_up	VAR_U_(0x00E59922, unsigned char)
#define go_down	VAR_U_(0x00E59929, unsigned char)
#define keypadx	VAR_U_(0x0051CF30, unsigned char)
#define keypady	VAR_U_(0x0051CF31, unsigned char)
#define keypadnuminputs	VAR_U_(0x0051CF32, unsigned char)
#define keypadpause	VAR_U_(0x0051CF33, unsigned char)
#define GnFrameCounter	VAR_U_(0x00E4B0FC, unsigned long)
#define use_the_bitch	VAR_U_(0x00E59921, char)	
#define menu_active	VAR_U_(0x00E5989A, char)
#define inventry_xpos	VAR_U_(0x0051CF34, short)
#define inventry_ypos	VAR_U_(0x0051CF36, short)
#define SmokeWeapon	VAR_U_(0x00E6CAA0, long)
#define HKTimer	VAR_U_(0x0051CEC9, char)
#define HKShotsFired	VAR_U_(0x0051CEC8, char)
#define joy_fire	VAR_U_(0x00878D9C, int)
#define joy_x	VAR_U_(0x00878DA0, int)
#define joy_y	VAR_U_(0x00878DA4, int)
#define XATrack	VAR_U_(0x00510B14, short)
#define MusicVolume	VAR_U_(0x00E4B0EC, int)
#define TargetSnaps	VAR_U_(0x0051CA2D, char)
#define SniperCount	VAR_U_(0x0051CA1C, char)
#define TLFlag	VAR_U_(0x0051CA44, char)
#define SniperOverlay	VAR_U_(0x0051D022, char)
#define sound_effects	VAR_U_(0x00E5C5F8, OBJECT_VECTOR*)
#define number_sound_effects	VAR_U_(0x00E5C5F0, int)
#define sound_active	VAR_U_(0x0051D004, int)
#define sample_infos	VAR_U_(0x00E528A8, SAMPLE_INFO*)
#define wf	VAR_U_(0x005078F0, long)
#define sample_lut	VAR_U_(0x00E528A4, short*)
#define examine_mode	VAR_U_(0x0051CF24, short)
#define boxes	VAR_U_(0x00EEFB64, box_info*)
#define SubHitCount	VAR_U_(0x0051CEE4, char)
#define subsuit	VAR_U_(0x00E5B850, SUBSUIT_INFO)
#define OldPickupPos	VAR_U_(0x00E59700, PHD_VECTOR)
#define CurrentSequence	VAR_U_(0x00E4EA61, unsigned char)
#define FlashFadeR	VAR_U_(0x0051D07A, short)
#define FlashFadeG	VAR_U_(0x0051D07C, short)
#define FlashFadeB	VAR_U_(0x0051D07E, short)
#define FlashFader	VAR_U_(0x0051D080, short)
#define PickupX	VAR_U_(0x00E5BF38, short)
#define PickupY	VAR_U_(0x00E5BF26, short)
#define PickupVel	VAR_U_(0x00E5BF3A, short)
#define CurrentPickup	VAR_U_(0x00E5BF3C, short)
#define Chris_Menu	VAR_U_(0x0051CE2E, char)
#define title_controls_locked_out	VAR_U_(0x00E5C2A8, char)
#define jobyfrigger	VAR_U_(0x0051CA9C, char)
#define CurrentPistolsAmmoType	VAR_U_(0x0051CF06, char)
#define CurrentUziAmmoType	VAR_U_(0x0051CF11, char)
#define CurrentRevolverAmmoType	VAR_U_(0x0051CF0A, char)
#define CurrentShotGunAmmoType	VAR_U_(0x0051CF0B, char)
#define CurrentGrenadeGunAmmoType	VAR_U_(0x0051CF00, char)
#define CurrentCrossBowAmmoType	VAR_U_(0x0051CF1C, char)
#define AmountPistolsAmmo	VAR_U_(0x0051CF16, short)
#define AmountRevolverAmmo	VAR_U_(0x0051CF14, short)
#define AmountHKAmmo1	VAR_U_(0x0051CF08, short)
#define AmountCrossBowAmmo1	VAR_U_(0x0051CF0E, short)
#define AmountCrossBowAmmo2	VAR_U_(0x0051CF0C, short)
#define AmountShotGunAmmo1	VAR_U_(0x0051CF04, short)
#define AmountShotGunAmmo2	VAR_U_(0x0051CF02, short)
#define AmountUziAmmo	VAR_U_(0x0051CF1A, short)
#define current_selected_option	VAR_U_(0x00E598F9, char)
#define ammo_active	VAR_U_(0x00E5991F, char)
#define right_repeat	VAR_U_(0x00E59915, unsigned char)
#define right_debounce	VAR_U_(0x00E59914, unsigned char)
#define left_repeat	VAR_U_(0x00E59E29, unsigned char)
#define left_debounce	VAR_U_(0x00E5989B, unsigned char)
#define	ammo_selector_fade_dir	VAR_U_(0x00E59926, short)
#define	ammo_selector_fade_val	VAR_U_(0x00E5990A, short)
#define	ammo_selector_flag	VAR_U_(0x00E59928, char)
#define num_ammo_slots	VAR_U_(0x00E598A4, char)
#define current_ammo_type	VAR_U_(0x00E59918, char*)
#define OBJLIST_SPACING	VAR_U_(0x00E59894, int)
#define combine_ring_fade_dir	VAR_U_(0x00E5991C, short)
#define	combine_obj1	VAR_U_(0x00E59912, short)
#define	combine_obj2	VAR_U_(0x00E59910, short)
#define	combine_ring_fade_val	VAR_U_(0x00E598F6, short)
#define	combine_type_flag	VAR_U_(0x00E59E28, short)
#define seperate_type_flag	VAR_U_(0x00E598F8, short)
#define loading_or_saving	VAR_U_(0x00E5989D, char)
#define normal_ring_fade_dir	VAR_U_(0x00E59924, short)
#define normal_ring_fade_val	VAR_U_(0x00E59908, short)
#define StashedCurrentPistolsAmmoType	VAR_U_(0x0051CF12, char)//static
#define StashedCurrentUziAmmoType	VAR_U_(0x0051CF01, char)//static
#define StashedCurrentRevolverAmmoType	VAR_U_(0x0051CF1D, char)//static
#define StashedCurrentShotGunAmmoType	VAR_U_(0x0051CF18, char)//static
#define StashedCurrentGrenadeGunAmmoType	VAR_U_(0x0051CF10, char)//static
#define StashedCurrentCrossBowAmmoType	VAR_U_(0x0051CF13, char)//static
#define Stashedcurrent_selected_option	VAR_U_(0x00E5992B, char)//static
#define	GLOBAL_invkeypadmode	VAR_U_(0x0051CF28, int)
#define up_debounce	VAR_U_(0x00E5992A, unsigned char)
#define down_debounce	VAR_U_(0x00E598D8, unsigned char)
#define GLOBAL_lastinvitem	VAR_U_(0x00508E14, int)
#define select_debounce	VAR_U_(0x00E59920, unsigned char)
#define deselect_debounce	VAR_U_(0x00E598F2, unsigned char)
#define friggrimmer	VAR_U_(0x00E598F4, char)
#define friggrimmer2	VAR_U_(0x00E598F3, char)
#define oldLaraBusy	VAR_U_(0x00E59898, char)
#define GLOBAL_numcutseq_frames	VAR_U_(0x00E7F020, int)
#define camera_pnodes	VAR_U_(0x00E7EE9C, PACKNODE*)
#define GLaraShadowframe	VAR_U_(0x00E86300, short*)
#define malloc_buffer	VAR_U_(0x00E4B10C, char*)
#define malloc_ptr	VAR_U_(0x00E4B0DC, char*)
#define malloc_size	VAR_U_(0x00E4B058, int)
#define malloc_used	VAR_U_(0x00E4B0F0, int)
#define malloc_free	VAR_U_(0x00E4B0F4, int)
#define ShatterItem	VAR_U_(0x00EEFAE0, SHATTER_ITEM)
#define GLOBAL_invkeypadcombination	VAR_U_(0x0051CF2C, int)
#define DestFadeScreenHeight	VAR_U_(0x0051D076, short)
#define dels_cutseq_selector_flag	VAR_U_(0x0051CE2A, short)
#define pcring1	VAR_U_(0x00E59BC0, RINGME)
#define pcring2	VAR_U_(0x00E59940, RINGME)
#define InventoryActive	VAR_U_(0x0051CF20, int)
#define xoffset	VAR_U_(0x00E598A0, int)//inv
#define yoffset	VAR_U_(0x00E5990C, int)//inv
#define pcbright	VAR_U_(0x00508E10, long)//inv
#define gfFog	VAR_U_(0x0051CE30, CVECTOR)
#define GlobalFogOff	VAR_U_(0x0051CE04, int)
#define LiftDoor	VAR_U_(0x0051CB40, char)
#define GlobalSoftReset	VAR_U_(0x00E5C2F8, int)
#define GlobalAlpha	VAR_U_(0x00506D3C, int)
#define current_item	VAR_U_(0x009158A8, ITEM_INFO*)
#define aGlobalSkinMesh	VAR_U_(0x00921680, int)
#define phd_top	VAR_U_(0x0051D0A8, long)
#define phd_bottom	VAR_U_(0x0055D204, long)
#define phd_left	VAR_U_(0x0055D20C, long)
#define phd_right	VAR_U_(0x0055DA3C, long)
#define	phd_winxmax	VAR_U_(0x0055D218, short)
#define	phd_winxmin	VAR_U_(0x0055D234, short)
#define	phd_winymax	VAR_U_(0x0055D240, short)
#define	phd_winymin	VAR_U_(0x0055D1E8, short)
#define phd_mxptr	VAR_U_(0x00E4B0F8, long*)
#define aMXPtr	VAR_U_(0x0055DA2C, float*)//formerly named phd_dxptr!
#define IM_rate	VAR_U_(0x00E6E464, long)
#define IM_frac	VAR_U_(0x00E6D734, long)
#define IMptr	VAR_U_(0x00E6E468, long*)
#define aIMXPtr	VAR_U_(0x00E6D834, float*)
#define aIFMStack	ARRAY_(0x00E6D860, float, [768])
#define	IMstack	ARRAY_(0x00E6CB00, long, [768])
#define f_persp	VAR_U_(0x0051D15C, float)
#define f_znear	VAR_U_(0x0051D158, float)
#define	f_znear3	VAR_U_(0x0055D24C, float)
#define	f_zfar	VAR_U_(0x0055DA38, float)
#define f_oneopersp	VAR_U_(0x0055D254, float)
#define phd_centery	VAR_U_(0x0055D1B4, int)
#define	phd_centerx	VAR_U_(0x0055D1B0, int)
#define font_height	VAR_U_(0x00E4DEA8, int)
#define	CurrentFOV	VAR_U_(0x00E4F504, short)
#define	phd_winheight	VAR_U_(0x0055D164, int)
#define	phd_winwidth	VAR_U_(0x0055D29C, int)
#define	f_persp_bis	VAR_U_(0x0055D268, float)
#define	f_persp_bis_over_znear3	VAR_U_(0x0055D238, float)
#define	one	VAR_U_(0x0050A444, float)
#define	phd_persp	VAR_U_(0x0055D208, int)
#define	LfAspectCorrection	VAR_U_(0x0055DA30, float)
#define	f_perspoznear	VAR_U_(0x0055D668, float)
#define IsRoomOutsideNo	VAR_U_(0x00EEF902, short)
#define _CutSceneTriggered1	VAR_U_(0x00EEF004, unsigned long)
#define _CutSceneTriggered2	VAR_U_(0x00EEF000, unsigned long)
#define richcutfrigflag	VAR_U_(0x0051CA5E, char)
#define number_los_rooms VAR_U_(0x0051CA70, int)
#define LaserSightActive VAR_U_(0x0051D072, char)
#define LaserSightY VAR_U_(0x00E4C9A0, long)
#define LaserSightZ VAR_U_(0x00E4C9A4, long)
#define LaserSightX VAR_U_(0x00E4C9A8, long)
#define LaserSightCol VAR_U_(0x0051D073, char)
#define GetLaraOnLOS VAR_U_(0x0051CA64, char)
#define ClosestDist VAR_U_(0x00EEF4A4, int)
#define ClosestCoord VAR_U_(0x00EEF460, PHD_VECTOR)
#define ClosestItem VAR_U_(0x00EEEFF8, int)
#define nRope VAR_U_(0x0051CA60, int)
#define CurrentPendulum VAR_U_(0x00EEF020, PENDULUM)
#define NullPendulum VAR_U_(0x0051CFD0, PENDULUM)
#define CamPos	VAR_U_(0x00E4B0D0, PHD_VECTOR)
#define bLaraUnderWater	VAR_U_(0x0057A150, int)
#define bLaraSkinBits	VAR_U_(0x0057A458, int)
#define aMappedNormals	VAR_U_(0x0057A45C, LPD3DVECTOR)
#define skinMatrixPtr	VAR_U_(0x00E5B918, long*)
#define bLaraInWater	VAR_U_(0x0057A468, char)
#define SmokeWindZ	VAR_U_(0x00E6C9E4, long)
#define SmokeWindX	VAR_U_(0x00E6C9E0, long)
#define hair_wind	VAR_U_(0x0051CEA4, int)
#define hair_dwind_angle	VAR_U_(0x005084D4, int)
#define hair_wind_angle	VAR_U_(0x005084D0, int)


/*title shit*/
#define sound_cut_flag	VAR_U_(0x0051CE58, int)//DoTitle and SoundEffect. flag before and after doing some title cutscene, 
//if 0 + playing cut menu selections dont make a sound. never seems to be the case though!

#define selected_option	VAR_U_(0x005082F0, __int64)

#define menu_to_display	VAR_U_(0x0051CE40, int)//which menu should we be displaying right now??
//0 main menu, del's cutseq selector. 1 level select. 2 the reload menu. 3 the options menu

#define DoFade	VAR_U_(0x00C87BF0, int)// 2 everywhere, 1 in loading screens

#define title_string	ARRAY_(0x0050842C, char, [8])

#define nframes	VAR_U_(0x005082C4, int)

#define selected_level	VAR_U_(0x0051CE50, int)//# (on the list) of the selected level in the level select menu

#define level_select_names	ARRAY_(0x005082C8, char, [40])

#define CreditsDone	VAR_U_(0x00E6D838, unsigned char)
#define CanLoad	VAR_U_(0x0051CE54, char)
#define JustLoaded	VAR_U_(0x0051D001, char)
/*title shit*/

//arrays
#define cutseq_meshbits	ARRAY_(0x00E7EEA0, unsigned long, [10])
#define objects	ARRAY_(0x0086CF50, OBJECT_INFO, [460])
#define SmashedMesh	ARRAY_(0x00EEF8C0, MESH_INFO*, [16])
#define SmashedMeshRoom	ARRAY_(0x00EEF480, short, [16])
#define blood	ARRAY_(0x00E4C9C0, BLOOD_STRUCT, [32])
#define RPickups	ARRAY_(0x00E596E0, unsigned char, [16])
#define AnimatingWaterfalls	ARRAY_(0x00E59720, OBJECT_TEXTURE*, [6])
#define AnimatingWaterfallsV	ARRAY_(0x00E59760, float, [6])
#define interpolated_bounds	ARRAY_(0x00E6E4D0, short, [6])
#define LM	ARRAY_(0x00506B94, char, [15])
#define	keymap	ARRAY_(0x0086BB8C, char, [256])
#define gfTakeaways	ARRAY_(0x00E5C290, unsigned char, [16])
#define gfPickups	ARRAY_(0x00E5C300, unsigned char, [16])
#define	weapons	ARRAY_(0x005085B0, WEAPON_INFO, [9])
#define	DeadlyBounds	ARRAY_(0x00E6C3C0, long, [6])
#define cutseq_meshswapbits	ARRAY_(0x00E7EEE0, unsigned long, [10])
#define fmv_to_play	ARRAY_(0x0051CE28, char, [2])
#define gfResidentCut	ARRAY_(0x00E5C278, unsigned char, [4])
#define	LightningRGB	ARRAY_(0x00E6E4B8, unsigned short, [3])
#define LightningRGBs	ARRAY_(0x00E6CAF0, unsigned short, [3])
#define gfMips	ARRAY_(0x00E5C2C0, unsigned char, [8])
#define inventry_objects_list	ARRAY_(0x00508E38, INVOBJ, [100])
#define itemlist	ARRAY_(0x00E88EA0, ITEM_INFO*, [1024])//what the fucking fuck
#define meshlist	ARRAY_(0x00E872A0, MESH_INFO*, [1024])//what the fucking fuck
#define staticlist	ARRAY_(0x00E89EA0, MESH_INFO*, [1024])//what the fucking fuck
#define	FootPrint	ARRAY_(0x00E5C3E0, FOOTPRINT, [32])
#define	gfLevelNames	ARRAY_(0x00E5C320, unsigned char, [40])
#define	dynamics	ARRAY_(0x00E6C3E0, DYNAMIC, [64])
#define Slist	ARRAY_(0x00E51FE0, SPHERE, [34])
#define keypadinputs	ARRAY_(0x00E59778, unsigned char, [4])
#define hairs	ARRAY_(0x00E5C000, HAIR_STRUCT, [2][7])
#define smoke_spark	ARRAY_(0x00E4B940, SMOKE_SPARKS, [32])
#define layout	ARRAY_(0x00516C3C, short, [2][18])
#define conflict	ARRAY_(0x00878C4C, int, [18])
#define reg_class	ARRAY_(0x0057A080, char, [4])
#define flip_stats	ARRAY_(0x00EEF060, int, [255])
#define LaSlot	ARRAY_(0x00E52420, SoundSlot, [32])
#define rings	ARRAY_(0x00E59900, RINGME*, [2])
#define SequenceUsed	ARRAY_(0x00E4EA78, unsigned char, [6])
#define SequenceResults	ARRAY_(0x00E4EA80, unsigned char, [3][3][3])
#define Sequences	ARRAY_(0x00E4EA9C, unsigned char, [3])
#define ClosedDoors	ARRAY_(0x0051CAC0, ITEM_INFO*, [32])
#define flipmap	ARRAY_(0x00EEEBA0, int, [255])
#define spark	ARRAY_(0x00E5F380, SPARKS, [128])
#define pickups	ARRAY_(0x00E5BF40, DISPLAYPU, [8])
#define ShatterSounds	ARRAY_(0x00506BAC, unsigned char, [18][10])
#define twogun	ARRAY_(0x00EEEB00, TWOGUN_INFO, [3])
#define ammo_object_list	ARRAY_(0x00E598E0, AMMOLIST, [3])
#define current_options	ARRAY_(0x00E598C0, MENUTHANG, [3])
#define actor_pnodes	ARRAY_(0x00E71180, PACKNODE*, [10])
#define temp_rotation_buffer	ARRAY_(0x00E711C0, short, [160])
#define los_rooms ARRAY_(0x00EEEFC0, short, [20])
#define static_objects ARRAY_(0x00874988, static_info, [70])
#define RopeList ARRAY_(0x00E54CC0, ROPE_STRUCT, [8])
#define lara_matricesF	ARRAY_(0x00E868E0, float, [180])
#define LaraNodeUnderwater	ARRAY_(0x00E862F0, unsigned char, [15])
#define lara_matrices	ARRAY_(0x00E86320, MATRIX3D, [15])
#define aScratchNormals	ARRAY_(0x0057A158, D3DVECTOR, [64])
#define duff_item	ARRAY_(0x00E71300, ITEM_INFO, [10])
#define LaraNodeAmbient	ARRAY_(0x0057A460, long, [2])
#define first_hair	ARRAY_(0x00E5BF60, int, [2])

//defs
#define NO_HEIGHT -32512
#define	NO_ITEM	-1


//unknowns
#define	dword_50A440	VAR_U_(0x0050A440, float)//AlterFOV
#define	flt_55D1F8	VAR_U_(0x0055D1F8, float)//AlterFOV
#define dword_00E916F0	VAR_U_(0x00E916F0, int)//special 1 control, special 2 init, special 3 init, special 4 init


