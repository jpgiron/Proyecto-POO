#include "Ave.h"

#define Radio 50

Ave::~Ave(void)
{
	
}

float Ave::calculoVelocidad()
{
	int tmp;
	tmp=sqrt(pow((double) posx-PosXo,2)+pow((double) posy-PosYo,2));
	return (tmp*120/Radio);

}

float Ave::calculoAngulo()
{
	Angle=abs(dbSpriteAngle(ID));//En grados;
	return (Angle*3.1415)/180;
}

void Ave::moveBird(){

	dbSprite(ID,posx,posy,ID_Image);
	dbOffsetSprite(ID,dbSpriteWidth(ID)/2,dbSpriteHeight(ID)/2);
	dbSync();
}

void Ave::rotateBird()
{
	dbRotateSprite(ID,dbSpriteAngle(ID)-1);
}

float Ave::RetornarAngulo()
{
	return Angle;
}
