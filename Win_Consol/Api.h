DWORD GetPid()
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapShot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapShot, &pe32))
		{
			do {
				std::string full_name(pe32.szExeFile);
				if (full_name.find(".exe ") != -1)
				{
					CloseHandle(hSnapShot);
					return pe32.th32ProcessID;
				}
			} while (Process32Next(hSnapShot, &pe32));
		}CloseHandle(hSnapShot);
	}
	return 0;
}

DWORD pPid = 0;

DWORD GetPid_(char szProcName[])
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapShot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapShot, &pe32))
		{
			do
			{
				if (!strcmp(pe32.szExeFile, szProcName))
				{
					pPid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapShot, &pe32));
		}

		if (pPid == pe32.th32ParentProcessID)
			pPid = pe32.th32ProcessID;
	}
	CloseHandle(hSnapShot);
	return pPid;
}

void HookFunc(DWORD Func, DWORD MyFunc, int Call = 0, byte* Value = 0, unsigned int size = 0) 
{
	int Hook = DWORD(Func) - DWORD(MyFunc) - 5;

	if(Call > 0)
		WriteProcessMemory(hProc, (void*)MyFunc, &Call, 1, NULL);
	WriteProcessMemory(hProc, (void*)(MyFunc + 1), &Hook, sizeof(Hook), NULL);

	if (Value != NULL)
		WriteProcessMemory(hProc, (void*)(MyFunc + 5), Value, size, NULL);
}

void SendMsg(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0, int Time = 0)
{
	SendMessageA(hwndPT, Msg, wParam, lParam);
	Sleep(Time);
}

DWORD AoBScan(byte *Reference, int size)
{
	void *pData = 0;
	MEMORY_BASIC_INFORMATION mbi;

	int Addr_Start = 0x07000000;
	pData = malloc(0x7FFFFF);

	if (pData != 0)
	{
		while(true)
		{
			VirtualQueryEx(hProc, (void*)Addr_Start, &mbi, sizeof(mbi));

			if (mbi.RegionSize != size)
				Addr_Start += mbi.RegionSize;
			else
			{
				ReadProcessMemory(hProc, (void*)Addr_Start, pData, size, NULL);

				for (int i = 0; i < size; i++)
					if (*(DWORD*)(DWORD(pData) + i) == *(DWORD*)Reference)
						return Addr_Start + i;
				break;
			}
		}
	}

	free(pData);
	return 0;
}

void WriteMem(DWORD Addr, byte* Value, int size)
{
	WriteProcessMemory(hProc, (void*)Addr, Value, size, NULL);
}

void WriteWord(DWORD Addr, int Value)
{
	WriteProcessMemory(hProc, (void*)Addr, &Value, 2, NULL);
}

void WriteDword(DWORD Addr, int Value)
{
	WriteProcessMemory(hProc, (void*)Addr, &Value, 4, NULL);
}

DWORD ReadMem(DWORD Addr, int size)
{
	DWORD Buffer = 0;
	ReadProcessMemory(hProc, (void*)Addr, &Buffer, size, NULL);
	return Buffer;
}

void CallFunc(DWORD Addr, int Value = 0)
{
	HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)Addr, &Value, 0, 0);
	CloseHandle(hThread);
}