void Variacao()
{
	while (true)
	{
		Sleep(10);

		if (bTela)
			SendMsg(WM_KEYDOWN, VK_LEFT);

		if (bMacro)
		{
			GetWindowRect(hwndPT, &lpRect);
			SendMsg(WM_MOUSEMOVE, 0, MAKELPARAM((lpRect.right - lpRect.left) / 2, (lpRect.bottom - lpRect.top) / 2), 700); //Move o mouse para o CenterScreen
			
			if (sec >= 57)
			{
				SendMsg(WM_MOUSEMOVE, 0, MAKELPARAM((lpRect.right - lpRect.left), lpRect.top, 300));
				for (int i = 0; i < 10; i++)
					SendMsg(WM_LBUTTONDOWN);
				Sleep(100);
				SendMsg(WM_LBUTTONUP);
			}

			//Loop das skills
			for (int i = 0; i < teclas_macro; i++)
			{
				secx[i] = ((GetTickCount() - Timex[i]) / 1000); //Get time

				if (secx[i] >= tempo_teclas[i] || cnt2 == 0)
				{
					if (tempo_teclas[i] > 0)
						SendMsg(WM_MOUSEMOVE, 0, MAKELPARAM((lpRect.right - lpRect.left), lpRect.top, 300));

					SendMsg(WM_KEYDOWN, 0x70 + i, 0, 300); //Pressiona a tecla
					SendMsg(WM_KEYUP, 0x70 + i); //Solta a tecla

					SendMsg(WM_RBUTTONDOWN, 0, 0, 300); //Pressiona o botão do mouse
					SendMsg(WM_RBUTTONUP); //Solta o botão do mouse

					//Tempo até a próxima iteração
					Sleep(1000);
					Timex[i] = GetTickCount(); //Reseta o time

					if (i == (teclas_macro - 1))
						cnt2++;
				}
			}

			//Loop dos pote
			for (int i = 0; i < 3; i++)
			{
				if (currBarra[i] < totalBarra[i] / 2)
				{
					SendMsg(WM_MOUSEMOVE, 0, MAKELPARAM(potX[i], potY[i]), 100);
					SendMsg(WM_RBUTTONDOWN, 0, 0, 300);
					SendMsg(WM_RBUTTONUP, 0, 0, 300);
				}
			}
		}
	}
}