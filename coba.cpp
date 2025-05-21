#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio> // Untuk FILE handling
using namespace std;

// Struktur Node untuk Linked List
struct Node
{
    char judul[100];
    int tahun;
    char genre[20];
    float rating;
    Node *next;
};

// Pointer ke awal daftar film
Node *head = nullptr;

// Array tipe genre yang valid
char genreValid[4][20] = {"horor", "komedi", "action", "romance"};

// Mengecek apakah genre valid
bool cekGenreValid(const char *type)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(genreValid[i], type) == 0)
        {
            return true;
        }
    }
    return false;
}

// Fungsi kembali ke menu dengan validasi input
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

// Menampilkan Menu
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

// Menyimpan data film ke file
void simpanDataFilm()
{
    FILE *file = fopen("data_film.txt", "w");
    if (file == nullptr)
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    Node *temp = head;
    while (temp != nullptr)
    {
        fprintf(file, "%s,%d,%s,%.2f\n",
                temp->judul,
                temp->tahun,
                temp->genre,
                temp->rating);
        temp = temp->next;
    }

    fclose(file);
}

// Menambahkan film baru ke linked list
void tambahFilm()
{
    Node *newFilm = new Node;
    cout << "\nJudul Film: ";
    cin.ignore();
    cin.getline(newFilm->judul, 100);

    cout << "Tahun Film: ";
    cin >> newFilm->tahun;

    cin.ignore();
    cout << "Genre: ";
    cin.getline(newFilm->genre, 20);

    if (!cekGenreValid(newFilm->genre))
    {
        cout << "Error: Genre tidak valid! Harus salah satu dari: horor, komedi, action, romance.\n";
        delete newFilm;
        return;
    }

    cout << "Rating Film: ";
    cin >> newFilm->rating;

    newFilm->next = head;
    head = newFilm;
    simpanDataFilm();
    cout << "Film berhasil ditambahkan!" << endl;
}

// Pengurutan film secara manual dalam linked list
void urutkanFilm(bool ascending)
{
    if (head == nullptr || head->next == nullptr)
        return;

    bool swapped;
    do
    {
        swapped = false;
        Node *temp = head;
        while (temp->next != nullptr)
        {
            if ((ascending && temp->rating > temp->next->rating) ||
                (!ascending && temp->rating < temp->next->rating))
            {
                swap(temp->judul, temp->next->judul);
                swap(temp->tahun, temp->next->tahun);
                swap(temp->genre, temp->next->genre);
                swap(temp->rating, temp->next->rating);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);
}

// Menampilkan film setelah sorting
void tampilkanFilm(bool ascending)
{
    if (head == nullptr)
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

    Node *temp = head;
    while (temp != nullptr)
    {
        cout << left
             << setw(20) << temp->judul
             << setw(10) << temp->tahun
             << setw(15) << temp->genre
             << setw(10) << fixed << setprecision(2) << temp->rating
             << endl;
        temp = temp->next;
    }
    cout << string(55, '=') << endl;

    if (!kembaliKeMenu())
    {
        exit(0);
    }
}

// **Sequential search untuk pencarian film**
void cariFilm()
{
    char judulCari[100];
    cout << "\nMasukkan Judul Film yang dicari: ";
    cin.ignore();
    cin.getline(judulCari, 100);

    Node *temp = head;
    bool ditemukan = false;
    while (temp != nullptr)
    {
        if (strcmp(temp->judul, judulCari) == 0)
        {
            cout << "\nFilm ditemukan:\n";
            cout << "Judul: " << temp->judul << endl;
            cout << "Tahun: " << temp->tahun << endl;
            cout << "Genre: " << temp->genre << endl;
            cout << "Rating: " << fixed << setprecision(2) << temp->rating << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
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

// **Menghapus film dari linked list**
void hapusFilm()
{
    char judulHapus[100];
    cout << "\nMasukkan Judul Film yang akan dihapus: ";
    cin.ignore();
    cin.getline(judulHapus, 100);

    Node *temp = head, *prev = nullptr;
    bool ditemukan = false;

    while (temp != nullptr)
    {
        if (strcmp(temp->judul, judulHapus) == 0)
        {
            if (prev == nullptr)
                head = temp->next;
            else
                prev->next = temp->next;

            delete temp;
            simpanDataFilm();
            cout << "Film berhasil dihapus!" << endl;
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
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
