#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
 

//Atrybuty
in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor zwi¹zany z wierzcho³kiem
in vec3 normal;
in vec2 texCoord0; //Atrybut do przekazania wspó³rzêdnych teksturowania


//dodadne
out vec2 iTexCoord0;
out vec3 FragPos;
out vec3 newNormal;


void main(void) {
    vec4 vertexx = vec4(vertex, 1);
	//vec4 normall = vec4(normal, 0); 

	FragPos = vec3(M * vertexx);
    newNormal = mat3(transpose(inverse(M))) * normal;

    iTexCoord0=texCoord0; //Przepisanie danych z atrybutu do zmiennej interpolowanej
    
    gl_Position=P*V*vec4(FragPos, 1.0);
}
