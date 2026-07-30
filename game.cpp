#include "stdafx.h"


int indexToTotalIndex[16][3] =
{
	{ 1, 9, 5 },		// (0,0)
	{ 1, 8, -1 },
	{ 1, 7, -1 },
	{ 1, 6, 0 },
	{ 2, 9, -1 },		// (1,0)
	{ 2, 8, 5 },
	{ 2, 7, 0 },
	{ 2, 6, -1 },
	{ 3, 9, -1 },		// (2,0)
	{ 3, 8, 0 },
	{ 3, 7, 5 },
	{ 3, 6, -1 },
	{ 4, 9, 0 },		// (3,0)
	{ 4, 8, -1 },
	{ 4, 7, -1 },
	{ 4, 6, 5 },
};

int totalIndexToPos[10][4][2] =
{
	{ { 0, 3 },{ 1, 2 },{ 2, 1 },{ 3, 0 } },	// diagonal from upper right to lower left
	{ { 0, 0 },{ 0, 1 },{ 0, 2 },{ 0, 3 } },	// rows
	{ { 1, 0 },{ 1, 1 },{ 1, 2 },{ 1, 3 } },
	{ { 2, 0 },{ 2, 1 },{ 2, 2 },{ 2, 3 } },
	{ { 3, 0 },{ 3, 1 },{ 3, 2 },{ 3, 3 } },
	{ { 0, 0 },{ 1, 1 },{ 2, 2 },{ 3, 3 } },	// diagonal from upper left to lower right
	{ { 0, 3 },{ 1, 3 },{ 2, 3 },{ 3, 3 } },	// columns
	{ { 0, 2 },{ 1, 2 },{ 2, 2 },{ 3, 2 } },
	{ { 0, 1 },{ 1, 1 },{ 2, 1 },{ 3, 1 } },
	{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 } },
};

int equationOrder[18][10] = 
{
	// diagonals first
 	{ 0, 5, 6, 11, 7, 12, 8, 13, 9, 14, },		// upper right corner
	{ 15, 0, 14, 16, 13, 17, 12, 18, 11, 19 },	// lower right corner
	{ 10, 15, 4, 19, 3, 18, 2, 17, 1, 16, },	// lower left corner
	{ 5, 0, 1, 9, 2, 8, 3, 7, 4, 6 },			// upper left corner
	// edges next to corner first
	{ 1, 9, 2, 8, 3, 7, 4, 6, 5, 0 },			// upper left corner
	{ 16, 14, 17, 13, 18, 12, 19, 11, 15, 0 },	// lower right corner
	{ 11, 6, 12, 7, 13, 8, 14, 9, 10, 5},		// upper right corner
	{ 4, 19, 3, 18, 2, 17, 1, 16, 10, 15 },		// lower left corner
	// middle edges
	{ 12, 13, 6, 17, 11, 14, 0, 15, 8, 19 },	// right middle edges
	{ 7, 8, 0, 5, 6, 9, 11, 2, 13, 4, },		// top middle edges
	{ 2, 3, 5, 10, 1, 4, 9, 18, 7, 16, },		// left middle edges
	{ 18, 17, 10, 15, 19, 16, 4, 13, 2, 11, },	// bottom middle edges
	// rows and columns first
	{ 11, 12, 13, 14, 6, 7, 8, 9, 0, 5 },		// right side rows
	{ 4, 3, 2, 1, 19, 18, 17, 16, 10, 5 },		// left side rows
	{ 9, 8, 7, 6, 1, 2, 3, 4, 5, 0 },			// top side columns
	{ 16, 17, 18, 19, 4, 3, 2, 1, 10, 15 },		// bottom side columns
	// strange criss cross
	{ 2, 13, 8, 17, 1, 14, 9, 16, 10, 15 },		// start on left
	{ 7, 18, 12, 3, 9, 16, 11, 4, 10, 15 },		// start on top
};

//	type 0 - no cells on diagonals
//	type 1 - only 1 on each diagonal
//	type 2 - one diagonal has 2 cells
//	type 3 - both diagonals have 2 cells
//	type 4 - one diagonal has 4 cells
//
int rowChoices[22][4] =						// all possible choices for the 4 cells w/o 2 in a diagonal
{
//		{ 0, 1, 2, 3 },						// type 4
		{ 0, 1, 3, 2 },						// type 2
		{ 0, 2, 1, 3 },						// type 3
		{ 0, 2, 3, 1 },						// type 1				
		{ 0, 3, 1, 2 },						// type 1
		{ 0, 3, 2, 1 },						// type 2

		{ 1, 0, 2, 3 },						// type 2
		{ 1, 0, 3, 2 },						// type 0
		{ 1, 2, 0, 3 },						// type 1
		{ 1, 2, 3, 0 },						// type 2
		{ 1, 3, 0, 2 },						// type 0
		{ 1, 3, 2, 0 },						// type 1

		{ 2, 0, 1, 3 },						// type 1				
		{ 2, 0, 3, 1 },						// type 0
		{ 2, 1, 0, 3 },						// type 2
		{ 2, 1, 3, 0 },						// type	1
		{ 2, 3, 0, 1 },						// type 0
		{ 2, 3, 1, 0 },						// type 2

		{ 3, 0, 1, 2 },						// type 2
		{ 3, 0, 2, 1 },						// type 1
		{ 3, 1, 0, 2 },						// type 1
		{ 3, 1, 2, 0 },						// type 3
		{ 3, 2, 0, 1 },						// type 2
//		{ 3, 2, 1, 0 },						// type 4
};


bool CheckRangeForHoles(int i, int j)
{
	int mask = solutionMask[i][j];
	if (mask == 0)
		return 0;
	while ((mask & 1) == 0)
		mask >>= 1;
	while ((mask & 1) != 0)
		mask >>= 1;
	return mask != 0;
}


bool PuzzleComplete()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
			if (min[y][x] != max[y][x])
				return false;
	}
	return true;
}


bool InvalidMinMax()
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (min[row][col] < 1
			|| max[row][col] > 9)
			{
				min[row][col] = 9;
				max[row][col] = 1;
				return true;
			}
			if (min[row][col] > max[row][col])
				return true;
		}
	}
	return false;
}


//	type 0 - no cells on diagonals			4/22=18.18%
//	type 1 - only 1 on each diagonal		8/22=36.36%
//	type 2 - one diagonal has 2 cells		8/22=36.36%
//	type 3 - both diagonals have 2 cells	2/22= 9.09%
//	type 4 - one diagonal has 4 cells		0/22= 0%
int GetPuzzleType()
{
	int diag0 = 0;
	int diag1 = 0;
	if (min[0][0] == max[0][0])
		diag1++;
	if (min[1][1] == max[1][1])
		diag1++;
	if (min[2][2] == max[2][2])
		diag1++;
	if (min[3][3] == max[3][3])
		diag1++;
	if (min[0][3] == max[0][3])
		diag0++;
	if (min[1][2] == max[1][2])
		diag0++;
	if (min[2][1] == max[2][1])
		diag0++;
	if (min[3][0] == max[3][0])
		diag0++;
	if (diag0 == 4 || diag1 == 4)
		return 4;
	if (diag0 > 1 && diag1 > 1)
		return 3;
	if (diag0 > 1 || diag1 > 1)
		return 2;
	if (diag0 == 0 && diag1 == 0)
		return 0;
	return 1;
}


int saveEquations[4][4][MAX_VARIABLES + 2];	// [][][0] < 0 if puzzle is set, = 0 if no equation yet,  else > 0 if equation exits here, [][][1-5] = constant, scalers for variables a,b,c,d...
bool saveAvailable[MAX_VARIABLES];			// if variable a, b, c, d is available to be used for equation
int saveVariablePos[MAX_VARIABLES][2];		// y, x pos of the variable in the puzzle if available[] = false
int saveRow, saveCol, saveVal;				/// position and value we are testing
int saveMin[4][4];
int saveMax[4][4];
void SaveEquations(int row, int col, int val)
{
	snprintf(equationString0, sizeof(equationString0), "Test (%d,%d)=%d", row, col, val);
	saveRow = row;
	saveCol = col;
	saveVal = val;
	for (int v = 0; v < MAX_VARIABLES; v++)
	{
		saveAvailable[v] = available[v];
		saveVariablePos[v][0] = variablePos[v][0];
		saveVariablePos[v][1] = variablePos[v][1];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (v == 0)
				{
					saveMin[row][col] = min[row][col];
					saveMax[row][col] = max[row][col];
					saveEquations[row][col][0] = equations[row][col][0];
					saveEquations[row][col][1] = equations[row][col][1];
				}
				saveEquations[row][col][v+2] = equations[row][col][v+2];
			}
		}
	}
	min[row][col] = max[row][col] = val;
}


