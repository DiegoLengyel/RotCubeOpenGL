#ifdef _WIN32
#include <GL/glut.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif*/
#include <iostream>
#include <math.h>
#include <stdlib.h> 
using namespace std;
int op;

#pragma region Variables Rotacion
GLfloat elevacion = 0;
GLfloat arco = 0;
GLfloat giro = 0;
#pragma endregion

#pragma region Variables Camara
GLfloat Camara[16];
//COP (4*7,4*7,4*7) = (28,28,28) 7 se refiere al ancho del cubo
//AT (0,0,0)
//UP (0,1,0)
#pragma endregion

#pragma region Variables Objeto3D
GLfloat vertice[8][3];//8 vertices 3 dimensiones (x,y,z)
GLint caras[6][4] = { {0,1,2,3},{3,2,6,7},{7,6,5,4},{4,5,1,0},{5,6,2,1},{7,4,0,3} }; //Conteo de caras 6 caras 4 aristas
GLint arista[12][2]; //12 vertices 2 aristas
GLfloat color[6][3]; //6 colores R G B
#pragma endregion

//Calculamos la camara que usara el programa
void MatrizVista() {
	Camara[0] = 1 / sqrt(2);
	Camara[1] = -(1 / sqrt(6));
	Camara[2] = 1 / sqrt(3);
	Camara[3] = 0;
	Camara[4] = 0;
	Camara[5] = sqrt(2 / 3);
	Camara[6] = 1 / sqrt(3);
	Camara[7] = 0;
	Camara[8] = -(1 / sqrt(2));
	Camara[9] = -(1 / sqrt(6));
	Camara[10] = 1 / sqrt(3);
	Camara[11] = 0;
	Camara[12] = -28 * sqrt(3);
	Camara[13] = -28 * sqrt(2);
	Camara[14] = ((28 * sqrt(2)) / sqrt(3)) - (28 * (sqrt(2 / 3)));
	Camara[15] = 1;
	glLoadMatrixf(Camara);
}

//Rellenamos las matrices con los puntos obtenidos
void Inicializar() {
#pragma region Vertices Objeto
	//Vertice # en x	//Vertice # en y	//Vertice # en z
	vertice[0][0] = -2;	vertice[0][1] = -2;	vertice[0][2] = 2;
	vertice[1][0] = 2;	vertice[1][1] = -2;	vertice[1][2] = 2;
	vertice[2][0] = 2;	vertice[2][1] = 2;	vertice[2][2] = 2;
	vertice[3][0] = -2;	vertice[3][1] = 2;	vertice[3][2] = 2;
	vertice[4][0] = -2;	vertice[4][1] = -2;	vertice[4][2] = -2;
	vertice[5][0] = 2;	vertice[5][1] = -2;	vertice[5][2] = -2;
	vertice[6][0] = 2;	vertice[6][1] = 2;	vertice[6][2] = -2;
	vertice[7][0] = -2;	vertice[7][1] = 2;	vertice[7][2] = -2;
#pragma endregion

#pragma region Colores Objeto
	//Para cada cara 1 color
	//Cara # R			//Cara # G			//Cara # B
	color[0][0] = 1;	color[0][1] = 0.6;	color[0][2] = 0.4;
	color[1][0] = 0.5;	color[1][1] = 1;	color[1][2] = 0.3;
	color[2][0] = 1;	color[2][1] = 0.4;	color[2][2] = 1;
	color[3][0] = 1;	color[3][1] = 0.2;	color[3][2] = 0.6;
	color[4][0] = 0.3;	color[4][1] = 1;	color[4][2] = 0.3;
	color[5][0] = 1;	color[5][1] = 0.2;	color[5][2] = 0.1;
#pragma endregion
}

#pragma region Rotacion Dinamica
void Rotacion(GLfloat distancia, GLfloat giro, GLfloat elevacion, GLfloat arco)
{
	glTranslated(0.0, 0.0, -distancia);
	glRotated(-giro, 0.0, 0.0, 1.0);
	glRotated(-elevacion, 1.0, 0.0, 0.0);
	glRotated(arco, 0.0, 0.0, 1.0);
}

