/*******************************************************************************
* Title                 :   MIRTOS 
* Filename              :   MIRTOS_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   15/01/2021
* Version               :   1.0.0
* Compiler              :   ARM Compiler Version 6
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  15/01/21   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file MIRTOS_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdint.h>
#include <stdlib.h>
#include "MIRTOS_interface.h"
#include "MIRTOS_config.h"
#include "MIRTOS_private.h"
#include "STK_interface.h"
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static OSTask_t * volatile Static_OSPtrToCurrentTask; /* Pointer To The Current Task Running*/
static OSTask_t * volatile Static_OSPtrToNextTask;    /* Pointer To The Next Task To Run*/
static u32                 Task0_StackArea[40];
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define THERE_ARE_TASKS_RUNNING ((Static_OSPtrToCurrentTask) != ((OSTask_t *)(0)))
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void MIRTOS_voidIdeleTask(void * Copy_voidPointer)
{
	while(1)
	{
		(void)Copy_voidPointer;
      //!<TODO: CPU Goes To Sleep..
	}
}

void MIRTOS_voidInitializeOs(Queue_t * Copy_PtrQueue)
{
   // Set The SysTic Exception To The Heighest Level
   // Set The PendSv Exception To The Lowset   Level
   SCB_SHPR3 = SYSTIC_HIGH_PENDSV_LOW;
   Copy_PtrQueue->Queue_Front = NULL;
   Copy_PtrQueue->Queue_Rear  = NULL;
   Copy_PtrQueue->Queue_Size  = 0;
   MIRTOS_u8CreateTask(LOWSET_PRIORITY, 0, 1, &MIRTOS_voidIdeleTask,  NULL, Task0_StackArea, sizeof(Task0_StackArea),Copy_PtrQueue); 
}

void MIRTOS_voidRunOs(Queue_t * Copy_PtrQueue)
{
   MSTK_voidSetIntervalPeriodic_ms(MIRTOS_ONE_TICK_IN_MS, &MIRTOS_voidScheduleTasks, (void *)(Copy_PtrQueue));
}

u8 MIRTOS_u8AddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue)
{
   QueueNode_t  * Local_PtrQueueNode = (QueueNode_t *)malloc(sizeof(QueueNode_t));
   if(! Local_PtrQueueNode)
   {
      return 0;
   }
   else
   {
      Local_PtrQueueNode->QueueNode_Entry = Copy_PtrQueueEntry;
      Local_PtrQueueNode->QueueNode_Next  = NULL;
      if(!Copy_PtrQueue->Queue_Rear)
      {
         Copy_PtrQueue->Queue_Front = Local_PtrQueueNode;
      }
      else
      {
         Copy_PtrQueue->Queue_Rear->QueueNode_Next = Local_PtrQueueNode;
      }
      Copy_PtrQueue->Queue_Rear = Local_PtrQueueNode;
      Copy_PtrQueue->Queue_Size++;
      return 1;
   }
}

