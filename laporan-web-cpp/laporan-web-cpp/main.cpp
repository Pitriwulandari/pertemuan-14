// ============================================================
//  LAPORAN PERTEMUAN 14 - PEMROGRAMAN I  (versi WEB dengan C++)
//  Pitri Wulandari (241011450139) - Universitas Pamulang
//
//  Server HTTP mini murni C++ (tanpa library eksternal).
//  Halaman HTML dibangkitkan oleh C++ dari data laporan,
//  gambar dilayani dari folder "media/".
//
//  Build (Linux/Mac): g++ -std=c++17 -pthread main.cpp -o laporan
//  Build (Windows)  : g++ -std=c++17 main.cpp -o laporan.exe -lws2_32
//  Jalankan         : ./laporan   lalu buka http://localhost:8080
// ============================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <thread>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #ifdef _MSC_VER
    #pragma comment(lib, "ws2_32.lib")
  #endif
  typedef SOCKET sock_t;
  #define CLOSESOCK closesocket
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <unistd.h>
  typedef int sock_t;
  #define INVALID_SOCKET (-1)
  #define CLOSESOCK close
#endif

using namespace std;

// ---------------------------------------------------------------
//  DATA LAPORAN
// ---------------------------------------------------------------
struct Blok {            // satu potong isi: paragraf atau gambar
    char tipe;           // 'p' = paragraf, 'i' = gambar
    string a;            // teks paragraf / nama file gambar
    string b;            // keterangan gambar
};
struct Bagian {
    string id, judul, soal;
    vector<string> langkah;   // daftar bernomor (opsional)
    vector<Blok> isi;
};

static Blok P(const string& t)                  { return {'p', t, ""}; }
static Blok G(const string& f, const string& c) { return {'i', f, c}; }

static const string JUDUL   = "TUGAS PERTEMUAN 14";
static const string MATKUL  = "MATA KULIAH PEMROGRAMAN I";
static const string NAMA    = "PITRI WULANDARI";
static const string NIM     = "241011450139";
static const string KELAS   = "04TPLK002";
static const string DOSEN   = "NIKI RATAMA M.Kom";
static const string PRODI   = "PROGRAM STUDI S1 TEKNIK INFORMATIKA - FAKULTAS ILMU KOMPUTER";
static const string KAMPUS  = "UNIVERSITAS PAMULANG 2026";

