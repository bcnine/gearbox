#include "ElementDrawable.h"

#include "Vector.h"

#include <iostream>

using namespace std;

namespace gbox
{

ElementDrawable::ElementDrawable() :
Drawable(),
m_ibo(0),
m_elemtype(0)
{
}

ElementDrawable::ElementDrawable(GLuint vao, GLuint vbo, GLuint ibo, GLenum elemtype) :
Drawable(vao, vbo),
m_ibo(ibo),
m_elemtype(elemtype)
{
}

void
ElementDrawable::addPrimitive(GLenum primtype,
                              unsigned int elemcount,
                              unsigned int elemoffset,
                              unsigned int vertoffset,
                              const std::vector<std::pair<GLenum, GLuint>> &textureset)
{
    m_primtypes.push_back(primtype);
    m_elemcounts.push_back(elemcount);
    m_elemoffsets.push_back(elemoffset);
    m_vertoffsets.push_back(vertoffset);
    m_texturesets.push_back(textureset);
}

void
ElementDrawable::draw()
{
	glBindVertexArray(m_vao);
    unsigned int numprimitives = m_primtypes.size();
	for (unsigned int i = 0; i < numprimitives; ++i)
		glDrawElementsBaseVertex(m_primtypes[i], m_elemcounts[i], m_elemtype, (const GLvoid *) m_elemoffsets[i], m_vertoffsets[i]);
}

void
ElementDrawable::render()
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
		glDrawElementsBaseVertex(m_primtypes[i], m_elemcounts[i], m_elemtype, (const GLvoid *) m_elemoffsets[i], m_vertoffsets[i]);
	}
}

};
