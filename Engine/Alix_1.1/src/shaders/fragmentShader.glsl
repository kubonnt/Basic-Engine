#version 330 core
out vec4 FragColor;

in vec3 ourColor;
// in vec3 Position; if I then set the FragColor = vec4(Position, 1.0f) the bottom-left side of the triangle becoms black 

void main()
{
	FragColor = vec4(ourColor, 1.0f);
}