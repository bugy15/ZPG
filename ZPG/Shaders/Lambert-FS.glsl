#version 400

float c = 0.1;  //Constant Attenuation
float l = 0.1;  //Linear Attenuation
float q = 0.001;//Quadratic Attenuation

struct lightSource{
	vec4  position;
	vec4  color;
	vec4  direction;
	float angle;
	float intensity;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 cameraPosition;
uniform lightSource light[3];
uniform vec4 model_ambient;
uniform	vec4 model_color;

void main (void)
{
	float edge_size = 1.1; 
	vec4  final_color = model_ambient * model_color;  //Ambient

	for(int i = 0; i < 3; i++)
	{
		vec3 L = normalize(light[i].position.xyz - ex_worldPosition.xyz);
		vec3 D = normalize(light[i].direction.xyz);
		vec3 N = normalize(ex_worldNormal);  
		vec3 E = normalize(cameraPosition - ex_worldPosition.xyz);
		vec3 R = normalize(reflect(-L, ex_worldNormal.xyz));

		float d = length(vec3 (light[i].position.xyz - ex_worldPosition.xyz)); //Distance of Light to surface
		float att = 1.0 / ( c + (l*d) + (q*d*d) );

		float dot_product = max( dot(N,L), 0.0);
		float alpha = dot(-L, D);
		float flashLight = cos(light[i].angle * 0.017453295);  //Angle of flashlight(degrees to rad)
		float inner_angle = (edge_size - flashLight) / 10;
	
		float spot = clamp((alpha - flashLight) / inner_angle, 0.0, light[i].intensity/100);
		vec4  specular = (pow(max(dot(R, E), 0.0), 10)) * light[i].color  * model_color;
		vec4  diffuse = dot_product * light[i].color  * model_color;

		if(dot_product > 0.0)
		{
			if(light[i].angle <= 90.0)  //Spot Light
			{
				final_color +=  diffuse  * spot * att;
			}
			else  //Point Light
			{
				final_color +=  diffuse  * light[i].intensity/100 * att;
			}
		}
	}
	
	gl_FragColor = final_color ;
}