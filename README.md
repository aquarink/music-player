# SplashKit C++ Music Player

Repositori ini berisi implementasi program **Music Player** berbasis konsol menggunakan bahasa **C++** dan SDK **SplashKit** (Aktivitas 3.2 dari *Programmer's Field Guide*).

---

## 💻 Spesifikasi Sistem & Lingkungan Pengujian
- **Sistem Operasi**: macOS (Darwin x86_64 / arm64)
- **Compiler**: Apple Clang (`clang++` via Xcode Command Line Tools)
- **Library Multimedia**: SplashKit SDK (didukung oleh SDL2)

---

## 🛠️ Langkah-Langkah Setup & Instalasi

Untuk menduplikasi lingkungan kerja ini di macOS baru, ikuti langkah-langkah command-line berikut:

### 1. Install Prerequisites & Dependencies
Pastikan Xcode Command Line Tools telah terinstal. Jika belum, jalankan:
```bash
xcode-select --install
```

SplashKit membutuhkan dependensi multimedia yang dikelola oleh Homebrew. Instal dependensi tersebut dengan menjalankan perintah instalasi SKM (SplashKit Manager) berikut:
```bash
# Unduh dan jalankan skrip instalasi SplashKit Manager
bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)
```
*Catatan: Proses di atas akan otomatis mengunduh dependensi Homebrew seperti `sdl2`, `sdl2_image`, `sdl2_mixer`, `sdl2_ttf`, `sdl2_net`, `cmake`, `jq`, dan `sponge`.*

### 2. Kompilasi & Instal SplashKit Library secara Lokal
Setelah SKM terpasang di `~/.splashkit`, kompilasi library SplashKit secara native pada macOS Anda dengan menjalankan:
```bash
# Kompilasi native library
~/.splashkit/skm macos install
```
*Jika ditanya password root/sudo di akhir untuk instalasi global, Anda dapat melewati atau membatalkannya jika hanya ingin menggunakannya secara lokal di level user.*

### 3. Inisialisasi Project Workspace
Di dalam folder project Anda, inisialisasi struktur template C++ SplashKit dan direktori resource standar:
```bash
# Buat template program C++ (menghasilkan program.cpp dan konfigurasi VS Code)
~/.splashkit/skm new c++

# Hasilkan folder Resources standar (images, sounds, fonts, dll.)
~/.splashkit/skm resources
```

### 4. Setup File Lagu Uji Coba
SplashKit secara default mencari file audio di folder `Resources/sounds/`.
1. Simpan file audio Anda (misalnya `.mp3`, `.wav`, atau `.ogg`) ke dalam folder `Resources/sounds/`.
2. Sebagai contoh, letakkan sebuah file bernama `sample.mp3` di dalam direktori `Resources/sounds/`.

---

## 🚀 Kompilasi & Menjalankan Program

### Kompilasi Kode
Kompilasi source code C++ menggunakan compiler wrapper dari SKM:
```bash
PATH=~/.splashkit:$PATH skm clang++ -g program.cpp -o music-player
```

### Jalankan Program
Eksekusi file binary yang telah dikompilasi:
```bash
./music-player
```

---

## 📖 Cara Penggunaan Program
Saat program berjalan, Anda akan dihadapkan pada menu konsol interaktif:

1. **Add a new song**:
   - Masukkan nama lagu (misal: `Sample Song`).
   - Masukkan nama file lagu yang berada di folder `Resources/sounds/` (misal: `sample.mp3`).
   - Tentukan status favorit/loved (`y` atau `n`).
2. **Play a song**:
   - Cari lagu dengan memasukkan potongan nama lagu.
   - Pilih nomor lagu yang cocok dari daftar yang muncul untuk memutarnya.
3. **Pause / Resume song**:
   - Menjeda (pause) lagu yang sedang berputar, atau melanjutkan (resume) lagu yang sedang dijeda.
4. **Update a song**:
   - Cari dan pilih lagu yang ingin diubah detailnya.
   - Menu update memungkinkan Anda untuk: mengubah nama, men-toggle status loved, mereset hitungan pemutaran, atau menghapus lagu dari pemutar musik.
5. **Print status**:
   - Menampilkan statistik umum pemutar musik (jumlah lagu, total pemutaran, dan total lagu loved).
6. **Quit**:
   - Keluar dari program dan membersihkan memori/resource SplashKit.
