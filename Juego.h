#ifndef JUEGO_H_
#define JUEGO_H_


#include "figura.h"
#include "obstaculo.h"
#include "pollo.h"
#include "darkgdk.h"
#include "StructFisica.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define PIXEL 1300

using namespace std;

typedef pair<int,int> pareja;

class Juego
{

private:
	int CantidadPollos;

	vector<figura*> Figuras;

	vector<pareja>  ParejasPos;
	
	vector<pollo*>  Pollos;
	
	fisica MotorFisico;
	
	int Puntos;

public:
	Juego(void);
	~Juego(void);
	
	void AgregarFigura(figura* OBJETO);
	
	void PintarFiguras();

	void CargarFigurasTxt();

	void SumarPuntos(int Puntos);

	void MoverPollo(int iX,int iY,int IDSprite);
	
	void MostrarPuntaje();

	void RotarPollo(int IDSprite);

	void VerificarMousePos(int iX,int iY,int iBoton);

	void MovProyectilPollo();

	int  VerificarColisionObjetos(pareja PosPollo);

	void CargarPolloLanzar();
};
#endif