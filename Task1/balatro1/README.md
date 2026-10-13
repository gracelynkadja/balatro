Refleksi

1. Apa struktur invarian dalam program Anda?
Invarian adalah urutan fase tetap yang dikontrol oleh `RunSession`: menghasilkan masukan, menghitung skor dasar, menghitung hadiah, memperbarui uang, fase toko, maju ke ronde berikutnya, yang diulang persis selama 3 ronde. `RunSession` menentukan *kapan* setiap langkah terjadi, tetapi bebas dari penentuan *bagaimana* hal itu dilakukan. Selama urutan ini tetap utuh, *run* akan selalu berperilaku secara dapat diprediksi.

2. Bagian mana saja yang bersifat mutabel?

`IInputGenerator` (`FixedInputGenerator`, `RandomInputGenerator`), `IScoringRule` (`SimpleScoringRule`), `IRewardRule` (`DirectRewardRule`, `BonusRewardRule`), serta isi dari `ShopSystem`. Masing-masing dapat ditukar atau diedit tanpa menyentuh loop, itulah sebabnya bagian-bagian ini aman untuk diubah.

3. Saat Anda mengganti InputGenerator, mengapa RunSession bebas dari perubahan?

`RunSession` hanya bergantung pada antarmuka abstrak `IInputGenerator` dan hanya memanggil fungsi `generate()`. Kelas ini bebas dari pengetahuan tentang kelas konkret apa yang berada di baliknya. `main()` membuat objek `RandomInputGenerator` dan menyuntikannya ke dalam `RunSession`, sehingga hanya perakitannya saja yang berubah, bukan loop-nya. Perubahan hadiah bekerja dengan cara yang sama melalui `IRewardRule`.

4. Apa yang akan terjadi jika logika penilaian ditempatkan di dalam RunSession?

`RunSession` akan memiliki dua tanggung jawab: 
Mengurutkan fase dan menghitung skor. Setiap perubahan penilaian akan mengharuskan penyuntingan pada `RunSession`, yang berisiko merusak urutan fase secara tidak sengaja. Aturan penilaian tidak lagi dapat ditukar tanpa menyentuh loop, pengujian akan menjadi lebih sulit, dan invarian tidak akan lagi terlindungi karena bagian yang stabil dan bagian yang berubah tercampur menjadi satu.