u8 MIRTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16ReleaseTime, u16 Copy_u16Period,
   ptr_TaskCode Copy_PtrTaskCode,void* Copy_PtrTaskParameter,void* Copy_voidPtrStack,u32 Copy_u32StackSize,
	 Queue_t* Copy_PtrQueue)
{
   OSTask_t * PtrToTCB               = (OSTask_t*)malloc(sizeof(OSTask_t));
   PtrToTCB->TASK_u8Priority         = Copy_u8Priority;
   PtrToTCB->Task_u16ReleaseTime     = Copy_u16ReleaseTime;
   PtrToTCB->Task_u16Period          = Copy_u16Period;
   PtrToTCB->Task_u8State            = MIRTOS_TASK_STATE_DORMANT;
   PtrToTCB->Task_PtrCode            = Copy_PtrTaskCode;
   PtrToTCB->Task_PtrVoidParameter   = Copy_PtrTaskParameter;
   /*
   * Round Down The Top Of The Stack To The 8-Byte Boundary
   * Note: ARM Cortex-M Stack Grows Down From High To Low Memory
   */
   u32 * Local_u32TaskStackPointer = (u32 *)((((u32)(Copy_voidPtrStack) + Copy_u32StackSize) / MIRTOS_ALIGN_8_BYTE_BOUNDARY) * MIRTOS_ALIGN_8_BYTE_BOUNDARY);
   u32 * Local_u32StackLimt;
   // Task Stack Frame
   *(--Local_u32TaskStackPointer) = SET_THUMB;                 /* PSR  Set Thumb Bit      */      
   *(--Local_u32TaskStackPointer) = (u32)(Copy_PtrTaskCode);   /* Initialize And Save PC  */
   *(--Local_u32TaskStackPointer) = 0x0000000EU;               /* Initialize And Save LR  */
   *(--Local_u32TaskStackPointer) = 0x0000000CU;               /* Initialize And Save R12 */
   *(--Local_u32TaskStackPointer) = 0x00000003U;               /* Initialize And Save R3  */
   *(--Local_u32TaskStackPointer) = 0x00000002U;               /* Initialize And Save R2  */
   *(--Local_u32TaskStackPointer) = 0x00000001U;               /* Initialize And Save R1  */
   *(--Local_u32TaskStackPointer) = 0x00000000U;               /* Initialize And Save R0  */
   *(--Local_u32TaskStackPointer) = 0x0000000BU;               /* Initialize And Save R11 */
   *(--Local_u32TaskStackPointer) = 0x0000000AU;               /* Initialize And Save R10 */
   *(--Local_u32TaskStackPointer) = 0x00000009U;               /* Initialize And Save R9  */
   *(--Local_u32TaskStackPointer) = 0x00000008U;               /* Initialize And Save R8  */
   *(--Local_u32TaskStackPointer) = 0x00000007U;               /* Initialize And Save R7  */
   *(--Local_u32TaskStackPointer) = 0x00000006U;               /* Initialize And Save R6  */
   *(--Local_u32TaskStackPointer) = 0x00000005U;               /* Initialize And Save R5  */
   *(--Local_u32TaskStackPointer) = 0x00000004U;               /* Initialize And Save R4  */
   // Save The Top Of The Stack In The Task Attributes*/
   PtrToTCB->Task_voidPtrStackPointer = Local_u32TaskStackPointer; 
   // Round Up The Bottom Of The Stack To The 8-Byte Boundary 
   Local_u32StackLimt = (u32 *)(((((u32)(Copy_voidPtrStack) - (1U)) / MIRTOS_ALIGN_8_BYTE_BOUNDARY) + (1U)) * MIRTOS_ALIGN_8_BYTE_BOUNDARY);
   MIRTOS_u8AddTask(PtrToTCB, Copy_PtrQueue);
   //!<TODO: Return Status.
}

void MIRTOS_voidScheduleTasks(void * Copy_voidPtrQueue)
{
   Queue_t     * Local_PtrQueue       = (Queue_t *)Copy_voidPtrQueue;
   QueueNode_t * Local_PtrQueueNode   = Local_PtrQueue->Queue_Front;
   QueueNode_t * Local_PtrNextTask    = Local_PtrQueueNode;
   u8            Local_u8Priority     = LOWSET_PRIORITY;
   u8            Local_u8TaskCounter  = 0;
   u8            Local_u8TaskPosition = 0;
   for(Local_PtrQueueNode = Local_PtrQueue->Queue_Front;Local_PtrQueueNode;Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next)
   {
      /*!<Check if there is a task at this location*/
      if(Local_PtrQueueNode->QueueNode_Entry->Task_PtrCode)
      {
         if(Local_PtrQueueNode->QueueNode_Entry->Task_u16ReleaseTime == TIME_TO_RUN_COME)
         {
            /*!<The task is ready to run*/
            Local_PtrQueueNode->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_READY_TO_RUN;
            if(Local_PtrQueueNode->QueueNode_Entry->TASK_u8Priority <= Local_u8Priority)
            {
               Local_u8TaskPosition   = Local_u8TaskCounter;
               Local_u8Priority       = Local_PtrQueueNode->QueueNode_Entry->TASK_u8Priority;
               Local_PtrNextTask      = Local_PtrQueueNode;
               __disable_irq();
               Static_OSPtrToNextTask = Local_PtrQueueNode->QueueNode_Entry;
               __enable_irq();
            }
         }
         else
         {
            /*!<Not yet ready to run: just decrement the Release Time*/
            Local_PtrQueueNode->QueueNode_Entry->Task_u16ReleaseTime -= MIRTOS_ONE_TICK_IN_MS;
				Local_PtrQueueNode->QueueNode_Entry->Task_u8State         = MIRTOS_TASK_STATE_SUSPENDED;
         }
      }
      Local_u8TaskCounter++;
   }
   if(Local_PtrNextTask->QueueNode_Entry->Task_u16Period)
   {
      /*!<Schedule periodic tasks to run again*/
      Local_PtrNextTask->QueueNode_Entry->Task_u16ReleaseTime = Local_PtrNextTask->QueueNode_Entry->Task_u16Period;
   }
   __disable_irq();
   if(Static_OSPtrToNextTask != Static_OSPtrToCurrentTask)
   {
		Local_PtrNextTask->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_RUNNING;
      SET_BIT(SCB_ICSR, PENDSV);
   }
   __enable_irq();
}

