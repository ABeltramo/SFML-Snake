#include "snakeClass.h"

Snake::Snake(int Rig, int Col,Fruit *Frutto){
	Snake(Rig,Col,2,Frutto);
}

Snake::Snake(int Rig, int Col, int LunIniSnake,Fruit *Frutto){
	Snake(Rig,Col,LunIniSnake,0,0,Frutto);
}

Snake::Snake(int Rig, int Col, int LunIniSnake,int PosIniX, int PosIniY,Fruit *Frutto){
	Point = 0;
	this->Frutto=Frutto;
	//Salvo le informazioni nell'oggetto
	NumRig = Rig;
	NumCol = Col;
	//Posiziono snake
	Coordinate Pos;
	for(int j=PosIniX;j<PosIniX+LunIniSnake;j++){
		Pos.x=j;
		Pos.y=PosIniY;
		Body.push_back(Pos);
	}
}

void Snake::Print_All(void){
	Coordinate Pos;
	vector<Coordinate>::iterator Find;
	for(int j=0;j<NumRig;j++){ //Scorro le righe
		for(int i=0;i<NumCol;i++){ //Scorro le colonne
			Pos.x = i;
			Pos.y = j;
			Find = find(Body.begin(),Body.end(),Pos);
			if(Find != Body.end()) //Se ho trovato stampo il serpente
				cout << "X";
			else //Altrimenti non stampo niente
				cout << "0";
		}
		cout << endl;
	}
}

bool Snake::Move_Next(int Direction){
	Coordinate NewDirection = Body[(int)Body.size()-1]; //La nuova direzione parte dall'ultima casella
	Body.erase(Body.begin()); //Rimuovo il primo elemento
	//La testa deve seguire la nuova direzione
	switch(Direction){
		case 1: //su
			NewDirection.y--;
			if(NewDirection.y == -1)
				return true;
		break;
		case 2: //destra
			NewDirection.x++;
			if(NewDirection.x >= NumCol)
				return true;
		break;
		case 3: //giu
			NewDirection.y++;
			if(NewDirection.y >= NumRig)
				return true;
		break;
		case 4: //sinistra
			NewDirection.x--;
			if(NewDirection.x == -1)
				return true;
		break;
	}
	if(FindSnake(NewDirection)) //Se ho trovato vuol dire che si è mangiato la coda
		return true;
	if((*Frutto).IsFruitPresent(NewDirection.x,NewDirection.y)){
		IncrementSnake(4);
		AddPoint(PointBase);
		(*Frutto).EraseFruit(NewDirection.x,NewDirection.y);
	}

	Body.push_back(NewDirection);
	return false;
}

bool Snake::Move_Next(int Direction,Snake *Player2){
	if(Move_Next(Direction))
		return true;
	Coordinate NewDirection = Body[(int)Body.size()-1];
	//if((*Player2).FindSnake(NewDirection) ) //Se ho toccato l'altro giocatore
		//return true;
	return false;
}

void Snake::DrawSnake(sf::RenderTarget& target,int DimSnake,sf::Texture *SnakeTexture,sf::Texture *HeadTexture){
	//Disegno il corpo
	sf::RectangleShape Snake;
	Snake.setSize(sf::Vector2f(DimSnake,DimSnake));
	Snake.setTexture(SnakeTexture);
	for(int i=0;i<(int)Body.size()-1;i++){
		Snake.setPosition((Body[i].x+1)*DimSnake,(Body[i].y+1)*DimSnake); //Assegno la sua posizione
		target.draw(Snake); //lo disegno sul target selezionato
	}
	// Disegno la testa
	sf::RectangleShape Head;
	Head.setSize(sf::Vector2f(DimSnake,DimSnake));
	Head.setTexture(HeadTexture);
	Head.setPosition((Body[Body.size()-1].x+1)*DimSnake,(Body[Body.size()-1].y+1)*DimSnake);
	target.draw(Head);

}

void Snake::DrawBorder(sf::RenderTarget& target,int DimSnake,sf::Texture *Background){
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(40*DimSnake,30*DimSnake));
	rectangle.setOutlineColor(sf::Color::Green);
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(0,0);
	rectangle.setTexture(Background,true);
	target.draw(rectangle);
}

void Snake::IncrementSnake(int N){
	Body.insert(Body.begin(),Body.begin(),Body.begin()+N);
}

bool Snake::FindSnake(Coordinate Pos){
	vector<Coordinate>::iterator Find;
	Find = find(Body.begin(),Body.end(),Pos);
	if(Find != Body.end()) //Se ho trovato vuol dire che si è morso la coda
		return true;
	return false;
}

void Snake::AddPoint(int Point){this->Point += Point;}

int Snake::GetPoint(void){return Point;}