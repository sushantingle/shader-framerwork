// diffuse fragment shader

varying vec4 diffuse, ambient, ecPos, vertexColor;
varying vec3 normal, halfVector;

void main()
{
	vec3 n, halfV,lightDir;
	float NDotL, NDotHV, dist, att;

	lightDir = vec3(gl_LightSource[0].position - ecPos);
	dist = length(lightDir);
	
	vec4 color = ambient;

	n = normalize(normal);
	
	NDotL = max(dot(n, normalize(lightDir)), 0.0);

	if(NDotL > 0.0) {
		att = 1.0 / (gl_LightSource[0].constantAttenuation + gl_LightSource[0].linearAttenuation * dist + gl_LightSource[0].quadraticAttenuation * dist * dist);
		
		//color = att * (diffuse * NDotL + ambient);
		halfV = normalize(halfVector);
		NDotHV = max(dot(n, halfV), 0.0);

		color = vertexColor * (att * (diffuse * NDotL + ambient) + (att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NDotHV, gl_FrontMaterial.shininess)));
	}
	gl_FragColor = color;
}
