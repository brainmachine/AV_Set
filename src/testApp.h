#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void parseOSCMessages();
        void drawHorizon();
        void makeRect(int rectIndex);
    
		
    //OSC stuff
    ofxOscReceiver receiver;
    float mainMix;
    float* meters;
    int* triggers;
    int* _triggers;
    
    
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
    
    // FUN STUFF
    int masterCounter;
    int direction;
    bool isFullScreen;


    
    
};
