#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5));

	int len = 720;
	if (ofGetFrameNum() % 2 == 0) {

		ofColor color;
		color.setHsb((int)ofRandom(ofGetFrameNum(), ofGetFrameNum() + 50) % 255, 200, 255);

		this->params.push_back(ofRandom(0, 50));
		this->colors.push_back(color);
	}

	while (this->params.size() > 120) {

		this->params.erase(this->params.begin());
		this->colors.erase(this->colors.begin());
	}

	for (int i = 0; i < this->params.size(); i++) {

		int p = this->params[i] * 2;
		if (p > 50) {

			ofPushMatrix();
			ofRotate(90);
		}

		vector<glm::vec2> vertices;
		vertices.push_back(this->make_point(len, p));
		vertices.push_back(this->make_point(len, p + 1));
		vertices.push_back(this->make_point(len, 100 - p - 1));
		vertices.push_back(this->make_point(len, 100 - p));

		ofFill();
		ofSetColor(this->colors[i], ofMap(i, 0, this->params.size(), 32, 255));
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39, ofMap(i, 0, this->params.size(), 32, 255));
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		if (p > 50) { ofPopMatrix(); }
	}

}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}