#include "VertexLayout.h"
#include "Utility.h"

#include <list>
#include <string>
#include <stdexcept>

using namespace std;

namespace gbox
{

VertexLayout::VertexLayout(const std::string &format) :
m_vertexsize(0)
{
    string clean;
    string::size_type fmtlen = format.length();
    for (string::size_type i = 0; i < fmtlen; ++i)
        if (!isspace(format[i]))
            clean += format[i];

    list<string> entries;
    split(clean, entries, ",");
    list<string>::const_iterator iter(entries.begin());
    for (; iter != entries.end(); ++iter)
    {
        const string &entry(*iter);
        string::size_type colon = entry.find_first_of(":");
        if (colon == string::npos)
			throw runtime_error("parse failed");
        string name(entry, 0, colon);
        string suffix(entry, colon+1);

        string::size_type suflen = suffix.length();
        if (name.empty() || suflen < 2)
			throw runtime_error("parse failed");
        const char *p = suffix.c_str();
        // We're done parsing the name, and the suffix is at least 2 characters.
        unsigned int num = *p++ - 48;

		if (!strcmp(p, "ubfn"))
			addAttribute(name, num, UByteFloatNormalized);
		else if (!strcmp(p, "ubf"))
			addAttribute(name, num, UByteFloat);
		else if (!strcmp(p, "ub"))
			addAttribute(name, num, UByte);
		else if (!strcmp(p, "bfn"))
			addAttribute(name, num, ByteFloatNormalized);
		else if (!strcmp(p, "bf"))
			addAttribute(name, num, ByteFloat);
		else if (!strcmp(p, "b"))
			addAttribute(name, num, Byte);
		else if (!strcmp(p, "usfn"))
			addAttribute(name, num, UShortFloatNormalized);
		else if (!strcmp(p, "usf"))
			addAttribute(name, num, UShortFloat);
		else if (!strcmp(p, "us"))
			addAttribute(name, num, UShort);
		else if (!strcmp(p, "sfn"))
			addAttribute(name, num, ShortFloatNormalized);
		else if (!strcmp(p, "sf"))
			addAttribute(name, num, ShortFloat);
		else if (!strcmp(p, "s"))
			addAttribute(name, num, Short);
		else if (!strcmp(p, "uifn"))
			addAttribute(name, num, UIntFloatNormalized);
		else if (!strcmp(p, "uif"))
			addAttribute(name, num, UIntFloat);
		else if (!strcmp(p, "ui"))
			addAttribute(name, num, UInt);
		else if (!strcmp(p, "ifn"))
			addAttribute(name, num, IntFloatNormalized);
		else if (!strcmp(p, "if"))
			addAttribute(name, num, IntFloat);
		else if (!strcmp(p, "i"))
			addAttribute(name, num, Int);
		else if (!strcmp(p, "f"))
			addAttribute(name, num, Float);
		else if (!strcmp(p, "df"))
			addAttribute(name, num, DoubleFloat);
		else if (!strcmp(p, "d"))
			addAttribute(name, num, Double);
		else
			throw runtime_error("parse failed");
    }
}

unsigned int
VertexLayout::addAttribute(const string &name, unsigned int elemcount, AttributeFormat format)
{
	assert(elemcount);
	assert(name.size() > 0);

	m_names.push_back(name);
	m_elementcounts.push_back(elemcount);
	m_offsets.push_back(m_vertexsize);

	switch (format)
	{
		case UByteFloatNormalized:
		m_intypes.push_back(GL_UNSIGNED_BYTE);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_BYTE);
		break;

		case UByteFloat:
		m_intypes.push_back(GL_UNSIGNED_BYTE);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_BYTE);
		break;

		case UByte:
		m_intypes.push_back(GL_UNSIGNED_BYTE);
		m_outtypes.push_back(GL_UNSIGNED_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_BYTE);
		break;

		case ByteFloatNormalized:
		m_intypes.push_back(GL_BYTE);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_BYTE);
		break;

		case ByteFloat:
		m_intypes.push_back(GL_BYTE);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_BYTE);
		break;

		case Byte:
		m_intypes.push_back(GL_BYTE);
		m_outtypes.push_back(GL_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_BYTE);
		break;

		case UShortFloatNormalized:
		m_intypes.push_back(GL_UNSIGNED_SHORT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_SHORT);
		break;

		case UShortFloat:
		m_intypes.push_back(GL_UNSIGNED_SHORT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_SHORT);
		break;

		case UShort:
		m_intypes.push_back(GL_UNSIGNED_SHORT);
		m_outtypes.push_back(GL_UNSIGNED_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_SHORT);
		break;

		case ShortFloatNormalized:
		m_intypes.push_back(GL_SHORT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_SHORT);
		break;

		case ShortFloat:
		m_intypes.push_back(GL_SHORT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_SHORT);
		break;

		case Short:
		m_intypes.push_back(GL_SHORT);
		m_outtypes.push_back(GL_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_SHORT);
		break;

		case UIntFloatNormalized:
		m_intypes.push_back(GL_UNSIGNED_INT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_INT);
		break;

		case UIntFloat:
		m_intypes.push_back(GL_UNSIGNED_INT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_INT);
		break;

		case UInt:
		m_intypes.push_back(GL_UNSIGNED_INT);
		m_outtypes.push_back(GL_UNSIGNED_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_UNSIGNED_INT);
		break;

		case IntFloatNormalized:
		m_intypes.push_back(GL_INT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(true);
		m_vertexsize += elemcount*sizeOf(GL_INT);
		break;

		case IntFloat:
		m_intypes.push_back(GL_INT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_INT);
		break;

		case Int:
		m_intypes.push_back(GL_INT);
		m_outtypes.push_back(GL_INT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_INT);
		break;

		case Float:
		m_intypes.push_back(GL_FLOAT);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_FLOAT);
		break;

		case DoubleFloat:
		m_intypes.push_back(GL_DOUBLE);
		m_outtypes.push_back(GL_FLOAT);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_DOUBLE);
		break;

		case Double:
		m_intypes.push_back(GL_DOUBLE);
		m_outtypes.push_back(GL_DOUBLE);
		m_normalized.push_back(false);
		m_vertexsize += elemcount*sizeOf(GL_DOUBLE);
		break;

		default:
		assert(0);
		break;
	};

	return m_names.size() - 1;
}

int
VertexLayout::position(const string &name) const
{
	int pos = -1;
	std::vector<std::string>::const_iterator iter(m_names.begin());
	for (unsigned int i = 0; iter != m_names.end(); ++iter, ++i)
	{
		if (*iter == name)
		{
			pos = i;
			break;
		}
	}

	return pos;
}

unsigned int
VertexLayout::size() const
{
	return m_vertexsize;
}

};
