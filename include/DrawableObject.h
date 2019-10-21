#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>


class SFObject {
public:
    SFObject(sf::Drawable *drawable, int layer = 2) : drawable(drawable), layer(layer) {}
    ~SFObject() {
        delete drawable;
        drawable = nullptr;
    }
    sf::Drawable* GetDrawable() { return drawable; }
    int GetLayer() { return layer; }
private:
    sf::Drawable* drawable;
    int layer;
};

class GLObject {
public:
    GLObject(const GLfloat* data, sf::Texture *texture, int layer = 1) : 
            data(data), texture(texture), layer(layer) {}
    ~GLObject() {
        delete data;
        delete texture;
        //data = nullptr;
        texture = nullptr;
    }
    const GLfloat* GetData() { return data; }
    int GetLayer() { return layer; }
private:
    const GLfloat* data;
    sf::Texture* texture;
    int layer;
};