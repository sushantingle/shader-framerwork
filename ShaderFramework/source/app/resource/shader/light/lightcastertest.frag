
#version 330 core
out vec4 fragColor;
uniform vec3 lightPos;
uniform vec3 lightDir; #for directional light
uniform vec3 viewPos;
uniform int shininess;
uniform float constantAtt;
uniform float linearAtt;
uniform float quadAtt;
uniform vec3 spotDir;
uniform float cutoff;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

in vec3 outNormal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
	vec4 ambient = texture(diffuseMap, texCoord);
	
	vec3 norm = normalize(outNormal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * texture(diffuseMap, texCoord);

	float distance = length(lightPos - fragPos);
	float attenuation = 1.0 / (constantAtt + (linearAtt * distance) + (quadAtt * distance * distance));
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec4 specular = 0.5 * spec * texture(specularMap, texCoord);

	vec3 fragDir = normalize(lightPos - fragPos);
	float theta = dot(fragDir, spotDir);
	if(theta > cutoff)
	{
			
	}

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec4 result = (ambient + diffuse + specular);
	fragColor = result;
}