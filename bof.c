#include <windows.h>
#include "beacon.h"


typedef int (WINAPI *MESSAGEBOXA)(HWND, LPCSTR, LPCSTR, UINT);

void go(char *args, int len) {

    datap parser;
    char* message = NULL;

    HMODULE user32_dll = LoadLibraryA("user32.dll");
    if (user32_dll == NULL) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to load user32.dll, please check whether this exists in Sys32.");
        return;
    }

    BeaconDataParse(&parser, args, len);

    message = BeaconDataExtract(&parser, NULL);

    MESSAGEBOXA pMessageBoxA = (MESSAGEBOXA)GetProcAddress(user32_dll, "MessageBoxA");
    if (pMessageBoxA == NULL) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to resolve MessageBoxA");
        return;
    }

    if (message == NULL || strlen(message) == 0)
    {
        message = "Default Message, no Argument Provided.";
    }
    pMessageBoxA(NULL, message, "BOF Message", MB_OK | MB_ICONINFORMATION);
    
    FreeLibrary(user32_dll);
}