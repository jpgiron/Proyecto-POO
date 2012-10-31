#include "Juego.h"

Juego::Juego(void)
{
	CantidadPollos	=	0; //Solo hay un pollo en el Mundo
	Puntos			=	0;

	//Las imagenes hacen parte del Juego
	dbLoadImage ( "PolloVolador2.bmp",			2);
	dbLoadImage ( "alcon.bmp",					3);
	dbLoadImage ( "ornitorrinco.bmp",			4);
	dbLoadImage	( "obstaculoMadera.bmp",		5);
	dbLoadImage ( "obstaculoMaderaAcostado.bmp",6);
	dbLoadImage ( "Huevo.bmp",					7);

}

Juego::~Juego(void)	
{
	for(int k = 0 ; k<(int) Figuras.size() ; k++){
		dbDeleteImage(k);
		dbDeleteSprite(k);
	}
}

/* Agrega un objeto derivado de Figura en el Vector Figuras   */

void Juego::AgregarFigura(figura* OBJETO)   
{
	pareja Temp;
    Figuras.push_back(OBJETO); //Agrega una Figura al mundo.
	Temp=OBJETO->getCoord();   //obtiene las Coordenadas e cada Figura
	ParejasPos.push_back(Temp);
}

/*  Pinta en el Mundo Las Figuras Cargadas   */
void Juego::PintarFiguras()
{
	int i = 0;
	for(;i <(int) Figuras.size();i++)
	{
		Figuras.at(i)->dibujar();
		
	}

}

/*  Carga las Figuras desde un archivo TXT. el orden del archivo es :

	ID_Sprite(int) ID_Imagen(int) CoordX(int) CoordY(int) Identificador(string)*/

