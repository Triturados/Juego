echo off

title Realizando la build - Crunch Through Hell
echo Comenzando con la magia!

rem Variables de batch
set WORKING_DIR=%cd%
set ENGINE_DIR=.\CrunchThroughHell\Engine\

git submodule update --remote

cd %ENGINE_DIR%

call automate_reset.bat

call automate.bat

cd %WORKING_DIR%    

pause
exit