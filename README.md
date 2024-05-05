# 🌐 IOT DEVICE - COLOG V3 FOR URSMARTECOSYSTEM (USE) 🛠️
![IoTDevice(mini)](https://github.com/erditona/Proyek-2/assets/91595733/6616ca5c-d72c-4642-80ac-570f9d8cd6cc)

## 📋 Deskripsi
Proyek ini adalah implementasi perangkat Internet of Things (IoT) yang dapat digunakan dalam ekosistem pintar [URSMARTECOSYSTEM](https://ursmartecosystem.my.id). Perangkat ini dapat dikontrol dan dimonitor dari jarak jauh melalui aplikasi USE.

## 🚀 Fitur Utama
- 📡 Kontrol jarak jauh melalui aplikasi USE.
- 🌡️ Monitoring suhu dan kelembaban menggunakan sensor DHT.
- 📶 Cepat dengan adanya MQTT protokol.

## 🛠️ Tech Stack
- **Microcontroller**: ![NodeMCU ESP8266](https://img.shields.io/badge/NodeMCU-ESP8266-orange) ![ESP32](https://img.shields.io/badge/ESP32-Board-blue)
- **Library**: ![MQTT](https://img.shields.io/badge/MQTT-Library-red) ![DHT sensor library for ESPx](https://img.shields.io/badge/DHT%20Sensor%20Library-blue)
- **Bahasa Pemrograman**: ![Arduino (C++)](https://img.shields.io/badge/Arduino-C++-yellow)

## 📋 PANDUAN SINGKAT

### A. CARA MENGGUNAKAN DENGAN PERANGKAT ASLI

> [!NOTE]
> Microcontroller yang digunakan disini adalah **NodeMCU ESP8266**

1. Download Arduino IDE.
2. Buka folder Kode Versi Real Device pada repositori ini.
3. Masukan Library yang tersedia.
4. Upload kode pemrograman hingga selesai.
5. Rakit perangkat sesuai dengan Gambar Rangkaian yang disediakan.
6. Coba Pakai. Pastikan terhubung ke internet dan terhubung ke komputer + ArduinoIDE jika ingin melihat Serial Monitor.
7. Akses aplikasi [USE](https://ursmartecosystem.my.id) untuk melakukan kontrol dan monitor.

### B. CARA MENGGUNAKAN DENGAN SIMULATOR WOKWI

> [!NOTE]
> Microcontroller yang digunakan disini adalah **ESP32**

1. Akses website resmi [Wokwi](https://wokwi.com/).
2. Pilih ESP32, kemudian pilih dan klik Starter Template ESP32.
3. Buka folder Kode Versi Simulator pada repositori ini.
4. Masukan kode yang ada pada file sketch.ino ke dalam wokwi tab Code.
5. Selanjutnya klik Library Manager dan tambahkan library yang dibutuhkan (MQTT dan DHT sensor library for ESPx).
6. Klik tab Simulation, klik tambah, tambahkan perangkat sensor DHT dan Relay, sesuaikan dengan gambar rangkaian yang disediakan.
7. Selanjutkan klik tombol play, tunggu hingga berhasil dan lihat serial monitornya pada bagian bawah.
8. Akses aplikasi [USE](https://ursmartecosystem.my.id) untuk melakukan kontrol dan monitor.

# 
> [!TIP]
> 1. Untuk pin bisa disesuaikan lagi sesuai dengan keinginan, pastikan saja pin yang dideklarasikan di kode sesuai dengan yang dirangkaikan pada hardware.
> 2. Ganti semua "em4il@m4ildotcom" ke email yang sudah didaftar di aplikasi [USE](https://ursmartecosystem.my.id)
> 3. Pastikan perangkat terhubung dengan Internet.

## 📄 Tambahan
- [Desain Rangkaian](https://drive.google.com/file/d/1xD4OENKsuTlTlvLzV0xnVjdLJiZQFuOu/view?usp=sharing)
- [Alur Kerja](https://drive.google.com/file/d/19PRDmsrBkBQpNa_65_RQLaJd1cBH2TpC/view?usp=sharing)
- [Buku Tutorial](https://play.google.com/store/books/details?id=wIHzEAAAQBAJ)

## ✨Terima Kasih
Kami ingin mengucapkan terima kasih kepada semua kontributor yang telah membantu membangun proyek ini! 🙏
Jika Anda memiliki pertanyaan atau saran, jangan ragu untuk menghubungi kami di [erditona.my.id](https://erditona.my.id).
