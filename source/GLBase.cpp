#include "GLBase.h"

namespace gbox
{

GLBase::GLBase(bool initialize)
{
	if (initialize)
		initializeOpenGLFunctions();
}

};
