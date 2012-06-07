#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void ReturnError(string Errore){
	//mostro la finestra se era nascosta
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_NORMAL );
	//Stampo l'errore
	cout << "Un errore inaspettato e' avvenuto:" << endl << " " << Errore << endl;
	system("PAUSE");
}

#include "Controller360.h"
#include "snakeClass.h"
#include <sstream>
//Classe che consente di recuperare i dati salvati su file DAT
#include "DatFileClass.h"

//Per nascondere la finestra di terminale
#include <process.h>
#define _WIN32_WINNT 0x0500

cDAT DataFile; //File .DAT contenente tutte le risorse necessarie
Controller360 Pad(0); //Controller xbox collegato al pc

struct PadConfig{
	char* PadSu;
	char* PadGiu;
	char* PadDes;
	char* PadSin;
	sf::Keyboard::Key Su;
	sf::Keyboard::Key Giu;
	sf::Keyboard::Key Des;
	sf::Keyboard::Key Sin;
};

int Attendi(double Sec,int *Direction, PadConfig PadCfg){
	int NewDirection = *Direction;
	clock_t endwait;
	int Velocity = (Pad.CheckTrigger("RT")/50)+1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) //Se preme space va al massimo della velocità
		Velocity = 5;
	endwait = clock () + (Sec/Velocity) * CLOCKS_PER_SEC ; //+1 per evitare la divisione per 0
	while(clock() < endwait){
		if((Pad.CheckThumb(PadCfg.PadSu) > 30000 || sf::Keyboard::isKeyPressed(PadCfg.Su)) && *Direction != 3) //SU
				NewDirection = 1;
		else if((Pad.CheckThumb(PadCfg.PadDes) > 30000 || sf::Keyboard::isKeyPressed(PadCfg.Des)) && *Direction != 4) //Destra
				NewDirection = 2;
		else if((Pad.CheckThumb(PadCfg.PadGiu) < -30000 || sf::Keyboard::isKeyPressed(PadCfg.Giu)) && *Direction != 1)//Giu
				NewDirection = 3;
		else if((Pad.CheckThumb(PadCfg.PadSin) < -30000 || sf::Keyboard::isKeyPressed(PadCfg.Sin)) && *Direction != 2) //Sinistra
				NewDirection = 4;
	}
	return NewDirection;
}

void CreaFrutti(Fruit *Frutti, int NumCol, int NumRig){
	if((*Frutti).GetNumFruits() < 1){
		//inizializzo il random
		srand((unsigned)time(NULL));
		int NewPosX = (rand() % (NumCol-1));
		int NewPosY = (rand() % (NumRig-1));
		//Aggiungo i frutti
		(*Frutti).AddFruit(NewPosX,NewPosY);
	}
}

struct ArgumentStartGame{
	class Snake *Snake;
	Fruit *Fruit;
	int NumCol;
	int NumRig;
	bool *Finito;
	PadConfig PadCfg;
	int Difficoltà;
};

void StartGame(ArgumentStartGame Arg){
	bool Dead = false;
	int Direction = 2;
	double SecBase = 0.1;
	if(Arg.Difficoltà == 1) //Facile
		SecBase *= 4;
	else if(Arg.Difficoltà == 2) //Medio
		SecBase *= 2;
	else if(Arg.Difficoltà == 3)//Difficile
		SecBase /= 2;
	else if(Arg.Difficoltà == 4)//Impossibile
		SecBase /= 8;
	while(!Dead){		
		Direction = Attendi(SecBase,&Direction,Arg.PadCfg); //Attendo il tempo e leggo l'input dall'utente
		CreaFrutti(Arg.Fruit,Arg.NumCol,Arg.NumRig); //Se c'è bisogno di nuovi frutti li creo
		Dead = (*Arg.Snake).Move_Next(Direction);//Calcolo la prossima mossa
	}
	*Arg.Finito = true;
}

void ImpostaTesto(sf::Text &Testo,sf::Font &Font,int FontSize){
	Testo.setFont(Font);
	Testo.setCharacterSize(FontSize);
	Testo.setColor(sf::Color::Black);
}

