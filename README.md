# FreeRTOS on STM32F4 with STM32CubeMX, Keil uVision 5 and Tracealyzer frin Percepio

The example project is a simple FreeRTOS project with multiple tasks, queues, and semaphores. 

How I created the project: 
 - start MDK uVision 5 and create a new project
 - add Device::CubeMX and FreeRTOS
 - export the project to csolution format.
 - open project on vscode 
 - click on generete code "CubeMx" and follow these steps in this [link](https://www.keil.com/pack/doc/stm32cube/html/cubemx_using.html#cubemx_proj_rtx5), **Note**: DO NOT add the inclide files for cmsis_os2.h 
 -  copy the main function from this [link](https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Device-independent-demo/Hardware-independent-RTOS-example) and paste in the app_main.c, **Note**: RENAME THE main() in app_main.c to app_main()
 -  call the app_main() in the main() function in the main.c
 -  to use snapshot mode: [link](https://percepio.com/tracealyzer/gettingstarted/keil-uvision/)