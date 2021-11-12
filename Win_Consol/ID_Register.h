char ID_Login[20], ID_Login2[3][20];
void *AlocAddr = 0;

byte ID[][28] = { "\x78\x72\x65\x79\x79", "\x73\x61\x6B\x61\x6F", "\x7A\x6F\x77\x65\x31\x32\x33", "\x61\x73\x61\x77\x65\x6C\x6C\x32\x38"}; //coxodinde3

BOOL Protect()
{
	ReadProcessMemory(hProc, (void*)String_UserID, ID_Login, strlen(ID_Login) + 1, NULL);

	for (int i = 0; i < 4; i++)
	{
		WriteMem((DWORD)AlocAddr + (i * 0x15), ID[i], sizeof(ID[i]));
		ReadProcessMemory(hProc, (void*)((DWORD)AlocAddr + (i * 0x15)), ID_Login2[i], strlen(ID_Login2[i]) + 1, NULL);

		if (!strcmp(ID_Login, ID_Login2[i]))
		{
			return true;
			break;
		}
	}
	return false;
}