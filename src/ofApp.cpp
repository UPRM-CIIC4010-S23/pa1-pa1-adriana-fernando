#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");           // Loads a sound file (in bin/data/)
    sound.setLoop(repeat);              // Makes the song loop indefinitely
    sound.setVolume(1);               // Sets the song volume
    ofSetBackgroundColor(36, 32, 56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    if (!pause) {
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    progress = sound.getPosition();
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();

    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    ofDrawBitmapString("Press 'd' to change song!", 0, 50);
    ofDrawBitmapString("Volume: "+ ofToString(sound.getVolume() * 100) + " %", 0, 70); //added volume 


    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    }

    if (loop) {
        if (song == '6' && percent == 99) {
            sound.load("geesebeat.wav");
            sound.play();
            song = '7';
        } else if (song == '7' && percent == 99) {
            sound.load("pigeon-coo.wav");
            sound.play();
            song = '8';
        } else if (song == '8' && percent == 99) {
            sound.load("rock-song.wav");
            sound.play();
            song = '9';
        } else if (song == '9' && percent == 99) {
            sound.load("beat.wav");
            sound.play();
            song = '6';
        }


    }

    if (repeat) {
        sound.setLoop(true);
    } else {
        sound.setLoop(false);
    }

     for (int l = 0; l < percent ; l ++) { //draws progress bar :)
        ofDrawRectangle(l * ofGetWidth() , 90, percent*ofGetWidth()/98, 10);
     }
    

    
    //ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
    if (shuffle && progress == 0) {
            int random = ofRandom(6, 10);
            if (random == 6) {
                sound.load("beat.wav");
                sound.play();
            } else if (random == 7) {
                sound.load("geesebeat.wav");
                sound.play();
            } else if (random == 8) {
                sound.load("pigeon-coo.wav");
                sound.play();
            } else if (random == 9) {
                sound.load("rock-song.wav");
                sound.play();
            }
        }
    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}

void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0,0,ofRandom(25,255));  // rectangle's color changes to different shades of blue :)
    

    for (int j = 0; j < 65; j += 1) { //draws more rectangles *fixed the width :)
        ofDrawRectRounded(j * (ofGetWidth()/64), ofGetHeight() - 100, ofGetWidth()/64, amplitudes[j]*2, 10); // *fixed the rectangle width when window changes size :)
        
        
    }
    // ofDrawRectRounded(2, ofGetHeight() - 100, 20, amplitudes[0], 10); //rounded rectangle's corners :)
    ofSetBackgroundColor(255, 182, 193); // Background color for mode 1
}

void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
    ofSetBackgroundColor(203, 195, 250); // Background color for mode 2
}

void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    // YOUR CODE HERE
    ofSetBackgroundColor(144, 238, 144); // Background color for mode 3
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case 'a': // pauses visualizer
        if (pause) {
            pause = false;
        } else {
            pause = true;
        }
        break;
    case 'l': // loops music
        if (loop) {
            loop = false;
            break;
        } else {
            loop = true;
        }
        break;
    case 'r': // repeats song
        if (repeat) {
            repeat = false;
        } else {
            repeat = true;
            if (progress == 0) {
                sound.play();
            }
        }
        break;
    case 'b': // shuffles songs
        if (shuffle) {
            shuffle = false;
        } else {
            shuffle = true;
        }
        break;
    case 'd': // When pressing 'd' changes song
        if (song == '6') {
            sound.load("geesebeat.wav");
            sound.play();
            sound.setLoop(true);
            song = '7';
        } else if (song == '7') {
            sound.load("pigeon-coo.wav");
            sound.play();
            sound.setLoop(true);
            song = '8';
        } else if (song == '8') {
            sound.load("rock-song.wav");
            sound.play();
            sound.setLoop(true);
            song = '9';
        } else if (song == '9') {
            sound.load("beat.wav");
            sound.play();
            sound.setLoop(true);
            song = '6';
        }

    case '=': // raises the volume :)
        if (sound.getVolume() < 1.0) { sound.setVolume(sound.getVolume() + 0.1); }
        else if ( sound.getVolume() == 1.0) { break; }
        break;
    
    case '-': // lowers the volume *fixed
        if (sound.getVolume() > 0.0) { sound.setVolume(sound.getVolume() - 0.1); }
        if (sound.getVolume() < 0) sound.setVolume(0);
        break;

    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------