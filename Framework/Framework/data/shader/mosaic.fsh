//
// フラグメントシェーダー
//

#version 400
in vec2 uv;

uniform sampler2D tex;

out vec4 outcolor;

in vec4 color;
in vec2 screen;
in float scale;

void main()
{
	vec2 mosaic = uv;
	mosaic.x = floor(mosaic.x * screen.x / scale) / (screen.x / scale) + (scale / 2.0) / screen.x;
	mosaic.y = floor(mosaic.y * screen.y / scale) / (screen.y / scale) + (scale / 2.0) / screen.y;
	outcolor = texture2D(tex,mosaic) * color;
}