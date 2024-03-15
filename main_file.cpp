/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "party/biodra.h"
#include "party/glowa.h"
#include "party/nogaL.h"
#include "party/nogaR.h"
#include "party/przedramieL.h"
#include "party/przedramieR.h"
#include "party/ramieL.h"
#include "party/ramieR.h"
#include "party/udoL.h"
#include "party/udoR.h"
#include "party/tors.h"
#include "myCube.h"
#include "kamien1.h"
#include "kamien2.h"
#include "lampa.h"
#include "lawka.h"



float speed_x = 0;
float speed_y = 0;
float cam_speed_x = 0;
float cam_speed_y = 0;
float walk_scale = 0;
float rotate_scale = 0;


/*
pozycja robota na mapce
KORDY KARTEZJAŃSKIE X, Y 
to tutaj kordy -x, z
*/ 
float robot_z_cor = 0;
float robot_x_cor = 0;
float robot_look_angle = 0;

// {x, z, r}
std::vector<std::vector<float>> obstacles{ 
	{0.0f, 20.0f, 6.0f},  // KLÓC
	{-15.0f, -25.0f, 6.0f},  // KLÓC2
	{25.0f, -25.0f, 5.0f},  // lawka
	{25.0f, 25.0f, 2.0f}, // lampa1 
	{25.0f, 0.0f, 2.0f},  // lampa2
	{0.0f, -25.0f, 2.0f}  // lampa3
};


float zoom = 1;
float cam_angle_shift = 0;

bool tryb;

float aspectRatio = 1;



ShaderProgram *sp;

GLuint tex[8];

//Odkomentuj, żeby rysować kostkę
float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;


//Odkomentuj, żeby rysować czajnik
//float* vertices = myTeapotVertices;
//float* normals = myTeapotNormals;
//float* texCoords = myTeapotTexCoords;
//float* colors = myTeapotColors;
//int vertexCount = myTeapotVertexCount;


//Odkomentuj, żeby rysować robota
float* vertices_biodra = biodraPositions;
float* normals_biodra = biodraNormals;
float* texCoords_biodra = biodraTexels;
float* colors_biodra = biodraColors;
int vertexCount_biodra = biodraVertices;

float* vertices_glowa = glowaPositions;
float* normals_glowa = glowaNormals;
float* texCoords_glowa = glowaTexels;
float* colors_glowa = glowaColors;
int vertexCount_glowa = glowaVertices;

float* vertices_nogaL = nogaLPositions;
float* normals_nogaL = nogaLNormals;
float* texCoords_nogaL = nogaLTexels;
float* colors_nogaL = nogaLColors;
int vertexCount_nogaL = nogaLVertices;

float* vertices_nogaR = nogaRPositions;
float* normals_nogaR = nogaRNormals;
float* texCoords_nogaR = nogaRTexels;
float* colors_nogaR = nogaRColors;
int vertexCount_nogaR = nogaRVertices;

float* vertices_przedramieL = przedramieLPositions;
float* normals_przedramieL = przedramieLNormals;
float* texCoords_przedramieL = przedramieLTexels;
float* colors_przedramieL = przedramieLColors;
int vertexCount_przedramieL = przedramieLVertices;

float* vertices_przedramieR = przedramieRPositions;
float* normals_przedramieR = przedramieRNormals;
float* texCoords_przedramieR = przedramieRTexels;
float* colors_przedramieR = przedramieRColors;
int vertexCount_przedramieR = przedramieRVertices;

float* vertices_ramieL = ramieLPositions;
float* normals_ramieL = ramieLNormals;
float* texCoords_ramieL = ramieLTexels;
float* colors_ramieL = ramieLColors;
int vertexCount_ramieL = ramieLVertices;

float* vertices_ramieR = ramieRPositions;
float* normals_ramieR = ramieRNormals;
float* texCoords_ramieR = ramieRTexels;
float* colors_ramieR = ramieRColors;
int vertexCount_ramieR = ramieRVertices;

float* vertices_udoL = udoLPositions;
float* normals_udoL = udoLNormals;
float* texCoords_udoL = udoLTexels;
float* colors_udoL = udoLColors;
int vertexCount_udoL = udoLVertices;

float* vertices_udoR = udoRPositions;
float* normals_udoR = udoRNormals;
float* texCoords_udoR = udoRTexels;
float* colors_udoR = udoRColors;
int vertexCount_udoR = udoRVertices;

