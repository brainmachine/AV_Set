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
    
    
    // FBO INIT
    // FBOs
    rectFBO.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    rectFBO.begin();
    ofClear(255,255,255, 0);
    rectFBO.end();
    
    horizonFBO.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    horizonFBO.begin();
    ofClear(255,255,255, 0);
    horizonFBO.end();
    
    //Rectmake
    myRectMaker.setupRect();
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
    
    horizonFBO.begin();
    ofClear(255, 255, 255, 0);
    drawHorizon();
    horizonFBO.end();
    
    // Structured rectangles
   
    
    rectFBO.begin();
    myRectMaker.drawRect(meters[0], meters[1], 1-meters[4]);
    rectFBO.end();
    
    rectFBO.draw(0,0);
    horizonFBO.draw(0,0);
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
                    ofLogNotice("triggers: "+ofToString(triggers[i]));
                    //do what you want in here:
                    myRectMaker.rectCount += triggers[4];
                    myRectMaker.updateRect(myRectMaker.rectCount);
//                    rectCount += triggers[i]*numXRects*i; //add 1 or 0. only counts the 1's
//                    updateRect(rectCount);
                
            }
            
            }
            
            
            //set previous trigger msgs
            for (int i = 0; i < m.getNumArgs(); i++) {
                _triggers[i] = triggers[i];
            }
            
        }
	}
}

//--------------------------------------------------------------
void testApp::drawHorizon() {
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
