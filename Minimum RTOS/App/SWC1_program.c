/*******************************************************************************
* Title                 :   SWC1 
* Filename              :   SWC1_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   16/01/2021
* Version               :   1.0.0
* Compiler              :   ARM Compiler Version 6
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  16/01/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file SWC1_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SWC1_interface.h"
#include "SWC1_config.h"
#include "SWC1_private.h"
#include <stdlib.h>
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "MIRTOS_interface.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern Queue_t ReadyQueue;
static u8      Global_u8LedStatus1;
static u8      Global_u8LedStatus2;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void SWC1_voidInitalizePeripherals(void)
{
  /* Initialize the RCC to HSE */
  MRCC_voidInitSysClock();
  MRCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL);
  MGPIO_voidSetPinMode(PINA0, GPIO_OUTPUT_10M_PULL_UP_DN);
  MGPIO_voidSetPinMode(PINA1, GPIO_OUTPUT_10M_PULL_UP_DN);
  MSTK_voidInit();
  __enable_irq();
}

void Task1_Blinky_Red(void * Copy_voidPointer)
{
  (void)Copy_voidPointer;
	while(1)
  {
	  if(Global_u8LedStatus1 == 0)
    {
      MGPIO_voidSetPinValue(PINA0,HIGH);
      Global_u8LedStatus1 = 1;
    }
    else if(Global_u8LedStatus1 == 1)
    {
      MGPIO_voidSetPinValue(PINA0,LOW);
      Global_u8LedStatus1 = 0;
    }
		MIRTOS_voidScheduleTasks((void *)(&ReadyQueue));
  }
}

void Task2_Blinky_Yellow(void * Copy_voidPointer)
{
	(void)Copy_voidPointer;
	while(1)
  {
	  if(Global_u8LedStatus2 == 0)
    {  
      MGPIO_voidSetPinValue(PINA1,HIGH);
	    Global_u8LedStatus2 = 1;
    }
    else if(Global_u8LedStatus2 == 1)
    {
      MGPIO_voidSetPinValue(PINA1,LOW);
	    Global_u8LedStatus2 = 0;
    }
		MIRTOS_voidScheduleTasks((void *)(&ReadyQueue));
  }
}



/*************** END OF FUNCTIONS ***************************************************************************/
