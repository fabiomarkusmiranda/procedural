
uniform sampler2D texture;

//Light
varying vec4 diffuse,ambient;
varying vec3 normal,lightDir,halfVector;
//varying vec3 lightDir,halfVector;




void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Vertex.z = texture2D(texture,gl_TexCoord[0].st).r * 0.5;
	
	
	/* first transform the normal into eye space and 
	normalize the result */
	//normal = normalize(gl_NormalMatrix * vec3(0,1,1));
	

	
	/* now normalize the light's direction. Note that 
	according to the OpenGL specification, the light 
	is stored in eye space. Also since we're talking about 
	a directional light, the position field is actually direction */
	lightDir = normalize(vec3(gl_LightSource[0].position));

	/* Normalize the halfVector to pass it to the fragment shader */
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
				
	/* Compute the diffuse, ambient and globalAmbient terms */
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;



	gl_Position = gl_ModelViewProjectionMatrix  * gl_Vertex;

}
