//http://www.youtube.com/user/thecplusplusguy
//fragment shader for VBO's
#version 120
uniform sampler2D img;
uniform vec3 color;
varying vec3 color2;
varying vec2 texcoord;

void main()
{
	vec3 texcolor=vec3(texture2D(img,texcoord));
	gl_FragColor=vec4(texcolor,1.0);
}