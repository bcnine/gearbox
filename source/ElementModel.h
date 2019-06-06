#ifndef ELEMENT_MODEL_H
#define ELEMENT_MODEL_H

#include <vector>

#include "Model.h"

namespace gbox
{

class ElementModel : public Model
{
public:
	ElementModel (const VertexLayout &vlayout);

    unsigned int addPrimitive (GLenum primtype, unsigned int vertcount, unsigned int elemcount, int mtl);

	// These methods are 0-based relative to the call to addPrimitive().
	void         setElement (unsigned int prim, unsigned int elem, unsigned int i);
	unsigned int element    (unsigned int prim, unsigned int elem) const;

	// These are for accessing the element block of the model as a whole
	// (see Model.h for more details, naming justification, etc.)
	void         setDirectElement (unsigned int elem, unsigned int i);
	unsigned int directElement    (unsigned int elem) const;

	unsigned int elementCount () const;

	// Iterate using primitiveCount() in Model.
	unsigned int         primitiveElementCount  (unsigned int prim) const;
	unsigned int         primitiveElementOffset (unsigned int prim) const;
	virtual unsigned int primitiveTriCount      (unsigned int prim) const;
	void                 primitiveTriElements   (unsigned int prim, unsigned int tri,
	                                             unsigned int &i0, unsigned int &i1, unsigned int &i2) const;

private:
	std::vector<unsigned int> m_elements;

	std::vector<unsigned int> m_primelems;
	std::vector<unsigned int> m_primelemoffsets;
};

};

#endif
