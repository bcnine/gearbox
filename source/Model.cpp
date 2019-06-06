#include "Model.h"

namespace gbox
{

Model::Model(const VertexLayout &vlayout) :
m_vlayout(vlayout)
{
	assert(vlayout.attributeCount());
	m_attributes.resize(vlayout.attributeCount());
}

unsigned int
Model::newPrimitive(GLenum primtype, unsigned int vertcount, int mtl)
{
	unsigned int primidx = m_primtypes.size();

	m_primtypes.push_back(primtype);
	m_primvertoffsets.push_back(vertexCount());
	m_primmaterials.push_back(mtl);

	for (unsigned int i = 0 ; i < m_vlayout.attributeCount(); ++i)
        m_attributes[i].resize(m_attributes[i].size() + m_vlayout.elementCount(i)*vertcount);

	m_primverts.push_back(vertcount);

	return primidx;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x)
{
	setAttribute(prim, vertex, attrib, (GLuint) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x)
{
	setAttribute(prim, vertex, attrib, (GLuint) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z, GLbyte w)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x)
{
	setAttribute(prim, vertex, attrib, (GLuint) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z, GLushort w)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x)
{
	setAttribute(prim, vertex, attrib, (GLuint) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z, GLshort w)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_ulong = x;
	m_attributes[attrib][i] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_ulong = x;
	m_attributes[attrib][i] = a;
	a.u_ulong = y;
	m_attributes[attrib][i+1] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_ulong = x;
	m_attributes[attrib][i] = a;
	a.u_ulong = y;
	m_attributes[attrib][i+1] = a;
	a.u_ulong = z;
	m_attributes[attrib][i+2] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z, GLuint w)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert((attrib < m_vlayout.attributeCount()) && (m_vlayout.elementCount(attrib) == 4));
	Attribute a;
	a.u_ulong = x;
	m_attributes[attrib][i] = a;
	a.u_ulong = y;
	m_attributes[attrib][i+1] = a;
	a.u_ulong = z;
	m_attributes[attrib][i+2] = a;
	a.u_ulong = w;
	m_attributes[attrib][i+3] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x)
{
	setAttribute(prim, vertex, attrib, (GLuint) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z, GLint w)
{
	setAttribute(prim, vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x)
{
	setAttribute(prim, vertex, attrib, (GLdouble) x);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y)
{
	setAttribute(prim, vertex, attrib, (GLdouble) x, (GLdouble) y);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z)
{
	setAttribute(prim, vertex, attrib, (GLdouble) x, (GLdouble) y, (GLdouble) z);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	setAttribute(prim, vertex, attrib, (GLdouble) x, (GLdouble) y, (GLdouble) z, (GLdouble) w);
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_double = x;
	m_attributes[attrib][i] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_double = x;
	m_attributes[attrib][i] = a;
	a.u_double = y;
	m_attributes[attrib][i+1] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_double = x;
	m_attributes[attrib][i] = a;
	a.u_double = y;
	m_attributes[attrib][i+1] = a;
	a.u_double = z;
	m_attributes[attrib][i+2] = a;
}

void
Model::setAttribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	assert(prim < m_primvertoffsets.size());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	Attribute a;
	a.u_double = x;
	m_attributes[attrib][i] = a;
	a.u_double = y;
	m_attributes[attrib][i+1] = a;
	a.u_double = z;
	m_attributes[attrib][i+2] = a;
	a.u_double = w;
	m_attributes[attrib][i+3] = a;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x) const
{
	GLuint _x;
	attribute(prim, vertex, attrib, _x);
	x = _x;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y) const
{
	GLuint _x, _y;
	attribute(prim, vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z) const
{
	GLuint _x, _y, _z;
	attribute(prim, vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z, GLubyte &w) const
{
	GLuint _x, _y, _z, _w;
	attribute(prim, vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x) const
{
	GLuint _x;
	attribute(prim, vertex, attrib, _x);
	x = _x;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y) const
{
	GLuint _x, _y;
	attribute(prim, vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z) const
{
	GLuint _x, _y, _z;
	attribute(prim, vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z, GLbyte &w) const
{
	GLuint _x, _y, _z, _w;
	attribute(prim, vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x) const
{
	GLuint _x;
	attribute(prim, vertex, attrib, _x);
	x = _x;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y) const
{
	GLuint _x, _y;
	attribute(prim, vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z) const
{
	GLuint _x, _y, _z;
	attribute(prim, vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z, GLushort &w) const
{
	GLuint _x, _y, _z, _w;
	attribute(prim, vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x) const
{
	GLuint _x;
	attribute(prim, vertex, attrib, _x);
	x = _x;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y) const
{
	GLuint _x, _y;
	attribute(prim, vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z) const
{
	GLuint _x, _y, _z;
	attribute(prim, vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z, GLshort &w) const
{
	GLuint _x, _y, _z, _w;
	attribute(prim, vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 1);
	assert(i < m_attributes[attrib].size());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_ulong;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 2);
	assert(i < m_attributes[attrib].size()-1);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 3);
	assert(i < m_attributes[attrib].size()-2);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
	z = (a+2)->u_ulong;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z, GLuint &w) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems == 4);
	assert(i < m_attributes[attrib].size()-3);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
	z = (a+2)->u_ulong;
	w = (a+3)->u_ulong;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x) const
{
	attribute(prim, vertex, attrib, (GLuint &) x);
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y) const
{
	attribute(prim, vertex, attrib, (GLuint &) x, (GLuint &) y);
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z) const
{
	attribute(prim, vertex, attrib, (GLuint &) x, (GLuint &) y, (GLuint &) z);
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z, GLint &w) const
{
	attribute(prim, vertex, attrib, (GLuint &) x, (GLuint &) y, (GLuint &) z, (GLuint &) w);
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x) const
{
	GLdouble _x;
	attribute(prim, vertex, attrib, _x);
	x = (GLfloat) _x;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y) const
{
	GLdouble _x, _y;
	attribute(prim, vertex, attrib, _x, _y);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z) const
{
	GLdouble _x, _y, _z;
	attribute(prim, vertex, attrib, _x, _y, _z);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
	z = (GLfloat) _z;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w) const
{
	GLdouble _x, _y, _z, _w;
	attribute(prim, vertex, attrib, _x, _y, _z, _w);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
	z = (GLfloat) _z;
	w = (GLfloat) _w;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 1);
	assert(i < m_attributes[attrib].size());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_double;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 2);
	assert(i < m_attributes[attrib].size()-1);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_double;
	y = (a+1)->u_double;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems >= 3);
	assert(i < m_attributes[attrib].size()-2);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_double;
	y = (a+1)->u_double;
	z = (a+2)->u_double;
}

void
Model::attribute(unsigned int prim, unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z, GLdouble &w) const
{
	assert(prim < m_primvertoffsets.size());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	unsigned int i = numelems*(m_primvertoffsets[prim]+vertex);

	assert(numelems == 4);
	assert(i < m_attributes[attrib].size()-3);
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][i];
	x = a->u_double;
	y = (a+1)->u_double;
	z = (a+2)->u_double;
	w = (a+3)->u_double;
}

unsigned int
Model::vertexCount() const
{
	return m_attributes[0].size() / m_vlayout.elementCount(0);
}

VertexLayout
Model::vertexLayout() const
{
	return m_vlayout;
}

unsigned int
Model::primitiveCount() const
{
	return m_primtypes.size();
}

GLenum
Model::primitiveType(unsigned int i) const
{
	assert(i < m_primtypes.size());
	return m_primtypes[i];
}

unsigned int
Model::primitiveVertexCount(unsigned int i) const
{
	assert(i < m_primverts.size());
	return m_primverts[i];
}

unsigned int
Model::primitiveVertexOffset(unsigned int i) const
{
	assert(i < m_primvertoffsets.size());
	return m_primvertoffsets[i];
}

int
Model::primitiveMaterial(unsigned int i) const
{
	assert(i < m_primmaterials.size());
	return m_primmaterials[i];
}

void
Model::addMaterial(const Material &material)
{
	m_materials.push_back(material);
}

Material
Model::material(unsigned int i) const
{
	assert(i < m_materials.size());
	return m_materials[i];
}

unsigned int
Model::materialCount() const
{
	return m_materials.size();
}

unsigned int
Model::primitiveTriCount(unsigned int i) const
{
	if (m_primtypes[i] == GL_TRIANGLES)
		return primitiveVertexCount(i) / 3;

	// Other primitive types (triangle strips/fans/etc) have different formulas.
	assert(0); // for now...
	return 0;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLubyte x)
{
	setDirectAttribute(vertex, attrib, (GLuint) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLbyte x)
{
	setDirectAttribute(vertex, attrib, (GLuint) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLbyte x, GLbyte y, GLbyte z, GLbyte w)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLushort x)
{
	setDirectAttribute(vertex, attrib, (GLuint) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLushort x, GLushort y)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLushort x, GLushort y, GLushort z, GLushort w)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLshort x)
{
	setDirectAttribute(vertex, attrib, (GLuint) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLshort x, GLshort y)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLshort x, GLshort y, GLshort z, GLshort w)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLuint x)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 1);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_ulong     = x;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLuint x, GLuint y)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 2);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_ulong     = x;
	(a+1)->u_ulong = y;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 3);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_ulong     = x;
	(a+1)->u_ulong = y;
	(a+2)->u_ulong = z;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLuint x, GLuint y, GLuint z, GLuint w)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems == 4);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_ulong     = x;
	(a+1)->u_ulong = y;
	(a+2)->u_ulong = z;
	(a+3)->u_ulong = w;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLint x)
{
	setDirectAttribute(vertex, attrib, (GLuint) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLint x, GLint y)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLint x, GLint y, GLint z, GLint w)
{
	setDirectAttribute(vertex, attrib, (GLuint) x, (GLuint) y, (GLuint) z, (GLuint) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLfloat x)
{
	setDirectAttribute(vertex, attrib, (GLdouble) x);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y)
{
	setDirectAttribute(vertex, attrib, (GLdouble) x, (GLdouble) y);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z)
{
	setDirectAttribute(vertex, attrib, (GLdouble) x, (GLdouble) y, (GLdouble) z);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	setDirectAttribute(vertex, attrib, (GLdouble) x, (GLdouble) y, (GLdouble) z, (GLdouble) w);
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLdouble x)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 1);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_double     = x;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 2);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_double     = x;
	(a+1)->u_double = y;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems >= 3);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_double     = x;
	(a+1)->u_double = y;
	(a+2)->u_double = z;
}

