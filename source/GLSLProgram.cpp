#include "GLSLProgram.h"

using namespace std;

namespace gbox
{

GLSLProgram::GLSLProgram(GLuint program, const std::map<std::string, GLint> &locations) :
m_id(program),
m_locations(locations)
{
}

GLuint
GLSLProgram::id() const
{
	return m_id;
}

void
GLSLProgram::setUniformf(const string &name, const Mat4d &m)
{
	static float fm[16];
	const double *p = m.ptr();
	for (unsigned int i = 0; i < 16; ++i)
		fm[i] = *p++;
	map<string, GLint>::const_iterator iter(m_locations.find(name));
	if (iter != m_locations.end())
		glUniformMatrix4fv((*iter).second, 1, GL_FALSE, fm);
}

void
GLSLProgram::setUniformf(const string &name, const Mat3d &m)
{
	static float fm[9];
	const double *p = m.ptr();
	for (unsigned int i = 0; i < 9; ++i)
		fm[i] = *p++;
	map<string, GLint>::const_iterator iter(m_locations.find(name));
	if (iter != m_locations.end())
		glUniformMatrix3fv((*iter).second, 1, GL_FALSE, fm);
}

void
GLSLProgram::setUniform(const string &name, const Vec3f &v)
{
	GLint location = 0;
	map<string, GLint>::const_iterator iter(m_locations.find(name));
	if (iter != m_locations.end())
		glUniform3fv((*iter).second, 1, v.ptr());
}

void
GLSLProgram::setUniform(const string &name, float f)
{
	GLint location = 0;
	map<string, GLint>::const_iterator iter(m_locations.find(name));
	if (iter != m_locations.end())
		glUniform1f((*iter).second, f);
}

void
GLSLProgram::setUniform(const string &name, int i)
{
	GLint location = 0;
	map<string, GLint>::const_iterator iter(m_locations.find(name));
	if (iter != m_locations.end())
		glUniform1i((*iter).second, i);
}

};
