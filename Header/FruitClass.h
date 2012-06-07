#ifndef FRUITCLASS_H_INCLUDED
#define FRUITCLASS_H_INCLUDED

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

#include "CoordinateClass.h"

class Fruit{
    private:
		vector<Coordinate> Fruits; //Oggetti da mangiare
		vector<Coordinate>::iterator FindFruits(Coordinate Pos);
	public:
		void AddFruit(int PosX,int PosY); //Aggiunge un frutto alla posizione specificata
		int GetNumFruits(void); //Recupera il numero di frutti presenti nel campo
		bool IsFruitPresent(int PosX,int PosY); //restituisce true se il frutto è presente in quella posizione
		bool EraseFruit(int PosX,int PosY);
		void DrawFruits(int DimFruit,sf::RenderTarget& target,sf::Texture *SnakeTexture);
};


#endif