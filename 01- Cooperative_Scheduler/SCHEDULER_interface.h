/****************************************************************************
* Title                 :   SCHEDULER   
* Filename              :   SCHEDULER_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
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
*  10/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  SCHEDULER_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

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

typedef void (*ptr_TaskCode)(void *);

/*!<Task Structure*/
typedef struct
{
   ptr_TaskCode Task_PtrCode;
   int          Task_intReleaseTime;
   int          Task_intPeriod;
   char         Task_u8RunMeFlag;
   void    *    Task_PtrVoidParameter;
}Task_t;

typedef Task_t* PtrStructTask_QueueENTRY;

/*!<Queue Definitions*/
typedef struct queuenode
{
    PtrStructTask_QueueENTRY  QueueNode_Entry;
    struct queuenode        * QueueNode_Next;
}QueueNode_t;

typedef struct Queue
{
    QueueNode_t * Queue_Front;
    QueueNode_t * Queue_Rear;
    int           Queue_Size;
}Queue_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

int  SCHEDULER_intCreateTask(ptr_TaskCode Copy_PtrTaskCode,int Copy_intReleaseTime, int Copy_intPeriod, char Copy_Flag , void * Copy_PtrTaskParameter);
void SCHEDULER_voidInitScheduler(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidStartScheduler(void);
int  SCHEDULER_intAddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidUpdateScheduler(void * Copy_voidPtrQueue);
void SCHEDULER_voidDispatchTasks(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidDeleteTask(int Copy_intTaskPosition,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidReplaceTask(int Copy_intTaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
int  SCHEDULER_intIsQueueEmpty(Queue_t * Copy_PtrQueue);
int  SCHEDULER_intIsQueueFull(Queue_t * Copy_PtrQueue);
int  SCHEDULER_intQueueSize(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidClearQueue(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY Copy_QueueEntry));


#endif /*File_H_*/

/*** End of File **************************************************************/
