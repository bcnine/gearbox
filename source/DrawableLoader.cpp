#include "DrawableLoader.h"

#include <iostream>
#include <limits.h>

#include "Utility.h"

#include <stdexcept>

#include "ElementModel.h"
#include "ElementDrawable.h"

#include "ArrayModel.h"
#include "ArrayDrawable.h"

#include "FreeImage.h"

using namespace std;

namespace gbox
{

DrawableLoader::DrawableLoader()
{
}

void
DrawableLoader::loadTexture(const string &file, GLuint &texobj, unsigned int texunit)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(file.c_str());

    FIBITMAP *dib = FreeImage_Load(fif, file.c_str(), 0);
    if (!dib)
      throw runtime_error("load failed");

    unsigned int pitch = FreeImage_GetPitch(dib);
    unsigned int bitspp = FreeImage_GetBPP(dib);

    unsigned int bytespp = bitspp / 8;
    if (bytespp < 1 || bytespp > 4)
    {
        FreeImage_Unload(dib);
		throw runtime_error("load failed");
    }

    unsigned int imgwidth  = FreeImage_GetWidth(dib);
    unsigned int imgheight = FreeImage_GetHeight(dib);
    BYTE *bytes = FreeImage_GetBits(dib);

	glGenTextures(1, &texobj);
	glActiveTexture(GL_TEXTURE0+texunit);
    glBindTexture(GL_TEXTURE_2D, texobj);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, imgwidth, imgheight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imgwidth, imgheight, GL_BGR, GL_UNSIGNED_BYTE, bytes);

	// TODO: How to set the sampler texture unit???
	//glProgramUniform1i(m_program, 0, 0);

    FreeImage_Unload(dib);
}

