#pragma once

#include "Ave.h"

class Ornitorrinco:public Ave
{
public:
	Ornitorrinco(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):
	  Ave(ID_Im,ID_Sprite,posx,posy,Identi)
	  {
		vidas = 2;
	  }
	
	~Ornitorrinco(void);
};
