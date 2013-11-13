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
    meters = new float[7];
    triggers = new float[7];
    _triggers = new float[7];
    //populate triggers
    for (int i = 0; i < 7; i++) {
        triggers[i] = 0;
        _triggers[i] = 0;
    }
    
    //RECT STUFF
    rectXPos = 0;
    rectYPos = 0;
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
    
    // STRUCTURED RECTANGLES
    
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    // Structured rectangles
    
    
    
    drawRect();
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
               // ofLogNotice("meter0"+ofToString(i)+": "+ofToString(meters[i]));
            }
        }
        else if(m.getAddress() == "/main/trigger")
        {
            //populate triggers
            for (int i = 0; i < m.getNumArgs(); i++) {
                triggers[i] = m.getArgAsFloat(i);
            }
            
            //only update triggers if the message is new
            for (int i = 0; i < m.getNumArgs(); i++) {
                
                //do your triggering in here:
                if (triggers[i] != _triggers[i] && triggers[i] != 0) {
                    triggers[i] = m.getArgAsFloat(i);
                    rectCount += triggers[i]; //add 1 or 0. only counts the 1's
                    updateRect(rectCount);
                }
                
            }
            //do what you want in here:
            
            
            //set previous trigger msgs
            for (int i = 0; i < m.getNumArgs(); i++) {
                _triggers[i] = triggers[i];
            }
            
        }
	}
}

//--------------------------------------------------------------
void testApp::updateRect(int rectIndex) {
    rectCount = rectIndex;
    rectXPos = (rectCount * rectSize)%ofGetWidth();
    if (rectCount%numXRects==0) {
        ofLogNotice("should go to new line");
        rectYPos += rectSize%ofGetHeight();
        ofLogNotice("rectCount: "+ofToString(rectCount));
    }
    if (rectCount > numRects) {
        
    }
}
void testApp::drawRect() {
    ofSetColor(255*meters[0], 255*meters[0], 255*(1-meters[4]));
    ofRect(rectXPos, rectYPos, rectSize, rectSize);
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