int MenuIniziale(sf::RenderWindow &window,Snake &Snake,sf::Texture *Background,sf::Font &font){
	vector<sf::Text> Voci;
	sf::Event event;
	int FontSize = 50;
	int PosYIniTesto = 35;
	//Creo il testo
	Voci.push_back(sf::Text("Facile"));
	Voci.push_back(sf::Text("Medio"));
	Voci.push_back(sf::Text("Difficile"));
	Voci.push_back(sf::Text("Impossibile"));
	Voci.push_back(sf::Text("Creato da: Alessandro Beltramo\nTestato da: Fili Andrea\nSupporto morale: Elisa Savoca"));
	//Imposto i testi
	for(int i=0;i<Voci.size();i++){
		if (i+1 == Voci.size())
			ImpostaTesto(Voci[i],font,FontSize/4);
		else
			ImpostaTesto(Voci[i],font,FontSize);
		Voci[i].setPosition(35,PosYIniTesto+2*i*FontSize);
	}
	int Selected = 1;
	while(true){
		Sleep(150);
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) // Close window : exit
				exit(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Pad.CheckButton("A")) //Se preme invio esco
			return Selected;
		else if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || Pad.CheckThumb("LY") < -30000 )&& Selected < 4) //Se preme giù cambio menù
			Selected++;
		else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || Pad.CheckThumb("LY") > 30000)&& Selected > 1) //Se preme su cambio menù
			Selected--;
		//Stampo lo sfondo
		Snake.DrawBorder(window,20,Background);
		//Stampo i testi
		for(int i=0;i<Voci.size();i++){
			if(Selected == i+1)
				Voci[i].setColor(sf::Color::Red);
			else
				Voci[i].setColor(sf::Color::Black);
			window.draw(Voci[i]);
		}
		window.display();
	}
}

void CreateResources(void){
	cDAT WriteFile;
	std::vector<std::string> FileList;
	FileList.push_back("Img\\Background.png");
	FileList.push_back("Img\\Frutto.png");
	FileList.push_back("Img\\SnakeTexture.png");
	FileList.push_back("Img\\SnakeHeadTexture.png");
	FileList.push_back("Img\\Font.ttf");
	if (!WriteFile.Create(FileList, "resources.dat"))
		ReturnError("Impossibile creare il file .DAT");
}

