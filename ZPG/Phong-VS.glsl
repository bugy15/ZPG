#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec3 ex_worldNormal;
out vec4 ex_worldPosition;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;


void main(void)
{
	gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix)* vec4(in_Position, 1.0f);
	ex_worldPosition = ModelMatrix * vec4(in_Position, 1.0f);
	ex_worldNormal = normalize(transpose(inverse(mat3(ModelMatrix))) * in_Normal);
}
