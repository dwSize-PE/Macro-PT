void Commands()
{
	//Get Time
	Min1 = (GetTickCount() - Time1) / 1000; //AC
	sec = ((GetTickCount() - Time2) / 1000);
	Min = ((GetTickCount() - Time) / 1000) / 60;
	
	if (Min >= 60)
		Time = GetTickCount();

	if(sec >= 60)
		Time2 = GetTickCount();

	Hour = ((GetTickCount() - Time_2) / 1000) / 60;

	if (GetAsyncKeyState(VK_MENU) < 0)
	{
		if (GetAsyncKeyState(0x31) < 0)
		{
			GetCursorPos(&pos);
			ScreenToClient(hwndPT, &pos);
			potX[cnt] = pos.x;
			potY[cnt] = pos.y;
			cnt++;

			Sleep(200);
		}

		if (GetAsyncKeyState(0x32) < 0)
		{
			if (!bTela)
			{
				sTelaStatus = "On";
				bTela = true, bConsoleUpdate = true;
				Beep(500, 500);
			}
			else
			{
				sTelaStatus = "Off";
				SendMsg(WM_KEYUP, VK_LEFT);
				bTela = false, bConsoleUpdate = true;
				Beep(500, 500);
			}
			Sleep(200);
		}

		//Macro
		if (GetAsyncKeyState(0x4D) < 0)
		{
			if (!bMacro)
			{
				sMacroStatus = "On";
				bConfig = true, cnt2 = 0, bConsoleUpdate = true;
				Beep(500, 500);
			}
			else
			{
				sMacroStatus = "Off";
				bMacro = false, bConsoleUpdate = true;
				Beep(500, 500);
			}
			Sleep(200);
		}
	}
}