void RestoreEquations(bool success)
{
	equationString[0] = 0;
	equationString0[0] = 0;
	for (int v = 0; v < MAX_VARIABLES; v++)
	{
		available[v] = saveAvailable[v];
		variablePos[v][0] = saveVariablePos[v][0];
		variablePos[v][1] = saveVariablePos[v][1];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (v == 0)
				{
					min[row][col] = saveMin[row][col];
					max[row][col] = saveMax[row][col];
					equations[row][col][0] = saveEquations[row][col][0];
					equations[row][col][1] = saveEquations[row][col][1];
				}
				equations[row][col][v + 2] = saveEquations[row][col][v + 2];
			}
		}
	}
 	if (success)
	{
		if (min[saveRow][saveCol] == saveVal)
			min[saveRow][saveCol]++;
		else if (max[saveRow][saveCol] == saveVal)
			max[saveRow][saveCol]--;
		snprintf(equationString, sizeof(equationString), "new range (%d,%d)=(%d-%d)",
			saveRow, saveCol, min[saveRow][saveCol], max[saveRow][saveCol]);
	}
}


bool EquationDone(int index)
{
	for (int i = 0; i < 4; i++)
	{
		int y = totalIndexToPos[index][i][0];
		int x = totalIndexToPos[index][i][1];
		if (min[y][x] != max[y][x])
			return false;
	}
	return true;
}


void EquationOrderIncrease()
{
	// use a different equation ordering next time
	if (++equationOrderIndex >= sizeof(equationOrder) / sizeof(equationOrder[0]))	
		equationOrderIndex = 0;
}


// if we get a variable = val then substitute val for variabale in all equations
void ReplaceVariable(int y, int x, int val)
{
	int v;
	for (v = 0; v < MAX_VARIABLES; v++)
	{
		if (equations[y][x][v+2] != 0)
			break;
	}
	if (v >= MAX_VARIABLES)
		return;										// WTF someone screwed up
	val -= equations[y][x][1];						// for -1+a = val change this to a = 2
	val = val / equations[y][x][v + 2];				// just in case we have 2b = 4
	for (int yy = 0; yy < 4; yy++)
	{
		for (int xx = 0; xx < 4; xx++)
		{
			if (equations[yy][xx][2 + v] != 0)		// variable used
			{
				equations[yy][xx][1] += val * equations[yy][xx][v + 2];
				equations[yy][xx][2 + v] = 0;		// remove variable
			}
		}
	}
	available[v] = true;							// we can reuse this variable
}


