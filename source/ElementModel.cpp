#include "ElementModel.h"

namespace gbox
{

ElementModel::ElementModel(const VertexLayout &vlayout) :
Model(vlayout)
{
}

unsigned int
ElementModel::addPrimitive(GLenum primtype, unsigned int vertcount, unsigned int elemcount, int mtl)
{
	unsigned int primidx = Model::newPrimitive(primtype, vertcount, mtl);
	m_primelemoffsets.push_back(elementCount());
	m_primelems.push_back(elemcount);

	m_elements.resize(m_elements.size() + elemcount);

	return primidx;
}

unsigned int
ElementModel::directElement(unsigned int elem) const
{
	assert(elem < m_elements.size());

	return m_elements[elem];
}

void
ElementModel::setDirectElement(unsigned int elem, unsigned int i)
{
	assert(elem < m_elements.size());

	m_elements[elem] = i;
}

void
ElementModel::setElement(unsigned int prim, unsigned int elem, unsigned int i)
{
	assert(prim < m_primelemoffsets.size());
	m_elements[m_primelemoffsets[prim] + elem] = i;
}

unsigned int
ElementModel::element(unsigned int prim, unsigned int elem) const
{
	assert(prim < m_primelemoffsets.size());
	unsigned int i = m_primelemoffsets[prim]+elem;

	return m_elements[i];
}

unsigned int
ElementModel::elementCount() const
{
	return m_elements.size();
}

unsigned int
ElementModel::primitiveElementCount(unsigned int prim) const
{
	assert(prim < m_primelems.size());
	return m_primelems[prim];
}

unsigned int
ElementModel::primitiveElementOffset(unsigned int prim) const
{
	assert(prim < m_primelemoffsets.size());
	return m_primelemoffsets[prim];
}

unsigned int
ElementModel::primitiveTriCount(unsigned int prim) const
{
	if (m_primtypes[prim] == GL_TRIANGLES)
        return primitiveElementCount(prim) / 3;

	// Other primitive types (triangle strips/fans/etc) have different formulas.
	assert(0); // for now...
	return 0;
}

void
ElementModel::primitiveTriElements(unsigned int prim, unsigned int tri,
                                   unsigned int &i0, unsigned int &i1, unsigned int &i2) const
{
	i0 = m_elements[m_primelemoffsets[prim] + 3*tri    ];
	i1 = m_elements[m_primelemoffsets[prim] + 3*tri + 1];
	i2 = m_elements[m_primelemoffsets[prim] + 3*tri + 2];
}

};
