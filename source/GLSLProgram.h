#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <map>
#include <string>
#include <memory>

#include "GLBase.h"
#include "Matrix.h"
#include "Vector.h"

namespace gbox
{

class GLSLProgram : public GLBase
{
public:
	GLSLProgram (GLuint program, const std::map<std::string, GLint> &locations);

	GLuint id () const;

	void setUniformf (const std::string &name, const Mat3d &m);
	void setUniformf (const std::string &name, const Mat4d &m);

	void setUniform (const std::string &name, const Vec3f &v);
	void setUniform (const std::string &name, float f);
	void setUniform (const std::string &name, int i);

private:
	GLuint m_id;

	const std::map<std::string, GLint> m_locations;
};

typedef std::shared_ptr<GLSLProgram> GLSLProgramPtr;

};

#endif
