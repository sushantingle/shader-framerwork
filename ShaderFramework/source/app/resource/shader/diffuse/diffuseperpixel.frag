// diffuse fragment shader

varying vec4 diffuse, ambient;
varying vec3 normal, halfVector;

void main()
{
	vec3 n, halfV,lightDir;
	float NDotL, NDotHV;

	lightDir = vec3(gl_LightSource[0].position);

	vec4 color = ambient;

	n = normalize(normal);
	
	NDotL = max(dot(n, lightDir), 0.0);

	if(NDotL > 0.0) {
		color += diffuse * NDotL;
		halfV = normalize(halfVector);
		NDotHV = max(dot(n, halfV), 0.0);

		color += (gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NDotHV, gl_FrontMaterial.shininess));
	}
	gl_FragColor = color;
}
