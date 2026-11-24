BALATRO C++ - HASIL MODIFIKASI

Fitur:
- Setiap ronde dimulai dengan 8 kartu acak dari satu deck standar 52 kartu.
- Pemain memiliki 3 kesempatan hand dan 3 kesempatan discard.
- Kesempatan hand berkurang setiap kali pemain memainkan kartu.
- Kesempatan discard berkurang setiap kali pemain membuang kartu.
- Discard: pilih 1-5 kartu, kartu tersebut diganti dari deck.
- Mainkan hand: pilih 1-5 kartu, HandChecker memeriksa kombinasi.
- Kartu yang dimainkan dikeluarkan dari tangan, lalu tangan diisi kembali hingga 8.
- Lucky Joker menambahkan 25 poin.
- Pair Joker menggandakan skor jika kombinasi minimal Pair.
- Skor akhir diperiksa terhadap Blind dan digunakan untuk menghitung reward.

Alur:
1. Pemain melihat 8 kartu.
2. Pilih Mainkan hand atau Buang kartu.
3. Pemain dapat melakukan discard maksimal 3 kali.
4. Pemain dapat memainkan hand maksimal 3 kali.
5. Setelah hand dimainkan, checker, scoring, dan Joker dijalankan.
6. Ronde berakhir jika Blind berhasil dilewati atau 3 kesempatan hand habis.

Cara compile (g++):
  g++ -std=c++11 main.cpp -o balatro

Jalankan:
  ./balatro

Di Windows MinGW:
  g++ -std=c++11 main.cpp -o balatro.exe
  balatro.exe

Catatan: main.cpp menggunakan unity build dengan meng-include file .cpp.
Kompilasi main.cpp saja, jangan menambahkan semua file .cpp sekaligus.
