// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITEXTURE_H
#define _GUITEXTURE_H

#include "Color.h"
#include "RefCounted.h"
#include "graphics/Drawables.h"
#include "graphics/Texture.h"

namespace Graphics {
	class Renderer;
	class Material;
	class VertexBuffer;
} // namespace Graphics

namespace Gui {

	// a textured quad with reversed winding for the UI
	// XXX possibly doesn't belong in Gui::, but its knowledge of reverse-winding
	// makes it seem odd for Graphics::Drawables
	class TexturedQuad {
	public:
		TexturedQuad(Graphics::Texture *texture) :
			m_texture(RefCountedPtr<Graphics::Texture>(texture)) {}
		virtual ~TexturedQuad() {}
		virtual void Draw(Graphics::Renderer *r) { Draw(r, vector2f(0.0f), vector2f(1.0f)); }
		void Draw(Graphics::Renderer *r, const Color &tint) { Draw(r, vector2f(0.0f), vector2f(1.0f), tint); }
		void Draw(Graphics::Renderer *r, const vector2f &pos, const vector2f &size, const Color &tint = Color::WHITE) { Draw(r, pos, size, vector2f(0.0f), m_texture->GetDescriptor().texSize, tint); }
		void Draw(Graphics::Renderer *r, const vector2f &pos, const vector2f &size, const vector2f &texPos, const vector2f &texSize, const Color &tint = Color::WHITE);

		const Graphics::Texture *GetTexture() const { return m_texture.Get(); }

	private:
		RefCountedPtr<Graphics::Texture> m_texture;
		std::unique_ptr<Graphics::Material> m_material;
		RefCountedPtr<Graphics::VertexBuffer> m_vb;
	};

} // namespace Gui

#endif
