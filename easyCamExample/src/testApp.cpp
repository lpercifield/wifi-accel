#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	glEnable(GL_DEPTH_TEST);
	
	// this sets the camera's distance from the object
	cam.setDistance(100);
	
	ofSetCircleResolution(64);
	bShowHelp = true;
    //create the socket and bind to port 11999
	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);
}

//--------------------------------------------------------------
void testApp::update(){
    char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;
	if(message!=""){
		//stroke.clear();
        
		//float x,y,z;
		vector<string> strPoints = ofSplitString(message,"[/p]");
		//for(int i=0;i<strPoints.size();i++){
        //cout << strPoints[0] << endl;
        vector<string> point = ofSplitString(strPoints[0],"|");
        if( point.size() == 3 ){
            x=atof(point[0].c_str());
            y=atof(point[1].c_str());
            z=atof(point[2].c_str());
            x = ofMap(x, 0, 1023, -512, 512);
            y = ofMap(y, 0, 1023, -512, 512);
            z = ofMap(z, 0, 1023, -512, 512);
            //stroke.push_back(ofPoint(x,y));
        }
        
		//}
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	cam.begin();		
	ofRotateX(ofRadToDeg(.5));
	ofRotateY(ofRadToDeg(-.5));
	
	ofBackground(0);
	
	ofSetColor(255,0,0);
	ofFill();
	ofBox(30);
	ofNoFill();
	ofSetColor(0);
	ofBox(30);
	
	ofPushMatrix();
	ofTranslate(0,0,20);
	ofSetColor(0,0,255);
	ofFill();
	ofBox(5);
	ofNoFill();
	ofSetColor(0);
	ofBox(5);
	ofPopMatrix();
    //cam.setTarget(ofVec3f(x, y));
    cam.lookAt(ofVec3f(0,0));
    cam.setPosition(x, y, z);
	cam.end();
	drawInteractionArea();
	ofSetColor(255);
	string msg = string("Using mouse inputs to navigate (press 'c' to toggle): ") + (cam.getMouseInputEnabled() ? "YES" : "NO");
	msg += string("\nShowing help (press 'h' to toggle): ")+ (bShowHelp ? "YES" : "NO");
	if (bShowHelp) {
		msg += "\n\nLEFT MOUSE BUTTON DRAG:\nStart dragging INSIDE the yellow circle -> camera XY rotation .\nStart dragging OUTSIDE the yellow circle -> camera Z rotation (roll).\n\n";
		msg += "LEFT MOUSE BUTTON DRAG + TRANSLATION KEY (" + ofToString(cam.getTranslationKey()) + ") PRESSED\n";
		msg += "OR MIDDLE MOUSE BUTTON (if available):\n";
		msg += "move over XY axes (truck and boom).\n\n";
		msg += "RIGHT MOUSE BUTTON:\n";
		msg += "move over Z axis (dolly)";
	}
	msg += "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapStringHighlight(msg, 10, 20);
}
//--------------------------------------------------------------
void testApp::drawInteractionArea(){
	ofRectangle vp = ofGetCurrentViewport();
	float r = MIN(vp.width, vp.height) * 0.5f;
	float x = vp.width * 0.5f;
	float y = vp.height * 0.5f;
	
	ofPushStyle();
	ofSetLineWidth(3);
	ofSetColor(255, 255, 0);
	ofNoFill();
	glDepthMask(false);
	ofCircle(x, y, r);
	glDepthMask(true);
	ofPopStyle();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key) {
		case 'C':
		case 'c':
			if(cam.getMouseInputEnabled()) cam.disableMouseInput();
			else cam.enableMouseInput();
			break;
			
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
			bShowHelp ^=true;
			break;
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
