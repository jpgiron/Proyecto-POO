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
	//dbSetWindowOn();
	//dbMaximizeWindow();
	//cargar imagen
	dbDrawSpritesFirst(); 
	dbLoadImage("BackGround2.bmp",1);		
	dbSprite(1,0,0,1); //BackGround
	
	dbShowMouse();	

	/* Instancia Objeto Mundo */
	
	Juego juego;
	juego.CargarFigurasTxt();
	juego.PintarFiguras();
	

	double resultado,h,k;

	while (LoopGDK())
	{
		juego.MostrarPuntaje();
		juego.MensajeJuego();
		if (dbKeyState(0x02) == 1)
		{
			while(dbKeyState(0x02) == 1);
			juego.CargarPolloLanzar();

		}

		if (dbKeyState(0x03) == 1)
		{
			while(dbKeyState(0x03) == 1);
			juego.MovProyectilPollo();
		}
		dbCircle(300,530,50);
		
		
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


		dbSync();
		
	}
	
	return;
}