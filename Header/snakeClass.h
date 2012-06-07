#ifndef SNAKECLASS_H_INCLUDED
#define SNAKECLASS_H_INCLUDED

#include <SFML\Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <bitset>
using namespace std;

#include "CoordinateClass.h"
#include "FruitClass.h"

class Snake{
	  private:
		  int NumRig;
		  int NumCol;
		  vector<Coordinate> Body; //corpo del serpente
		  int Direction; //Direzione: 1-su, 2-destra, 3-giu, 4-sinistra
		  Fruit *Frutto;
		  static const int PointBase = 50; //punteggio aggiunto ad ogni frutto preso
		  int Point; //punteggio del giocatore
      public:
		  Snake(int Rig, int Col,Fruit *Frutto);
		  Snake(int Rig, int Col, int LunIniSnake,Fruit *Frutto);
		  Snake(int Rig, int Col, int LunIniSnake,int PosIniX, int PosIniY,Fruit *Frutto);
		  void Print_All(void);
		  bool Move_Next(int Direction); //restituisce true se si tocca un muro o se stessi(dead = true)
		  bool Move_Next(int Direction,Snake *Player2); //restituisce true se si tocca un muro, se stessi o il player 2 (dead = true)
		  void DrawSnake(sf::RenderTarget& target,int DimSnake,sf::Texture *SnakeTexture,sf::Texture *HeadTexture); //Disegna lo snake sullo schermo
		  void DrawBorder(sf::RenderTarget& target,int DimSnake,sf::Texture *Background); //Disegna lo snake sullo schermo
		  void IncrementSnake(int N); //Aumenta il corpo dello snake di N
		  bool FindSnake(Coordinate Pos); //Vero se il serpente è in quella casella
		  //Recupero e modifico il Punteggio
		  void AddPoint(int Point);
		  int GetPoint(void);
};

#endif