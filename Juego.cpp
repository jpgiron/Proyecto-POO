#include "Juego.h"

Juego::Juego(void)
{
	CantidadAves	=	0; 
	Puntos			=	0;
	CantidadHuevos	=	0;
	//Las imagenes hacen parte del Juego
	dbLoadImage ( "PolloVolador2.bmp",			2);
	dbLoadImage ( "alcon.bmp",					3);
	dbLoadImage ( "ornitorrinco.bmp",			4);
	dbLoadImage	( "obstaculoMadera.bmp",		5);
	dbLoadImage ( "obstaculoMaderaAcostado.bmp",6);
	dbLoadImage ( "Huevo.bmp",					7);
	dbLoadImage	( "Granja1.bmp",8);
	dbLoadImage	( "Granja2.bmp",9);
	dbLoadImage	( "Granja3.bmp",10);
	dbLoadImage	( "Granja4.bmp",11);
	dbLoadImage	( "Granja5.bmp",12);
	dbLoadImage	( "obstaculoPiedra.bmp",13);
	dbLoadImage ( "obstaculoPiedraAcostado.bmp",14);
	Mundo			=	0;	
	Jugando			=	false;
}

/* Share Pointer */

Juego::~Juego(void)	
{
	for(int k = 0 ; k<(int) Figuras.size() ; k++)
	{
		dbDeleteImage(k);
		dbDeleteSprite(k);
	}
	
}

/* Agrega un objeto derivado de Figura en el Vector Figuras   */

void Juego::AgregarFigura(figura* OBJETO)   
{
    Figuras.push_back(OBJETO); //Agrega una Figura al mundo.
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

void Juego::CargarFigurasTxt(string TipoMundo)
{	
	int posx;
	int posy;
	int IDSprite;
	int IDImage;
	const char *NombreArchivo;
	NombreArchivo = TipoMundo.c_str();
	string TipoObjeto;
	ifstream Map(NombreArchivo);

	while(!Map.eof())
	{
		Map >> IDSprite >> IDImage >> posx >> posy >> TipoObjeto;
		if (TipoObjeto == "Pollo")
		{
			//AgregarFigura(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
		}
		if (TipoObjeto == "Ornitorrinco")
		{
			//AgregarFigura(new Ornitorrinco(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new Ornitorrinco(IDImage,IDSprite,posx,posy,TipoObjeto));
		}

		if (TipoObjeto == "Aguila")
		{
			//AgregarFigura(new Aguila(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new Aguila(IDImage,IDSprite,posx,posy,TipoObjeto));
		}

		if (TipoObjeto == "Obstaculo" )
		{
			//AgregarFigura(new ParedMadera(IDImage,IDSprite,posx,posy,TipoObjeto));
			Enemigos.push_back(new ParedMadera(IDImage,IDSprite,posx,posy,TipoObjeto));
		}
		if (TipoObjeto == "ObstaculoP" )
		{
			//AgregarFigura(new ParedMadera(IDImage,IDSprite,posx,posy,TipoObjeto));
			Enemigos.push_back(new ParedCemento(IDImage,IDSprite,posx,posy,TipoObjeto));
		}
		if (TipoObjeto == "Huevo")
		{
			//AgregarFigura(new Huevo(IDImage,IDSprite,posx,posy,TipoObjeto));
			Enemigos.push_back(new Huevo(IDImage,IDSprite,posx,posy,TipoObjeto));
			CantidadHuevos++;
		}
		AgregarFigura(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
	}
	CantidadAves=(int) Aves.size();
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
	sprintf ( string, "Puntaje= %d",Puntos);
	dbText (650,600, string );
	dbSetTextSize(30);
}

/* Actualiza la Posicion del Pollo */

void Juego::MoverPollo(int iX,int iY)
{
	Aves.at(0)->setCoords(iX,iY);
	Aves.at(0)->moveBird();
}

/* Actualiza el Angulo de disparo del Pollo */

void Juego::RotarPollo()
{
	/* Condicion Necesaria Para para que el Ave solo tenga una rotacion de hasta 90 grados  */
	if (Aves.at(0)->RetornarAngulo() < 89)
	{
		Aves.at(0)->rotateBird();
	}
}

/* Verifica si la posicion del Mouse esta dentro de un Objeto Pollo  */

void Juego::VerificarMousePos(int iX,int iY,int iBoton)
{
	double resultado;
	int Altom;
	int Anchom;

	if (CantidadAves > 0)
	{
		pareja P=Aves.at(0)->getCoord();
		int posx,posy;
		posx=P.first;
		posy=P.second;
		Altom  = dbSpriteHeight(Aves.at(0)->RetornarIDSprite())/2;
		Anchom = dbSpriteWidth(Aves.at(0)->RetornarIDSprite())/2;
		
		if (iX>=posx-Anchom && iY >=posy-Altom && iX <=posx+Anchom && iY <=posy+Altom )
		{
			
			/*  Calcula Si el Pollo esta dentro del circulo para lanzarse */
			double h=iX-300;
			double k=iY-530;
			resultado=pow(h,2)+pow(k,2);
			double radio=pow((double) 50,2);
			if (resultado<=radio)
			{
				if (iBoton==1)
				{
					MostrarTrayectoria();
					MoverPollo(iX,iY);

				}
				if (iBoton==2)
				{
					MostrarTrayectoria();
					RotarPollo();
				}
			}
			
		}
	}
}

void Juego::MostrarTrayectoria()
{
	/*
	float Angle	= Aves.at(PtrPollo)->calculoAngulo();
	float Vo	= Aves.at(PtrPollo)->calculoVelocidad();
	pareja P	= Aves.at(PtrPollo)->getCoord();
	*/
	float Angle	= Aves.at(0)->calculoAngulo();
	float Vo	= Aves.at(0)->calculoVelocidad();
	pareja P	= Aves.at(0)->getCoord();

	int y;
	int PosXo	= P.first;								
	int PosYo	= P.second;							    
	int i		= 0;

	if ( MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle) != -1 )
	{
		for ( ; i<200 ; i+=5)
		{
			y = MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle);
			/* Muestra 5 Puntos indicando la trayectoria que tiene el Ave en esa posicion y angulo indicada */
			dbCircle(i+PosXo,y,1);
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
	if (CantidadAves > 0 && VerificarSiHayPollo())
	{
		Angle = Aves.at(0)->calculoAngulo();
		Vo	  = Aves.at(0)->calculoVelocidad();
		P     = Aves.at(0)->getCoord();
		
		PosXo = P.first;								
		PosYo = P.second;							   
		i=0;

		if ( MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle) != -1 )
		{
			for ( ; i<PIXEL ; i+=6)
			{
				y = MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle);
				MostrarPuntaje();
				Verificar = VerificarColisionObjetos();
						
				if (Verificar == -1)  // -1 significa que no colisiono con nada
				{
					MoverPollo(i+PosXo,y);
				}

				else                  // Colisiono un Ave con algun Obstaculo
				{
					if(FuncionRespuestaColision(Verificar))
					{
						/* Si retorna true es por que el Ave no tiene mas vidas */
						Aves.erase(Aves.begin());
						CantidadAves = (int) Aves.size();
						return;
					}
				}
				
			}
			Aves.erase(Aves.begin());
			CantidadAves = (int) Aves.size();
		}
		else
		{
			dbDeleteSprite(Aves.at(0)->RetornarIDSprite());
			Aves.erase(Aves.begin());
			CantidadAves = (int) Aves.size();
		}
	}
}

