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
    int accelerate = 420;
    int brake = 20;
    /* ------------------------------- */


    /* ---------- GAME START ---------- */
    window.draw(splash);
    window.display();
    std::cout << "GAME IS RUNNING \n \n";
    Sleep(SPLASH_SHOW_TIME);
    /* -------------------------------- */

    /* -------------------- GAME MUSIC -------------------- */
    sf::Music gameMusic;
    if (!gameMusic.openFromFile("audio/gameLoop.wav")) {}
    gameMusic.setLoop(true);
    gameMusic.setVolume(80);
    gameMusic.play();
    /* ---------------------------------------------------- */

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {if (event.type == sf::Event::Closed) window.close();}
        window.clear();
        window.draw(bg);

        /* ---------------------------- ACCELERATION SYSTEM ---------------------------- */
        if (accelerate == 740) accelerate = 751;
        if (accelerate >= 400 && accelerate < 740) { accelerate = accelerate * 1.005; }
        /* ----------------------------------------------------------------------------- */

        /* ---------------------- LINE SYSTEM INITIALIZATION ---------------------- */
        float posX = car.getPosition().x;
        float x = 0, dx = 0;
        int maxy = SCREEN_HEIGHT;
        if (posZ >= N * SEGMENT_LENGTH) {posZ -= N * SEGMENT_LENGTH;}
        if (posZ < 0) {posZ += N * SEGMENT_LENGTH;}
        int startPos = posZ / SEGMENT_LENGTH;
        /* ------------------------------------------------------------------------ */

        /* ------------------------------ CAR CONTROLS ------------------------------ */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { car.move(rightMove, 0); car.setTexture(&carRightTex); posZ += accelerate; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { car.move(leftMove, 0); car.setTexture(&carLeftTex); posZ += accelerate; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { posZ += accelerate; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { accelerate -= 50; }
        if (event.type == sf::Event::KeyReleased) { car.setTexture(&carMidTex); accelerate = 420; posZ += accelerate; }
        /* -------------------------------------------------------------------------- */


        /* ------------------------------------ LINE SYSTEM ------------------------------------ */
        for (int n = startPos; n < startPos + 300; n++){
            Line& currLine = lines[(n+1) % N];
            currLine.project(posX - x, 1500, posZ - (n >= N ? N * SEGMENT_LENGTH : 0));

            x += dx;
            dx += currLine.getCurve();

            if (currLine.getY() >= maxy) continue;

            Line prevLine = lines[n % N];

            /* ------------------------- COLOR OF ROAD, APEX, AND ENVIRONMENT ------------------------- */
            sf::Color environmentC = (n / 5) % 2 ? sf::Color(2, 41, 2) : sf::Color(3, 43, 3);
            sf::Color apexC = (n / 3) % 2 ? sf::Color(200, 50, 50) : sf::Color(255, 255, 255);
            sf::Color roadC = (n / 12) % 2 ? sf::Color(107, 107, 107) : sf::Color(109, 109, 109);
            /* ---------------------------------------------------------------------------------------- */

            /* --------------------------------- DRAWING ROAD, APEX, AND ENVIRONMENT --------------------------------- */
            createShape environment(window, environmentC, 0, prevLine.getY(), SCREEN_WIDTH, 0, currLine.getY(), SCREEN_WIDTH);
            createShape apex(window, apexC, prevLine.getX(), prevLine.getY(), prevLine.getW() * 1.2, currLine.getX(), currLine.getY(), currLine.getW() * 1.2);
            createShape road(window, roadC, prevLine.getX(), prevLine.getY(), prevLine.getW(), currLine.getX(), currLine.getY(), currLine.getW());
            /* ------------------------------------------------------------------------------------------------------- */
        }
        /* ------------------------------------------------------------------------------------- */

        /* ---------------------------------- DRAW OBSTACLE ---------------------------------- */
        for (int n = startPos + 300; n > startPos; n--) { lines[n % N].drawObstacle(window); }
        /* ----------------------------------------------------------------------------------- */

        window.draw(car);
        std::cout << accelerate << std::endl;
        window.display();
    }
    return 0;
}


/*      UNUSED CODE

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