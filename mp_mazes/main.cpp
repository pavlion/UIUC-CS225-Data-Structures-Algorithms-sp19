#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

double alculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = ((p1.h - p2.h)>0)?(p1.h - p2.h):(p2.h-p1.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return (h*h) + (s*s) + (l*l);
}

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    PNG base;
    base.readFromFile("myFloodFill.png");

    SquareMaze maze;
    maze.makeMaze(base.width(), base.height());
  	maze.solveMaze();
  	PNG * output = maze.drawMazeWithSolution();

    int w = base.width();
    int h = base.height();
    int m = (w<h)?w:h;
    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j){
        if ( (i-w/2)*(i-w/2) + (j-h/2)*(j-h/2) < m*m/10){
          base.getPixel(i,j) = output->getPixel(i,j);

        }
      }

  	base.writeToFile("newCreativePic"+ string(".png"));

    return 0;
}
