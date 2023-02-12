#pragma once
#include "types.h"
#include "math_tbls.h"

// Variable macros
#define VAR_(address, type)			(*(type*)(address)) // uninitialized variable
#define ARRAY_(address, type, length)	(*(type(*)length)(address)) // array (can be multidimensional)

//vars
#define old_lara_holster VAR_(0x00E7EFE0, ushort)
#define GotLaraSpheres	VAR_(0x00E51F2E, char)
#define LaraDrawType	VAR_(0x00EEEAD0, char)
#define WeatherType	VAR_(0x00EEF4A0, char)
#define GameTimer	VAR_(0x00E5C27C, ulong)
#define savegame	VAR_(0x00E52EC0, SAVEGAME_INFO)
#define	cheat_hit_points	VAR_(0x00E5BBF8, short)
#define	GLOBAL_oldcamtype	VAR_(0x00E711AC, camera_type)
#define bDoCredits	VAR_(0x0051CE35, uchar)
#define num_fmvs	VAR_(0x0051CE25, char)
#define	baddie_slots	VAR_(0x00E5B834, CREATURE_INFO*)
#define GnFrameCounter	VAR_(0x00E4B0FC, ulong)
#define HKTimer	VAR_(0x0051CEC9, char)
#define HKShotsFired	VAR_(0x0051CEC8, char)
#define KeyCount	VAR_(0x0086BA48, long)
#define boxes	VAR_(0x00EEFB64, BOX_INFO*)
#define SubHitCount	VAR_(0x0051CEE4, char)
#define subsuit	VAR_(0x00E5B850, SUBSUIT_INFO)
#define OldPickupPos	VAR_(0x00E59700, PHD_VECTOR)
#define CurrentSequence	VAR_(0x00E4EA61, uchar)
#define camera_pnodes	VAR_(0x00E7EE9C, PACKNODE*)
#define GLaraShadowframe	VAR_(0x00E86300, short*)
#define LiftDoor	VAR_(0x0051CB40, char)
#define GlobalSoftReset	VAR_(0x00E5C2F8, long)
#define GlobalAlpha	VAR_(0x00506D3C, long)
#define current_item	VAR_(0x009158A8, ITEM_INFO*)
#define aGlobalSkinMesh	VAR_(0x00921680, long)
#define nRope VAR_(0x0051CA60, long)
#define CurrentPendulum VAR_(0x00EEF020, PENDULUM)
#define NullPendulum VAR_(0x0051CFD0, PENDULUM)
#define GlobalAmbient	VAR_(0x0092167C, long)
#define dbm_command	VAR_(0x00E4ACB4, ulong)
#define dbm_clearlog	VAR_(0x00E4ACAC, ulong)
#define GLOBAL_resident_depack_buffers	VAR_(0x00E7EFDC, char*)
#define lastcamnum	VAR_(0x00E711A8, long)
#define next_debris	VAR_(0x0051CA8C, long)
#define GlobalPulleyFrigItem	VAR_(0x00E5BF24, short)
#define cd_drive	VAR_(0x00874960, char)
#define clipflags	VAR_(0x00D9AB34, short*)
#define outside	VAR_(0x00E6CAF8, long)
#define torchroom	VAR_(0x00507AB0, short)
#define NotHitLaraCount VAR_(0x0051D0A4, char)
#define credits_timer	VAR_(0x0051064C, long)
#define CurrentRoom	VAR_(0x00E6D754, long)
#define snow_outside	VAR_(0x00E6CAE8, long)
#define NumSpecialFeatures	VAR_(0x008FBD9C, long)
#define SpecialFeaturesNum	VAR_(0x00517B28, long)
#define default_font_height	VAR_(0x00E4DC40, long)
#define SGcount	VAR_(0x0051CFFC, long)
#define SGpoint	VAR_(0x0051CFF8, char*)
#define FmvSceneTriggered	VAR_(0x00EEEAD8, long)
#define samples_buffer	VAR_(0x0086BEDC, char*)
#define slots_used	VAR_(0x0051CEE8, long)
#define number_boxes	VAR_(0x00EEFB68, long)
#define skelly_backgunbak	VAR_(0x00E6D732, short)
#define skelly_rhandbak	VAR_(0x00E6D840, short*)
#define skelly_lhandbak	VAR_(0x00E6D828, short*)
#define rain_count	VAR_(0x00D6866C, short)
#define max_rain	VAR_(0x00C713D8, short)
#define snow_count	VAR_(0x00C713D0, short)
#define max_snow	VAR_(0x00C717E4, short)
#define FPCW	VAR_(0x00878654, short)
#define save_counter	VAR_(0x008786EC, long)
#define num_level_meshes	VAR_(0x007DFFE4, long)
#define DoFade	VAR_(0x00C87BF0, long)
#define FadeVal	VAR_(0x00C86BE8, long)
#define FadeStep	VAR_(0x00C713D4, long)
#define FadeCnt	VAR_(0x00C713DC, long)
#define FadeEnd	VAR_(0x00C713E0, long)
#define resChangeCounter	VAR_(0x00D9AD9C, long)
#define start_setup	VAR_(0x0057A098, bool)
#define fmvs_disabled	VAR_(0x0057A099, bool)
#define targetMeshP	VAR_(0x00E6E460, MESH_DATA*)
#define binocsMeshP	VAR_(0x00E6D744, MESH_DATA*)
#define num_boxes	VAR_(0x00EEFB68, long)
#define overlap	VAR_(0x00EEFB5C, ushort*)

//arrays
#define	weapons	ARRAY_(0x005085B0, WEAPON_INFO, [9])
#define inventry_objects_list	ARRAY_(0x00508E38, INVOBJ, [100])

//defs
#define NO_HEIGHT -32512
#define	NO_ITEM	-1
#define NO_ROOM	255
#define MAX_ITEMS	256
#define MAX_SAMPLES	450
#define FVF (D3DFVF_TEX2 | D3DFVF_SPECULAR | D3DFVF_DIFFUSE | D3DFVF_XYZRHW)
#define MALLOC_SIZE	5000000		//5MB
#define WINDOW_STYLE	(WS_OVERLAPPED | WS_BORDER | WS_CAPTION)
