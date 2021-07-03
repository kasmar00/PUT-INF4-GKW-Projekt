#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 light;
uniform vec4 camera;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
//in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord; //współrzędne teksturowania

//Zmienne interpolowane
//out vec4 ic;
out float d;
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0; //interpolowane współrzędne teksturowania

void main(void) {
    vec4 lp = light; //pozcyja światła, przestrzeń świata
    l = normalize(V * lp - V*M*vertex); //wektor do światła w przestrzeni oka
    //v = normalize(vec4(0,0,0,1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    v = normalize(V*camera - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    
  //  ic = color;

    d = abs(distance(M*vertex, light));
    d=d/100;
    d=1-clamp(d, 0, 1);

    gl_Position=P*V*M*vertex;

    iTexCoord0=texCoord;
}