void MIRTOS_voidSuspendTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
   u8 Local_u8Counter;
   QueueNode_t * Local_PtrQueueNode;
   if(Copy_u8TaskPosition == 0)
   {
      Copy_PtrQueue->Queue_Front->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_SUSPENDED;
   }
   else if(Copy_u8TaskPosition > 0)
   {
       for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
      {
         Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
      }
      
      Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_SUSPENDED;
   }
   else
   {
      //!<TODO: Error Code
   }

}

void MIRTOS_voidResumeTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
   u8 Local_u8Counter;
   QueueNode_t * Local_PtrQueueNode;
   if(Copy_u8TaskPosition == 0)
   {
      Copy_PtrQueue->Queue_Front->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_READY;
   }
   else if(Copy_u8TaskPosition > 0)
   {
       for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
      {
         Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
      }
      
      Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry->Task_u8State = MIRTOS_TASK_STATE_READY;
   }
   else
   {
      //!<TODO: Error Code
   }
}

void MIRTOS_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
   QueueNode_t * Local_PtrQueueNode = Copy_PtrQueue->Queue_Front;
   *Copy_PtrQueueEntry = Local_PtrQueueNode->QueueNode_Entry;
   if(!Copy_PtrQueue->Queue_Front)
   {
      Copy_PtrQueue->Queue_Rear = NULL;
   }
}

void MIRTOS_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
   QueueNode_t *Local_PtrQueueNode = Copy_PtrQueue->Queue_Front;
   *Copy_PtrQueueEntry = Local_PtrQueueNode->QueueNode_Entry;
   Copy_PtrQueue->Queue_Front = Local_PtrQueueNode->QueueNode_Next;
   free(Local_PtrQueueNode->QueueNode_Entry);
   free(Local_PtrQueueNode);
   if(!Copy_PtrQueue->Queue_Front)
   {
      Copy_PtrQueue->Queue_Rear = NULL;
   }
   Copy_PtrQueue->Queue_Size--;
}

void MIRTOS_voidDeleteTask(u8 Copy_u8TaskPosition,Queue_t * Copy_PtrQueue)
{
   u8 Local_u8Counter;
   QueueNode_t * Local_PtrQueueNodeTemp;
   QueueNode_t * Local_PtrQueueNode;
   if(Copy_u8TaskPosition == 0)
   {
      Local_PtrQueueNodeTemp = Copy_PtrQueue->Queue_Front->QueueNode_Next;
      free(Copy_PtrQueue->Queue_Front->QueueNode_Entry);
      free(Copy_PtrQueue->Queue_Front);
      Copy_PtrQueue->Queue_Front = Local_PtrQueueNodeTemp;
   }
   else
   {
      for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front,Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition - 1;Local_u8Counter++)
      {
         Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
      }
      Local_PtrQueueNodeTemp = Local_PtrQueueNode->QueueNode_Next->QueueNode_Next;
      free(Local_PtrQueueNode->QueueNode_Next->QueueNode_Entry);
      free(Local_PtrQueueNode->QueueNode_Next);
      Local_PtrQueueNode->QueueNode_Next = Local_PtrQueueNodeTemp;
   }
   Copy_PtrQueue->Queue_Size--;
}

