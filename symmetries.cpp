#include "stdafx.h"


void HFlip()
{
	int t;
	for (int y = 0; y < 4; y++)
	{
		t = puzzle[y][0];
		puzzle[y][0] = puzzle[y][3];
		puzzle[y][3] = t;
		t = puzzle[y][1];
		puzzle[y][1] = puzzle[y][2];
		puzzle[y][2] = t;
		t = restart[y][0];
		restart[y][0] = restart[y][3];
		restart[y][3] = t;
		t = restart[y][1];
		restart[y][1] = restart[y][2];
		restart[y][2] = t;
		t = min[y][0];
		min[y][0] = min[y][3];
		min[y][3] = t;
		t = min[y][1];
		min[y][1] = min[y][2];
		min[y][2] = t;
		t = max[y][0];
		max[y][0] = max[y][3];
		max[y][3] = t;
		t = max[y][1];
		max[y][1] = max[y][2];
		max[y][2] = t;
		t = solutionMin[y][0];
		solutionMin[y][0] = solutionMin[y][3];
		solutionMin[y][3] = t;
		t = solutionMin[y][1];
		solutionMin[y][1] = solutionMin[y][2];
		solutionMin[y][2] = t;
		t = solutionMax[y][0];
		solutionMax[y][0] = solutionMax[y][3];
		solutionMax[y][3] = t;
		t = solutionMax[y][1];
		solutionMax[y][1] = solutionMax[y][2];
		solutionMax[y][2] = t;
		t = solutionMask[y][0];
		solutionMask[y][0] = solutionMask[y][3];
		solutionMask[y][3] = t;
		t = solutionMask[y][1];
		solutionMask[y][1] = solutionMask[y][2];
		solutionMask[y][2] = t;
	}
	t = totals[9];
	totals[9] = totals[6];
	totals[6] = t;
	t = totals[8];
	totals[8] = totals[7];
	totals[7] = t;
	t = totals[0];
	totals[0] = totals[5];
	totals[5] = t;
	t = resolved[9];
	resolved[9] = resolved[6];
	resolved[6] = t;
	t = resolved[8];
	resolved[8] = resolved[7];
	resolved[7] = t;
	t = resolved[0];
	resolved[0] = resolved[5];
	resolved[5] = t;
}

void VFlip()
{
	int t;
	for (int x = 0; x < 4; x++)
	{
		t = puzzle[0][x];
		puzzle[0][x] = puzzle[3][x];
		puzzle[3][x] = t;
		t = puzzle[1][x];
		puzzle[1][x] = puzzle[2][x];
		puzzle[2][x] = t;
		t = restart[0][x];
		restart[0][x] = restart[3][x];
		restart[3][x] = t;
		t = restart[1][x];
		restart[1][x] = restart[2][x];
		restart[2][x] = t;
		t = min[0][x];
		min[0][x] = min[3][x];
		min[3][x] = t;
		t = min[1][x];
		min[1][x] = min[2][x];
		min[2][x] = t;
		t = max[0][x];
		max[0][x] = max[3][x];
		max[3][x] = t;
		t = max[1][x];
		max[1][x] = max[2][x];
		max[2][x] = t;
		t = solutionMin[0][x];
		solutionMin[0][x] = solutionMin[3][x];
		solutionMin[3][x] = t;
		t = solutionMin[1][x];
		solutionMin[1][x] = solutionMin[2][x];
		solutionMin[2][x] = t;
		t = solutionMax[0][x];
		solutionMax[0][x] = solutionMax[3][x];
		solutionMax[3][x] = t;
		t = solutionMax[1][x];
		solutionMax[1][x] = solutionMax[2][x];
		solutionMax[2][x] = t;
		t = solutionMask[0][x];
		solutionMask[0][x] = solutionMask[3][x];
		solutionMask[3][x] = t;
		t = solutionMask[1][x];
		solutionMask[1][x] = solutionMask[2][x];
		solutionMask[2][x] = t;
	}
	t = totals[1];
	totals[1] = totals[4];
	totals[4] = t;
	t = totals[2];
	totals[2] = totals[3];
	totals[3] = t;
	t = totals[0];
	totals[0] = totals[5];
	totals[5] = t;
	t = resolved[1];
	resolved[1] = resolved[4];
	resolved[4] = t;
	t = resolved[2];
	resolved[2] = resolved[3];
	resolved[3] = t;
	t = resolved[0];
	resolved[0] = resolved[5];
	resolved[5] = t;
}

