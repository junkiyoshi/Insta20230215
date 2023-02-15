#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetCircleResolution(60);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int len = 300;
	int radius = len * 0.35;

	for (int x = -170; x <= 170; x += 340) {

		for (int y = -170; y <= 170; y += 340) {

			ofSetColor(64);
			ofNoFill();
			ofDrawCircle(glm::vec2(x, y), radius);
			ofDrawRectangle(glm::vec2(x, y), len, len);

			vector<glm::vec2> vertices;
			for (float param = 0; param < 100; param++) {

				auto noise_value = ofNoise(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, param) * 0.02, ofGetFrameNum() * 0.015));
				if (noise_value < 0.5) {

					vertices.push_back(this->make_point(len, param));
				}
				else if (noise_value > 0.6) {

					vertices.push_back(glm::normalize(this->make_point(len, param)) * radius);
				}
				else {

					vertices.push_back(glm::normalize(this->make_point(len, param)) * radius + (this->make_point(len, param) - glm::normalize(this->make_point(len, param)) * radius) * ofMap(noise_value, 0.5, 0.6, 1, 0));
				}
			}

			ofSetColor(255);

			ofFill();
			for (auto& vertex : vertices) {

				vertex += glm::vec2(x, y);
				ofDrawCircle(vertex, 2);
			}

			ofNoFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
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