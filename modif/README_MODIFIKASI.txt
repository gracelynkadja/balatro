BALATRO C++ - HASIL MODIFIKASI

Fitur:
- Setiap ronde menghasilkan 8 kartu acak dari deck standar.
- Pemain memasukkan nomor kartu yang ingin dimainkan, dipisahkan spasi.
  Contoh: 1 3 5
- Pilihan harus minimal 1 dan maksimal 5 kartu, tanpa nomor duplikat.
- HandChecker memeriksa kombinasi kartu sebelum Joker dijalankan.
- Lucky Joker menambahkan 25 poin.
- Pair Joker menggandakan skor jika kombinasi minimal Pair.
- Skor akhir digunakan untuk pemeriksaan Blind dan perhitungan reward.

Cara compile (g++):
  g++ -std=c++11 main.cpp -o balatro

Jalankan:
  ./balatro

Di Windows MinGW:
  g++ -std=c++11 main.cpp -o balatro.exe
  balatro.exe

Catatan: main.cpp menggunakan pola unity build dengan meng-include file .cpp.
Karena itu, compile main.cpp saja. Jangan menambahkan semua file .cpp sekaligus.
