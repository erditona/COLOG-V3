# IOT DEVICE - COLOG FOR URSMARTECOSYSTEM (USE)

# PANDUAN SINGKAT

## A. CARA MENGGUNAKAN DENGAN PERANGKAT ASLI

> [!NOTE]
> Microcontroller yang digunakan disini adalah **NodeMCU ESP8266**

1. Download Arduino IDE
2. Buka folder Kode Versi Real Device pada repostory ini.
3. Masukan Library yang tersedia.
4. Upload kode pemograman hinngga selesai.
5. Rakit perangkat sesuai dengan Gambar Rangkaian yang disediakan.
6. Coba Pakai. Pastikan terhubung ke internet dan terhubung ke komputer + ArduinoIDE jika ingin melihat Serial Monitor.
7. Akses aplikasi [USE](https://ursmartecosystem.my.id) untuk melakukan kontrol dan monitor.

## B. CARA MENGGUNAKAN DENGAN SIMULATOR WOKWI

> [!NOTE]
> Microcontroller yang digunakan disini adalah **ESP32**

1. Akses website resmi [Wokwi](https://wokwi.com/)
2. Pilih ESP32, kemudian pilih dan klik Starter Template ESP32
3. Buka folder Kode Versi Simulator pada repostory ini
4. Masukan kode yang ada pada file sketch.ino ke dalam wokwi tab Code
5. Selanjutnya klik Library Manager dan tambahkan library yang dibutuhkan (MQTT dan DHT sensor library for ESPx)
6. Klik tab Simulation, klik tambah, tambahkan perangkat sensor DHT dan Relay, sesuaikan dengan gambar rangkaian yang disediakan
7. Selanjutkan klik tombol play, tunggu hingga berhasil dan lihat serial monitornya pada bagian bawah.
8. Akses aplikasi [USE](https://ursmartecosystem.my.id) untuk melakukan kontrol dan monitor.
