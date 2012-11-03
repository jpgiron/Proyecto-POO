#pragma once

#include "darkgdk.h"
#include "Ave.h"

class pollo:public Ave
{
public:
	pollo(int ID_Im,int ID_Sprite,int posx,int posy,string Identi):
	  Ave(ID_Im,ID_Sprite,posx,posy,Identi)
	  {
		vidas = 1;
	  }
	
	~pollo(void);
	
};
