/*
*********************************************************************************************************
*
* Filename      : MIDI.C
* Version       : V1.00
* Programmer(s) : Julian Schotborgh
*
*  21-10-19 	Opstart midi.c en maken midi_proc()
*********************************************************************************************************
*/

#include 	"MIDI.h"

int MIDI_PROC(uint8_t MIDI_DATA[2])
{
	uint8_t MIDI_STATUS;								// binnengekomen status byte
	uint8_t FUNC_VAR[1];								// binnengekomen data voor de functies
	char MIDI_FUNC;										// variabele om fucntie nibble op te slaan
	char MIDI_CHANNEL;									// variabele om channel nibble op te slaan
	int err = 0;											// error variabele

	MIDI_FUNC = (char)(MIDI_STATUS & 0x0F);				// lsb bits van byte omzetten in nibble
	MIDI_CHANNEL = (char)((MIDI_STATUS & 0x0F)>>4);		// msb bits van byte omzetten in nibble

	for (int i=0;i<2;i++)								// data halen uit binnengekomen bericht
	{
		FUNC_VAR[i] = MIDI_DATA[i+1];
	}

	switch(MIDI_FUNC)									// switch om data naar goeie YM functie te sturen
	{
	case NOTE_OFF:
		err = YM_NOTE_ON(MIDI_CHANNEL,FUNC_VAR[0],0);
		break;
	case NOTE_ON:
		err = YM_NOTE_ON(MIDI_CHANNEL,FUNC_VAR[0],FUNC_VAR[1]);
		break;
	case CONT_CHANGE:
		err = YM_CONT_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],FUNC_VAR[1]);
		break;
	case PROG_CHANGE:
		err = YM_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0]);
		break;
	case PITCH:
		err = YM_PITCH(MIDI_CHANNEL,FUNC_VAR[1]);
		break;

	return err;
	}




}
