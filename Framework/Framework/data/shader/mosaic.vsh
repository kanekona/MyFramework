//
// バーテックスシェーダー
//

#version 400

in vec2 inpos;
in vec4 incolor;
in vec2 inuv;
uniform vec2 inscreen;
in float inscale;
out vec2 uv;
out vec2 screen;
out float scale;
out vec4 color;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = vec4(inpos, 0.0, 1.0) * viewMatrix;
	uv = inuv;
	color = incolor;
	screen = inscreen;
	scale = inscale;
}