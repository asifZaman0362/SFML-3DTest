#include "engine.h"
#include <iostream>


Game::Game(Settings settings) : settings(settings) {}

Game::~Game() {}

void Game::Start() {
    running = true;
    while(running) {
        sf::VideoMode videoMode(settings.window_width, settings.window_height);
        int style = settings.fullScreen ? 8 : 7;
        sf::ContextSettings ctxSettings;
        ctxSettings.depthBits = settings.depthBits;
        ctxSettings.sRgbCapable = settings.sRGB;
        window.create(videoMode, settings.title, style, ctxSettings);

        if(settings.vSync) {
            window.setVerticalSyncEnabled(true);
        } else if (settings.frameRateLimit > 0) {
            window.setFramerateLimit(settings.frameRateLimit);
        }

        InitObjects();
        std::cout << "SKSJSJ";

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glClearDepth(1.0);
        glClearColor(1.0f, 0.0f, 1.0f, 1);
        glViewport(0, 0, window.getSize().x, window.getSize().y);
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float ratio = float(window.getSize().x) / window.getSize().y;
        glFrustum(-ratio, ratio, -1.0, 1.0, 1.0, 500.0);

        window.setActive(false);

        while(window.isOpen()) {
            sf::Event e {};
            while(window.pollEvent(e)) {
                switch (e.type) {
                    case sf::Event::Closed:
                        Quit();
                        break;
                    case sf::Event::Resized:
                        Resize(e.size.width, e.size.height);
                        break;
                    case sf::Event::KeyPressed:
                        if (e.key.code == sf::Keyboard::Escape) Quit();
                        break;
                    default:
                        continue;
                }
            }
            Draw();
        }
    }
}

void Game::InitObjects() {
    std::cout << "SKSJSJ";
    sf::Texture* backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile("Assets/Textures/background.jpg");
    sf::Sprite *sprite = new sf::Sprite(*backgroundTexture);
    sf::CircleShape circle(400);
    sfObjects.push_back(new SFObject(sprite, 0));
    //sfObjects.push_back(new SFObject(&circle, 0));
    sf::Text *text = new sf::Text();
    sf::Font *sansation = new sf::Font();
    sansation->loadFromFile("Assets/Fonts/sansation.ttf");
    text->setFont(*sansation);
    text->setString("Go Fuck Yourself Punk!");
    sfObjects.push_back(new SFObject(text, 2));
    //std::cout << "SKSJSJ";
    //SortObjectsByLayer();
}

void Game::Resize(unsigned int x, unsigned int y) {
    window.setSize(sf::Vector2u(x, y));
    window.setActive(true);
    glViewport(0, 0, window.getSize().x, window.getSize().y);
    float ratio = float(x) / y;
    glFrustum(-ratio, ratio, -1.0, 1.0, 1.0, 500);
    window.setActive(false);
}

void Game::Draw() {
    window.clear(sf::Color( 255, 0, 255));
    int nextObjects = 0;
    int i = 0;
    // First pass to draw background objects
    for (i; i < sfObjects.size(); i++) {
        if (sfObjects.at(i)->GetLayer() == 0) {
            window.draw(*sfObjects.at(i)->GetDrawable());
        } else { 
            nextObjects = i;
            break;
        }
    }
    // Seccond pass to draw GLObjects
    window.setActive(true);
    glClear(GL_DEPTH_BUFFER_BIT);
    //Draw some shit
    window.setActive(false);
    // Third pass to draw UI Objects
    for (i; i < sfObjects.size(); i++) {
        if (sfObjects.at(i)->GetLayer() == 2) {
            window.draw(*sfObjects.at(i)->GetDrawable());
        } else break;
    }
    window.display();
}

void Game::Quit() {
    window.close();
    running = false;
    std::cout << "Quit Game." << std::endl;
}

bool Game::Compare(SFObject* obj1, SFObject* obj2) {
    return obj1->GetLayer() > obj2->GetLayer();
}

void Game::SortObjectsByLayer() {
    int max = sfObjects.size();
    SFObject* key;
    for (int i = 1; i < max; i++) {
        key = sfObjects.at(i);
        int pos = i-1;
        while (pos >= 0 && Compare(sfObjects.at(pos), key)) {
            sfObjects.at(pos + 1) = sfObjects.at(pos);
            pos--;
        }
        sfObjects.at(pos + 1) = key;
    }
}