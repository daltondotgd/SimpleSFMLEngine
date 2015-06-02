uniform float time;

void main()
{
    vec4 twerk = (sin(gl_Vertex * time * 0.05) - cos(gl_Vertex * time * 0.05)) * 0.0025;

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + twerk;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}