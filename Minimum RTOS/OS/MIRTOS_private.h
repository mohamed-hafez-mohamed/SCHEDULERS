/****************************************************************************
* Title                 :   MIRTOS   
* Filename              :   MIRTOS_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   15/01/2021
* Version               :   1.0.0
* Compiler              :   ARM Compiler Version 6
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  15/01/21   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  MIRTOS_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef MIRTOS_PRIVATE_H_
#define MIRTOS_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/******************************************************************************
* Typedefs
*******************************************************************************/
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define SCB_ICSR_ADDRESS            0xE000ED04
#define SCB_ICSR                    *((volatile u32 *)SCB_ICSR_ADDRESS)
#define SCB_SHPR3_ADDRESS           0xE000ED20
#define SCB_SHPR3                   *((volatile u32 *)SCB_SHPR3_ADDRESS)
#define PENDSV                      28
#define SET_LOWSET_PRIORITY_LEVEL   0xFFU
#define PENDSV_PRIORITY_BITS        16
#define SYSTIC_PRIORITY_BITS        24
#define SYSTIC_HIGH_PENDSV_LOW      0x00FF0000U

#define MIRTOS_QUEUENODE_SIZE      8
#define MIRTOS_TASKSTRUCT_SIZE     14
#define MIRTOS_ONE_SHOT_TASK       0
#define TIME_TO_RUN_COME           0
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#endif
/*** End of File **************************************************************/
