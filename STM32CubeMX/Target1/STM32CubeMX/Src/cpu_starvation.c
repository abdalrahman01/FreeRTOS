/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */

/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware(void);

static int x = 0;
static int y1 = 0;
static int y2 = 0;

int calculation() {
  for (int i = 0; i < 1000000; i++) {
    x++;
  }

  for (int i = 0; i < 999997; i++) {
    x--;
  }
  int *p = (int *)pvPortMalloc(x * sizeof(int));

  if (p == NULL) {
    return 0;
  }
  vPortFree(p);

  return x;
}

static void vTask1(void *pvParameters) {

  for (;;) {
    for (int i = 0; i < 100; i++) {

      calculation();
    }

    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}



static void vTask4(void *pvParameters) {

  for (;;) {
    /* Print out the name of this task. */
    for (int i = 0; i < 1; i++) {

      calculation();
    }

    vTaskDelay(1 / portTICK_PERIOD_MS);
    /* Delay for a period. */
  }
}

/*-----------------------------------------------------------*/

int app_main_cpuStarvation(void) {

  xTaskCreate(vTask1, "Task High 1", configMINIMAL_STACK_SIZE, NULL, 6, NULL);
  xTaskCreate(vTask4, "Task Low 4", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  vTaskStartScheduler();

  /* If all is well, the scheduler will now be running, and the following line
     will never be reached. If the following line does execute, then there was
     insufficient FreeRTOS heap memory available for the idle and/or timer tasks
     to be created. See the memory management section on the FreeRTOS web site
     for more details. */
  for (;;)
    ;
}

static void prvSetupHardware(void) {
  /* Ensure all priority bits are assigned as preemption priority bits
     if using a ARM Cortex-M microcontroller. */
  NVIC_SetPriorityGrouping(0);

  /* TODO: Setup the clocks, etc. here, if they were not configured before
     main() was called. */
}