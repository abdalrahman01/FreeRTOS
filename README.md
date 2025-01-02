# FreeRTOS on STM32F4 with STM32CubeMX, Keil uVision 5 and Tracealyzer from Percepio

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
  


## Notes from the USER MANUAL
övergripande koll på rtos 
kolla på timing 
memroy heap allocation (free malloc): make a malloc and do not free that you see the graph go up and never go down.


overiew of use: 
. For RTOS-based systems, Tracealyzer shows task scheduling and timing, calls to RTOS services (including blocking and timeouts) and internal RTOS events such as task activations and OS ticks. Tracealyzer can also show interrupt handlers as well as User Events logged from your application code.


requires no extra hardware. 


genarate the trace output:
- Thirdparty solutions provided by rtos vendor
- tracelayzer has libraries that can be integrated with rtos 


TRACE_RACORDER 
 - FreeRTOS
 - SafeRtos
 - AzureRTOS
 - THREADx
 - Zepher
 - baremetal (without RTOS)
 - OTHER RTOS


How tracealyzer reads the trace: the trace recorder library uses trace hooks, i.e., the library is hooked with the RTOS



live visualization vs Unlimited trace:
1. live visualiztion uses ram, thus you can't save a lot
2. unlimted, the trace will be recorded in Disk



**Note** that each traced event typically adds a few microseconds to the execution time, so the execution times will be somewhat higher than without tracing enabled. While this is usually a minor effect, adding trace calls to highly time-critical or very frequent ISRs can be problematic. The ISR tracing support is mainly intended for debugging purposes, not for accurate profiling of ISR execution times in the microsecond range.

### Streaming Trace Data
- ARM ITM
- SEGGER J-Link
- USB CDC
- TCP/IP
- UDP
- UART 
- (Make your own Stream Port)

Tracealyzer can receive the data in five ways, using a TCP socket, a UDP socket, a COM port, by opening a file, or via a Named Pipe. The latter is for Windows only.


timing properties of each actor instance, like execution time, response time, response interference and fragmentation. This allows for viewing the distribution and how the properties vary over time, for example if some tasks have occational anomalies in the response time. 

