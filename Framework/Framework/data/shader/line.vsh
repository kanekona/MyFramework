//
// バーテックスシェーダー
//

#version 400
in vec2 inpos;

uniform mat4 viewMatrix;

in vec4 incolor;

out vec4 color;

void main()
{
	gl_Position = vec4(inpos, 0.0, 1.0) * viewMatrix;
	color = incolor;
}