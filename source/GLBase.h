#ifndef GL_BASE_H
#define GL_BASE_H

#include "glcorearb.h"
#include <QOpenGLFunctions_4_2_Core.h>

namespace gbox
{

typedef QOpenGLFunctions_4_2_Core GLVersion;

class GLBase : public GLVersion
{
public:
	GLBase (bool initialize = true);
};

};

#endif
