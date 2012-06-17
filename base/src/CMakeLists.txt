include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/config)

set(ELFFILE myproject.elf)
set(HEXFILE myproject.hex)

add_executable(${ELFFILE}
    main.cpp
    ${AVR32_USER_BOARD_DIR}/init.c
    ${ASF_SOURCE_FILES}
    ${AVR32_TRAMPOLINE}
    ${ASF_PATH}/avr32/drivers/intc/exception.S
)


add_custom_command(OUTPUT ${HEXFILE}
    COMMAND ${SIZE} ${ELFFILE}
    COMMAND ${OBJCOPY} -O ihex ${ELFFILE} ${HEXFILE}
    DEPENDS ${ELFFILE}
    COMMENT "Creating .hex file")
add_custom_target(hex ALL DEPENDS ${HEXFILE})

add_custom_target(flash DEPENDS ${HEXFILE} erase)
add_custom_target(erase)
add_custom_target(start)
add_custom_command(TARGET erase POST_BUILD
    COMMAND ${DFUPROGRAM} ${DFUPART} erase
    )

add_custom_command(TARGET start POST_BUILD
    COMMAND ${DFUPROGRAM} ${DFUPART} start
    )

add_custom_command(TARGET flash
    POST_BUILD
    COMMAND ${DFUPROGRAM} ${DFUPART} flash --suppress-bootloader-mem ${HEXFILE}
    )
