/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */

static void prvSetupHardware(void);

static SemaphoreHandle_t xEventSemaphore = NULL;

static void vTask_H(void *pvParameters) {
  for (;;) {
    vTaskDelay(1);

    xSemaphoreTake(xEventSemaphore, portMAX_DELAY);

    for (int i = 0; i < 100; i++) {
      int *p = (int *)pvPortMalloc(100 * sizeof(int));
      vPortFree(p);
    }

    xSemaphoreGive(xEventSemaphore);
  }
}
static void vTask_M(void *pvParameters) {
  for (;;) {

    int *p = (int *)pvPortMalloc(100 * sizeof(int));
    vTaskDelay(1000);
    vPortFree(p);
  }
}
static void vTask_L(void *pvParameters) {
  for (;;) {
    xSemaphoreTake(xEventSemaphore, portMAX_DELAY);

    for (int i = 0; i < 100; i++) {
      int *p = (int *)pvPortMalloc(100 * sizeof(int));
      vPortFree(p);
    }

    xSemaphoreGive(xEventSemaphore);
  }
}

/*-----------------------------------------------------------*/

int app_main_priorityIversion(void) {

  prvSetupHardware();

  /* Create the semaphore used by the FreeRTOS tick hook function and the
     event semaphore task. **NOTE:** A semaphore is used for example purposes,
     using a direct to task notification will be faster! */
  xEventSemaphore = xSemaphoreCreateMutex();

  /* Create the queue receive task as described in the comments at the top
     of this file. */
  xTaskCreate(/* The function that implements the task. */
              vTask_L,
              /* Text name for the task, just to help debugging. */
              "Task LOW",
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
              NULL);
  xTaskCreate(/* The function that implements the task. */
              vTask_M,
              /* Text name for the task, just to help debugging. */
              "Task Medium",
              /* The size (in words) of the stack that should be created
                 for the task. */
              configMINIMAL_STACK_SIZE,
              /* A parameter that can be passed into the task. Not used
                 in this simple demo. */
              NULL,
              /* The priority to assign to the task. tskIDLE_PRIORITY
                 (which is 0) is the lowest priority. configMAX_PRIORITIES - 1
                 is the highest priority. */
              2,
              /* Used to obtain a handle to the created task. Not used in
                 this simple demo, so set to NULL. */
              NULL);
  xTaskCreate(/* The function that implements the task. */
              vTask_H,
              /* Text name for the task, just to help debugging. */
              "Task HIGH",
              /* The size (in words) of the stack that should be created
                 for the task. */
              configMINIMAL_STACK_SIZE,
              /* A parameter that can be passed into the task. Not used
                 in this simple demo. */
              NULL,
              /* The priority to assign to the task. tskIDLE_PRIORITY
                 (which is 0) is the lowest priority. configMAX_PRIORITIES - 1
                 is the highest priority. */
              3,
              /* Used to obtain a handle to the created task. Not used in
                 this simple demo, so set to NULL. */
              NULL);

  /* Start the tasks and timer running. */
  vTaskStartScheduler();

  /* If all is well, the scheduler will now be running, and the following line
     will never be reached. If the following line does execute, then there was
     insufficient FreeRTOS heap memory available for the idle and/or timer tasks
     to be created. See the memory management section on the FreeRTOS web site
     for more details. */
  for (;;)
    ;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware(void) {
  /* Ensure all priority bits are assigned as preemption priority bits
     if using a ARM Cortex-M microcontroller. */
  NVIC_SetPriorityGrouping(0);

  /* TODO: Setup the clocks, etc. here, if they were not configured before
     main() was called. */
}