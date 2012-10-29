
#include <cmath>

using namespace std;

struct fisica
{

	/*  Vo Corresponde a la magnitud de la velocidad del Polllo, el angulo correponde 
	
		al angulo del vector velocidad. PosXo y PosYo es el centro inicial del pollo 
		
		pixel representa cada pixel de la pantalla horizontal.*/

	int CalculoAltura(float Vo,int PosXo,int PosYo,int pixel,float angle)
	{
		int y;
		float Vx,Vy,t;

		Vx=Vo*(cos(angle));
		Vy=Vo*(sin(angle));

		if (Vo==0)
		{
			return -1; //  -1 representa que no hay velocidad
		}
		else
		{
			t=(pixel+PosXo)/(Vx);
			y=abs((Vy)*t-(5*t*t)-PosYo);
			return (int) ceil(y+0.5);
		}

	}

};