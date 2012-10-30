#pragma once

#include "darkgdk.h"
#include "figura.h"
#include <cmath>

class pollo:public figura
{
private:
	int pixel;
	float Angle;
public:
	pollo(int ID_Im,int ID_Sprite,int posx,int posy):figura(ID_Im,ID_Sprite,posx,posy){pixel=0;}
	~pollo(void);

	void  setPos(); //calcula la ecuacion de la parabola
	void  moveBird();
	void  rotateBird();
	float calculoAngulo();
	float calculoVelocidad();
	void  dibujar();
	float RetornarAngulo();
};
