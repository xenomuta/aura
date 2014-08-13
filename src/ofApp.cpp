#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
 	ofBackground(30, 30, 30, 255);
	cam.initGrabber(320, 240);
	img.allocate(320, 240, OF_IMAGE_COLOR);
	shadow.allocate(320, 240, OF_IMAGE_COLOR);
	color.allocate(320, 240);
	finder.setup("haarcascade_frontalface_default.xml");
	fbo.allocate(320, 240, GL_RGBA32F_ARB);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	img.setFromPixels(cam.getPixels(), 320, 240, OF_IMAGE_COLOR);
	if (ofRandom(0, 10) < 4) {
		shadow = img;
	}
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();
    ofEnableSmoothing();
//	ofNoFill();
	// ofSetLineWidth(2);
	ofFill();

	fbo.begin();
  ofEnableAlphaBlending();
//  ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
//    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
//  ofEnableBlendMode(OF_BLENDMODE_SCREEN);

  //  ofDisableBlendMode();

  
	float h = fmodf(ofGetElapsedTimef()*10, 255);
	float s = 255;
	float v = 255 * cos(ofGetFrameNum() / 10);
  
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
  
	ofColor cc = ofColor::fromHsb(255 - h, 200, 128);
	ofSetColor(255 - (int)cc.r, 255 - (int)cc.g, 255 - (int)cc.b, ofRandom(16, 32));
	shadow.draw(8 - (cos(ofGetFrameNum() / 4) * 16), -ofRandom(1, 3));

	ofSetColor(255, 255, 255, 16);
  fbo.draw(5 - (cos(ofGetFrameNum() / 8) * 10), -ofRandom(1, 3));

  ofEnableBlendMode(OF_BLENDMODE_ADD);

	for (unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofxCvBlob b = finder.blobs[i];
		ofRectangle r = b.boundingRect;
		//ofPoint p = b.centroid;
		ofPoint p = ofPoint(r.x, r.y);
		// int a = (r.width + r.height) / 3;
		int a = ofRandom(10, 60);

		h = fmodf(ofGetElapsedTimef() * 10, 255);
		cc = ofColor::fromHsb(h, s, 255);
		ofSetColor((int)cc.r, (int)cc.g, (int)cc.b, ofRandom(24, 32));
		for (int j = 0; j < ofRandom(5, 250); j++) {
			ofCircle(ofRandom(p.x, p.x + r.width), ofRandom(p.y, p.y + r.height), a);
			ofCircle(ofRandom(p.x, p.x + r.width) - (r.width / 2), ofRandom(p.y, p.y + r.height) + (r.height * 1.5), a);
			ofCircle(ofRandom(p.x, p.x + r.width) + (r.width / 2), ofRandom(p.y, p.y + r.height) + (r.height * 1.5), a);
		}
	}
	fbo.end();
	// ofSetColor(255, 255, 255, 255);
	// shadow.draw(0, 0, 640, 480);
	ofSetColor(255, 255, 255, 255);
	img.draw(0, 0, 640, 480);
	ofSetColor(255, 255, 255, 255);
  if (!debug) return;
  
	fbo.draw(0, 0, 640, 480);
  fbo.draw(660, 0, 640, 480);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'd' || key == 'D') {
    debug = !debug;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
