#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string.h>
#include "drawableObject.h"


struct Settings {
    
    int window_width;
    int window_height;
    int depthBits;
    int frameRateLimit;
    bool sRGB;
    bool mipmap;
    bool vSync;
    bool fullScreen;
    char* title;
    
    Settings(char* title, int window_width, int window_height, int depthBits,
    int frameRateLimit, bool sRGB, bool mipmap, bool vSync, bool fullScreen) {
        this->title = title;
        this->window_width = window_width;
        this->window_height = window_height;
        this->depthBits = depthBits;
        this->frameRateLimit = frameRateLimit;
        this->sRGB = sRGB;
        this->mipmap = mipmap;
        this->vSync = vSync;
        this->fullScreen = fullScreen;
    }

};

class Game {
public:
    Game(Settings);
    ~Game();

    // Create a RenderWindow and setup OpenGL.
    void Start();
    // Clear OpenGL settings and terminate the app after closing the RenderWindow.
    void Quit();

private:
    Settings settings;
    sf::RenderWindow window;
    bool running;
    sf::Clock mainClock;
    std::vector<SFObject*> sfObjects;
    std::vector<GLObject*> glObjects;

    void InitObjects();
    void Input();
    void Update();
    void Draw();
    void Resize(unsigned int, unsigned int);
    bool Compare(SFObject*, SFObject*);
    void SortObjectsByLayer();
};