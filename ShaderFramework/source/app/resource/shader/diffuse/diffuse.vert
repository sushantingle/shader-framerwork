// Diffuse vertex shader

varying vec4 gl_FrontColor;

void main(void)
{			
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient, specular;
	float NDotL, NDotHV;

	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[0].position));

	NDotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * (gl_LightSource[0].diffuse);
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	if(NDotL > 0.0) {
		NDotHV = max(dot(normal, normalize(gl_LightSource[0].halfVector.xyz)), 0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NDotHV, gl_FrontMaterial.shininess);
		gl_FrontColor = gl_Color * (NDotL * diffuse + ambient + globalAmbient + specular);
	}
	else
	{
		gl_FrontColor = gl_Color * (NDotL * diffuse + ambient + globalAmbient);
	}

	gl_Position = ftransform();
}