#ifndef VERTEXLAYOUT_H
#define VERTEXLAYOUT_H

#include <string>
#include <vector>
#include <assert.h>

#include "glcorearb.h"

namespace gbox
{

class VertexLayout
{
public:
	// Use addAttribute() calls if using this ctor.
    VertexLayout ()
    {
    }

    // This is just a convenience routine if you know ahead of time what the format is.
	// The format will be decoded and the appropriate addAttribute() calls will be made.
	// Format strings are of the form
	//
	// <name>:[1-4][datatype], ...
	//
	// where datatype is one of
	//
	// ubfn (unsigned byte to normalized floating point)
	// ubf  (unsigned byte to floating point)
	// ub   (unsigned byte to unsigned int)
	// bfn  (signed byte to normalized floating point)
	// bf   (signed byte to floating point)
	// b    (signed byte to signed int)
	// usfn (unsigned short to normalized floating point)
	// usf  (unsigned short to floating point)
	// us   (unsigned short to unsigned int)
	// sfn  (signed short to normalized floating point)
	// sf   (signed short to floating point)
	// s    (signed short to signed int)
	// uifn (unsigned int to normalized floating point)
	// uif  (unsigned int to floating point)
	// ui   (unsigned int to unsigned int)
	// ifn  (signed int to normalized floating point)
	// if   (signed int to floating point)
	// i    (signed int to signed int)
	// f    (float to float)
	// df   (double to float)
	// d    (double to double)
	//
	// Note that fd (float to double) is not allowed, as glVertexAttribLPointer only
	// allows type to be GL_DOUBLE.
	//
	// The datatype specification consists of a mandatory input data type, and an optional
	// output type of floating point (f) for integral types. The input types refer to VBO
	// storage, while the output types refer to vertex attribute representation in the shaders.
	// There are in total 8 valid input data types (ub, b, us, s, ui, i, f, d). The f output
	// type specifies that the input type is to be converted to single precision float. If
	// present, an additional specifier (n) for integral types can be used to indicate that
	// the output is to be normalized (e.g. an unsigned byte value of 255 would be converted
	// to 1.0 and a signed byte value of -128 would be converted to -1.0).
	VertexLayout (const std::string &format);

    unsigned int attributeCount () const
    {
        return m_names.size();
    }

    const std::string name (unsigned int i) const
    {
		assert(i < m_names.size());
        return m_names[i];
    }

    unsigned int elementCount (unsigned int i) const
    {
		assert(i < m_elementcounts.size());
        return m_elementcounts[i];
    }

    GLuint inType (unsigned int i) const
    {
		assert(i < m_intypes.size());
        return m_intypes[i];
    }

    GLuint outType (unsigned int i) const
    {
		assert(i < m_outtypes.size());
        return m_outtypes[i];
    }

	bool normalized (unsigned int i) const
	{
		assert(i < m_normalized.size());
		return m_normalized[i];
	}

	bool integerOutput (unsigned int i) const
	{
		assert(i < m_outtypes.size());
		return (m_outtypes[i] == GL_UNSIGNED_INT || m_outtypes[i] == GL_INT);
	}

	bool singlePrecisionOutput (unsigned int i) const
	{
		assert(i < m_outtypes.size());
		return (m_outtypes[i] == GL_FLOAT);
	}

	bool doublePrecisionOutput (unsigned int i) const
	{
		assert(i < m_outtypes.size());
		return (m_outtypes[i] == GL_DOUBLE);
	}

    int position (const std::string &name) const;

	// Calculate the size in bytes of a complete vertex. size*numvertices would be useful to size e.g. a VBO.
	unsigned int size () const;

	unsigned int offset (unsigned int i) const
	{
		assert(i < m_offsets.size());
		return m_offsets[i];
	}

	enum AttributeFormat
	{
		UByteFloatNormalized,
		UByteFloat,
		UByte,
		ByteFloatNormalized,
		ByteFloat,
		Byte,
		UShortFloatNormalized,
		UShortFloat,
		UShort,
		ShortFloatNormalized,
		ShortFloat,
		Short,
		UIntFloatNormalized,
		UIntFloat,
		UInt,
		IntFloatNormalized,
		IntFloat,
		Int,
		Float,
		DoubleFloat,
		Double
	};

    unsigned int addAttribute (const std::string &name, unsigned int numelems, AttributeFormat format);

private:
    std::vector<std::string> m_names;
    std::vector<unsigned int> m_elementcounts;
    std::vector<GLuint> m_intypes;
    std::vector<GLuint> m_outtypes;
	std::vector<bool> m_normalized;
	std::vector<unsigned int> m_offsets;

	unsigned int m_vertexsize;
};

};

#endif
