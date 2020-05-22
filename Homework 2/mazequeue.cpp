#include <iostream>
#include <string>
#include <stack>
#include <queue>
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
	queue<Coord> coordQueue;
	Coord start(sr, sc);
	coordQueue.push(start);
	maze[sr][sc] = '&';
	while (!coordQueue.empty()) {
		int currentrow = coordQueue.front().r();
		int currentcol = coordQueue.front().c();
		coordQueue.pop();
		if (currentrow == er && currentcol == ec) {
			return true;
		}
		if (currentcol < nCols - 1 && maze[currentrow][currentcol + 1] == '.') {
			coordQueue.push(Coord(currentrow, currentcol + 1));
			maze[currentrow][currentcol + 1] = '&';
		}
		if (currentrow < nRows - 1 && maze[currentrow + 1][currentcol] == '.') {
			coordQueue.push(Coord(currentrow + 1, currentcol));
			maze[currentrow + 1][currentcol] = '&';
		}
		if (currentcol > 0 && maze[currentrow][currentcol - 1] == '.') {
			coordQueue.push(Coord(currentrow, currentcol - 1));
			maze[currentrow][currentcol - 1] = '&';
		}
		if (currentrow > 0 && maze[currentrow - 1][currentcol] == '.') {
			coordQueue.push(Coord(currentrow - 1, currentcol));
			maze[currentrow - 1][currentcol] = '&';
		}
	}
	return false;

}

