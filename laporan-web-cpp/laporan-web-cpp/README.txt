LAPORAN PERTEMUAN 14 - PEMROGRAMAN I (WEB DENGAN C++)
Pitri Wulandari (241011450139) - Universitas Pamulang

ISI FOLDER
  main.cpp   -> server web + halaman laporan (semua C++, tanpa library tambahan)
  media/     -> gambar-gambar laporan (image1.png ... image11.png)

CARA MENJALANKAN

[Windows - MinGW / g++]
  g++ -std=c++17 main.cpp -o laporan.exe -lws2_32
  laporan.exe

[Windows - Visual Studio (Developer Command Prompt)]
  cl /EHsc /std:c++17 main.cpp
  main.exe

[Linux / macOS]
  g++ -std=c++17 main.cpp -o laporan
  ./laporan

Lalu buka browser ke:  http://localhost:8080
Ganti port (opsional):  laporan.exe 9000

CATATAN
- Jalankan program dari DALAM folder ini, supaya folder media/ terbaca.
- Jika port 8080 sudah dipakai, jalankan dengan port lain.
- Tekan Ctrl+C untuk menghentikan server.
- Klik gambar di halaman untuk memperbesar, Esc untuk menutup.

HOSTING (Render, gratis, pakai Docker)
  1. Buat repository GitHub, upload isi folder ini (main.cpp, media/, Dockerfile, .dockerignore).
  2. Di render.com: New + -> Web Service -> pilih repository -> Language/Runtime: Docker -> Instance Type: Free.
  3. Klik Create Web Service, tunggu build sekitar 2-5 menit.
  4. Alamat publik muncul, contoh: https://nama-layanan.onrender.com
  Catatan: server membaca port dari variabel PORT secara otomatis.
  Layanan gratis tidur setelah ~15 menit tanpa pengunjung; akses pertama setelahnya butuh sekitar 1 menit.
