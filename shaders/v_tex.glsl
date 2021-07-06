#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 camera;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord; //współrzędne teksturowania

//Zmienne interpolowane
out float d;
out vec4 n; // wektor normalny ściany
out vec2 iTexCoord0; //interpolowane współrzędne teksturowania
out vec4 fragPos; // pozycja fragmentu

void main(void) {
    //vec4 lp = light; //pozcyja światła, przestrzeń świata
    //l = normalize(V * lp - V*M*vertex); //wektor do światła w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka

    
    //d = abs(distance(M*vertex, light));
    //d=d/100;
    //d=1-clamp(d, 0, 1);

    fragPos=M*vertex;

    gl_Position=P*V*M*vertex;

    iTexCoord0=texCoord;
}
