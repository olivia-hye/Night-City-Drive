#pragma once

#define TITLE "NIGHT CITY DRIVE"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_FRAMERATE 60

#define SPLASH_SHOW_TIME 3000
#define SPLASH_BACKGROUND_PATH "textures/splash.png"

#define FONT_PATH "fonts/Montserrat-Bold.ttf"
#define GAME_MUSIC_PATH "audios/gameLoop.wav"
#define GAME_BACKGROUND_PATH "textures/bg.png"
#define CLOUD_PATH "textures/cloud.png"

#define CAR_LEFT_PATH "textures/car_left.png"
#define CAR_MID_PATH "textures/car_mid.png"
#define CAR_RIGHT_PATH "textures/car_right.png"
#define CAR_ENGINE_SOUND "audio/carEngine.wav"

#define OBSTACLE_BILL1_PATH "textures/bill1.jpg"
#define OBSTACLE_BILL2_PATH "textures/bill2.jpg"
#define OBSTACLE_TREE1_PATH "textures/tree1.png"
#define OBSTACLE_TREE2_PATH "textures/tree2.png"
#define OBSTACLE_CAR1_PATH "textures/car1.png"
#define OBSTACLE_CAR2_PATH "textures/car2.png"

#define ROAD_WIDTH 2000
#define SEGMENT_LENGTH 180
#define CAMERA_DEPTH 0.84

#define CAR_SIZE_X 250.f
#define CAR_SIZE_Y 200.f


#define NOMINMAX
#include <Windows.h>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ProjectionSystem.h"
#include "Road.h"
#include "Generator.h"

//#include <unistd.h> | for linux