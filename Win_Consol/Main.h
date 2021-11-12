#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windowsx.h>

#pragma comment(lib, "User32.lib") //Solução de erro GetAsyncKeyState
#pragma comment(lib, "Gdi32.lib")

using namespace std; //Comando cout

char randstring[50];
char randchar[] = {
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz" };

HWND hwndPT = 0;
DWORD Pid = 0;
HANDLE hProc = 0;

DWORD Old;
bool bUnhook;
byte lol[2];
bool b;

//Source.cpp
bool bConsoleUpdate, bCommandsUpdate, bhwndPT, bPid, bhProc;
std::string sGameStatus, sMacroStatus, sTelaStatus;

//Pointer
int psinChar;

//Get Time
int UpdateTime, UpdateTime_Exit, Hour = 0, Min = 0, Time = 0, Time_2 = 0, Min1 = 0, Time1 = 0;
bool bGetTime;

//Bypass.h
bool bSearchAddr, bBypassSucess, bBypassFail;
int SubLife, HookMana;

//Hotkeys.h
bool bMacro, bConfig, bTela;
int teclas_macro, cnt = 0, cnt2 = 0;
DWORD tempo_teclas[12], Timex[12], secx[12], posPot[3][3], currBarra[3], totalBarra[3];
RECT lpRect;
POINT pos;

int sec;
int Time2 = 0;

//Global Functions
void WriteMem(DWORD Addr, byte* Value, int size);
DWORD ReadMem(DWORD Addr, int size);

#include "Addr.h"
#include "Api.h"
#include "Hotkeys.h"
#include "Thread.h"
#include "ID_Register.h"
#include "Bypass.h"