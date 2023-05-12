# Pemantauan Data Sensor

Kode ini merupakan contoh pemantauan data sensor menggunakan papan Arduino. Kode ini membaca nilai sensor suhu, kebakaran, dan gas (asap) serta melakukan perhitungan logika kabur untuk menentukan tingkat keamanan, peringatan, dan bahaya berdasarkan pembacaan sensor. Kode ini juga mencakup penggunaan buzzer yang diaktifkan ketika tingkat bahaya melebihi ambang batas tertentu.

## Persyaratan

Untuk menjalankan kode ini, Anda membutuhkan komponen berikut:

- Papan Arduino (teruji pada Arduino Uno)
- Sensor suhu dan kelembaban DHT11
- Sensor kebakaran (input analog)
- Sensor gas (input analog)
- Buzzer (output digital)

## Koneksi

Lakukan koneksi berikut antara komponen dan papan Arduino:

- Sambungkan sensor DHT11 ke pin digital 3 pada papan Arduino.
- Sambungkan sensor kebakaran ke pin analog A2 pada papan Arduino.
- Sambungkan sensor gas ke pin analog A3 pada papan Arduino.
- Sambungkan buzzer ke pin digital 9 pada papan Arduino.

## Penggunaan

Ikuti langkah-langkah berikut untuk menggunakan kode ini:

1. Pasang perpustakaan yang diperlukan:
   - dht.h (untuk sensor DHT11)

2. Unggah kode ke papan Arduino menggunakan Arduino IDE atau perangkat lunak yang kompatibel lainnya.

3. Buka serial monitor untuk melihat pembacaan sensor dan perhitungan logika kabur. Pastikan baud rate diatur ke 115200.

4. Kode ini akan terus-menerus membaca data sensor dan melakukan perhitungan. Serial monitor akan menampilkan suhu, tingkat kebakaran, tingkat gas, dan tingkat keluaran keamanan, peringatan, dan bahaya.

5. Amati buzzer yang menyala ketika tingkat bahaya melebihi ambang batas. Ini menunjukkan adanya situasi yang berpotensi berbahaya.

## Penjelasan
Berikut adalah penjelasan mengenai fungsionalitas kode:

1. Kode diawali dengan mengimpor perpustakaan yang diperlukan dan mendefinisikan konstanta dan variabel untuk konfigurasi pin dan pembacaan sensor.

2. Fungsi `setup()` mengatur pin input dan output serta menginisialisasi komunikasi serial untuk tujuan debugging.

3. Fungsi `loop()` adalah loop program utama yang berjalan secara terus-menerus. Dalam loop ini, kode melakukan langkah-langkah berikut:

    a. Membaca suhu dan kelembaban dari sensor DHT11 menggunakan fungsi DHT.read11().

    b. Memeriksa apakah pembacaan DHT11 berhasil menggunakan konstanta DHTLIB_OK.

    c. Jika pembacaan berhasil, kode mengambil nilai suhu dari sensor DHT11.

    d. Kode ini mempertahankan sebuah array pembacaan suhu untuk menghitung suhu rata-rata. Array tersebut diperbarui, suhu rata-rata dihitung, dan diberikan offset untuk menyesuaikan pembacaan suhu.

    e. Membaca nilai analog dari sensor kebakaran dan gas dan mengonversinya ke dalam satuan yang relevan menggunakan konstanta yang ditentukan.

    f. Perhitungan logika kabur dilakukan untuk tingkat suhu, tingkat kebakaran, dan tingkat gas untuk menentukan derajat dingin, hangat, panas, tidak ada, kecil, besar, tidak ada gas, gas ringan, dan gas berat.

    g. Aturan logika kabur diterapkan untuk menentukan tingkat keluaran keamanan, peringatan, dan bahaya.

    h. Tingkat keluaran disesuaikan agar jumlahnya sama dengan 1.

    i. Pembacaan sensor, perhitungan logika kabur, dan tingkat keluaran dicetak pada serial monitor untuk tujuan debugging dan pemantauan.

    j. Buzzer diaktifkan jika tingkat bahaya melebihi ambang batas tertentu; jika tidak, buzzer dimatikan.

    k. Diberikan penundaan singkat sebelum membaca input kembali untuk menghindari fluktuasi cepat dalam pembacaan.

