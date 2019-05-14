//http://www.youtube.com/user/thecplusplusguy
//vertex shader for VBOs
#version 120
uniform vec3 color;
varying vec3 color2;
varying vec2 texcoord;
attribute vec3 vertex;
attribute vec3 inputcolor;
attribute vec2 inputcolor2;

void main()
{
	gl_Position=gl_ModelViewProjectionMatrix*vec4(vertex,1.0);
	color2=vec3(inputcolor);
	texcoord=inputcolor2;
}