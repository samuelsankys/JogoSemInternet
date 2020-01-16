#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

GLfloat tx = -40, ty = -12 ;
GLfloat mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=8, nx =500, nx1= 800;
GLfloat win = 25;
GLint temp = 30, auxpause=0;
GLint estado = 0;
char texto[30];

GLfloat wine, r, g, b;

GLfloat pontuacao=0.0, aux;

GLint win_width, win_height;
GLuint DataPos, imageSize;
GLsizei Width,Height;
GLuint texture_id[1];
GLfloat xf, yf,winw, aspecto;





void jogo();
void iniciando();
void comandos();
void SobreJogo();


void DesenhaTexto(void *font, char *string) 
{
	// Exibe caractere a caractere
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++); 
}
                     
void Timer(int value)
{
    mx = mx-1;
    mx2 = mx2-1;
    mx3 = mx3-1;
    nx = nx-.6;
    nx1 = nx1-1.5;

    if(mx < -80)
        mx = 100;
    if(mx2 < -80)
        mx2 = 100;
    if(nx < -80)
    	nx = 100;
    if(nx1 <-80)
    	nx1 = 100;
    if(mx3 < -80){
        mx3 = 100;
        if(temp > 10)
            temp=temp-5;
    }
	pontuacao+=0.2;
	glutTimerFunc(temp,Timer,1);
    glutPostRedisplay();
}


void Pular2(int value)
{
    if(ty != -12){
        if(ty == 0){
            ty--;
            glutTimerFunc(50,Pular2,1);
    }else{
        ty--;
        glutTimerFunc(20,Pular2,1);
    }
    }

    glutPostRedisplay();
}

void GameOver()
{
    glColor3f(1,1,1);
    glRasterPos2f(30,10);
    char* p = (char*) "GAME OVER!!";
    
    while (*p != '\0')
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
    temp = 30;
    estado++;
    
}

void Pause()
{
    temp = 30;
    aux=pontuacao;
    estado++;
    
}

void Pular1(int value)
{
    if(ty < 0){
        ty++;
        glutTimerFunc(10,Pular1,1);
    }else if(ty == 0 || ty < 3)
    {
        ty++;
        glutTimerFunc(30,Pular1,1);
    }else
        glutTimerFunc(10,Pular2,1);

    glutPostRedisplay();
}


void Pontuacao()
{	
		glColor3f(0,0,0);
	
	glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    if(pontuacao > 0)
    	sprintf(texto, "Pontuacao: %.1f", pontuacao);

    
    glTranslatef(-58.0f, 22.0f,0.0f);
    glRasterPos2f(0,0);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,texto);
    glPopMatrix();

}


// Função para desenhar um obstaculo
void DesenhaObstaculo()
{
	glLineWidth(2);
	glBegin(GL_QUADS);
		glVertex2f(0,3);
		glVertex2f(0,-3);
		glVertex2f(3,-3);
		glVertex2f(3,3);
	glEnd();
	
}


void DesenhaPersonagem()
{
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(0.0,-3.0);
		glVertex2f(0.0,5.0);
	glEnd();

	
}


