// Diffuse vertex shader

varying vec4 gl_FrontColor;

void main(void)
{			
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NDotL;

	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[0].position));

	NDotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * (gl_LightSource[0].diffuse);
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	gl_FrontColor = NDotL * diffuse + ambient + globalAmbient;

	gl_Position = ftransform();
}
