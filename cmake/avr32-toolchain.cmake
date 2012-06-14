SET(ASF_PATH /home/kim/src/asf-3.2.0/)
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_C_COMPILER avr32-elf-gcc)
SET(CMAKE_CXX_COMPILER avr32-elf-g++)
SET(OBJCOPY avr32-elf-objcopy)
SET(SIZE avr32-elf-size)
SET(DFUPROGRAM dfu-programmer)
SET(DFUPART at32uc3b0256)
SET(AVR32_LINKER_SCRIPT "${ASF_PATH}/avr32/utils/linker_scripts/at32uc3b/0256/gcc/link_uc3b0256.lds")

# For other boards, create a new directory under hardware/ and create a user_board.h, init.h and init.c there.
SET(AVR32_USER_BOARD chiplab7)
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(AVR32_USER_BOARD_DIR "${SELF_DIR}/../hardware/${AVR32_USER_BOARD}" ABSOLUTE)


SET(CSTANDARD "-std=gnu99")
SET(CXXSTANDARD "-std=c++0x")
#~ SET(CDEBUG "-gstabs")
SET(CXXWARN "-Wall -Wextra -pedantic")
SET(CWARN "-Wall -Wextra -Wstrict-prototypes -pedantic")
#~ SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET(CTUNING "-ffunction-sections -fdata-sections")
SET(COPT "-O1")
#~ SET(COPT "-O1 -falign-functions -falign-jumps -falign-labels -fcaller-saves -fcrossjumping -fcse-follow-jumps -fdelete-null-pointer-checks -fexpensive-optimizations -fforward-propagate -fgcse -finline-functions -finline-small-functions -fipa-cp -foptimize-register-move -foptimize-sibling-calls -fpeephole2 -fregmove -freorder-blocks -freorder-functions -frerun-cse-after-loop -fschedule-insns -fschedule-insns2 -fstrict-aliasing -fthread-jumps -ftree-builtin-call-dce -ftree-pre -ftree-vrp")
SET(CMPART "-mpart=uc3b0256")
SET(CDEFS "-DBOARD=USER_BOARD")
#~ SET(CDEFS "-DF_CPU=16000000")


SET(CFLAGS "${CMPART} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING} ${CWARN} ${CSTANDARD} ${CEXTRA}")
SET(CXXFLAGS "${CMPART} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING} ${CXXWARN} ${CXXSTANDARD} ${CXXEXTRA}")

SET(CMAKE_C_FLAGS ${CFLAGS})
SET(CMAKE_CXX_FLAGS ${CXXFLAGS})
SET(CMAKE_ASM_FLAGS ${CFLAGS})
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-e,_trampoline -Wl,--gc-sections -Wl,-T,${AVR32_LINKER_SCRIPT}")