void Flip0()
{
	int t;
	t = puzzle[0][0];
	puzzle[0][0] = puzzle[3][3];
	puzzle[3][3] = t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[2][3];
	puzzle[2][3] = t;
	t = puzzle[0][2];
	puzzle[0][2] = puzzle[1][3];
	puzzle[1][3] = t;
	t = puzzle[1][0];
	puzzle[1][0] = puzzle[3][2];
	puzzle[3][2] = t;
	t = puzzle[1][1];
	puzzle[1][1] = puzzle[2][2];
	puzzle[2][2] = t;
	t = puzzle[2][0];
	puzzle[2][0] = puzzle[3][1];
	puzzle[3][1] = t;

	t = restart[0][0];
	restart[0][0] = restart[3][3];
	restart[3][3] = t;
	t = restart[0][1];
	restart[0][1] = restart[2][3];
	restart[2][3] = t;
	t = restart[0][2];
	restart[0][2] = restart[1][3];
	restart[1][3] = t;
	t = restart[1][0];
	restart[1][0] = restart[3][2];
	restart[3][2] = t;
	t = restart[1][1];
	restart[1][1] = restart[2][2];
	restart[2][2] = t;
	t = restart[2][0];
	restart[2][0] = restart[3][1];
	restart[3][1] = t;

	t = min[0][0];
	min[0][0] = min[3][3];
	min[3][3] = t;
	t = min[0][1];
	min[0][1] = min[2][3];
	min[2][3] = t;
	t = min[0][2];
	min[0][2] = min[1][3];
	min[1][3] = t;
	t = min[1][0];
	min[1][0] = min[3][2];
	min[3][2] = t;
	t = min[1][1];
	min[1][1] = min[2][2];
	min[2][2] = t;
	t = min[2][0];
	min[2][0] = min[3][1];
	min[3][1] = t;

	t = max[0][0];
	max[0][0] = max[3][3];
	max[3][3] = t;
	t = max[0][1];
	max[0][1] = max[2][3];
	max[2][3] = t;
	t = max[0][2];
	max[0][2] = max[1][3];
	max[1][3] = t;
	t = max[1][0];
	max[1][0] = max[3][2];
	max[3][2] = t;
	t = max[1][1];
	max[1][1] = max[2][2];
	max[2][2] = t;
	t = max[2][0];
	max[2][0] = max[3][1];
	max[3][1] = t;

	t = solutionMin[0][0];
	solutionMin[0][0] = solutionMin[3][3];
	solutionMin[3][3] = t;
	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[2][3];
	solutionMin[2][3] = t;
	t = solutionMin[0][2];
	solutionMin[0][2] = solutionMin[1][3];
	solutionMin[1][3] = t;
	t = solutionMin[1][0];
	solutionMin[1][0] = solutionMin[3][2];
	solutionMin[3][2] = t;
	t = solutionMin[1][1];
	solutionMin[1][1] = solutionMin[2][2];
	solutionMin[2][2] = t;
	t = solutionMin[2][0];
	solutionMin[2][0] = solutionMin[3][1];
	solutionMin[3][1] = t;

	t = solutionMax[0][0];
	solutionMax[0][0] = solutionMax[3][3];
	solutionMax[3][3] = t;
	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[2][3];
	solutionMax[2][3] = t;
	t = solutionMax[0][2];
	solutionMax[0][2] = solutionMax[1][3];
	solutionMax[1][3] = t;
	t = solutionMax[1][0];
	solutionMax[1][0] = solutionMax[3][2];
	solutionMax[3][2] = t;
	t = solutionMax[1][1];
	solutionMax[1][1] = solutionMax[2][2];
	solutionMax[2][2] = t;
	t = solutionMax[2][0];
	solutionMax[2][0] = solutionMax[3][1];
	solutionMax[3][1] = t;

	t = solutionMask[0][0];
	solutionMask[0][0] = solutionMask[3][3];
	solutionMask[3][3] = t;
	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[2][3];
	solutionMask[2][3] = t;
	t = solutionMask[0][2];
	solutionMask[0][2] = solutionMask[1][3];
	solutionMask[1][3] = t;
	t = solutionMask[1][0];
	solutionMask[1][0] = solutionMask[3][2];
	solutionMask[3][2] = t;
	t = solutionMask[1][1];
	solutionMask[1][1] = solutionMask[2][2];
	solutionMask[2][2] = t;
	t = solutionMask[2][0];
	solutionMask[2][0] = solutionMask[3][1];
	solutionMask[3][1] = t;

	t = totals[1];
	totals[1] = totals[6];
	totals[6] = t;
	t = totals[2];
	totals[2] = totals[7];
	totals[7] = t;
	t = totals[3];
	totals[3] = totals[8];
	totals[8] = t;
	t = totals[4];
	totals[4] = totals[9];
	totals[9] = t;

	t = resolved[1];
	resolved[1] = resolved[6];
	resolved[6] = t;
	t = resolved[2];
	resolved[2] = resolved[7];
	resolved[7] = t;
	t = resolved[3];
	resolved[3] = resolved[8];
	resolved[8] = t;
	t = resolved[4];
	resolved[4] = resolved[9];
	resolved[9] = t;
}

