#include "FruitClass.h"

vector<Coordinate>::iterator Fruit::FindFruits(Coordinate Pos){
	return find(Fruits.begin(),Fruits.end(),Pos);
}

void Fruit::AddFruit(int PosX,int PosY){
	Coordinate NewPos;
	NewPos.x = PosX;
	NewPos.y = PosY;
	Fruits.push_back(NewPos); //Aggiungo un frutto
}

int Fruit::GetNumFruits(void){return (int)Fruits.size();}

bool Fruit::IsFruitPresent(int PosX,int PosY){
	Coordinate Pos;
	Pos.x=PosX;
	Pos.y=PosY;
	if(FindFruits(Pos) != Fruits.end())
		return true;
	else
		return false;
}

bool Fruit::EraseFruit(int PosX,int PosY){
	Coordinate Pos;
	Pos.x=PosX;
	Pos.y=PosY;
	vector<Coordinate>::iterator Find = FindFruits(Pos);
	if(Find != Fruits.end()){
		Fruits.erase(Find);
		return true;
	}
	else
		return false;
}

void Fruit::DrawFruits(int DimFruit,sf::RenderTarget& target,sf::Texture *FruitTexture){
	//Disegno i frutti
	sf::RectangleShape Fruit;
	Fruit.setSize(sf::Vector2f(DimFruit,DimFruit));
	Fruit.setTexture(FruitTexture);
	for(int i=0;i<(int)Fruits.size();i++){
		int X = (Fruits[i].x+1)*DimFruit+1;
		int Y = (Fruits[i].y+1)*DimFruit+1;
		Fruit.setPosition(X,Y); //Assegno la sua posizione
		target.draw(Fruit); //lo disegno sul target selezionato
	}
}