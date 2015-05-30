uniform sampler2D texture;
uniform float time;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy) * abs(sin(2.5 * time));

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}