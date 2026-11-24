BALATRO C++ - ALUR HAND DAN DISCARD (REVISI)

ALUR SETIAP RONDE:
1. Sistem mengocok satu deck standar 52 kartu dan menampilkan 8 kartu.
2. Pemain memilih 1 sampai 5 kartu dari 8 kartu tersebut.
3. Setelah memilih, pemain menentukan tindakan: HAND atau DISCARD.

JIKA MEMILIH DISCARD:
- Kartu yang dipilih dibuang.
- Kartu yang tidak dipilih tetap berada di tangan.
- Sistem mengambil kartu baru dari deck yang sama untuk mengisi slot kosong
  sampai tangan kembali berisi 8 kartu.
- Kesempatan discard berkurang satu.
- Kesempatan hand TIDAK berkurang.
- Jika 3 discard habis, pilihan discard tidak tersedia lagi sampai ronde baru.

JIKA MEMILIH HAND:
- Kartu pilihan masuk ke Hand Checker.
- Scoring dijalankan, lalu dua Joker diterapkan.
- Skor final ditambahkan ke total skor ronde.
- Kesempatan hand berkurang satu.
- Kartu yang dimainkan dikeluarkan; kartu lain dipertahankan dan tangan
  diisi kembali dari deck yang sama hingga 8 kartu jika deck masih tersedia.
- Proses berulang sampai 3 hand dimainkan.

AKHIR RONDE:
- Blind diperiksa berdasarkan total skor dari 3 hand.
- Reward dihitung.
- Jika pemain memilih ronde berikutnya, hand dan discard kembali menjadi 3,
  lalu deck baru dikocok dan 8 kartu baru dibagikan.

JOKER:
- Lucky Joker: +25 poin pada setiap hand.
- Pair Joker: menggandakan skor jika hand minimal Pair.

KOMPILASI:
  g++ -std=c++11 main.cpp -o balatro

JALANKAN:
  ./balatro

Windows MinGW:
  g++ -std=c++11 main.cpp -o balatro.exe
  balatro.exe

Catatan: main.cpp memakai unity build. Kompilasi main.cpp saja, jangan
menambahkan file .cpp lain ke perintah compile.
