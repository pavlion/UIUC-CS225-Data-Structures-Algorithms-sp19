#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG *input = new PNG();
  input->readFromFile(inputFile);
  PNG output = *input;
  
  for (unsigned x = 0; x < input->width();x++){
    for (unsigned y = 0; y < input->height(); y++)
    {
      HSLAPixel &currPixel = input->getPixel(input->width()-x-1,input->height()-y-1);
	  HSLAPixel &destPixel = output.getPixel(x,y);
	  destPixel = currPixel;
    }
  }
  output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  
  int center_w = width/2;
  int center_h = height/2;
  
  double max = 0;
  double min = INT_MAX;
  double max2 = 0;
  double min2 = INT_MAX;
  for (int x = 0; x   < width;x++){
    for (int y = 0; y < height; y++){
	  if( (tan(x+y)+1)*180 > max)
		  max = (tan(x+y)+1)*180;
	  
	  if( (tan(x+y)+1)*180 < min)
		  min = (tan(x+y)+1)*180;
	  
	  double theta = 0;
	  int deltaX = x-center_w, deltaY = y-center_h;
	  if( deltaY!=0 ) theta = atan( deltaX/deltaY );
	  if( theta> max2 ) max2 = theta;
	  if( theta< min2 ) min2 = theta;
	}
  }
  //std::cout<<"REACHED LINE:"<<__LINE__<<std::endl;
  //std::cout<<width<<","<<height<<","<<center_w<<","<<center_h<<std::endl;
  const double a =0.5/3.1415926, b = 0;//std::cout<<"REACHED LINE:"<<__LINE__<<std::endl;
  for (int x = 0; x   < width;x++){
    for (int y = 0; y < height; y++)
    {
      HSLAPixel &currPixel = png.getPixel(x,y);
	  currPixel.h = ((tan(x+y)+1)*180-min)/(max-min)*360;
	  if(currPixel.h<0||currPixel.h>360) std::cout<<currPixel.h<<","<<std::endl;
	  double theta = 0;
	  int deltaX = x-center_w, deltaY = y-center_h;
	  if( deltaY!=0 ) theta = atan( deltaX/deltaY );
	  currPixel.s = (a*theta+b-min2)/(max2-min2)*100;
	  if(currPixel.s<0||currPixel.s>100) std::cout<<currPixel.s<<","<<std::endl;
	  currPixel.l = 0.8;
    }
  }
  ///std::cout<<"REACHED LINE:"<<__LINE__<<std::endl;
    
  png.writeToFile("art.png");
  return png;
}
