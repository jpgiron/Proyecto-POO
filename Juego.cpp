#include "Juego.h"

Juego::Juego(void)
{
	CantidadAves	=	0; 
	Puntos			=	0;
	CantidadHuevos	=	0;
	PtrPollo		=	0;
	//Las imagenes hacen parte del Juego
	dbLoadImage ( "PolloVolador2.bmp",			2);
	dbLoadImage ( "alcon.bmp",					3);
	dbLoadImage ( "ornitorrinco.bmp",			4);
	dbLoadImage	( "obstaculoMadera.bmp",		5);
	dbLoadImage ( "obstaculoMaderaAcostado.bmp",6);
	dbLoadImage ( "Huevo.bmp",					7);
	
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

void Juego::CargarFigurasTxt()
{
	
	int posx;
	int posy;
	int IDSprite;
	int IDImage;
	string TipoObjeto;
	ifstream Map("Mundo5.txt");

	while(!Map.eof())
	{
		Map >> IDSprite >> IDImage >> posx >> posy >> TipoObjeto;
		if (TipoObjeto == "Pollo")
		{
			AgregarFigura(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new pollo(IDImage,IDSprite,posx,posy,TipoObjeto));
		}
		if (TipoObjeto == "Ornitorrinco")
		{
			AgregarFigura(new Ornitorrinco(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new Ornitorrinco(IDImage,IDSprite,posx,posy,TipoObjeto));
		}

		if (TipoObjeto == "Aguila")
		{
			AgregarFigura(new Aguila(IDImage,IDSprite,posx,posy,TipoObjeto));
			Aves.push_back(new Aguila(IDImage,IDSprite,posx,posy,TipoObjeto));
		}

		if (TipoObjeto == "Obstaculo" )
		{
			AgregarFigura(new ParedMadera(IDImage,IDSprite,posx,posy,TipoObjeto));
			Enemigos.push_back(new ParedMadera(IDImage,IDSprite,posx,posy,TipoObjeto));
		}
		if (TipoObjeto == "Huevo")
		{
			AgregarFigura(new Huevo(IDImage,IDSprite,posx,posy,TipoObjeto));
			Enemigos.push_back(new Huevo(IDImage,IDSprite,posx,posy,TipoObjeto));
			CantidadHuevos++;
		}
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

void Juego::MoverPollo(int iX,int iY,int IDSprite)
{
	Aves.at(IDSprite)->setCoords(iX,iY);
	Aves.at(IDSprite)->moveBird();
		
}

/* Actualiza el Angulo de disparo del Pollo */

void Juego::RotarPollo(int IDSprite)
{
	/* Condicion Necesaria Para para que el Ave solo tenga una rotacion de hasta 90 grados  */
	if (Aves.at(IDSprite)->RetornarAngulo() < 89)
	{
		Aves.at(IDSprite)->rotateBird();
	}

}

/* Verifica si la posicion del Mouse esta dentro de un Objeto Pollo  */

void Juego::VerificarMousePos(int iX,int iY,int iBoton)
{
	double resultado;
	int ptr = 0;

	if (CantidadAves > 0)
	{
		pareja P=Aves.at(PtrPollo)->getCoord();
		int posx,posy;
		posx=P.first;
		posy=P.second;
		if (iX>=posx-24 && iY >=posy-22 && iX <=posx+24 && iY <=posy+22 )
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
					
					MoverPollo(iX,iY,PtrPollo);
				}
				if (iBoton==2)
				{
					RotarPollo(PtrPollo);
					
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
	if (CantidadAves > 0 && VerificarSiHayPollo())
	{
		Angle = Aves.at(PtrPollo)->calculoAngulo();
		Vo	  = Aves.at(PtrPollo)->calculoVelocidad();
		P     = Aves.at(PtrPollo)->getCoord();
		
		PosXo = P.first;								//22 representa la distancia del vertice superior izquiero al centro en x
		PosYo = P.second;							    //22 representa la distancia del vertice superior izquiero al centro en Y
		
		CantidadAves--;
		i=0;

		if ( MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle) != -1 )
		{
			for ( ; i<PIXEL ; i+=10)
			{
				y = MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle);
				MostrarPuntaje();
				P = Aves.at(PtrPollo)->getCoord();
				Verificar = VerificarColisionObjetos(P);
						
				if (Verificar == -1)  // -1 significa que no colisiono con nada
				{
					MoverPollo(i+PosXo,y,PtrPollo);
				}

				else                  // Colisiono un Ave con algun Obstaculo
				{
					
					FuncionRespuestaColision(PtrPollo,Verificar);
					
				}
				
			}
			PtrPollo++;
		}
		else
		{
			dbDeleteSprite(Aves.at(PtrPollo)->RetornarIDSprite());
			PtrPollo++;
		}
	}
}

/* Este metodo se encarga de borrar los Sprites los cuales colisionaron si la vida es 1 */

void Juego::FuncionRespuestaColision(int iAve,int iObstaculo)
{
	int p;
	int VidaAve			= Aves.at(iAve)->RetornarVidas();
	int VidaObstaculo	= Enemigos.at(iObstaculo)->RetornarVidas();

	if ( VidaAve > 1 )
	{
		dbDeleteSprite(Aves.at(iAve)->RetornarIDSprite());	
		Aves.at(iAve)->SetVidas(VidaAve--);
		PtrPollo++;
		return;
	}
	
	if ( VidaObstaculo == 1 )
	{
		dbDeleteSprite(Enemigos.at(iObstaculo)->RetornarIDSprite());
		p = Enemigos.at(iObstaculo)->getPuntaje();
		Enemigos.at(iObstaculo)->SetVidas(VidaObstaculo--);
		Aves.at(iAve)->SetVidas(VidaAve--);
		SumarPuntos(p);
		ActualizarCantidadHuevos(iObstaculo);
	}	
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

int Juego::VerificarColisionObjetos(pareja PosPollo) 
{
	int i=0;
	for ( ; i < (int) Enemigos.size() ; i++ )
	{
		int ID;
		ID = Enemigos.at(i)->RetornarIDSprite();
		int ID_Pollo = Aves.at(PtrPollo)->RetornarIDSprite();
		if ( dbSpriteCollision(ID_Pollo,ID) == 1 && ID_Pollo != ID)
		{
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
			MoverPollo(300,530,PtrPollo);
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
	for(int i=PtrPollo; i < (int) Aves.size() ; i++ )
	{
		Tmp = Aves.at(i)->getCoord();
		h	= Tmp.first  - x;
		k	= Tmp.second - y;
		Hi	= pow((double) h ,2);
		Ki	= pow((double) k ,2);
		
		if ( (Hi+Ki) <= pow ((double) 50,2) )
		{
			return true;
		}
	}
	return false;
}

void Juego::MensajeJuego()
{
	if (CantidadAves > 0)
	{
		MostrarPuntaje();
	}
	
	if ( CantidadHuevos == 0 )
	{
		char string[200];
		sprintf ( string,"GANASTE!");
		dbText (650,300, string );
		dbSetTextSize(60);
		
	}
	if ( CantidadHuevos > 0 && CantidadAves == 0 )
	{
		char string[200],strPuntaje[200];
		sprintf ( string, "GAME OVER -.-!!");
		dbCenterText(650,300, string );
		sprintf ( strPuntaje, "Puntaje Final %d",Puntos);
		dbCenterText(650,360,strPuntaje);
		dbSetTextSize(40);

	}
	

}

void Juego::DecrementarRotacionAve()
{
	if (CantidadAves > 0)
	{
		if (Aves.at(PtrPollo)->RetornarAngulo() != 0)
		{
			Aves.at(PtrPollo)->MenosRotateBird();
		}
	}
}