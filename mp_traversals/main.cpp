
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"
#include "colorPicker/MyColorPicker2.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG aplus;
  aplus.readFromFile("colorPicker/artwork/aplus.png");
  
  FloodFilledImage image(aplus);
  BFS bfs(aplus, Point(108, 106), 0.4);
  
  MyColorPicker my;
  image.addFloodFill( bfs, my );
  Animation animation = image.animate(50);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  for(int i=0; i<50; ++i)
	animation.addFrame( lastFrame );
  
  FloodFilledImage image2(lastFrame);
  DFS dfs(lastFrame, Point(112, 112), 1);
  MyColorPicker2 my2;
  image2.addFloodFill( dfs, my2 );
  
  Animation animation2 = image2.animate(50);
  unsigned frameCounts = animation2.frameCount();
  for(unsigned i=0; i<frameCounts; ++i)
	animation.addFrame( animation2.getFrame(i) );

  
  
  lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  
  for(int i=0; i<50; ++i)
	animation.addFrame( lastFrame );
  animation.write("myFloodFill.gif");
  


  return 0;
}
