#version 120

varying vec4 color;

varying float cosValue;
void main(void)
{
	vec4 color1 = vec4(1.0, 1.0, 0.0, 1);
    vec4 color2 = vec4(0.0, 0.0, 0.0, 1);
	gl_FragColor = mix(color1, color2, cosValue);
}
