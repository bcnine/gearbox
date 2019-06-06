#include "Utility.h"

#include <ctype.h>
#include <assert.h>
#include <fstream>
#ifndef WIN32
#include <unistd.h>
#endif

using namespace std;

namespace gbox
{

const string lowercase(const string &s)
{
    string t(s);
    for (string::size_type i = 0; i < t.length(); ++i)
        t[i] = tolower(t[i]);

    return t;
}

const string uppercase(const string &s)
{
    string t(s);
    for (string::size_type i = 0; i < t.length(); ++i)
        t[i] = toupper(t[i]);

    return t;
}

const string lstrip(const string &s)
{
    string::size_type i = 0;
    for (; i < s.length(); ++i)
        if (!isspace(s[i]))
            return string(s, i);

  return "";
}

const string rstrip(const string &s)
{
    int i = int(s.length()-1);
    for (; i >= 0; --i)
        if (!isspace(s[i]))
            return string(s, 0, i+1);

    return "";
}

const string strip(const string &s)
{
    return rstrip(lstrip(s));
}

void split(const string &s, list<string> &l, const string &d)
{
    string::size_type n, len(s.size()), begin(0), end(string::npos);
    while (!begin || begin < len)
    {
        end = s.find_first_of(d, begin);
        n = (end == string::npos) ? len-begin : end-begin;
        l.push_back(string(s, begin, n));
        begin += n+1;
    }
    if (end != string::npos)
        l.push_back(string());
}

unsigned int
sizeOf(GLuint gltype)
{
	switch (gltype)
	{
		case GL_UNSIGNED_BYTE:
		return sizeof(GLubyte);
		break;

		case GL_BYTE:
		return sizeof(GLbyte);
		break;

		case GL_UNSIGNED_SHORT:
		return sizeof(GLushort);
		break;

		case GL_SHORT:
		return sizeof(GLshort);
		break;

		case GL_UNSIGNED_INT:
		return sizeof(GLuint);
		break;

		case GL_INT:
		return sizeof(GLint);
		break;

		case GL_FLOAT:
		return sizeof(GLfloat);
		break;

		case GL_DOUBLE:
		return sizeof(GLdouble);
		break;

		default:
		assert(0);
		break;
	}

	return 0;
}

bool readFile(const string &path, string &data)
{
    if (!path.size())
        return false;

    string line;
    ifstream in(path.c_str());
    if (!in)
        return false;
    while(std::getline(in,line))
    {
        data += line;
        data += '\n';
    }

    if (!in.eof())
        return false;

    return true;
}

bool writeFile(const string &path, const string &data)
{
    FILE *fp = fopen(path.c_str(), "w");
    if (!fp)
        return false;

    size_t num = fwrite(data.c_str(), data.length(), 1, fp);
    if (fclose(fp) != 0)
        return false;

    return num == 1;
}

bool removeFile(const string &path)
{
#ifdef WIN32
    return (DeleteFile(std::string(path.begin(), path.end()).c_str()) == TRUE) ? true : false;
#else
    return (unlink(path.c_str()) == 0) ? true : false;
#endif
}

};
