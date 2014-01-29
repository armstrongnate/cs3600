// This file defines a Maze class, for CS 3600 maze assignment
// January, 2014
// (Your name here)

// The maze will be M by N cells big.
const int M = 5;
const int N = 4;
class Maze
{
	struct Cell
	{
	public:
		Cell()
		{
			mLeft = mTop = mRight = mBottom = true;
			mVisited = false;
		}
		void Draw(int i, int j);
	private:
		bool mLeft, mTop, mRight, mBottom;
		bool mVisited;
	};
public:
	Maze();
	void Draw();
private:
	Cell mCells[M][N];
};
