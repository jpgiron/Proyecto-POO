#pragma once

#ifndef HUEVO_H_
#define HUEVO_H_

#include "darkgdk.h"
#include "obstaculo.h"


class Huevo:public obstaculo
{

public:
	Huevo(int ID_Imagen,int ID_Sprite,int posx,int posy,string Identi):obstaculo(ID_Imagen,ID_Sprite,posx,posy,Identi){puntaje=50;}
	~Huevo(){};

};
#endif