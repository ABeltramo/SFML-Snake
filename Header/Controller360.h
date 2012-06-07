#ifndef CONTROLLER360_H_INCLUDED
#define CONTROLLER360_H_INCLUDED

#include <Windows.h>
#include <XInput.h>                       // Defines XBOX controller API
#pragma comment(lib, "XInput.lib")

class Controller360{
	  private:
		  XINPUT_STATE Stato;
      public:
		int NumPad; //NumPad compreso tra 0 e 3
		Controller360(int NumPad); 
        bool CheckControllerStatus(void);
		bool CheckButton(char * Btn); //Restituisce se un bottone è premuto oppure no
		int CheckTrigger(char * Btn); //Restituisce il valore dei trigger
		float CheckThumb(char * Btn); //Restituisce il valore dei pad (LX, LY o RX, RY)
		void SetVibrations(char * Pos, unsigned int Value); //Setta la vibrazione o a SX o a DX: Minimo 0 Massimo 100
};

#endif