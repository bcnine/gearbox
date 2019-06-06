#ifndef TBN_H
#define TBN_H

#include "ElementModel.h"

namespace gbox
{

extern void generateTangentVectors (ElementModel &model,
                                    unsigned int positionidx,
                                    unsigned int normalidx,
                                    unsigned int textureidx,
                                    unsigned int tangentidx);

};

#endif