void Flip1()
{
	int t;
	t = puzzle[0][3];
	puzzle[0][3] = puzzle[3][0];
	puzzle[3][0] = t;
	t = puzzle[0][2];
	puzzle[0][2] = puzzle[2][0];
	puzzle[2][0] = t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[1][0];
	puzzle[1][0] = t;
	t = puzzle[1][3];
	puzzle[1][3] = puzzle[3][1];
	puzzle[3][1] = t;
	t = puzzle[1][2];
	puzzle[1][2] = puzzle[2][1];
	puzzle[2][1] = t;
	t = puzzle[2][3];
	puzzle[2][3] = puzzle[3][2];
	puzzle[3][2] = t;

	t = restart[0][3];
	restart[0][3] = restart[3][0];
	restart[3][0] = t;
	t = restart[0][2];
	restart[0][2] = restart[2][0];
	restart[2][0] = t;
	t = restart[0][1];
	restart[0][1] = restart[1][0];
	restart[1][0] = t;
	t = restart[1][3];
	restart[1][3] = restart[3][1];
	restart[3][1] = t;
	t = restart[1][2];
	restart[1][2] = restart[2][1];
	restart[2][1] = t;
	t = restart[2][3];
	restart[2][3] = restart[3][2];
	restart[3][2] = t;

	t = min[0][3];
	min[0][3] = min[3][0];
	min[3][0] = t;
	t = min[0][2];
	min[0][2] = min[2][0];
	min[2][0] = t;
	t = min[0][1];
	min[0][1] = min[1][0];
	min[1][0] = t;
	t = min[1][3];
	min[1][3] = min[3][1];
	min[3][1] = t;
	t = min[1][2];
	min[1][2] = min[2][1];
	min[2][1] = t;
	t = min[2][3];
	min[2][3] = min[3][2];
	min[3][2] = t;

	t = max[0][3];
	max[0][3] = max[3][0];
	max[3][0] = t;
	t = max[0][2];
	max[0][2] = max[2][0];
	max[2][0] = t;
	t = max[0][1];
	max[0][1] = max[1][0];
	max[1][0] = t;
	t = max[1][3];
	max[1][3] = max[3][1];
	max[3][1] = t;
	t = max[1][2];
	max[1][2] = max[2][1];
	max[2][1] = t;
	t = max[2][3];
	max[2][3] = max[3][2];
	max[3][2] = t;

	t = solutionMin[0][3];
	solutionMin[0][3] = solutionMin[3][0];
	solutionMin[3][0] = t;
	t = solutionMin[0][2];
	solutionMin[0][2] = solutionMin[2][0];
	solutionMin[2][0] = t;
	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[1][0];
	solutionMin[1][0] = t;
	t = solutionMin[1][3];
	solutionMin[1][3] = solutionMin[3][1];
	solutionMin[3][1] = t;
	t = solutionMin[1][2];
	solutionMin[1][2] = solutionMin[2][1];
	solutionMin[2][1] = t;
	t = solutionMin[2][3];
	solutionMin[2][3] = solutionMin[3][2];
	solutionMin[3][2] = t;

	t = solutionMax[0][3];
	solutionMax[0][3] = solutionMax[3][0];
	solutionMax[3][0] = t;
	t = solutionMax[0][2];
	solutionMax[0][2] = solutionMax[2][0];
	solutionMax[2][0] = t;
	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[1][0];
	solutionMax[1][0] = t;
	t = solutionMax[1][3];
	solutionMax[1][3] = solutionMax[3][1];
	solutionMax[3][1] = t;
	t = solutionMax[1][2];
	solutionMax[1][2] = solutionMax[2][1];
	solutionMax[2][1] = t;
	t = solutionMax[2][3];
	solutionMax[2][3] = solutionMax[3][2];
	solutionMax[3][2] = t;

	t = solutionMask[0][3];
	solutionMask[0][3] = solutionMask[3][0];
	solutionMask[3][0] = t;
	t = solutionMask[0][2];
	solutionMask[0][2] = solutionMask[2][0];
	solutionMask[2][0] = t;
	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[1][0];
	solutionMask[1][0] = t;
	t = solutionMask[1][3];
	solutionMask[1][3] = solutionMask[3][1];
	solutionMask[3][1] = t;
	t = solutionMask[1][2];
	solutionMask[1][2] = solutionMask[2][1];
	solutionMask[2][1] = t;
	t = solutionMask[2][3];
	solutionMask[2][3] = solutionMask[3][2];
	solutionMask[3][2] = t;

	t = totals[1];
	totals[1] = totals[9];
	totals[9] = t;
	t = totals[2];
	totals[2] = totals[8];
	totals[8] = t;
	t = totals[3];
	totals[3] = totals[7];
	totals[7] = t;
	t = totals[4];
	totals[4] = totals[6];
	totals[6] = t;

	t = resolved[1];
	resolved[1] = resolved[9];
	resolved[9] = t;
	t = resolved[2];
	resolved[2] = resolved[8];
	resolved[8] = t;
	t = resolved[3];
	resolved[3] = resolved[7];
	resolved[7] = t;
	t = resolved[4];
	resolved[4] = resolved[6];
	resolved[6] = t;
}

