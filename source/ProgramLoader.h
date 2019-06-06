#ifndef PROGRAMLOADER_H
#define PROGRAMLOADER_H

#include <map>
#include <string>
#include <stdint.h>

#include "GLBase.h"
#include "GLSLProgram.h"

namespace gbox
{

class ProgramLoader : GLBase
{
public:
	ProgramLoader (const uint64_t shaders);

	void           compile (const uint64_t shader, const std::string &source, std::string &log);
	GLSLProgramPtr link    (std::string &log);

	static const uint64_t VertexShader;
	static const uint64_t FragmentShader;
	static const uint64_t GeometryShader       = 0x4;
	static const uint64_t TessControlShader    = 0x8;
	static const uint64_t TessEvaluationShader = 0x10;
	static const uint64_t ComputeShader        = 0x20;

private:
	GLuint glShaderType (const uint64_t shader);

	std::string getLog (GLuint object, bool program);

	std::string getAnnotatedSource (const std::string &code);

	uint64_t m_todo, m_shaders;

	std::map<uint64_t, GLuint> m_shaderids;

    static const std::string LogSeparator;
};

};

#endif
