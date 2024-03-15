#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;
in vec3 normal;
out vec4 iC;


void main(void) {
    vec4 vertexx = vec4(vertex, 1);
    vec4 normall = vec4(normal, 0);
    float d = distance(V*M*vertexx, vec4(0,0,0,1));
    d = 1-((d-3.3)/3.4);
    iC = vec4(color.rgb*d, color.a);
    gl_Position=P*V*M*vertexx;
}
