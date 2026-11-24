@echo off
cd /d "%~dp0"
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp GameManager.cpp HandGenerator.cpp HandPlayer.cpp ChosenHand.cpp HandChecker.cpp HandScoreTable.cpp ScoringRule.cpp HandResolver.cpp JokerSystem.cpp -o Task1.exe
if errorlevel 1 exit /b %errorlevel%
Task1.exe
