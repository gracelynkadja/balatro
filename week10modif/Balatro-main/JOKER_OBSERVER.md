# Balatro-like — Joker Observer Pattern

## Peran class

- `JokerObserver`: interface observer yang menyediakan callback `onScoreCalculated`.
- `Joker`: abstraksi Joker yang juga merupakan `JokerObserver`.
- `JokerManager`: Subject yang menyimpan observer, mendaftarkan Joker melalui `registerObserver()`, lalu mengirim notifikasi.
- `PairJoker`: observer yang menambahkan `+4 Mult` jika hand yang dimainkan adalah Pair.
- `FlatChipJoker`: observer yang menambahkan `+20 Chips` pada setiap hand yang dihitung.

## Alur notifikasi

1. `RunSessionService::processPlayAction()` meminta `GameManager` menyelesaikan chosen hand.
2. `GameManager::resolveHand()` menghasilkan base hand result.
3. `GameManager::createScoreContext()` membuat context dari base result.
4. `GameManager::applyJokers()` meminta `JokerManager` menotifikasi semua Joker.
5. Setiap Joker menerima `ScoreContext` yang sama dan dapat memodifikasi Chips/Mult.
6. Skor akhir dihitung dari `context.chips * context.mult`.

```text
RunSessionService
       |
       v
 GameManager
       |
       v
 JokerManager (Subject)
       |
       +---- notify ----> PairJoker (Observer)
       |
       +---- notify ----> FlatChipJoker (Observer)
       |
       v
 Updated ScoreContext
```

## Menambahkan Joker baru

Buat class baru yang mewarisi `Joker`, implementasikan:
- `getName()`
- `getDescription(const ScoreContext&)`
- `onScoreCalculated(ScoreContext&)`

Kemudian daftarkan di `GameManager::setupJokers()`:

```cpp
jokerManager.registerObserver(std::make_unique<MyJoker>());
```

Tidak perlu mengubah `JokerManager` untuk setiap jenis Joker baru.
