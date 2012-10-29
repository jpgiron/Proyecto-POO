#include "Juego.h"

Juego::Juego(void)
{
	CantidadPollos=1; //Solo hay un pollo en el Mundo
	Puntos=0;
}

Juego::~Juego(void)
{
}

void Juego::AgregarFigura(figura* OBJETO)
{
	pareja Temp;
    Figuras.push_back(OBJETO); //Agrega una Figura al mundo.
	Temp=OBJETO->getCoord(); //obtiene las Coordenadas e cada Figura
	ParejasPos.push_back(Temp);
}


void Juego::PintarFiguras()
{
	int i=0;
	for(;i<(int) Figuras.size();i++)
	{
		Figuras.at(i)->dibujar();
			
	}
}

void Juego::SumarPuntos(int Puntos)
{

	this->Puntos+=Puntos;
	MostrarPuntaje();
}

void Juego::MostrarPuntaje()
{
	char string[200];
	sprintf ( string, "Puntaje= %d", Puntos );
	dbText (650,600, string );
	dbSetTextSize(30);
	
}

void Juego::MoverPollo(int iX,int iY)
{

	Figuras.at(0)->setCoords(iX,iY);
	Figuras.at(0)->moveBird();
		
}

void Juego::RotarPollo()
{
	
	Figuras.at(0)->rotateBird();

}

void Juego::VerificarMousePos(int iX,int iY,int iBoton)
{
	
	pareja P=Figuras.at(0)->getCoord();
	int posx,posy;
	posx=P.first;
	posy=P.second;
	double resultado;
	if (CantidadPollos > 0)
	{
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
					MoverPollo(iX,iY);
				}
				if (iBoton==2)
				{
					RotarPollo();
				}
			}
			
		}
	}
}

void Juego::MovProyectilPollo()
{
	int i=0;
	int y;
	int PosXo,PosYo;
	float Vo, Angle;
	pareja P;
	int Verificar;
	if (CantidadPollos > 0 ) //Se ejecuta Si hay Pollo en El juego.
	{
		Vo    = Figuras.at(0)->calculoVelocidad();
		Angle = Figuras.at(0)->calculoAngulo();
		
		P = Figuras.at(0)->getCoord();
		PosXo=P.first+22;	//22 representa la distanci del vertice superior izquiero al centro en x
		PosYo=P.second+22;	//22 representa la distanci del vertice superior izquiero al centro en Y
		
		for (;i<PIXEL;i+=4)
		{
			y=MotorFisico.CalculoAltura(Vo,PosXo,PosYo,i,Angle);
			MostrarPuntaje();
			P = Figuras.at(0)->getCoord();

			Verificar = VerificarColisionObjetos(P);
					
			if (Verificar == -1)  // -1 significa que no colisiono con nada
			{
				MoverPollo(i+124,y);
			}

			else                  // Elimina las Figuras que Colisionaron
			{
				dbDeleteSprite(Figuras.at(0)->RetornarIDSprite());
				dbDeleteSprite(Figuras.at(Verificar)->RetornarIDSprite());
				SumarPuntos(500);
				MostrarPuntaje();
				return;
			}
			
		}
	}
}

int Juego::VerificarColisionObjetos(pareja PosPollo) //Retorna un entero que representa la ubicacion de la Figura con la que el pollo Colisiono
{
	int i=1;
	
	for ( ; i < (int) Figuras.size() ; i++ )
	{
		int ID;
		ID = Figuras.at(i)->RetornarIDSprite();
		if ( dbSpriteCollision(5,ID) == 1 )
		{
			return i;
		}
	}
	return -1;

	
}