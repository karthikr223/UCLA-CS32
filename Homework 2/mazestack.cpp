#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	stack<Coord> coordStack;
	Coord start(sr, sc);
	coordStack.push(start);
	maze[sr][sc] = '&';
	while (!coordStack.empty()) {
		int currentrow = coordStack.top().r();
		int currentcol = coordStack.top().c();
		coordStack.pop();
		if (currentrow == er && currentcol == ec) {
			return true;
		}
		if (currentcol < nCols-1 && maze[currentrow][currentcol + 1] == '.') {
			coordStack.push(Coord(currentrow, currentcol + 1));
			maze[currentrow][currentcol + 1] = '&';
		}
		if (currentrow < nRows-1 && maze[currentrow+1][currentcol] == '.') {
			coordStack.push(Coord(currentrow+1, currentcol));
			maze[currentrow+1][currentcol] = '&';
		}
		if (currentcol > 0 && maze[currentrow][currentcol- 1] == '.') {
			coordStack.push(Coord(currentrow, currentcol - 1));
			maze[currentrow][currentcol - 1] = '&';
		}
		if (currentrow > 0 && maze[currentrow - 1][currentcol] == '.') {
			coordStack.push(Coord(currentrow - 1, currentcol));
			maze[currentrow - 1][currentcol] = '&';
		}
	}
	return false;

}

