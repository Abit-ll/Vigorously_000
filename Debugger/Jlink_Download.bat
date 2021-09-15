@echo off
set dir_path=F:\\Free\\Smart_Car\\
set jink_cfg=F:\\Free\\Smart_Car\\Code\\Debugger\\jlink_swd.cfg
set image=F:\\Free\\Smart_Car\\Code\\Obj\\Smart_Car.hex
set stm32_cfg=F:\\Free\\Smart_Car\\Code\\Debugger\\stm32f4x.cfg

openocd -s %dir_path% -f %jink_cfg% -f %stm32_cfg% -c ^
"init;halt;reset halt;flash write_image erase %image%;reset;shutdown;"
@echo on