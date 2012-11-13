#pragma once

#ifndef PAREDMADERA_H_
#define PAREDMADERA_H_

#include "obstaculo.h"


class ParedMadera:public obstaculo
{

public:
	ParedMadera(int ID_Imagen,int ID_Sprite,int posx,int posy,string Identi):obstaculo(ID_Imagen,ID_Sprite,posx,posy,Identi){puntaje=10;vidas=1;}
	~ParedMadera(){};

};
#endif