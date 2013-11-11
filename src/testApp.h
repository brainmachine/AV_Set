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
    
    
		
    //OSC stuff
    ofxOscReceiver receiver;
    float mainMix;
    float chan01, chan02, chan03, chan04, chan05, chan06, chan07;
    float meter01, meter02, meter03, meter04, meter05, meter06, meter07;
    float* meters;
    
    

    
    // FUN STUFF
    int masterCounter;
    int direction;
    bool isFullScreen;
    

    
    
};
