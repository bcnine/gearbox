#ifndef ARRAY_DRAWABLE_H
#define ARRAY_DRAWABLE_H

#include "Drawable.h"

#include <vector>
#include <utility>

namespace gbox
{

class ArrayDrawable : public Drawable
{

friend class DrawableLoader;

public:
	ArrayDrawable ();
	ArrayDrawable (GLuint vao, GLuint vbo);

    virtual void draw   ();
	virtual void render ();

private:

    void addPrimitive(GLenum primtype,
                      unsigned int numindices,
                      unsigned int arrayoffset,
                      const std::vector<std::pair<GLenum, GLuint>> &textureset);

	GLuint m_vbo;

	std::vector<GLenum> m_primtypes;

	std::vector<unsigned int> m_primsizes, m_arrayoffsets;

	std::vector<std::vector<std::pair<GLenum, GLuint>>> m_texturesets;
};

};

#endif
