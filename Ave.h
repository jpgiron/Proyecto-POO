#pragma once

#include "figura.h"
#include "darkgdk.h"
#include <cmath>



using namespace std;


class Ave:public figura
{
private:

	int Angle;

public:
	Ave(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):figura(ID_Im,ID_Sprite,posx,posy,Identi)
	{
		
		
	}
	~Ave(void);
	void  moveBird();
	void  rotateBird();
	void  MenosRotateBird();
	float calculoAngulo();
	float calculoVelocidad();
	int RetornarAngulo();
};