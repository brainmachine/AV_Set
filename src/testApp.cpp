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
    
    //RECT STUFF
    rectX = 0;
    rectY = 0;
    rectSize = 30;
    rectSpacing = 0;
    numXRects = ofGetWidth()/rectSize-rectSpacing;
    numYRects = ofGetHeight()/rectSize-rectSpacing;
    numRects = numYRects*numXRects;
    rectCount = 0;
    doRectCount = true;
    didRectCount = false;
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
    
    // Structured rectangles
    
    //If the signal is above a certain limit
    if (meters[0] > 0.001) { //if percussion (ch04) occurs
        doRectCount = true; //don't count while stuff goes on
        
    }
    
    else if (doRectCount) {
        rectX += rectSize;
        rectCount++;
        doRectCount = false;
    }
    
    ofLogNotice(ofToString(doRectCount));
    

    if (rectCount%numXRects == 0 && doRectCount) {
        rectX = 0;
        rectY += rectSize;
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    drawHorizon();
    
    // Structured rectangles
    
    ofSetColor(0, 255*meters[0], 255);
    ofRect(rectX, rectY, rectSize, rectSize);
}

//--------------------------------------------------------------
void testApp::drawHorizon() {
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
        
        ofSetColor(r, g, b); //Replace this with pixel colors from feed
        ofLine(xStart, yStart, xDest, yDest);
    }
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
        else if(m.getAddress() == "/main/trigger") {
            
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
