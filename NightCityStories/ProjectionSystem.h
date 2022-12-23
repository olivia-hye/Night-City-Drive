#ifndef PROJECTION_H
#define PROJECTION_H

#include "DEFINITONS.h"

int height = SCREEN_HEIGHT;
int width = SCREEN_WIDTH;
float cameraDepth = CAMERA_DEPTH;
int roadWidth = ROAD_WIDTH;
int segmentLength = SEGMENT_LENGTH;

class Line {
private:
    float x, y, z; //3D Coordinates
    float sX, sY, sW; //Projected Coordinates
    float curve;
    float scale;
    float obstacleX;
    sf::Sprite obstacle;

    //sf::FloatRect obstacle_collider;

public:
    Line() { obstacleX = curve = x = y = z = 0; }
    ~Line() {}

    void project(int camX, int camY, int camZ) {
        scale = cameraDepth / (z - camZ);
        sX = (1 + scale * (x - camX)) * width / 2;
        sY = (1 - scale * (y - camY)) * height / 2;
        sW = scale * roadWidth * width / 2;
    }

    void drawObstacle(sf::RenderWindow& window) {
        sf::Sprite obs = obstacle;
        int obsW = obs.getTextureRect().width;
        int obsH = obs.getTextureRect().height;

        float destX = sX + scale * obstacleX * width / 2;
        float destY = sY;
        float destW = obsW * sW / 266;
        float destH = obsH * sW / 266;

        destX += destW * obstacleX;
        destY += destH * (-1);

        obs.setScale(destW / obsW, destH / obsH);
        obs.setPosition(destX, destY);

        //obstacle_collider = obs.getGlobalBounds();

        window.draw(obs);
    }

    //sf::FloatRect getObstacleBounds(){return obstacle_collider;}

    float getx() { return x; }
    float gety() { return y; }
    float getz() { return z; }
    float getSX() { return sX; }
    float getSY() { return sY; }
    float getSW() { return sW; }
    float getCurve() { return curve; }

    friend void generateLines();
    friend void generateObstacles(sf::Sprite[]);
};

#endif PROJECTION_H