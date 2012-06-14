
IF(NOT DEFINED ASF_PLATFORM OR NOT DEFINED ASF_PATH)
    message( FATAL_ERROR "ASF_PLATFORM and ASF_PATH need to be defined to use Atmel Software Framework.")
ENDIF(NOT DEFINED ASF_PLATFORM OR NOT DEFINED ASF_PATH)
IF(NOT DEFINED ASF_CPU AND ASF_SERVICES MATCHES ".*sysclk.*")
    message( FATAL_ERROR "You should define your ASF_CPU for sysclk support such as uc3b0_b1 or sam4s")
ENDIF(NOT DEFINED ASF_CPU AND ASF_SERVICES MATCHES ".*sysclk.*")


SET(ASF_COMMON_INCLUDES
    "${ASF_PATH}/common"
    "${ASF_PATH}/common/boards"
    "${ASF_PATH}/common/utils"
    )
SET(ASF_PLATFORM_INCLUDES
    "${ASF_PATH}/${ASF_PLATFORM}"
    "${ASF_PATH}/${ASF_PLATFORM}/boards"
    "${ASF_PATH}/${ASF_PLATFORM}/utils"
    "${ASF_PATH}/${ASF_PLATFORM}/utils/preprocessor"
)

# Special cases which don't follow the usual platform/category/module/module.c pattern are listed below
#~ SET(ASF_

#~ include_directories(${ASF_PATH}/avr32)
#~ include_directories(${ASF_PATH}/common)
#~ include_directories(${ASF_PATH}/avr32/boards)
#~ include_directories(${ASF_PATH}/common/boards)
#~ include_directories(${ASF_PATH}/avr32/utils)
#~ include_directories(${ASF_PATH}/common/utils)
#~ include_directories(${ASF_PATH}/avr32/utils/preprocessor)

set(ASF_DRIVER_cycle_counter_EXTRA_SEARCHPATH "${ASF_PATH}/${ASF_PLATFORM}/drivers/cpu/cycle_counter")
set(ASF_SERVICE_sysclk_EXTRA_SEARCHPATH
    "${ASF_PATH}/common/services/clock"
    "${ASF_PATH}/common/services/clock/${ASF_CPU}")

set(ASF_SOURCE_FILES)
set(ASF_INCLUDE_DIRS)

foreach(DRIVER ${ASF_DRIVERS})
    #~ set(ASF_DRIVER_${DRIVER}_SOURCE_FILE)
    #~ set(ASF_DRIVER_${DRIVER}_HEADER_FILE)

    #~ message(STATUS "Looking for ${DRIVER}.c")
    foreach(ASF_PATHTMP ${ASF_DRIVER_${DRIVER}_EXTRA_SEARCHPATH} "${ASF_PATH}/${ASF_PLATFORM}/drivers/${DRIVER}" )
        #~ message(STATUS "in: ${ASF_PATHTMP}")
        SET(ASF_FILETMP "${ASF_PATHTMP}/${DRIVER}.c")
        if(EXISTS "${ASF_FILETMP}")
            set(ASF_DRIVER_${DRIVER}_SOURCE_FILE "${ASF_FILETMP}")
            message(STATUS "Found ${ASF_DRIVER_${DRIVER}_SOURCE_FILE}")
            list(APPEND ASF_SOURCE_FILES "${ASF_DRIVER_${DRIVER}_SOURCE_FILE}")
            break()
        endif(EXISTS "${ASF_FILETMP}")
    endforeach(ASF_PATHTMP)

    #~ message(STATUS "Looking for ${DRIVER}.h")
    foreach(ASF_PATHTMP ${ASF_DRIVER_${DRIVER}_EXTRA_SEARCHPATH} "${ASF_PATH}/${ASF_PLATFORM}/drivers/${DRIVER}" )
        #~ message(STATUS "in: ${ASF_PATHTMP}")
        SET(ASF_FILETMP "${ASF_PATHTMP}/${DRIVER}.h")
        if(EXISTS "${ASF_FILETMP}")
            set(ASF_DRIVER_${DRIVER}_HEADER_FILE "${ASF_FILETMP}")
            message(STATUS "Found ${ASF_DRIVER_${DRIVER}_HEADER_FILE}")
            get_filename_component(ASF_DRIVER_${DRIVER}_RELPATH "${ASF_DRIVER_${DRIVER}_HEADER_FILE}" PATH)
            get_filename_component(ASF_DRIVER_${DRIVER}_PATH "${ASF_DRIVER_${DRIVER}_RELPATH}" ABSOLUTE)
            list(APPEND ASF_INCLUDE_DIRS "${ASF_DRIVER_${DRIVER}_PATH}")
            list(APPEND ASF_HEADER_FILES "${ASF_DRIVER_${DRIVER}_HEADER_FILE}")
            break()
        endif(EXISTS "${ASF_FILETMP}")
    endforeach(ASF_PATHTMP)
