#pragma once

#include "figura.h"

class Ave:public figura
{
private:
	int pixel;
	float Angle;
	int PosXo;
	int PosYo;
public:
	Ave(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):figura(ID_Im,ID_Sprite,posx,posy,Identi)
	{
		pixel=0;
		PosXo=300;  //Centro en X del circulo de radio 50
		PosYo=530;  //Centro en Y del circulo de radio 50
	}
	~Ave(void);
	void  moveBird();
	void  rotateBird();
	float calculoAngulo();
	float calculoVelocidad();
	float RetornarAngulo();
};