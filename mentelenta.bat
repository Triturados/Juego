@echo off

title Te faltan dos veranos - Crunch Through Hell
echo Comenzando con lo que cualquiera haría pero a ti te lo tiene que hacer un ejecutable de windows!

rem Variables de batch
set WORKING_DIR=%cd%
set ENGINE_DIR=.\CrunchThroughHell\Engine\
set SKELETON_SOL=.\CrunchThroughHell\Engine\Skeleton\Skeleton.sln
set CRUNCH_THROUGH_HELL_SOL=.\CrunchThroughHell\CrunchThroughHell.sln

rem Inicializamos el submódulo
git submodule update --remote

rem Compilacion de la solucion del motor
msbuild %SKELETON_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142
msbuild %SKELETON_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v142

rem Compilacion de la solucion del juego
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v142

echo Magia hecha, a jugar!

pause
exit