bool EvaluateEquations(bool testing)
{
	// look for any constants and count number of variables in equation
	int count[4][4];								// < 0 if NA, 0 for constant only, else number of variables
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (equations[y][x][0] < 0)
			{
				count[y][x] = -1;
				continue;
			}
			count[y][x] = 0;
			for (int v = 0; v < MAX_VARIABLES; v++)
			{
				if (equations[y][x][2 + v] != 0)
					count[y][x]++;
			}
			if (count[y][x] == 0					// fixed value so use it
			&& min[y][x] != max[y][x])				// not done before
			{
#if DISPLAY_EQUATIONS
				snprintf(equationString, sizeof(equationString), "Fixed value (%d,%d) = %d", y, x, equations[y][x][1]);
#endif
				min[y][x] = max[y][x] = equations[y][x][1];
				SetUnresolved(x, y);				// mark these are unresolved
				return true;
			}
		}
	}
	// look for only one variable
	// set min and max based on the one variable
	int changes = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (count[y][x] == 1)					// something like -2+a or 9-a or even a 
			{
				int v;
				for (v = 0; v < MAX_VARIABLES; v++)
					if (equations[y][x][2 + v] != 0)
						break;
				if (min[y][x] == max[y][x])
				{
#if DISPLAY_EQUATIONS
					snprintf(equationString, sizeof(equationString), "Variable %c at (%d,%d) Min=Max=%d", variables[2+v], y, x, equations[y][x][1]);
#endif
					ReplaceVariable(y, x, min[y][x]);
					return true;
				}
				int yy = variablePos[v][0];
				int xx = variablePos[v][1];
				int min0 = 10; 
				int max0 = 0;
				int min1 = 10;
				int max1 = 0;
				for (int m = min[yy][xx]; m <= max[yy][xx]; m++)
				{
					int val = equations[y][x][1] + m * equations[y][x][2+v];
					if (val >= min[y][x] && val <= max[y][x])
					{
						if (min0 > m)
							min0 = m;
						if (max0 < m)
							max0 = m;
						if (min1 > val)
							min1 = val;
						if (max1 < val)
							max1 = val;
					}
				}
				if (min0 != min[yy][xx] || max0 != max[yy][xx])
				{
					changes++;
					min[yy][xx] = min0;
					max[yy][xx] = max0;
					SetUnresolved(xx, yy);
				}
				if (min1 != min[y][x] || max1 != max[y][x])
				{
					changes++;
					min[y][x] = min1;
					max[y][x] = max1;
					SetUnresolved(x, y);
				}
				if (changes != 0)
				{
#if DISPLAY_EQUATIONS
					snprintf(equationString, sizeof(equationString), "Using %c at (%d,%d)=(%d-%d) and (%d,%d)=(%d-%d)", variables[2+v], yy, xx, min0, max0, y, x, min1, max1);
#endif
					return true;
				}
			}
		}
	}
	// Now look at the general case with multiple variables in the equations
	// When I say a or -b I mean scaler times a or -b
	// k is the constant for the cell
	// min = min range for cell 
	// max = max range for cell 
	// min(a) = min for variable a
	// max(a) = max for variable a
	// m0(a) = min(a) if scaler for variable a is positive else -max(a)
	// m1(a) = max(a) if scaler for variable a is positive else -min(a)
	// 
	// For max >= k+-a+-b+-c... >= min
	// To reduce the range min & max of the cell
	//	max = min(max, k+m1(a)+m1(b)...)
	//	min = max(min, k+m0(a)+m0(b)...)
	// 
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (count[y][x] <= 1)						// we have already dealt with this above
				continue;
			// lets check the range for the cells
			// add up k+m1(a)+m1(b)... and k+m0(a)+m0(b)...
			int m0 = equations[y][x][1];				// k 
			int m1 = equations[y][x][1];
			int maxs = m1;								// add all max and min values
 			int mins = m0;
			for (int v = 0; v < MAX_VARIABLES; v++)
			{
				if (equations[y][x][2 + v] == 0)		// not in the formula
					continue;
				int vy = variablePos[v][0];
				int vx = variablePos[v][1];
				int scaler = equations[y][x][2 + v];
				if (scaler > 0)			// positive scaler
				{
					m0 += scaler * min[vy][vx];
					m1 += scaler * max[vy][vx];
				}
				else
				{
					m1 += scaler * min[vy][vx];
					m0 += scaler * max[vy][vx];
				}
				mins = m0;
				maxs = m1;
			}
			if (max[y][x] > m1)
			{
				max[y][x] = m1;
				changes++;
				SetUnresolved(x, y);
			}
			if (min[y][x] < m0)
			{
 				min[y][x] = m0;
				SetUnresolved(x, y);
				changes++;
			}
			if (changes != 0)
			{
#if DISPLAY_EQUATIONS
				snprintf(equationString, sizeof(equationString), "(%d,%d)=(%d-%d) new min or max", y, x, m0, m1);
#endif
				return true;
			}
			// now see if we can alter the range of any variables
			// max >= k+-a+-b... >= min
			// max-k-+b-+c... >= +-a >= min-k-+b-+c...
			//  mins = (k+m0(b)+m0(c)...) minimum sum excluding m0(a)
			//  maxs = (k+m1(b)+m1(c)...) maximum sum excluding m1(a)
			// For +a: max-mins >= a >=  min-maxs 
			//	if max-mins > max(a) set max(a) to max-mins
			//	if min-maxs < min(a) set min(a) to min-maxs
			// For -a: -max+mins <= a <= -min+maxs 
			//  if -max+mins > min(a) set min(a) to -max+mins
			//  if -min+maxs < max(a) set max(a) to -min+maxs
			//
			// NOTE: if we get something like 3 <= 2a <=7
			// if we divide the equation we get 1 <= a <= 3
			// but 1 cannot be the minimum so we need to round up
			// and get 2 <= a <= 3
			//
			for (int v = 0; v < MAX_VARIABLES; v++)
			{
				if (equations[y][x][2 + v] == 0)
					continue;
				int vy = variablePos[v][0];
				int vx = variablePos[v][1];
				int scaler = equations[y][x][2 + v];
				if (scaler > 0)						// positive scaler
				{
					m0 = scaler * min[vy][vx];
					m1 = scaler * max[vy][vx];
					m0 = (max[y][x] - mins + m0) / scaler;
 					if (m0 < max[vy][vx])
					{
						changes++;
						max[vy][vx] = m0;
						SetUnresolved(vx, vy);
					}
					m1 = (min[y][x] - maxs + m1 + (scaler - 1)) / scaler;
					if (m1 > min[vy][vx])
					{
						changes++;
						min[vy][vx] = m1;
						SetUnresolved(vx, vy);
					}
					if (changes != 0)
					{
#if DISPLAY_EQUATIONS
 						snprintf(equationString, sizeof(equationString), "%c at (%d,%d) implies new range (%d-%d)", variables[2+v], y, x, min[vy][vx], max[vy][vx]);
#endif
						return true;
					}
				}
				else
				{
					//  if -min+maxs < max(a) set max(a) to -min+maxs
					//  if -max+mins > min(a) set min(a) to -max+mins
					scaler = -scaler;
					m0 = scaler * min[vy][vx];
					m1 = scaler * max[vy][vx];
					m0 = (-min[y][x] + maxs + m0 + (scaler - 1)) / scaler;
					if (m0 < max[vy][vx])
					{
						changes++;
						max[vy][vx] = m0;
						SetUnresolved(vx, vy);
					}
					m1 = (-max[y][x] + mins + m1) / scaler;
					if (m1 > min[vy][vx])
					{
						changes++;
						min[vy][vx] = m1;
						SetUnresolved(vx, vy);
					}
				}
				if (changes != 0)
				{
#if DISPLAY_EQUATIONS
					snprintf(equationString, sizeof(equationString), "%c at (%d,%d) implies new range (%d-%d)", variables[2+v], y, x, min[vy][vx], max[vy][vx]);
#endif
					return true;
				}
			}
		}
		// now make sure the totals for the rows/cols/diagonals will work
		for (int i = 0; i < 10; i++)
		{
			changes = 0;
			for (int j = 0; j < 4; j++)
			{
				int x, y;
				int mmin = totals[i];
				int mmax = totals[i];
				for (int jj = 0; jj < 4; jj++)
				{
					if (jj == j)
						continue;							// skip the cell we are looking at
					y = totalIndexToPos[i][jj][0];
					x = totalIndexToPos[i][jj][1];
					mmax -= min[y][x];
					mmin -= max[y][x];
				}
				y = totalIndexToPos[i][j][0];
				x = totalIndexToPos[i][j][1];
				if (mmin > min[y][x])
				{
					changes++;
					min[y][x] = mmin;
					SetUnresolved(x, y);
				}
				if (mmax < max[y][x])
				{
					changes++;
					max[y][x] = mmax;
					SetUnresolved(x, y);
				}
				if (changes != 0)
				{
#if DISPLAY_EQUATIONS
					snprintf(equationString, sizeof(equationString), "(%d,%d) new min or max (%d-%d)", y, x, min[y][x], max[y][x]);
#endif
					return true;
				}
			}
		}
	}
	// now look for similar entries i.e. the same variables and scalers
	// For example one cell with 6+b-c with a range 1-2
	// and another cell 3-b+c with a range of 7-9 where b=1-2 and c=5-7
	// So 1 <= 6+b-c <= 2 or -1 >= -6+b-c >= -2
	// so the cell with 3-b+c must be 8 >= 3+b-c >= 7
	// Hence we can reset the max to 7-8 instead of 7-9
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (equations[y][x][0] <= 0)				// no equations exist
				continue;
			int yy = y;
			int xx = x + 1;
			if (xx >= 4)
			{
				if (++yy >= 4)
					break;
			}
			for (yy = y; yy < 4; yy++)
			{
				for (xx = 0; xx < 4; xx++)
				{
					if (yy == y && xx <= x)				// skip to next location
						continue;
					if (equations[yy][xx][0] <= 0)		// no equations exist
						continue;
					int v;
					int pos = 0;						// 0 is undertined else 1 for positive and -1 for negative
					for (v = 2; v < MAX_VARIABLES; v++)
					{
						if (equations[y][x][v] == 0		// not used
						&&  equations[yy][xx][v] == 0)
							continue;
						if (pos == 0)
						{
							if (equations[yy][xx][v] * equations[y][x][v] > 0)
								pos = 1;
							else
								pos = -1;
						}
						if (equations[y][x][v] != pos * equations[yy][xx][v])
							break;						// not a valid match
					}
					if (v == MAX_VARIABLES)				// we have a valid match
					{
 						changes = 0;
						int min0, max0, min1, max1;
						min0 = min[y][x] - equations[y][x][1];
						max0 = max[y][x] - equations[y][x][1];
						if (pos > 0)
						{
							min1 = min[yy][xx] - equations[yy][xx][1];
							max1 = max[yy][xx] - equations[yy][xx][1];
							if (min0 < min1)			// new min0
							{
								changes++;
								min[y][x] += min1 - min0;
								SetUnresolved(x, y);
							}
							else if (min1 < min0)		// new min1
							{
								changes++;
								min[yy][xx] += min0 - min1;
								SetUnresolved(xx, yy);
							}
							if (max0 > max1)			// new max0
							{
								changes++;
								max[y][x] += max1 - max0;
								SetUnresolved(x, y);
							}
							else if (max1 > max0)		// new max1
							{
								changes++;
								max[yy][xx] += max0 - max1;
								SetUnresolved(xx, yy);
							}
						}
						else
						{
							max1 = -min[yy][xx] + equations[yy][xx][1];
							min1 = -max[yy][xx] + equations[yy][xx][1];
							if (min0 < min1)			// new min0
							{
								changes++;
								min[y][x] += min1 - min0;
								SetUnresolved(x, y);
							}
							else if (min1 < min0)		// new max1
							{
								changes++;
								max[yy][xx] -= min0 - min1;
								SetUnresolved(xx, yy);
							}
							if (max0 > max1)			// new max0
							{
								changes++;
								max[y][x] -= max0 - max1;
								SetUnresolved(x, y);
							}
							else if (max1 > max0)		// new min1
							{
								changes++;
								min[yy][xx] += max1 - max0;
								SetUnresolved(xx, yy);
							}
						}
						if (changes)
						{
#if DISPLAY_EQUATIONS
							snprintf(equationString, sizeof(equationString), "Similar (%d,%d) (%d,%d) changes min or max", y, x, yy, xx);
#endif
							return true;

						}
					}
				}
			}
		}
	}
	if (testing && testMode == -2)				// we are doing some equations and then perturbations so do one pass
		return false;
	if (equation2Passes == false)				// only one pass on equations
		return false;
	// now look for any min or max that is not a valid value and test it for contradictions
	if (equationString0[0] != 0)				// we are already testing 
	{
		RestoreEquations(false);				// restore values 
		return false;
	}
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (min[row][col] < solutionMin[row][col])
			{
				SaveEquations(row, col, min[row][col]);
 				return true;
			}
			if (max[row][col] > solutionMax[row][col])
			{
				SaveEquations(row, col, max[row][col]);
				return true;
			}
		}
	}
	return false;
}