/* Este metodo se encarga de borrar los Sprites los cuales colisionaron si la vida es 1 */

bool Juego::FuncionRespuestaColision(int iObstaculo)
{
	int p;
	int VidaAve			= Aves.at(0)->RetornarVidas();
	int VidaObstaculo	= Enemigos.at(iObstaculo)->RetornarVidas();

		
	if ( VidaObstaculo > 1)
	{
		VidaObstaculo--;
		Enemigos.at(iObstaculo)->SetVidas(VidaObstaculo);
	}

	if ( VidaObstaculo == 1 )
	{
		p = Enemigos.at(iObstaculo)->getPuntaje();
		dbDeleteSprite(Enemigos.at(iObstaculo)->RetornarIDSprite());
		//
		
		//
		ActualizarCantidadHuevos(iObstaculo);
		Enemigos.erase(Enemigos.begin()+iObstaculo);
		SumarPuntos(p);
		
	}

	if ( VidaAve == 1 )
	{
		dbDeleteSprite(Aves.at(0)->RetornarIDSprite());
		return true;
	}
	
	if ( VidaAve > 1)
	{
		VidaAve--;
		Aves.at(0)->SetVidas(VidaAve);
	}

	return false;
}

/* Actualiza la cantidad de Huevos en el Mundo */
void Juego::ActualizarCantidadHuevos(int iObstaculo)
{
	string ReferenciaObstaculo;
	ReferenciaObstaculo = Enemigos.at(iObstaculo)->getIdentificador();
	if ( ReferenciaObstaculo == "Huevo" )
	{
		CantidadHuevos--;
	}
}

