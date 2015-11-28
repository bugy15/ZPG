#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal; 

out vec4 out_Color;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

void main(void)
{
	vec3 L = normalize(lightPosition.xyz - ex_worldPosition.xyz);
	vec3 N = normalize(ex_worldNormal);
	vec3 R = normalize(reflect(-L, ex_worldNormal.xyz));
	vec3 E = normalize(cameraPosition - ex_worldPosition.xyz);
	
	float dot_product = max(dot(L, N), 0.0);
	vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
	vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	float specular =  pow(max(dot(R, E), 0.0), 10);

	out_Color = ambient + diffuse;
}


