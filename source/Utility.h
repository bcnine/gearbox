#ifndef UTILITY_H
#define UTILITY_H

#include <list>
#include <string>

#include "glcorearb.h"

namespace gbox
{

const std::string lowercase (const std::string &s);
const std::string uppercase (const std::string &s);
const std::string lstrip    (const std::string &s);
const std::string rstrip    (const std::string &s);
const std::string strip     (const std::string &s);

/// split() fills l with substrings in s that exist between delimiters d.
/// Note that it does not discard empty strings, so for example if
/// s = ':::', and d = ':', split() fills l with four empty strings.
/// It does this because that information may be valuable in some context,
/// and it is easy to ignore in those contexts in which it's not.
void split (const std::string &s, std::list<std::string> &l, const std::string &d=" ");

unsigned int sizeOf(GLuint gltype);

bool readFile   (const std::string &path, std::string &data);
bool writeFile  (const std::string &path, const std::string &data);
bool removeFile (const std::string &path);

};

#endif
