
#version 330 core
out vec4 fragColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int shininess;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

in vec3 outNormal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
	vec4 ambient = texture(diffuseMap, texCoord);
	
	vec3 norm = normalize(outNormal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * texture(diffuseMap, texCoord);

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec4 specular = 0.5 * spec * texture(specularMap, texCoord);

	vec4 result = (ambient + diffuse + specular);
	fragColor = result;
}
