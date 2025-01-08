/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h" /* RTOS task related API prototypes. */
#include "queue.h" /* RTOS queue related API prototypes. */
#include "timers.h" /* Software timer related API prototypes. */
#include "semphr.h" /* Semaphore related API prototypes. */


/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware( void );


/* The handle of the task that is going to leak memory */
static TaskHandle_t memory_leak_handle1;
static TaskHandle_t memory_leak_handle2;

void memoryLeakTask1(void *pvParameters)
{

   // allocate memory 5 times (random size 1-4), wait between each allocation a random 1000 - 3000 ms, then free random times (1-5) the allocated memory
      while (1) {

         char *p[5];
         for (int i = 0; i < 5; i++)
         {
            p[i] = pvPortMalloc((rand() % 2 + 3) * sizeof(char));
            vTaskDelay((rand() % 200 + 500) / portTICK_PERIOD_MS);

         }

         for (int i = 0; i < 3; i++)
         {
            vPortFree(p[i]);
            vTaskDelay((rand() % 200 + 500) / portTICK_PERIOD_MS);
         } 
      }

}
static int memoryUsedByTask; 



/*-----------------------------------------------------------*/

int app_main_memoryLeak(void)
{
    prvSetupHardware();

    xTaskCreate( /* The function that implements the task. */
                 memoryLeakTask1,
                 /* Text name for the task, just to help debugging. */
                 "memoryLeakTask1",
                 /* The size (in words) of the stack that should be created
                    for the task. */
                 configMINIMAL_STACK_SIZE,
                 /* A parameter that can be passed into the task. Not used
                    in this simple demo. */
                 NULL,
                 /* The priority to assign to the task. tskIDLE_PRIORITY
                    (which is 0) is the lowest priority. configMAX_PRIORITIES - 1
                    is the highest priority. */
                 1,
                 /* Used to obtain a handle to the created task. Not used in
                    this simple demo, so set to NULL. */
                 &memory_leak_handle1 );
    

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
       will never be reached. If the following line does execute, then there was
       insufficient FreeRTOS heap memory available for the idle and/or timer tasks
       to be created. See the memory management section on the FreeRTOS web site
       for more details. */
    for( ;; ) {
   }
}
/*-----------------------------------------------------------*/


static void prvSetupHardware( void )
{
 /* Ensure all priority bits are assigned as preemption priority bits
    if using a ARM Cortex-M microcontroller. */
 NVIC_SetPriorityGrouping( 0 );

 /* TODO: Setup the clocks, etc. here, if they were not configured before
    main() was called. */
}