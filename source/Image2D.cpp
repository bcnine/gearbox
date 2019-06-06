#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Image2D.h"
#include <assert.h>
#include <algorithm>

using namespace std;

struct TGAFileHeader
{
    unsigned char  fileType;
    unsigned char  colorMapType;
    unsigned char  imageType;
    unsigned short cmapFirstEntry;
    unsigned short cmapLength;
    unsigned char  cmapEntrySize;
    unsigned short origX, origY;
    unsigned short width, height;
    unsigned char  bpp;
    unsigned char  info;
};

namespace gbox
{

Image2DPtr
Image2D::create(unsigned int width, unsigned int height,
                unsigned int channels, DataType dtype,
                const void *data, bool alloc)
{
    Image2DPtr p(new Image2D(width,height,channels,dtype,data,alloc));
    return p;
}

Image2DPtr
Image2D::create(const Image2DPtr &refimage, bool copy)
{
    const void *data = copy ? refimage->m_data : 0;
    Image2DPtr  p(new Image2D(refimage->m_width, refimage->m_height,
                              refimage->m_channels, refimage->m_dtype,
                              data, true));

  return p;
}

Image2D::Image2D(unsigned int width, unsigned int height,
                 unsigned int channels, DataType dtype,
                 const void *data, bool alloc) :
m_width(width),
m_height(height),
m_channels(channels),
m_dtype(dtype)
{
    unsigned int numbytes = width*height*channels*SizeOf(m_dtype);
    if (data || alloc)
        m_data = new unsigned char[numbytes];
    if (data)
        memcpy(m_data, (unsigned char *) data, numbytes);
}

bool
Image2D::writeTGA(const string &path)
{
    if (!m_data || (SizeOf(m_dtype) != 1))
        return false;

    FILE *output = fopen(path.c_str(), "wb");
    if (output == NULL)
        return false;

    TGAFileHeader header;
    header.fileType = 0;       // No image ident field
    header.colorMapType = 0;   // No colormap
    header.imageType = 0x2;    // Uncompressed RGB
    header.cmapFirstEntry = 0; // Ignored
    header.cmapLength = 0;     // Ignored
    header.cmapEntrySize = 0;  // Ignored
    header.origX = 0;          // Typical
    header.origY = 0;          // Typical
    header.width = m_width;
    header.height = m_height;
    header.bpp  = (m_channels == 4 || m_channels == 2) ? 32 : 24;
    header.info = (m_channels == 4 || m_channels == 2) ? 0x8 : 0x0;

    fwrite(&header.fileType, sizeof(header.fileType), 1, output);
    fwrite(&header.colorMapType, sizeof(header.colorMapType), 1, output);
    fwrite(&header.imageType, sizeof(header.imageType), 1, output);
    fwrite(&header.cmapFirstEntry, sizeof(header.cmapFirstEntry), 1, output);
    fwrite(&header.cmapLength, sizeof(header.cmapLength), 1, output);
    fwrite(&header.cmapEntrySize, sizeof(header.cmapEntrySize), 1, output);
    fwrite(&header.origX, sizeof(header.origX), 1, output);
    fwrite(&header.origY, sizeof(header.origY), 1, output);
    fwrite(&header.width, sizeof(header.width), 1, output);
    fwrite(&header.height, sizeof(header.height), 1, output);
    fwrite(&header.bpp, sizeof(header.bpp), 1, output);
    fwrite(&header.info, sizeof(header.info), 1, output);

    unsigned char *newdata=(unsigned char *)malloc(header.bpp/8*m_width*m_height);
    unsigned char *newp = newdata;

    for (unsigned int row = 0; row < m_height; ++row)
    {
        for (unsigned int col = 0; col < m_width; ++col)
        {
            unsigned char *p=(unsigned char *) &m_data[m_channels*(row*m_width+col)];
            unsigned char r, g, b, a;
            switch (m_channels)
            {
            case 1:
                *newp++ = *p;
                *newp++ = *p;
                *newp++ = *p;
                break;

            case 2:
                *newp++ = *p;
                *newp++ = *p;
                *newp++ = *p++;
                *newp++ = *p;
                break;

            case 3:
                r = *p++;
                g = *p++;
                b = *p;
                *newp++ = b;
                *newp++ = g;
                *newp++ = r;
                break;

            case 4:
                r = *p++;
                g = *p++;
                b = *p++;
                a = *p;
                *newp++ = b;
                *newp++ = g;
                *newp++ = r;
                *newp++ = a;
                break;
            }
        }
    }

    fwrite(newdata, sizeof(unsigned char),header.bpp/8*m_width*m_height, output);
    free(newdata);
    fclose(output);

    return true;
}

void
Image2D::xflip()
{
    int half = m_width/2;
    int size = m_channels*SizeOf(m_dtype);
    int pitch = m_width*size;

    unsigned char *hp = &m_data[0];
    unsigned char *tp = hp+pitch-size;
    for (int j = 0; j < int(m_height); ++j, hp += half*size, tp = hp+pitch-size)
    {
        for (int i = 0; i < half; ++i, tp -= 2*size)
        {
            for (int k = 0; k < size; ++k)
            {
                unsigned char t = *hp;
                *hp++ = *tp;
                *tp++ = t;
            }
        }
    }
}

void
Image2D::yflip()
{
    int half = m_height/2;
    int size = m_channels*SizeOf(m_dtype);
    int pitch = m_width*size;
    unsigned char *hp = &m_data[0];
    unsigned char *tp = &m_data[(m_height-1)*pitch];
    for (int j = 0; j < half; ++j, tp -= 2*pitch)
    {
        for (int i = 0; i < pitch; ++i)
        {
            unsigned char t = *hp;
            *hp++ = *tp;
            *tp++ = t;
        }
    }
}

void
Image2D::xyflip()
{
    int half = m_height/2;
    int size = m_channels*SizeOf(m_dtype);
    int pitch = m_width*size;

    unsigned char *hp = &m_data[0];
    unsigned char *tp = &m_data[(m_height-1)*pitch+(m_width-1)*size];
    for (int j = 0; j < half; ++j)
    {
        for (int i = 0; i < int(m_width); ++i, tp -= 2*size)
        {
            for (int k = 0; k < size; ++k)
            {
                unsigned char t = *hp;
                *hp++ = *tp;
                *tp++ = t;
            }
        }
    }
}

void
Image2D::copy(unsigned int dli, unsigned int dlj, const Image2DPtr &image,
              unsigned int sli, unsigned int slj, unsigned int sw, unsigned int sh)
{
    assert(m_channels == image->getChannels());
    assert(m_dtype == image->getDataType());
    assert(sli+sw-1 <= image->getWidth()-1);
    assert(slj+sh-1 <= image->getHeight()-1);

    int dui = std::min(dli+sw-1, m_width-1);
    int duj = std::min(dlj+sh-1, m_height-1);
    int size = m_channels*SizeOf(m_dtype);
    int pitch = (dui-dli+1)*size;
    int spitch = image->getWidth()*size;
    int dpitch = m_width*size;
    unsigned char *sphead = &(image->getData()[slj*spitch+sli*size]);
    unsigned char *dphead = &(m_data[dlj*dpitch+dli*size]);
    int numrows = duj-dlj+1;

    for (int j = 0; j < numrows; ++j)
    {
        unsigned char *sp = sphead + j*spitch;
        unsigned char *dp = dphead + j*dpitch;
        for (int i = 0; i < pitch; ++i)
            *dp++ = *sp++;
    }
}

unsigned char *
Image2D::mallocAligned(unsigned int nbytes)
{
    unsigned int padding = (nbytes - (m_width*m_channels % nbytes)) % nbytes;
    unsigned int srcpitch = m_width*m_channels;
    unsigned int dstpitch = srcpitch + padding;
    unsigned char *dst = (unsigned char *) malloc(m_height*dstpitch);
    unsigned char *src = m_data;

    for (unsigned int row = 0; row < m_height; ++row)
        memcpy(dst+row*dstpitch, src+row*srcpitch, srcpitch);

    return dst;
}

Image2DPtr
Image2D::transpose(unsigned int imgxoff, unsigned int imgyoff, unsigned int w, unsigned int h)
{
    int size = m_channels*SizeOf(m_dtype);
    int ipitch = m_width*size;

    Image2DPtr tpose(Image2D::create(h, w, m_channels, m_dtype, 0, true));

    int tpitch = h*size;

    unsigned char *idata = m_data;
    unsigned char *tdata = tpose->getData();

    int li = imgxoff;
    int ui = li+w-1;
    int lj = imgyoff;
    int uj = lj+h-1;

    for (int j = uj; j >= lj; --j)
    {
        for (int i = li; i <= ui; ++i)
        {
            int ti = uj-j;
            int tj = ui-i;
            unsigned char *ip = &idata[j*ipitch+i*size];
            unsigned char *tp = &tdata[tj*tpitch+ti*size];
            for (int k = 0; k < size; ++k)
                *tp++ = *ip++;
        }
    }

    return tpose;
}

};
