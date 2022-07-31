/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    led.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>

#include "led.h"
#include "peripheral/gpio/plib_gpio.h"

#include "FreeRTOS.h"
#include "task.h"


#define DDR_START		(0xA8000000)

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the LED_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

LED_DATA ledData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void LED_Initialize ( void )

  Remarks:
    See prototype in led.h.
 */

void LED_Initialize ( void )
	{
    /* Place the App state machine in its initial state. */
    ledData.state		= LED_STATE_INIT;
	ledData.delayInMs	= 500;


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
	}


/******************************************************************************
  Function:
    void LED_Tasks ( void )

  Remarks:
    See prototype in led.h.
 */

void LED_Tasks ( void )
	{
	static uint32_t val		= 0x0;
	static uint32_t *ptr	= (uint32_t *)DDR_START;

    /* Check the application's current state. */
    switch ( ledData.state )
		{
        /* Application's initial state. */
        case LED_STATE_INIT:
			{
            bool appInitialized = true;


            if (appInitialized)
				{

                ledData.state = LED_STATE_SERVICE_TASKS;
				}
            break;
			}

        case LED_STATE_SERVICE_TASKS:
			{
			const TickType_t xDelay = ledData.delayInMs / portTICK_PERIOD_MS;
			GPIO_RH0_Toggle();
			
			*ptr = val;
			if (*ptr != val)
				{
				printf("*\nerror @ 0x%p\n", ptr);
				}
			else
				{
				printf(".");
				if ((val %24) == 0)
					printf("\n");
				}
			val ++;
			ptr ++;
			
			if (val > 0xffffff)
				{
				val = 0;
				ptr = (uint32_t *)DDR_START;
				}
			
			vTaskDelay(xDelay);

            break;
			}

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
			{
            /* TODO: Handle error in application's state machine. */
            break;
			}
		}
	}



void LED_SetDelay(int delayInMs)
	{
	ledData.delayInMs = delayInMs;
	}

/*******************************************************************************
 End of File
 */
