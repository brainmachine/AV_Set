//
//  rectMaker.h
//  AV_Set_OSC_test
//
//  Created by Leó Stefánsson on 2013-11-13.
//
//


#include "ofMain.h"


class RectMaker : public ofRectangle  {
public:
    void setupRect();
    void updateRect(int rectIndex);
    void drawRect(int, int g, int b);
    
public:
    // RECT STUFF
    int rectXPos;
    int rectYPos;
    int rectSize;
    int rectSpacing;
    
    int numXRects;
    int numYRects;
    int numRects;
    int rectCount;
    bool doRectCount;
};