#pragma once

#ifndef FIGURA_H_
#define FIGURA_H_

#include <iostream>
using namespace std;

typedef pair<int,int> Pareja;

class figura
{

protected:
	int posx;
	int posy;
	int ID;
	int vidas;
	int ID_Image;
	string Identificador;
public:
	
	figura(int ID_Im,int ID_Sprite,int PosX,int PosY,string Identi):ID_Image(ID_Im),ID(ID_Sprite),posx(PosX),posy(PosY),
																	Identificador(Identi){}
	~figura(void);
	//sets
	void setIdentificador(string NombreFigura);
	virtual void setCoords(int PosX,int PosY);
	Pareja getCoord();
	virtual void dibujar();
	int RetornarIDSprite();
	int RetornarVidas();
	string getIdentificador();
};

#endif;