bool SolveEquation(int index, int row, int col)
{
	int equation[MAX_VARIABLES+2];
	for (int v = 0; v < MAX_VARIABLES + 2; v++)
		equation[v] = 0;
	if (row >= 0)
	{
		equation[1] = -min[col][row];
		for (int v = 1; v < MAX_VARIABLES + 1; v++)
		{
			equation[v] += equations[col][row][v];
		}
	}
	else
	{
		equation[1] = -totals[index];
		for (int i = 0; i < 4; i++)
		{
			int y = totalIndexToPos[index][i][0];
			int x = totalIndexToPos[index][i][1];
			for (int v = 1; v < MAX_VARIABLES + 1; v++)
			{
				equation[v] += equations[y][x][v];
			}
		}
	}
	// now we have an equation == 0
	// can we reduce it by finding minimum scaler
	int scaler = 999999;							// find minimum scaler (non-zero) and what variable it is
	int variable = 0;								// use this last min variable for the substitution
	for (int v = 2; v < MAX_VARIABLES+2; v++)
	{
		int s = equation[v];
		if (s == 0)
			continue;
		if (s < 0)
			s = -s;
		if (s <= scaler)
		{
			scaler = s;
			variable = v;
		}
	}
	if (scaler > 100)							// the equation evaluates to 0 = 0
		return false;
	// WARNING: all scalers and the constant must be multiple of the scaler
	if (scaler > 1)
	{
		for (int v = 1; v < MAX_VARIABLES+2; v++)
			equation[v] /= scaler;
	}
	// now create the equation for substitution like b = 9-a
	int s = equation[variable];
 	equation[variable]= 0;						// change something like 14-a-b=0 to 14-a=b
	if (s > 0)									// else make 5-a+b=0 to b=-5+a
	{
		for (int v = 1; v < MAX_VARIABLES+2; v++)
		{
			equation[v] = -equation[v];
		}
	}
#if DISPLAY_EQUATIONS
	if (row >= 0)
	{
		sprintf(equationString, "(%d,%d) %c=", col, row, variables[variable]);
	}
	else switch (index)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		sprintf(equationString, "Row %d %c=", index -1, variables[variable]);
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		sprintf(equationString, "Col %d %c=", 9 - index, variables[variable]);
		break;
	case 0:
		sprintf(equationString, "Diag0 %c=", variables[variable]);
		break;
	default:
	case 5:
		sprintf(equationString, "Diag1 %c=", variables[variable]);
		break;
	}
	char str[10], string[20];;
	string[0] = 0;
	for (int v = 1; v < MAX_VARIABLES + 2; v++)
	{
		if (equation[v] == 0)
			continue;
		str[0] = 0;
		if (equation[v] == -1)
		{
			if (v == 1)
				snprintf(str, sizeof(str), "-1");
			else
				snprintf(str, sizeof(str), "-%c", variables[v]);
			strncat(string, str, strlen(str));
		}
		else if (equation[v] == 1)
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
			if (strlen(string) == 0 && equation[v] > 0)
				snprintf(str, sizeof(str), "%d%c", equation[v], variables[v]);
			else
				snprintf(str, sizeof(str), "%+d%c", equation[v], variables[v]);
			strncat(string, str, strlen(str));
		}
	}
	strncat(equationString, string, strlen(string));
#endif
	// substitute the variable in all locations
	available[variable-2] = true;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			s = equations[y][x][variable];
			if (s == 0)
				continue;
			equations[y][x][variable] = 0;
			for (int v = 1; v < MAX_VARIABLES + 2; v++)
			{
				equations[y][x][v] += s * equation[v];
			}
		}
	}
	return true;
}


// look for any cell with min=max but an equation exists other than a constant
// then we may get something like min=max=5-a+b which we can use to solve
bool SolveEquation0()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (min[y][x] != max[y][x]					// we must have min=max	
			|| equations[y][x][0] < 0)					// no equation here
				continue;
			int v;
			for (v = 2; v < MAX_VARIABLES + 2; v++)
			{
				if (equations[y][x][v] != 0)
					break;
			}
			if (v < MAX_VARIABLES						// we have at least one variable
			&& SolveEquation(0, x, y))					// and we substituted the variable everywhere
				return true;
		}
	}
	return false;
}

bool SetNextEquation(bool testing)
{
	int x, y;
	int min, m, index, mIndex;
	equationString[0] = 0;
	// using the equationOrder list search for the direction with the fewest unfilled cells
	// so in case of ties the first one in the list wins 
RETRY: min = 4;
	int rc;											// best index into equationOrder for best row/col/diagonal
	for (int ii = 0; ii < 10; ii++)
	{
		index = equationOrder[equationOrderIndex][ii];
		if (index >= 10)							// go backwards
			index -= 10;
		if (equationsDone[index])
			continue;
		m = 0;										// number of entries w/o an equation in this row/col/diag
		for (int i = 0; i < 4; i++)
		{
			y = totalIndexToPos[index][i][0];
			x = totalIndexToPos[index][i][1];
			if (equations[y][x][0] == 0)
				m++;
		}
		if (m < min)
		{
			rc = ii;
			min = m;
			mIndex = index;
		}
	}
	if (min == 4)
	{
		if (SolveEquation0())						// if any min = max an equations exists so substitute variable if possible
			return true;
		return EvaluateEquations(testing);			// reduce by substitution if we can else we are done
	}
	equationsDone[mIndex] = true;
	if (min == 0)
	{
		if (SolveEquation(mIndex, -1, -1))			// solve by removing one variable using direction mIndex
			return true;
		goto RETRY;									// this equation must evaluate to 0=0 so we cannot reduce anything
	}
	index = equationOrder[equationOrderIndex][rc];
	int dir = 1;									// -1 if decreasing else increasing for adding variables 
	if (index >= 10)
	{
		dir = -1;
		index -= 10;
	}
#if DISPLAY_EQUATIONS
	switch (index)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		sprintf(equationString, "Fill row %d", index - 1);
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		sprintf(equationString, "Fill col %d", 9 - index);
		break;
	case 0:
		sprintf(equationString, "Fill diag0");
		break;
	default:
	case 5:
		sprintf(equationString, "Fill diag1");
		break;
	}
#endif
	for (int i = 0; i < 4; i++)
	{
		int ii;
		if (dir < 0)
			ii = 3 - i;
		else
			ii = i;
		y = totalIndexToPos[mIndex][ii][0];
		x = totalIndexToPos[mIndex][ii][1];
		if (equations[y][x][0] == 0)				// add variable here
		{
			if (min > 1)
			{
				for (int v = 0; v < MAX_VARIABLES; v++)
				{
					if (available[v])
					{
						equations[y][x][0] = 1;		// we have an equation here
						equations[y][x][1] = 0;		// constant of 0
						equations[y][x][2 + v] = 1;	// equation = a or b or c...
						variablePos[v][0] = y;		// save position
						variablePos[v][1] = x;
						available[v] = false;
						break;
					}
				}
			}
			else
			{
				// subtract all equations from the total
				equations[y][x][1] = totals[mIndex];
				for (int i = 0; i < 4; i++)
				{
					if (index < 0)
						ii = 3 - i;
					else
						ii = i;
					int yy = totalIndexToPos[mIndex][ii][0];
					int xx = totalIndexToPos[mIndex][ii][1];
					if (equations[yy][xx][0] < 0)			// subtract fixed puzzle values
					{
						equations[y][x][1] -= equations[yy][xx][1];
					}
					else if (equations[yy][xx][0] > 0)
					{
						for (int v = 1; v < MAX_VARIABLES+2; v++)
						{
							equations[y][x][v] -= equations[yy][xx][v];
						}
					}
				}
				equations[y][x][0] = 1;						// we have an equation here now
			}
			if (--min == 0)
				break;
		}
	}
	// set equation for last cell
	return true;
}


void StartEquations()
{
	equationString0[0] = 0;						// clear testing string
	for (int v = 0; v < MAX_VARIABLES; v++)
	{
		available[v] = true;
		variablePos[v][0] = variablePos[v][1] = -1;	// sowe can tell if this variable is ever used
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (min[i][j] == max[i][j])
			{
				equations[i][j][0] = -1;
				equations[i][j][1] = min[i][j];
			}
			else
			{
				equations[i][j][0] = 0;
				equations[i][j][1] = 0;
			}
			for (int ii = 2; ii < 2 + MAX_VARIABLES; ii++)
				equations[i][j][ii] = 0;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		equationsDone[i] = EquationDone(i);
	}
}


void SetUnresolved(int x, int y)
{
	int index = (y << 2) + x;
	for (int i = 0; i < 3; i++)
	{
		if (indexToTotalIndex[index][i] < 0)
			continue;
		resolved[indexToTotalIndex[index][i]] = false;
	}
}


bool CheckMinMax(int index)
{
	int minTotal = 0;
	int maxTotal = 0;
	int x, y;
	bool changed = false;
	puzzleFailed = false;
	for (int i = 0; i < 4; i++)
	{
		y = totalIndexToPos[index][i][0];
		x = totalIndexToPos[index][i][1];
		if (min[y][x] == 0)									// set min value now
		{
			min[y][x] = 1;
			changed = true;
		}
		minTotal += min[y][x];
		maxTotal += max[y][x];
	}
	int count;
	for (int i = 0; i < 4; i++)
	{
		y = totalIndexToPos[index][i][0];
		x = totalIndexToPos[index][i][1];
		if (min[y][x] == max[y][x])							// nothing can change so try another position
			continue;
		count = totals[index] - (maxTotal - max[y][x]);		// min value for this entry
		if (count <= 0)
			count = 1;
		if (count > min[y][x])
		{ 
			minTotal += count - min[y][x];					// new min total
			min[y][x] = count;
			changed = true;
		}
		count = totals[index] - (minTotal - min[y][x]);		// max value for this entry
		if (count > 9)
			count = 9;
		if (count < max[y][x])
		{
			maxTotal += count - max[y][x];					// new max total
			max[y][x] = count;
			changed = true;
		}
		if (minTotal > maxTotal)							// puzzle failed
		{
			puzzleFailed = true;
			return false;
		}
		if (changed)										// flag totals as unresolved
			SetUnresolved(x, y);
	}
	resolved[index] = true;
	return changed;
}


