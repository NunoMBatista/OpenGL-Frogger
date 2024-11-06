#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   

    perspective(60, 10, 1000);
    //glOrtho(-800, 800, -800, 800, -10000, 10000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // lookat(
    //     0, 0, -1, 
    //     0, 0, 0,
    //     0, 1, 0
    // );

    lookat(
        //0, 0, cam_dist, 
        gw()/2, gh()/2, cam_dist, 
        0, 0, 0,
        0, 1, 0
    );

    draw_frog(300, 400, 320);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
