# Pemantauan Data Sensor dengan Adafruit IO MQTT
Panduan ini memberikan instruksi tentang cara memantau data sensor menggunakan papan Arduino, melakukan perhitungan logika kabur, dan mempublikasikan data ke Adafruit IO MQTT untuk pelacakan dan visualisasi secara real-time.

## Pemantauan Data Sensor
Berikut ini adalah contoh kode untuk memantau data sensor menggunakan papan Arduino. Kode ini membaca nilai sensor suhu, kebakaran, dan gas (asap) serta melakukan perhitungan logika kabur untuk menentukan tingkat keamanan, peringatan, dan bahaya berdasarkan pembacaan sensor. Kode ini juga mencakup buzzer yang diaktifkan ketika tingkat bahaya melebihi ambang batas tertentu.

## Persyaratan
Untuk menjalankan kode ini, Anda akan membutuhkan komponen-komponen berikut:

- Papan Arduino (telah diuji pada Arduino Uno)
- Sensor suhu dan kelembaban DHT11
- Sensor kebakaran (input analog)
- Sensor gas (input analog)
- Buzzer (output digital)
- Koneksi
- Buat koneksi-koneksi berikut antara komponen-komponen dan papan Arduino:

	- Hubungkan sensor DHT11 ke pin digital 8 pada papan Arduino.
	- Hubungkan sensor kebakaran ke pin analog A2 pada papan Arduino.
	- Hubungkan sensor gas ke pin analog A3 pada papan Arduino.
	- Hubungkan buzzer ke pin digital 9 pada papan Arduino.

## Penggunaan
Ikuti langkah-langkah berikut untuk menggunakan kode ini:

1. Pasang perpustakaan yang diperlukan:

	- dht.h (untuk sensor DHT11)
	- ESP8266WiFi (untuk konektivitas Wi-Fi)
	- SoftwareSerial (untuk komunikasi dengan modul ESP8266)
	- Adafruit_MQTT (untuk fungsionalitas MQTT)
	- Adafruit_MQTT_Client (untuk implementasi klien MQTT)

2. Unggah kode ke papan Arduino menggunakan Arduino IDE atau perangkat lunak yang kompatibel lainnya.

3. Buka serial monitor untuk melihat pembacaan sensor, perhitungan logika kabur, dan status koneksi MQTT. Pastikan baud rate diatur menjadi 115200.

4. Kode ini akan terus-menerus membaca data sensor, melakukan perhitungan, dan mempublikasikan data ke Adafruit IO MQTT. Serial monitor akan menampilkan pembacaan sensor, perhitungan logika kabur, dan status koneksi MQTT.

5. Pantau dasbor Adafruit IO untuk melihat data sensor dan melacak perubahan secara real-time. Data yang dipublikasikan akan ditampilkan pada feed yang sesuai di akun Adafruit IO Anda.

## Penjelasan
Berikut ini adalah penjelasan tentang fungsionalitas kode:

1. Kode dimulai dengan mengimpor perpustakaan yang diperlukan dan mendefinisikan konstanta dan variabel untuk konfigurasi pin, pembacaan sensor, dan pengaturan MQTT.

2. Fungsi `setup()` mengatur pin-pin input dan output, menginisialisasi komunikasi serial untuk tujuan debugging, dan membuat koneksi Wi-Fi dengan modul ESP8266.