void MIRTOS_voidReplaceTask(u8 Copy_u8TaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue)
{
   u8 Local_u8Counter;
   QueueNode_t * Local_PtrQueueNode;
   if(Copy_u8TaskPosition == 0)
   {
     Copy_PtrQueue->Queue_Front->QueueNode_Entry = *Copy_PtrQueueEntry;
   }
   else
   {
     for(Local_PtrQueueNode = Copy_PtrQueue->Queue_Front, Local_u8Counter = 0;Local_u8Counter < Copy_u8TaskPosition;Local_u8Counter++)
     {
        Local_PtrQueueNode = Local_PtrQueueNode->QueueNode_Next;
     }
     Local_PtrQueueNode->QueueNode_Entry = *Copy_PtrQueueEntry;
   }

}

u8  MIRTOS_u8IsQueueEmpty(Queue_t * Copy_PtrQueue)
{
   return !Copy_PtrQueue->Queue_Size;
}

u8  MIRTOS_u8IsQueueFull(Queue_t * Copy_PtrQueue)
{
   return 0;
}

u8  MIRTOS_u8QueueSize(Queue_t * Copy_PtrQueue)
{
   return Copy_PtrQueue->Queue_Size;
}


void MIRTOS_voidClearQueue(Queue_t * Copy_PtrQueue)
{
    while(Copy_PtrQueue->Queue_Front)
    {
      Copy_PtrQueue->Queue_Rear = Copy_PtrQueue->Queue_Front->QueueNode_Next;
      free(Copy_PtrQueue -> Queue_Front);
      Copy_PtrQueue->Queue_Front = Copy_PtrQueue->Queue_Rear;
    }
    Copy_PtrQueue->Queue_Size = 0;
}

void MIRTOS_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY Copy_QueueEntry))
{
    QueueNode_t *Local_PtrQueueNode;
    for(Local_PtrQueueNode = Copy_PtrQueue -> Queue_Front;Local_PtrQueueNode;Local_PtrQueueNode = Local_PtrQueueNode -> QueueNode_Next)
    {
      (*PF)(Local_PtrQueueNode -> QueueNode_Entry);
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/



void PendSV_Handler(void)
{  
   __asm(
	"#pargma IMPORT   Static_OSPtrToCurrentTask\n"         // External Variable 
   "#pargma IMPORT   Static_OSPtrToNextTask\n"            // External Variable 
   // __disable_irq();
   "CPSID    I\n"
   // if(THERE_ARE_TASKS_RUNNING) 
   // Saving The Context Of The Current 
   "LDR      r1,=Static_OSPtrToCurrentTask\n"
   "LDR      r1,[r1,#0x00]\n"
   "CBZ      r1,PendSV_restore\n"
   // PUSH RegistersR4:R11 Into New Stack
   "PUSH     {r4-r11}\n"   
   // Saving Stack Pointer In The Private Stack Pointer Member Of Static_OSPtrToCurrentTask
   "LDR      r1,=Static_OSPtrToCurrentTask\n"
   "LDR      r1,[r1,#0x00]\n"
   // Static_OSPtrToCurrentTask->Task_voidPtrStackPointer = Local_voidPtrSimulateStackPointer;
   "STR      sp,[r1,#0x00]\n"
   
"PendSV_restore:\n"
   // Restore The Context Of The Next Task To Run
   // Local_voidPtrSimulateStackPointer = Static_OSPtrToNextTask->Task_voidPtrStackPointer;
   "LDR      r1,=Static_OSPtrToNextTask\n"
   "LDR      r1,[r1,#0x00]\n"
   "LDR      sp,[r1,#0x00]\n"

   // Static_OSPtrToCurrentTask = Static_OSPtrToNextTask; 
   "LDR      r1,=Static_OSPtrToNextTask\n"
   "LDR      r1,[r1,#0x00]\n"
   "LDR      r2,=Static_OSPtrToCurrentTask\n"
   "STR      r1,[r2,#0x00]\n"
   
   // Pop RegistersR4:R11 From The Stack
   "POP      {r4-r11}\n"
   // __enable_irq(); 
   "CPSIE    I\n"
   // Returb To Next Thread
   "BX       lr"
	 ); 
}



/*************** END OF FUNCTIONS ***************************************************************************/
