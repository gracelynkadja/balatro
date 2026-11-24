#pragma once

#include "Joker.h"

#include <memory>
#include <vector>

// Subject dalam Observer Pattern.
// JokerManager mengelola observer (Joker) dan memberi notifikasi
// ketika base score sudah dihitung.
class JokerManager {
public:
    // Mendaftarkan Joker sebagai observer.
    void registerObserver(std::unique_ptr<Joker> joker);

    // Alias agar kode lama yang memakai addJoker tetap kompatibel.
    void addJoker(std::unique_ptr<Joker> joker);

    // Mengirim event score-calculated ke seluruh Joker yang terdaftar.
    void notifyScoreCalculated(ScoreContext& context) const;
    void notifyScoreCalculatedWithLog(ScoreContext& context) const;

    int size() const;

private:
    std::vector<std::unique_ptr<Joker>> observers;
};
