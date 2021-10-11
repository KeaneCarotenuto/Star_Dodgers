#ifdef GL_ES
precision mediump float;
#endif



// Uniform Inputs
uniform sampler2D iImageTexture;
uniform vec2 iResolution;
uniform float iTime;
uniform vec2 ShakeAmplitude = vec2(0.005, 0.005);
uniform vec2 ShakeFrequency = vec2(50.0, 50.0);



void main()
{
	vec2 uv = (gl_FragCoord.xy / iResolution);

	uv.y += ShakeAmplitude.y * sin(iTime * ShakeFrequency.y);
	uv.x += ShakeAmplitude.x * cos(iTime * ShakeFrequency.x);
	vec4 color = texture(iImageTexture, uv);
	gl_FragColor = color;

	
}
	
	
	
