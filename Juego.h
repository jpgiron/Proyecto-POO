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
#include "ParedCemento.h"
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

	int Mundo;

	bool Jugando;

public:
	Juego(void);
	~Juego(void);
	
	void AgregarFigura(figura* OBJETO);
	
	void PintarFiguras();

	void CargarFigurasTxt(string TipoMundo);

	void SumarPuntos(int Puntos);

	void MoverPollo(int iX,int iY);
	
	void MostrarPuntaje();

	void RotarPollo();

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

	void MenuMundoIzquierda();

	void MenuMundoDerecha();
};
#endif