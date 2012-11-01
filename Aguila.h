#pragma once

#include "Ave.h"

class Aguila:public Ave
{
public:
	Aguila(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):
	  Ave(ID_Im,ID_Sprite,posx,posy,Identi){}
	
	~Aguila(void);
};
