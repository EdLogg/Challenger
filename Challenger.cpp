// Challenger.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#define MAX_LOADSTRING	100
#define SOLVE_SPEED		500						// speed in milliseconds
#define PERTURBATION_SPEED	750					// speed in milliseconds
#define GUESS_SPEED		750						// speed in milliseconds
#define GUESS_INVALID	2000					// speed in milliseconds

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP hBackgnd = NULL;
HBITMAP hFont = NULL;
HBITMAP hEvals = NULL;
HBITMAP hShaded = NULL;
HBITMAP hFontLock = NULL;
HBITMAP hFontOn = NULL;
HBITMAP hFontError = NULL;

RECT TryRect = { 0, 35, 290, 72 };
RECT StateRect = { 0, 52, 290, 72 };
char* stateString[STATE_END] =
{
	"Enter Totals",
	"Enter Puzzle",
	"Step",
	"Wait",
	"Solve",
	"Solutions",
	"Done",
	"Equations",
	"Perturbation",
	"Perturbation Failed",
	"Guess",
	"Guess Failed",
};

U32 dialogSeed;
bool startTest;
int testCount;
int totalX[10] = { 304, 304, 304, 304, 304, 304, 224, 152, 80, 8 };
int totalY[10] = { 8, 80, 152, 224, 296, 376, 376, 376, 376, 376 };
int puzzleX[4] = { 8, 80, 152, 224 };
int puzzleY[4] = { 80, 152, 224, 296 };
RECT TextRect = { 0, 0, 290, 72 };
char variables[MAX_VARIABLES + 2] = { 0, 0, 'a', 'b', 'c', 'd', 'e', 'f' };
// background is 376x448 with 64x64 openings
static RECT	NoRect = { 4, 4, 370, 440, };		// smaller rect to prevent background draw


//***********************************************************************
//*** Center the second window in relation to the desktop ***************
//***********************************************************************
void CenterWindow(HWND CW_h2)
{
	RECT CW_rect1, CW_rect2;
	int CW_midx, CW_midy, CW_wx, CW_wy;
	HWND CW_h1;

	CW_h1 = GetDesktopWindow();
	GetWindowRect(CW_h1, &CW_rect1);
	GetWindowRect(CW_h2, &CW_rect2);
	CW_midx = (CW_rect1.right + CW_rect1.left) >> 1;
	CW_midy = (CW_rect1.bottom + CW_rect1.top) >> 1;
	CW_wx = CW_rect2.right - CW_rect2.left;
	CW_wy = CW_rect2.bottom - CW_rect2.top;
	MoveWindow(CW_h2, CW_midx - (CW_wx >> 1), CW_midy - (CW_wy >> 1), CW_wx, CW_wy, false);
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


bool AllResolved()
{
	for (int i = 0; i < 10; i++)
		if (resolved[i] == false)
			return false;
	return true;
}


void EnterState(HMENU hMenu, STATE newState)
{
	STATE oldState = state;
	state = newState;

	switch (state)
	{
	case STATE_ENTER_TOTALS:
		equationOrderIndex = 0;
		exclusions = 0;							// do not exclude any perturbations
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_CREATE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_TEST, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_ENTER_PUZZLE:
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_WAIT:
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_SOLUTIONS:
		if (PuzzleComplete())
		{
			state = STATE_DONE;
			goto DONE;
		}
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_DONE:
DONE:	for (int i = 0; i < 10; i++)							// in case we came from the equations
			resolved[i] = true;
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_EQUATIONS:
		StartEquations();
		SetNextEquation(false);
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_EQUATIONS_FAILED:
		strncat(equationString0, " Failed!", sizeof(equationString0) - 1);
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	case STATE_GUESS:
#if DEBUG_PERTURBATIONS
		DeleteFile("perturbations.txt");		// delete any existing file
#endif
		solutionsSave = solutions;
		for (int y = 0; y < 4; y++)				// save min and max in case guess failed
		{
			for (int x = 0; x < 4; x++)
			{
				minSave[y][x] = min[y][x];
				maxSave[y][x] = max[y][x];
			}
		}
	case STATE_PERTURBATION:
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_GRAYED);
		break;
	case STATE_GUESS_FAILED:
		exclusions++;			// add the exclusion
	case STATE_PERTURBATION_FAILED:
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_ENABLED);
		break;
	default:
		if (oldState == STATE_ENTER_PUZZLE)
		{
			// save old puzzle
			EnableMenuItem(hMenu, IDM_RESTART, MF_BYCOMMAND | MF_ENABLED);
			for (int n = 0; n < 4; n++)
				for (int m= 0; m < 4; m++)
					restart[n][m] = puzzle[n][m];
		}
		EnableMenuItem(hMenu, IDM_HFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_VFLIP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIP1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX0, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX1, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX2, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FLIPX3, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_STEP, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_SOLVE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GUESS, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PERTURBATION, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_LOAD, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_FILE_SAVE, MF_BYCOMMAND | MF_GRAYED);
		break;
	}
}


