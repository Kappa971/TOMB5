#pragma once
#include "../global/vars.h"

void inject_dxshell(bool replace);

void DXReadKeyboard(char* KeyMap);
void DXBitMask2ShiftCnt(ulong mask, uchar* shift, uchar* count);
long DXAttempt(HRESULT r);
long DIAttempt(HRESULT r);
void* AddStruct(void* p, long num, long size);
long DXDDCreate(LPGUID pGuid, void** pDD4);
long DXD3DCreate(LPDIRECTDRAW4 pDD4, void** pD3D);
long DXSetCooperativeLevel(LPDIRECTDRAW4 pDD4, HWND hwnd, long flags);
HRESULT __stdcall DXEnumDisplayModes(DDSURFACEDESC2* lpDDSurfaceDesc2, LPVOID lpContext);
HRESULT __stdcall DXEnumZBufferFormats(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
HRESULT __stdcall DXEnumTextureFormats(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
long BPPToDDBD(long BPP);
long DXCreateD3DDevice(LPDIRECT3D3 d3d, GUID guid, LPDIRECTDRAWSURFACE4 surf, LPDIRECT3DDEVICE3* device);
long DXSetVideoMode(LPDIRECTDRAW4 dd, long dwWidth, long dwHeight, long dwBPP);
long DXCreateSurface(LPDIRECTDRAW4 dd, LPDDSURFACEDESC2 desc, LPDIRECTDRAWSURFACE4* surf);
long DXCreateViewport(LPDIRECT3D3 d3d, LPDIRECT3DDEVICE3 device, long w, long h, LPDIRECT3DVIEWPORT3* viewport);
void DXSaveScreen(LPDIRECTDRAWSURFACE4 surf, const char* name);
HRESULT DXShowFrame();
void DXMove(long x, long y);
void DXClose();
long DXCreate(long w, long h, long bpp, long Flags, DXPTR* dxptr, HWND hWnd, long WindowStyle);
long DXChangeVideoMode();
long DXToggleFullScreen();
HRESULT __stdcall DXEnumDirect3D(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext);
BOOL __stdcall DXEnumDirectDraw(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);
BOOL __stdcall DXEnumDirectSound(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
long DXGetInfo(DXINFO* dxinfo, HWND hwnd);
void DXFreeInfo(DXINFO* dxinfo);
void DXJoyAcquisition(long acquire);
void DXSize(long x, long y);
long DXFindTextureFormat(long r, long g, long b, long a);
void FlashLEDs();
long DXFindDevice(long w, long h, long bpp, long hw);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
BOOL CALLBACK EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
long DXUpdateJoystick();

#define DXGetErrorString	( (const char*(__cdecl*)(HRESULT)) 0x0049E050 )
#define DIGetErrorString	( (const char*(__cdecl*)(HRESULT)) 0x0049EFA0 )
#define DXInitInput	( (void(__cdecl*)(HWND, HINSTANCE)) 0x004A2970 )
