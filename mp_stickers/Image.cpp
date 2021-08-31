#include<iostream>
#include"Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
using cs225::PNG;

void Image::lighten(){	
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.l+= 0.1;
	  if(currPixel.l<0) currPixel.l=0;
	  if(currPixel.l>1) currPixel.l=1;;
	}
	}
}
	
void Image::lighten (double amount){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.l+= amount;
	  if(currPixel.l<0) currPixel.l=0;
	  if(currPixel.l>1) currPixel.l=1;;
	}
	}
}

void Image::darken (){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.l-= 0.1;
		if(currPixel.l<0) currPixel.l=0;
		if(currPixel.l>1) currPixel.l=1;;
	}
	}
}

void Image::darken (double amount){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.l-= amount;
	  if(currPixel.l<0) currPixel.l=0;
	  if(currPixel.l>1) currPixel.l=1;
	}
	}
}

void Image::saturate (){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.s+= 0.1;
		if(currPixel.s<0) currPixel.s=0;
		if(currPixel.s>1) currPixel.s=1;;
	}
	}
}
void Image::saturate (double amount){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.s+= amount;
		if(currPixel.s<0) currPixel.s=0;
		if(currPixel.s>1) currPixel.s=1;;
	}
	}
}

void Image::desaturate (){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.s-= 0.1;
		if(currPixel.s<0) currPixel.s=0;
		if(currPixel.s>1) currPixel.s=1;;
	}
	}
}

void Image::desaturate (double amount){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.s-= amount;
		if(currPixel.s<0) currPixel.s=0;
		if(currPixel.s>1) currPixel.s=1;;
	}
	}
}

void Image::grayscale (){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.s = 0;
	}
	}
}

void Image::rotateColor (double degrees){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &currPixel = this->getPixel(x,y);
	  currPixel.h += degrees;
	  if(currPixel.h>360) currPixel.h-=360;
	  if(currPixel.h<0)   currPixel.h+=360;
	}
	}
}

void Image::illinify (){
	for (unsigned x = 0; x<this->width(); x++){
	for (unsigned y = 0; y<this->height();y++)
	{
	  HSLAPixel &pixel = this->getPixel(x,y);
	  
	  float distanceWithOrange = 0;
      float distanceWithBlue = 0;

      if( pixel.h > 180+11 ) distanceWithOrange = 360-pixel.h+11;
      else if(pixel.h < 11)  distanceWithOrange = 11-pixel.h;
      else distanceWithOrange = pixel.h-11;

      if( pixel.h < 216-180 ) distanceWithBlue = pixel.h+(360-216);
      else if(pixel.h >216)   distanceWithBlue = pixel.h-216;
      else distanceWithBlue = 216-pixel.h;

      if(distanceWithOrange>distanceWithBlue) pixel.h = 216;
      else pixel.h = 11;
	  
	}
	}
}
Image* Image::padding (const Image *oriImage){
	Image *paddedImage = new Image();
	paddedImage->resize(oriImage->width()+2, oriImage->height()+2);
	
	for (unsigned x = 0; x<oriImage->width(); x++){
	for (unsigned y = 0; y<oriImage->height();y++)
	{
	  HSLAPixel &pixel  = oriImage->getPixel(x,y);
	  HSLAPixel &pixel2 = paddedImage->getPixel(x+1,y+1);
	  pixel2 =  pixel;
	}
	}
	return paddedImage;
}

void Image::scale (double factor){
	Image original = *this;
	this->resize(this->width()*factor, this->height()*factor);
	
	if(factor<1){
		for (unsigned x = 0; x < this->width(); x++){
		for (unsigned y = 0; y < this->height();y++)
		{
		  HSLAPixel &pixel  = original.getPixel(x/factor, y/factor);
		  HSLAPixel &pixel2 = this->getPixel(x,y);
		  
		  pixel2 =  pixel;
		}
		}
		
	}
	else { //factor>=1 
		for (unsigned x = 0; x<original.width(); x++){
		for (unsigned y = 0; y<original.height();y++)
		{
		  HSLAPixel &pixel  = original.getPixel(x, y);
		  for(unsigned i = x*factor; i<(x+1)*factor; ++i)
			for(unsigned j = y*factor; j<(y+1)*factor; ++j){
			  HSLAPixel &pixel2 = this->getPixel(i,j);
			  pixel2 = pixel;
			}
		}
		}
	}
	
}
void Image::scale (unsigned w, unsigned h){
	  double newW = ((double)(w*1.0)) / ((double)this->width()*1.0);
    double newF = ((double)(h*1.0)) / ((double)this->height()*1.0);
    (newW < newF)?scale(newW):scale(newF);
}