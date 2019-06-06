#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>

namespace gbox
{

class Material
{
public:
	void addTexture (const std::string &file);

	unsigned int textureCount () const;

	std::string texture (unsigned int i) const;

private:
	std::vector<std::string> m_textures;
};

};

#endif
