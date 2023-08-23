/****************************************************************************
* Title                 :   MIRTOS   
* Filename              :   MIRTOS_interface.h
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
/** @file  MIRTOS_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef MIRTOS_INTERFACE_H_
#define MIRTOS_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void (*ptr_TaskCode)(void * );

/*Task States*/
typedef enum
{
   MIRTOS_TASK_STATE_DORMANT          = 0,
   MIRTOS_TASK_STATE_READY,
   MIRTOS_TASK_STATE_READY_TO_RUN,
   MIRTOS_TASK_STATE_RUNNING,
   MIRTOS_TASK_STATE_SUSPENDED
}Task_States_t;

// Task Control Block
typedef struct 
{
   void              * Task_voidPtrStackPointer;    /* Stack Pointer */
   u8                  TASK_u8Priority;
   u16                 Task_u16ReleaseTime;
   u16                 Task_u16Period;
   Task_States_t       Task_u8State;
   ptr_TaskCode        Task_PtrCode;
   void              * Task_PtrVoidParameter;
}OSTask_t;

typedef OSTask_t* PtrStructTask_QueueENTRY;

/*!<Queue Definitions*/
typedef struct queuenode
{
   OSTask_t          * QueueNode_Entry;
   struct queuenode  * QueueNode_Next;
}QueueNode_t;

typedef struct Queue
{
   QueueNode_t       * Queue_Front;
   QueueNode_t       * Queue_Rear;
   u8                  Queue_Size;
}Queue_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void MIRTOS_voidIdeleTask(void   * Copy_voidPointer);
void MIRTOS_voidInitializeOs(Queue_t * Copy_PtrQueue);
u8   MIRTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16ReleaseTime, u16 Copy_u16Period,
     ptr_TaskCode Copy_PtrTaskCode,void* Copy_PtrTaskParameter,void* Copy_voidPtrStack,u32 Copy_u32StackSize,
		 Queue_t* Copy_PtrQueue);
void MIRTOS_voidRunOs(Queue_t * Copy_PtrQueue);
u8   MIRTOS_u8AddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue);
// This Function Must Be Called With Interrupt Disabled.
void MIRTOS_voidScheduleTasks(void * Copy_voidPtrQueue);
// Auxaliary Functions.
void MIRTOS_voidSuspendTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void MIRTOS_voidResumeTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void MIRTOS_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void MIRTOS_voidDeleteTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue);
void MIRTOS_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void MIRTOS_voidReplaceTask(u8 Copy_u8TaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
u8   MIRTOS_u8IsQueueEmpty(Queue_t * Copy_PtrQueue);
u8   MIRTOS_u8IsQueueFull(Queue_t * Copy_PtrQueue);
u8   MIRTOS_u8QueueSize(Queue_t * Copy_PtrQueue);
void MIRTOS_voidClearQueue(Queue_t * Copy_PtrQueue);
void MIRTOS_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY Copy_QueueEntry));

#endif /*File_H_*/

/*** End of File **************************************************************/