/* Verifica si algun objeto del vector Pollo Collisiona con un obstaculo o con un Huevo 
   Retorna un entero que representa la ubicacion de la Figura con la que el pollo Colisiono */

int Juego::VerificarColisionObjetos() 
{
	int i=0;
	for ( ; i < (int) Enemigos.size() ; i++ )
	{
		int ID;
		ID = Enemigos.at(i)->RetornarIDSprite();
		int ID_Pollo = Aves.at(0)->RetornarIDSprite();
		if ( dbSpriteCollision(ID_Pollo,ID) == 1)
		{
			//Colisiono
			return i;
		}
	}
	return -1;
	
}

void Juego::CargarPolloLanzar()
{
	if (CantidadAves > 0 && CantidadHuevos > 0)
	{
		if (!VerificarSiHayPollo())
		{
			MoverPollo(300,530);
		}
	}
}

/* Verifica Si hay un pollo en el circulo */

bool Juego::VerificarSiHayPollo()
{
	Pareja Tmp;		//Captura La coordenada de Cada Pollo 
	int x = 300;	//Centro X del circulo
	int y = 530;	//Centro Y del circulo
	int	h,k;
	double Hi,Ki;
	Tmp = Aves.at(0)->getCoord();
	h	= Tmp.first  - x;
	k	= Tmp.second - y;
	Hi	= pow((double) h ,2);
	Ki	= pow((double) k ,2);
	if ( (Hi+Ki) <= pow ((double) 50,2) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Juego::MensajeJuego()
{
	if ( Jugando == true )
	{
		if ( CantidadAves > 0 && CantidadHuevos > 0)
		{
			MostrarPuntaje();
		}
		if ( CantidadHuevos == 0 )
		{
			char strPuntaje[200];
			dbCenterText(650,240,"Presiona Jugar de Nuevo..");
			dbCenterText(650,300,"GANASTE!!" );
			sprintf ( strPuntaje, "Puntaje Final %d",Puntos);
			dbCenterText(650,360,strPuntaje);
			dbSetTextSize(40);
		}
		if ( CantidadHuevos > 0 && CantidadAves == 0 )
		{
			char strPuntaje[200];
			dbCenterText(650,240,"Presiona Enter Para Intentar de Nuevo..");
			dbCenterText(650,300, "GAME OVER -.-!!" );
			sprintf ( strPuntaje, "Puntaje Final %d",Puntos);
			dbCenterText(650,360,strPuntaje);
			dbSetTextSize(40);
		}
	}
	else
	{
		
		char TipoMundo[1];
		sprintf ( TipoMundo, "Mundo %d",Mundo);
		dbCenterText(650,600,TipoMundo);
		
	}
}

void Juego::DecrementarRotacionAve()
{
	if (CantidadAves > 0)
	{
		if (Aves.at(0)->RetornarAngulo() != 0)
		{

			Aves.at(0)->MenosRotateBird();
			MostrarTrayectoria();
		}
	}

}


void Juego::ReiniciarJuego()
{

	if ( Jugando == false )
	{
		string sMundo;
		dbDeleteSprite(1);
		dbDeleteImage(1);
		if ( Mundo == 1)
		{
			sMundo = "World1.txt";
		}
		else if ( Mundo == 2)
		{
			sMundo = "World2.txt";
		}
		else if ( Mundo == 3)
		{
			sMundo = "World3.txt";
		}
		else if ( Mundo == 4)
		{
			sMundo = "World4.txt";
		}
		else if ( Mundo == 5)
		{
			sMundo = "World5.txt";
		}
		CargarFigurasTxt(sMundo);
		PintarFiguras();
		Jugando = true;
	}
	else
	{
		if ((CantidadHuevos > 0 && CantidadAves == 0 ) || (CantidadHuevos == 0 ))
		{
			VaciarVectores();
			CantidadHuevos=0;
//			CargarFigurasTxt();
//			PintarFiguras();
			Puntos=0;
		}
	}
}

void Juego::VaciarVectores()
{
	int TmpNoSprites = 0;
	TmpNoSprites = (int) Figuras.size();
	for ( int i=0 ; i < TmpNoSprites ; i++ )
	{
		dbDeleteSprite(i);
	}
	Enemigos.clear();
	Aves.clear();
	Figuras.clear();

}
void Juego::MenuMundoIzquierda()
{
	
	if ( Mundo == 1)
	{	
		Mundo = 5;
	}
	else
	{
		Mundo--;
	}
}
void Juego::MenuMundoDerecha()
{
	if ( Mundo == 5)
	{	
		Mundo = 1;
	}
	else
	{
		Mundo++;
	}
}
