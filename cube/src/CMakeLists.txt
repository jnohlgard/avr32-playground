include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/config)
include_directories(${ASF_PATH}/avr32)
include_directories(${ASF_PATH}/common)
include_directories(${ASF_PATH}/avr32/boards)
include_directories(${ASF_PATH}/common/boards)
include_directories(${ASF_PATH}/avr32/utils)
include_directories(${ASF_PATH}/common/utils)
include_directories(${ASF_PATH}/common/services/clock)
include_directories(${ASF_PATH}/avr32/utils/preprocessor)
include_directories(${ASF_PATH}/avr32/drivers/gpio)
include_directories(${ASF_PATH}/avr32/drivers/intc)
include_directories(${ASF_PATH}/avr32/drivers/spi)
include_directories(${ASF_PATH}/avr32/drivers/flashc)
include_directories(${ASF_PATH}/avr32/drivers/cpu/cycle_counter)
#~ include_directories(${ASF_PATH}/boards)
#~ include_directories(${ASF_PATH}/utils)
#~ include_directories(${ASF_PATH}/utils/preprocessor)
#~ include_directories(${ASF_PATH}/drivers/gpio)
#~ include_directories(${ASF_PATH}/drivers/intc)

add_executable(cube.elf
    ../../Framebuffer/Framebuffer.cpp
    ../../Framebuffer/SSD1306.cpp
    Render.cpp
    utility3d.cpp
    cube.cpp
    ${AVR32_USER_BOARD_DIR}/init.c
    millis.c
    ${ASF_PATH}/common/services/clock/uc3b0_b1/sysclk.c
    ${ASF_PATH}/avr32/drivers/gpio/gpio.c
    ${ASF_PATH}/avr32/drivers/intc/intc.c
    ${ASF_PATH}/avr32/drivers/spi/spi.c
    ${ASF_PATH}/avr32/drivers/pm/pm.c
    ${ASF_PATH}/avr32/drivers/flashc/flashc.c
    #~ software_framework/boards/EVK1101/led.c
    ${ASF_PATH}/avr32/utils/startup/trampoline_uc3.S
)

set(DFUHEXFILE cube.hex)

add_custom_command(OUTPUT cube.hex
    COMMAND ${SIZE} cube.elf
    COMMAND ${OBJCOPY} -O ihex cube.elf cube.hex
    DEPENDS cube.elf
    COMMENT "Creating .hex file")
add_custom_target(hex ALL DEPENDS cube.hex)

add_custom_target(flash DEPENDS ${DFUHEXFILE} erase)
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
    COMMAND ${DFUPROGRAM} ${DFUPART} flash --suppress-bootloader-mem ${DFUHEXFILE}
    )
