
in vec2 pos;
in vec3 color;

varying out vec3 vColor;

void main(void)
{			
	gl_Position = vec4(pos, 0.0, 1.0);
	vColor = color;
}
