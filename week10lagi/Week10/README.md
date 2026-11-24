# Praktikum Week 10 — Pengembangan Week 8

Week10 ini mengikuti struktur dan gameplay dari source Week8 terbaru (`week8_balatro_3hands_3discards.zip`), lalu mengembangkan pemilihan kartu dan pemisahan tanggung jawab class.

## Struktur

```text
Week10/
├── Card.h
├── Hand.h
├── HandGenerator.h / HandGenerator.cpp
├── HandPlayer.h / HandPlayer.cpp
├── ChosenHand.h / ChosenHand.cpp
├── HandChecker.h / HandChecker.cpp
├── HandScoreTable.h / HandScoreTable.cpp
├── ScoringRule.h / ScoringRule.cpp
├── HandResolver.h / HandResolver.cpp
├── JokerSystem.h / JokerSystem.cpp
├── BlindRule.h
├── RewardRule.h
├── GameManager.h / GameManager.cpp
├── main.cpp
├── run.sh
├── run.bat
└── tests/
```

## Alur Game

1. `HandGenerator` membuat 52 kartu standar dan mengacaknya satu kali.
2. Pemain menerima 8 kartu awal.
3. Pemain mendapat 3 kesempatan memainkan hand dan 3 kesempatan discard.
4. Pada setiap aksi, pemain dapat memilih 1–5 posisi kartu dari tangan.
5. Input rapat `415` dibaca sebagai posisi ke-4, ke-1, dan ke-5. Input dengan pemisah seperti `4 1 5` juga diterima. Urutan pilihan dipertahankan di `ChosenHand`.
6. Jika pemain memilih Play, `ChosenHand` dikirim ke `HandResolver`. `HandChecker` menentukan `HandType`, lalu `ScoringRule` menghitung Chips, Mult, dan base score.
7. Setelah base score dihitung, `JokerManager` memberi notifikasi kepada Joker Observer. Dua Joker bawaan mengikuti Week8: Lucky Joker memberi +25 dan Pair Joker menggandakan score jika hand minimal Pair.
8. Kartu yang dimainkan dikeluarkan dari tangan lalu diganti sesuai jumlah kartu yang dimainkan.
9. Jika pemain memilih Discard, setiap posisi yang dipilih langsung diganti dari sisa deck (posisi kartu lain tetap). Kesempatan discard berkurang, sedangkan kesempatan hand tidak berkurang.
10. Ronde berakhir saat blind tercapai atau tiga kesempatan hand habis.

## Catatan kompatibilitas dengan Week8

- Satu ronde menggunakan target Blind 100, 3 kesempatan hand, dan 3 kesempatan discard seperti `GameManager.cpp` pada Week8 yang diberikan.
- Deck dibuat satu kali pada awal ronde; kartu pengganti berasal dari sisa deck yang sama.
- Flush dan Straight hanya dievaluasi jika pemain memilih tepat 5 kartu, mengikuti `HandChecker.cpp` Week8.
- Joker bawaan mempertahankan efek yang ada pada `JokerSystem.h` Week8.
- Untuk Week10, proses pengecekan hand dipisah menjadi `HandChecker`, `HandResolver`, dan `ScoringRule`; data base Chips/Mult berada di `HandScoreTable`.
- Blind pada source Week8 membandingkan hasil akhir hand terhadap target. Implementasi ini mempertahankan perilaku tersebut, bukan mengubahnya menjadi akumulasi beberapa hand.

## Build dan Run

Dari folder `Week10`:

```bash
./run.sh
```

Runner Windows: `run.bat`.

Command g++ satu baris:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp GameManager.cpp HandGenerator.cpp HandPlayer.cpp ChosenHand.cpp HandChecker.cpp HandScoreTable.cpp ScoringRule.cpp HandResolver.cpp JokerSystem.cpp -o Task1
```

Jalankan hasil compile:

```bash
./Task1
```

## Tests

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/selection_test.cpp ChosenHand.cpp -o selection_test && ./selection_test
```

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/handchecker_test.cpp ChosenHand.cpp HandChecker.cpp -o handchecker_test && ./handchecker_test
```

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/deck_test.cpp HandGenerator.cpp -o deck_test && ./deck_test
```

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/scoring_test.cpp ChosenHand.cpp HandChecker.cpp HandScoreTable.cpp ScoringRule.cpp HandResolver.cpp -o scoring_test && ./scoring_test
```
