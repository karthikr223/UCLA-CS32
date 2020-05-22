#include <iostream>
#include "History.h"
#include "City.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			grid[i][j] = '.';
		}
}
}

bool History::record(int r, int c)
{
	if (r > m_rows || c > m_cols || r < 1 || c < 1)
		return false;
	else {
		if (grid[r - 1][c - 1] == '.')
			grid[r - 1][c - 1] = 'A';
		else if (grid[r - 1][c - 1] >= 'A' && grid[r - 1][c - 1] < 'Z')
			grid[r - 1][c - 1] += 1;
		else
			grid[r - 1][c - 1] = 'Z';
		return true;
	}
}

void History::display() const
{
	clearScreen();
	for(int i = 0; i<m_rows; i++){
		for (int j = 0; j < m_cols; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
}