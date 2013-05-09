#version 120

uniform mat4 MVP,ModelView;

attribute vec4 Position;
attribute vec3 Normal;

varying vec3 normal,pos;

void main()
{	
    vec3 vVertex = vec3(ModelView * Position);
    
    normal = mat3(ModelView) * Normal;
    pos = vVertex;

    gl_Position = MVP * Position;
}
