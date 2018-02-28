@echo off

@echo Rebuild KornetOSC

c:\Keil_v5\UV4\UV4 -c sources\Panel\PanelOSC.uvprojx -j0
c:\Keil_v5\UV4\UV4 -c sources\Device\DeviceOSC.uvprojx -j0

call buildKornetOSC.bat
