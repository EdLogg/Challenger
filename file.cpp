
#include "stdafx.h"


//***********************************************************************
//	Open and save puzzle functions
//***********************************************************************
BOOL LoadTextFile(HWND hEdit, LPCTSTR pszFileName)
{
	FILE * file = NULL;

	file = fopen(pszFileName, "r");
	if (file != NULL)
	{
		int c = fscanf(file, "%d,%d", &state, &index);
		if (c != 2)
		{
			fclose(file);
			return false;
		}
		c = fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			&totals[0], &totals[1], &totals[2], &totals[3], &totals[4],
			&totals[5], &totals[6], &totals[7], &totals[8], &totals[9]);
		if (c != 10)
		{
			fclose(file);
			return false;
		}
		for (int i = 0; i < 10; i++)				// just in case we need these
		{
			if (state == STATE_SOLUTIONS)
				resolved[i] = true;
			else 
				resolved[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			int c = fscanf(file, "%d,%d,%d,%d",
				&puzzle[i][0], &puzzle[i][1], &puzzle[i][2], &puzzle[i][3]);
			if (c != 4)
			{
				fclose(file);
				return false;
			}
		}
		for (int n = 0; n < 4; n++)					// in case we need these too
			for (int m = 0; m < 4; m++)
				restart[n][m] = puzzle[n][m];
		for (int i = 0; i < 4; i++)
		{
			int c = fscanf(file, "%d,%d,%d,%d",
				&min[i][0], &min[i][1], &min[i][2], &min[i][3]);
			if (c != 4)
			{
				fclose(file);
				return false;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			int c = fscanf(file, "%d,%d,%d,%d",
				&max[i][0], &max[i][1], &max[i][2], &max[i][3]);
			if (c != 4)
			{
				fclose(file);
				return false;
			}
		}
		fclose(file);
	}
	return true;
}


BOOL SaveTextFile(LPCTSTR pszFileName)
{
	FILE * file = NULL;
	file = fopen(pszFileName, "w");
	if (file != NULL)
	{
		if (state == STATE_EQUATIONS)
			fprintf(file, "%d,%d\n", STATE_SOLUTIONS, index);		// restart any equations
		else
			fprintf(file, "%d,%d\n", state, index);
		fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			totals[0], totals[1], totals[2], totals[3], totals[4],
			totals[5], totals[6], totals[7], totals[8], totals[9]);
		for (int i = 0; i < 4; i++)
		{
			fprintf(file, "%d,%d,%d,%d\n", puzzle[i][0], puzzle[i][1], puzzle[i][2], puzzle[i][3]);
		}
		for (int i = 0; i < 4; i++)
		{
			fprintf(file, "%d,%d,%d,%d\n", min[i][0], min[i][1], min[i][2], min[i][3]);
		}
		for (int i = 0; i < 4; i++)
		{
			fprintf(file, "%d,%d,%d,%d\n", max[i][0], max[i][1], max[i][2], max[i][3]);
		}
		fclose(file);
		return true;
	}
	return false;
}


bool DoFileOpen(HWND hwnd)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";

	if (GetOpenFileName(&ofn))
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		if (LoadTextFile(hEdit, szFileName))
			return true;
	}
	return false;
}


void DoFileSave(HWND hwnd)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		if (SaveTextFile(szFileName) == false)
			MessageBox(hwnd, "Unable to open save file!", "User input error", MB_ICONSTOP | MB_OK | MB_APPLMODAL);
	}
}

