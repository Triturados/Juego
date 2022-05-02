@echo off

title Actualizacion de submodulo y compilacion de motor y juego - Crunch Through Hell
echo Comenzando...

rem Variables de batch
set GAME_ROOT_DIR=%cd%
set SKELETON_SOL=.\CrunchThroughHell\Engine\Skeleton\Skeleton.sln
set CRUNCH_THROUGH_HELL_SOL=.\CrunchThroughHell\CrunchThroughHell.sln
set ENGINE_DIR=.\CrunchThroughHell\Engine\

rem Actualizamos el submodulo
git submodule update --remote --merge

cd %ENGINE_DIR%

git checkout Functional
git pull

cd %GAME_ROOT_DIR%

rem Compilacion de la solucion del motor
msbuild %SKELETON_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142
msbuild %SKELETON_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v142

rem Compilacion de la solucion del juego
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Debug /p:Platform=x64 /p:PlatformToolset=v142
msbuild %CRUNCH_THROUGH_HELL_SOL% /p:configuration=Release /p:Platform=x64 /p:PlatformToolset=v142

echo Magia hecha, a jugar!

pause
exit