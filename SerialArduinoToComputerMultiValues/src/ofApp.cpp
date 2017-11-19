#include "ofApp.h"


void ofApp::setup()
{
    // Choosing '0' here will connect to the first available serial device.
    // It is recommended to connect to a specific device to avoid problems, e.g.
    //
    // serial.setup("/dev/tty.usbmodem620711", 9600);
    //
    // You can list available devices like this.
    //
    // for (auto device: serial.getDeviceList())
    // {
    //      std::cout << "Device: " << device.getDeviceID() << ": " << device.getDevicePath() << std::endl;
    // }
    //
    // For now, chosing '0' is a good place to start.
    
    ////////// Runthis on terminal ls -ls /dev/cu* - This command lets you see all the serial devices on your computer.
    ////////// Copy the name of your ardunio in here, like the red port downhere
    serial.setup("/dev/cu.usbmodem1411", 9600);

        mySound.load("gholf-ball.wav");
    
    }



void ofApp::update()
{
    // As long as there is serial data available to read, repeat.
    while (serial.available() > 0)
    {
        // Read the byte.
        char b = serial.readByte();
        
        // End of line character.
        if (b == '\n')
        {
            // Split the buffer on the commas.
            std::vector<std::string> tokens = ofSplitString(buffer, ",");
            
            // The number of tokens in our packet is 3, here we check to make
            // sure that our packet is correctly formed.
            if (tokens.size() == 3)
            {
                potValue = ofToInt(tokens[0]);
                buttonValue_0 = ofToBool(tokens[1]);
                sensorValue_1 = ofToBool(tokens[2]);
            }
            
            std::cout << ofToString(tokens) << std::endl;
            
            buffer = "";
        }
        else
        {
            // If it's not the line feed character, add it to the buffer.
            buffer += b;
            // buffer = buffer + b
            // 60, 0, 1 = string
        }
    }
}


void ofApp::draw()
{
    // The potentiometer values range from 0 - 1023.
    // We mape these from 0 - 255, which is a valid grayscale range.
    //
    // This will always use the last valid `potValue` that we received from
    // the Arduino.
    int color = ofMap(potValue, 0, 1023, 0, 255);
    
    // Draw a background color that corresponds to the potentiometer.
    ofBackground(color);
    
    ofSetColor(ofColor::yellow);
    ofFill();
    
    if (buttonValue_0 != true)
    {
        if (!mySound.isPlaying()){
            mySound.play();
        }
    }
    
    ofSetColor(ofColor::green);
    ofFill();

    if (sensorValue_1 != true)
    {
        ofDrawRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
    }
}
