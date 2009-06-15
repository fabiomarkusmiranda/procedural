
uniform sampler2D texture;

void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Vertex.z = texture2D(texture,gl_TexCoord[0].st).r * 5.0;
	
	
	gl_Position = gl_ModelViewProjectionMatrix  * gl_Vertex;

}