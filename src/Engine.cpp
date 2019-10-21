#include "Engine.h"
#include <iostream>


Game::Game(Settings settings) : settings(settings) {}

Game::~Game() {
    for(SFObject* object : sfObjects) {
        delete object;
        object = nullptr;
    }
    for(GLObject* object : glObjects) {
        delete object;
        object = nullptr;
    }
}

void Game::Start() {
    running = true;

    while (running)
    {
        // Request a 24-bits depth buffer when creating the window
        sf::ContextSettings ctxSettings;
        ctxSettings.depthBits = settings.depthBits;
        ctxSettings.sRgbCapable = settings.sRGB;

        // Create the main window
        int style = settings.fullScreen ? 8 : 7;
        sf::VideoMode videoMode(settings.window_width, settings.window_height);
        window.create(videoMode, settings.title, style, ctxSettings);
        window.setVerticalSyncEnabled(true);

        // Create a sprite for the background
        backgroundTexture.setSrgb(settings.sRGB);
        if (!backgroundTexture.loadFromFile("Assets/Textures/background.jpg"))
            return;
        background.setTexture(backgroundTexture);

        // Create some text to draw on top of our OpenGL object
        sf::Font font;
        if (!font.loadFromFile("Assets/Fonts/sansation.ttf"))
            return;
        text = sf::Text("SFML / OpenGL demo", font);
        sRgbInstructions = sf::Text("Press space to toggle sRGB conversion", font);
        mipmapInstructions = sf::Text("Press return to toggle mipmapping", font);
        text.setFillColor(sf::Color(255, 255, 255, 170));
        sRgbInstructions.setFillColor(sf::Color(255, 255, 255, 170));
        mipmapInstructions.setFillColor(sf::Color(255, 255, 255, 170));
        text.setPosition(250.f, 300.f);
        sRgbInstructions.setPosition(150.f, 350.f);
        mipmapInstructions.setPosition(180.f, 400.f);

        // Load a texture to apply to our 3D cube
        sf::Texture texture;
        if (!texture.loadFromFile("Assets/Textures/texture.jpg"))
            return;
        texture.setSrgb(settings.sRGB);

        // Attempt to generate a mipmap for our cube texture
        // We don't check the return value here since
        // mipmapping is purely optional in this example
        texture.generateMipmap();

        // Make the window the active window for OpenGL calls
        window.setActive(true);

        // Enable Z-buffer read and write
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glClearDepth(1.f);

        // Disable lighting
        glDisable(GL_LIGHTING);

        // Configure the viewport (the same size as the window)
        glViewport(0, 0, window.getSize().x, window.getSize().y);

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

        // Bind the texture
        glEnable(GL_TEXTURE_2D);
        sf::Texture::bind(&texture);

        // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
        static const GLfloat cube[] =
        {
            // positions    // texture coordinates
            -20, -20, -20,  0, 0,
            -20,  20, -20,  1, 0,
            -20, -20,  20,  0, 1,
            -20, -20,  20,  0, 1,
            -20,  20, -20,  1, 0,
            -20,  20,  20,  1, 1,

             20, -20, -20,  0, 0,
             20,  20, -20,  1, 0,
             20, -20,  20,  0, 1,
             20, -20,  20,  0, 1,
             20,  20, -20,  1, 0,
             20,  20,  20,  1, 1,

            -20, -20, -20,  0, 0,
             20, -20, -20,  1, 0,
            -20, -20,  20,  0, 1,
            -20, -20,  20,  0, 1,
             20, -20, -20,  1, 0,
             20, -20,  20,  1, 1,

            -20,  20, -20,  0, 0,
             20,  20, -20,  1, 0,
            -20,  20,  20,  0, 1,
            -20,  20,  20,  0, 1,
             20,  20, -20,  1, 0,
             20,  20,  20,  1, 1,

            -20, -20, -20,  0, 0,
             20, -20, -20,  1, 0,
            -20,  20, -20,  0, 1,
            -20,  20, -20,  0, 1,
             20, -20, -20,  1, 0,
             20,  20, -20,  1, 1,

            -20, -20,  20,  0, 0,
             20, -20,  20,  1, 0,
            -20,  20,  20,  0, 1,
            -20,  20,  20,  0, 1,
             20, -20,  20,  1, 0,
             20,  20,  20,  1, 1
        };

        // Enable position and texture coordinates vertex components
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

        // Disable normal and color vertex components
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        // Make the window no longer the active window for OpenGL calls
        window.setActive(false);

        // Create a clock for measuring the time elapsed
        sf::Clock clock;

        // Flag to track whether mipmapping is currently enabled
        bool mipmapEnabled = true;

        // Start game loop
        while (window.isOpen())
        {
            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                {
                    running = false;
                    window.close();
                }

                // Escape key: exit
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    running = false;
                    window.close();
                }

                // Return key: toggle mipmapping
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                {
                    if (mipmapEnabled)
                    {
                        // We simply reload the texture to disable mipmapping
                        if (!texture.loadFromFile("Assets/Textures/texture.jpg"))
                            return;

                        mipmapEnabled = false;
                    }
                    else
                    {
                        texture.generateMipmap();

                        mipmapEnabled = true;
                    }
                }

                // Adjust the viewport when the window is resized
                if (event.type == sf::Event::Resized)
                {
                    Resize(event.size.width, event.size.height);
                }
            }

            Draw(clock.getElapsedTime().asSeconds());
        }
    }
}

void Game::InitObjects() {
    
}

void Game::Resize(unsigned int x, unsigned int y) {
    window.setActive(true);
    glViewport(0, 0, x, y);
    window.setActive(false);
}

void Game::Draw(float dt) {
    // Draw the background
    window.pushGLStates();
    window.draw(background);
    window.popGLStates();

    // Make the window the active window for OpenGL calls
    window.setActive(true);

    // Clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // We get the position of the mouse cursor, so that we can move the box accordingly
    float x =  sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
    float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, -100.f);
    glRotatef(dt * 50.f, 1.f, 0.f, 0.f);
    glRotatef(dt * 30.f, 0.f, 1.f, 0.f);
    glRotatef(dt * 90.f, 0.f, 0.f, 1.f);

    // Draw the cube
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Make the window no longer the active window for OpenGL calls
    window.setActive(false);

    // Draw some text on top of our OpenGL object
    window.pushGLStates();
    window.draw(text);
    window.draw(sRgbInstructions);
    window.draw(mipmapInstructions);
    window.popGLStates();

    // Finally, display the rendered frame on screen
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