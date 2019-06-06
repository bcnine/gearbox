#ifndef ELEMENT_DRAWABLE_H
#define ELEMENT_DRAWABLE_H

#include "Drawable.h"

namespace gbox
{

class ElementDrawable : public Drawable
{

friend class DrawableLoader;

public:
	ElementDrawable ();
	ElementDrawable (GLuint vao, GLuint vbo, GLuint ibo, GLenum elemtype);

    virtual void draw   ();
	virtual void render ();

private:

    void addPrimitive(GLenum primtype,
                      unsigned int elemcount,
                      unsigned int elemoffset,
                      unsigned int vertoffset,
                      const std::vector<std::pair<GLenum, GLuint>> &textureset);

	GLuint m_vbo, m_ibo;

	GLenum m_elemtype;

	std::vector<GLenum> m_primtypes;

	std::vector<unsigned int> m_elemcounts;
	std::vector<unsigned int> m_elemoffsets;
	std::vector<unsigned int> m_vertoffsets;

	std::vector<std::vector<std::pair<GLenum, GLuint>>> m_texturesets;
};

};

#endif
