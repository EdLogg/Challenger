// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN						// Exclude rarely-used stuff from Windows headers
// Windows Header Files:	
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>								// used for _CrtDumpMemoryLeaks()
#include <commdlg.h>							// required for load and save files
#include <stdio.h>								// required for load and save files

#include "resource.h"
#include "rand.h"
#include "time.h"


enum STATE
{
	STATE_ENTER_TOTALS = 0,						// entering totals data
	STATE_ENTER_PUZZLE,							// entering puzzle data
	STATE_STEP,									// allow one step or solving
	STATE_WAIT,									// wait mode before next solving step
	STATE_SOLVE,								// auto solve mode
	STATE_SOLUTIONS,							// show number of solutions and allow us to enter new guesses
	STATE_DONE,									// puzzle is complete
	STATE_EQUATIONS,							// step through equations
	STATE_EQUATIONS_FAILED,						// if our equation guess fails
	STATE_PERTURBATION,							// process perturbation guess
	STATE_PERTURBATION_FAILED,					// perturnbation guessing has failed
	STATE_GUESS,								// process guess
	STATE_GUESS_FAILED,							// 0 solutions or totals cannot be achieved
	STATE_END
};

enum PUZZLE_TYPE
{
	TYPE_0 = 0,									// no starting numbers on a diagonal (hardest to solve)
	TYPE_1 = 1,									// only one starting number per diagonal
	TYPE_2 = 2,									// two starting numbers on one diagonal
	TYPE_3 = 3,									// two starting numbers on both diagonals (100% solvable)
	TYPE_4 = 4,									// all four starting numbers on oner diagonal (not used but 100% solvable)
	TYPE_MAX = 5
};

enum EQUATION_CLASS
{
	CLASS_0 = 0,								// no variables used so puzzle is solved
	CLASS_1 = 1,								// one variable needed for all equations
	CLASS_2 = 2,								// two variables needed but only one per equation
	CLASS_3 = 3,								// some equations have two variables
	CLASS_4 = 4,								// all other cases
	CLASS_MAX = 5
};


// stdafx.cpp
#define MAX_VARIABLES		6					// max variables used in equations
#define DEBUG_STATES		0					// display states in header
#define DISPLAY_EQUATIONS	1					// show changes in equation steps
#define DEBUG_PERTURBATIONS	1					// write a file pertrubations.txt on our choices
#define USE_AVERAGE_PERTURBATIONS 1				// use lowest average perturbations not the first lowest
#define MAX_EXCLUSIONS		16					// only exclude this many guesses

extern STATE state;
extern int index;
extern int totals[10];
extern bool resolved[10];
extern int puzzle[4][4];
extern int restart[4][4];
extern int min[4][4];
extern int max[4][4];
extern int exclusions;							
extern int exclude[MAX_EXCLUSIONS][3];
extern int minSave[4][4];
extern int maxSave[4][4];
extern int solutionsSave;
extern bool equationsDone[10];
extern int equations[4][4][MAX_VARIABLES+2];
extern bool available[MAX_VARIABLES];
extern int variablePos[MAX_VARIABLES][2];
extern char variables[MAX_VARIABLES + 2];
extern int equationOrderIndex;
extern char equationString[64];
extern char equationString0[64];	
extern int solutions;
extern bool puzzleFailed;
extern int solutionMask[4][4];
extern int solutionMin[4][4], solutionMax[4][4];
extern bool doAllPerturbations;
extern bool equation2Passes;
extern bool showValidRanges;
extern int testMode;

// game.cpp
bool InvalidMinMax();
void RestoreEquations(bool success);
bool PuzzleComplete();
bool EquationDone(int index);
void EquationOrderIncrease();
void StartEquations();
bool SetNextEquation(bool testing);
bool ValidTotal(int n);
bool CheckMinMax(int index);
void SetUnresolved(int x, int y);
void SolvePuzzle(HWND hWnd);
int NextPerturbation(bool testing, bool oneStep);
void CreatePuzzle();
void TestPuzzles(int count, U32 seed);

// symmetries.cpp
void HFlip();
void VFlip();
void Flip0();
void Flip1();
void FlipX0();
void FlipX1();
void FlipX2();
void FlipX3();
void CreateSymmetries();

// file.cpp 
BOOL SaveTextFile(LPCTSTR pszFileName);
bool DoFileOpen(HWND hwnd);
void DoFileSave(HWND hwnd);
