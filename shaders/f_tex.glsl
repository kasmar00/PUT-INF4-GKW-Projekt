#version 330

uniform sampler2D tex; // jednostka teksturująca

uniform mat4 V;

uniform vec4 lights[300];
uniform int count;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//in vec4 ic; 
//in float d;
in vec4 n;
in vec2 iTexCoord0;
in vec4 fragPos;

vec3 calcLight(vec4 normal, vec4 light) {
	//normal - wektor normalny sciany w przestrzeni oka
	//light - wspolrzedne swiatla w przestrzeni swiata

	float d=0.1;
	d=abs(distance(fragPos, light));
	d=d/25;
	d=1-clamp(d,0,1);

	vec4 ml=normalize(V*light - V*fragPos); //wektor do światła w przestrzeni oka
	float nl = clamp(dot(normal, ml), 0, 1);
	return vec3(d*nl);
}

void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 mn = normalize(n);

	//Parametry powierzchni
	vec4 kd = texture(tex, iTexCoord0); // pobranie koloru
	vec4 ks = vec4(1, 1, 1, 1);

	//Obliczenie modelu oświetlenia
	//pixelColor= vec4(kd.rgb*d * nl, kd.a);
	pixelColor=vec4(0,0,0,kd.a);
	for (int i=0; i<count; i++){
		vec3 tmp=calcLight(mn, lights[i]);
		pixelColor+=vec4(kd.rgb*tmp,0);
	}
}