bool NextPosition(int & x, int &y)
{
	if (min[y][x] == max[y][x])
	{
		if (++x == 4)
		{
			x = 0;
			if (++y == 4)
				return false;
		}
	}
	return true;
}


// where n = direction 0-9
bool ValidTotal(int n)
{
	int minTotal = 0;
	int maxTotal = 0;
	for (int i = 0; i < 4; i++)
	{
		int y = totalIndexToPos[n][i][0];
		int x = totalIndexToPos[n][i][1];
		minTotal += min[y][x];
		maxTotal += max[y][x];
	}
	if (minTotal > totals[n]
	|| maxTotal < totals[n])
		return false;										// invalid total
	return true;
}


// where n = direction 0-9
int Total(int n)
{
	int total = 0;
	for (int i = 0; i < 4; i++)
	{
		int y = totalIndexToPos[n][i][0];
		int x = totalIndexToPos[n][i][1];
		if (min[y][x] == max[y][x])
			total += min[y][x];
	}
	return total;
}


// check all totals that use this position
bool ValidTotals(int row, int col)
{
	int n = (row << 2) + col;
	for (int i = 0; i < 3; i++)
	{
		int mm = indexToTotalIndex[n][i];					
		if (mm < 0)
			continue;
		int minTotal = 0;
		int maxTotal = 0;
		int x, y;
		for (int i = 0; i < 4; i++)
		{
			y = totalIndexToPos[mm][i][0];
			x = totalIndexToPos[mm][i][1];
			minTotal += min[y][x];
			maxTotal += max[y][x];
		}
		if (minTotal > totals[mm]
		||  maxTotal < totals[mm])
			return false;									// invalid entries
	}
	return true;
}


// if file is null do not print the solutions
void Solve(FILE * file, int x, int y)
{
	int n = (y << 2) + x;									// index into totals array
	int start0, end0;
	int start = min[y][x];
	int end = max[y][x];
	start0 = start;
	end0 = end;

	for (int m = start0; m <= end0; m++)
	{
		min[y][x] = m;
		max[y][x] = m;
		if (ValidTotals(y, x))								// see if the totals are still valid
		{
			int x1 = x;
			int y1 = y;
			if (NextPosition(x1, y1))						// find starting location							
				Solve(file, x1, y1);						// recurse on next location
			else
			{
				solutions++;								// complete solution
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						solutionMask[i][j] |= 1 << min[i][j];
						if (solutionMin[i][j] > min[i][j])
							solutionMin[i][j] = min[i][j];
						if (solutionMax[i][j] < max[i][j])
							solutionMax[i][j] = max[i][j];
					}
				}
				if (file != NULL)
				{
					fprintf(file, "            | %2d\n", totals[0]);
					for (int i = 0; i < 4; i++)
					{
						fprintf(file, "%2d %2d %2d %2d | %2d\n",
							min[i][0], min[i][1], min[i][2], min[i][3], totals[i + 1]);
					}
					fprintf(file, "------------+\n");
					fprintf(file, "%2d %2d %2d %2d   %2d\n\n",
						totals[9], totals[8], totals[7], totals[6], totals[5]);
				}
			}
		}
	}
	min[y][x] = start;
	max[y][x] = end;
}


void SolvePuzzle(HWND hWnd)
{
	FILE * file;

	solutions = 0;
	file = fopen("solutions.txt", "w");
	if (file == NULL)
	{
		MessageBox(hWnd, "Could not open solutions.txt!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	int x = 0;
	int y = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			solutionMask[i][j] = 0;
			solutionMin[i][j] = 9;
			solutionMax[i][j] = 1;
		}
	}
	NextPosition(x, y);										// find starting location							
	Solve(file, x, y);										// find solution
	// print all min and max ranges
	fprintf(file, "                | %2d\n", totals[0]);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (solutionMin[i][j] == solutionMax[i][j])
				fprintf(file, " %d  ", solutionMin[i][j]);
			else if (CheckRangeForHoles(i,j))
				fprintf(file, "%d,%d ", solutionMin[i][j], solutionMax[i][j]);
			else
				fprintf(file, "%d-%d ", solutionMin[i][j], solutionMax[i][j]);
		}
		fprintf(file, "| %2d\n", totals[i + 1]);

	}
	fprintf(file, "----------------+\n");
	fprintf(file, "%2d  %2d  %2d  %2d    %2d\n\n",
		totals[9], totals[8], totals[7], totals[6], totals[5]);
	fclose(file);
}


struct PertData
{
	int count;
	int total;
	int low;
	int dir;
	double offset;
} pertData[9];

// return 0 when we are done so exit perturbation mode
// return 1 when a change was made
// return 2 when a change was made by guessing
// return -1 when we failed
// oneStep is true if we are doing just one perturbation step 
// and stopping
// if we are guessing do not stop even if equations >= unknowns
int NextPerturbation(bool testing, bool oneStep)
{
	int changes = 0;
	int unknowns = 0;
	int equations = 0;
	for (int index = 0; index < 10; index++)
	{
		if (resolved[index])								// find unresolved direction
			continue;
		if (ValidTotal(index) == false)
			return -1;										// if we are going to fail exit now
		if (CheckMinMax(index))								// redo any new min and max values
			return 1;
		if (puzzleFailed)									// puzzle is now invalid with no solutions
			return -1;
		changes++;
	}
	if (changes > 0)										// we resolved some directions without and changes
		return 1;
	if (oneStep)											// do only one perturbation so stop
		return 0;
	if (doAllPerturbations == false)
	{
		for (int row0 = 0; row0 < 4; row0++)
		{
			for (int col0 = 0; col0 < 4; col0++)
			{
				if (min[row0][col0] != max[row0][col0])
					unknowns++;
			}
		}
		for (int index = 0; index < 10; index++)
		{
			if (Total(index) != totals[index])
				equations++;
		}
		if (unknowns <= equations)							// we should be able to solve now by equations
			return 0;
	}
	FILE* file = NULL;
#if DEBUG_PERTURBATIONS
	if (testing == false)
		file = fopen("perturbations.txt", "a");
#endif
	int bestRow = -1, bestCol = -1, bestVal = 999;
	double bestOffset = 0.0;
	double bestAvgPert = 99.0;
	int bestOtherRange = 0;
	int bestDir = 0;
	int bestPerturbation = 99;
	bool bestDiag;
	for (int row0 = 0; row0 < 4; row0++)
	{
		for (int col0 = 0; col0 < 4; col0++)
		{
			if (min[row0][col0] == max[row0][col0])			// find a cell we can check
				continue;
			// find direction using row0 col0 with 3 unfinished cells 
			int row1, col1, row2, col2;
			int range, otherRange;
			double offset;
			int index = (row0 << 2) + col0;
			bool diagonal = false;
			if (row0 == col0 || row0 + col0 == 3)
				diagonal = true;
			// optional - SKIP ALL NON_DIAGONALS
			if (diagonal == false)
				continue;
			for (int i = 0; i < 9; i++)
			{
				pertData[i].count = 0;
				pertData[i].total = 0;
				pertData[i].low = 99;
				pertData[i].offset = 0.0;
			}
			for (int i = 0; i < 3; i++)
			{
				int dir = indexToTotalIndex[index][i];		// try this direction
				if (dir < 0)								// no valid direction
					continue;
				int count = 0;
				int total = 0;
				row1 = -1;
				for (int i = 0; i < 4; i++)
				{
					int row = totalIndexToPos[dir][i][0];
					int col = totalIndexToPos[dir][i][1];
					if (min[row][col] == max[row][col])
					{
						total = totals[dir] - min[row][col];	// total remaining
						continue;
					}
					count++;
					if (row == row0 && col == col0)
						continue;
					if (row1 < 0)
					{
						row1 = row;
						col1 = col;
					}
					else
					{
						row2 = row;
						col2 = col;
					}
				}
				if (count < 3)								// not enough cells to check
					continue;
				// find best perturbation for all choices
				int perturbation;
				for (int m = min[row0][col0]; m <= max[row0][col0]; m++)
				{
					int t = total - m;						// remaining total
					int min1 = t - max[row2][col2];
					if (min1 < min[row1][col1])
						min1 = min[row1][col1];
					int max1 = t - min[row2][col2];
					if (max1 > max[row1][col1])
						max1 = max[row1][col1];
					int min2 = t - max[row1][col1];
					if (min2 < min[row2][col2])
						min2 = min[row2][col2];
					int max2 = t - min[row1][col1];
					if (max2 > max[row2][col2])
						max2 = max[row2][col2];
					int delta = m - min[row0][col0];
					otherRange = max[row1][col1] - min[row1][col1] + 1;
					otherRange += max[row2][col2] - min[row2][col2] + 1;
					range = max[row0][col0] - min[row0][col0] + 1;
					if (delta > max[row0][col0] - m)
						delta = max[row0][col0] - m;
					offset = 100.0 * delta / (int)(range/2);
					perturbation = min1 - min[row1][col1];
					perturbation += max[row1][col1] - max1;
					perturbation += min2 - min[row2][col2];
					perturbation += max[row2][col2] - max2;
					pertData[m - 1].count++;
					pertData[m - 1].total += perturbation;
					if (pertData[m - 1].low > perturbation)
					{
						pertData[m - 1].low = perturbation;
						pertData[m - 1].dir = dir;
						pertData[m - 1].offset += offset;
					}
					if (file != NULL)
						fprintf(file, "(%d,%d)=%d dir=%d pert=%d offset=%.1f%% %s\n", 
							row0, col0, m, dir, perturbation, offset, 
							(solutionMask[row0][col0] & (1 << m)) == 0 ? "fail" : "");
#if USE_AVERAGE_PERTURBATIONS == 0		
					// all these were tried with 10,000 samples
#if 0
					// best perturbation with lowest otherRange
					// seed=1 solve=61.38%
					//	type[0]=1806 solved=33.67%
					//	type[1]=3594 solved=60.66%
					//	type[2]=3666 solved=65.93%
					//	type[3]=934 solved=99.89%
					if (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& bestOtherRange < otherRange))
#endif
#if 0
					// best perturbation with highest offset (middle of min max range)
					// seed=1 solve=55.67%
					//	type[0]=1806 solved=35.44%
					//	type[1]=3594 solved=48.02%
					//	type[2]=3666 solved=61.87%
					//	type[3]=934 solved=99.89%
					if (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& bestOffset < offset))
#endif
#if 0
					// best perturbation on a diagonal with highest offset (middle of min max range)
					// seed=1 solve=55.67%
					//	type[0]=1806 solved=38.87%
					//	type[1]=3594 solved=60.66%
					//	type[2]=3666 solved=69.91%
					//	type[3]=934 solved=100.00%
					if (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& bestOffset < offset
						&& diagonal == true))				// pick only diagonal entries
#endif
#if 0
					// best perturbation with lowest offset (close to min or max)
					// seed=1 solve=62.60%
					//	type[0]=1806 solved=31.56%
					//	type[1]=3594 solved=59.63%
					//	type[2]=3666 solved=71.28%
					//	type[3]=934 solved=100.00%
					if (diagonal == true
					&& (perturbation < bestPerturbation
					  || (perturbation == bestPerturbation
						&& bestOffset > offset)))
#endif
#if 0
					// Take the first best perturbation
					// seed=1 solve=62.18%
					//	type[0]=1806 solved=35.71%
					//	type[1]=3594 solved=58.29%
					//	type[2]=3666 solved=69.39%
					//	type[3]=934 solved=100.00%
					if (perturbation < bestPerturbation)
#endif
#if 0				
					// Pick the 1st best non-diagonal 
					// seed=1 solve=51.79%
					//	type[0]=1806 solved=28.74%
					//	type[1]=3594 solved=47.52%
					//	type[2]=3666 solved=55.24%
					//	type[3]=934 solved=99.25%
					if (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& diagonal == false
						&& bestDiag == true))			// take 1st best non-diagonal case
#endif
#if 0				
					// The best diagonal pertubation with the lowest offset
					// seed=1 solve=%65.86%
					//	type[0]=1806 solved=31.34%
					//	type[1]=3594 solved=64.75%
					//	type[2]=3666 solved=75.26%
					//	type[3]=934 solved=100.00%
					if (diagonal == true				// pick only diagonal entries
					&& (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& bestOffset > offset)))