3. Fungsi `loop()`	merupakan loop program utama yang berjalan secara kontinu. Dalam loop ini, kode melakukan langkah-langkah berikut:

	a. Membaca suhu dan kelembaban dari sensor DHT11 menggunakan fungsi DHT.read11().
	
	b. Memeriksa apakah pembacaan DHT11 berhasil menggunakan konstanta DHTLIB_OK.
	
	c. Jika pembacaan berhasil, kode mengambil nilai suhu dari sensor DHT11.
	
	d. Kode menjaga sebuah array pembacaan suhu untuk menghitung suhu rata-rata. Ia memperbarui array, menghitung rata-rata, dan menerapkan offset untuk menyesuaikan pembacaan suhu.
	
	e. Kode membaca nilai analog dari sensor kebakaran dan gas, dan mengubahnya menjadi satuan yang relevan menggunakan konstanta yang ditentukan.
	
	f. Perhitungan logika kabur dilakukan untuk suhu, tingkat kebakaran, dan tingkat gas untuk menentukan tingkat dingin, hangat, panas, tidak ada, kecil, besar, tidak ada gas, gas ringan, dan gas berat.
	
	g. Aturan logika kabur diterapkan untuk menentukan tingkat output keamanan, peringatan, dan bahaya.
	
	h. Tingkat output disesuaikan untuk memastikan jumlahnya sama dengan 1.
	
	i. Pembacaan sensor, perhitungan logika kabur, dan tingkat output dicetak ke serial monitor untuk tujuan debugging dan pemantauan.
	
	j. Buzzer diaktifkan jika tingkat bahaya melebihi ambang batas tertentu; jika tidak, buzzer dimatikan.
	
	k. Kode membuat koneksi MQTT dengan Adafruit IO menggunakan modul Wi-Fi dan nama pengguna serta kunci Adafruit IO yang diberikan.
	
	l. Setelah koneksi MQTT terbentuk, kode mempublikasikan data sensor ke topik MQTT yang sesuai di Adafruit IO. Topik-topik ini didefinisikan dalam kode dan dapat disesuaikan dengan feed Adafruit IO Anda.
	
	m. Kode terus-menerus memeriksa pesan-pesan MQTT yang masuk, meskipun tidak ada fungsionalitas khusus terkait penerimaan pesan yang diimplementasikan dalam kode ini. Bagian ini dapat disesuaikan untuk menangani pesan-pesan yang masuk jika diperlukan.
	
	n. Delay singkat ditambahkan sebelum membaca input lagi untuk menghindari fluktuasi cepat dalam pembacaan.

Kode mengulangi langkah-langkah dalam fungsi `loop()` secara tak terbatas, terus memantau data sensor, melakukan perhitungan logika kabur, dan mempublikasikan data ke Adafruit IO MQTT.
Catatan: Penting untuk memastikan bahwa perpustakaan yang diperlukan diinstal, koneksi sensor dibuat dengan benar, dan konfigurasi Wi-Fi dan Adafruit IO diatur dengan benar sebelum menjalankan kode. Juga, sesuaikan konfigurasi pin dan nilai kalibrasi sesuai dengan setup perangkat keras dan persyaratan spesifik Anda.

## Penyesuaian
Anda dapat menyesuaikan kode sesuai dengan kebutuhan spesifik Anda. Berikut ini adalah beberapa modifikasi yang mungkin dilakukan:

- Sesuaikan penugasan pin: Jika Anda telah menghubungkan sensor atau buzzer ke pin yang berbeda pada papan Arduino, pastikan untuk memperbarui penugasan pin dalam kode sesuai dengan itu.

- Modifikasi nilai kalibrasi: Kode ini mencakup nilai offset dan rentang pemetaan untuk pembacaan sensor. Anda mungkin perlu menyesuaikan nilai-nilai ini berdasarkan karakteristik sensor Anda atau persyaratan aplikasi spesifik.

- Ubah aturan logika kabur: Perhitungan dan aturan logika kabur yang digunakan dalam kode ini didasarkan pada rentang dan kondisi tertentu. Anda dapat mengubah aturan-aturan ini sesuai dengan kriteria keamanan dan tingkat ambang batas aplikasi Anda.

- Tambahkan sensor atau fungsi tambahan: Jika Anda memiliki sensor atau aktuator tambahan yang perlu diintegrasikan ke dalam sistem, Anda dapat menambahkan kode yang diperlukan untuk membaca nilai mereka dan melakukan tindakan yang relevan berdasarkan pembacaan sensor.

- Implementasikan fungsionalitas MQTT tambahan: Saat ini kode ini mempublikasikan data sensor ke Adafruit IO MQTT, tetapi Anda dapat memperluasnya untuk berlangganan topik MQTT dan menangani pesan-pesan yang masuk jika diperlukan.

- Sesuaikan dasbor Adafruit IO: Adafruit IO menyediakan dasbor yang dapat disesuaikan di mana Anda dapat membuat widget untuk memvisualisasikan dan berinteraksi dengan data sensor Anda. Anda dapat menyesuaikan dasbor sesuai dengan preferensi Anda dan menampilkan data dengan cara yang bermakna.