void PerturbationStep(HWND hWnd, HMENU hMenu)
{
	int res = NextPerturbation(false, false);
	if (res < 0)
	{
		equationString[0] = 0;
		KillTimer(hWnd, IDT_SOLVETIMER);
		EnterState(hMenu, STATE_PERTURBATION_FAILED);
	}
	else if (res == 0)							// we are done
	{
		equationString[0] = 0;
		KillTimer(hWnd, IDT_SOLVETIMER);
		if (PuzzleComplete())
			EnterState(hMenu, STATE_DONE);
		else
		{
			SolvePuzzle(hWnd);					// recalculate number of solutions
			EnterState(hMenu, STATE_SOLUTIONS);
		}
	}
}


void EquationStep(HWND hWnd, HMENU hMenu)
{
	if (SetNextEquation(false) == false)		// we are done
	{
		// resolve all totals because they must be correct
		for (int i = 0; i < 10; i++)
			resolved[i] = true;
		EquationOrderIncrease();				// try next equation order
		if (PuzzleComplete())
			EnterState(hMenu, STATE_DONE);
		else 
			EnterState(hMenu, STATE_SOLUTIONS);
	}
	else if (equationString0[0] != 0			// we are making a guess
	&& InvalidMinMax())							// an error occurred
	{
 		EnterState(hMenu, STATE_EQUATIONS_FAILED);		
		SetTimer(hWnd, IDT_SOLVETIMER, GUESS_SPEED, (TIMERPROC)NULL);
	}
}