void FlipX0()
{
	int t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[0][2];
	puzzle[0][2] = t;
	t = puzzle[1][0];
	puzzle[1][0] = puzzle[2][0];
	puzzle[2][0] = t;
	t = puzzle[1][3];
	puzzle[1][3] = puzzle[2][3];
	puzzle[2][3] = t;
	t = puzzle[3][1];
	puzzle[3][1] = puzzle[3][2];
	puzzle[3][2] = t;
	t = puzzle[1][1];
	puzzle[1][1] = puzzle[2][2];
	puzzle[2][2] = t;
	t = puzzle[1][2];
	puzzle[1][2] = puzzle[2][1];
	puzzle[2][1] = t;

	t = restart[0][1];
	restart[0][1] = restart[0][2];
	restart[0][2] = t;
	t = restart[1][0];
	restart[1][0] = restart[2][0];
	restart[2][0] = t;
	t = restart[1][3];
	restart[1][3] = restart[2][3];
	restart[2][3] = t;
	t = restart[3][1];
	restart[3][1] = restart[3][2];
	restart[3][2] = t;
	t = restart[1][1];
	restart[1][1] = restart[2][2];
	restart[2][2] = t;
	t = restart[1][2];
	restart[1][2] = restart[2][1];
	restart[2][1] = t;

	t = min[0][1];
	min[0][1] = min[0][2];
	min[0][2] = t;
	t = min[1][0];
	min[1][0] = min[2][0];
	min[2][0] = t;
	t = min[1][3];
	min[1][3] = min[2][3];
	min[2][3] = t;
	t = min[3][1];
	min[3][1] = min[3][2];
	min[3][2] = t;
	t = min[1][1];
	min[1][1] = min[2][2];
	min[2][2] = t;
	t = min[1][2];
	min[1][2] = min[2][1];
	min[2][1] = t;

	t = max[0][1];
	max[0][1] = max[0][2];
	max[0][2] = t;
	t = max[1][0];
	max[1][0] = max[2][0];
	max[2][0] = t;
	t = max[1][3];
	max[1][3] = max[2][3];
	max[2][3] = t;
	t = max[3][1];
	max[3][1] = max[3][2];
	max[3][2] = t;
	t = max[1][1];
	max[1][1] = max[2][2];
	max[2][2] = t;
	t = max[1][2];
	max[1][2] = max[2][1];
	max[2][1] = t;

	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[0][2];
	solutionMin[0][2] = t;
	t = solutionMin[1][0];
	solutionMin[1][0] = solutionMin[2][0];
	solutionMin[2][0] = t;
	t = solutionMin[1][3];
	solutionMin[1][3] = solutionMin[2][3];
	solutionMin[2][3] = t;
	t = solutionMin[3][1];
	solutionMin[3][1] = solutionMin[3][2];
	solutionMin[3][2] = t;
	t = solutionMin[1][1];
	solutionMin[1][1] = solutionMin[2][2];
	solutionMin[2][2] = t;
	t = solutionMin[1][2];
	solutionMin[1][2] = solutionMin[2][1];
	solutionMin[2][1] = t;

	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[0][2];
	solutionMax[0][2] = t;
	t = solutionMax[1][0];
	solutionMax[1][0] = solutionMax[2][0];
	solutionMax[2][0] = t;
	t = solutionMax[1][3];
	solutionMax[1][3] = solutionMax[2][3];
	solutionMax[2][3] = t;
	t = solutionMax[3][1];
	solutionMax[3][1] = solutionMax[3][2];
	solutionMax[3][2] = t;
	t = solutionMax[1][1];
	solutionMax[1][1] = solutionMax[2][2];
	solutionMax[2][2] = t;
	t = solutionMax[1][2];
	solutionMax[1][2] = solutionMax[2][1];
	solutionMax[2][1] = t;

	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[0][2];
	solutionMask[0][2] = t;
	t = solutionMask[1][0];
	solutionMask[1][0] = solutionMask[2][0];
	solutionMask[2][0] = t;
	t = solutionMask[1][3];
	solutionMask[1][3] = solutionMask[2][3];
	solutionMask[2][3] = t;
	t = solutionMask[3][1];
	solutionMask[3][1] = solutionMask[3][2];
	solutionMask[3][2] = t;
	t = solutionMask[1][1];
	solutionMask[1][1] = solutionMask[2][2];
	solutionMask[2][2] = t;
	t = solutionMask[1][2];
	solutionMask[1][2] = solutionMask[2][1];
	solutionMask[2][1] = t;

	t = totals[2];
	totals[2] = totals[3];
	totals[3] = t;
	t = totals[7];
	totals[7] = totals[8];
	totals[8] = t;

	t = resolved[2];
	resolved[2] = resolved[3];
	resolved[3] = t;
	t = resolved[7];
	resolved[7] = resolved[8];
	resolved[8] = t;
}
void FlipX1()
{
	int t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[3][1];
	puzzle[3][1] = t;
	t = puzzle[0][2];
	puzzle[0][2] = puzzle[3][2];
	puzzle[3][2] = t;
	t = puzzle[1][0];
	puzzle[1][0] = puzzle[1][3];
	puzzle[1][3] = t;
	t = puzzle[2][0];
	puzzle[2][0] = puzzle[2][3];
	puzzle[2][3] = t;
	t = puzzle[0][0];
	puzzle[0][0] = puzzle[3][3];
	puzzle[3][3] = t;
	t = puzzle[0][3];
	puzzle[0][3] = puzzle[3][0];
	puzzle[3][0] = t;

	t = restart[0][1];
	restart[0][1] = restart[3][1];
	restart[3][1] = t;
	t = restart[0][2];
	restart[0][2] = restart[3][2];
	restart[3][2] = t;
	t = restart[1][0];
	restart[1][0] = restart[1][3];
	restart[1][3] = t;
	t = restart[2][0];
	restart[2][0] = restart[2][3];
	restart[2][3] = t;
	t = restart[0][0];
	restart[0][0] = restart[3][3];
	restart[3][3] = t;
	t = restart[0][3];
	restart[0][3] = restart[3][0];
	restart[3][0] = t;

	t = min[0][1];
	min[0][1] = min[3][1];
	min[3][1] = t;
	t = min[0][2];
	min[0][2] = min[3][2];
	min[3][2] = t;
	t = min[1][0];
	min[1][0] = min[1][3];
	min[1][3] = t;
	t = min[2][0];
	min[2][0] = min[2][3];
	min[2][3] = t;
	t = min[0][0];
	min[0][0] = min[3][3];
	min[3][3] = t;
	t = min[0][3];
	min[0][3] = min[3][0];
	min[3][0] = t;

	t = max[0][1];
	max[0][1] = max[3][1];
	max[3][1] = t;
	t = max[0][2];
	max[0][2] = max[3][2];
	max[3][2] = t;
	t = max[1][0];
	max[1][0] = max[1][3];
	max[1][3] = t;
	t = max[2][0];
	max[2][0] = max[2][3];
	max[2][3] = t;
	t = max[0][0];
	max[0][0] = max[3][3];
	max[3][3] = t;
	t = max[0][3];
	max[0][3] = max[3][0];
	max[3][0] = t;

	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[3][1];
	solutionMin[3][1] = t;
	t = solutionMin[0][2];
	solutionMin[0][2] = solutionMin[3][2];
	solutionMin[3][2] = t;
	t = solutionMin[1][0];
	solutionMin[1][0] = solutionMin[1][3];
	solutionMin[1][3] = t;
	t = solutionMin[2][0];
	solutionMin[2][0] = solutionMin[2][3];
	solutionMin[2][3] = t;
	t = solutionMin[0][0];
	solutionMin[0][0] = solutionMin[3][3];
	solutionMin[3][3] = t;
	t = solutionMin[0][3];
	solutionMin[0][3] = solutionMin[3][0];
	solutionMin[3][0] = t;

	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[3][1];
	solutionMax[3][1] = t;
	t = solutionMax[0][2];
	solutionMax[0][2] = solutionMax[3][2];
	solutionMax[3][2] = t;
	t = solutionMax[1][0];
	solutionMax[1][0] = solutionMax[1][3];
	solutionMax[1][3] = t;
	t = solutionMax[2][0];
	solutionMax[2][0] = solutionMax[2][3];
	solutionMax[2][3] = t;
	t = solutionMax[0][0];
	solutionMax[0][0] = solutionMax[3][3];
	solutionMax[3][3] = t;
	t = solutionMax[0][3];
	solutionMax[0][3] = solutionMax[3][0];
	solutionMax[3][0] = t;

	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[3][1];
	solutionMask[3][1] = t;
	t = solutionMask[0][2];
	solutionMask[0][2] = solutionMask[3][2];
	solutionMask[3][2] = t;
	t = solutionMask[1][0];
	solutionMask[1][0] = solutionMask[1][3];
	solutionMask[1][3] = t;
	t = solutionMask[2][0];
	solutionMask[2][0] = solutionMask[2][3];
	solutionMask[2][3] = t;
	t = solutionMask[0][0];
	solutionMask[0][0] = solutionMask[3][3];
	solutionMask[3][3] = t;
	t = solutionMask[0][3];
	solutionMask[0][3] = solutionMask[3][0];
	solutionMask[3][0] = t;

	t = totals[1];
	totals[1] = totals[4];
	totals[4] = t;
	t = totals[6];
	totals[6] = totals[9];
	totals[9] = t;

	t = resolved[1];
	resolved[1] = resolved[4];
	resolved[4] = t;
	t = resolved[6];
	resolved[6] = resolved[9];
	resolved[9] = t;
}

