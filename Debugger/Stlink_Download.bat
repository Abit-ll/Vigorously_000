@echo off

set dir_path=F:\\Free\\Vigorously_001\\Src\\Debugger
set image=F:\\Free\\Vigorously_001\\Src\\Obj\\Vigorously_001.bin
set stlink_cfg=F:\\Free\\Vigorously_001\\Src\\Debugger\\stlink.cfg
set stm32_cfg=F:\\Free\\Vigorously_001\\Src\\Debugger\\stm32f4x.cfg

openocd -s %dir_path% -f %stlink_cfg% -f %stm32_cfg% -c ^
"init;halt;reset halt;flash write_image erase %image% 0x08000000;shutdown;"

@echo on