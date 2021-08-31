#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using std::cout;
using std::endl;

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
/** @todo [Part 1] */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
	: png_(png), start_(start), tolerance_(tolerance)
	{ DFSStack.push_front(start_); }

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(png_, start_, tolerance_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  for (std::list<Point>::iterator it = DFSStack.begin(); it != DFSStack.end(); ++it)
	if( *it == point)  {
	  DFSStack.erase(it);
	  break;
    }
  DFSStack.push_front(point);
  //cout<<point<<" is added\n";
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point p = DFSStack.front();
  DFSStack.pop_front();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : DFSStack.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return DFSStack.empty();
}