void FlipX2()
{
	int t;
	t = puzzle[0][0];
	puzzle[0][0] = puzzle[1][1];
	puzzle[1][1] = t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[1][0];
	puzzle[1][0] = t;
	t = puzzle[0][2];
	puzzle[0][2] = puzzle[1][3];
	puzzle[1][3] = t;
	t = puzzle[0][3];
	puzzle[0][3] = puzzle[1][2];
	puzzle[1][2] = t;
	t = puzzle[2][0];
	puzzle[2][0] = puzzle[3][1];
	puzzle[3][1] = t;
	t = puzzle[2][1];
	puzzle[2][1] = puzzle[3][0];
	puzzle[3][0] = t;
	t = puzzle[2][2];
	puzzle[2][2] = puzzle[3][3];
	puzzle[3][3] = t;
	t = puzzle[2][3];
	puzzle[2][3] = puzzle[3][2];
	puzzle[3][2] = t;

	t = min[0][0];
	min[0][0] = min[1][1];
	min[1][1] = t;
	t = min[0][1];
	min[0][1] = min[1][0];
	min[1][0] = t;
	t = min[0][2];
	min[0][2] = min[1][3];
	min[1][3] = t;
	t = min[0][3];
	min[0][3] = min[1][2];
	min[1][2] = t;
	t = min[2][0];
	min[2][0] = min[3][1];
	min[3][1] = t;
	t = min[2][1];
	min[2][1] = min[3][0];
	min[3][0] = t;
	t = min[2][2];
	min[2][2] = min[3][3];
	min[3][3] = t;
	t = min[2][3];
	min[2][3] = min[3][2];
	min[3][2] = t;

	t = max[0][0];
	max[0][0] = max[1][1];
	max[1][1] = t;
	t = max[0][1];
	max[0][1] = max[1][0];
	max[1][0] = t;
	t = max[0][2];
	max[0][2] = max[1][3];
	max[1][3] = t;
	t = max[0][3];
	max[0][3] = max[1][2];
	max[1][2] = t;
	t = max[2][0];
	max[2][0] = max[3][1];
	max[3][1] = t;
	t = max[2][1];
	max[2][1] = max[3][0];
	max[3][0] = t;
	t = max[2][2];
	max[2][2] = max[3][3];
	max[3][3] = t;
	t = max[2][3];
	max[2][3] = max[3][2];
	max[3][2] = t;

	t = solutionMin[0][0];
	solutionMin[0][0] = solutionMin[1][1];
	solutionMin[1][1] = t;
	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[1][0];
	solutionMin[1][0] = t;
	t = solutionMin[0][2];
	solutionMin[0][2] = solutionMin[1][3];
	solutionMin[1][3] = t;
	t = solutionMin[0][3];
	solutionMin[0][3] = solutionMin[1][2];
	solutionMin[1][2] = t;
	t = solutionMin[2][0];
	solutionMin[2][0] = solutionMin[3][1];
	solutionMin[3][1] = t;
	t = solutionMin[2][1];
	solutionMin[2][1] = solutionMin[3][0];
	solutionMin[3][0] = t;
	t = solutionMin[2][2];
	solutionMin[2][2] = solutionMin[3][3];
	solutionMin[3][3] = t;
	t = solutionMin[2][3];
	solutionMin[2][3] = solutionMin[3][2];
	solutionMin[3][2] = t;

	t = solutionMax[0][0];
	solutionMax[0][0] = solutionMax[1][1];
	solutionMax[1][1] = t;
	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[1][0];
	solutionMax[1][0] = t;
	t = solutionMax[0][2];
	solutionMax[0][2] = solutionMax[1][3];
	solutionMax[1][3] = t;
	t = solutionMax[0][3];
	solutionMax[0][3] = solutionMax[1][2];
	solutionMax[1][2] = t;
	t = solutionMax[2][0];
	solutionMax[2][0] = solutionMax[3][1];
	solutionMax[3][1] = t;
	t = solutionMax[2][1];
	solutionMax[2][1] = solutionMax[3][0];
	solutionMax[3][0] = t;
	t = solutionMax[2][2];
	solutionMax[2][2] = solutionMax[3][3];
	solutionMax[3][3] = t;
	t = solutionMax[2][3];
	solutionMax[2][3] = solutionMax[3][2];
	solutionMax[3][2] = t;

	t = solutionMask[0][0];
	solutionMask[0][0] = solutionMask[1][1];
	solutionMask[1][1] = t;
	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[1][0];
	solutionMask[1][0] = t;
	t = solutionMask[0][2];
	solutionMask[0][2] = solutionMask[1][3];
	solutionMask[1][3] = t;
	t = solutionMask[0][3];
	solutionMask[0][3] = solutionMask[1][2];
	solutionMask[1][2] = t;
	t = solutionMask[2][0];
	solutionMask[2][0] = solutionMask[3][1];
	solutionMask[3][1] = t;
	t = solutionMask[2][1];
	solutionMask[2][1] = solutionMask[3][0];
	solutionMask[3][0] = t;
	t = solutionMask[2][2];
	solutionMask[2][2] = solutionMask[3][3];
	solutionMask[3][3] = t;
	t = solutionMask[2][3];
	solutionMask[2][3] = solutionMask[3][2];
	solutionMask[3][2] = t;

	t = restart[0][0];
	restart[0][0] = restart[1][1];
	restart[1][1] = t;
	t = restart[0][1];
	restart[0][1] = restart[1][0];
	restart[1][0] = t;
	t = restart[0][2];
	restart[0][2] = restart[1][3];
	restart[1][3] = t;
	t = restart[0][3];
	restart[0][3] = restart[1][2];
	restart[1][2] = t;
	t = restart[2][0];
	restart[2][0] = restart[3][1];
	restart[3][1] = t;
	t = restart[2][1];
	restart[2][1] = restart[3][0];
	restart[3][0] = t;
	t = restart[2][2];
	restart[2][2] = restart[3][3];
	restart[3][3] = t;
	t = restart[2][3];
	restart[2][3] = restart[3][2];
	restart[3][2] = t;

	t = totals[1];
	totals[1] = totals[2];
	totals[2] = t;
	t = totals[3];
	totals[3] = totals[4];
	totals[4] = t;
	t = totals[6];
	totals[6] = totals[7];
	totals[7] = t;
	t = totals[8];
	totals[8] = totals[9];
	totals[9] = t;

	t = resolved[1];
	resolved[1] = resolved[2];
	resolved[2] = t;
	t = resolved[3];
	resolved[3] = resolved[4];
	resolved[4] = t;
	t = resolved[6];
	resolved[6] = resolved[7];
	resolved[7] = t;
	t = resolved[8];
	resolved[8] = resolved[9];
	resolved[9] = t;
	resolved[9] = t;
}

