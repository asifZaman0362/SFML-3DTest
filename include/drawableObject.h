#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>


class SFObject {
public:
    SFObject(sf::Drawable *drawable, int layer = 2) : drawable(drawable), layer(layer) {}
    sf::Drawable* GetDrawable() { return drawable; }
    int GetLayer() { return layer; }
private:
    sf::Drawable* drawable;
    int layer;
};

class GLObject {
public:
    GLObject(GLfloat* data, sf::Texture &texture, int layer = 1) : 
            data(data), texture(texture), layer(layer) {}
    GLfloat* GetData() { return data; }
    int GetLayer() { return layer; }
private:
    GLfloat* data;
    sf::Texture& texture;
    int layer;
};