float* vertices_tors = torsPositions;
float* normals_tors = torsNormals;
float* texCoords_tors = torsTexels;
float* colors_tors = torsColors;
int vertexCount_tors = torsVertices;

//kamienie
float* vertices_kamien1 = kamien1Positions; 
float* normals_kamien1 = kamien1Normals;
float* texCoords_kamien1 = kamien1Texels;
float* colors_kamien1 = kamien1Colors;
int vertexCount_kamien1 = kamien1Vertices;

float* vertices_kamien2 = kamien2Positions; 
float* normals_kamien2 = kamien2Normals;
float* texCoords_kamien2 = kamien2Texels;
float* colors_kamien2 = kamien2Colors;
int vertexCount_kamien2 = kamien2Vertices;

//LATARNIA
float* vertices_lampa = lampaPositions;
float* normals_lampa = lampaNormals;
float* texCoords_lampa = lampaTexels;
float* colors_lampa = lampaColors;
int vertexCount_lampa = lampaVertices;

//Ławka
float* vertices_lawka = lawkaPositions;
float* normals_lawka = lawkaNormals;
float* texCoords_lawka = lawkaTexels;
float* colors_lawka = lawkaColors;
int vertexCount_lawka = lawkaVertices;


GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
	unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {

    if (action==GLFW_PRESS) {
		if (key == GLFW_KEY_A) speed_x = -PI / 2;
		if (key == GLFW_KEY_D) speed_x = PI / 2;
		if (key == GLFW_KEY_W) speed_y = PI * 1.5f;
		if (key == GLFW_KEY_S) speed_y = -PI * 1.5f;

		if (key == GLFW_KEY_LEFT) cam_speed_x = -PI / 2;
		if (key == GLFW_KEY_RIGHT) cam_speed_x = PI / 2;
		if (key == GLFW_KEY_UP) cam_speed_y = PI * 1.5f;
		if (key == GLFW_KEY_DOWN) cam_speed_y = -PI * 1.5f;

		if (key == GLFW_KEY_R) {
			zoom = 1;
			cam_angle_shift = 0;
		};
    }
    if (action==GLFW_RELEASE) {
        if (key== GLFW_KEY_A) speed_x=0;
        if (key== GLFW_KEY_D) speed_x=0;
        if (key== GLFW_KEY_W) speed_y=0;
        if (key== GLFW_KEY_S) speed_y=0;

		if (key == GLFW_KEY_LEFT) cam_speed_x = 0;
		if (key == GLFW_KEY_RIGHT) cam_speed_x = 0;
		if (key == GLFW_KEY_UP) cam_speed_y = 0;
		if (key == GLFW_KEY_DOWN) cam_speed_y = 0;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0.015, 0.015, 0.2, .8);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);

	tex[0] = readTexture("ROBO_T.png");
	tex[1] = readTexture("ROBO_MET.png");
	tex[2] = readTexture("trawa.png");
	tex[3] = readTexture("BLANK.png");
	tex[4] = readTexture("ROCK.png");
	tex[5] = readTexture("LATARNIA.png");
	tex[6] = readTexture("lawka_T.png");
	tex[7] = readTexture("lawka_MET.png");

	sp=new ShaderProgram("v_simplest1.glsl",NULL,"f_simplest1.glsl");
	//sp = new ShaderProgram("v_9.glsl", NULL, "f_9.glsl");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	float kamera_angle = robot_look_angle + cam_angle_shift + PI + 3.0f / 4.0f * rotate_scale;
	glm::vec3 kamera_pos = glm::vec3(10 * (robot_x_cor - zoom * sin(kamera_angle)), 10, 10 * (robot_z_cor - zoom * cos(kamera_angle)));
	//kamera_pos = glm::vec3(10.0f,10.0f,10.0f);
	glm::mat4 V=glm::lookAt(kamera_pos,
							glm::vec3(robot_x_cor * 10, 7, robot_z_cor * 10), 
							glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 280.0f); //Wylicz macierz rzutowania
	sp->use();//Aktywacja programu cieniującego

    glm::mat4 M=glm::mat4(1.0f);
	M = glm::scale(M, glm::vec3(10.0f, 10.0f, 10.0f));
    

    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
	glUniform1i(sp->u("textureMap0"), 0);
	glUniform1i(sp->u("textureMap1"), 1);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu color

	glUniform3fv(sp->u("cam_pos"), 3, glm::value_ptr(kamera_pos));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[1]);

	float animation_angle;

	// BIODRA
	animation_angle = rotate_scale/3;

	glm::mat4 Mbiodra = M;
	Mbiodra = glm::translate(Mbiodra, glm::vec3(robot_x_cor, 0, robot_z_cor)); // przemieszczenie robota po mapce
	Mbiodra = glm::translate(Mbiodra, glm::vec3(0.0f, 0.408565f, 0.0f));
	Mbiodra = glm::rotate(Mbiodra, animation_angle+robot_look_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Mbiodra = glm::translate(Mbiodra, glm::vec3(-0.0f, -0.408565f, -0.0f));
	
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mbiodra));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_biodra);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_biodra); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_biodra); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_biodra); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_biodra); //Narysuj obiekt


	// TORS
	animation_angle = rotate_scale /3;

	glm::mat4 Mtors = Mbiodra;
	Mtors = glm::translate(Mtors, glm::vec3(0.0f, 0.45601f, 0.0f));
	Mtors = glm::rotate(Mtors, animation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Mtors = glm::translate(Mtors, glm::vec3(-0.0f, -0.45601f, -0.0f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[1]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mtors));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_tors);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_tors); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_tors); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_tors); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_tors); //Narysuj obiekt
	

	// GŁOWA
	animation_angle = rotate_scale/3;
	
	glm::mat4 Mglowa = Mtors;
	Mglowa = glm::translate(Mglowa, glm::vec3(0.0f, 0.667672f, 0.0f));
	Mglowa = glm::rotate(Mglowa, animation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Mglowa = glm::translate(Mglowa, glm::vec3(-0.0f, -0.667672f, -0.0f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[0]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mglowa));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_glowa);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_glowa); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_glowa); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_glowa); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_glowa); //Narysuj obiekt


	// PRAWE RAMIE
	animation_angle = (.35f * sin(angle_y) + .15f) * walk_scale;
	
	glm::mat4 MramieR = Mtors;
	MramieR = glm::translate(MramieR, glm::vec3(-0.099636f, 0.59486f, 0.016287f));
	MramieR = glm::rotate(MramieR, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MramieR = glm::translate(MramieR, glm::vec3(0.099636f, -0.59486f, -0.016287f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[1]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MramieR));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_ramieR);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_ramieR); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_ramieR); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_ramieR); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_ramieR); //Narysuj obiekt


	// LEWE RAMIE
	animation_angle = (.35f * -sin(angle_y) + .15f) * walk_scale;

	glm::mat4 MramieL = Mtors;
	MramieL = glm::translate(MramieL, glm::vec3(0.099636f, 0.59486f, 0.016287f));
	MramieL = glm::rotate(MramieL, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MramieL = glm::translate(MramieL, glm::vec3(-0.099636f, -0.59486f, -0.016287f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[0]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MramieL));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_ramieL);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_ramieL); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_ramieL); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_ramieL); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_ramieL); //Narysuj obiekt


	// PRAWE PRZEDRAMIE
	animation_angle = (.4f * sin(angle_y) + .2f) * walk_scale;
	
	glm::mat4 MprzedramieR = MramieR;
	MprzedramieR = glm::translate(MprzedramieR, glm::vec3(0.104158f, 0.495254f, 0.015044f));
	MprzedramieR = glm::rotate(MprzedramieR, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MprzedramieR = glm::translate(MprzedramieR, glm::vec3(-0.104158f, -0.495254f, -0.015044f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[1]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MprzedramieR));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_przedramieR);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_przedramieR); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_przedramieR); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_przedramieR); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_przedramieR); //Narysuj obiekt


	// LEWE PRZEDRAMIE
	animation_angle = (.4f * -sin(angle_y) + .2f) * walk_scale;
	
	glm::mat4 MprzedramieL = MramieL;
	MprzedramieL = glm::translate(MprzedramieL, glm::vec3(-0.104158f, 0.495254f, 0.015044f));
	MprzedramieL = glm::rotate(MprzedramieL, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MprzedramieL = glm::translate(MprzedramieL, glm::vec3(0.104158f, -0.495254f, -0.015044f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[0]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MprzedramieL));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_przedramieL);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_przedramieL); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_przedramieL); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_przedramieL); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_przedramieL); //Narysuj obiekt


	// PRAWE UDO
	animation_angle = (.3f * -sin(angle_y) + .1f) * walk_scale;
	
	glm::mat4 MudoR = Mbiodra;
	MudoR = glm::translate(MudoR, glm::vec3(0.046454f, 0.378301f, -0.023791f));
	MudoR = glm::rotate(MudoR, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MudoR = glm::translate(MudoR, glm::vec3(-0.046454f, -0.378301f, 0.023791f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[1]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MudoR));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_udoR);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_udoR); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_udoR); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_udoR); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_udoR); //Narysuj obiekt


	// LEWE UDO
	animation_angle = (.3f * sin(angle_y) + .1f) * walk_scale;
	
	glm::mat4 MudoL = Mbiodra;
	MudoL = glm::translate(MudoL, glm::vec3(-0.046454f, 0.378301f, -0.023791f));
	MudoL = glm::rotate(MudoL, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MudoL = glm::translate(MudoL, glm::vec3(0.046454f, -0.378301f, 0.023791f));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[0]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MudoL));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_udoL);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_udoL); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_udoL); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_udoL); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_udoL); //Narysuj obiekt


	// PRAWA NOGA
	animation_angle = (.3f * -sin(angle_y) + -0.3f) * walk_scale;
	
	glm::mat4 MnogaR = MudoR;
	MnogaR = glm::translate(MnogaR, glm::vec3(0.060846, 0.234132, 0.002016));
	MnogaR = glm::rotate(MnogaR, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MnogaR = glm::translate(MnogaR, glm::vec3(-0.060846, -0.234132, -0.002016));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[1]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MnogaR));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_nogaR);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_nogaR); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_nogaR); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_nogaR); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_nogaR); //Narysuj obiekt


	// LEWA NOGA
	animation_angle = (.3f * sin(angle_y) + -0.3f)* walk_scale;
	
	glm::mat4 MnogaL = MudoL;
	MnogaL = glm::translate(MnogaL, glm::vec3(-0.060846, 0.234132, 0.002016));
	MnogaL = glm::rotate(MnogaL, animation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	MnogaL = glm::translate(MnogaL, glm::vec3(0.060846, -0.234132, -0.002016));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tex[0]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(MnogaL));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_nogaL);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_nogaL); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_nogaL); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_nogaL); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_nogaL); //Narysuj obiekt


	//kamien1

	glm::mat4 Mkam1 = M;
	Mkam1 = glm::translate(Mkam1, glm::vec3(obstacles[0][0]+.5f, 2.0f, obstacles[0][1]+.5f) / 10.0f);
	Mkam1 = glm::scale(Mkam1, glm::vec3(obstacles[0][2]/13));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[4]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mkam1));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_kamien1);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_kamien1); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_kamien1); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_kamien1); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_kamien1); //Narysuj obiekt


	//kamien2

	glm::mat4 Mkam2 = M;
	Mkam2 = glm::translate(Mkam2, glm::vec3(obstacles[1][0], 2.0f, obstacles[1][1]) / 10.0f);
	Mkam2 = glm::scale(Mkam2, glm::vec3(obstacles[1][2] / 15));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[4]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mkam2));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_kamien2);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_kamien2); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_kamien2); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_kamien2); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_kamien2); //Narysuj obiekt


	//lawka

	glm::mat4 Mlaw1 = M;
	Mlaw1 = glm::translate(Mlaw1, glm::vec3(obstacles[2][0], 0.0f, obstacles[2][1]) / 10.0f);
	Mlaw1 = glm::rotate(Mlaw1, PI*0.75f, glm::vec3(0.0f, 1.0f, 0.f));
	Mlaw1 = glm::scale(Mlaw1, glm::vec3(obstacles[2][2] / 5));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[6]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[7]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mlaw1));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_lawka);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_lawka); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_lawka); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_lawka); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_lawka); //Narysuj obiekt


	//lampa 1

	glm::mat4 Mlamp1 = M;
	Mlamp1 = glm::translate(Mlamp1, glm::vec3(obstacles[3][0], 0.0f, obstacles[3][1]) / 10.0f);
	Mlamp1 = glm::scale(Mlamp1, glm::vec3(obstacles[3][2] / 16));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[3]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mlamp1));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_lampa);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_lampa); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_lampa); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_lampa); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_lampa); //Narysuj obiekt


	//lampa 2

	glm::mat4 Mlamp2 = M;
	Mlamp2 = glm::translate(Mlamp2, glm::vec3(obstacles[4][0], 0.0f, obstacles[4][1]) / 10.0f);
	Mlamp2 = glm::scale(Mlamp2, glm::vec3(obstacles[4][2] / 16));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[3]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mlamp2));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_lampa);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_lampa); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_lampa); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_lampa); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_lampa); //Narysuj obiekt


	//lampa 3

	glm::mat4 Mlamp3 = M;
	Mlamp3 = glm::translate(Mlamp3, glm::vec3(obstacles[5][0], 0.0f, obstacles[5][1]) / 10.0f);
	Mlamp3 = glm::scale(Mlamp3, glm::vec3(obstacles[5][2] / 16));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[3]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mlamp3));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords_lampa);
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices_lampa); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors_lampa); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals_lampa); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, vertexCount_lampa); //Narysuj obiekt


	// PODŁOGA
	glm::mat4 Mground = M;
	Mground = glm::translate(Mground, glm::vec3(0.0f, -0.1f, 0.0f));
	Mground = glm::scale(Mground, glm::vec3(3.5f, 0.1f, 3.5f));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[2]);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mground));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myCubeTexCoords);
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices); //Wskaż tablicę z danymi dla atrybutu vertex
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myCubeColors); //Wskaż tablicę z danymi dla atrybutu color
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myCubeNormals); //Wskaż tablicę z danymi dla atrybutu normal
	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount); //Narysuj obiekt

	
	//KONIEC
	glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("texCoord0"));
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "( ͠° ͟ʖ ͡°)", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x=0; //Aktualny kąt obrotu obiektu
	float angle_y=0; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle_x+=speed_x*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        angle_y+=speed_y*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki

		// pozycjonowanie robota
		robot_z_cor -= 2*speed_y*cos(robot_look_angle)/500;
		robot_x_cor -= 2*speed_y*sin(robot_look_angle)/500;
		// kolizje
		for (int i = 0; i < obstacles.size(); i++) {
			float d = sqrt(pow(robot_x_cor*10 - obstacles[i][0], 2) + pow(robot_z_cor*10 - obstacles[i][1], 2));
			if (d <= obstacles[i][2]) {
				//cofnięcie ruhcu
				//std::cout << "1:  " << d << std::endl;
				robot_z_cor += 2*speed_y * cos(robot_look_angle) / 500;
				robot_x_cor += 2*speed_y * sin(robot_look_angle) / 500;
				break;
			}
		};
		robot_look_angle = -2*angle_x;

		// pozycjonowanie kamery
		zoom -= cam_speed_y*glfwGetTime() / 1;
		float lower=0.5f, upper=6.0f;
		zoom = zoom <= lower ? lower : zoom >= upper ? upper : zoom;
		cam_angle_shift -= cam_speed_x* glfwGetTime() / 1;

		// SMOOTH animacja chodzenia
		if (speed_y > 0) {
			walk_scale = walk_scale + (1 - walk_scale) * 0.2; // <--- 0.5 ustawia płynność
		}
		else if (speed_y < 0) {
			walk_scale = walk_scale - (-1 + walk_scale) * 0.2; // <--- 0.5 ustawia płynność
		}
		else {
			walk_scale = walk_scale * 0.8; // <--- 0.5 ustawia płynność
		}
		//zerownaie animajci chodzenia
		if (abs(walk_scale) < 0.01) {
			//angle_y = 0.0f;
			walk_scale = 0.0f;
		}

		// SMOOTH obrót przy chodzeniu
		if (speed_x < 0) {
			rotate_scale = rotate_scale + (1 - rotate_scale) * 0.2; // <--- 0.5 ustawia płynność
		}
		else if (speed_x > 0) {
			rotate_scale = rotate_scale + (-1 - rotate_scale) * 0.2; // <--- 0.5 ustawia płynność
		}
		else {
			rotate_scale = rotate_scale * 0.8; // <--- 0.5 ustawia płynność
		}
		//zerownaie obrotu przy chodzeniu
		if (abs(rotate_scale) < 0.01) {
			//angle_x = 0.0f;
			rotate_scale = 0.0f;
		}

        glfwSetTime(0); //Zeruj timer
		drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
