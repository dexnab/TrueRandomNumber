//Just call teTrueRand();

#pragma once
#include <Windows.h>
#include <time.h>

#pragma optimize( "", off )

//This determines the time consumed to generate a new random number
//The greater this is, the greater randomness the random number will has
#define RNG_LOOPTIME 10

volatile unsigned int g_nRandGenBuf1 = 0;
volatile unsigned int g_nRandGenBuf2 = 0;
volatile BOOL g_iContinue = TRUE;

//Call this function to get a rand number
int teTrueRand();
int im_teTrueRand();
DWORD WINAPI RNGProc(LPVOID lpParam);

int teTrueRand()
{
	int nTRNG;
	int nSeed;
	int nRan;

	nTRNG = im_teTrueRand();
	nSeed = nTRNG ^ time(0);
	srand(nSeed);
	nRan = rand();

	return nRan;
}

int im_teTrueRand()
{
	HANDLE hThread[2];
	int nTRN = 0;

	//Reset
	g_nRandGenBuf1 = 0;
	g_nRandGenBuf2 = 0;
	g_iContinue = TRUE;

	//Create 2 threads
	hThread[0] = CreateThread(NULL, NULL, RNGProc, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, NULL, RNGProc, NULL, 0, NULL);

	//Wait for 1s for adding
	Sleep(RNG_LOOPTIME);

	//Close thread
	g_iContinue = FALSE;
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	nTRN = g_nRandGenBuf1 - g_nRandGenBuf2;
	if ((nTRN) >= 0) return nTRN;
	else return -nTRN;
}

DWORD WINAPI RNGProc(LPVOID lpParam)
{
	while (g_iContinue)
	{
		g_nRandGenBuf1++;
		g_nRandGenBuf2++;
	}
	return 0;
}

#pragma optimize( "", on )