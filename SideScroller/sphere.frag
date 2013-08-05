[Pixel_Shader]
//uniform vec2 resolution; // Screen resolution
uniform vec2 pos;
uniform sampler2D tex0; // scene buffer
void main(void)
{
    vec2 tc = gl_TexCoord[0].xy;
    vec2 p = -1.0 + 2.0 * tc;
    float r = dot(p,p);
    if (r > 1.0) discard;
    float f = (1.0-sqrt(1.0-r))/(r);
    vec2 uv;
    uv.x = p.x*f + vec2.x;
    uv.y = p.y*f + vec2.y;
    gl_FragColor = vec4(texture2D(tex0,uv).xyz, 1.0);
}