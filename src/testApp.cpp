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
	current_msg_string = 0;
    mainMix = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/main/mix"){
			// both the arguments are int32's
			mainMix = m.getArgAsFloat(0);
            ofLogNotice("you are the master of the universe"+ofToString(m.getArgAsFloat(0)));
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
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
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
        int r = daMouseX*sin(masterCounter)/4;
        int g = i/4;
        int b = daMouseX*daMouseY*i/4;
        ofSetColor(r, g, b); //Replace this with pixel colors from feed
        ofLine(i, ofGetHeight()/2, i*sin(i)*mouseY, i*cos(i)*/*mouseY*30*/masterCounter);
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
