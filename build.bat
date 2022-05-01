@echo off

title Realizando la build - Crunch Through Hell
echo Comenzando con la magia!

rem Variables de batch
set GAME_ROOT_DIR=%cd%
set ENGINE_DIR=.\CrunchThroughHell\Engine\
set CRUNCH_THROUGH_HELL_SOL=.\CrunchThroughHell\CrunchThroughHell.sln

rem Inicializamos el submódulo
git submodule init
git submodule update

rem Se aniade el Ogre.log que se ignora
type nul > .\CrunchThroughHell\config\ogre.log

cd %ENGINE_DIR%

call automate_reset.bat

call automate.bat

cd %GAME_ROOT_DIR%

rem Compilacion de la solucion del juego
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v142

echo Magia hecha, a jugar!

pause
exit