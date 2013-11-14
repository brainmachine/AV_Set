//
//  rectMaker.cpp
//  AV_Set_OSC_test
//
//  Created by Leó Stefánsson on 2013-11-13.
//
//

#include "rectMaker.h"

void RectMaker::setupRect(int offset) {
    //RECT STUFF
    rectXPos = 0;
    rectYPos = 0+offset;
    rectSize = 30;
    rectSpacing = 0;
    numXRects = ofGetWidth()/rectSize-rectSpacing;
    numYRects = ofGetHeight()/rectSize-rectSpacing;
    numRects = numYRects*numXRects;
    rectCount = 0;
    doRectCount = true;
    ofLogNotice("\n numYRects: "+ofToString(numYRects)+"\n numXRects: "+ofToString(numXRects)+"\n numRects: "+ofToString(numRects));
    
}
//--------------------------------------------------------------
void RectMaker::updateRect() {
    //rectCount = index;
    rectXPos = (rectCount * rectSize)%ofGetWidth();
    if (rectCount%numXRects==0) {
        ofLogNotice("should go to new line");
        rectYPos += rectSize%ofGetHeight();
        ofLogNotice("rectCount: "+ofToString(rectCount));
    }
    if (rectCount >= numRects) {
        rectYPos = 0;
    }
}
void RectMaker::drawRect(float r, float g, float b) {
    ofSetColor(255*r, 255*g, 255*b);
    ofRect(rectXPos, rectYPos, rectSize, rectSize);
}