// Funçao que faz a colisão dos carros
void Colisao(GLint  x)
{
    float px = tx;
    float py = ty;

    float obx = x;
    float oby = my;
	
    if(px == x && py == oby)
	{
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+1 && py == oby)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+1 && py == oby+1)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+2 && py == oby+2)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x && py == oby+2)
    {
		pontuacao=0.0;
		GameOver(); 
	}else if(px == x && py == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}else if(px == x+1 && py == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
	else if(px == x+2 && py == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
	else if(px == x+3 && py == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
}


void Colisaosup(GLint  x)
{
    float px = tx;
    float py = ty;

    float obx = x;
    float oby = ny;
	
    if(px == x && py == oby)
	{
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+1 && py+8 == oby)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+1 && py+8 == oby+1)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x+2 && py+8 == oby+2)
    {
		pontuacao=0.0;
		GameOver(); 
	}
    else if(px == x && py+8 == oby+2)
    {
		pontuacao=0.0;
		GameOver(); 
	}else if(px == x && py+8 == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}else if(px == x+1 && py+8 == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
	else if(px == x+2 && py+8 == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
	else if(px == x+3 && py+8 == oby+3)
    {
		pontuacao=0.0;
		GameOver(); 
	}
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	


    if(estado == 0){
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();

	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o chão
	glLineWidth(3);
	glBegin(GL_QUADS);
        glColor3f(1.5f,1.25f,1.0f);
		glVertex2f(-100,-15);
		glVertex2f(100,-15);
		glColor3f(0.0f,0.0f,0.0f);
		glVertex2f(100,-30);
		glVertex2f(-100,-30);
	glEnd();


	// Desenha um objeto modelado com transformações hierárquicas
	glPushMatrix();
	glTranslatef(tx,ty,0.0f);

	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	DesenhaPersonagem();
    glPopMatrix();

   
    glPopMatrix();

   

    //Desenha obstaculos no chão

	glPushMatrix();
	glTranslatef(mx,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
	Colisao(mx);
    glPopMatrix();
  
    glPushMatrix();
	glTranslatef(mx2,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();	
    Colisao(mx2);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(mx3,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
	Colisao(mx3);
    glPopMatrix();
	
	
	    
    //Desenha obstaculos no céu
	
	glPushMatrix();
	glTranslatef(nx,ny,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
    Colisaosup(nx);
    glPopMatrix();

	glPushMatrix();
	glTranslatef(nx1,ny,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();	
    Colisaosup(nx1);
    glPopMatrix();
    
    
    // pontuação
    Pontuacao();
    
	// Executa os comandos OpenGL
	glutSwapBuffers();
    }
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior,
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura)
	{
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}
	else
	{
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;
	}
}



void TeclasEspeciais(int key, int x, int y)
{

	if(key == GLUT_KEY_UP)
	{
	    if(ty == -12)
            glutTimerFunc(20,Pular1,1);
	}

	glutPostRedisplay();
}



// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.10f, 0.77f, 1.0f, 1.0f);

}



///////////////////////////////////////////////////
void DesenhaTexto(char *string) 
{  
  	glPushMatrix();
        // Posição no universo onde o texto será colocado          
        glRasterPos2f(-win,win-(win*0.08)); 
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	glPopMatrix();
}


void AlteraTamanhoJanela2(GLsizei w, GLsizei h)
{ 
 
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-wine, wine, -wine, wine);
}

void TeclasEspeciais2(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           wine -= 10;
           if (wine < 10) wine = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-wine, wine, -wine, wine);
    }
    if(key == GLUT_KEY_DOWN) {
           wine += 10;
           if (wine > 500) wine = 500;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-wine, wine, -wine, wine);
    }
    glutPostRedisplay();
}

////////////////////////


 void LoadBMP(char *filename) {
    #define SAIR {fclose(fp_arquivo); return ;}
    #define CTOI(C) (*(int*)&C)
 
    GLubyte *image;
    GLubyte Header[0x54];
 
    FILE * fp_arquivo = fopen(filename,"rb");
 
    if (fread(Header,1,0x36,fp_arquivo)!=0x36)
    SAIR;
 
    Width = CTOI(Header[0x12]);
    Height = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    imageSize=Width*Height*3;
 
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
 
    int t, i;
    for ( i = 0; i < imageSize; i += 3 ) {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    fclose (fp_arquivo);
    free (image);
    return ;
}
 
void T_Quads(GLuint *t_quad, int i, int x, int y, int w, int h) {
    glBindTexture ( GL_TEXTURE_2D, t_quad[i] );
    glBegin(GL_QUADS);
 
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(x+w, y);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(x+w, y+h);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(x, y+h);
    glEnd();
}
 
void Draw(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("inicial.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}
void Draw2(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("comandos.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}
void Draw3(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("sobreojogo.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}
 
void Anima(int value) {
 
    glutPostRedisplay();
    glutTimerFunc(120,Anima, 1);
 
}
 
void MouseManager(int button, int state, int x, int y) {
 
    glutPostRedisplay();
}
 
void SpecialKeys(int key, int x, int y){
 
    glutPostRedisplay();
}
 
void ModifyWindownsSize(GLsizei w, GLsizei h) {
    if(h == 0) h = 1;
 
    win_width = w;
    win_height = h;
 
    aspecto = (float) win_width/win_height;
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    gluOrtho2D (-winw*aspecto, winw*aspecto, -winw, winw);
}
 
void Start (void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    winw = 50.0f;
}

//teclas
void Teclado( unsigned char key, int x, int y)
{
		
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'I':
		case 'i':
			iniciando();			
			break;
		case 13:
			tx = -40, ty = -12;
			mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=10 ,nx =500, nx1= 800;
			win = 25;
			temp = 30;
			estado = 0;
			pontuacao=0.0;
			break;	
		case 'P':
		case 'p':
			Pause();
			glutPostRedisplay();
			break;
		case 'R':
		case 'r':
		pontuacao=aux;
		estado=0;
			break;
		}	
		
	glutPostRedisplay();	
}

// Gerenciamento do menu principal           


void MenuPrincipal(int op)
{
	switch (op)
	{
		case 0: // iniciar
			tx = -40, ty = -12;
			mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=10 ,nx =500, nx1= 800;
			win = 25;
			temp = 30;
			estado = 0;
			pontuacao=0.0;

				jogo();		
				
			
			break;
		case 1: // Sobre o jogo
				
				SobreJogo();
			break;
		case 2: // comando
			
				comandos();
				break;
		case 3: 	// sair
				
		    exit(1);
			
			break;
	}
	  glutPostRedisplay();

}
              
// Criacao do Menu
void CriaMenu() 
{
    int menu,submenu1,submenu2;

	menu = glutCreateMenu(MenuPrincipal);
    glutAddMenuEntry("Iniciar",0);
    glutAddMenuEntry("Sobre o Jogo",1);
    glutAddMenuEntry("Comandos",2);
    glutAddMenuEntry("Sair",3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
   
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
            CriaMenu();
         
    glutPostRedisplay();
}

// jogo
	
void jogo()
{

			glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Sem internet");
			glutDisplayFunc(Desenha);
			glutReshapeFunc(AlteraTamanhoJanela);
			glutKeyboardFunc (Teclado);
			glutSpecialFunc(TeclasEspeciais);   
		    glutTimerFunc(60, Timer, 1);
			Inicializa();
			glutMainLoop();
			
					

}

// tela inicio

void iniciando()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
		    glutInitWindowPosition(5,5);
		    glutInitWindowSize(1200,500);
		    glutCreateWindow("Jogo sem Internet");
		    glutReshapeFunc(ModifyWindownsSize);
		    glutDisplayFunc(Draw);
		    glutMouseFunc(MouseManager);
		    glutSpecialFunc(SpecialKeys);
		    glutTimerFunc(150, Anima, 1);
		    Start();
			glutSpecialFunc(TeclasEspeciais2); 
			glutMouseFunc(GerenciaMouse);    
		    glutMainLoop();
}

void comandos()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Jogo sem Internet");
			glutDisplayFunc(Draw2);
			glutReshapeFunc(ModifyWindownsSize);
			glutMouseFunc(MouseManager);
			glutSpecialFunc(SpecialKeys);
			glutTimerFunc(150, Anima, 1);
			Start();
			glutSpecialFunc(TeclasEspeciais2);    
			glutKeyboardFunc (Teclado);
			glutMainLoop();	

}


void SobreJogo()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Jogo sem Internet");
			glutDisplayFunc(Draw3);
			glutReshapeFunc(ModifyWindownsSize);
			glutMouseFunc(MouseManager);
			glutSpecialFunc(SpecialKeys);
			glutTimerFunc(150, Anima, 1);
			Start();
			glutSpecialFunc(TeclasEspeciais2);    
			glutKeyboardFunc (Teclado);
			glutMainLoop();	

}


// Programa Principal
int main(int argc,char **argv)
{	
	glutInit(&argc,argv);
	iniciando();
    
	return 0;
}
