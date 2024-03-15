#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
//uniform vec4 lp; 
uniform float angle;
uniform vec3 cam_pos;


//Atrybuty
in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;
in vec3 normal;
out vec4 iC;
in vec2 texCoord0;

//dodadne
out vec4 n;
out vec4 v;
out vec4 l1;
out vec4 l2;
out float ndist1;
out float ndist2;
out vec2 iTexCoord0; 
out vec2 iTexCoord1; 


// autorskie dodawanie jasnooœci
vec4 colorSum(vec4 col1, vec4 col2) {
    return vec4(1-(1-col1.r)*(1-col2.r), 1-(1-col1.g)*(1-col2.g), 1-(1-col1.b)*(1-col2.b), 1-(1-col1.a)*(1-col2.a));
}


void main(void) {
    vec4 vertexx = vec4(vertex, 1);
    vec4 normall = vec4(normal, 0);
    vec4 lp1 = vec4(2,5,2,1);
    vec4 lp2 = vec4(80,5,80,1);
    float dist1 = distance(lp1, M[3]);
    float dist2 = distance(lp2, M[3]);
    float ndist1 = (dist1 - 1) * (15 - 1) / (500) + 1;
    float ndist2 = (dist2 - 1) * (15 - 1) / (500) + 1;
    
    l1 = (V*lp1-V*M*vertexx); // wektor padania 
    l2 = (V*lp2-V*M*vertexx); // wektor padania 
    n = (V*M*normall); // wektor normalny
    v = normalize(vec4(vec4(cam_pos.xyz*10, 1) - V*M*vertexx)); //wektor "do oka"
    iC = color*clamp(1/ndist1 + 1/ndist2, 0, 1);

    iTexCoord1 = (n.xy+1)/2;
    iTexCoord0 = texCoord0;

    gl_Position = P*V*M*vertexx;
}
