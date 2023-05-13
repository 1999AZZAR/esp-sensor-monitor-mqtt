# Sensor Data to Adafruit IO MQTT Readme

Kode ini memungkinkan Anda untuk membaca data sensor dari papan Arduino dan mempublikasikannya ke Adafruit IO MQTT. Kode ini menggunakan modul Wi-Fi ESP8266 dan SoftwareSerial untuk komunikasi dengan papan Arduino.

## Persyaratan

Untuk menggunakan kode ini, Anda akan membutuhkan komponen berikut:

- Arduino board (kompatibel dengan ESP8266)
- Modul Wi-Fi ESP8266
- Sensor yang terhubung ke papan Arduino (misalnya, suhu, api, gas)
- Akun Adafruit IO dengan akses MQTT (nama pengguna dan kunci)

## Instalasi

Untuk menginstal dan mengatur kode, ikuti langkah-langkah berikut:

1. Install library yang diperlukan:
   - `ESP8266WiFi`: Library ini memungkinkan modul ESP8266 terhubung ke jaringan Wi-Fi.
   - `SoftwareSerial`: Library ini menyediakan komunikasi serial perangkat lunak antara papan Arduino dan modul ESP8266.
   - `Adafruit_MQTT`: Library ini menyediakan fungsionalitas MQTT untuk berinteraksi dengan Adafruit IO.
   - `Adafruit_MQTT_Client`: Library ini menyediakan implementasi klien MQTT.

2. Konfigurasikan pengaturan Wi-Fi dan Adafruit IO:
   - Ganti `"YOUR_WIFI_SSID"` dengan SSID (nama) jaringan Wi-Fi Anda.
   - Ganti `"YOUR_WIFI_PASSWORD"` dengan kata sandi jaringan Wi-Fi Anda.
   - Ganti `"YOUR_AIO_USERNAME"` dengan nama pengguna Adafruit IO Anda.
   - Ganti `"YOUR_AIO_KEY"` dengan kunci Adafruit IO Anda.

3. Hubungkan papan Arduino dengan modul ESP8266 menggunakan SoftwareSerial:
   - Tentukan pin RX dan TX untuk komunikasi SoftwareSerial di dalam kode (`SOFT_SERIAL_RX_PIN` dan `SOFT_SERIAL_TX_PIN`).
   - Hubungkan pin RX modul ESP8266 ke pin TX papan Arduino, dan sebaliknya.

4. Tentukan topik MQTT di dalam kode:
   - Sesuaikan topik MQTT sesuai dengan feed Adafruit IO Anda. Topik-topik ini akan digunakan untuk mempublikasikan data sensor.

5. Unggah kode ke papan Arduino.

## Penggunaan

Untuk menggunakan kode ini dan mempublikasikan data sensor ke Adafruit IO MQTT, ikuti langkah-langkah berikut:

1. Pastikan papan Arduino telah dinyalakan dan terhubung dengan modul ESP8266.

2. Monitor output serial papan Arduino untuk memverifikasi koneksi Wi-Fi dan MQTT.
   - Output serial akan memberikan informasi tentang status koneksi dan pesan kesalahan yang mungkin terjadi.

3. Hubungkan sensor ke papan Arduino dan pastikan mereka menghasilkan data dalam format yang diharapkan.
   - Kode ini mengharapkan format data mirip dengan: `"Temp: 25.0, Fire: 123, Gas: 456, Output: Safe=0.1, Warning=0.2, Danger=0.7"`.
   - Modifikasi logika parsing di fungsi `loop()` jika format data Anda berbeda.

4. Setelah papan Arduino menerima data sensor, data tersebut akan dipublikasikan ke topik MQTT yang sesuai di Adafruit IO.
   - Topik MQTT yang ditentukan di kode (temperature, fire, gas, outputSafe, outputWarning, outputDanger) akan digunakan untuk mempublikasikan data sensor yang sesuai.

5. Monitor dasbor Adafruit IO untuk melihat data sensor dan melacak perubahan secara real-time.
   - Data yang dipublikasikan akan ditampilkan di feed yang sesuai di akun Adafruit IO Anda.

## Troubleshooting
Jika Anda mengalami masalah saat menggunakan kode ini, pertimbangkan langkah-langkah perbaikan berikut:

- Periksa kredensial Wi-Fi dan pastikan modul ESP8266 terhubung dengan jaringan Wi-Fi dengan benar.
- Verifikasi pengaturan MQTT Adafruit IO yang benar (server, port, nama pengguna, kunci).
- Periksa konfigurasi topik MQTT dan pastikan sesuai dengan feed Adafruit IO Anda.
- Verifikasi koneksi antara papan Arduino, modul ESP8266, dan sensor.
- Monitor output serial papan Arduino untuk pesan kesalahan atau masalah koneksi.
- Pastikan data sensor diterima dan diparsing dengan benar di dalam fungsi loop().
- Periksa dasbor Adafruit IO untuk memastikan bahwa data dipublikasikan ke feed yang benar.
- Jika Anda masih mengalami masalah, lihat dokumentasi dari perpustakaan yang digunakan atau cari bantuan dari komunitas atau forum terkait.

## Customization
Anda dapat menyesuaikan kode ini sesuai dengan kebutuhan spesifik Anda:

- Modifikasi logika parsing data sensor di dalam fungsi loop() jika format data berbeda dari contoh.
- Sesuaikan topik MQTT dan feed di dalam kode sesuai dengan pengaturan Adafruit IO Anda.
- Perluas kode untuk mendukung sensor atau fungsionalitas tambahan dengan menambahkan bagian kode yang sesuai.
- Implementasikan penanganan kesalahan dan notifikasi untuk mengatasi situasi yang tidak biasa atau mengirimkan peringatan.

## Lisensi
Kode ini dirilis di bawah Lisensi MIT. Silakan modifikasi dan gunakan kode ini untuk proyek Anda sendiri.

## Penghargaan
- Kode ini menggunakan perpustakaan ESP8266WiFi, SoftwareSerial, dan Adafruit_MQTT, yang bersifat open-source dan banyak digunakan dalam komunitas Arduino.
- Kode ini terinspirasi oleh Adafruit IO dan protokol MQTT, yang memberikan cara mudah untuk menghubungkan dan mempublikasikan data sensor ke Adafruit IO.

## Penulis
Kode ini dikembangkan oleh azzar. Anda dapat menghubungi saya di azzar.mr.zs@gmail.com untuk pertanyaan atau umpan balik.
