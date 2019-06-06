#include "Material.h"

#include <assert.h>

using namespace std;

namespace gbox
{

void
Material::addTexture(const string &file)
{
	m_textures.push_back(file);
}

unsigned int
Material::textureCount() const
{
	return m_textures.size();
}

string
Material::texture(unsigned int i) const
{
	assert(i < m_textures.size());
	return m_textures[i];
}

};
