#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);
    ofSetBackgroundAuto(false);
    isFullScreen = false;
    ofSetFrameRate(30);
    
    masterCounter = 0;
    direction = 1; //count up
    
    // OSC STUFF
    receiver.setup(PORT);
    mainMix = 0;
    chan01, chan02, chan03, chan04, chan05, chan06, chan07 = 0;
    meter01, meter02, meter03, meter04, meter05, meter06, meter07 = 0;
    meters = new float[7];
   
}

//--------------------------------------------------------------
void testApp::update(){

    
	parseOSCMessages();
    
    // FUN STUFF
    masterCounter+=direction;
    if (masterCounter > 2000) {
        direction = -1;
    }
    if (masterCounter < -2000) {
        direction = 1;
    }


}

//--------------------------------------------------------------
void testApp::draw(){
    //normalize mouse (within the window space...
    float daMouseX = float(mouseX)/float(ofGetWidth());
    float daMouseY = float(mouseY)/float(ofGetHeight());
   // ofLogNotice(ofToString(daMouseX));
    
    //Abstract line stuff
    for (int i = 0; i < ofGetWidth(); i++) {
        
        // set the color for each line
        int r = meters[0]*255;
        int g = meters[1]*255;
        int b = meters[2]*255;
        
        // line start and destination
        int xStart = i;
        int yStart = ofGetHeight()/2;
        int xDest = i*sin(i)*400; //400 is arbitrary.
        int yDest = i*cos(i)*masterCounter*mainMix;
        
        //shake the signal
        if (masterCounter%2 == 0) {
            yStart += mainMix*10;
            xDest += xDest*mainMix;
            yDest += yDest*mainMix;
        }
        else {
           yStart -= mainMix*10;
            xDest -= xDest*mainMix;
            yDest -= yDest*mainMix;
            
        }

        ofSetColor(r, g, b); //Replace this with pixel colors from feed
         ofLine(xStart, yStart, xDest, yDest);    }

}

//--------------------------------------------------------------
void testApp::parseOSCMessages() {
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for meter messages
        if(m.getAddress() == "/main/meter") {
            //Go through arguments, get them as floats
            for (int i = 0; i < m.getNumArgs(); i++) {
                meters[i] = m.getArgAsFloat(i);
            }
            mainMix = meters[1];
        }
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f' || 'F') {
        isFullScreen = !isFullScreen;
        ofSetFullscreen(isFullScreen);
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
