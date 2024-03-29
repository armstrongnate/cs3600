// This file defines a Maze class, for CS 3600 maze assignment
// January, 2014
// (Your name here)

// The maze will be M by N cells big.
const int M = 7;
const int N = 7;
class Maze
{
  struct Cell
  {
  public:
    Cell()
    {
      left = top = right = bottom = true;
      visited = false;
    }
    void draw(int i, int j);
    void setVisited(bool visited);
    bool getVisited();
    void setLeft(bool left);
    bool getLeft();
    void setTop(bool top);
    bool getTop();
    void setRight(bool right);
    bool getRight();
    void setBottom(bool bottom);
    bool getBottom();
  private:
    bool left, top, right, bottom;
    bool visited;
  };
public:
	Maze();
	void draw();
  bool isLegal(double x, double y, double r);
private:
	Cell cells[M][N];
  void visitCell(int i, int j);
};
