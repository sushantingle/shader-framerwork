
#version 330 core
out vec4 fragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D inTexture1;
uniform sampler2D inTexture2;

void main()
{
	fragColor = mix( texture(inTexture1, TexCoord), texture(inTexture2, TexCoord), 0.2);
}
