#include "Helper.h"

int main()
{
    //  ESTABLISH PROCESS PATH
    printf("PROCESS PATH: ");
    GetInput(PATH);

    //  DEFINE LAUNCH PARAMS
    printf("PROCESS PARAMS: ");
    GetInput(PARAMS);

    //	GET DLL PATH
    printf("DLL PATH: ");
    GetInput(DLL);

    system("cls");

    //	DEBUG PRINT
    printf("SELECTED PROCESS: %s\n", PATH);
    printf("PROCESS PARAMS: %s\n", PARAMS);
    printf("SELECTED DLL: %s\n", DLL);

    //  ALLOC MEMORY
    ZeroMemory(&sInfo, sizeof(sInfo));
    sInfo.cb = sizeof(sInfo);
    ZeroMemory(&pInfo, sizeof(pInfo));

    //  CREATE PROCESS
    if (!CreateProcessW(Char2WChar(PATH), (LPWSTR)PARAMS, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        printf("[!] CREATE PROCESS FAILED!\n[!] ERROR CODE: (%d)\n", GetLastError());
        Sleep(5000);
        return exit("[!] Exiting . . .\n");
    }

    //  INJECT
    if (!Inject(pInfo.hProcess, DLL)) {
        MessageBoxA(NULL, "FAILED TO INJECT INTO PROCESS!\n\nTROUBLESHOOTING TIPS:\n[1] double check the dll path\n[2] Make sure you have placed the dll in the correct path 'DLL\PATH\DLLNAME.dll'\n", "ERROR", MB_ICONERROR);
        TerminateProcess(pInfo.hProcess, EXIT_FAILURE);
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
        return exit("[!] Exiting . . .\n");
    }

    //  EXIT
    return exit("SUCCESS, EXITING");
}