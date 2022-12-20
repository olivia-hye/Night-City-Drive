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
    
    float spriteX;
    sf::Sprite obstacle;

public:
    Line() { spriteX = curve = x = y = z = 0; }
    ~Line() {}

    void project(int camX, int camY, int camZ) {
        scale = cameraDepth / (z - camZ);
        sX = (1 + scale * (x - camX)) * width / 2;
        sY = (1 - scale * (y - camY)) * height / 2;
        sW = scale * roadWidth * width / 2;
    }

    void drawObstacle(sf::RenderWindow& window) {
        sf::Sprite s = obstacle;
        int obsW = s.getTextureRect().width;
        int obsH = s.getTextureRect().height;

        float destX = sX + scale * spriteX * width / 2;
        float destY = sY;
        float destW = obsW * sW / 266;
        float destH = obsH * sW / 266;

        destX += destW * spriteX;
        destY += destH * (-1);

        s.setScale(destW / obsW, destH / obsH);
        s.setPosition(destX, destY);

        window.draw(s);
    }

    float getx() { return x; }
    float gety() { return y; }
    float getX() { return sX; }
    float getY() { return sY; }
    float getW() { return sW; }
    float getCurve() { return curve; }

    friend void generateLines();
    friend void generateObstacles(sf::Sprite[]);
};