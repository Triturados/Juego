@echo off

title Actualizacion de submodulo y compilacion de motor y juego - Crunch Through Hell
echo Comenzando...

rem Variables de batch
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