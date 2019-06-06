#ifndef ARRAY_MODEL_H
#define ARRAY_MODEL_H

#include <vector>

#include "Model.h"

namespace gbox
{

class ArrayModel : public Model
{
public:
	ArrayModel (const VertexLayout &vlayout);

    unsigned int addPrimitive (GLenum primtype, unsigned int vertcount, int mtl);

	// Iterate using primitiveCount() in Model.
	virtual unsigned int primitiveTriCount (unsigned int prim) const;
};

};

#endif
