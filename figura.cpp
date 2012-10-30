#include "figura.h"
#include "darkgdk.h"

figura::~figura(void)
{
}

void figura::setIdentificador(string NombreFigura)
{
	Identificador=NombreFigura;
}

void figura::setCoords(int PosX,int PosY)
{
	posx=PosX;
	posy=PosY;
}

Pareja figura::getCoord()
{
	Pareja P;
	P.first  = posx;
	P.second = posy;
	return P;

}

void figura::dibujar()
{
	dbSprite(ID,posx,posy,ID_Image);

}

int figura::RetornarIDSprite()
{
	return ID;

}
string figura::getIdentificador()
{
	return Identificador;
}