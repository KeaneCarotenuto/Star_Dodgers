#ifdef GL_ES
precision mediump float;
#endif


uniform float iResolution;
uniform float iTime;
//uniform float iTimeDelta


float iSpeed = 100.0;
float iDensity = 5.0;
float iStarSize = 5.0;


float rand(vec2 co)
{
    return fract(sin(dot(co.xy,vec2(12.9898,78.233)))*43758.5453123);
}

void main( void ) 
{	
    vec2 filteredRes = vec2(gl_FragCoord.x - mod(gl_FragCoord.x, iStarSize), gl_FragCoord.y - mod(gl_FragCoord.y, iStarSize));
    vec2 st = filteredRes/iResolution;
    st *= 1.0;

    vec2 ipos = floor(st);
    vec2 fpos = fract(st);



    float isStar = (pow(rand(fpos), 100.0 / iDensity)) * sin((iTime/(100.0/iSpeed)) * (rand(filteredRes) * (3.14159 * 2.0)));
	gl_FragColor = vec4(isStar, isStar, isStar, 1.0);
}
	
	
	
