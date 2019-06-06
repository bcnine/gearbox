#include "ArrayModel.h"

namespace gbox
{

ArrayModel::ArrayModel(const VertexLayout &vlayout) :
Model(vlayout)
{
}

unsigned int
ArrayModel::addPrimitive(GLenum primtype, unsigned int vertcount, int mtl)
{
	return Model::newPrimitive(primtype, vertcount, mtl);
}

unsigned int
ArrayModel::primitiveTriCount(unsigned int prim) const
{
	if (m_primtypes[prim] == GL_TRIANGLES)
        return primitiveVertexCount(prim) / 3;

	// Other primitive types (triangle strips/fans/etc) have different formulas.
	assert(0); // for now...
	return 0;
}

};
