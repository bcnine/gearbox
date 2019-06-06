#ifndef DRAWABLE_LOADER_H
#define DRAWABLE_LOADER_H

#include "GLBase.h"

namespace gbox
{

class Model;
class ElementModel;
class ElementDrawable;

class ArrayModel;
class ArrayDrawable;

class VertexLayout;

class DrawableLoader : public GLBase
{
public:
	DrawableLoader ();

	std::shared_ptr<ArrayDrawable>   createArrayDrawable   (const ArrayModel &model);
	std::shared_ptr<ElementDrawable> createElementDrawable (const ElementModel &model);

private:
	void loadTexture     (const std::string &file, GLuint &texobj, unsigned int texunit);
    void loadTextureSets (const Model &model, std::vector<std::vector<std::pair<GLenum, GLuint>>> &texsets);

    GLuint createVBO (const VertexLayout &layout, const Model &model);

    template <class T>
    void *writeBytes (void *p, T arg1)
    {
        T *rp = reinterpret_cast<T *>(p);
        *rp++ = arg1;
        return reinterpret_cast<void *>(rp);
    }

    template <class T>
    void *writeBytes (void *p, T arg1, T arg2)
    {
        T *rp = reinterpret_cast<T *>(p);
        *rp++ = arg1;
        *rp++ = arg2;
        return reinterpret_cast<void *>(rp);
    }

    template <class T>
    void *writeBytes (void *p, T arg1, T arg2, T arg3)
    {
        T *rp = reinterpret_cast<T *>(p);
        *rp++ = arg1;
        *rp++ = arg2;
        *rp++ = arg3;
        return reinterpret_cast<void *>(rp);
    }

    template <class T>
    void *writeBytes (void *p, T arg1, T arg2, T arg3, T arg4)
    {
        T *rp = reinterpret_cast<T *>(p);
        *rp++ = arg1;
        *rp++ = arg2;
        *rp++ = arg3;
        *rp++ = arg4;
        return reinterpret_cast<void *>(rp);
    }
};

};

#endif
