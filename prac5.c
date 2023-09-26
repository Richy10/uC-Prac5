/**
 * \file
 *
 * \brief megaAVR STK600 GPIO Example
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

 /**
 * \mainpage
 * \section intro Introduction
 * This example demonstrates GPIO port access, pin access, pin interrupt and
 * pin pull up configuration.
 *
 * \section files Files:
 * - mega_gpio_example.c: megaAVR GPIO example application
 * - conf_example.h: Example configuration
 *
 * \section setup Setup
 * This example is made for STK600 with two 10-pin cables in the following
 * strap configuration:
 * - PORTB <-> SWITCHES
 * - PORTD <-> LEDS
 *
 * \section description Description
 * The example will utilize different registers for setting and reading port
 * and pin GPIOs. These GPIOs are connected to switches and LEDs on the STK600.
 *
 * In the end of the example pin change interrupts are enabled and can be
 * tested with STK600 SW0. This will toggle LED0 from the interrupt handler.
 * Not all megaAVR devices supports pin change interrupts, so for those this
 * is disabled.
 *
 * For the best demonstration it's recommended to run this in a debug session
 * and single step through the different operations.
 *
 * \section compinfo Compilation Info
 * This software was written for the <A href="http://gcc.gnu.org/">GNU GCC</A>
 * for AVR. \n
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "compiler.h"
#include <avr/io.h>
//#include "conf_example.h"

#define LEFT_BTN        PD2
#define RIGHT_BTN       PD3
#define LED_ON_DELAY    300
#define LED_OFF_DELAY   50
#define SPEED_UP        20

uint8_t btnArray[] =
{
	LEFT_BTN,
	RIGHT_BTN  
};

enum
{
	eGoingLeft = -1,
	eGoingRight = 1
};



// Enumerations
typedef enum ButtonState_tag
{
	eBtnUndefined = 0,
	eBtnShortPressed, 
	eBtnLongPressed //se considera long press despues de 1000mS
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
{/*
	// FIXME:
	// Replace the following code and insert
	// code to initialize all IO pins for the assigment
	gpio_reset_pin(LED_GPIO);
	gpio_reset_pin(BTN_GPIO);
	//Set LED GPIO as a push/pull output 
	gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
	//Set LED GPIO as a push/pull output 
	gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
	gpio_pullup_en(BTN_GPIO);
	
	*/
}

void playSequence(eGameState_t gameState)
{
	// FIXME:
	// Playback the corresponding animation of the gameState parameter
	//gpio_set_level(LED_GPIO, !gpio_get_level(BTN_GPIO));
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

void delayMs(uint16_t ms)
{
	//vTaskDelay(ms / portTICK_PERIOD_MS);
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
		delayMs(1);
		_millis++;
	}
}