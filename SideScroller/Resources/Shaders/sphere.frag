uniform vec2 pos;
uniform sampler2D tex0; // scene buffer
void main(void)
{
    gl_FragColor = vec4(pos.x/1024.0,pos.x/1024.0,pos.x/1024.0,1);
//    vec2 tc = gl_TexCoord[0].xy;
//    vec2 p = -1.0 + 2.0 * tc;
//    float r = dot(p,p);
//    if (r > 1.0) discard;
//    float f = (1.0-sqrt(1.0-r))/(r);
//    vec2 uv;
//    uv.x = p.x*f + pos.x;
//    uv.y = p.y*f + pos.y;
//    gl_FragColor = vec4(texture2D(tex0,uv).xyz, 1.0);
}