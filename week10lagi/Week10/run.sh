#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp GameManager.cpp HandGenerator.cpp HandPlayer.cpp ChosenHand.cpp HandChecker.cpp HandScoreTable.cpp ScoringRule.cpp HandResolver.cpp JokerSystem.cpp -o Task1
exec ./Task1
