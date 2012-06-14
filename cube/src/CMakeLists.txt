include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/config)

add_executable(cube.elf
    ../../Framebuffer/Framebuffer.cpp
    ../../Framebuffer/SSD1306.cpp
    Render.cpp
    utility3d.cpp
    cube.cpp
    ${AVR32_USER_BOARD_DIR}/init.c
    millis.c
    ${ASF_SOURCE_FILES}
    ${AVR32_TRAMPOLINE}
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
