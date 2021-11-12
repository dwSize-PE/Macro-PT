//Teste de otimização para ConsoleProject_Cliente

#include "Main.h"

//Caso o usuario feche o console
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		TerminateProcess(hProc, 0);
		CloseHandle(hProc);

		MessageBoxA(0, "Desenvolvido por: dwSize \n\nContato via Discord: dwSize#3592", "", MB_OK | MB_ICONINFORMATION);
		ExitProcess(0);

		return 0;
	}
	return TRUE;
}

int main() {
	srand(time(NULL));

	for (int i = 0; i < 8; i++)
		randstring[i] = randchar[rand() % (strlen(randchar) + 1)];

	SetConsoleTitle(randstring);
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)HandlerRoutine, TRUE);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Variacao, NULL, 0, 0);

	UpdateTime = clock();
	bConsoleUpdate = true;

	void *pNtOpenProcess = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtOpenProcess");

	VirtualProtect(pNtOpenProcess, 5, PAGE_EXECUTE_READWRITE, &Old);
	MoveMemory(lol, pNtOpenProcess, 2);
	VirtualProtect(pNtOpenProcess, 5, Old, &Old);

	while (true)
	{
		Sleep(10);

		if (!bUnhook)
		{
			void* pNtOpenProcess = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtOpenProcess");
			VirtualProtect(pNtOpenProcess, 5, PAGE_EXECUTE_READWRITE, &Old);
			MoveMemory(pNtOpenProcess, lol, 2);
			VirtualProtect(pNtOpenProcess, 5, Old, &Old);
		}

		if (bConsoleUpdate || clock() - UpdateTime > 3000)
		{
			UpdateTime = clock();
			system("cls");
			printf("/------------------------------------------------------------------------------/\n");
			printf("Tempo de jogo -> %.2d:%.2d:%.2d | Desenvolvido por: dwSize\n", Hour / 60, Min, sec); //Captura a quantidade de minutos
			printf("/------------------------------------------------------------------------------/\n");
			cout << sGameStatus;

			GetCursorPos(&pos);
			COLORREF _color = GetPixel(GetDC(0), pos.x, pos.y);
			int _red = GetRValue(_color);
			int _green = GetGValue(_color);
			int _blue = GetBValue(_color);
			cout << _red << endl << _green << endl << _blue;

			if (bCommandsUpdate)
			{
				cout << "/------------------------------------------------------------------------------/\n";
				cout << "[Alt + 1] - Gravar a posicao dos potes" << endl;
				cout << "[Alt + 2] - Girar a tela [ " << sTelaStatus << " ]\n";	
				cout << "------------------------------------------------------------------------------\n";
				cout << "[ALT + M] -> Macro [ " << sMacroStatus << " ]\n\n";
			}

			if (bConfig)
			{
				do
				{
					cout << "------------------------------------------------------------------------------\n";
					cout << "Informe a qtd de teclas para o macro" << endl;
					cin >> teclas_macro;
				} while (teclas_macro < 1 || teclas_macro > 12);

				for (int i = 0; i < teclas_macro; i++)
				{
					cout << "\nInforme o tempo(s) da tecla F" << i + 1 << endl;
					cin >> tempo_teclas[i];
				}

				for (int i = 0; i < teclas_macro; i++)
					Timex[i] = GetTickCount();

				bMacro = true, bConfig = false;
			}
			bConsoleUpdate = false;
		}

		hwndPT = FindWindowA(0, "Priston Tale");

		if (hwndPT > 0)
		{
			if (!bhwndPT)
			{
				sGameStatus = "Game Status -> Janela pega com sucesso!";
				bConsoleUpdate = true, bhwndPT = true;
			}
			else
			{
				GetWindowThreadProcessId(hwndPT, &Pid);

				if (Pid > 0)
				{
					if (!bPid)
					{
						sGameStatus = "Game Status -> ID do processo pego com sucesso!";
						bConsoleUpdate = true, bPid = true;
					}
					else
					{
						if (!bhProc)
						{
							hProc = OpenProcess(PROCESS_TERMINATE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, Pid);

							if (hProc == 0)
								sGameStatus = "Game Status -> Erro ao obter acesso a memoria!";
							else
							{
								sGameStatus = "Game Status -> Acesso a memoria concedido!";
								bConsoleUpdate = true, bUnhook = true, bhProc = true;
							}
						}
						else
						{
							Bypass();

							psinChar = ReadMem(sinChar, 4);

							for (int i = 0; i < 3; i++)
							{
								currBarra[0] = ReadMem(psinChar + 0x124, 2) ^ ReadMem(CodeXorLife, 2);
								currBarra[i + 1] = ReadMem(psinChar + 0x128 + (0x4 * i), 2);
								totalBarra[i] = ReadMem(psinChar + 0x126 + (0x4 * i), 2);
							}

							if (bSearchAddr && bBypassSucess)
							{
								if (!bGetTime)
								{
									Hour = 0, Min = 0, Time = 0, Time_2 = 0, Time2 = 0;;

									Time = GetTickCount();
									Time_2 = GetTickCount();
									Time2 = GetTickCount();
									bGetTime = true;
								}

								if (ReadMem(psinChar - 0x1D0, 4) > 0)
								{
									//if (!b)
									//{
									Commands();
									sGameStatus = "Game Status -> Funcoes Liberadas, aproveite!\n";

									bCommandsUpdate = true;
									/* }
									else
									{
										sGameStatus = "Game Status -> Acesso negado, usuario nao cadastrado!\n";

										if (clock() - UpdateTime_Exit > 5000)
										{
											UpdateTime_Exit = clock();

											ExitProcess(0);
										}
									}*/
								}
								else
								{
									//ID
									//if (ReadMem(SockLogin, 4) > 0)
									//	b = Protect();

									sGameStatus = "Game Status -> Aguardando login ingame..\n";

									UpdateTime_Exit = clock();
									bGetTime = false, bMacro = false, bTela = false;
									sMacroStatus = "Off", sTelaStatus = "Off";
								}
							}
							else if (bBypassFail && bSearchAddr)
								//sGameStatus = "Game Status -> Erro ao realizar a varredura. \n\nDescricao: Isso pode ter sido causado devido a uma atualizacao do ZForce ou o hack foi aberto com o Priston Tale ja em execucao. \n\nTente novamente. Se o problema persistir, entre em contato com o desenvolvedor.";
								sGameStatus = "Periodo de teste expirado. Entre em contato com o desenvolvedor.";
						}
					}
				}
				else
					sGameStatus = "Game Status -> Erro ao obter o ID do processo!";
			}
		}
		else
		{
			if (hProc != 0)
			{
				CloseHandle(hProc);
				hProc = 0, Pid = 0, AlocAddr = 0;
			}
			else
			{
				sGameStatus = "Game Status -> Aguardando Priston Tale ser aberto\n\n";
				bhProc = false, bhwndPT = false, bPid = false, bUnhook = false, bSearchAddr = false, bBypassFail = false, bBypassSucess = false;
			}
		}
	}

	return 0;
}