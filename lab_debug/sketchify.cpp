/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */

#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
 /***changes 1***/
HSLAPixel* myFavoriteColor() {
    HSLAPixel *p = new HSLAPixel(238, 0.8, 0.5);
    return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = NULL;//std::cout << "Reached line " << __LINE__ << std::endl;
    //std::cout<<inputFile<< std::endl;
    original = new PNG();
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();//std::cout << "Reached line " << __LINE__ << std::endl;

    // Create out.png
    PNG* output;
    /***changes 2***/
    output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();
    //std::cout << "Reached line " << __LINE__ << std::endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
	/***changes 3: from 0 < y < height to 0 < y && y < height***/
    for (unsigned y = 1; 0 < y && y < height; y++) { 
        for (unsigned x = 1; 0 < x && x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
			
			/***changes 4: change from HSLAPixel currOutPixel to HSLAPixel &currOutPixel***/
            HSLAPixel &currOutPixel = output->getPixel(x, y);
            if (diff > 20) { 
				/***changes 5: change from currOutPixel = *myPixel; to the following***/
                currOutPixel.h = myPixel->h;
				currOutPixel.s = myPixel->s;
				currOutPixel.l = myPixel->l;
				currOutPixel.a = myPixel->a;
            }
        }
    }
    //std::cout << "Reached line " << __LINE__ << std::endl;
    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
