#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int BIOSKOP = 100;

struct film
{
    char judul[100];
    int tahun;
    string genre;
    float rating;
};

// Array tipe genre yang valid
string genreValid[4] = {"horor", "komedi", "action", "romance"};

film daftarFilm[BIOSKOP];
int jumlahFilm = 0;

// Pointer untuk mengecek jenis genre yang valid
bool cekGenreValid(string type)
{
    for (int i = 0; i < 4; i++)
    {
        if (genreValid[i] == type)
        {
            return true;
        }
    }
    return false;
}

// Optimasi fungsi kembali ke menu
bool kembaliKeMenu()
{
    char pilihan;
    do
    {
        cout << "\nBalik ke menu? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'y' || pilihan == 'Y')
            return true;
        if (pilihan == 'n' || pilihan == 'N')
            return false;
        cout << "Masukan tidak valid, silakan pilih 'y' atau 'n'.\n";
    } while (true);
}

// Fungsi Menampilkan Menu
void tampilkanMenu()
{
    cout << "\n=== MENU BIOSKOP ===\n"
         << "1. Tambah Film\n"
         << "2. Tampilkan Rating Film Dari Yang Terendah\n"
         << "3. Tampilkan Rating Film Dari Yang Tertinggi\n"
         << "4. Cari Data Film\n"
         << "5. Hapus Data Film\n"
         << "6. Keluar\n"
         << "Pilih menu: ";
}

// Fungsi FILE Menyimpan data film
void simpanDataFilm()
{
    FILE *file = fopen("data_film.txt", "w");
    if (file == nullptr)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    for (int i = 0; i < jumlahFilm; i++)
    {
        fprintf(file, "%s,%d,%s,%.2f\n",
                daftarFilm[i].judul,
                daftarFilm[i].tahun,
                daftarFilm[i].genre.c_str(),
                daftarFilm[i].rating);
    }

    fclose(file);
}

// Fungsi untuk menambahkan film
void tambahFilm()
{
    film newFilm;
    cout << "\nJudul Film: ";
    cin.ignore();
    cin.getline(newFilm.judul, 100);

    cout << "Tahun Film: ";
    cin >> newFilm.tahun;

    cin.ignore();
    cout << "Genre: ";
    getline(cin, newFilm.genre);

    if (!cekGenreValid(newFilm.genre))
    {
        cout << "Error: Genre film tidak valid. Harus salah satu dari: horor, komedi, action, romance.\n";
        return;
    }

    cout << "Rating Film: ";
    cin >> newFilm.rating;

    daftarFilm[jumlahFilm] = newFilm;
    jumlahFilm++;
    simpanDataFilm();
}

// Fungsi pengurutan film
void urutkanFilm(bool ascending)
{
    for (int i = 0; i < jumlahFilm - 1; i++)
    {
        for (int j = 0; j < jumlahFilm - i - 1; j++)
        {
            bool kondisi = ascending ? (daftarFilm[j].rating > daftarFilm[j + 1].rating)
                                     : (daftarFilm[j].rating < daftarFilm[j + 1].rating);
            if (kondisi)
            {
                swap(daftarFilm[j], daftarFilm[j + 1]);
            }
        }
    }
}

// Fungsi untuk menampilkan film setelah pengurutan
void tampilkanFilm(bool ascending)
{
    if (jumlahFilm == 0)
    {
        cout << "Belum ada data film." << endl;
        return;
    }

    urutkanFilm(ascending);
    cout << setw(20) << left << "Judul"
         << setw(10) << "Tahun"
         << setw(15) << "Genre"
         << setw(10) << "Rating" << endl;
    cout << string(55, '=') << endl;

    for (int i = 0; i < jumlahFilm; i++)
    {
        cout << left
             << setw(20) << daftarFilm[i].judul
             << setw(10) << daftarFilm[i].tahun
             << setw(15) << daftarFilm[i].genre
             << setw(10) << fixed << setprecision(2) << daftarFilm[i].rating
             << endl;
    }
    cout << string(55, '=') << endl;

    if (!kembaliKeMenu())
    {
        exit(0);
    }
}

// Fungsi mencari film
void cariFilm()
{
    char judulCari[100];
    cout << "\nMasukkan Judul Film yang dicari: ";
    cin.ignore();
    cin.getline(judulCari, 100);

    bool ditemukan = false;
    for (int i = 0; i < jumlahFilm; i++)
    {
        if (strcmp(daftarFilm[i].judul, judulCari) == 0)
        {
            cout << "\nFilm ditemukan:\n";
            cout << "Judul: " << daftarFilm[i].judul << endl;
            cout << "Tahun: " << daftarFilm[i].tahun << endl;
            cout << "Genre: " << daftarFilm[i].genre << endl;
            cout << "Rating: " << fixed << setprecision(2) << daftarFilm[i].rating << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Film tidak ditemukan." << endl;
    }

    if (!kembaliKeMenu())
    {
        exit(0);
    }
}

// Fungsi menghapus film
void hapusFilm()
{
    char judulHapus[100];
    cout << "\nMasukkan Judul Film yang akan dihapus: ";
    cin.ignore();
    cin.getline(judulHapus, 100);

    bool ditemukan = false;
    for (int i = 0; i < jumlahFilm; i++)
    {
        if (strcmp(daftarFilm[i].judul, judulHapus) == 0)
        {
            for (int j = i; j < jumlahFilm - 1; j++)
            {
                daftarFilm[j] = daftarFilm[j + 1];
            }
            jumlahFilm--;
            simpanDataFilm();
            cout << "Film berhasil dihapus!" << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Film tidak ditemukan." << endl;
    }

    if (!kembaliKeMenu())
    {
        exit(0);
    }
}

int main()
{
    int pilihan;
    do
    {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahFilm();
            break;
        case 2:
            tampilkanFilm(true);
            break;
        case 3:
            tampilkanFilm(false);
            break;
        case 4:
            cariFilm();
            break;
        case 5:
            hapusFilm();
            break;
        case 6:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 6);

    return 0;
}
