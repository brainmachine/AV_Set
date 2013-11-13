//
//  drawHorizon.cpp
//  AV_Set_OSC_test
//
//  Created by Leó Stefánsson on 2013-11-13.
//
//

#include "horizon.h"


//--------------------------------------------------------------
void horizon::drawHorizon() {
    //Abstract line stuff
    // set the color for each line
    int r = meters[0]*255;
    int g = meters[1]*255;
    int b = meters[2]*255;
    ofSetColor(r, g, b); //Replace this with pixel colors from feed
    
    for (int i = 0; i < ofGetWidth(); i++) {
        
        
        // line start and destination
        int xStart = i;
        int yStart = ofGetHeight()/2;
        int xDest = i*sin(i)*400; //400 is arbitrary.
        int yDest = i*cos(i)*masterCounter*meters[1];
        
        //shake the signal
        if (masterCounter%2 == 0) {
            yStart += meters[1]*10;
            xDest += xDest*meters[1];
            yDest += yDest*meters[1];
        }
        else {
            yStart -= meters[1]*10;
            xDest -= xDest*meters[1];
            yDest -= yDest*meters[1];
        }
        
        ofLine(xStart, yStart, xDest, yDest);
    }
}