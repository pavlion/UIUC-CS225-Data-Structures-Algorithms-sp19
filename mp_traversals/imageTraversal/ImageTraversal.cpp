#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using std::cout;
using std::endl;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
/** @todo [Part 1] */
ImageTraversal::Iterator::Iterator() 
	: traversal_(NULL), current_(Point()), start_(Point()), png_(NULL), tolerance_(0.0)
{
  // nothing
}

/**
 * Two parameters iterator constructor.
 */ 
/** [Part 1] added function */
ImageTraversal::Iterator::Iterator(PNG& png, Point& start, double tolerance, ImageTraversal* traversal) 
	: traversal_(traversal), current_(start), start_(start), png_(&png),tolerance_(tolerance) 
{ 
  for (unsigned i = 0; i < png_->width(); i++) {
    for (unsigned j = 0; j < png_->height(); j++){
		Point p(i,j);
		visited[p] = false;
    }
  }
  
  traversal_->pop(); 
  visited[current_] = true;
  
  Point p1 = Point(current_.x+1,current_.y);
  Point p2 = Point(current_.x  ,current_.y+1);
  Point p3 = Point(current_.x-1,current_.y);
  Point p4 = Point(current_.x  ,current_.y-1);
  //cout<<"current point:"<<current_<<endl;
  // checking the tolerance
  if ( ValidToVisit(p1) && !visited[p1]) {traversal_->add(p1);}//cout<<p1<<" will be added\n";}
  if ( ValidToVisit(p2) && !visited[p2]) {traversal_->add(p2);}//cout<<p2<<" will be added\n";}
  if ( ValidToVisit(p3) && !visited[p3]) {traversal_->add(p3);}//cout<<p3<<" will be added\n";}
  if ( ValidToVisit(p4) && !visited[p4]) {traversal_->add(p4);}//cout<<p4<<" will be added\n";}
  
  //visited[start_] = true;
  /*
  if ( ValidToVisit(start_) ){
	  //cout<<"true = = \n";
	  visited[start_] = true;
  }
  else{
	//traversal_->pop();  
	// There must be one element in the stack/queue
	// so we can just pop without checking emptyness
  }*/
  
}	

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if( traversal_->empty() ){
	*this = Iterator();//cout<<"traversal_->empty() is true\n";
	return *this;    
  }
  
  current_ = traversal_->pop();
  visited[current_] = true;
  
  
  Point p1 = Point(current_.x+1,current_.y);
  Point p2 = Point(current_.x  ,current_.y+1);
  Point p3 = Point(current_.x-1,current_.y);
  Point p4 = Point(current_.x  ,current_.y-1);
  //cout<<"current point:"<<current_<<endl;
  // checking the tolerance
  if ( ValidToVisit(p1) ) {traversal_->add(p1);}//cout<<p1<<" will be added\n";}
  if ( ValidToVisit(p2) ) {traversal_->add(p2);}//cout<<p2<<" will be added\n";}
  if ( ValidToVisit(p3) ) {traversal_->add(p3);}//cout<<p3<<" will be added\n";}
  if ( ValidToVisit(p4) ) {traversal_->add(p4);}//cout<<p4<<" will be added\n";}
  //cout<<"\n";
  //cout<<"new current_ :"<<current_<<endl<<endl;
  
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
	bool thisEmpty = false;
	bool otherEmpty = false;
	
	if (traversal_ == NULL) { thisEmpty = true; }
	if (other.traversal_ == NULL) { otherEmpty = true; }
	/*
	cout<<"!= "<<thisEmpty<<","<<otherEmpty<<endl;
	if (!thisEmpty)  { thisEmpty = traversal_->empty(); }
	if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }
	*/
	//cout<<"!= "<<thisEmpty<<","<<otherEmpty<<endl<<endl;
	if (thisEmpty && otherEmpty) return false; // both empty then the traversal_s are equal, return true
	else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_); //both not empty then compare the traversal_s
	else return true; // one is empty while the other is not, return true
	
	return false;
}

/** 
 * Added function
 * 
 * Determines if the point is goning to be visited.
 */
bool ImageTraversal::Iterator::ValidToVisit(const Point& p){
  if ( p.x >= png_->width() || p.y >= png_->height() ) 
	return false;

  if(visited[p] == true)
	return false;

  HSLAPixel& start = png_->getPixel(start_.x, start_.y);
  HSLAPixel& thisPoint = png_->getPixel(p.x, p.y);
  if ( calculateDelta(start, thisPoint) >= tolerance_ ) 
	return false;
  return true;
}

