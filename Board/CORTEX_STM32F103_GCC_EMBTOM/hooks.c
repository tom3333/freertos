
// ////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////
#include <FreeRTOS.h>
#include <task.h>


void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

void vApplicationTickHook( void )
{
	#if ( mainCREATE_SIMPLE_LED_FLASHER_DEMO_ONLY == 0 )
	{
//		/* Just to verify that the interrupt nesting behaves as expected,
//		increment ulFPUInterruptNesting on entry, and decrement it on exit. */
//		ulFPUInterruptNesting++;
//
//		/* Fill the FPU registers with 0. */
//		vRegTestClearFlopRegistersToParameterValue( 0UL );
//
//		/* Trigger a timer 2 interrupt, which will fill the registers with a
//		different value and itself trigger a timer 3 interrupt.  Note that the
//		timers are not actually used.  The timer 2 and 3 interrupt vectors are
//		just used for convenience. */
//		NVIC_SetPendingIRQ( TIM2_IRQn );
//
//		/* Ensure that, after returning from the nested interrupts, all the FPU
//		registers contain the value to which they were set by the tick hook
//		function. */
//		configASSERT( ulRegTestCheckFlopRegistersContainParameterValue( 0UL ) );
//
//		ulFPUInterruptNesting--;
	}
	#endif
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
