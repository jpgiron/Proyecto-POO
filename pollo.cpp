#include "pollo.h"

#define POSXo 124 //Posicion Inicial del pollo en X
#define POSYo 422 //Posicion Inicial del pollo en Y
#define Radio 50
#define enemigo 2


pollo::~pollo(void)
{

}


void pollo::setPos()
{
	
	float t;
	float y;
	float angle=calculoAngulo();
	float Vx=calculoVelocidad()*(cos(angle));
	float Vy=calculoVelocidad()*(sin(angle));

	if(calculoVelocidad()==0)
	{
		dbDeleteSprite(ID);
	}
	else{
		for(int pixel=0;pixel<1200;pixel+=4)
		{
			t=(pixel+POSXo)/(Vx);
			y=abs((Vy)*t-(5*t*t)-POSYo);
			dbSprite(ID,pixel+POSXo,(int) ceil(y+0.5),1);

			

			if (dbSpriteCollision(ID,enemigo)==1)
			{
				dbDeleteSprite(ID);
				dbDeleteSprite(enemigo);
				return;
			}
			if (dbSpriteCollision(ID,3)==1)
			{
				dbDeleteSprite(ID);
				dbDeleteSprite(3);
				return;
			}
			
			if (dbSpriteCollision(ID,4)==1)
			{
				dbDeleteSprite(ID);
				dbDeleteSprite(4);
				return;
			}

			dbSync();//refrescar la pantalla
						
		}
	}
}

float pollo::calculoVelocidad()
{
	int tmp;
	tmp=sqrt(pow((double) posx-POSXo,2)+pow((double) posy-POSYo,2));
	return (tmp*80/Radio);

}

float pollo::calculoAngulo()
{
	return (abs(dbSpriteAngle(ID))*3.1415)/180;
}


void pollo::moveBird(){

	dbSprite(ID,posx,posy,ID_Image);
	dbOffsetSprite(ID,dbSpriteWidth(ID)/2,dbSpriteHeight(ID)/2);
	dbSync();

}

void pollo::rotateBird()
{
	dbRotateSprite(ID,dbSpriteAngle(ID)-1);
	
}

void pollo::dibujar()
{
	int X,Y;
	X=dbSpriteWidth(ID);
	Y=dbSpriteHeight(ID);
	dbSprite(ID,posx-44,posy-44,ID_Image);
	//dbSprite(ID,posx-22,posy-22,ID_Image);
	//dbOffsetSprite(ID,dbSpriteWidth(ID)/2,dbSpriteHeight(ID)/2);
	dbSync();
}