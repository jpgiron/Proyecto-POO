#pragma once

#ifndef OBSTACULO_H_
#define OBSTACULO_H_

#include "figura.h"



class obstaculo:public figura
{
protected:
	
	int puntaje;
	
public:
	obstaculo(int ID_Imagen,int ID_Sprite,int posx,int posy,string Identi):figura(ID_Imagen,ID_Sprite,posx,posy,identi){puntaje=10;}
	~obstaculo(){};

	void setPuntaje(int puntaje);
	int getPuntaje();
};

#endif 