#endif
#if 0				
					// Pick the 1st best diagonal unless the non-diagonal is better
					// seed=1 solve=67.73%
					//	type[0]=1806 solved=35.66%
					//	type[1]=3594 solved=66.53%
					//	type[2]=3666 solved=76.49%
					//	type[3]=934 solved=100.00%
					if (perturbation < bestPerturbation
					|| (perturbation == bestPerturbation
						&& diagonal == true
						&& bestDiag == false))			// take 1st best diagonal case
#endif
#if 1				
					// The first best diagonal pertubation 
					// seed=1 solve=67.97%
					//	type[0]=1806 solved=34.22%
					//	type[1]=3594 solved=67.39%
					//	type[2]=3666 solved=77.00%
					//	type[3]=934 solved=100.00%
					if (perturbation < bestPerturbation
					&& diagonal == true)				// pick only diagonal entries
#endif
					{
						bestDir = dir;
						bestPerturbation = perturbation;
						bestVal = m;
						bestRow = row0;
						bestCol = col0;
						bestOffset = offset;
						bestOtherRange = otherRange;
						bestDiag = diagonal;
					}
#endif
				}
			}
#if USE_AVERAGE_PERTURBATIONS			
			// The first best diagonal with lowest average pertubation 
			// seed=1 solve= 87.92%
			//	type[0] = 1806 solved = 81.17 %
			//	type[1] = 3594 solved = 87.28 %
			//	type[2] = 3666 solved = 88.79 %
			//	type[3] = 934 solved = 100.00 %
			if (diagonal == false)
				continue;
			for (int i = 0; i < 9; i++)
			{
				if (pertData[i].count == 0)					// no data to average
					continue;
				int excluded;
				for (excluded = 0; excluded < exclusions; excluded++)	// ignore this if excluded
				{
					if (exclude[excluded][0] == row0
					&& exclude[excluded][1] == col0
					&& exclude[excluded][2] == i + 1)
						break;
				}
				double average = (double)pertData[i].total / pertData[i].count;
				if (file != NULL)
					fprintf(file, "(%d,%d)=%d pert=%d avgPert=%.1f avgOffset=%.1f%% %s %s\n",
						row0, col0, i+1, pertData[i].low, average, pertData[i].offset/pertData[i].count,
						(solutionMask[row0][col0] & (1 << (i+1))) == 0 ? "fail" : "",
						(excluded < exclusions ? "excluded" : ""));
				if (excluded < exclusions)					// skip excluded tries
					continue;
				int type = GetPuzzleType();
//				if (type > TYPE_1)				// type 2 does poorly average perturbation only
				if (true)
				{
					// find lowest perturbation and use avgPerturbation as a tie breaker
					// this solves about 85% of the puzzles with max 2 passes of perturbations
					if (pertData[i].low < bestPerturbation
					|| (pertData[i].low == bestPerturbation
						&& average < bestAvgPert))
					{
						bestDir = pertData[i].dir;
						bestPerturbation = pertData[i].low;
						bestAvgPert = average;
						bestVal = i + 1;
						bestRow = row0;
						bestCol = col0;
						bestOffset = pertData[i].offset;
						bestOtherRange = 0;
						bestDiag = diagonal;
					}
				}
				else
				{
					// use lowest average perturbation
					// this solves about 82% of the puzzles with max 2 passes of perturbations
					if (average < bestAvgPert)
					{
						bestDir = pertData[i].dir;
						bestPerturbation = pertData[i].low;
						bestAvgPert = average;
						bestVal = i + 1;
						bestRow = row0;
						bestCol = col0;
						bestOffset = pertData[i].offset;
						bestOtherRange = 0;
						bestDiag = diagonal;
					}
				}
			}
#endif
		}
	}
	if (bestPerturbation == 99)								// we found nothing
	{
		if (file != NULL)
			fclose(file);
		return 0;
	}
	if (file != NULL)
	{
#if USE_AVERAGE_PERTURBATIONS			
		fprintf(file, "--------------- (%d,%d)=%d dir=%d pert=%d avgPert=%.2f offset=%.1f%% %s\n",
			bestRow, bestCol, bestVal, bestDir, bestPerturbation, bestAvgPert, bestOffset,
			(solutionMask[bestRow][bestCol] & (1 << bestVal)) == 0 ? "fail" : "");
#else
		fprintf(file, "--------------- (%d,%d)=%d dir=%d pert=%d offset=%.1f%% %s\n",
			bestRow, bestCol, bestVal, bestDir, bestPerturbation, bestOffset,
			(solutionMask[bestRow][bestCol] & (1 << bestVal)) == 0 ? "fail" : "");
#endif
		fclose(file);
	}
	min[bestRow][bestCol] = max[bestRow][bestCol] = bestVal;
	exclude[exclusions][0] = bestRow;					// save this now in case we fail our guess
	exclude[exclusions][1] = bestCol;
	exclude[exclusions][2] = bestVal;
	SetUnresolved(bestCol, bestRow);					// unresolve totals
