#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

/* =========================================================================
 * ported by Xpatr0nX
 * original resource: https://github.com/KingOfTheNOPs/ChangeWallpaper-BOF
 * ========================================================================= */
DECLSPEC_IMPORT void BadgerDispatch(WCHAR **dispatch, const char *fmt, ...);

#define BeaconPrintf(type, fmt, ...) BadgerDispatch(dispatch, fmt, ##__VA_ARGS__)
#define CALLBACK_OUTPUT 0x0
#define CALLBACK_ERROR  0x0d

#define MAX_PATH_LENGTH 260

DECLSPEC_IMPORT WINUSERAPI WINBOOL WINAPI USER32$SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
DECLSPEC_IMPORT WINBASEAPI DWORD   WINAPI KERNEL32$GetLastError (VOID);
DECLSPEC_IMPORT size_t    __cdecl MSVCRT$mbstowcs(wchar_t * _Dest, const char * _Source, size_t _MaxCount);

// BRC4 Entrypoint
void coffee(char **argv, int argc, WCHAR **dispatch) {
    WCHAR oldWallPaper[MAX_PATH_LENGTH];
    WCHAR imagePath[MAX_PATH];
    
    const char *input = NULL;

    if (argc < 1) {
        BeaconPrintf(CALLBACK_ERROR, "[-] Usage: coffexec change_wallpaper.o <image_path>\n");
        return;
    }

    input = argv[0];

    MSVCRT$mbstowcs(imagePath, input, MAX_PATH);

    if(USER32$SystemParametersInfoW(SPI_GETDESKWALLPAPER, MAX_PATH_LENGTH, oldWallPaper, 0)) {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Original wallpaper path was: %ls\n", oldWallPaper);
    } else {
        BeaconPrintf(CALLBACK_ERROR, "[-] Error getting current wallpaper: %d\n", KERNEL32$GetLastError());
    }
    
    if(USER32$SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, imagePath, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE )) {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Wallpaper successfully changed to: %ls \n", imagePath);
    } else {
        BeaconPrintf(CALLBACK_ERROR, "[-] Error setting wallpaper: %d\n", KERNEL32$GetLastError());
    }
}
