
in vec2 pos;
in vec3 color;
in float sides;

varying out vec3 vColor;
varying out float vSides;
void main(void)
{			
	gl_Position = vec4(pos, 0.0, 1.0);
	vColor = color;
	vSides = sides;
}
