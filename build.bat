@echo off

title Realizando la build - Crunch Through Hell
echo Comenzando con la magia!

rem Variables de batch
set WORKING_DIR=%cd%
set ENGINE_DIR=.\CrunchThroughHell\Engine\
set CRUNCH_THROUGH_HELL_SOL=.\CrunchThroughHell\CrunchThroughHell.sln

rem Inicializamos el submódulo
git submodule update --remote

cd %ENGINE_DIR%

call automate_reset.bat

call automate.bat

cd %WORKING_DIR%

rem Compilacion de la solucion del juego
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Debug /p:Platform=x64
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Release /p:Platform=x64

echo Magia hecha, a jugar!

pause
exit