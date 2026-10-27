// Unity build: semua file .cpp di-include di sini supaya cukup mengompilasi
// main.cpp saja (mis. lewat tombol Run di VS Code / Code Runner):
//     g++ main.cpp -o main
// Catatan: jangan kompilasi file .cpp lain secara terpisah bersama main.cpp,
// karena akan menyebabkan error "multiple definition".
#include "ChosenHand.cpp"
#include "HandChecker.cpp"
#include "HandGenerator.cpp"
#include "HandPlayer.cpp"
#include "ScoringRule.cpp"
#include "GameManager.cpp"

int main() {
    GameManager g;
    g.runSession();
    g.runSession();
    return 0;
}
