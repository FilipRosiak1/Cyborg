#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 iC;

//dodane
in vec4 n;
in vec4 v;
in vec4 l1;
in vec4 l2;
in float ndist1;
in float ndist2;

in vec2 iTexCoord0; 
in vec2 iTexCoord1; 

float t(float a, float s) {
	return round(s*a)/s;
	}

void main(void) {
	vec4 ml1 = normalize(l1); 
	vec4 ml2 = normalize(l2); 
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	vec4 mr1 = reflect(-ml1,mn); //normalizowny wektor odbicia
	vec4 mr2 = reflect(-ml2,mn); //normalizowny wektor odbicia
	
	//model phonga, str168
	float nl1 = clamp(dot(mn, ml1), 0, 1); // dot swiat這-normalna
	float nl2 = clamp(dot(mn, ml2), 0, 1); // dot swiat這-normalna
	float rv1 = pow(clamp(dot(mr1, mv), 0, 1), 100); // (dot swiat這Odbite-oko)^ alfa<50>
	float rv2 = pow(clamp(dot(mr2, mv), 0, 1), 100); // (dot swiat這Odbite-oko)^ alfa<50>

	//nl1 = t(nl1, 5);
	//rv1 = t(rv1, 5);
	//nl2 = t(nl2, 5);
	//rv2 = t(rv2, 5);

	vec4 test = texture(textureMap1,iTexCoord0);

	//pixelColor= vec4(.1, .1, .1, 1) + 
				vec4(texture(textureMap0,iTexCoord0).rgb * clamp(nl1 + nl2, 0, 1), texture(textureMap0,iTexCoord0).a) +
				vec4(clamp(rv1+rv2, 0, 1), clamp(rv1+rv2, 0, 1), clamp(rv1+rv2, 0, 1), 1); //   

	pixelColor= vec4(.1, .1, .1, 1) + 
				vec4(texture(textureMap0,iTexCoord0).rgb * clamp(nl1 + nl2, 0, 1), texture(textureMap0,iTexCoord0).a) +
				vec4(clamp(rv1+rv2, 0, 1), clamp(rv1+rv2, 0, 1), clamp(rv1+rv2, 0, 1), 1)*test; //   
}
//vec4 kd =mix(texture(textureMap0,iTexCoord0), texture(textureMap1,iTexCoord1), 0.4);