4. Kode mengulangi langkah-langkah dalam fungsi `loop()` secara terus-menerus, terus memantau data sensor dan memperbarui keluaran berdasarkan perhitungan logika kabur.

Catatan: Penting untuk memastikan bahwa perpustakaan yang diperlukan terinstal dan koneksi sensor dibuat dengan benar sebelum menjalankan kode ini. Selain itu, sesuaikan konfigurasi pin dan nilai kalibrasi sesuai dengan setup perangkat keras dan kebutuhan spesifik Anda.

## Penyesuaian
Anda dapat menyesuaikan kode ini sesuai dengan kebutuhan Anda. Berikut beberapa modifikasi yang mungkin dilakukan:

- Sesuaikan penugasan pin: Jika Anda telah menghubungkan sensor atau buzzer ke pin yang berbeda pada papan Arduino, pastikan untuk memperbarbarui penugasan pin dalam kode sesuai dengan konfigurasi Anda.

- Modifikasi nilai kalibrasi: Kode ini mencakup nilai offset dan rentang pemetaan untuk pembacaan sensor. Anda mungkin perlu menyesuaikan nilai-nilai ini berdasarkan karakteristik sensor Anda atau persyaratan aplikasi tertentu.

- Ubah aturan logika kabur: Perhitungan logika kabur dan aturan yang digunakan dalam kode ini didasarkan pada rentang dan kondisi tertentu. Anda dapat mengubah aturan ini sesuai dengan kriteria keamanan dan ambang batas aplikasi Anda.

- Tambahkan sensor atau fungsionalitas tambahan: Jika Anda memiliki sensor atau aktuator tambahan yang perlu diintegrasikan ke dalam sistem, Anda dapat menambahkan kode yang diperlukan untuk membaca nilai sensor dan melakukan tindakan yang relevan berdasarkan pembacaan sensor.

- Implementasikan pencatatan data atau pemantauan jarak jauh: Jika Anda ingin mencatat data sensor atau mengirimkannya ke server jarak jauh untuk pemantauan dan analisis, Anda dapat memasukkan kode tambahan untuk membangun koneksi jaringan (misalnya, Wi-Fi atau Ethernet) dan mengirimkan data melalui protokol seperti MQTT atau HTTP.

## Troubleshooting
Berikut adalah beberapa masalah umum yang mungkin Anda temui dan solusi yang mungkin:

- Pembacaan sensor yang tidak benar: Pastikan sensor terhubung dengan benar dan penugasan pin sudah tepat. Periksa spesifikasi sensor dan lembar data untuk persyaratan khusus.

- Perilaku yang tidak diharapkan: Verifikasi bahwa nilai kalibrasi sesuai dengan sensor Anda dan sesuaikan jika diperlukan. Periksa aturan logika kabur dan kondisi untuk memastikan sesuai dengan logika yang diinginkan.

- Masalah komunikasi serial: Pastikan baud rate yang benar (115200) diatur di serial monitor. Periksa koneksi antara papan Arduino dan komputer.

- Buzzer tidak berfungsi: Pastikan buzzer terhubung ke pin yang benar, dan mode pin sudah diatur dengan benar. Periksa apakah buzzer memerlukan komponen atau rangkaian tambahan.

## Kesimpulan
Kode ini memberikan kerangka kerja untuk memantau data sensor dan melakukan perhitungan logika kabur untuk menentukan tingkat keamanan berdasarkan pembacaan sensor suhu, kebakaran, dan gas. Kode ini memperlihatkan bagaimana papan Arduino dapat digunakan untuk memproses data sensor dan membuat keputusan berdasarkan aturan yang telah ditentukan sebelumnya. Dengan melakukan penyesuaian kode sesuai dengan kebutuhan spesifik Anda, Anda dapat membuat sistem pemantauan sensor dan keamanan yang handal.

Untuk informasi dan sumber daya lebih lanjut mengenai pemrograman Arduino, silakan merujuk pada dokumentasi resmi Arduino dan tutorial online.

Anda dapat memodifikasi dan menyesuaikan kode ini sesuai dengan kebutuhan Anda. Selamat mencoba dan semoga sukses!
