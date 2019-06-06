#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "GLBase.h"

namespace gbox
{

class Drawable : public GLBase
{
public:
	Drawable ();
	Drawable (GLuint vao, GLuint vbo);

    virtual void draw   ();
	virtual void render ();

    virtual ~Drawable ();

protected:
	GLuint m_vao, m_vbo;
};

};

#endif
