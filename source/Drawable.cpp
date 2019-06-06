#include "Drawable.h"

namespace gbox
{

Drawable::Drawable() :
m_vao(0),
m_vbo(0)
{
}

Drawable::Drawable(GLuint vao, GLuint vbo) :
m_vao(vao),
m_vbo(vbo)
{
}

void
Drawable::draw()
{
}

void
Drawable::render()
{
}

Drawable::~Drawable()
{
}

};
