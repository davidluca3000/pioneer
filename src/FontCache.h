// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _FONTCACHE_H
#define _FONTCACHE_H

#include "RefCounted.h"
#include "text/TextureFont.h"
#include <map>
#include <string>

class FontCache {
public:
	FontCache() {}

	RefCountedPtr<Text::TextureFont> GetTextureFont(const std::string &name);

private:
	FontCache(const FontCache &);
	FontCache &operator=(const FontCache &);

	std::map<std::string, RefCountedPtr<Text::TextureFont>> m_textureFonts;
};

#endif
