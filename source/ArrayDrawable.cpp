#include "ArrayDrawable.h"

#include "Vector.h"

#include <iostream>

using namespace std;

namespace gbox
{

ArrayDrawable::ArrayDrawable() :
Drawable()
{
}

ArrayDrawable::ArrayDrawable(GLuint vao, GLuint vbo) :
Drawable(vao, vbo)
{
}

void
ArrayDrawable::addPrimitive(GLenum primtype,
                            unsigned int numindices,
                            unsigned int arrayoffset,
                            const std::vector<std::pair<GLenum, GLuint>> &textureset)
{
    m_primtypes.push_back(primtype);
    m_primsizes.push_back(numindices);
    m_arrayoffsets.push_back(arrayoffset);
    m_texturesets.push_back(textureset);
}

void
ArrayDrawable::draw()
{
	glBindVertexArray(m_vao);
    unsigned int numprimitives = m_primtypes.size();
	for (unsigned int i = 0; i < numprimitives; ++i)
		glDrawArrays(m_primtypes[i], m_arrayoffsets[i], m_primsizes[i]);
}

void
ArrayDrawable::render()
{
	glBindVertexArray(m_vao);
    unsigned int numprimitives = m_primtypes.size();
	for (unsigned int i = 0; i < numprimitives; ++i)
	{
        unsigned int numtextures = m_texturesets[i].size();
		for (unsigned int j = 0; j < numtextures; ++j)
		{
			glActiveTexture(GL_TEXTURE0+j);
			glBindTexture(m_texturesets[i][j].first, m_texturesets[i][j].second);
		}
		glDrawArrays(m_primtypes[i], m_arrayoffsets[i], m_primsizes[i]);
	}
}

};
