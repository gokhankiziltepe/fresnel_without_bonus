#version 120

varying vec3 normal,pos;

void main(void)
{
	vec3 N = normalize(normal);
	vec3 L = normalize(vec3(gl_LightSource[0].position.xyz - pos));
    
    vec4 color1 = vec4(1.0, 1.0, 0.0, 1);
    vec4 color2 = vec4(1.0, 0.0, 0.0, 1);
    
	gl_FragColor = mix(color1, color2, dot(N,L) / (length(N)*length(L)));
}
