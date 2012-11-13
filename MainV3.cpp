//Este codigo sirve para saber cuando hay una collision con cualquier 
//objeto.
#include "DarkGDK.h"
#include "Juego.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <dinput.h>
using namespace std;

// the main entry point for the application is this function

void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate (60);
	dbDisableEscapeKey ( );
	dbSetWindowTitle("Pollos Voladores");
	
	dbSetDisplayMode(1300,628,32);
	dbSetImageColorKey(255,0,255);//Define el contorno de la imagen
	dbDrawSpritesFirst(); 
	dbLoadImage("BackGround2.bmp",1);		
	dbSprite(1,0,0,1); //BackGround
	
	dbShowMouse();	

	/* Instancia Objeto Mundo */
	
	Juego juego;
	//juego.CargarFigurasTxt();
	//juego.PintarFiguras();

	double resultado,h,k;

	while (LoopGDK())
	{
		juego.MensajeJuego();
		dbCircle(300,530,50);
		
		/* Num1 Carga El pollo Para Lanzar  */
		if (dbKeyState(0x02) == 1)
		{
			while(dbKeyState(0x02) == 1);
			juego.CargarPolloLanzar();

		}
		
		/* Num2 Dispara el Ave */
		if (dbKeyState(0x03) == 1)
		{
			while(dbKeyState(0x03) == 1);
			juego.MovProyectilPollo();
		}

		/* Num3 Decrementa Angulo del Ave*/
		if (dbKeyState(0x04) == 1) 
		{
			juego.DecrementarRotacionAve();
		}	
		
		if (dbMouseClick()==1)
		{
			int pointX=dbMouseX();
			int pointY=dbMouseY();
			juego.VerificarMousePos(pointX,pointY,1);

		}

		if (dbMouseClick() == 2) //El clic derecho del Mouse permite Rotar al Pollo
		{
			int pointX=dbMouseX();
			int pointY=dbMouseY();
			juego.VerificarMousePos(pointX,pointY,2);
		}
		
		if (dbKeyState(0x1C) == 1)
		{
			while (dbKeyState(0x1C) == 1);
			juego.ReiniciarJuego();

		}
		
		if (dbLeftKey() == 1)
		{
			while (dbLeftKey() == 1);
			juego.MenuMundoIzquierda();
		}
		
		if (dbRightKey() == 1)
		{
			while (dbRightKey() == 1);
			juego.MenuMundoDerecha();
		}
		dbSync();
	}
	return;
}