#if DISPLAY_EQUATIONS
	switch (bestDir)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		sprintf(equationString, "(%d,%d)=%d row %d perturbation=%d", bestRow, bestCol, bestVal, bestDir - 1, bestPerturbation);
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		sprintf(equationString, "(%d,%d)=%d col %d perturbation=%d", bestRow, bestCol, bestVal, 9 - bestDir, bestPerturbation);
		break;
	case 0:
		sprintf(equationString, "(%d,%d)=%d diag0 perturbation=%d", bestRow, bestCol, bestVal, bestPerturbation);
		break;
	default:
	case 5:
		sprintf(equationString, "(%d,%d)=%d diag1 perturbation=%d", bestRow, bestCol, bestVal, bestPerturbation);
		break;
	}
#endif
	return 2;
}


// To create a new puzzle I will randomly fill the 4x4 cells first with random numbers
// Next I will add up the 10 totals and then remove all but 4 numbers
// leaving one on each row and col but do not allow more than 2 on any diagonal
// This will guarantee at least one solution
void CreatePuzzle()
{
	for (int i = 0; i < 10; i++)
	{
		resolved[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			min[i][j] = max[i][j] = puzzle[i][j] = Random(9) + 1;
		}
	}
	// now add up all totals
	for (int i = 0; i < 10; i++)
	{
		totals[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			int y = totalIndexToPos[i][j][0];
			int x = totalIndexToPos[i][j][1];
			totals[i] += puzzle[y][x];
		}
	}
	// Now remove entries leaving one entry per row and column
	// but do not allow more than 2 in a column
//RETRY:
	int choice = Random(22);						// what pattern of numbers will we use
//	choice = 6;										// type 0 
//	choice = 1;										// choice with both diagonals with 2 cells
//	choice = 20;									// choice with both diagonals with 2 cells
//	choice = 21;									// choice with one diagonal with 2 cells
//	if (choice == 1 || choice == 20)				// test solutions without both diagonals having two cells
//		goto RETRY;
	for (int col = 0; col < 4; col++)
	{
		int row = rowChoices[choice][col];
		for (int x = 0; x < 4; x++)
		{
			if (x != row)
			{
				puzzle[col][x] = 0;
				min[col][x] = 0;
				max[col][x] = 9;
			}
		}
	}
	int x = 0;
	int y = 0;
	NextPosition(x, y);								// find starting location							
}


// determine ending equation details
// returns true if puzzle solved (i.e. min and max are valid)
// eclass is EQUATION_CLASS
// holes is number of holes in the range that will not lead to a solution
// varUsed = number of variables used to get to the end (be sure to set variablePos[][] to < 0 before starting)
bool EquationClassification(EQUATION_CLASS &eclass, int &holes, int &varUsed, int &varEnd)
{
	varEnd = 0;
	varUsed = 0;
	for (int i = 0; i < MAX_VARIABLES; i++)
	{
		if (variablePos[i][0] >= 0)
			varUsed++;
		if (available[i] == false)
			varEnd++;
	}
	bool solved = true;
	eclass = CLASS_0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (solutionMin[y][x] > min[y][x]
			|| solutionMax[y][x] < max[y][x])
				solved = false;
			if (varEnd > 0
			&&  equations[y][x][0] > 0)
			{
				int count = 0;
				for (int v = 0; v < MAX_VARIABLES; v++)
				{
					if (equations[y][x][2 + v] != 0)
						count++;
				}
				if (count > 2)
					eclass = CLASS_4;
				else if (count == 2
				&& eclass < CLASS_3)
					eclass = CLASS_3;
				else if (count == 1
				&& varEnd > 1
				&& eclass < CLASS_2)
					eclass = CLASS_2;
				else if (count == 1
				&& eclass < CLASS_1)
					eclass = CLASS_1;
			}
		}
	}
	holes = 0;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (CheckRangeForHoles(c, r))
			{
				holes++;
			}
		}
	}
	return solved;
};


