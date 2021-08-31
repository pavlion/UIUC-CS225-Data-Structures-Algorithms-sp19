/* Your code here! */
/**
 * @file maze.cpp
 * Implementation of SquareMaze.
 */

#include "maze.h"
#include "dsets.h"
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <iterator>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using std::vector;
using cs225::HSLAPixel;
using cs225::PNG;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::pair;
using std::make_pair;


SquareMaze::SquareMaze() { }

void SquareMaze::makeMaze(int width,int height)
{
	this->width = width;
	this->height = height;
	int size = width * height;

	for (int i = 0; i < size; ++i)
		// pari: right, down, respectively
		wall.push_back( wallRecord(true, true) );

	DisjointSets dsets;
	dsets.addelements(size);


	int trees = 0;
	int randX = 0;
	int randY = 0;
	int coord = 0;
	int rightDown = 0;

	//srand(time(NULL));
	while (trees < size-1){
    //srand(time(NULL));
		// select a random position to delete
		// randomly select
		randX = rand() % width;
		randY = rand() % height;
		coord = randX + randY * width;
		rightDown = rand() % 2;

		if (rightDown == 0){
			if(randX != width-1 && wall[coord].right == true
				&& dsets.find(coord) != dsets.find(coord+1) ){ //(randX + 1) + randY * width
				wall[coord].right = false;
				dsets.setunion( dsets.find(coord), dsets.find(coord+1) );
				++trees;
			}
    }
		else if(randY != height-1 && wall[coord].down == true
					&& dsets.find(coord) != dsets.find(coord+width) ){ //randX + (1 + randY) * width
				wall[coord].down = false;
				dsets.setunion( dsets.find(coord), dsets.find(coord+width) );
				++trees;
    }
	}

}

bool SquareMaze::canTravel(int x,int y,int 	dir) const{
	int coord = x + y * width;
	switch (dir){
		case 0: return !wall[coord].right;
		case 1: return !wall[coord].down;
		case 2: return (x == 0)? false: !wall[coord-1].right; // x-1+y*width
		case 3: return (y == 0)? false: !wall[coord-width].down;// x+(y-1)*width
		default:return false;
	}
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
	if (dir == 0)
		wall[x + y * width].right = exists;
	else
		wall[x + y * width].down = exists;
}
vector<int> SquareMaze::solveMaze(){
	vector<int> bottomRow(width, 0);

	vector< pair<int, int> > parent(width*height);
  vector<bool> dummy(width, false);
  vector< vector<bool> > visited(height, dummy);

	queue< pair<int, int> > q;

	q.push(make_pair(0,0));
	visited[0][0] = true;

  int dist = 0;
	while(!q.empty()) {
		pair<int, int> coord = q.front();
		q.pop();
		int x = coord.first;
		int y = coord.second;

		if (y == height - 1) {
			bottomRow[x] = dist;
		}

		if (canTravel(x, y, 0) && visited[x+1][y] == false ) {
			parent[x+1 + y*width] = coord;
			visited[x+1][y] = true;
			q.push(make_pair(x+1, y));
		}
		if (canTravel(x, y, 1) && visited[x][y+1] == false ) {
			parent[x + (y+1)*width] = coord;
			visited[x][y+1] = true;
			q.push(make_pair(x, y+1));
		}
		if (canTravel(x, y, 2) && visited[x-1][y] == false ) {
			parent[x-1 + y*width] = coord;
			visited[x-1][y] = true;
			q.push(make_pair(x-1, y));
		}
		if (canTravel(x, y, 3) && visited[x][y-1] == false ) {
			parent[x + (y-1)*width] = coord;
			visited[x][y-1] = true;
			q.push(make_pair(x, y-1));
		}

		++dist;
	}

	int maxDist = 0;
  int destX;
  for(int i = 0; i < width; i++) {
    if(bottomRow[i] > maxDist) {
      maxDist = bottomRow[i];
      destX = i;
    }
  }

  vector<int> ret;
	pair<int, int> dest = make_pair(destX, height-1);
  pair<int, int> curr = dest;

  int dir = 0;

  // use parent vector to backtrack from dest to
  // origin and insert directions into return vector
  while(!(curr.first == 0 && curr.second == 0)) {
		int cx = curr.first, cy = curr.second;
		int px = parent[cx + cy * width].first;
		int py = parent[cx + cy * width].second;


    if (px == cx) {
      if (py + 1 == cy)
        dir = 1;

      if (py - 1 == cy)
        dir = 3;
    }

    if (py == cy) {
      if (px + 1 == cx)
        dir = 0;

      if (px - 1 == cx)
        dir = 2;
    }

    ret.insert(ret.begin(), dir);
    curr = make_pair(px, py);
  }

	return ret;
}

PNG* SquareMaze::drawMaze()	const{
	int H = height * 10 + 1;
	int W = width * 10 + 1;
	PNG* ret = new PNG(W, H);

	// blacken topmost row
	for (int i=0; i<H; ++i){
		ret->getPixel(0, i).l = 0;
	}

	// blacken topmost row
	for (int i=10; i<W; ++i){
		ret->getPixel(i, 0).l = 0;
	}

	for (int x = 0; x < width; ++x){
		for (int y = 0; y< height; ++y){
			if (wall[x + y * width].right == true){
				for (int i = 0; i < 11; ++i)
					ret->getPixel( (x+1)*10, y*10 + i).l = 0;
			}
			if (wall[x + y * width].down){
				for (int i = 0; i < 11; ++i)
					ret->getPixel( x*10 + i, (y+1)*10).l = 0;
			}
		}
	}

	return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
	PNG* ret = drawMaze();
  vector<int> path = solveMaze();
  HSLAPixel red(0, 1, 0.5, 1);

  int x = 5, y = 5;
  for (unsigned i = 0; i < path.size(); ++i){
    // color current point x,y to red
    switch (path[i]){
	      case 0: {
					for (int i = 0; i < 10; ++i){
			      ret->getPixel(x, y) = red;
	        	++x;
					}
						break;
	      }
	      case 1:{
					for (int i = 0; i < 10; ++i){
			      ret->getPixel(x, y) = red;
	        	++y;
					}
					break;
	      }
	      case 2:{
					for (int i = 0; i < 10; ++i){
			      ret->getPixel(x, y) = red;
	        	--x;
					}
					break;
	      }
	      case 3:{
					for (int i = 0; i < 10; ++i){
			      ret->getPixel(x, y) = red;
	        	--y;
					}
					break;
	      }

		}
  }

  ret->getPixel(x, y) = red;

  x -= 4;
  y += 5;
  for (int i = 0; i < 9; ++i){
    HSLAPixel & p = ret->getPixel(x, y);
    //p.h = 0;
    //p.s = 0;
    p.l = 1; p.a = 1;
    ++x;
  }

  return ret;
}
