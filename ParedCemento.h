#pragma once

#ifndef PAREDMADERA_H_
#define PAREDMADERA_H_

#include "obstaculo.h"


class ParedCemento:public obstaculo
{

public:
	ParedCemento(int ID_Imagen,int ID_Sprite,int posx,int posy,string Identi):obstaculo(ID_Imagen,ID_Sprite,posx,posy,Identi){puntaje=15;vidas=2;}
	~ParedCemento(){};

};
#endif