#include "ProgramLoader.h"

#include <string>
#include <assert.h>

#include "Utility.h"
#include <stdexcept>
#include <sstream>

using namespace std;

namespace gbox
{

const string ProgramLoader::LogSeparator("-----\n\n");

const uint64_t ProgramLoader::VertexShader = 0x1;
const uint64_t ProgramLoader::FragmentShader = 0x2;

ProgramLoader::ProgramLoader(const uint64_t shaders) :
m_todo(shaders),
m_shaders(shaders)
{
    assert(shaders & VertexShader);
}

GLuint
ProgramLoader::glShaderType(const uint64_t shader)
{
	switch (shader)
	{
		case VertexShader:
		return GL_VERTEX_SHADER;
		break;

		case FragmentShader:
		return GL_FRAGMENT_SHADER;
		break;

		case GeometryShader:
		return GL_GEOMETRY_SHADER;
		break;

		case TessControlShader:
		return GL_TESS_CONTROL_SHADER;
		break;

		case TessEvaluationShader:
		return GL_TESS_EVALUATION_SHADER;
		break;

		case ComputeShader:
		return GL_COMPUTE_SHADER;
		break;

		default:
		assert(0);
		break;
	}

	return 0;
}

void
ProgramLoader::compile(const uint64_t shader, const std::string &source, std::string &log)
{
	// Because the caller can use the size of the log to detect warnings, it's important
	// to always clear it.
	log.clear();

	if (!(shader & m_todo))
	{
		log = "error: shader is not scheduled for compilation.";
		throw runtime_error("compile failed");
	}

	assert(m_shaderids.find(shader) == m_shaderids.end());
    m_shaderids[shader] = glCreateShader(glShaderType(shader));
    const GLchar *str = source.c_str();
    glShaderSource(m_shaderids[shader], 1, &str, NULL);
    glCompileShader(m_shaderids[shader]);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    string message(getLog(shader, false));

	if (!compiled || message.size())
        log = (getAnnotatedSource(source) + LogSeparator + message);

	if (!compiled)
	{
		glDeleteShader(m_shaderids[shader]);
		m_shaderids.erase(shader);
		throw runtime_error("compile failed");
	}

	m_todo &= ~shader;
}

GLSLProgramPtr
ProgramLoader::link(std::string &log)
{
	log.clear();

	if (m_todo)
	{
		log = "error: not all shaders have been compiled.";
		throw runtime_error("link failed");
	}

    GLuint program = glCreateProgram();

	assert(m_shaderids.find(VertexShader) != m_shaderids.end());
    glAttachShader(program, m_shaderids[VertexShader]);

	// Insert more shader types here as needed...

	if (m_shaders & FragmentShader)
	{
		assert(m_shaderids.find(FragmentShader) != m_shaderids.end());
		glAttachShader(program, m_shaderids[FragmentShader]);
	}

	glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    string message(getLog(program, true));

	if (!linked || message.size())
        log = message;

	if (!linked)
	{
		glDeleteProgram(program);
		throw runtime_error("link failed");
	}

	GLint activecount = 0;
	map<string, GLint> locations;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activecount);
    const GLint maxlen = 255;
	GLchar name[maxlen+1];
	for (GLint i = 0; i < activecount; ++i)
	{
        GLint size;
        GLenum type;
        GLsizei len;
        glGetActiveUniform(program, i, maxlen, &len, &size, &type, name);
        if (len > 3 && name[0] == 'g' && name[1] == 'l' && name[2] == '_')
            continue;
        if (size == 1)
        {
            GLint location = glGetUniformLocation(program, name);
			locations[name] = location;
        }
        else
        {
            for (int j = 0; j < size; ++j)
            {
				ostringstream s;
				s << name;
				s << "[" << j << "]";
                GLint location = glGetUniformLocation(program, s.str().c_str());
				locations[name] = location;
            }
        }
	}

	return make_shared<GLSLProgram>(program, locations);
}

string
ProgramLoader::getLog(GLuint object, bool program)
{
    GLint written = 0, loglen = 0;
    string logdata;
    if (program)
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &loglen);
    else
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &loglen);

    if (loglen > 0)
    {
        char *logbytes = (char *) malloc(loglen);
        if (program)
            glGetProgramInfoLog(object, loglen, &written, logbytes);
        else
            glGetShaderInfoLog(object, loglen, &written, logbytes);
        if (strlen(logbytes) > 0)
            logdata += logbytes;
        free(logbytes);
    }

    return logdata;
}

string
ProgramLoader::getAnnotatedSource(const string &code)
{
    list<string> lines;
    split(code, lines, "\n");

    char buf[7];
    string codelines;
    list<string>::iterator iter(lines.begin());
    for (int lnum=1; iter != lines.end(); ++iter, ++lnum)
    {
        lnum = (lnum > 9999) ? 9999 : lnum;
        sprintf(buf, "%4d: ", lnum);
        codelines += buf;
        codelines += *iter;
        codelines += '\n';
    }

    return codelines;
}

};