void FlipX3()
{
	int t;
	t = puzzle[0][0];
	puzzle[0][0] = puzzle[2][2];
	puzzle[2][2] = t;
	t = puzzle[0][1];
	puzzle[0][1] = puzzle[2][3];
	puzzle[2][3] = t;
	t = puzzle[0][2];
	puzzle[0][2] = puzzle[2][0];
	puzzle[2][0] = t;
	t = puzzle[0][3];
	puzzle[0][3] = puzzle[2][1];
	puzzle[2][1] = t;
	t = puzzle[1][0];
	puzzle[1][0] = puzzle[3][2];
	puzzle[3][2] = t;
	t = puzzle[1][1];
	puzzle[1][1] = puzzle[3][3];
	puzzle[3][3] = t;
	t = puzzle[1][2];
	puzzle[1][2] = puzzle[3][0];
	puzzle[3][0] = t;
	t = puzzle[1][3];
	puzzle[1][3] = puzzle[3][1];
	puzzle[3][1] = t;

	t = min[0][0];
	min[0][0] = min[2][2];
	min[2][2] = t;
	t = min[0][1];
	min[0][1] = min[2][3];
	min[2][3] = t;
	t = min[0][2];
	min[0][2] = min[2][0];
	min[2][0] = t;
	t = min[0][3];
	min[0][3] = min[2][1];
	min[2][1] = t;
	t = min[1][0];
	min[1][0] = min[3][2];
	min[3][2] = t;
	t = min[1][1];
	min[1][1] = min[3][3];
	min[3][3] = t;
	t = min[1][2];
	min[1][2] = min[3][0];
	min[3][0] = t;
	t = min[1][3];
	min[1][3] = min[3][1];
	min[3][1] = t;

	t = max[0][0];
	max[0][0] = max[2][2];
	max[2][2] = t;
	t = max[0][1];
	max[0][1] = max[2][3];
	max[2][3] = t;
	t = max[0][2];
	max[0][2] = max[2][0];
	max[2][0] = t;
	t = max[0][3];
	max[0][3] = max[2][1];
	max[2][1] = t;
	t = max[1][0];
	max[1][0] = max[3][2];
	max[3][2] = t;
	t = max[1][1];
	max[1][1] = max[3][3];
	max[3][3] = t;
	t = max[1][2];
	max[1][2] = max[3][0];
	max[3][0] = t;
	t = max[1][3];
	max[1][3] = max[3][1];
	max[3][1] = t;

	t = solutionMin[0][0];
	solutionMin[0][0] = solutionMin[2][2];
	solutionMin[2][2] = t;
	t = solutionMin[0][1];
	solutionMin[0][1] = solutionMin[2][3];
	solutionMin[2][3] = t;
	t = solutionMin[0][2];
	solutionMin[0][2] = solutionMin[2][0];
	solutionMin[2][0] = t;
	t = solutionMin[0][3];
	solutionMin[0][3] = solutionMin[2][1];
	solutionMin[2][1] = t;
	t = solutionMin[1][0];
	solutionMin[1][0] = solutionMin[3][2];
	solutionMin[3][2] = t;
	t = solutionMin[1][1];
	solutionMin[1][1] = solutionMin[3][3];
	solutionMin[3][3] = t;
	t = solutionMin[1][2];
	solutionMin[1][2] = solutionMin[3][0];
	solutionMin[3][0] = t;
	t = solutionMin[1][3];
	solutionMin[1][3] = solutionMin[3][1];
	solutionMin[3][1] = t;

	t = solutionMax[0][0];
	solutionMax[0][0] = solutionMax[2][2];
	solutionMax[2][2] = t;
	t = solutionMax[0][1];
	solutionMax[0][1] = solutionMax[2][3];
	solutionMax[2][3] = t;
	t = solutionMax[0][2];
	solutionMax[0][2] = solutionMax[2][0];
	solutionMax[2][0] = t;
	t = solutionMax[0][3];
	solutionMax[0][3] = solutionMax[2][1];
	solutionMax[2][1] = t;
	t = solutionMax[1][0];
	solutionMax[1][0] = solutionMax[3][2];
	solutionMax[3][2] = t;
	t = solutionMax[1][1];
	solutionMax[1][1] = solutionMax[3][3];
	solutionMax[3][3] = t;
	t = solutionMax[1][2];
	solutionMax[1][2] = solutionMax[3][0];
	solutionMax[3][0] = t;
	t = solutionMax[1][3];
	solutionMax[1][3] = solutionMax[3][1];
	solutionMax[3][1] = t;

	t = solutionMask[0][0];
	solutionMask[0][0] = solutionMask[2][2];
	solutionMask[2][2] = t;
	t = solutionMask[0][1];
	solutionMask[0][1] = solutionMask[2][3];
	solutionMask[2][3] = t;
	t = solutionMask[0][2];
	solutionMask[0][2] = solutionMask[2][0];
	solutionMask[2][0] = t;
	t = solutionMask[0][3];
	solutionMask[0][3] = solutionMask[2][1];
	solutionMask[2][1] = t;
	t = solutionMask[1][0];
	solutionMask[1][0] = solutionMask[3][2];
	solutionMask[3][2] = t;
	t = solutionMask[1][1];
	solutionMask[1][1] = solutionMask[3][3];
	solutionMask[3][3] = t;
	t = solutionMask[1][2];
	solutionMask[1][2] = solutionMask[3][0];
	solutionMask[3][0] = t;
	t = solutionMask[1][3];
	solutionMask[1][3] = solutionMask[3][1];
	solutionMask[3][1] = t;

	t = restart[0][0];
	restart[0][0] = restart[2][2];
	restart[2][2] = t;
	t = restart[0][1];
	restart[0][1] = restart[2][3];
	restart[2][3] = t;
	t = restart[0][2];
	restart[0][2] = restart[2][0];
	restart[2][0] = t;
	t = restart[0][3];
	restart[0][3] = restart[2][1];
	restart[2][1] = t;
	t = restart[1][0];
	restart[1][0] = restart[3][2];
	restart[3][2] = t;
	t = restart[1][1];
	restart[1][1] = restart[3][3];
	restart[3][3] = t;
	t = restart[1][2];
	restart[1][2] = restart[3][0];
	restart[3][0] = t;
	t = restart[1][3];
	restart[1][3] = restart[3][1];
	restart[3][1] = t;

	t = totals[1];
	totals[1] = totals[3];
	totals[3] = t;
	t = totals[2];
	totals[2] = totals[4];
	totals[4] = t;
	t = totals[6];
	totals[6] = totals[8];
	totals[8] = t;
	t = totals[7];
	totals[7] = totals[9];
	totals[9] = t;

	t = resolved[1];
	resolved[1] = resolved[3];
	resolved[3] = t;
	t = resolved[2];
	resolved[2] = resolved[4];
	resolved[4] = t;
	t = resolved[6];
	resolved[6] = resolved[8];
	resolved[8] = t;
	t = resolved[7];
	resolved[7] = resolved[9];
	resolved[9] = t;
}


