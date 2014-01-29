#include "maze.h"
#include <GLUT/GLUT.h>

void Maze::Cell::Draw(int i, int j)
{
	glBegin(GL_LINE_LOOP);
	glVertex2d(i,j);
	glVertex2d(i+1,j);
	glVertex2d(i+1,j+1);
	glVertex2d(i,j+1);
	glEnd();
}

void Maze::Draw()
{
	/*
	glBegin(GL_LINE_LOOP);
	glVertex2d(0,0);
	glVertex2d(M,0);
	glVertex2d(M,N);
	glVertex2d(0,N);
	glEnd();
	*/
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
		{
			mCells[i][j].Draw(i,j);
		}
}

Maze::Maze()
{
	// Carve out the cell walls.
}
