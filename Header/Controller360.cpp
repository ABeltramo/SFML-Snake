#include "Controller360.h"
#include <map>
using namespace std;

Controller360::Controller360(int NumPad){
	ZeroMemory( &this->Stato, sizeof(XINPUT_STATE) ); // Azzera lo stato del controller
	this->NumPad = NumPad;
}

bool Controller360::CheckControllerStatus(void)
{
      DWORD dwResult;
      // Recupera lo stato del controller Selezionato
      dwResult = XInputGetState(this->NumPad, &this->Stato);
      if(dwResult == ERROR_SUCCESS)
		return true;
	 else
		return false;
}

bool Controller360::CheckButton(char * Btn){
	map<char*,WORD> Bottoni; //Mappa di valori del controller
	Bottoni["A"] = XINPUT_GAMEPAD_A;
	Bottoni["B"] = XINPUT_GAMEPAD_B;
	Bottoni["X"] = XINPUT_GAMEPAD_X;
	Bottoni["Y"] = XINPUT_GAMEPAD_Y;
	Bottoni["BACK"] = XINPUT_GAMEPAD_BACK;
	Bottoni["START"] = XINPUT_GAMEPAD_START;
	Bottoni["PADUP"] = XINPUT_GAMEPAD_DPAD_UP;
	Bottoni["PADDOWN"] = XINPUT_GAMEPAD_DPAD_DOWN;
	Bottoni["PADLEFT"] = XINPUT_GAMEPAD_DPAD_LEFT;
	Bottoni["PADRIGHT"] = XINPUT_GAMEPAD_DPAD_RIGHT;
	Bottoni["RB"] = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	Bottoni["LB"] = XINPUT_GAMEPAD_LEFT_SHOULDER;
	Bottoni["BTNDX"] = XINPUT_GAMEPAD_RIGHT_THUMB;
	Bottoni["BTNRX"] = XINPUT_GAMEPAD_LEFT_THUMB;

	XInputGetState(this->NumPad, &this->Stato ); //Aggiorno lo stato del controller
	if(this->Stato.Gamepad.wButtons == Bottoni[Btn])
		return true;
	else
		return false;
}

int Controller360::CheckTrigger(char * Btn){
	XInputGetState(this->NumPad, &this->Stato );
	if(Btn == "LT") return this->Stato.Gamepad.bLeftTrigger;
	else if(Btn == "RT") return this->Stato.Gamepad.bRightTrigger;
	else return 0;
}

float Controller360::CheckThumb(char * Btn){
	XInputGetState(this->NumPad, &this->Stato );
	if(Btn == "LX") return this->Stato.Gamepad.sThumbLX;
	else if(Btn == "LY") return this->Stato.Gamepad.sThumbLY;
	else if(Btn == "RX") return this->Stato.Gamepad.sThumbRX;
	else if(Btn == "RY") return this->Stato.Gamepad.sThumbRY;
	else return 0;
}

void Controller360::SetVibrations(char * Pos, unsigned int Value){
	long int ValMax = 65535;
	XINPUT_VIBRATION vibration;
    ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
	if(Pos == "DX") vibration.wRightMotorSpeed = (Value / 100)*ValMax;
	else if(Pos == "SX") vibration.wLeftMotorSpeed = (Value / 100)*ValMax;
	else return;
	XInputSetState(this->NumPad, &vibration );
}