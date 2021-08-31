#include <iterator>
#include <cmath>
#include <iostream>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;
using std::cout;
using std::endl;
/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
 /** @todo [Part 1] */
BFS::BFS(const PNG & png, const Point & start, double tolerance) 
	: png_(png), start_(start), tolerance_(tolerance)
	{ BFSQueue.push_front(start_); }

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(png_, start_, tolerance_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */ 
  // BFS is different from the concept of DFS, should be very careful!
  
  /*for (std::vector<Point>::iterator it = finished.begin(); it != finished.end(); ++it)
	if( *it == point){  
	  traversed = true;
	  break;
	}
  if(traversed == false){
	finished.push_back(point);
	BFSQueue.push_front(point);
  }*/
  std::list<Point>::iterator it;
  for (it = BFSQueue.begin(); it != BFSQueue.end(); ++it)
	if( *it == point)  
	  return;
  
  BFSQueue.push_front(point);
  //cout<<point<<" is added\n";
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = BFSQueue.back();
  BFSQueue.pop_back();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : BFSQueue.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return BFSQueue.empty();
}
