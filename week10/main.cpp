// Unity build: cukup kompilasi main.cpp, contoh: g++ -std=c++11 main.cpp -o balatro
// Jangan kompilasi file .cpp lain secara bersamaan karena sudah di-include di sini.
#include "ChosenHand.cpp"
#include "HandChecker.cpp"
#include "HandGenerator.cpp"
#include "HandPlayer.cpp"
#include "ScoringRule.cpp"
#include "GameManager.cpp"

int main() {
    GameManager game;
    game.runSession();
    return 0;
}
