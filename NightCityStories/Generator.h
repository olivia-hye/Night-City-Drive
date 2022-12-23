#include "DEFINITONS.h"

std::vector<Line> lines;

/* ----------------- LINE GENERATOR ----------------- */
void generateLines(){
    for (int i = 0; i < 4000; i++){
        Line line;
        line.z = i * segmentLength;

        if (i > 300  && i < 700 ) line.curve = 1.4;
        if (i > 1100 && i < 1400) line.curve = -0.9;
        if (i > 1600 && i < 1800) line.curve = 0.7;
        if (i > 2200 && i < 3200) line.curve = 2.0;
        if (i > 3500 && i < 3800) line.curve = -1.0;

        lines.push_back(line);
    }
}
/* -------------------------------------------------- */

/* -------- OBSTACLE GENERATOR -------- */
void generateObstacles(sf::Sprite ob[]){
    for (int i = 0; i < 4000; i++) {

        /* ----------------------- SAUL BILLBOARD 1 ----------------------- */
        if (i == 80) {lines[i].obstacleX = 2; lines[i].obstacle = ob[0];}
        if (i == 300) {lines[i].obstacleX = -3; lines[i].obstacle = ob[0];}
        if (i == 900) {lines[i].obstacleX = 2; lines[i].obstacle = ob[0];}
        if (i == 1800) {lines[i].obstacleX = -3; lines[i].obstacle = ob[0];}
        /* ---------------------------------------------------------------- */

        /* ---------------------- SAUL BILLBOARD 2 ---------------------- */
        if (i == 600) {lines[i].obstacleX = 2; lines[i].obstacle = ob[1];}
        if (i == 1200) {lines[i].obstacleX = -3; lines[i].obstacle = ob[1];}
        if (i == 2400) {lines[i].obstacleX = 2; lines[i].obstacle = ob[1];}
        /* -------------------------------------------------------------- */

        /* ---------------------------------------- TREE 1 ---------------------------------------- */
        if (i > 0 && i < 450 && i % 45 == 0) {lines[i].obstacleX = 2.5; lines[i].obstacle = ob[2];}
        if (i > 55 && i < 1000 && i % 50 == 0) {lines[i].obstacleX = -3.5; lines[i].obstacle = ob[2];}
        /* ---------------------------------------------------------------------------------------- */

        /* ------------------------------------- TREE 2 ------------------------------------- */
        if (i > 1800 && (i - 99) % 91 == 0) {lines[i].obstacleX = 2; lines[i].obstacle = ob[3];}
        if (i > 1600 && i % 151 == 0) {lines[i].obstacleX = -3; lines[i].obstacle = ob[3];}
        /* ---------------------------------------------------------------------------------- */

        /* ------------------------------------------ CAR 1 ------------------------------------------ */
        if (i > 0 && i < 1000 && i % 140 == 0) {lines[i].obstacleX = 0.35; lines[i].obstacle = ob[4];}
        if (i > 2000 && i < 4000 && i % 370 == 0) {lines[i].obstacleX = -0.55; lines[i].obstacle = ob[4];}
        /* ------------------------------------------------------------------------------------------- */

        /* ------------------------------------------- CAR 2 ------------------------------------------- */
        if (i > 0 && i < 1000 && i % 194 == 0) {lines[i].obstacleX = -0.55; lines[i].obstacle = ob[5];}
        if (i > 2000 && i < 4000 && i % 410 == 0) {lines[i].obstacleX = 0.35; lines[i].obstacle = ob[5];}
        /* --------------------------------------------------------------------------------------------- */
    }
    /* -------------------------------- */
}