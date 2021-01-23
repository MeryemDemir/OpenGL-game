#include "iostream"
#include "cstdlib"
#include "glew.h"
#include "freeglut.h"
#include "array"
#include "String"

using namespace std;

int width = 480, height = 640; //pencere genisligi ve yuksekligi
int a = 240; int b = 480; //ucagin baslangic x konumu ,ucagin baslangic y konumu(sol ust (0,0))
static int perm = 1; //helikopter pervane hareketi
static int skor = 0;
static int zorluk = 0;
static int can = 3;
bool dongu = true;
//helikopter random x kordinatlari
static int xa = rand() % 420; static int xb = rand() % 420; static int xc = rand() % 420; static int xd = rand() % 420;

//helikopter y kordinatlari
int ya = 50; int yb = 150; int yc = 250; int yd = 350;

//helikopter yonleri
static int yona = rand() % 2; static int yonb = rand() % 2; static int yonc = rand() % 2; static int yond = rand() % 2;

//helikopter hizlari
static int hiza = rand() % 4 + 1; static int hizb = rand() % 4 + 1; static int hizc = rand() % 4 + 1; static int hizd = rand() % 4 + 1;

//helikopter renkleri 
array <float, 3> randomRenk()
{
	float r1 = rand() % 100;
	float r2 = rand() % 100;
	float r3 = rand() % 100;
	array<float, 3> r = { r1 / 100,r2 / 100,r3 / 100 };
	return r;
}
array <float, 3> renka = randomRenk(); array < float, 3> renkb = randomRenk(); array < float, 3> renkc = randomRenk(); array < float, 3> renkd = randomRenk();

//verilen rakamin aranilan aralikta olup olmadigini kontrol ediyor.
bool inRange(unsigned alt, unsigned ust, unsigned x)
{
	return  ((x - alt) <= (ust - alt));
}
//ekrana yazi yazar (yapilacak)
void yazilar()
{
	string str;
	if (!dongu)
	{
		str = "Tekrar dene Enter";
		glRasterPos2i(170, 300);
		for (int i = 0; i < str.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
		str = "Skor : " + to_string(skor);
		glRasterPos2i(170, 350);
		for (int i = 0; i < str.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}

	}
	else if (dongu)
	{
		str = "Skor: " + to_string(skor) + " Kalan Hak: " + to_string(can);
		glRasterPos2i(240, 40);
		for (int i = 0; i < str.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		}
	}
}
//ucak cizer
void ucak(int x, int y)
{
	glBegin(GL_POLYGON);
	glVertex2i(x - 3, y);
	glVertex2i(x - 3, y + 50);
	glVertex2i(x + 3, y + 50);
	glVertex2i(x + 3, y);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x - 25, y + 10);
	glVertex2i(x + 25, y + 10);
	glVertex2i(x + 25, y + 16);
	glVertex2i(x - 25, y + 16);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x - 15, y + 35);
	glVertex2i(x + 15, y + 35);
	glVertex2i(x + 15, y + 41);
	glVertex2i(x - 15, y + 41);
	glEnd();
}

//helikopter cizer
void helikopter(int x, int y, array <float, 3> renk)
{
	//helikopter hareket
	glColor3f(renk[0], renk[1], renk[2]);
	glBegin(GL_POLYGON);
	glVertex2i(x, y + 10);
	glVertex2i(x, y + 20);
	glVertex2i(x + 30, y + 20);
	glVertex2i(x + 30, y + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x + 30, y);
	glVertex2i(x + 60, y);
	glVertex2i(x + 60, y + 30);
	glVertex2i(x + 30, y + 30);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(x + 35, y + 30);
	glVertex2i(x + 35, y + 35);
	glVertex2i(x + 37, y + 35);
	glVertex2i(x + 37, y + 30);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(x + 55, y + 30);
	glVertex2i(x + 55, y + 35);
	glVertex2i(x + 57, y + 35);
	glVertex2i(x + 57, y + 30);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(x + 30, y + 35);
	glVertex2i(x + 30, y + 37);
	glVertex2i(x + 60, y + 37);
	glVertex2i(x + 60, y + 35);
	glEnd();
	glColor4f(0, 0.5, 0.5, 0.3);//camin rengi
	glBegin(GL_POLYGON);
	glVertex2i(x + 45, y + 5);
	glVertex2i(x + 55, y + 5);
	glVertex2i(x + 55, y + 20);
	glVertex2i(x + 45, y + 20);
	glEnd();
	glColor3f(renk[0], renk[1], renk[2]);
	glBegin(GL_POLYGON);
	glVertex2i(x + 44, y);
	glVertex2i(x + 44, y - 6);
	glVertex2i(x + 46, y - 6);
	glVertex2i(x + 46, y);
	glEnd();
	//ust pervaneler
	if (perm % 2 == 1)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 17, y - 16);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 73, y - 16);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 17, y + 6);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 73, y + 6);
		glEnd();
	}
	else
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 15, y - 6);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 75, y - 6);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 45, y + 11);
		glVertex2i(x + 45, y - 6);
		glVertex2i(x + 45, y - 17);
		glEnd();
	}
	//kuyruk
	if (perm % 2 == 1)
	{
		glBegin(GL_LINES);
		glVertex2i(x, y + 15);
		glVertex2i(x - 10, y + 5);
		glVertex2i(x, y + 15);
		glVertex2i(x - 10, y + 25);
		glVertex2i(x, y + 15);
		glVertex2i(x + 10, y + 5);
		glVertex2i(x, y + 15);
		glVertex2i(x + 10, y + 25);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		glVertex2i(x, y + 15);
		glVertex2i(x + 14, y + 15);
		glVertex2i(x, y + 15);
		glVertex2i(x - 14, y + 15);
		glVertex2i(x, y + 15);
		glVertex2i(x, y + 29);
		glVertex2i(x, y + 15);
		glVertex2i(x, y + 1);
		glEnd();
	}
}

