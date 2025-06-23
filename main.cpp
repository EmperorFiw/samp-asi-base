
#include "main.h"

HANDLE g_DllHandle;
DWORD g_SAMP = NULL;

void WriteLog(const char* message)
{
	FILE* logFile = fopen("Emperor.log", "w");
	if (logFile)
	{
		fprintf(logFile, "%s\n", message);
		fclose(logFile);
	}
}

void MainThread()
{
	while (g_SAMP == NULL)
	{
		g_SAMP = (DWORD)GetModuleHandle("samp.dll");
		Sleep(1000);
	}

	WriteLog("ASI Loaded.");
	while (true)
	{
		// Ex. Infinity Run
		if (GetAsyncKeyState(VK_F3) & 1) // F3 
		{
			bool* bInfiniteRun = (bool*)0xB7CEE4;
			if (!*bInfiniteRun)
			{
				*(BYTE*)0x969170 = 1;

				WriteLog("Infinite Run Activated.");
			}
			else
			{
				*(BYTE*)0x969170 = 0;
				WriteLog("Infinite Run Deactivated.");
			}
		}
		Sleep(100);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, NULL);
	return TRUE;
}

