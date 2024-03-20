
#include "compiler.h"
#include <avr/io.h>
//#include "conf_example.h"

#define LEFT_BTN        PC0
#define RIGHT_BTN       PD1
//Add more buttons
#define LED_ON_DELAY    300
#define LED_OFF_DELAY   50
#define SPEED_UP        20

uint8_t btnArray[] =
{
	LEFT_BTN,
	RIGHT_BTN  
	//Add more buttons
};


// Enumerations
typedef enum ButtonState_tag
{
	eBtnUndefined = 0,
	eBtnShortPressed, // if duration is lower than 999mS, its a short press
	eBtnLongPressed  // else if > 1000ms its a long Press
} eButtonState_t;

typedef enum PlayerInputState_tag
{
	eWaiting = 0,
	eCorrect,
	eIncorrect
} ePlayerInputState_t;

typedef enum ButtonId_tag
{
	eLeftButton = 0, // This enum must follow btnArray
	eRightButton,
	eMaxButtonId
} eButtonId_t;

typedef enum GameState_tag
{
	eGameRestart = 0,
	eWaitForStart,
	eOngoingGame,
	eEnd
} eGameState_t;

// Global variable
uint32_t _millis;
uint8_t score;

static void initIO(void)
{
	// FIXME:
	// add code to initialize all IO pins for the assigment

	//DDRB = 0x03; PB0 and PB1 as output
	//DDRD ... 
	//Set LED GPIO as a push/pull output 
	
	
}

void playSequence(eGameState_t gameState)
{
	// FIXME:
	// Playback the corresponding animation of the gameState parameter
}

eButtonState_t checkButtons(eButtonId_t *buttonNumber)
{
	// FIXME:
	// Polls each button and returns the press state and the corresponding button
	*buttonNumber = eMaxButtonId;
	return eBtnUndefined;
}

ePlayerInputState_t checkPlayerInput(eButtonState_t buttonState, eButtonId_t buttonId)
{
	// FIXME:
	// Waits for player input and verifies that it is matching the pattern
	return eWaiting;
}

int main(void)
{
	eGameState_t  currentGameState = eGameRestart;
	ePlayerInputState_t playerInputState;
	eButtonId_t buttonId;
	eButtonState_t buttonState;

	initIO();

	while(1)
	{
		buttonState = checkButtons(&buttonId);
		
		if (buttonState == eBtnLongPressed)
		currentGameState = eGameRestart;

		switch(currentGameState)
		{
			case eGameRestart:
			//Init game variables
			currentGameState++;
			break;

			case eWaitForStart:
			playSequence(eWaitForStart);
			if (buttonState == eBtnShortPressed)
			currentGameState++;
			break;

			case eOngoingGame:
			playSequence(eOngoingGame);
			playerInputState = checkPlayerInput(buttonState, buttonId);
			if (playerInputState == eCorrect)
			{
				score++;
			}
			else if (playerInputState == eIncorrect)
			{
				currentGameState = eEnd;
			}
			break;
			case eEnd:
			playSequence(eEnd);
			break;
		}
		//Delay(1); Call assembly function for a 1 millisec Delay
		_millis++;
	}
}