void LoadResources(sf::RenderWindow &window,sf::Texture &Background,sf::Texture &Frutto, sf::Texture &Snake,sf::Texture &Head,sf::Font &font,PadConfig &Pad1Cfg){
	//Recupero i file dal file DAT
	 
	 char* buffer;
	 DataFile.Read("Resources.dat");
	 //Nascondo la finestra del terminale
	 HWND hWnd = GetConsoleWindow();
	 ShowWindow( hWnd, SW_HIDE );
	 window.setFramerateLimit(60);
	 window.setVerticalSyncEnabled(true);
	 window.clear();
	/*******************************************************************************************************
	* CARICAMENTO DELLE TEXTURE
	********************************************************************************************************/
	string FileName;
	//Carico lo sfono
	FileName = "Img\\Background.png";
	buffer = DataFile.GetFile(FileName);
	if(!Background.loadFromMemory(buffer,DataFile.GetFileSize(FileName)) || buffer == NULL)
		ReturnError("Errore nel caricare il file "+FileName);
	//Carico il frutto
	FileName = "Img\\Frutto.png";
	buffer = DataFile.GetFile(FileName);
	if(!Frutto.loadFromMemory(buffer,DataFile.GetFileSize(FileName)) || buffer == NULL)
		ReturnError("Errore nel caricare il file "+FileName);
	//Carico lo snake
	FileName = "Img\\SnakeTexture.png";
	buffer = DataFile.GetFile(FileName);
	if(!Snake.loadFromMemory(buffer,DataFile.GetFileSize(FileName)) || buffer == NULL)
		ReturnError("Errore nel caricare il file "+FileName);
	//Carico la testa
	FileName = "Img\\SnakeHeadTexture.png";
	buffer = DataFile.GetFile(FileName);
	if(!Head.loadFromMemory(buffer,DataFile.GetFileSize(FileName)) || buffer == NULL)
		ReturnError("Errore nel caricare il file "+FileName);
	//Carico il font da file
	FileName = "Img\\Font.ttf";
	buffer = DataFile.GetFile(FileName);
	if(!font.loadFromMemory(buffer,DataFile.GetFileSize(FileName)) || buffer == NULL)
		ReturnError("Errore nel caricare il file "+FileName);
	/*******************************************************************************************************
	* Configurazione del pad
	********************************************************************************************************/
	Pad1Cfg.Des = sf::Keyboard::D;
	Pad1Cfg.Sin = sf::Keyboard::A;
	Pad1Cfg.Su = sf::Keyboard::W;
	Pad1Cfg.Giu = sf::Keyboard::S;
	Pad1Cfg.PadDes = "LX";
	Pad1Cfg.PadGiu = "LY";
	Pad1Cfg.PadSin = "LX";
	Pad1Cfg.PadSu = "LY";
}

 int main()
 {
	 sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
	 sf::Texture TBackground;
	 sf::Texture TFrutto;
	 sf::Texture TSnake;
	 sf::Texture THead;
	 sf::Font FontNokia;
	 PadConfig Pad1Cfg;
	 LoadResources(window,TBackground,TFrutto,TSnake,THead,FontNokia,Pad1Cfg);
	 int NumRig = 24;
	 int NumCol = 38;
	 int DimSnake = 20;
	 //Creo l'oggetto frutti
	 Fruit Frutti;
     // Start the game loop
	 sf::Event event;
     while (window.isOpen()){
		 Snake Player1(NumRig,NumCol,10,0,0,&Frutti);
		 Pad.SetVibrations("DX",0);
		/*******************************************************************************************************
		* Lancio il menù iniziale
		********************************************************************************************************/
		int Difficoltà = MenuIniziale(window,Player1,&TBackground,FontNokia);
		/*******************************************************************************************************
		* Configurazione del player1
		********************************************************************************************************/
		//Argomenti del thread
		bool EndP1 = false;
		ArgumentStartGame ArgP1;
		ArgP1.Snake = &Player1;
		ArgP1.Fruit = &Frutti;
		ArgP1.NumCol = NumCol;
		ArgP1.NumRig = NumRig;
		ArgP1.Finito = &EndP1;
		ArgP1.PadCfg = Pad1Cfg;
		ArgP1.Difficoltà = Difficoltà;
		sf::Thread GameP1(&StartGame,ArgP1);
		/*******************************************************************************************************
		* Ciclo del gioco...
		********************************************************************************************************/
		//Lancio il gioco per il giocatore 1
		GameP1.launch();
		stringstream Punteggio;
		sf::Text TextPunteggio(Punteggio.str());
		TextPunteggio.setColor(sf::Color::Black);
		TextPunteggio.setPosition(DimSnake,(NumRig+2)*DimSnake);
		TextPunteggio.setFont(FontNokia);
		TextPunteggio.setCharacterSize(20);
		while(!EndP1){
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){ // Close window : exit
					 exit(0);
				}
			} //fine window pollEvent
			window.clear(); //Svuota lo schermo
			Player1.DrawBorder(window,20,&TBackground); //Stampo lo sfondo
			Frutti.DrawFruits(20,window,&TFrutto);
			Player1.DrawSnake(window,20,&TSnake,&THead); //Stampo lo snake
			//Stampo il punteggio
			Punteggio.str("");
			Punteggio << "Punteggio: " << Player1.GetPoint();
			TextPunteggio.setString(Punteggio.str());
			window.draw(TextPunteggio);
			window.display(); //Update the window
		}
        /*******************************************************************************************************
		* Snake morto. In attesa dell'input dell'utente per ricominciare
		********************************************************************************************************/
         //window.clear();
		 Pad.SetVibrations("DX",100);
		 string Str = "Game over!!\nPremi start o R per ricominciare";
		 TextPunteggio.setString(Str);
		 TextPunteggio.setPosition((NumCol/2)*DimSnake,(NumRig+2)*DimSnake);
		 window.draw(TextPunteggio); //lo disegno sul target selezionato
		 window.display();
		 while(!Pad.CheckButton("START") && !sf::Keyboard::isKeyPressed(sf::Keyboard::R)){ //fintanto che non si preme start o spazio
			Sleep(5);
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed) // Close window : exit
					 return EXIT_SUCCESS;
			} //fine window pollEvent
		 } //fine checkbutton
     } //Fine window open
     return EXIT_SUCCESS;
 }