project(lib_FREERTOS)

SET (FREERTOS_DIR FreeRTOS)

######################################################################################
# Selector to choose architecture to build lib_trace_CORTEXM
######################################################################################
# Global Registration of the available list lock practices 
FUNCTION(lib_freertos_add_board)
	FOREACH(ARG ${ARGV})
  		set_property(GLOBAL APPEND PROPERTY LIB_FREERTOS_BOARDS ${ARG})
	ENDFOREACH(ARG)
ENDFUNCTION(lib_freertos_add_board)

lib_freertos_add_board("CORTEX_STM32F103_GCC_EMBTOM")
lib_freertos_add_board("CORTEX_STM32F401_GCC_EMBTOM")

set(LIB_FREERTOS_BOARD ${LIB_FREERTOS_BOARD} CACHE STRING "Freertos board type")
get_property(boards GLOBAL PROPERTY LIB_FREERTOS_BOARDS)
list(SORT boards)
set_property(CACHE LIB_FREERTOS_BOARD PROPERTY STRINGS None ${boards})

#######################################################################################
# Evaluate selection
#######################################################################################

SET(LIB_FREERTOS_SOURCE_C   	${FREERTOS_DIR}/Source/croutine.c 
                                ${FREERTOS_DIR}/Source/event_groups.c
                                ${FREERTOS_DIR}/Source/list.c
                                ${FREERTOS_DIR}/Source/queue.c
                                ${FREERTOS_DIR}/Source/stream_buffer.c
                                ${FREERTOS_DIR}/Source/tasks.c
                                ${FREERTOS_DIR}/Source/timers.c)

SET(LIB_FREERTOS_INTERFACE_HEADER  ${FREERTOS_DIR}/Source/include)


if("${LIB_FREERTOS_BOARD}" STREQUAL "CORTEX_STM32F103_GCC_EMBTOM")
    SET(LIB_FREERTOS_SOURCE_C ${LIB_FREERTOS_SOURCE_C}  Board/CORTEX_STM32F103_GCC_EMBTOM/hooks.c 
                                                        ${FREERTOS_DIR}/Source/portable/MemMang/heap_4.c
                                                        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM3/port.c)
    SET(LIB_FREERTOS_INTERFACE_HEADER   ${LIB_FREERTOS_INTERFACE_HEADER} 
                                        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM3/
                                        Board/CORTEX_STM32F103_GCC_EMBTOM)

elseif("${LIB_FREERTOS_BOARD}" STREQUAL "CORTEX_STM32F401_GCC_EMBTOM")
    SET(LIB_FREERTOS_SOURCE_C ${LIB_FREERTOS_SOURCE_C}  Board/CORTEX_STM32F401_GCC_EMBTOM/hooks.c 
                                                        ${FREERTOS_DIR}/Source/portable/MemMang/heap_4.c
                                                        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM4F/port.c)
    SET(LIB_FREERTOS_INTERFACE_HEADER   ${LIB_FREERTOS_INTERFACE_HEADER} 
                                        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM4F/
                                        Board/CORTEX_STM32F401_GCC_EMBTOM)
    
elseif("${LIB_TRACE_ARCHITECTURE}" STREQUAL "None")
	message(FATAL_ERROR "No valid build architecture chosen! Please check lib_FREERTOS.")
else()
    message(FATAL_ERROR "No valid build architecture chosen! Please check lib_FREERTOS.")
endif()

#######################################################################################
#Build target settingsLIB_FREERTOS_INTERNAL_HEADER
#######################################################################################
add_library(${PROJECT_NAME} STATIC ${LIB_FREERTOS_SOURCE_C})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_FREERTOS_INTERFACE_HEADER})
target_compile_options(${PROJECT_NAME} PRIVATE -O2) # only internal

