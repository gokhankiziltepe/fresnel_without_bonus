#version 120

uniform mat4 MVP,ModelView;

attribute vec4 Position;
attribute vec3 Normal;

varying float cosValue;
void main()
{	
    vec3 vVertex = vec3(ModelView * Position);
    
    vec3 N = mat3(ModelView) * Normal;
	vec3 L = normalize(vec3(gl_LightSource[0].position.xyz - vVertex));
    
    cosValue = dot(N, L) / (length(N) / length(L));
    gl_Position = MVP * Position;
}
	
