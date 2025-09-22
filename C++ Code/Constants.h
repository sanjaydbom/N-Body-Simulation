#pragma once

//Particle constants
const float MASS = 1.0; //kg
const float RADIUS = 80; //m
const float X_LENGTH = 800; //m
const float Y_LENGTH = 600; //m

//Simulation Constants
const float G = 0.1; //N * (m / kg) ^ 2
const int NUM_PARTICLES = 2;

//Visualization Constants
const int HEIGHT = 600; //pixels
const int WIDTH = 800; //pixels
const int RESOLUTION = 50; //Number of triangles per circle
const float PIXEL_RADIUS = 2 * RADIUS / X_LENGTH;
const std::string TITLE = "Simulation";
const float BACKGROUND_COLOR[] = {0.0,0.0,0.0,1.0};
const float OBJECT_COLOR[] = {1.0,1.0,1.0,1.0};


