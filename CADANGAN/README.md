Refleksi

1. Apa struktur invarian dalam program Anda?
Invarian adalah urutan fase tetap yang dikontrol oleh `RunSession`: menghasilkan masukan, menghitung skor dasar, menghitung hadiah (HP yang didapat), memperbarui HP, fase toko, maju ke ronde berikutnya, yang diulang persis selama 3 ronde. `RunSession` menentukan *kapan* setiap langkah terjadi, tetapi bebas dari penentuan *bagaimana* hal itu dilakukan. Selama urutan ini tetap utuh, *run* akan selalu berperilaku secara dapat diprediksi.

2. Bagian mana saja yang bersifat mutabel?

`IInputGenerator` (`FixedInputGenerator`, `RandomInputGenerator`), `IScoringRule` (`SimpleScoringRule`), `IRewardRule` (`DirectRewardRule`, `BonusRewardRule`), serta isi dari `ShopSystem`. Masing-masing dapat ditukar atau diedit tanpa menyentuh loop, itulah sebabnya bagian-bagian ini aman untuk diubah.

3. Saat Anda mengganti InputGenerator, mengapa RunSession bebas dari perubahan?

`RunSession` hanya bergantung pada antarmuka abstrak `IInputGenerator` dan