static vector<Bagian> buatLaporan() {
    vector<Bagian> d;

    Bagian persiapan;
    persiapan.id = "persiapan";
    persiapan.judul = "Persiapan Aplikasi yang Dibutuhkan";
    persiapan.langkah = {
        "Pastikan project FutsalApp dari pertemuan 13 sudah berjalan dengan baik.",
        "Pastikan XAMPP dan service MySQL dalam status Start.",
        "Pastikan kelas Koneksi dan form FormMember sudah ada, termasuk tombol Simpan dan Tampil."
    };
    persiapan.isi = {
        G("image2.png", "Gambar 1 - Pertemuan 13"),
        G("image3.png", "Gambar 2 - Tampilan XAMPP")
    };
    d.push_back(persiapan);

    Bagian l1;
    l1.id = "latihan-1";
    l1.judul = "Latihan 1 - Validasi No HP";
    l1.soal = "Tambahkan validasi agar no HP hanya berisi angka sebelum data diupdate. "
              "Gunakan matches(\"[0-9]+\") pada String.";
    l1.isi = {
        G("image4.png", "Validasi No HP saat berisi huruf"),
        G("image5.png", "Pengujian fitur Simpan"),
        P("Gambar ini menunjukkan pengujian fitur Simpan pada aplikasi Data Member Futsal. "
          "Berdasarkan penambahan kolom Alamat pada tabel member dan form input, data baru "
          "berhasil dimasukkan (dengan Nama: arinal, No HP: 085678999999, Email: "
          "arinal123@gmail.com, dan Alamat: pamulang). Pada panel Status di sebelah kanan "
          "muncul keterangan \"Data berhasil disimpan\", dan data tersebut langsung tampil di "
          "baris terbawah pada tabel JTable lengkap dengan kolom Alamat yang baru ditambahkan.")
    };
    d.push_back(l1);

    Bagian l2;
    l2.id = "latihan-2";
    l2.judul = "Latihan 2 - Konfirmasi Update";
    l2.soal = "Tampilkan kotak konfirmasi sebelum tombol Update dijalankan.";
    l2.isi = {
        G("image6.png", "Memilih data untuk diupdate"),
        G("image7.png", "Kotak dialog Konfirmasi Update"),
        P("Di sini, saya mencoba melakukan proses pembaruan data. Ketika tombol Update diklik, "
          "sistem langsung memunculkan kotak dialog konfirmasi bertuliskan 'Konfirmasi Update' "
          "dengan pesan 'Yakin ingin mengubah data ID 1?'. Dengan adanya dialog ini, proses "
          "update ke database tidak akan langsung tereksekusi kecuali saya menekan tombol Yes, "
          "sehingga mencegah terjadinya kesalahan perubahan data secara tidak sengaja.")
    };
    d.push_back(l2);

    Bagian l3;
    l3.id = "latihan-3";
    l3.judul = "Latihan 3 - JComboBox Pencarian";
    l3.soal = "Tambahkan JComboBox berisi pilihan \"Nama\", \"No HP\", dan \"Email\", lalu ubah "
              "query Cari agar hanya mencari pada kolom yang dipilih.";
    l3.isi = {
        G("image8.png", "Kode JComboBox pada panel pencarian (NetBeans)"),
        P("Nah ini ketika di run:"),
        G("image9.png", "Hasil pengujian saat dijalankan"),
        P("Gambar tersebut menampilkan pengujian validasi nomor HP pada aplikasi saat "
          "dijalankan, di mana pesan peringatan muncul karena inputan mengandung huruf.")
    };
    d.push_back(l3);

    Bagian l4;
    l4.id = "latihan-4";
    l4.judul = "Latihan 4 - Pesan Data Tidak Ditemukan";
    l4.soal = "Jika pencarian tidak menemukan data, tampilkan pesan \"Data tidak ditemukan\" "
              "pada txtOutput.";
    l4.isi = {
        G("image10.png", "Pencarian tanpa hasil"),
        P("Gambar tersebut menunjukkan hasil pengujian fitur pencarian data di mana ketika "
          "kata kunci yang dicari (seperti \"anggl\" dengan pencarian berdasarkan \"Nama\") "
          "tidak ditemukan di database, panel status (txtOutput) berhasil memunculkan pesan "
          "\"Data tidak ditemukan.\" dan tabel data menjadi kosong.")
    };
    d.push_back(l4);

    Bagian l5;
    l5.id = "latihan-5";
    l5.judul = "Latihan 5 - Kolom Alamat";
    l5.soal = "Tambahkan kolom alamat pada tabel member, lalu ikutkan kolom tersebut pada "
              "fitur Edit, Update, dan Cari.";
    l5.isi = {
        G("image11.png", "Tabel member pada phpMyAdmin dengan kolom alamat")
    };
    d.push_back(l5);

    return d;
}

// ---------------------------------------------------------------
//  UTILITAS
// ---------------------------------------------------------------
static string esc(const string& s) {
    string o;
    for (char c : s) {
        switch (c) {
            case '&': o += "&amp;";  break;
            case '<': o += "&lt;";   break;
            case '>': o += "&gt;";   break;
            case '"': o += "&quot;"; break;
            default:  o += c;
        }
    }
    return o;
}

static string mimeDari(const string& f) {
    auto akhir = [&](const char* e) {
        size_t n = strlen(e);
        return f.size() >= n && f.compare(f.size() - n, n, e) == 0;
    };
    if (akhir(".png"))  return "image/png";
    if (akhir(".jpg") || akhir(".jpeg")) return "image/jpeg";
    if (akhir(".gif"))  return "image/gif";
    if (akhir(".svg"))  return "image/svg+xml";
    if (akhir(".css"))  return "text/css";
    return "application/octet-stream";
}

static bool namaFileAman(const string& n) {
    if (n.empty() || n.find("..") != string::npos) return false;
    for (char c : n)
        if (!(isalnum((unsigned char)c) || c == '.' || c == '_' || c == '-')) return false;
    return true;
}

