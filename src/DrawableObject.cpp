#include "DrawableObject.h"

// SFObject definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SFObject::SFObject(sf::Drawable* drawable, int layer) : drawable(drawable), layer(layer) {}

SFObject::~SFObject() {
    delete drawable;
    drawable = nullptr;
}

sf::Drawable* SFObject::GetDrawable() { return drawable; }

int SFObject::GetLayer() { return layer; }

void SFObject::SetDrawable(sf::Drawable* drawable) { this->drawable = drawable; }

void SFObject::SetLayer(int layer) { this->layer = layer; }


// GLObject definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


GLObject::GLObject(const GLfloat* data, sf::Texture* texture, int layer) : data(data), texture(texture), layer(layer) {}

GLObject::~GLObject() {
    delete[] data;
    delete texture;
    data = nullptr;
    texture = nullptr;
}

const GLfloat* GLObject::GetData() { return data; }

int GLObject::GetLayer() { return layer; }

sf::Texture* GLObject::GetTexture() { return texture; }

void GLObject::SetTexture(sf::Texture* texture) { this->texture = texture; }

void GLObject::SetLayer(int layer) { this->layer = layer; }