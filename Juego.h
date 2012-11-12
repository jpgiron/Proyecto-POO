#ifndef JUEGO_H_
#define JUEGO_H_


#include "figura.h"
#include "obstaculo.h"
#include "pollo.h"
#include "darkgdk.h"
#include "StructFisica.h"
#include "Huevo.h"
#include "Ave.h"
#include "Ornitorrinco.h"
#include "Aguila.h"
#include "ParedMadera.h"
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
	int CantidadAves;

	int CantidadHuevos;

	vector<figura*> Figuras;
	
	vector<Ave*>  Aves;

	vector<obstaculo*> Enemigos;
	
	fisica MotorFisico;
	
	int Puntos;

	int PtrPollo; //Posicion Pollo Actual

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

	bool FuncionRespuestaColision(int iObstaculo);

	void ActualizarCantidadHuevos(int iObstaculo);
	
	int  VerificarColisionObjetos();

	void CargarPolloLanzar();

	bool VerificarSiHayPollo();

	void MostrarTrayectoria();

	void MensajeJuego();

	void DecrementarRotacionAve();

	void ReiniciarJuego();

	void VaciarVectores();
};
#endif