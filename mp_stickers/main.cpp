#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {

  Image photo; 
	photo.readFromFile("alma.png");
  Image I;    
	I.readFromFile("i.png");
	I.scale(45/327.0);

  Image P;    
	P.readFromFile("popcorn.png");
	P.scale(0.1);

  Image S;    
	S.readFromFile("sunglasses.png");
	S.scale(450,300);

	Image S2(P);


  StickerSheet sheet(photo, 4);
	sheet.addSticker(I, 0, 0);
	sheet.addSticker(P, 300, 300);
	sheet.addSticker(S, 450, 100);
	//std::cout << (sheet.getSticker(0)==NULL) << std::endl; 
	//std::cout << (sheet.getSticker(1)==NULL) << std::endl;
	//std::cout << (sheet.getSticker(2)==NULL) << std::endl;
	//std::cout << (sheet.getSticker(3)==NULL) << std::endl;
	//std::cout << (sheet.getSticker(4)==NULL) << std::endl;
	//std::cout << (sheet.getSticker(5)==NULL) << std::endl;
	
	sheet.render().writeToFile("myImage.png");
	
	StickerSheet sheet2(sheet);
	sheet2.render().writeToFile("myImage2.png");

	cout<<"REACHED LINE"<<__LINE__<<endl;
	StickerSheet sheet3=sheet; 	
	sheet3.render().writeToFile("myImage3.png");
  
	return 0;
}