enum SYMMETRIES
{
	HFLIP = 0,
	VFLIP = 1,
	FLIP0 = 2,
	FLIP1 = 3,
	FLIPX0 = 4,
	FLIPX1 = 5,
	FLIPX2 = 6,
	FLIPX3 = 7,
	NUM_FLIPS = 8
};

#define MAX_SYMMETRIES		64
struct Symmetry
{
	int count;								// number of flips in the array flips[]
	int flips[4];							// what flips were used
	int totals[10];							// resulting totals
} symmetries[MAX_SYMMETRIES];
int numSymmetries = 0;						// numbwer in the array symmetries[]


bool SaveSymmetry(int count, int f0, int f1, int f2, int f3)
{
	// see if we already have this
	int i;
	for (i = 0; i < numSymmetries; i++)
	{
		int t;
		for (t = 0; t < 10; t++)
		{
			if (totals[t] != symmetries[i].totals[t])
				break;
		}
		if (t == 10)						// this is a duplicate		
			return false;
	}
	if (numSymmetries == MAX_SYMMETRIES - 1)
		return true;
	symmetries[numSymmetries].count = count;
	symmetries[numSymmetries].flips[0] = f0;
	symmetries[numSymmetries].flips[1] = f1;
	symmetries[numSymmetries].flips[2] = f2;
	symmetries[numSymmetries].flips[3] = f3;
	for (int i = 0; i < 10; i++)
		symmetries[numSymmetries].totals[i] = totals[i];
	numSymmetries++;
	return true;
}