//verilen noktanin helikopterlerin alani icinde olup olmadigini kontrol eder
bool carpismaDet(int a, int b)
{
	if (inRange(xa, xa + 50, a) && inRange(ya, ya + 50, b)
		|| inRange(xb, xb + 50, a) && inRange(yb, yb + 50, b)
		|| inRange(xc, xc + 50, a) && inRange(yc, yc + 50, b)
		|| inRange(xd, xd + 50, a) && inRange(yd, yd + 50, b))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//ucak bitise ulastiginda veya helikoptere carptiginda calisir
void ucakReset()
{
	//bitise ulasinca
	if (b < 5)
	{
		a = 240;
		b = 480;
		skor = skor + zorluk + 10; // zorluk arttikca daha fazla puan
		zorluk++;
	}
	//ucak burun carpisma
	if (carpismaDet(a, b))
	{
		a = 240;
		b = 480;
		can--;
	}
	//ucak sag kanat carpma
	else if (carpismaDet(a + 25, b + 13))
	{
		a = 240;
		b = 480;
		can--;
	}
	//ucak sol kanat carpma
	else if (carpismaDet(a - 25, b + 13))
	{
		a = 240;
		b = 480;
		can--;
	}
	else if (carpismaDet(a - 15, b + 35))
	{
		a = 240;
		b = 480;
		can--;
	}
	else if (carpismaDet(a + 15, b + 35))
	{
		a = 240;
		b = 480;
		can--;
	}
	else if (carpismaDet(a, b + 50))
	{
		a = 240;
		b = 480;
		can--;
	}
	if (can == 0)
	{
		dongu = false;
	}
}



//helikopterin ekran sinirlari icinde olup olmadiginin kontrolu
bool heliInScreen(int x)
{
	if (x + 60 < 480 && x > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//helikopter hareketi ve ekran sinirlarina geldiginde yon degistirme
int heliMove(int x, int &yon, int hiz)
{
	if (yon == 0)
	{
		x = x + (hiz + zorluk);
		if (!heliInScreen(x))yon = 1;
		return x;
	}
	else if (yon == 1)
	{
		x = x - (hiz + zorluk);
		if (!heliInScreen(x))yon = 0;
		return x;
	}
	else
	{
		return x;
	}
}

//glutIdleFunc ile programin duraksamadan calismasini saglar ve zamana bagli eylemleri gerceklestirir
void idle()
{
	perm++;
	xa = heliMove(xa, yona, hiza);
	xb = heliMove(xb, yonb, hizb);
	xc = heliMove(xc, yonc, hizc);
	xd = heliMove(xd, yond, hizd);
	Sleep(20);
	ucakReset();
	glutPostRedisplay();
}

//dongu sirasinda ekran ciktisi
void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	switch (dongu)
	{
	case true:
		yazilar();
		ucakReset();
		ucak(a, b);
		helikopter(xa, ya, renka);
		helikopter(xb, yb, renkb);
		helikopter(xc, yc, renkc);
		helikopter(xd, yd, renkd);
	case false:
		yazilar();
	}
	glFlush();
	glutSwapBuffers();
}

//Ok tuslari ile ucagin hareketi ve ekran sinirlari kontrolu 
void klavye(int key, int x, int y)
{

	ucakReset();
	if (key == GLUT_KEY_UP)
	{
		if (b > 0)
		{
			b -= 5;
			glutPostRedisplay();
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (b < height - 50)
		{
			b += 5;
			glutPostRedisplay();
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (a > 25)
		{
			a -= 5;
			glutPostRedisplay();
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (a < width - 25)
		{
			a += 5;
			glutPostRedisplay();
		}
	}
}

//enter yeniden baslar
void retry(unsigned char key, int x, int y)
{
	if (key == 13)
	{
		if (!dongu)
		{
			dongu = true;
			can = 3;
			skor = 0;
			zorluk = 0;
			a = 240;
			b = 480;
		}
		glutPostRedisplay();
	}
}

//cizim alani ve arka plan rengi
void init()
{
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(0, width, height, 0);
}

//main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("160313038 - Meryem Nur - Demir");
	init();
	glutSpecialFunc(klavye);
	glutKeyboardFunc(retry);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}