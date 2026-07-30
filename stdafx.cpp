// stdafx.cpp : source file that includes just the standard includes
// Challenger.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

STATE state;
int index;								// position in puzzle; y=row = index>>2; x=col = index&3
int totals[10];
bool resolved[10];
int puzzle[4][4];						// starting puzzle values
int restart[4][4];
int min[4][4];							// min and max range for puzzle
int max[4][4];
int minSave[4][4];						// save min and max for guessing
int maxSave[4][4];
int solutionsSave;						// in case guess fails with 0 solutions
int exclusions;							// number of exclusions
int exclude[MAX_EXCLUSIONS][3];			// (y,x)=z are the three 
bool equationsDone[10];					// true when we have created equations or there is none to be done
int equations[4][4][MAX_VARIABLES + 2];	// [][][0] < 0 if puzzle is set, = 0 if no equation yet,  else > 0 if equation exits here, [][][1-N] = constant, scalers for variables a,b,c,d...
bool available[MAX_VARIABLES];			// if variable a, b, c, d is available to be used for equation
int variablePos[MAX_VARIABLES][2];		// y, x pos of the variable in the puzzle if available[] = false
int equationOrderIndex = 0;				// which equation ordering do we use 
char equationString[64];				// equation step information
char equationString0[64];				// equation guess
int solutions;
bool puzzleFailed;
int solutionMask[4][4];					// set bits for all solutions
int solutionMin[4][4], solutionMax[4][4];	// min and max over all solutions
int testMode;							// are testing equations (-1) or equations then perturbnations (-2) or perturbations (0) or perturbations then equations (1)
bool doAllPerturbations;				// do all possible perturbations i.e. do not stop when unknowns <= equations
bool equation2Passes;					// if true we use the 2nd pass on equations to resolve any invalid min or max range values
bool showValidRanges;					// if true show valid ranges with bold text
