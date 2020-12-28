@echo off
g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp
set /a red=0
set /a blue=0
@REM set /a numofgame=%1
@REM for /L %%n in (1 1 %numofgame%) do (
for /L %%n in (1 1 100) do (
a.exe > output
find "Red Player won the game" .\output>nul && set /a red+=1
find "Blue Player won the game" .\output>nul && set /a blue+=1
)
@REM echo  %numofgame% games
echo red wins %red%
echo blue wins %blue%
@REM pause