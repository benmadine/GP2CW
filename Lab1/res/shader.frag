#version 120

varying vec2 texCoord0;
varying vec3 norms0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0,0,10), norms0), 0.5, 1.0);
}

