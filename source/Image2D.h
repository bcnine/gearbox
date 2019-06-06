#ifndef IMAGE2D_H
#define IMAGE2D_H

#include <string>
#include <memory>

#include "Types.h"

namespace gbox
{

// It's tempting to want to implement Image2D as a template, parameterized
// by datatype and additionally by perhaps the number of channels. I have
// avoided this temptation for a few reasons. First, I don't want to
// run into "template dependency hell", and the main way to avoid that is
// to have a non-template base class with a template derived class, which is
// complicated and messy. Also, this idea, while elegant in theory, doesn't
// really buy you much because most of the operations don't know or care
// (and rightly so) what the types are - they just to the right thing. The
// exception is the averaging, which I may move somewhere else anyway. Also,
// clients don't currently have to know or care about the # of channels and
// the datatype, unless they query them via function calls. Otherwise, every
// use of a Image2D would encode the type, and that can be very restrictive.
// Finally, even if I were to parameterize by datatype, other code (like
// OpenGL) needs to know the type in terms of a value (e.g. GL_FLOAT), meaning
// that I'd *still* need functions like getDataType() and whatnot. These things
// start to tarnish some of the elegance a template would otherwise suggest.

class Image2D;
typedef std::shared_ptr<Image2D> Image2DPtr;

class Image2D
{
public:
    // Image2D can avoid actually allocating memory, if for example the
    // texture data will be defined entirely at run-time and stored in the
    // run-time data structures. However, another use case entails creating
    // a Image2D, initially empty, but filling it manually elsewhere. In
    // this case, we'd like the memory to actually exist so we can write to
    // it. In this case, set alloc = true. Note that alloc only applies if
    // data = 0 (non-zero data always causes an alloc and a copy).
    static Image2DPtr create (unsigned int width, unsigned int height,
                              unsigned int channels, DataType dtype,
                              const void *data = 0, bool alloc = false);

    // This is a convenience function that infers width, height, datatype,
    // and number of channels from the provided reference image. Memory
    // is always allocated, but copying (from refimage) is conditional.
    static Image2DPtr create (const Image2DPtr &refimage, bool copy=false);

    unsigned int getWidth () const
    {
        return m_width;
    }

    unsigned int getHeight () const
    {
        return m_height;
    }

    unsigned int getChannels () const
    {
        return m_channels;
    }

    DataType getDataType () const
    {
        return m_dtype;
    }

    unsigned char *getData () const
    {
        return m_data;
    }

    unsigned int getSize () const
    {
        return m_width*m_height*m_channels;
    }

    unsigned char *mallocAligned (unsigned int nbytes);

    void copy (unsigned int xoff, unsigned int yoff, const Image2DPtr &image,
               unsigned int imgxoff, unsigned int imgyoff, unsigned int w, unsigned int h);

    void xflip  ();
    void yflip  ();
    void xyflip ();

    Image2DPtr transpose (unsigned int imgxoff, unsigned int imgyoff,
                          unsigned int w, unsigned int h);

    // writeTGA() is a simple function for dumping the image out to disk
    // using the Targa file format. Comes in handy for debugging texture
    // images. Currently only works if datatype is unsigned byte.
    bool writeTGA (const std::string &path);

    static bool makeJPEGThumbnail (const char *sourcepath, const char *thumbpath, unsigned int width, unsigned int height);

    static bool resize3 (const unsigned char *srcbuf, unsigned int srcw, unsigned int srch, unsigned char *dstbuf, unsigned int dstw, unsigned int dsth);

private:
    Image2D (unsigned int width, unsigned int height,
             unsigned int channels, DataType type,
             const void *data, bool alloc);

    unsigned char * m_data;

    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_channels;

    DataType m_dtype;
};

};

#endif