void TryFlip(int flip)
{
	switch (flip)
	{
	case HFLIP:
		HFlip();
		break;
	case VFLIP:
		VFlip();
		break;
	case FLIP0:
		Flip0();
		break;
	case FLIP1:
		Flip1();
		break;
	case FLIPX0:
		FlipX0();
		break;
	case FLIPX1:
		FlipX1();
		break;
	case FLIPX2:
		FlipX2();
		break;
	case FLIPX3:
		FlipX3();
		break;
	}
}


// init puzzle for next test
void InitSymmetries()
{
	for (int i = 0; i < 10; i++)
		totals[i] = i + 10;
}

void CreateSymmetries()
{
#if 0										// create all symmetries
	InitSymmetries();
	SaveSymmetry(0, -1, -1, -1, -1);		// starting position
	// find all one flip symmetries
	for (int f0 = 0; f0 < NUM_FLIPS; f0++)
	{
		InitSymmetries();
		TryFlip(f0);
		SaveSymmetry(1, f0, -1, -1, -1);			
	}
	for (int f0 = 0; f0 < NUM_FLIPS; f0++)
	{
		for (int f1 = 0; f1 < NUM_FLIPS; f1++)
		{
			InitSymmetries();
			TryFlip(f0);
			TryFlip(f1);
			SaveSymmetry(2, f0, f1, -1, -1);
		}
	}
	for (int f0 = 0; f0 < NUM_FLIPS; f0++)
	{
		for (int f1 = 0; f1 < NUM_FLIPS; f1++)
		{
			for (int f2 = 0; f2 < NUM_FLIPS; f2++)
			{
				InitSymmetries();
				TryFlip(f0);
				TryFlip(f1);
				TryFlip(f2);
				SaveSymmetry(3, f0, f1, f2, -1);
			}
		}
	}
	for (int f0 = 0; f0 < NUM_FLIPS; f0++)
	{
		for (int f1 = 0; f1 < NUM_FLIPS; f1++)
		{
			for (int f2 = 0; f2 < NUM_FLIPS; f2++)
			{
				for (int f3 = 0; f3 < NUM_FLIPS; f3++)
				{
					InitSymmetries();
					TryFlip(f0);
					TryFlip(f1);
					TryFlip(f2);
					TryFlip(f3);
					SaveSymmetry(4, f0, f1, f2, f3);
				}
			}
		}
	}
#endif
}