void
Model::setDirectAttribute(unsigned int vertex, unsigned int attrib, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());
	unsigned int numelems = m_vlayout.elementCount(attrib);
	assert(numelems == 4);

	Attribute *a = &m_attributes[attrib][numelems*vertex];
	a->u_double     = x;
	(a+1)->u_double = y;
	(a+2)->u_double = z;
	(a+3)->u_double = w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLubyte &x) const
{
	GLuint _x;
	directAttribute(vertex, attrib, _x);
	x = _x;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y) const
{
	GLuint _x, _y;
	directAttribute(vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z) const
{
	GLuint _x, _y, _z;
	directAttribute(vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLubyte &x, GLubyte &y, GLubyte &z, GLubyte &w) const
{
	GLuint _x, _y, _z, _w;
	directAttribute(vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLbyte &x) const
{
	GLuint _x;
	directAttribute(vertex, attrib, _x);
	x = _x;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y) const
{
	GLuint _x, _y;
	directAttribute(vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z) const
{
	GLuint _x, _y, _z;
	directAttribute(vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLbyte &x, GLbyte &y, GLbyte &z, GLbyte &w) const
{
	GLuint _x, _y, _z, _w;
	directAttribute(vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLushort &x) const
{
	GLuint _x;
	directAttribute(vertex, attrib, _x);
	x = _x;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y) const
{
	GLuint _x, _y;
	directAttribute(vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z) const
{
	GLuint _x, _y, _z;
	directAttribute(vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLushort &x, GLushort &y, GLushort &z, GLushort &w) const
{
	GLuint _x, _y, _z, _w;
	directAttribute(vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLshort &x) const
{
	GLuint _x;
	directAttribute(vertex, attrib, _x);
	x = _x;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y) const
{
	GLuint _x, _y;
	directAttribute(vertex, attrib, _x, _y);
	x = _x;
	y = _y;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z) const
{
	GLuint _x, _y, _z;
	directAttribute(vertex, attrib, _x, _y, _z);
	x = _x;
	y = _y;
	z = _z;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLshort &x, GLshort &y, GLshort &z, GLshort &w) const
{
	GLuint _x, _y, _z, _w;
	directAttribute(vertex, attrib, _x, _y, _z, _w);
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLuint &x) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 1);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_ulong;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 2);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 3);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
	z = (a+2)->u_ulong;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLuint &x, GLuint &y, GLuint &z, GLuint &w) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems == 4);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_ulong;
	y = (a+1)->u_ulong;
	z = (a+2)->u_ulong;
	w = (a+3)->u_ulong;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLint &x) const
{
	directAttribute(vertex, attrib, (GLuint &) x);
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLint &x, GLint &y) const
{
	directAttribute(vertex, attrib, (GLuint &) x, (GLuint &) y);
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z) const
{
	directAttribute(vertex, attrib, (GLuint &) x, (GLuint &) y, (GLuint &) z);
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLint &x, GLint &y, GLint &z, GLint &w) const
{
	directAttribute(vertex, attrib, (GLuint &) x, (GLuint &) y, (GLuint &) z, (GLuint &) w);
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLfloat &x) const
{
	GLdouble _x;
	directAttribute(vertex, attrib, _x);
	x = (GLfloat) _x;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y) const
{
	GLdouble _x, _y;
	directAttribute(vertex, attrib, _x, _y);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z) const
{
	GLdouble _x, _y, _z;
	directAttribute(vertex, attrib, _x, _y, _z);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
	z = (GLfloat) _z;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &w) const
{
	GLdouble _x, _y, _z, _w;
	directAttribute(vertex, attrib, _x, _y, _z, _w);
	x = (GLfloat) _x;
	y = (GLfloat) _y;
	z = (GLfloat) _z;
	w = (GLfloat) _w;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLdouble &x) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 1);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_double;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 2);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_double;
	y = (a+1)->u_double;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems >= 3);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_double;
	y = (a+1)->u_double;
	z = (a+2)->u_double;
}

void
Model::directAttribute(unsigned int vertex, unsigned int attrib, GLdouble &x, GLdouble &y, GLdouble &z, GLdouble &w) const
{
	unsigned int numelems = m_vlayout.elementCount(attrib);

	assert(numelems == 4);
	assert(vertex < vertexCount());
	assert(attrib < m_vlayout.attributeCount());

	const Attribute *a = &m_attributes[attrib][numelems*vertex];
	x = a->u_double;
	y = (a+1)->u_double;
	z = (a+2)->u_double;
	w = (a+3)->u_double;
}

};
