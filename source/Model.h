#ifndef MODEL_H
#define MODEL_H

#include <assert.h>
#include <vector>

#include "Material.h"
#include "VertexLayout.h"

namespace gbox
{

class Model
{
public:
	// There will be a model loader somewhere, implemented with Assimp or similar, that, when given
	// a file, will figure out an appropriate vertex layout. Then, it will instantiate an instance
	// of this class, passing in the vertex layout, and proceed to fill the model out. This is a
	// nice interface because one could also procedurally define a model by using this class directly.
	Model (const VertexLayout &vlayout);

	// Matrices as vertex attributes are not supported. To store e.g. 4x4 matrices, use 4 attributes of size 4 each instead.

	void addMaterial (const Material &material);

	// vertex is 0-based from the point at which addPrimitive() is called.
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z, GLbyte w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z, GLushort w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z, GLshort w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z, GLuint w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z, GLint w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z);
	void setAttribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

	// These get methods are per-primitive, where vertex is 0-based for each primitive.
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z, GLubyte &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z, GLbyte &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z, GLushort &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z, GLshort &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z, GLuint &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z, GLint &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w) const;

	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z) const;
	void attribute (unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z, GLdouble &w) const;

	// These get methods are for the entire vertex block defined by the model, and are
	// therefore *not* 0-based for each primitive. These are primarily used by routines
	// wanting to process all vertices together, regardless of connectivity information
	// (e.g. code that builds a VBO from this data). They are so-named because there
	// is no layer of indirection (i.e. a primitive offset) present here. 'vertex' indexes
	// directly into the vertex attribute vector for the entire model.
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLubyte x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLbyte x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z, GLbyte w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLushort x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLushort x, GLushort y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z, GLushort w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLshort x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLshort x, GLshort y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z, GLshort w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLuint x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLuint x, GLuint y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z, GLuint w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLint x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLint x, GLint y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z, GLint w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLfloat x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLdouble x);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z);
	void setDirectAttribute (unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z, GLdouble w);

	void directAttribute (unsigned int vertex, unsigned int attrib, GLubyte &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z, GLubyte &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLbyte &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z, GLbyte &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLushort &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z, GLushort &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLshort &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z, GLshort &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLuint &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z, GLuint &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLint &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLint &x, GLint &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z, GLint &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLfloat &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w) const;

	void directAttribute (unsigned int vertex, unsigned int attrib, GLdouble &x) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z) const;
	void directAttribute (unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z, GLdouble &w) const;

	unsigned int vertexCount  () const;

	VertexLayout vertexLayout () const;

	unsigned int primitiveCount () const;

	GLenum               primitiveType         (unsigned int i) const;
	unsigned int         primitiveVertexCount  (unsigned int i) const;
	unsigned int         primitiveVertexOffset (unsigned int i) const;
	int                  primitiveMaterial     (unsigned int i) const;
	virtual unsigned int primitiveTriCount     (unsigned int i) const;

	Material material (unsigned int i) const;

	unsigned int materialCount () const;

	virtual ~Model () {}

protected:

    unsigned int newPrimitive (GLenum primtype, unsigned int vertcount, int mtl);

	VertexLayout m_vlayout;

	union Attribute
	{
		double u_double;
		unsigned long u_ulong;
	};

	std::vector<std::vector<Attribute> > m_attributes;

	std::vector<GLenum> m_primtypes;
	std::vector<unsigned int> m_primverts;
	std::vector<unsigned int> m_primvertoffsets;
	std::vector<int> m_primmaterials;

	std::vector<Material> m_materials;

	GLenum m_mode;
};

};

#endif