void TestPuzzles(int count, U32 seed)
{
	time_t now;
	time(&now);
	struct tm* time;
	time = localtime(&now);
	char timeString[50];
	char fileString[64];

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	RandomSeed(seed);							// so we get the same puzzles with the same seed

	sprintf(timeString, "%04d.%02d.%02d-%02d.%02d.%02d", time->tm_year+1900, time->tm_mon+1, time->tm_mday,
		time->tm_hour, time->tm_min, time->tm_sec);
	
	// create Test folder if needed
	bool creastedDir = CreateDirectory("Test", NULL) || ERROR_ALREADY_EXISTS == GetLastError();

	// open Test\summary.txt as append for count of solutions
	FILE * summary = NULL;
	summary = fopen("Test\\summary.txt", "a");
	if (summary == NULL)
		return;

	state = STATE_WAIT;								// set this so the saved file opens correctly
	int maxSolutions = 1;
	int puzzlesWithHolesInRange = 0;
	int minsTotal = 0;
	int maxsTotal = 0;
	int minsFailed = 0;
	int maxsFailed = 0;
	int totalFailed = 0;
	int typesTotal[5];
	int typesFailed[5];
	int totalGuessTried = 0;
	int eclassCount[CLASS_MAX];
	int countVariablesUsed[MAX_VARIABLES + 1];
	int countVariablesEnd[MAX_VARIABLES + 1];
	int maxVariablesUsed = 0;
	EQUATION_CLASS maxEClass = CLASS_0;
	int endSolutionTotal = 0;
	int endSolutionCount[10];
	for (int i = 0; i < 5; i++)
	{
		typesTotal[i] = 0;
		typesFailed[i] = 0;
	}
	for (int i = 0; i < 10; i++)
		endSolutionCount[i] = 0;
	for (int i = 0; i <= MAX_VARIABLES; i++)
	{
		countVariablesUsed[i] = 0;
		countVariablesEnd[i] = 0;
	}
	for (int i = 0; i < CLASS_MAX; i++)
		eclassCount[i] = 0;
	int guesses = 0;
	for (int i = 1; i <= count; i++)
	{
		CreatePuzzle();							// create puzzle
		// save puzzle too
		snprintf(fileString, sizeof(fileString), "Test//%s puzzle %d.txt", &timeString, i);
		SaveTextFile(fileString);
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				if (puzzle[c][r] == 0)
				{
					min[c][r] = 1;				// otherwise solutions will use 0 for solutions
					max[c][r] = 9;
				}
				else
				{
					min[c][r] = max[c][r] = puzzle[c][r];
				}
				solutionMask[c][r] = 0;
				solutionMin[c][r] = 9;
				solutionMax[c][r] = 1;
			}
		}
		int x = 0;
		int y = 0;
		NextPosition(x, y);						// find starting location	
		solutions = 0;
		Solve(NULL, x, y);						// solve puzzle
		if (maxSolutions < solutions)
			maxSolutions = solutions;
		int res = 0;
		int startSolutions = solutions;
		// -------------------------------------------------
		// now do perturbations first
		int type = GetPuzzleType();				// what type of puzzle we have
		typesTotal[type]++;
		if (testMode >= 0)						// perturbations only or perturbations+equations
		{
			int pass = 0;
			bool complete = true;
			EQUATION_CLASS eclass = CLASS_0;
			int varUsed = 0;
			int varEnd = 0;
			int holes = 0;
			while (true)
			{
				if ((res = NextPerturbation(true, false)) <= 0)
					break;
				if (res > 1)
				{
					guesses++;
					pass++;
				}
			}
			if (res < 0)
			{
				totalFailed++;
				typesFailed[type]++;
			}
			else
			{
				if (PuzzleComplete())
				{
					endSolutionCount[1]++;
					endSolutionTotal++;
					solutions = 1;
				}
				else 
				{
					solutions = 0;
					Solve(NULL, x, y);			// solve puzzle again to make sure we have no errors
					if (solutions > 9)
						endSolutionCount[9]++;
					else
					{
						endSolutionCount[solutions]++;
						if (solutions == 0)
						{
							typesFailed[type]++;
							totalFailed++;
						}
					}
					endSolutionTotal++;
				}
				// -------------------------------------------------
				// test perturbations and then equations
				if (testMode > 0
				&& solutions == 1)
				{
					eclassCount[CLASS_0]++;
				}
				else if (testMode > 0				// test perturbations and then equations
				&& solutions > 0)
				{
					// try equations now
					StartEquations();
					equationOrderIndex = 0;
					bool guessTried = false;
					while (true)
					{
						if (SetNextEquation(true) == false)		// we are done
							break;
						if (equationString0[0] != 0)			// if we tried a guess
							guessTried = true;
						if (equationString0[0] != 0				// we are making a guess
						&& InvalidMinMax())						// an error occurred
						{
							RestoreEquations(true);				// update ranges
						}
					}
					complete = EquationClassification(eclass, holes, varUsed, varEnd);
					if (maxVariablesUsed < varUsed)
						maxVariablesUsed = varUsed;
					if (maxEClass < eclass)
						maxEClass = eclass;
					countVariablesUsed[varEnd]++;
					eclassCount[eclass]++;
					if (guessTried)
						totalGuessTried++;
					if (holes > 0)
						puzzlesWithHolesInRange++;
					if (complete == false)
					{
						totalFailed++;
						typesFailed[type]++;
					}
				}
			}
			if (summary != NULL)
			{
				if (res < 0)
					fprintf(summary, "%s puzzle %d type=%d solutions=%d ---------------- Failed pass=%d\n", 
						&timeString, i, type, solutions, pass);
				else if (testMode == 0
				|| solutions == 0)
					fprintf(summary, "%s puzzle %d type=%d solutions=%d endSolutions=%d passes=%d %s\n", 
						&timeString, i, type, startSolutions, solutions, pass, (solutions == 0 ? "-------- Failed" : ""));
				else
					fprintf(summary, "%s puzzle %d type=%d solutions=%d eclass=%d varUsed=%d %s %s\n",
						&timeString, i, type, solutions, eclass, varUsed, 
						(holes ? "hole in range" : ""), (complete == false ? "-------- Incomplete" : ""));
			}
		}
		else
		{
			// -------------------------------------------------
			// now start with equations to solve the puzzle 
			StartEquations();
			equationOrderIndex = 0;
			bool guessTried = false;
			bool complete = true;
			EQUATION_CLASS eclass = CLASS_0;
			int varUsed = 0;
			int varEnd = 0;
			int holes = 0;
			while (true)
			{
				if (SetNextEquation(true) == false)		// we are done
					break;
				if (equationString0[0] != 0)
					guessTried = true;
				if (equationString0[0] != 0				// we are making a guess
				&& InvalidMinMax())						// an error occurred
				{
					RestoreEquations(true);				// our guess succeeded
				}
			}
			complete = EquationClassification(eclass, holes, varUsed, varEnd);
			if (maxVariablesUsed < varUsed)
				maxVariablesUsed = varUsed;
			if (maxEClass < eclass)
				maxEClass = eclass;
			countVariablesUsed[varEnd]++;
			eclassCount[eclass]++;
			if (guessTried)
				totalGuessTried++;
			if (holes > 0)
				puzzlesWithHolesInRange++;
			int mins = 0;
			int maxs = 0;
			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					if (solutionMin[c][r] != min[c][r])
					{
						mins++;
					}
					if (solutionMax[c][r] != max[c][r])
					{
						maxs++;
					}
				}
			}
			if (testMode == -1)			// equations only
			{
				if (solutions > 9)
					endSolutionCount[9]++;
				else
					endSolutionCount[solutions]++;
				endSolutionTotal++;
				if (complete == false)
				{
					totalFailed++;
					typesFailed[type]++;
				}
				minsTotal += mins;
				maxsTotal += maxs;
				// append information to the summary file
				if (summary != NULL)
				{
					if (complete)
						fprintf(summary, "%s puzzle %d type=%d solutions=%d variables=%d %s %s\n",
							&timeString, i, type, solutions, varUsed, (guessTried ? "2-pass equations" : ""),
							(holes ? "hole in range" : ""));
					else
						fprintf(summary, "%s puzzle %d type=%d solutions=%d variables=%d mins=%d maxs=%d %s\n", 
							&timeString, i, type, solutions, varUsed, mins, maxs, (holes ? "hole in range" : ""));
				}
			}
			// -------------------------------------------------
			// now do equations then perturbations  
			else
			{
				if (complete = PuzzleComplete())
				{
					solutions = 1;
					res = 0;						// we are done
				}
				while (complete == false)
				{
					if ((res = NextPerturbation(true, false)) <= 0)
						break;
					if (res > 1)
						guesses++;
				}
				if (res < 0)
				{
					typesFailed[type]++;
					totalFailed++;
				}
				else
				{
					if (PuzzleComplete())
					{
						endSolutionCount[1]++;
						endSolutionTotal++;
						solutions = 1;
					}
					else
					{
						solutions = 0;
						Solve(NULL, x, y);			// solve puzzle again to make sure we have no errors
						if (solutions > 9)
							endSolutionCount[9]++;
						else
						{
							endSolutionCount[solutions]++;
							if (solutions == 0)
							{
								typesFailed[type]++;
								totalFailed++;
							}
						}
						endSolutionTotal++;
					}
				}
				if (summary != NULL)
				{
					if (complete)
						fprintf(summary, "%s puzzle %d type=%d solutions=%d Complete %s\n",
							&timeString, i, type, solutions, (holes ? "hole in range " : ""));
					else if (res < 0)
						fprintf(summary, "%s puzzle %d type=%d solutions=%d %s------- Failed\n",
							&timeString, i, type, solutions, (holes ? "hole in range " : ""));
					else
						fprintf(summary, "%s puzzle %d type=%d solutions=%d endSolutions=%d %s%s\n",
							&timeString, i, type, startSolutions, solutions, 
							(holes ? "hole in range " : ""), (solutions == 0 ? "-------- Failed" : ""));
				}
			}
		}
	}
	// close summary file
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	if (summary != NULL)
	{
		if (testMode == -1)
			fprintf(summary, "Test Equations\n");
		else if (testMode < -1)
			fprintf(summary, "Test Equations then Perturbations\n");
		else if (testMode == 0)
			fprintf(summary, "Test Perturbations\n");
		else 
			fprintf(summary, "Test Perturbations then equations\n");
		fprintf(summary, "CPU time = %.3f\nrandom seed=0x%x\n", cpu_time_used, seed);
		for (int i = 0; i < TYPE_MAX; i++)
		{
			if (typesTotal[i] > 0)
				fprintf(summary, "type[%d]=%d solved=%.2f%%\n", i, typesTotal[i], 100.0 * (typesTotal[i] - typesFailed[i]) / typesTotal[i]);
		}
		if (testMode != 0)								// we do not use eclss on perturbations
		{
			for (int i = 0; i < CLASS_MAX; i++)
			{
				fprintf(summary, "eclass[%d]=%d %.2f%%\n", i, eclassCount[i], 100.0 * eclassCount[i] / endSolutionTotal);
			}
		}
		if (testMode == 0)								// perturbations only
		{
			fprintf(summary, "maxSolutions=%d\nGuesses=%d\nPuzzle solved=%.2f%%\n",
				maxSolutions, guesses, 100.0 * (count - totalFailed - endSolutionCount[0]) / count);
			fprintf(summary, "Puzzle failed=%.2f%%\nNo solutions=%.2f%%\n",
				100.0 * totalFailed / count, 100.0 * endSolutionCount[0] / count);
		}
		else 
		{
			fprintf(summary, "order=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				equationOrder[0][0], equationOrder[0][1], equationOrder[0][2], equationOrder[0][3], equationOrder[0][4],
				equationOrder[0][5], equationOrder[0][6], equationOrder[0][7], equationOrder[0][8], equationOrder[0][9]);
			fprintf(summary, "puzzles with holes in ranges=%d\n", puzzlesWithHolesInRange);
			if (testMode == -1)					// equations only
			{
				fprintf(summary, "maxSolutions=%d\nPuzzle solved=%.2f%%\n",
					maxSolutions, 100.0 * (count - totalFailed) / count);
				fprintf(summary, "Puzzles using 2-pass equations=%.2f%%\n", 100.0 * totalGuessTried / count);
				fprintf(summary, "Number of ending variables\n");
				for (int v = 0; v <= maxVariablesUsed; v++)
					fprintf(summary, "CountVariables[%d]=%d\n", v, countVariablesUsed[v]);
				fprintf(summary, "Undetected mins=%d maxs=%d total=%d\n",
					minsTotal, maxsTotal, minsTotal + maxsTotal);
			}
			else						// equations then minimal perturbations
			{
				fprintf(summary, "maxSolutions=%d\nGuesses=%d\nPuzzle solved=%.2f%%\n",
					maxSolutions, guesses, 100.0 * (count - totalFailed - endSolutionCount[0]) / count);
				fprintf(summary, "Puzzle failed=%.2f%%\nNo solutions=%.2f%%\n",
					100.0 * totalFailed / count, 100.0 * endSolutionCount[0] / count);
			}
		}
		if (endSolutionTotal > 0)
		{
			for (int i = 1; i < 10; i++)
			{
				fprintf(summary, "solutions[%d]=%3d %5.2f%%\n", i, endSolutionCount[i], endSolutionCount[i] * 100.0 / endSolutionTotal);
			}
		}
		fclose(summary);
	}
}