- Implementasikan pencatatan data atau pemantauan jarak jauh: Jika Anda ingin mencatat data sensor atau mengirimkannya ke server jarak jauh untuk pemantauan dan analisis, Anda dapat memasukkan kode tambahan untuk membentuk koneksi jaringan (misalnya Wi-Fi atau Ethernet) dan mengirimkan data melalui protokol seperti MQTT atau HTTP.

## Troubleshooting
Berikut ini adalah beberapa masalah umum yang mungkin Anda temui dan solusi yang mungkin:

- Pembacaan sensor yang salah: Pastikan sensor terhubung dengan benar, dan penugasan pin sudah benar. Periksa spesifikasi sensor dan lembar data untuk persyaratan tertentu.

- Perilaku yang tidak terduga: Verifikasi bahwa nilai kalibrasi sesuai untuk sensor Anda dan sesuaikan jika diperlukan. Periksa kembali aturan logika kabur dan kondisi untuk memastikan mereka mencerminkan logika yang diinginkan.

- Masalah komunikasi serial: Pastikan baud rate yang benar (115200) diatur di serial monitor. Periksa koneksi antara papan Arduino dan komputer.

- Masalah koneksi Wi-Fi: Periksa kembali kredensial Wi-Fi dan pastikan bahwa modul ESP8266 terhubung dengan benar ke jaringan Wi-Fi.

- Masalah koneksi MQTT: Verifikasi bahwa pengaturan MQTT Adafruit IO (server, port, nama pengguna, kunci) sudah benar. Periksa koneksi internet dan pengaturan firewall jika Anda mengalami kesulitan menghubungkan ke Adafruit IO.

- Konfigurasi topik MQTT: Pastikan topik MQTT yang didefinisikan dalam kode cocok dengan feed yang Anda telah atur di Adafruit IO. Jika topik tidak cocok, data mungkin tidak akan dipublikasikan ke feed yang benar.

- Parsing data sensor: Jika format data sensor berbeda dari contoh dalam kode, Anda perlu memodifikasi logika parsing di fungsi loop() untuk mengekstrak pembacaan sensor dengan benar dan menghitung tingkat keluaran.

- Debug menggunakan output serial: Pantau output serial dari papan Arduino untuk memeriksa pesan kesalahan atau masalah koneksi. Output serial dapat memberikan informasi berharga untuk melakukan pemecahan masalah.

- Kompatibilitas pustaka: Pastikan Anda telah menginstal versi pustaka yang benar yang diperlukan dan bahwa mereka kompatibel satu sama lain. Ketidakcocokan antara pustaka dapat menyebabkan perilaku yang tidak terduga.

- Periksa koneksi perangkat keras: Verifikasi bahwa semua komponen perangkat keras terhubung dengan benar, dan tidak ada kabel yang longgar atau koneksi yang rusak. Periksa koneksi fisik antara papan Arduino, sensor, dan modul Wi-Fi.

- Minta bantuan dari komunitas: Jika Anda telah mencoba langkah-langkah pemecahan masalah dan masih menghadapi masalah, pertimbangkan untuk mencari bantuan dari komunitas atau forum terkait. Arduino dan Adafruit IO memiliki komunitas aktif di mana Anda dapat mengajukan pertanyaan dan mendapatkan dukungan.

- Ingatlah untuk mendokumentasikan semua modifikasi yang Anda lakukan pada kode dan melacak perubahan tersebut untuk referensi di masa mendatang. Secara teratur uji dan validasi sistem untuk memastikan fungsionalitas dan keakuratan.

## Kesimpulan
Dengan menggabungkan fungsionalitas dua file readme, Anda sekarang memiliki panduan komprehensif untuk pemantauan data sensor menggunakan papan Arduino dan mempublikasikan data ke Adafruit IO MQTT. Kode ini memungkinkan Anda membaca nilai sensor, melakukan perhitungan, dan menentukan tingkat keamanan berdasarkan logika kabur. Selain itu, kode ini membangun koneksi dengan Adafruit IO MQTT untuk mempublikasikan data sensor untuk pemantauan dan analisis jarak jauh.

Bebas untuk memodifikasi dan menyesuaikan kode sesuai dengan kebutuhan dan pengaturan perangkat keras spesifik Anda. Selamat coding!
