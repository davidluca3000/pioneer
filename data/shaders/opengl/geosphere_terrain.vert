// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "attributes.glsl"
#include "lib.glsl"

out vec3 varyingEyepos;
out vec3 varyingNormal;
out vec4 vertexColor;

uniform vec3 geosphereCenter;
uniform float geosphereRadius;

out vec2 texCoord0;
out float dist;

#ifdef TERRAIN_WITH_LAVA
out vec4 varyingEmission;
uniform Material material;
#endif

void main(void)
{
	gl_Position = matrixTransform();
	vertexColor = a_color;
	varyingEyepos = vec3(uViewMatrix * a_vertex);
	varyingNormal = normalize(uNormalMatrix * a_normal);

	texCoord0 = a_uv0.xy;
	dist = abs(varyingEyepos.z);

#ifdef TERRAIN_WITH_LAVA
	varyingEmission = material.emission;
	//Glow lava terrains
	if ( vertexColor.r > 0.4 && vertexColor.g < 0.2 && vertexColor.b < 0.4 )
	{
		varyingEmission = 3.0*vertexColor;
		varyingEmission *= (vertexColor.r+vertexColor.g+vertexColor.b);
	}
#endif
}