void DrawPuzzle(HWND hWnd, HDC hdc, bool drawBackgnd)
{
	BITMAP bm;

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBackgnd);				// select new object and save the old
	if (drawBackgnd)
	{
		GetObject(hBackgnd, sizeof(bm), &bm);								// get blit info
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		switch (state)
		{
		case STATE_ENTER_TOTALS:
			DrawText(hdc, "Enter totals.\nPress Enter for next entry.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_ENTER_PUZZLE:
			DrawText(hdc, "Enter puzzle entries.\nUse cursor or arrow keys to select entry.\nPress Enter to solve.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_STEP:
			DrawText(hdc, "Iterate once step.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_WAIT:
			DrawText(hdc, "Press Enter to Solve\nor Space to make one step.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_SOLVE:
			DrawText(hdc, "Solving", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_PERTURBATION:
			DrawText(hdc, "Guessing using a minimum perturbation.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_PERTURBATION_FAILED:
			DrawText(hdc, "Perturbation guess has failed!\nTry another location.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_GUESS:
			DrawText(hdc, "Guessing using a minimum perturbation.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_GUESS_FAILED:
			DrawText(hdc, "This guess has failed!\nSo we will remove the inital guess\nand you can try solving again.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_SOLUTIONS:
		{
				char string[64];
				sprintf(string, "There is %d solution(s).\nEnter digit to continue.", solutions);
				DrawText(hdc, string, -1, &TextRect, DT_CENTER | DT_VCENTER);
				break;
			}
		case STATE_DONE:
			DrawText(hdc, "Puzzle Solved!", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_EQUATIONS_FAILED:
			DrawText(hdc, "This guess has failed!\nThe min or max will be adjusted.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		case STATE_EQUATIONS:
			DrawText(hdc, "Press Enter for equations\nor Space to make one step.", -1, &TextRect, DT_CENTER | DT_VCENTER);
			break;
		default:
			break;
		}
#if DEBUG_STATES
		if (state != STATE_EQUATIONS && state != STATE_EQUATIONS_FAILED)
			DrawText(hdc, stateString[state], -1, &StateRect, DT_CENTER | DT_VCENTER);
#endif
#if DISPLAY_EQUATIONS
		if (state == STATE_EQUATIONS || state == STATE_EQUATIONS_FAILED)
		{
			DrawText(hdc, equationString0, -1, &TryRect, DT_CENTER | DT_VCENTER);
			DrawText(hdc, equationString, -1, &StateRect, DT_CENTER | DT_VCENTER);
		}
		else if (state == STATE_PERTURBATION || state == STATE_PERTURBATION_FAILED)
		{
			DrawText(hdc, equationString, -1, &StateRect, DT_CENTER | DT_VCENTER);
		}
		else if (state == STATE_GUESS || state == STATE_GUESS_FAILED)
		{
			DrawText(hdc, equationString, -1, &StateRect, DT_CENTER | DT_VCENTER);
		}
#endif
	}

	// display totals
	for (int i = 0; i < 10; i++)
	{
		if ((state == STATE_SOLUTIONS || state == STATE_PERTURBATION_FAILED || state == STATE_GUESS_FAILED)
		&&  ValidTotal(i) == false)
			SelectObject(hdcMem, hFontError);
		else if (resolved[i])
			SelectObject(hdcMem, hFontLock);
		else
			SelectObject(hdcMem, hFont);
		BitBlt(hdc, totalX[i], totalY[i], 64, 64, hdcMem, 64 * totals[i], 0, SRCCOPY);	// blit into new memory
	}

	// display puzzle
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (min[i][j] == max[i][j])
			{
				SelectObject(hdcMem, hFont);
				BitBlt(hdc, puzzleX[j], puzzleY[i], 64, 64, hdcMem, 64 * min[i][j], 0, SRCCOPY);
			}
			else if (min[i][j] < max[i][j])
			{
				SelectObject(hdcMem, hEvals);
				if (showValidRanges
				&& (state == STATE_SOLUTIONS
				  || state == STATE_EQUATIONS))
				{
					if (solutionMin[i][j] > min[i][j])
						SelectObject(hdcMem, hShaded);
					else
						SelectObject(hdcMem, hEvals);
					BitBlt(hdc, puzzleX[j], puzzleY[i], 32, 64, hdcMem, 64 * max[i][j], 64 * min[i][j], SRCCOPY);
					if (solutionMax[i][j] < max[i][j])
						SelectObject(hdcMem, hShaded);
					else
						SelectObject(hdcMem, hEvals);
					BitBlt(hdc, puzzleX[j] + 32, puzzleY[i], 32, 64, hdcMem, 64 * max[i][j] + 32, 64 * min[i][j], SRCCOPY);
					SelectObject(hdcMem, hEvals);
				}
				else 
					BitBlt(hdc, puzzleX[j], puzzleY[i], 64, 64, hdcMem, 64 * max[i][j], 64 * min[i][j], SRCCOPY);
			}
		}
	}

	// display equations
	if (state == STATE_EQUATIONS || state == STATE_EQUATIONS_FAILED)
	{
		for (int i = 0; i < 4; i++)
		{
			char string[20], str[10];
			for (int j = 0; j < 4; j++)
			{
				if (equations[i][j][0] > 0)
				{
					string[0] = 0;
					for (int v = 1; v < MAX_VARIABLES + 2; v++)
					{
						if (equations[i][j][v] != 0)
						{
							if (equations[i][j][v] == -1)
							{
								if (v == 1)
									snprintf(str, sizeof(str), "-1");
								else
									snprintf(str, sizeof(str), "-%c", variables[v]);
								strncat(string, str, strlen(str));
							}
							else if (equations[i][j][v] == 1)
							{
								if (v == 1)
									snprintf(str, sizeof(str), "1");
								else if (strlen(string) == 0)
									snprintf(str, sizeof(str), "%c", variables[v]);
								else
									snprintf(str, sizeof(str), "+%c", variables[v]);
								strncat(string, str, strlen(str));
							}
							else
							{
								if (strlen(string) == 0  && equations[i][j][v] > 0)
									snprintf(str, sizeof(str), "%d%c", equations[i][j][v], variables[v]);
								else 
									snprintf(str, sizeof(str), "%+d%c", equations[i][j][v], variables[v]);
								strncat(string, str, strlen(str));
							}
						}
					}
					RECT EquationRect;
					EquationRect.left = puzzleX[j];
					EquationRect.top = puzzleX[i] + 120;
					EquationRect.right = EquationRect.left + 64;
					EquationRect.bottom = EquationRect.top + 20;
					DrawText(hdc, string, -1, &EquationRect, DT_CENTER | DT_VCENTER);
				}
			}
		}
	}

	// display active entry
	SelectObject(hdcMem, hFontOn);
	int x = index & 3;
	int y = index >> 2;
	switch (state)
	{
	case STATE_ENTER_TOTALS:
	case STATE_SOLVE:
		BitBlt(hdc, totalX[index], totalY[index], 64, 64, hdcMem, 64 * totals[index], 0, SRCCOPY);	
		break;
	case STATE_ENTER_PUZZLE:
		BitBlt(hdc, puzzleX[x], puzzleY[y], 64, 64, hdcMem, 64 * puzzle[y][x], 0, SRCCOPY);	
		break;
	case STATE_SOLUTIONS:
		if (min[y][x] == max[y][x])
		{
			BitBlt(hdc, puzzleX[x], puzzleY[y], 64, 64, hdcMem, 64 * min[y][x], 0, SRCCOPY);
		}
		else if (showValidRanges)
		{
			if (solutionMin[y][x] > min[y][x])
				SelectObject(hdcMem, hShaded);
			else
				SelectObject(hdcMem, hEvals);
			BitBlt(hdc, puzzleX[x], puzzleY[y], 32, 64, hdcMem, 64 * min[y][x], 64 * max[y][x], SRCCOPY);
			if (solutionMax[y][x] < max[y][x])
				SelectObject(hdcMem, hShaded);
			else
				SelectObject(hdcMem, hEvals);
			BitBlt(hdc, puzzleX[x] + 32, puzzleY[y], 32, 64, hdcMem, 64 * min[y][x] + 32, 64 * max[y][x], SRCCOPY);
		}
		else
		{
			SelectObject(hdcMem, hEvals);
			BitBlt(hdc, puzzleX[x], puzzleY[y], 64, 64, hdcMem, 64 * min[y][x], 64 * max[y][x], SRCCOPY);
		}
		break;
	default:
		break;
	}

	SelectObject(hdcMem, hbmOld);										// restore the old object
	DeleteDC(hdcMem);													// delete 												
}


void	ClearPuzzle(bool restarting)
{
	index = 0;
	for (int i = 0; i < 10; i++)
	{
		if (restarting == false)
			totals[i] = 0;
		resolved[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			min[i][j] = 0;
			max[i][j] = 9;
			if (restarting)
			{
				if (puzzle[i][j] != 0)
				{
					min[i][j] = max[i][j] = puzzle[i][j];
				}
				puzzle[i][j] = restart[i][j];
			}
			else
				puzzle[i][j] = 0;
		}
	}
}


// four numbers must be entered
bool ValidPuzzle()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (puzzle[i][j] > 0)
				count++;
		}
	}
	if (count < 4)
		return false;
	return true;
}


bool	ChangeIndex(HWND hWnd, int xx, int yy)
{
	int width = puzzleX[1] - puzzleX[0];
	int height = puzzleY[1] - puzzleY[0];
	if (xx < puzzleX[0]
	||  xx >= puzzleX[3] + width
	||  yy < puzzleY[0]
	||  yy >= puzzleY[3] + height)
		return false;
	int x, y;
	for (x = 3; x > 0; x--)
	{
		if (xx >= puzzleX[x])
			break;
	}
	for (y = 3; y > 0; y--)
	{
		if (yy >= puzzleY[y])
			break;
	}
	index = (y << 2) + x;
	return true;
}


INT_PTR CALLBACK RandomDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HWND hwndOwner;
	RECT rcOwner;
	HWND hwndList;
	char string[16];

	switch (message)
	{
	case WM_INITDIALOG:
		if ((hwndOwner = GetParent(hDlg)) == NULL)
			hwndOwner = GetDesktopWindow();
		CenterWindow(hDlg);
		GetWindowRect(hwndOwner, &rcOwner);

		hwndList = GetDlgItem(hDlg, IDC_TESTCOUNT);
		snprintf(string, sizeof(string), "%d", testCount);
		SetWindowText(hwndList, string);

		hwndList = GetDlgItem(hDlg, IDC_RANDOMSEED);
		dialogSeed = RandomInit();
		snprintf(string, sizeof(string), "0x%x", dialogSeed);
		SetWindowText(hwndList, string);
		SetFocus(hwndList);

		if (testMode == -1)
			CheckDlgButton(hDlg, IDC_TEST_EQUATIONS, BM_SETCHECK);
		else if(testMode == -2)
			CheckDlgButton(hDlg, IDC_TEST_EQUATION_PERT, BM_SETCHECK);
		else if (testMode == 0)
			CheckDlgButton(hDlg, IDC_TEST_PERTURBATIONS, BM_SETCHECK);
		else // testmode == 1
			CheckDlgButton(hDlg, IDC_TEST_PERT_EQUATIONS, BM_SETCHECK);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			if (IsDlgButtonChecked(hDlg, IDC_TEST_EQUATIONS) == BST_CHECKED)
				testMode = -1;
			else if (IsDlgButtonChecked(hDlg, IDC_TEST_EQUATION_PERT) == BST_CHECKED)
				testMode = -2;
			else if (IsDlgButtonChecked(hDlg, IDC_TEST_PERTURBATIONS) == BST_CHECKED)
				testMode = 0;
			else if (IsDlgButtonChecked(hDlg, IDC_TEST_PERT_EQUATIONS) == BST_CHECKED)
				testMode = 1;
			else	// IDC_TEST_EQUATION_PERT
				testMode = 1;
			hwndList = GetDlgItem(hDlg, IDC_RANDOMSEED);
			GetWindowText(hwndList, string, sizeof(string));
			int base = 10;
			if (string[0] == '0' && string[1] == 'x')
				base = 16;
			dialogSeed = strtoul(string, NULL, base);
			if (dialogSeed == 0)						// do not use 0 for the seed
				dialogSeed = 19480911;
			hwndList = GetDlgItem(hDlg, IDC_TESTCOUNT);
			GetWindowText(hwndList, string, sizeof(string));
			base = 10;
			if (string[0] == '0' && string[1] == 'x')
				base = 16;
			testCount = strtoul(string, NULL, base);
			startTest = true;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			startTest = false;
			dialogSeed = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

{
	int wmId;
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU hMenu = GetMenu(hWnd);
	HMENU hSubMenu;
	int x, y;

	switch (message)
	{
	case WM_CREATE:
		hBackgnd = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BACKGND));
		hFont = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_FONT));
		hEvals = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_EVALS));
		hShaded = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_SHADED));
		hFontLock = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_FONT_LOCK));
		hFontOn = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_FONT_ON));
		hFontError = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_FONT_ERROR));
		if (hBackgnd == NULL
		|| hFont == NULL
		|| hEvals == NULL
		|| hShaded == NULL
		|| hFontLock == NULL
		|| hFontOn == NULL
		|| hFontError == NULL)
			MessageBox(hWnd, "Could not load art!", "Error", MB_OK | MB_ICONEXCLAMATION);
		testMode = 0;									// default to test perturbations
		testCount = 1000;								// default to 1000 puzzles
		doAllPerturbations = false;						// do minimal perturbations
		equation2Passes = false;						// default to do 1 pass on equations because 2 passes always works
		hSubMenu = GetSubMenu(hMenu, SUBMENU_OPTIONS);
		CheckMenuItem(hSubMenu, IDM_2PASS_EQUATIONS - SUBMENU_START, MF_BYPOSITION | MF_UNCHECKED);
		showValidRanges = false;							// default to show valid ranges
		hSubMenu = GetSubMenu(hMenu, SUBMENU_OPTIONS);
		CheckMenuItem(hSubMenu, IDM_SHOW_VALID_RANGES - SUBMENU_START, MF_BYPOSITION | MF_UNCHECKED);
		RandomInit();									// init random number generator
		ClearPuzzle(false);								// reset puzzle
		EnterState(hMenu, STATE_ENTER_TOTALS);
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		CreateSymmetries();
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if (state == STATE_ENTER_PUZZLE
		|| state == STATE_SOLUTIONS)
		{
			if (ChangeIndex(hWnd, lParam & 0xffff, (int)(lParam >> 16)))
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_FILE_NEW:
			ClearPuzzle(false);
			EnterState(hMenu, STATE_ENTER_TOTALS);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FILE_CREATE:
			CreatePuzzle();
			EnterState(hMenu, STATE_ENTER_PUZZLE);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FILE_TEST:
			startTest = false;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_RANDOMBOX), hWnd, RandomDialog);
			if (startTest)
			{
				TestPuzzles(testCount, dialogSeed);
				EnterState(hMenu, STATE_WAIT);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case IDM_SOLVE:
			goto RETURN;
		case IDM_STEP:
			goto SPACE;
		case IDM_GUESS:
GUESS:		EnterState(hMenu, STATE_GUESS);
			PerturbationStep(hWnd, hMenu);
			SetTimer(hWnd, IDT_SOLVETIMER, GUESS_SPEED, (TIMERPROC)NULL);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_PERTURBATION:
PERTURBATIONS: 
			EnterState(hMenu, STATE_PERTURBATION);
			SetTimer(hWnd, IDT_SOLVETIMER, GUESS_SPEED, (TIMERPROC)NULL);
			exclusions = 0;					// do not exclude anything
			PerturbationStep(hWnd, hMenu);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_RESTART:
			equationOrderIndex = 0;
			exclusions = 0;
			KillTimer(hWnd, IDT_SOLVETIMER);
			ClearPuzzle(true);
			EnterState(hMenu, STATE_ENTER_PUZZLE);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_ALL_PERTURBATIONS:
			hSubMenu = GetSubMenu(hMenu, SUBMENU_OPTIONS);
			if (doAllPerturbations)
			{
				doAllPerturbations = false;		// minimal perturbations
				CheckMenuItem(hSubMenu, IDM_ALL_PERTURBATIONS - SUBMENU_START, MF_BYPOSITION | MF_UNCHECKED);
			}
			else
			{
				doAllPerturbations = true;		// do all perturbations
				CheckMenuItem(hSubMenu, IDM_ALL_PERTURBATIONS - SUBMENU_START, MF_BYPOSITION | MF_CHECKED);
			}
			break;
		case IDM_2PASS_EQUATIONS:
			hSubMenu = GetSubMenu(hMenu, SUBMENU_OPTIONS);
			if (equation2Passes)
			{
				equation2Passes = false;		// 1 pass on equations
				CheckMenuItem(hSubMenu, IDM_2PASS_EQUATIONS - SUBMENU_START, MF_BYPOSITION | MF_UNCHECKED);
			}
			else
			{
				equation2Passes = true;			// 2 passes on equations
				CheckMenuItem(hSubMenu, IDM_2PASS_EQUATIONS - SUBMENU_START, MF_BYPOSITION | MF_CHECKED);
			}
			break;
		case IDM_SHOW_VALID_RANGES:
			hSubMenu = GetSubMenu(hMenu, SUBMENU_OPTIONS);
			if (showValidRanges)
			{
				showValidRanges = false;		// turn off valid ranges
				CheckMenuItem(hSubMenu, IDM_SHOW_VALID_RANGES - SUBMENU_START, MF_BYPOSITION | MF_UNCHECKED);
			}
			else
			{
				showValidRanges = true;			// turn on valid ranges
				CheckMenuItem(hSubMenu, IDM_SHOW_VALID_RANGES - SUBMENU_START, MF_BYPOSITION | MF_CHECKED);
			}
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_HFLIP:
			HFlip();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_VFLIP:
			VFlip();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIP0:
			Flip0();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIP1:
			Flip1();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIPX0:
			FlipX0();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIPX1:
			FlipX1();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIPX2:
			FlipX2();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FLIPX3:
			FlipX3();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FILE_LOAD:
			equationOrderIndex = 0;
			exclusions = 0;							// clear exclusions
			if (DoFileOpen(hWnd) == false)
			{
				ClearPuzzle(false);
				EnterState(hMenu, STATE_ENTER_TOTALS);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			else
			{
				if (state == STATE_SOLUTIONS)
				{
					SolvePuzzle(hWnd);				// recalculate number of solutions
					EnterState(hMenu, STATE_SOLUTIONS);
				}
				else
					EnterState(hMenu, state);
			}
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case IDM_FILE_SAVE:
			DoFileSave(hWnd);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		x = index & 3;
		y = index >> 2;
		switch (wParam)
		{
		case 'x':
		case 'X':
			if (state == STATE_SOLUTIONS
			&&  solutions > 0)
				goto GUESS;
			break;
		case 'z':
		case 'Z':
			if (state == STATE_SOLUTIONS
			&& solutions > 0)
				goto PERTURBATIONS;
			break;
		case VK_LEFT:
			if (state == STATE_ENTER_PUZZLE
			|| state == STATE_SOLUTIONS)
			{
				x--;
				index = (y << 2) | (x & 3);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case VK_UP:
			if (state == STATE_ENTER_PUZZLE
			|| state == STATE_SOLUTIONS)
			{
				y = (--y & 3);
				index = (y << 2) | (x & 3);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case VK_RIGHT:
			if (state == STATE_ENTER_PUZZLE
			|| state == STATE_SOLUTIONS)
			{
				x++;
				index = (y << 2) | (x & 3);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case VK_DOWN:
			if (state == STATE_ENTER_PUZZLE
			|| state == STATE_SOLUTIONS)
			{
				y = (++y & 3);
				index = (y << 2) | (x & 3);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case VK_DELETE:
		case VK_BACK:
			if (state == STATE_ENTER_TOTALS)
				totals[index] = 0;
			else if (state == STATE_ENTER_PUZZLE)
			{
				puzzle[y][x] = 0;
				min[y][x] = 0;
				max[y][x] = 9;
			}
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (state == STATE_ENTER_TOTALS)
			{
				int num = totals[index] * 10 + (int)wParam - '0';
				if (num > 36)									// illegal number
					num = 0;
				totals[index] = num;
			}
			else if (state == STATE_ENTER_PUZZLE)
			{
				min[y][x] = max[y][x] = puzzle[y][x] = (int)wParam - '0';
			}
			else if (state == STATE_SOLUTIONS)
			{
				int num = (int)wParam - '0';
				if (num >= min[y][x] 
				&&  num <= max[y][x])
				{
					EnterState(hMenu, STATE_GUESS);
					min[y][x] = max[y][x] = num;
					snprintf(equationString, sizeof(equationString), "Guessing (%d,%d)=%d", y, x, num);
					SetUnresolved(x, y);				// unresolve totals
					SetTimer(hWnd, IDT_SOLVETIMER, GUESS_SPEED, (TIMERPROC)NULL);
				}
			}
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case VK_SPACE:
SPACE:		if (state == STATE_ENTER_PUZZLE
			|| state == STATE_WAIT)
			{
				if (ValidPuzzle())						// verify that it is a valid puzzle
				{
					if (state == STATE_ENTER_PUZZLE)	// use first diagonal else current row/col/diagonal
						index = 0;
					EnterState(hMenu, STATE_STEP);
					SetTimer(hWnd, IDT_SOLVETIMER, SOLVE_SPEED, (TIMERPROC)NULL);
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				}
			}
			else if (state == STATE_SOLUTIONS)
			{
				EnterState(hMenu, STATE_EQUATIONS);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			else if (state == STATE_EQUATIONS)
			{
				EquationStep(hWnd, hMenu);				// make a change and if done change modes
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case VK_RETURN:
RETURN:		if (state == STATE_ENTER_TOTALS)
			{
				if (totals[index] >= 4
				&&  totals[index] <= 36)				// valid total
				{
					++index;
					if (index == 10)					// entered all totals
					{
						index = 0;
						EnterState(hMenu, STATE_ENTER_PUZZLE);
					}
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				}
				else
					MessageBeep(MB_ICONWARNING);		// error sound		
			}
			else if (state == STATE_ENTER_PUZZLE
			||  state == STATE_WAIT)
			{
				if (ValidPuzzle())						// verify that it is a valid puzzle
				{
					index = 0;
					EnterState(hMenu, STATE_SOLVE);
					SetTimer(hWnd, IDT_SOLVETIMER, SOLVE_SPEED, (TIMERPROC)NULL);
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				}
				else
					MessageBeep(MB_ICONWARNING);		// error sound		
			}
			else if (state == STATE_SOLUTIONS
			|| state == STATE_EQUATIONS)
			{
				if (state == STATE_SOLUTIONS)
					EnterState(hMenu, STATE_EQUATIONS);
				EquationStep(hWnd, hMenu);
				if (state == STATE_EQUATIONS || state == STATE_EQUATIONS_FAILED)
					SetTimer(hWnd, IDT_SOLVETIMER, SOLVE_SPEED, (TIMERPROC)NULL);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_SOLVETIMER:
			KillTimer(hWnd, IDT_SOLVETIMER);
			if (state == STATE_EQUATIONS_FAILED)
			{
				state = STATE_EQUATIONS;				// return to equations
 				RestoreEquations(true);					// our guess succeeded
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				break;
			}
			else if (state == STATE_GUESS)
			{
				int res = NextPerturbation(false, true);
				if (res > 0)
				{
					SetTimer(hWnd, IDT_SOLVETIMER, GUESS_SPEED, (TIMERPROC)NULL);
				}
				else if (res < 0)				// we failed
				{
					EnterState(hMenu, STATE_GUESS_FAILED);
					SetTimer(hWnd, IDT_SOLVETIMER, GUESS_INVALID, (TIMERPROC)NULL);
				}
				else
				{
					SolvePuzzle(hWnd);			// recalculate number of solutions
					if (solutions == 0)			// no solutions to this guess
					{
						EnterState(hMenu, STATE_GUESS_FAILED);
						SetTimer(hWnd, IDT_SOLVETIMER, GUESS_INVALID, (TIMERPROC)NULL);
					}
					else
						EnterState(hMenu, STATE_SOLUTIONS);
				}
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				break;
			}
			else if (state == STATE_GUESS_FAILED)
			{
				for (int y = 0; y < 4; y++)				// save min and max in case guess failed
				{
					for (int x = 0; x < 4; x++)
					{
						min[y][x] = minSave[y][x];
						max[y][x] = maxSave[y][x];
					}
				}
				solutions = solutionsSave;
				for (int i = 0; i < 10; i++)			// they were resolved to start with
					resolved[i] = true;				
				EnterState(hMenu, STATE_SOLUTIONS);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				break;
			}
			else if (state == STATE_PERTURBATION)
			{
				SetTimer(hWnd, IDT_SOLVETIMER, PERTURBATION_SPEED, (TIMERPROC)NULL);
				exclusions = 0;							// do not exclude anything
				PerturbationStep(hWnd, hMenu);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				break;
			}
			else if (state == STATE_PERTURBATION_FAILED)
			{
				EnterState(hMenu, STATE_WAIT);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			else if (state == STATE_EQUATIONS)
			{
				goto RETURN;
			}
			x = index;
RETRY:		bool changed = CheckMinMax(index);			// see if min and max need adjustments
			if (puzzleFailed)							// no solutions
			{
				solutions = 0;
				EnterState(hMenu, STATE_SOLUTIONS);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				break;
			}
			do
			{
				index++;
				if (index >= 10)
					index = 0;
				if (state == STATE_STEP)
				{
					if (changed == false)				// no change in this row/col/diagonal
					{
						if (index == x)					// no changes anywhere
							goto SOLVE;
						goto RETRY;
					}
					EnterState(hMenu, STATE_WAIT);
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
					goto WAIT;
				}
				if (resolved[index] == false)
				{
					SetTimer(hWnd, IDT_SOLVETIMER, SOLVE_SPEED, (TIMERPROC)NULL);
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
					break;
				}
			} while (index != x);
			if (index == x)
			{
SOLVE:			SolvePuzzle(hWnd);						// we are stuck so find number of solutions
				EnterState(hMenu, STATE_SOLUTIONS);
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
WAIT:		break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawPuzzle(hWnd, hdc, ps.rcPaint.left != NoRect.left || ps.rcPaint.right != NoRect.right
			|| ps.rcPaint.top != NoRect.top || ps.rcPaint.bottom != NoRect.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBackgnd);
		DeleteObject(hFont);
		DeleteObject(hEvals);
		DeleteObject(hShaded);
		DeleteObject(hFontLock);
		DeleteObject(hFontOn);
		DeleteObject(hFontError);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHALLENGER));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_CHALLENGER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;						// do not erase background when redrawing
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_CHALLENGER);
	wcex.lpszClassName = szWindowClass;

	return RegisterClassEx(&wcex);
}


//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
		0, 0, 376 + 16, 448 + 59, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;
	CenterWindow(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_CHALLENGER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHALLENGER));

    // Main message loop:
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	_CrtDumpMemoryLeaks();				// report any memory leaks

    return (int) msg.wParam;
}
