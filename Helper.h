#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

PROCESS_INFORMATION pInfo;
STARTUPINFO sInfo;

//  INPUT BUFFERS
char PATH[1024]{};
char PARAMS[512]{};
char DLL[1024]{};

char* GetInput(char* Input)
{
    fgets(Input, 256, stdin);
    if ((strlen(Input) > 0) && (Input[strlen(Input) - 1] == '\n'))
        Input[strlen(Input) - 1] = '\0';
    return Input;
}

const wchar_t* Char2WChar(const char* in)
{
    if (in == NULL) {
        wchar_t* Out = NULL;
        return Out;
    }
    wchar_t* Out = new wchar_t[strlen(in) + 1];
    mbstowcs_s(NULL, Out, strlen(in) + 1, in, strlen(in));
    return Out;
}

bool Inject(HANDLE Process, const char* PATH)
{
    void* addr = VirtualAllocEx(Process, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(Process, addr, PATH, strlen(PATH) + 1, 0);
    HANDLE hThread = CreateRemoteThread(Process, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, addr, 0, 0);
    if (!hThread) {
        VirtualFreeEx(Process, addr, 0, MEM_RELEASE);
        return FALSE;
    }
    CloseHandle(hThread);
    return TRUE;
}

int exit(const char* Text)
{
    printf(Text);
    Sleep(2000);
    memset(PATH, 0, 1024);
    memset(PARAMS, 0, 512);
    memset(DLL, 0, 1024);
    return EXIT_SUCCESS;
}