void Juego::CargarFigurasTxt()
{

	int posx;
	int posy;
	int IDSprite;
	int IDImage;
	string TipoObjeto;
	ifstream Map("Mundo2.txt");

	while(!Map.eof())
	{
		Map >> IDSprite >> IDImage >> posx >> posy >> TipoObjeto;
		if (TipoObjeto == "Pollo")
		{
			AgregarFigura(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
			Pollos.push_back(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
			CantidadPollos++;
		}
		if (TipoObjeto == "Obstaculo")
		{
			AgregarFigura(new obstaculo(IDImage,IDSprite,posx,posy,TipoObjeto));

		}

	}
	
	Map.close();

}

/* ACtualiza los puntos obtenidos en el juego  */

void Juego::SumarPuntos(int Puntos)
{

	this->Puntos+=Puntos;
	MostrarPuntaje();
}

/* Muestra el Puntaje en Pantalla  */

void Juego::MostrarPuntaje()
{
	char string[200];
	sprintf ( string, "Puntaje= %d", Puntos );
	dbText (650,600, string );
	dbSetTextSize(30);
	
}

/* Actualiza la Posicion del Pollo */

void Juego::MoverPollo(int iX,int iY,int IDSprite)
{

	/*Figuras.at(0)->setCoords(iX,iY);
	Figuras.at(0)->moveBird();*/
	Pollos.at(IDSprite)->setCoords(iX,iY);
	Pollos.at(IDSprite)->moveBird();
		
}

/* Actualiza el Angulo de disparo del Pollo */

void Juego::RotarPollo(int IDSprite)
{
	
	//Figuras.at(0)->rotateBird();
	Pollos.at(IDSprite)->rotateBird();
}

/* Verifica si la posicion del Mouse esta dentro de un Objeto Pollo  */

void Juego::VerificarMousePos(int iX,int iY,int iBoton)
{
	/*
	pareja P=Figuras.at(0)->getCoord();
	
	int posx,posy;
	posx=P.first;
	posy=P.second;*/
	double resultado;
	int ptr=0;
	int cPollos;
	cPollos = (int) Pollos.size()-CantidadPollos;
	if (CantidadPollos > 0)
	{
		pareja P=Pollos.at(cPollos)->getCoord();
		int posx,posy;
		posx=P.first;
		posy=P.second;
		if (iX>=posx-24 && iY >=posy-22 && iX <=posx+24 && iY <=posy+22 )
		{
			
			/*  Calcula Si el Bird esta dentro del circulo para lanzarse */
			double h=iX-100;
			double k=iY-400;
			resultado=pow(h,2)+pow(k,2);
			double radio=pow((double) 50,2);
			if (resultado<=radio)
			{
				if (iBoton==1)
				{
					MoverPollo(iX,iY,cPollos);
				}
				if (iBoton==2)
				{
					RotarPollo(cPollos);
				}
			}
			
		}
	}
}

/* Mueve el Pollo Con un movimiento Proyectil dependiendo del angulo y la velocidad Obtenida */

void Juego::MovProyectilPollo()
{
	int i=0;
	int y;
	int PosXo,PosYo;
	float Vo, Angle;
	pareja P;
	int Verificar;
	int cPollos;
	cPollos = (int) Pollos.size()-CantidadPollos;
	if (CantidadPollos > 0 ) //Se ejecuta Si hay Pollo en El juego.
	{
		//Vo    = Figuras.at(0)->calculoVelocidad();
		//Angle = Figuras.at(0)->calculoAngulo();
		//P   = Figuras.at(0)->getCoord();
		Angle = Pollos.at(cPollos)->calculoAngulo();
		Vo	  = Pollos.at(cPollos)->calculoVelocidad();
		P     = Pollos.at(cPollos)->getCoord();
		
		PosXo = P.first+22;								//22 representa la distancia del vertice superior izquiero al centro en x
		PosYo = P.second+22;							//22 representa la distancia del vertice superior izquiero al centro en Y
		
		for ( ; i<PIXEL ; i+=4)
		{
			y = MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle);
			MostrarPuntaje();
			//P = Figuras.at(0)->getCoord();
			P = Pollos.at(cPollos)->getCoord();
			Verificar = VerificarColisionObjetos(P);
					
			if (Verificar == -1)  // -1 significa que no colisiono con nada
			{
				MoverPollo(i+124,y,cPollos);
			}

			else                  // Elimina las Figuras que Colisionaron
			{
				//dbDeleteSprite(Figuras.at(0)->RetornarIDSprite());
				//dbDeleteSprite(Figuras.at(Verificar)->RetornarIDSprite());
				dbDeleteSprite(Pollos.at(cPollos)->RetornarIDSprite());
				dbDeleteSprite(Figuras.at(Verificar)->RetornarIDSprite());
				SumarPuntos(500);
				MostrarPuntaje();
				return;
			}
			
		}
	}
}

/* Verifica si algun objeto del vector Pollo Collisiona con un obstaculo o con un Huevo */

int Juego::VerificarColisionObjetos(pareja PosPollo) //Retorna un entero que representa la ubicacion de la Figura con la que el pollo Colisiono
{
	int i=1;
	int cPollos;
	cPollos = (int) Pollos.size()-CantidadPollos;
	for ( ; i < (int) Figuras.size() ; i++ )
	{
		int ID;
		ID = Figuras.at(i)->RetornarIDSprite();
		
		if ( dbSpriteCollision(cPollos,ID) == 1 )
		{
			
			return i;
		}
	}
	return -1;
	
}

void Juego::CargarPolloLanzar()
{
	int cPollos;
	cPollos = (int) Pollos.size()-CantidadPollos; //Selecciona un Pollo a la vez del Vector Pollos
	//if (( cPollos - CantidadPollos ) == 0 )
	//{

	MoverPollo(300,530,cPollos);
	CantidadPollos--;
	char string[200];
	sprintf ( string, "CantidadP= %d SizeV = %d",CantidadPollos,(int) Pollos.size());
	dbText (650,600, string );
	dbSetTextSize(30);

}