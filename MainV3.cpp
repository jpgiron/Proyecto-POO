//Este codigo sirve para saber cuando hay una collision con cualquier 
//objeto.
#include "DarkGDK.h"
#include "pollo.h"
#include "figura.h"
#include "obstaculo.h"
#include "Juego.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

// the main entry point for the application is this function

void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate (60);
	dbDisableEscapeKey ( );
	dbSetWindowTitle("Happy Chicken");
	
	//cargar imagenes/sprites
	dbSetDisplayMode(1300,628,32);
	dbSetImageColorKey(255,0,255);//Define el contorno de la imagen
	
	//cargar imagen
	dbDrawSpritesFirst(); 
	dbLoadImage("BackGround2.bmp",4);
	dbLoadImage("PolloVolador2.bmp",1);
	dbLoadImage("obstaculoMadera.bmp",2);
	dbLoadImage("obstaculoMaderaAcostado.bmp",3);
	
		
	dbSprite(1,0,0,4); //BackGround
	
	dbShowMouse();	

	/* Instancia Objeto Mundo */
	
	Juego juego;

	/* Instancia Objetos Del Mundo */
	/*pollo		*pollo1	=	new pollo(1,5,124,422);
	pollo		*pollo2	=	new pollo()


	obstaculo	*ob1	=	new obstaculo(2,2,392,179);
	obstaculo	*ob2	=	new obstaculo(3,3,412,159);
	obstaculo	*ob3	=	new obstaculo(2,4,453,179);
	
	juego.AgregarFigura(pollo1);
	juego.AgregarFigura(ob1);
	juego.AgregarFigura(ob2);
	juego.AgregarFigura(ob3);*/

	pollo		*pollo1	=	new pollo(1,5,143,510);
	pollo		*pollo2	=	new pollo(1,6, 50,585);
	pollo		*pollo3	=	new pollo(1,7,	1,585);


	obstaculo	*ob1	=	new obstaculo(2,2,392,179);
	obstaculo	*ob2	=	new obstaculo(3,3,412,159);
	obstaculo	*ob3	=	new obstaculo(2,4,453,179);
	
	juego.AgregarFigura(pollo1);
	juego.AgregarFigura(pollo2);
	juego.AgregarFigura(pollo3);
	juego.AgregarFigura(ob1);
	juego.AgregarFigura(ob2);
	juego.AgregarFigura(ob3);
	
	juego.PintarFiguras();
	

	double resultado,h,k;

	while (LoopGDK())
	{
		
		if (dbKeyState(12)==1)
		{
			juego.MovProyectilPollo();
		}
		dbCircle(100,400,50);
		
		
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
	for(int i=1;i<10;i++){
		dbDeleteImage(i);
		dbDeleteSprite(i);
	}
	return;
}