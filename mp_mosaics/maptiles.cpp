/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
	if (theTiles.empty()) return NULL;
	
	vector< Point<3> > tiles; // converted 
	map< Point<3>, int > mapping;
    vector< TileImage >::iterator it;
    
    //Loop through the tiles
    //for (it = theTiles.begin(); it != theTiles.end(); it++)
    for (unsigned i = 0; i < theTiles.size(); ++i)
    {
        //get average color
        LUVAPixel ori = theTiles[i].getAverageColor();
        Point<3> p(ori.l, ori.u, ori.v);
        tiles.push_back(p);
        mapping[p] = i;
    }

    KDTree<3>::KDTree tree(tiles);

    int row = theSource.getRows();
    int col = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(row, col);

    //loop through each tile
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            LUVAPixel regionColor = theSource.getRegionColor(i, j); 
			
            Point<3> target(regionColor.l, regionColor.u, regionColor.v);
            Point<3> closestPoint = tree.findNearestNeighbor(target);
            //use the map to find the tile 
            int tileIndex = mapping[closestPoint];

            //put the tile onto canvas
            canvas->setTile(i,j, &theTiles[tileIndex]);
        }
    }

    //return canvas
    return canvas;
}

