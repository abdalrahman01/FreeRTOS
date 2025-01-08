/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h" /* RTOS task related API prototypes. */
#include "queue.h" /* RTOS queue related API prototypes. */
#include "timers.h" /* Software timer related API prototypes. */
#include "semphr.h" /* Semaphore related API prototypes. */


/* Priorities at which the tasks are created. The event semaphore task is
   given the maximum priority of ( configMAX_PRIORITIES - 1 ) to ensure it runs as
   soon as the semaphore is given. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define mainEVENT_SEMAPHORE_TASK_PRIORITY ( configMAX_PRIORITIES - 1 )

/* The rate at which data is sent to the queue, specified in milliseconds, and
   converted to ticks using the pdMS_TO_TICKS() macro. */
#define mainQUEUE_SEND_PERIOD_MS pdMS_TO_TICKS( 200 )

/* The period of the example software timer, specified in milliseconds, and
   converted to ticks using the pdMS_TO_TICKS() macro. */
#define mainSOFTWARE_TIMER_PERIOD_MS pdMS_TO_TICKS( 1000 )

/* The number of items the queue can hold. This is 1 as the receive task
   has a higher priority than the send task, so will remove items as they are added,
   meaning the send task should always find the queue empty. */
#define mainQUEUE_LENGTH ( 1 )

/*-----------------------------------------------------------*/

/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware( void );


/*
 * The event semaphore task as described at the top of this file.
 */
static void prvEventSemaphoreTask( void *pvParameters );

/*-----------------------------------------------------------*/


/* The semaphore (in this case binary) that is used by the FreeRTOS tick hook
 * function and the event semaphore task.
 */
static SemaphoreHandle_t xEventSemaphore1 = NULL;
static SemaphoreHandle_t xEventSemaphore2 = NULL;


static int criticalResource = 0;
static int criticalResourceLow = 0;


static void TICK_task( void* pvParameters )
{

   for (int i = 0; i < 10 ; i++) {
         xSemaphoreTake( xEventSemaphore1, portMAX_DELAY );
         criticalResourceLow++;
         xSemaphoreGive( xEventSemaphore1 );
         vTaskDelay( pdMS_TO_TICKS( 1000 ) );

      
   }

    for( ;; )
    {
         xSemaphoreTake( xEventSemaphore1, portMAX_DELAY );
         vTaskDelay( pdMS_TO_TICKS( 1000 ) );
         xSemaphoreTake( xEventSemaphore2, portMAX_DELAY );
         criticalResource++;
         xSemaphoreGive( xEventSemaphore2 );
         xSemaphoreGive( xEventSemaphore1 );
    }
}
static void TOCK_task( void* pvParameters )
{

   
   for (int i = 0; i < 10 ; i++) {
         xSemaphoreTake( xEventSemaphore2, portMAX_DELAY );
         criticalResourceLow++;
         xSemaphoreGive( xEventSemaphore2 );
         vTaskDelay( pdMS_TO_TICKS( 1000 ) );

   }
    for( ;; )
    {
         xSemaphoreTake( xEventSemaphore2, portMAX_DELAY );
         vTaskDelay( pdMS_TO_TICKS( 1000 ) );
         xSemaphoreTake( xEventSemaphore1, portMAX_DELAY );
         criticalResource++;
         xSemaphoreGive( xEventSemaphore1 );
         xSemaphoreGive( xEventSemaphore2 );
    }
}

/*-----------------------------------------------------------*/

int app_main_deadlock(void)
{
TimerHandle_t xExampleSoftwareTimer = NULL;

    /* Configure the system ready to run the demo. The clock configuration
       can be done here if it was not done before main() was called. */
    prvSetupHardware();

    /*
      Mutex: is used to demonstrate the deadlock scenario.
    */
    xEventSemaphore1 = xSemaphoreCreateMutex();
    xEventSemaphore2 = xSemaphoreCreateMutex();

   
  
    xTaskCreate( TICK_task,
                 "TICK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 1,
                 NULL );
    xTaskCreate( TOCK_task,
                 "TOCK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 1,
                 NULL );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
       will never be reached. If the following line does execute, then there was
       insufficient FreeRTOS heap memory available for the idle and/or timer tasks
       to be created. See the memory management section on the FreeRTOS web site
       for more details. */
    for( ;; );
}

static void prvSetupHardware( void )
{
 /* Ensure all priority bits are assigned as preemption priority bits
    if using a ARM Cortex-M microcontroller. */
 NVIC_SetPriorityGrouping( 0 );

 /* TODO: Setup the clocks, etc. here, if they were not configured before
    main() was called. */
}