uniform vec2 pos;
uniform sampler2D tex0; // scene buffer
void main(void)
{
    //cull pixels that aren't in the circle
    vec2 tc = gl_TexCoord[0].xy;
    vec2 p = -1.0 + 2.0 * tc;
    float r = dot(p,p);
    if (r > 1.0) discard;

    //warp the texture to appear spherical
    float f = (1.0-sqrt(1.0-r))/(r);
    vec2 uv;
    uv.x = fract(p.x*f - pos.x/1024.0*10.0);
    uv.y = fract(p.y*f - pos.y/768.0*10.0);
    gl_FragColor = vec4(texture2D(tex0,uv).xyz, 1.0);
}