// basic geometry shader
#version 400

layout(points) in;
layout(line_strip, max_vertices = 64) out;

in vec3 vColor[];
out vec3 fColor;

in float vSides[];
const float PI = 3.1415926;

void main()
{
	fColor = vColor[0];
	
	for(int i = 0; i <= vSides[0]; i++) {
		float ang = (PI * 2.0 / vSides[0]) * i;
		
		vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
		gl_Position = gl_in[0].gl_Position + offset;
		EmitVertex();
	}
	
	EndPrimitive();
}