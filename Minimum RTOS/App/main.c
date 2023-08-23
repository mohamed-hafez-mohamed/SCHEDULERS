/*******************************************************************************
* Title                 :   main  
* Filename              :   main.c
* Author                :   Mohamed Hafez
* Origin Date           :   04/08/2020
* Version               :   1.0.0
* Compiler              :   ARM Compiler Version 6
* Target                :   STM32F103
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/08/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file main.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/		
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdlib.h>
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "MIRTOS_interface.h"
#include "SWC1_interface.h"
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
Queue_t          ReadyQueue;
static   u32     Task1_StackArea[40];
static   u32     Task2_StackArea[40];
/******************************************************************************
* Function Definitions
*******************************************************************************/

int main()
{
	SWC1_voidInitalizePeripherals();
	MIRTOS_voidInitializeOs(&ReadyQueue);
	/* Create Cortex-M Stack Frame For Task1 */
   MIRTOS_u8CreateTask(0, 0,   1000, &Task1_Blinky_Red,    NULL, Task1_StackArea, sizeof(Task1_StackArea),&ReadyQueue);
	/* Create Cortex-M Stack Frame For Task2 */
	MIRTOS_u8CreateTask(1, 275, 1000, &Task2_Blinky_Yellow, NULL, Task2_StackArea, sizeof(Task2_StackArea),&ReadyQueue);
   // Run Os.
   MIRTOS_voidRunOs(&ReadyQueue);
	while(1)
	{
		
	}
}

/*************** END OF FUNCTIONS ***************************************************************************/
