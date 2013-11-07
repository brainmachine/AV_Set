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
    chan01 = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/main/mix"){
			// both the arguments are int32's
			mainMix = m.getArgAsFloat(0);
            ofLogNotice("mainMix: "+ofToString(m.getArgAsFloat(0)));
		}
        if (m.getAddress() == "main/chan01") {
            chan01 = m.getArgAsFloat(0);
            ofLogNotice("this is what it is: "+ofToString(chan01));
        }
		// check for mouse button message
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
		
		}
        
	}
    
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
    float daMouseY = float(mouseY)/ofGetHeight();
   // ofLogNotice(ofToString(daMouseX));
    
    //Abstract line stuff
    for (int i = 0; i < ofGetWidth(); i++) {
        
        // set the color for each line
        int r = daMouseX*sin(masterCounter)/4;
        int g = i/4;
        int b = daMouseX*daMouseY*i/4;
        
        // line start and destination
        int xStart = i;
        int yStart = ofGetHeight()/2;
        int xDest = i*sin(i)*mouseY;
        int yDest = i*cos(i)*masterCounter*mainMix;
        
        //shake the signal
        if (masterCounter%2 == 0) {
            yStart += mainMix*30;
            xDest += xDest*mainMix;
            yDest += yDest*mainMix;
        }
        else {
           yStart -= mainMix*30;
            xDest -= xDest*mainMix;
            yDest -= yDest*mainMix;
            
        }
        
        
        
        ofSetColor(r, g, b); //Replace this with pixel colors from feed
         ofLine(xStart, yStart, xDest, yDest);    }

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
