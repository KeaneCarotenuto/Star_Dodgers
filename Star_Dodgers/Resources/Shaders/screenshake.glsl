#ifdef GL_ES
precision mediump float;
#endif



// Uniform Inputs
uniform sampler2D iImageTexture;
uniform vec2 iResolution;
uniform float iTime;
uniform vec2 ShakeAmplitude = vec2(0.005, 0.005);
uniform vec2 ShakeFrequency = vec2(50.0, 50.0);
uniform float ChromaticAberration = 0.0005;
vec2 AberrationR = vec2(0.001, -0.001);
vec2 AberrationG = vec2(0.002, -0.002);
vec2 AberrationB = vec2(0.003, -0.003);
float pi = 3.14159;


void main()
{
	//ChromaticAberration = ((sin(iTime)+1.0)/2.0) * 0.002;
	vec2 uv = (gl_FragCoord.xy / iResolution);
	ShakeAmplitude = ShakeAmplitude * 0.001;
	uv.y += ShakeAmplitude.y * sin(iTime * ShakeFrequency.y);
	uv.x += ShakeAmplitude.x * cos(iTime * ShakeFrequency.x);
	AberrationR = vec2(sin((iTime * 15.0)), cos((iTime * 15.0)));
	AberrationG = vec2(sin((iTime * 15.0) + ((pi * 2.0)/3.0)), cos((iTime * 15.0) + ((pi * 2.0)/3.0)));
	AberrationB = vec2(sin((iTime * 15.0) + (((pi * 2.0)/3.0)*2.0)), cos((iTime * 15.0) + (((pi * 2.0)/3.0)*2.0)));
	vec4 color = texture(iImageTexture, uv);
	vec4 rVal = texture(iImageTexture, uv + (AberrationR * ChromaticAberration));
	vec4 gVal = texture(iImageTexture, uv + (AberrationG * ChromaticAberration));
	vec4 bVal = texture(iImageTexture, uv + (AberrationB * ChromaticAberration));
	gl_FragColor = vec4(rVal.r, gVal.g, bVal.b, 1.0);

	
}
	
	
	
