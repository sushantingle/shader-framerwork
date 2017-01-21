// Diffuse vertex shader

uniform float time;
varying vec4 gl_Color;

void main(void)
{			
	vec4 v = vec4(gl_Vertex);
	v.y = sin(5.0 * v.x + time) * 0.25;
	gl_Position = gl_ModelViewProjectionMatrix * v;
}
