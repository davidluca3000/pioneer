// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _MATERIAL_H
#define _MATERIAL_H
/*
 * Materials are used to apply an appropriate shader and other rendering parameters.
 * Users request materials from the renderer by filling a MaterialDescriptor structure,
 * and calling Renderer::CreateMaterial.
 * Users are responsible for deleting a material they have requested. This is because materials
 * are rarely shareable.
 * Material::Apply is called by renderer before drawing, and Unapply after drawing (to restore state).
 * For the OGL renderer, a Material is always accompanied by a Program.
 */
#include "Color.h"
#include "matrix4x4.h"
#include "RefCounted.h"

namespace Graphics {

	class Texture;
	class RendererOGL;

	// Shorthand for unique effects
	// The other descriptor parameters may or may not have effect,
	// depends on the effect
	enum EffectType {
		EFFECT_DEFAULT,
		EFFECT_VTXCOLOR,
		EFFECT_UI,
		EFFECT_STARFIELD,
		EFFECT_PLANETRING,
		EFFECT_GEOSPHERE_TERRAIN,
		EFFECT_GEOSPHERE_TERRAIN_WITH_LAVA,
		EFFECT_GEOSPHERE_TERRAIN_WITH_WATER,
		EFFECT_GEOSPHERE_SKY,
		EFFECT_GEOSPHERE_STAR,
		EFFECT_GASSPHERE_TERRAIN,
		EFFECT_FRESNEL_SPHERE,
		EFFECT_SHIELD,
		EFFECT_SKYBOX,
		EFFECT_SPHEREIMPOSTOR,
		EFFECT_GEN_GASGIANT_TEXTURE,
		EFFECT_BILLBOARD_ATLAS,
		EFFECT_BILLBOARD
	};

	// XXX : there must be a better place to put this
	enum MaterialQuality {
		HAS_ATMOSPHERE = 1 << 0,
		HAS_ECLIPSES = 1 << 1,
		HAS_HEAT_GRADIENT = 1 << 2
	};

	// Renderer creates a material that best matches these requirements.
	// EffectType may override some of the other flags.
	class MaterialDescriptor {
	public:
		MaterialDescriptor();
		EffectType effect;
		bool alphaTest;
		bool glowMap;
		bool ambientMap;
		bool lighting;
		bool normalMap;
		bool specularMap;
		bool usePatterns; //pattern/color system
		bool vertexColors;
		bool instanced;
		Sint32 textures; //texture count
		Uint32 dirLights; //set by RendererOGL if lighting == true
		Uint32 quality; // see: Graphics::MaterialQuality
		Uint32 numShadows; //use by GeoSphere/GasGiant for eclipse

		friend bool operator==(const MaterialDescriptor &a, const MaterialDescriptor &b);
	};

	/*
 * A generic material with some generic parameters.
 */
	class Material : public RefCounted {
	public:
		Material();
		virtual ~Material() {}

		Texture *texture0;
		Texture *texture1;
		Texture *texture2;
		Texture *texture3;
		Texture *texture4;
		Texture *texture5;
		Texture *texture6;
		Texture *heatGradient;

		Color diffuse;
		Color specular;
		Color emissive;
		int shininess; //specular power 0-128

		virtual void Apply() {}
		virtual void Unapply() {}
		virtual bool IsProgramLoaded() const = 0;

		virtual void SetCommonUniforms(const matrix4x4f &mv, const matrix4x4f &proj) = 0;

		void *specialParameter0; //this can be whatever. Bit of a hack.

		//XXX may not be necessary. Used by newmodel to check if a material uses patterns
		const MaterialDescriptor &GetDescriptor() const { return m_descriptor; }

	protected:
		MaterialDescriptor m_descriptor;

	private:
		friend class RendererOGL;
	};

} // namespace Graphics

#endif