endforeach(DRIVER)

foreach(SERVICE ${ASF_SERVICES})
    #~ message(STATUS "Looking for ${SERVICE}.c")
    foreach(ASF_PATHTMP ${ASF_SERVICE_${SERVICE}_EXTRA_SEARCHPATH} "${ASF_PATH}/${ASF_PLATFORM}/services/${SERVICE}" "${ASF_PATH}/common/services/${SERVICE}")
        #~ message(STATUS "in: ${ASF_PATHTMP}")
        SET(ASF_FILETMP "${ASF_PATHTMP}/${SERVICE}.c")
        if(EXISTS "${ASF_FILETMP}")
            set(ASF_SERVICE_${SERVICE}_SOURCE_FILE "${ASF_FILETMP}")
            message(STATUS "Found ${ASF_SERVICE_${SERVICE}_SOURCE_FILE}")
            list(APPEND ASF_SOURCE_FILES "${ASF_SERVICE_${SERVICE}_SOURCE_FILE}")
            break()
        endif(EXISTS "${ASF_FILETMP}")
    endforeach(ASF_PATHTMP)

    #~ message(STATUS "Looking for ${SERVICE}.h")
    foreach(ASF_PATHTMP ${ASF_SERVICE_${SERVICE}_EXTRA_SEARCHPATH} "${ASF_PATH}/${ASF_PLATFORM}/services/${SERVICE}" "${ASF_PATH}/common/services/${SERVICE}")
        #~ message(STATUS "in: ${ASF_PATHTMP}")
        SET(ASF_FILETMP "${ASF_PATHTMP}/${SERVICE}.h")
        if(EXISTS "${ASF_FILETMP}")
            set(ASF_SERVICE_${SERVICE}_HEADER_FILE "${ASF_FILETMP}")
            message(STATUS "Found ${ASF_SERVICE_${SERVICE}_HEADER_FILE}")
            get_filename_component(ASF_SERVICE_${SERVICE}_RELPATH "${ASF_SERVICE_${SERVICE}_HEADER_FILE}" PATH)
            get_filename_component(ASF_SERVICE_${SERVICE}_PATH "${ASF_SERVICE_${SERVICE}_RELPATH}" ABSOLUTE)
            list(APPEND ASF_INCLUDE_DIRS "${ASF_SERVICE_${SERVICE}_PATH}")
            list(APPEND ASF_HEADER_FILES "${ASF_SERVICE_${SERVICE}_HEADER_FILE}")
            break()
        endif(EXISTS "${ASF_FILETMP}")
    endforeach(ASF_PATHTMP)
endforeach(SERVICE)

LIST(APPEND ASF_INCLUDE_DIRS ${ASF_COMMON_INCLUDES} ${ASF_PLATFORM_INCLUDES})
#~ message(STATUS "Sources: ${ASF_SOURCE_FILES}")
#~ message(STATUS "Dirs: ${ASF_INCLUDE_DIRS}")