void teclado(unsigned char op, int x, int y)
{
	switch (op) {
		//Mayusculas giro horario, x y z representan el eje de giro
	case 'X':
		elevacion = elevacion + 10.0f;
		glutPostRedisplay();
		break;
	case 'Y':
		arco = arco + 10.0f;
		glutPostRedisplay();
		break;
	case 'Z':
		giro = giro + 10.0f;
		glutPostRedisplay();
		break;
		//Minusculas giro anti-horario, x y z representan el eje de giro
	case 'x':
		elevacion = elevacion - 10.0f;
		glutPostRedisplay();
		break;
	case 'y':
		arco = arco - 10.0f;
		glutPostRedisplay();
		break;
	case 'z':
		giro = giro - 10.0f;
		glutPostRedisplay();
		break;
	}
}
//Funcion para rotar las cosas en pantalla
void iniciarRot()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	Rotacion(20, giro, elevacion, arco);
}
#pragma endregion

#pragma region Dibujo Objeto 3D
//Objeto en diferentes estados
void NubePuntos() {
#pragma region Dibujo ejes x y z 1
	iniciarRot();
	//Eje X
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	//Eje Y
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, -40, 0);
	glVertex3f(0, 40, 0);
	//Eje Z
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -40);
	glVertex3f(0, 0, 40);
	glEnd();
	glFlush();
#pragma endregion
	for (int i = 0; i < 6; i++)
	{
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3fv(&color[i][0]);
		glVertex3fv(&vertice[caras[i][0]][0]);
		glVertex3fv(&vertice[caras[i][1]][0]);
		glVertex3fv(&vertice[caras[i][2]][0]);
		glVertex3fv(&vertice[caras[i][3]][0]);
		glEnd();
		glFlush();
	}
}

void Alambres() {
#pragma region Dibujo ejes x y z 2
	iniciarRot();
	//Eje X
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-50, 0, 0);
	glVertex3f(50, 0, 0);
	//Eje Y
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, -50, 0);
	glVertex3f(0, 50, 0);
	//Eje Z
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -50);
	glVertex3f(0, 0, 50);
	glEnd();
	glFlush();
#pragma endregion
	for (int i = 0; i < 6; i++)
	{

		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3fv(&color[i][0]);
		glVertex3fv(&vertice[caras[i][0]][0]);
		glVertex3fv(&vertice[caras[i][1]][0]);
		glVertex3fv(&vertice[caras[i][2]][0]);
		glVertex3fv(&vertice[caras[i][3]][0]);
		glEnd();
		glFlush();
	}
}

void MallasPoligonales() {
#pragma region Dibujo ejes x y z 3
	iniciarRot();
	//Eje X
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-50, 0, 0);
	glVertex3f(50, 0, 0);
	//Eje Y
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, -50, 0);
	glVertex3f(0, 50, 0);
	//Eje Z
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -50);
	glVertex3f(0, 0, 50);
	glEnd();
	glFlush();
#pragma endregion
	for (int i = 0; i < 6; i++)
	{
		glBegin(GL_QUADS);
		glColor3fv(&color[i][0]);
		glVertex3fv(&vertice[caras[i][0]][0]);
		glVertex3fv(&vertice[caras[i][1]][0]);
		glVertex3fv(&vertice[caras[i][2]][0]);
		glVertex3fv(&vertice[caras[i][3]][0]);
		glEnd();
	}
}
#pragma endregion
//Funcion para iniciar modos de OpenGL
void Modos()
{
	//Color de fondo
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Para que opengl sepa de los vertices
	Inicializar();
	//No dibujamos las caras ocultas
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
}


void pantalla()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	MatrizVista();
	switch (op) {
	case 1:
		NubePuntos();
		break;
	case 2:
		Alambres();
		break;
	case 3:
		MallasPoligonales();
		break;
	default:
		break;
	}
	glFlush();
}

void ajuste(int ancho, int alto)
{
	glViewport(0, 0, (GLsizei)ancho, (GLsizei)alto);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)ancho / (float)alto, 1.0, 300.0);
	glFlush();
}

void Menu() {
	cout << "Escoge una de las 3 opciones:" << endl << endl;
	cout << "1. Nube de puntos" << endl;
	cout << "2. Modelo Alambrado" << endl;
	cout << "3. Modelo Solido" << endl;
	cout << endl << endl;
	cout << "Para girar el cubo, usas x y z (en el teclado)" << endl;
	cout << "en minusculas gira en sentido anti-horario" << endl;
	cout << "en mayusculas gira en sentido horario" << endl;
	cin >> op;
}

int main(int argc, char** argv)
{
	Menu();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(150, 150);
	glutCreateWindow(argv[0]);
	glutSetWindowTitle("Parcial Computacion Grafica Corte 2.");
	Modos();
	glutDisplayFunc(pantalla);
	glutReshapeFunc(ajuste);
	glutKeyboardFunc(teclado);
	glutMainLoop();
	return 0;
}