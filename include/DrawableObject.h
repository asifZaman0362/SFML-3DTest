#ifndef _DRAWABLEOBJECT_H_
#define _DRAWABLEOBJECT_H_

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>


class SFObject {
public:
    SFObject(sf::Drawable*, int);
    ~SFObject();
    
    sf::Drawable* GetDrawable();
    int GetLayer();
    
    void SetDrawable(sf::Drawable*);
    void SetLayer(int);

private:
    sf::Drawable* drawable;
    int layer;
};

class GLObject {
public:
    GLObject(const GLfloat*, sf::Texture*, int);
    ~GLObject();

    const GLfloat* GetData();
    int GetLayer();
    sf::Texture* GetTexture();
    
    void SetTexture(sf::Texture*);
    void SetLayer(int);

private:
    const GLfloat* data;
    sf::Texture* texture;
    int layer;
};


#endif