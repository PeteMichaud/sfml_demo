//in vec2 v;
//in vec2 shift;

void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;// + vec4(0.1,0.1,0.0,0.0);
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
    //vec4(v.x,v.y,0.0,1.0);
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_Position = ftransform();
}