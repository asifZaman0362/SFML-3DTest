#include "stdfx.h"

int main() {
    
    sf::Window window(sf::VideoMode(800, 480), "3DTest");
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    glClearColor(0.8f, 0.0f, 0.3f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glEnable(GL_DEPTH_TEST);
    //gluPerspective(45.0, 1.6, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    bool running = true;
    while(running) {
        
        sf::Event e {};
        while(window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                running = false;
            else if (e.type == sf::Event::Resized)
                glViewport(0, 0, e.size.width, e.size.height);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_POLYGON);

        glColor3f(1.0, 0.0, 0.0);   glVertex3f(-0.5, -0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);   glVertex3f(-0.5,  0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);   glVertex3f( 0.5,  0.5, -0.5);
        glColor3f(1.0, 0.0, 1.0);   glVertex3f( 0.5, -0.5, -0.5);
        
        glEnd();

        window.display();
    }

    return EXIT_SUCCESS;

}
