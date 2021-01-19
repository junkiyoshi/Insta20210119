#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 100;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->target_list.push_back(glm::vec2());
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int i = 0; i < this->number_of_targets; i++) {

		int deg = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.005 + i * 0.003), 0, 1, -360, 360);
		this->target_list[i] = glm::vec2(ofGetWidth() * 0.5 + 250 * cos(deg * DEG_TO_RAD), ofGetHeight() * 0.5 + 250 * sin(deg * DEG_TO_RAD));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->target_list[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}