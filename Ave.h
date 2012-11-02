#pragma once

#include "figura.h"
#include "darkgdk.h"
#include <cmath>

#define PosXo=300;  //Centro en X del circulo de radio 50
#define	PosYo=530;  //Centro en Y del circulo de radio 50 

using namespace std;


class Ave:public figura
{
private:

	float Angle;

public:
	Ave(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):figura(ID_Im,ID_Sprite,posx,posy,Identi)
	{
		
		
	}
	~Ave(void);
	void  moveBird();
	void  rotateBird();
	float calculoAngulo();
	float calculoVelocidad();
	float RetornarAngulo();
};