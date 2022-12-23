#include "DEFINITONS.h" // - ALL INCLUDED HEADER AND FILES ARE DEFINED HERE

int main(){
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE);
    window.setFramerateLimit(SCREEN_FRAMERATE);

    /* --------- SPLASH SCREEN INITIALIZATION --------- */
    sf::Texture splashTex;
    if (!splashTex.loadFromFile(SPLASH_BACKGROUND_PATH)) {}
    sf::RectangleShape splash(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    splash.setTexture(&splashTex);
    /* ------------------------------------------------ */

    /* ------------------ BACKGROUND INITIALIZATION ------------------ */
    sf::Texture bgTex;
    if (!bgTex.loadFromFile(GAME_BACKGROUND_PATH)) {}
    sf::RectangleShape bg(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    bg.setTexture(&bgTex);
    /* --------------------------------------------------------------- */

    /* --------- CAR INITIALIZATION --------- */
    sf::Texture carLeftTex;
    if (!carLeftTex.loadFromFile(CAR_LEFT_PATH)) {}
    sf::Texture carMidTex;
    if (!carMidTex.loadFromFile(CAR_MID_PATH)) {}
    sf::Texture carRightTex;
    if (!carRightTex.loadFromFile(CAR_RIGHT_PATH)) {}
    sf::RectangleShape car(sf::Vector2f(CAR_SIZE_X, CAR_SIZE_Y));
    car.setOrigin(car.getSize().x / 2, car.getSize().y / 2);
    car.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 5));
    car.setTexture(&carMidTex);

    /*sf::SoundBuffer engine;
    if (!engine.loadFromFile("audio/carEngine.wav")) {}
    sf::Sound carEngine;
    carEngine.setBuffer(engine);
    carEngine.setVolume(100);
    carEngine.setLoop(1);*/

    /* -------------------------------------- */

    /* --------- OBSTACLE INITIALIZATION --------- */
    sf::Texture obstacleTex[6];
    sf::Sprite obstacle[6];
    obstacleTex[0].loadFromFile(OBSTACLE_BILL1_PATH);
    obstacleTex[1].loadFromFile(OBSTACLE_BILL2_PATH);
    obstacleTex[2].loadFromFile(OBSTACLE_TREE1_PATH);
    obstacleTex[3].loadFromFile(OBSTACLE_TREE2_PATH);
    obstacleTex[4].loadFromFile(OBSTACLE_CAR1_PATH);
    obstacleTex[5].loadFromFile(OBSTACLE_CAR2_PATH);
    for (int i = 0; i <= 5; i++) {
        obstacleTex[i].setSmooth(true);
        obstacle[i].setTexture(obstacleTex[i]);
    }
    /* ------------------------------------------- */

    /* ---------------- SPEED TEXT INITIALIZATION ---------------- */
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {}
    sf::Text speedText;
    speedText.setPosition(80, 25);
    speedText.setFont(font);
    /* ----------------------------------------------------------- */

    /* ---------------- TIME TEXT INITIALIZATION ----------------
    sf::Text timeText;
    timeText.setPosition(180, 25);
    timeText.setFont(font);
     ---------------------------------------------------------- */

    /* - CIRCUIT INITIALIZATION - */
    generateLines();
    generateObstacles(obstacle);
    /* -------------------------- */

    /* - LINE INITIALIZATION - */
    int N = lines.size();
    int posZ = 0;
    int posX = 0;
    /* ----------------------- */

    /* --- MOVEMENT INITIALIZATION --- */
    float rightMove = 15;
    float leftMove = -15;
    int accelerate = 0;
    int brake = 10;
    /* ------------------------------- */

    /* ---------- GAME START ---------- */
    window.draw(splash);
    window.display();
    std::cout << "GAME IS RUNNING \n \n";
    Sleep(SPLASH_SHOW_TIME);

    //sf::Clock clock;
    //sf::Time elapsed = clock.getElapsedTime();
    //carEngine.play();

    /* -------------------------------- */

    /* -------------------- GAME MUSIC -------------------- */
    sf::Music gameMusic;
    if (!gameMusic.openFromFile("audio/gameLoop.wav")) {}
    gameMusic.setLoop(true);
    gameMusic.setVolume(50);
    gameMusic.play();
    /* ---------------------------------------------------- */

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {if (event.type == sf::Event::Closed) window.close();}
        window.clear();
        window.draw(bg);

        /* ---------------------------- ACCELERATION SYSTEM ---------------------------- */
        if (accelerate >= 740) {accelerate = 751; accelerate-=20;}
        if (accelerate <= 0) {accelerate = 0;}
        /* ----------------------------------------------------------------------------- */

        /* ---------------------- LINE SYSTEM INITIALIZATION ---------------------- */
        float posX = car.getPosition().x;
        float x = 0, dx = 0;
        int maxy = SCREEN_HEIGHT;
        if (posZ >= N * SEGMENT_LENGTH) {posZ -= N * SEGMENT_LENGTH;}

        int startPos = posZ / SEGMENT_LENGTH;
        /* ------------------------------------------------------------------------ */

        /* ------------------------------ CAR CONTROLS ------------------------------ */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {car.move(rightMove, 0); car.setTexture(&carRightTex); posZ += accelerate;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {car.move(leftMove, 0); car.setTexture(&carLeftTex); posZ += accelerate;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {accelerate += 10; posZ += accelerate;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {accelerate -= brake;}
        if (event.type == sf::Event::KeyReleased) {car.setTexture(&carMidTex); accelerate--; posZ += accelerate;}
        
        //carEngine.setPitch(accelerate / 50);
        /* -------------------------------------------------------------------------- */


        /* ------------------------------------ LINE SYSTEM ------------------------------------ */
        for (int n = startPos; n < startPos + 300; n++){
            Line& currLine = lines[(n+1) % N];
            currLine.project(posX - x, 1500, posZ - (n >= N ? N * SEGMENT_LENGTH : 0));

            x += dx; //adds the curve so that the camera would turn
            dx += currLine.getCurve();  //takes the curve from the generated in generator
            if (currLine.getSY() >= maxy) continue; //only draws the next line if the current line has been fully generated

            Line prevLine = lines[n % N];

            /* ------------------------- COLOR OF ROAD, APEX, AND ENVIRONMENT ------------------------- */
            sf::Color environmentC = (n / 5) % 2 ? sf::Color(2, 41, 2) : sf::Color(3, 43, 3);
            sf::Color apexC = (n / 3) % 2 ? sf::Color(200, 50, 50) : sf::Color(255, 255, 255);
            sf::Color roadC = (n / 12) % 2 ? sf::Color(107, 107, 107) : sf::Color(109, 109, 109);
            /* ---------------------------------------------------------------------------------------- */

            /* --------------------------------- DRAW ROAD, APEX, AND ENVIRONMENT --------------------------------- */
            createShape environment(window, environmentC, 0, prevLine.getSY(), SCREEN_WIDTH, 0, currLine.getSY(), SCREEN_WIDTH);
            createShape apex(window, apexC, prevLine.getSX(), prevLine.getSY(), prevLine.getSW() * 1.2, currLine.getSX(), currLine.getSY(), currLine.getSW() * 1.2);
            createShape road(window, roadC, prevLine.getSX(), prevLine.getSY(), prevLine.getSW(), currLine.getSX(), currLine.getSY(), currLine.getSW());
            /* ------------------------------------------------------------------------------------------------------- */
        }
        /* ------------------------------------------------------------------------------------- */

        /* ---------------------------------- DRAW OBSTACLE ---------------------------------- */
        for (int n = startPos + 300; n > startPos; n--) { lines[n % N].drawObstacle(window); }
        /* ----------------------------------------------------------------------------------- */
        
        /* --------------------------- DRAW TEXT --------------------------- */
        speedText.setString("Speed: " + std::to_string(accelerate / 4) + "KM/H");
        window.draw(speedText);

        //timeText.setString("Time Remaining: " + std::to_string(elapsed.asSeconds()));
        //window.draw(timeText);
        /* ----------------------------------------------------------------- */

        window.draw(car);
        window.display();
    }
    return 0;
}

/*      NCS UNUSED CODE
* 
        //CAR UPGRADE TO FLY
        float posY = car.getPosition().y;
        float upMove = -10.f;
        float downMove = 10.f;
        if (posY == car.getSize().y / 2) {upMove = 0; }
        if (posY == height - (car.getSize().y/2)) {downMove= 0;}

        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){car.move(0, upMove);}
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){car.move(0, downMove);}
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){car.rotate(leftMove);}
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){car.rotate(rightMove);}

        /*
        createRoad(window, sf::Color(90, 10, 40), 0, 720, 1280, 0, 520, 1280);
        createRoad(window, sf::Color(100, 100, 100), 640, 720, 600, 640, 520, 200);
        createRoad(window, sf::Color(255, 255, 255), 640, 700, 30, 640, 540, 15);
        window.draw(cloud1);
        window.draw(cloud2);
        window.draw(car);
        */