// ---------------------------------------------------------------
//  PEMBANGKIT HALAMAN HTML
// ---------------------------------------------------------------
static const char* CSS = R"CSS(
:root{--bg:#f4f6fb;--card:#fff;--ink:#1d2433;--muted:#5b6478;--brand:#2563eb;--brand2:#1e40af;--line:#e3e8f2}
*{box-sizing:border-box}html{scroll-behavior:smooth}
body{margin:0;font-family:"Segoe UI",system-ui,-apple-system,Roboto,Arial,sans-serif;background:var(--bg);color:var(--ink);line-height:1.7}
header.hero{background:linear-gradient(135deg,var(--brand2),var(--brand));color:#fff;text-align:center;padding:56px 20px 64px}
.hero img{width:130px;height:130px;object-fit:contain;background:#fff;border-radius:50%;padding:8px;box-shadow:0 8px 24px rgba(0,0,0,.25)}
.hero h1{margin:18px 0 2px;font-size:clamp(1.5rem,4vw,2.3rem);letter-spacing:.5px}
.hero h2{margin:0 0 22px;font-weight:500;font-size:clamp(1rem,2.5vw,1.3rem);opacity:.9}
.hero .meta{display:inline-block;text-align:left;background:rgba(255,255,255,.14);border-radius:14px;padding:14px 22px;font-size:.98rem}
.hero .meta div{margin:2px 0}.hero .meta b{display:inline-block;min-width:110px}
.hero .kampus{margin-top:22px;font-weight:600;opacity:.95}.hero .kampus small{display:block;font-weight:400;opacity:.85}
nav{position:sticky;top:0;z-index:10;background:#fff;border-bottom:1px solid var(--line);box-shadow:0 2px 8px rgba(20,30,60,.05)}
nav ul{list-style:none;margin:0 auto;padding:0 12px;max-width:1000px;display:flex;gap:4px;overflow-x:auto}
nav a{display:block;padding:13px 14px;color:var(--muted);text-decoration:none;font-size:.92rem;white-space:nowrap;border-bottom:3px solid transparent}
nav a:hover{color:var(--brand);border-bottom-color:var(--brand)}
main{max-width:1000px;margin:28px auto;padding:0 16px}
section{background:var(--card);border:1px solid var(--line);border-radius:16px;padding:26px;margin-bottom:24px;box-shadow:0 2px 10px rgba(20,30,60,.04);scroll-margin-top:60px}
section h3{margin:0 0 14px;font-size:1.3rem;color:var(--brand2)}
.soal{background:#eef3ff;border-left:4px solid var(--brand);border-radius:8px;padding:12px 16px;margin:0 0 18px}
.soal b{color:var(--brand2)}
ol.langkah{padding-left:22px}
figure{margin:20px 0;text-align:center}
figure img{max-width:100%;height:auto;border:1px solid var(--line);border-radius:10px;cursor:zoom-in;box-shadow:0 3px 12px rgba(20,30,60,.1)}
figcaption{margin-top:8px;font-size:.88rem;font-style:italic;color:var(--muted)}
p.teks{text-align:justify;margin:14px 0}
footer{text-align:center;color:var(--muted);font-size:.88rem;padding:10px 16px 40px}
#lb{position:fixed;inset:0;background:rgba(10,15,30,.88);display:none;align-items:center;justify-content:center;z-index:99;cursor:zoom-out;padding:20px}
#lb img{max-width:96vw;max-height:94vh;border-radius:8px}
@media(max-width:600px){section{padding:18px}.hero .meta b{min-width:90px}}
)CSS";

static string halamanLaporan() {
    vector<Bagian> laporan = buatLaporan();
    ostringstream h;
    int no = 0;

    h << "<!DOCTYPE html><html lang=\"id\"><head><meta charset=\"utf-8\">"
      << "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
      << "<title>" << esc(JUDUL) << " - " << esc(NAMA) << "</title>"
      << "<style>" << CSS << "</style></head><body>";

    // --- Sampul ---
    h << "<header class=\"hero\" id=\"sampul\">"
      << "<img src=\"/media/image1.png\" alt=\"Logo Universitas Pamulang\">"
      << "<h1>" << esc(JUDUL) << "</h1><h2>" << esc(MATKUL) << "</h2>"
      << "<div class=\"meta\">"
      << "<div><b>Disusun oleh</b>: " << esc(NAMA) << "</div>"
      << "<div><b>NIM</b>: " << esc(NIM) << "</div>"
      << "<div><b>Kelas</b>: " << esc(KELAS) << "</div>"
      << "<div><b>Dosen Pengampu</b>: " << esc(DOSEN) << "</div></div>"
      << "<div class=\"kampus\">" << esc(KAMPUS) << "<small>" << esc(PRODI) << "</small></div>"
      << "</header>";

    // --- Navigasi ---
    h << "<nav><ul>";
    for (auto& b : laporan)
        h << "<li><a href=\"#" << b.id << "\">" << esc(b.judul) << "</a></li>";
    h << "</ul></nav><main>";

    // --- Isi tiap bagian ---
    for (auto& b : laporan) {
        h << "<section id=\"" << b.id << "\"><h3>" << esc(b.judul) << "</h3>";
        if (!b.soal.empty())
            h << "<div class=\"soal\"><b>Soal:</b> " << esc(b.soal) << "</div>";
        if (!b.langkah.empty()) {
            h << "<ol class=\"langkah\">";
            for (auto& l : b.langkah) h << "<li>" << esc(l) << "</li>";
            h << "</ol>";
        }
        for (auto& k : b.isi) {
            if (k.tipe == 'p') {
                h << "<p class=\"teks\">" << esc(k.a) << "</p>";
            } else {
                ++no;
                h << "<figure><img src=\"/media/" << esc(k.a) << "\" alt=\"" << esc(k.b)
                  << "\" loading=\"lazy\"><figcaption>" << esc(k.b) << "</figcaption></figure>";
            }
        }
        h << "</section>";
    }

    h << "</main><footer>&copy; 2026 " << esc(NAMA) << " &middot; " << esc(NIM)
      << " &middot; Dilayani oleh server C++</footer>"
      << "<div id=\"lb\"><img alt=\"\"></div>"
      << "<script>"
      << "const lb=document.getElementById('lb'),li=lb.querySelector('img');"
      << "document.querySelectorAll('figure img').forEach(i=>i.onclick=()=>{li.src=i.src;lb.style.display='flex'});"
      << "lb.onclick=()=>lb.style.display='none';"
      << "document.onkeydown=e=>{if(e.key==='Escape')lb.style.display='none'};"
      << "</script></body></html>";
    return h.str();
}

// ---------------------------------------------------------------
//  SERVER HTTP
// ---------------------------------------------------------------
static void kirimSemua(sock_t s, const string& data) {
    size_t terkirim = 0;
    while (terkirim < data.size()) {
        int n = send(s, data.data() + terkirim, (int)(data.size() - terkirim), 0);
        if (n <= 0) return;
        terkirim += (size_t)n;
    }
}

static void kirimRespon(sock_t s, int kode, const string& status,
                        const string& tipe, const string& badan) {
    ostringstream r;
    r << "HTTP/1.1 " << kode << " " << status << "\r\n"
      << "Content-Type: " << tipe << "\r\n"
      << "Content-Length: " << badan.size() << "\r\n"
      << "Connection: close\r\n\r\n";
    kirimSemua(s, r.str());
    kirimSemua(s, badan);
}

static void tangani(sock_t klien) {
    char buf[8192];
    int n = recv(klien, buf, sizeof(buf) - 1, 0);
    if (n <= 0) return;
    buf[n] = '\0';

    istringstream baris(buf);
    string metode, path, versi;
    baris >> metode >> path >> versi;
    size_t q = path.find('?');
    if (q != string::npos) path = path.substr(0, q);

    cout << metode << " " << path << endl;

    if (metode != "GET") {
        kirimRespon(klien, 405, "Method Not Allowed", "text/plain", "405");
        return;
    }
    if (path == "/" || path == "/index.html") {
        kirimRespon(klien, 200, "OK", "text/html; charset=utf-8", halamanLaporan());
        return;
    }
    if (path.rfind("/media/", 0) == 0) {
        string nama = path.substr(7);
        if (namaFileAman(nama)) {
            ifstream f("media/" + nama, ios::binary);
            if (f) {
                string data((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
                kirimRespon(klien, 200, "OK", mimeDari(nama), data);
                return;
            }
        }
    }
    kirimRespon(klien, 404, "Not Found", "text/html; charset=utf-8",
                "<h1>404</h1><p>Halaman tidak ditemukan. <a href=\"/\">Kembali</a></p>");
}

int main(int argc, char** argv) {
    // Urutan prioritas port: argumen > variabel lingkungan PORT (hosting) > 8080
    int port = 8080;
    if (const char* ep = getenv("PORT")) port = atoi(ep);
    if (argc > 1) port = atoi(argv[1]);

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "WSAStartup gagal\n";
        return 1;
    }
#endif

    sock_t server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) { cerr << "Gagal membuat socket\n"; return 1; }

    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((unsigned short)port);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) < 0) {
        cerr << "Bind gagal. Port " << port << " mungkin sedang dipakai.\n";
        return 1;
    }
    if (listen(server, 16) < 0) { cerr << "Listen gagal\n"; return 1; }

    cout << "Laporan Pertemuan 14 aktif di  http://localhost:" << port << "\n"
         << "Tekan Ctrl+C untuk berhenti.\n";

    while (true) {
        sock_t klien = accept(server, nullptr, nullptr);
        if (klien == INVALID_SOCKET) continue;
        // Satu thread per koneksi supaya koneksi kosong/lambat tidak memblokir server
        thread([klien]() {
#ifdef _WIN32
            DWORD tmo = 5000;
            setsockopt(klien, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tmo, sizeof(tmo));
#else
            timeval tmo{5, 0};
            setsockopt(klien, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tmo, sizeof(tmo));
#endif
            tangani(klien);
            CLOSESOCK(klien);
        }).detach();
    }
}
