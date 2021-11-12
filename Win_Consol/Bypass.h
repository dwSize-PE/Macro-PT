void Bypass()
{
	if (!bSearchAddr)
	{
		//Reference
		HookMana = AoBScan((byte*)"\x40\x8D\x1C\xC5", 0xFF000) + 0x158;
		SubLife = AoBScan((byte*)"\x5d\xc3\x0f\xb7\x46\x16", 0x125000) - 0x6D; //PlayAttack

		if (ReadMem(HookMana - 0x2, 2) == 0x25FF && ReadMem(SubLife - 0x1, 1) == 0x15)
			bSearchAddr = true;
		else
			bBypassFail = true, bSearchAddr = true;
	}
	else if (bBypassFail == false)
	{
		if (!bBypassSucess)
		{
			AlocAddr = VirtualAllocEx(hProc, 0, 100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			Beep(500, 500);
			bBypassSucess = true;
		}
	}
}