GLuint
DrawableLoader::createVBO(const VertexLayout &vlayout, const Model &model)
{
    GLuint vbo;
	glGenBuffers(1, &vbo);
	unsigned int numbytes = vlayout.size() * model.vertexCount();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numbytes, NULL, GL_STATIC_DRAW);

	void *p = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (unsigned int v = 0; v < model.vertexCount(); ++v)
	{
		for (unsigned int a = 0; a < vlayout.attributeCount(); ++a)
		{
			switch (vlayout.inType(a))
			{
				case GL_UNSIGNED_BYTE:
				{
					GLubyte x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_BYTE:
				{
					GLbyte x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_UNSIGNED_SHORT:
				{
					GLushort x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_SHORT:
				{
					GLshort x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_UNSIGNED_INT:
				{
					GLuint x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_INT:
				{
					GLint x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_FLOAT:
				{
					GLfloat x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				case GL_DOUBLE:
				{
					GLdouble x, y, z, w;
					switch (vlayout.elementCount(a))
					{
						case 1:
						model.directAttribute(v, a, x);
						p = writeBytes(p, x);
						break;

						case 2:
						model.directAttribute(v, a, x, y);
						p = writeBytes(p, x, y);
						break;

						case 3:
						model.directAttribute(v, a, x, y, z);
						p = writeBytes(p, x, y, z);
						break;

						case 4:
						model.directAttribute(v, a, x, y, z, w);
						p = writeBytes(p, x, y, z, w);
						break;

						default:
						assert(0);
						break;
					}
				}
				break;

				default:
				assert(0);
				break;
			}
		}
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);

	for (unsigned int i = 0; i < vlayout.attributeCount(); ++i)
	{
		glEnableVertexAttribArray(i);
		switch (vlayout.outType(i))
		{
			case GL_UNSIGNED_INT:
			case GL_INT:
			glVertexAttribIPointer(i, vlayout.elementCount(i),
			                       vlayout.inType(i),
								   vlayout.size(),
								   (const GLvoid *) vlayout.offset(i));
			break;

			case GL_FLOAT:
			glVertexAttribPointer(i, vlayout.elementCount(i),
			                      vlayout.inType(i),
								  vlayout.normalized(i),
								  vlayout.size(),
								  (const GLvoid *) vlayout.offset(i));
			break;

			case GL_DOUBLE:
			glVertexAttribLPointer(i, vlayout.elementCount(i),
			                       vlayout.inType(i),
								   vlayout.size(),
								   (const GLvoid *) vlayout.offset(i));
			break;
		}
	}

    return vbo;
}

void
DrawableLoader::loadTextureSets(const Model &model, vector<vector<pair<GLenum, GLuint>>> &texsets)
{
	texsets.resize(model.materialCount());
	for (unsigned int i = 0; i < model.materialCount(); ++i)
	{
		Material mat(model.material(i));
		for (unsigned int j = 0; j < mat.textureCount(); ++j)
		{
			GLuint texobj = 0;
			string file(mat.texture(j));
			loadTexture(file, texobj, j);
			texsets[i].push_back(make_pair(GL_TEXTURE_2D, texobj));
		}
	}
}

shared_ptr<ElementDrawable>
DrawableLoader::createElementDrawable(const ElementModel &model)
{
	vector<vector<pair<GLenum, GLuint>>> texsets;
    loadTextureSets(model, texsets);

	// Currently this function builds a single interleaved VBO. It could be modified to
	// take an interleaved flag or something, which would also require modifying
	// ElementDrawable, perhaps by having it store a vector of VBOs instead of just a
	// single one...

	VertexLayout vlayout(model.vertexLayout());

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo = createVBO(vlayout, model);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	unsigned int vertexcount = model.vertexCount();

	GLenum elemtype = 0;
	unsigned int elemcount = model.elementCount();
	if (vertexcount <= UCHAR_MAX+1)
	{
		elemtype = GL_UNSIGNED_BYTE;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*elemcount, NULL, GL_STATIC_DRAW);
		void *p = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (unsigned int i = 0; i < elemcount; ++i)
		{
            GLubyte elem = model.directElement(i);
			p = writeBytes(p, elem);
		}
	}
	else if (vertexcount <= USHRT_MAX+1)
	{
		elemtype = GL_UNSIGNED_SHORT;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*elemcount, NULL, GL_STATIC_DRAW);
		void *p = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (unsigned int i = 0; i < elemcount; ++i)
		{
            GLushort elem = model.directElement(i);
			p = writeBytes(p, elem);
		}
	}
	else
	{
		elemtype = GL_UNSIGNED_INT;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*elemcount, NULL, GL_STATIC_DRAW);
		void *p = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (unsigned int i = 0; i < elemcount; ++i)
		{
            GLuint elem = model.directElement(i);
			p = writeBytes(p, elem);
		}
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindVertexArray(0);

	vector<pair<GLenum, GLuint>> empty;

    auto drawable(std::make_shared<ElementDrawable>(vao, vbo, ibo, elemtype));

	for (unsigned int i = 0; i < model.primitiveCount(); ++i)
	{
		GLenum ptype = model.primitiveType(i);
		unsigned int elemoffset = sizeOf(elemtype) * model.primitiveElementOffset(i);
		unsigned int vertoffset = model.primitiveVertexOffset(i);
		unsigned int elemcount = model.primitiveElementCount(i);
		unsigned int mtlidx = model.primitiveMaterial(i);

        drawable->addPrimitive(ptype, elemcount, elemoffset, vertoffset, (mtlidx == -1) ? empty : texsets[mtlidx]);
	}

	return drawable;
}

shared_ptr<ArrayDrawable>
DrawableLoader::createArrayDrawable(const ArrayModel &model)
{
	vector<vector<pair<GLenum, GLuint>>> texsets;
    loadTextureSets(model, texsets);

    // See notes in createElementDrawable re: interleaved VBO.

	VertexLayout vlayout(model.vertexLayout());

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo = createVBO(vlayout, model);

	glBindVertexArray(0);

	vector<pair<GLenum, GLuint>> empty;

    auto drawable(std::make_shared<ArrayDrawable>(vao, vbo));

	for (unsigned int i = 0; i < model.primitiveCount(); ++i)
	{
		GLenum ptype = model.primitiveType(i);
		unsigned int vertexcount = model.primitiveVertexCount(i);
		unsigned int vertoffset = model.primitiveVertexOffset(i);
		unsigned int mtlidx = model.primitiveMaterial(i);

        drawable->addPrimitive(ptype, vertexcount, vertoffset, (mtlidx == -1) ? empty : texsets[mtlidx]);
	}

	return drawable;
}

};
