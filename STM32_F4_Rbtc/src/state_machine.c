
//#include "state_machine.h"
#include "main.h"


void state_idle(){

	SSD1306_GotoXY(10,27);
	SSD1306_Puts("Idle", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
	SSD1306_Fill(0x00);

};
void state_running(){

	SSD1306_GotoXY(10,27);
	SSD1306_Puts("Running", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
	SSD1306_Fill(0x00);
};

void state_error(){

	SSD1306_GotoXY(10,27);
	SSD1306_Puts("Error", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
	SSD1306_Fill(0x00);
};

void state_stop(){

	SSD1306_GotoXY(10,27);
	SSD1306_Puts("Stop", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
	SSD1306_Fill(0x00);
};

const state_machine_t state_machine[] = {
		{IDLE_STATE, &state_idle},
		{RUNNING_STATE, &state_running},
		{ERROR_STATE, &state_error},
		{STOP_STATE, &state_stop}
};


void state_check(){

	state_machine[Machine.state_t].state_machine_fun();

}


