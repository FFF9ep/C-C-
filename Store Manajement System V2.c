#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

/*UNTUK BISA MENGGUNAKAN PROGRAM INI LOGIN DENGAN User = Admin dan Password = toko123
DAN AGAR DAPAT BERFUNGSI DENGAN BAIK PASTIKAN ANDA MEMILIKI FOLDER "D"
DAN JUGA SELALU BUAT INFORMASI BARANG TERLEBIH DAHULU
PROGRAM INI BELOM FINAL!!!
----FANDI ARDYAN----*/

struct informasiBarang
{
    int idBarang;
    char namaBarang[100];
    char jenisBarang[100];
    int stokBarang;
    int hargaBarang;
} barang;

void menuLogin();
void menuAwal();
void sembunyikanPw();
int login();
void menuManajementInventaris();
void dataBaseTulisBarang();
int cekBarang(int id);
void tambahBarang();
void displayBarang();
void hapusBarang();
void updateStokBarang();
void updateStokBarangNext();

int main()
{
    system("color 0A");
    menuLogin();
    return 0;
}

void sembunyikanPw(char *sandi)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch(); // Baca karakter tanpa menampilkannya
        if (ch == 13) // Jika Enter, selesai
            break;
        else if (ch == 8 && i > 0)
        { // Jika Backspace, hapus karakter sebelumnya
            printf("\b \b");
            i--;
        }
        else
        { // Jika karakter normal, tambahkan ke kata sandi dan tampilkan '*' pada layar
            sandi[i++] = ch;
            printf("*");
        }
    }
    sandi[i] = '\0'; // Akhiri string
}

int login(char *idUser, char *sandi)
{
    if (strcmp(idUser, "Admin") == 0 && strcmp(sandi, "toko123") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void menuLogin()
{
    char idUser[100];
    char sandi[100];

    system("cls");
    printf("Loading");
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    system("cls");
    printf("========== WELCOME TO LOGIN SYSTEM STORE MANAJEMENT ==========\n");
    printf("Please Login On Below!\n");
User_Login:
    printf("Input User Name : ");
    scanf("%s", idUser);

    printf("Input Password  : ");
    sembunyikanPw(sandi);

    if (login(idUser, sandi))
    {
        printf("\nSuccessful Login\n");
        printf("Loading ");
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        menuAwal();
    }
    else
    {
        printf("\nLogin Failed Please Re-Input!\n");
        goto User_Login;
    }
}

void menuAwal()
{
    int menuAwalPilih;
Invalid_Input:
    system("cls");
    printf("========== STORE MANAJEMENT SYSTEM ==========\n");
    printf("Hey User Welcome To My Program!\n");
    printf("Please Use The Following Menu  \n");
    printf("[1] Inventory Management \n");
    printf("[0] Exit Program \n");
    printf("Select Menu Above : ");
    scanf(" %d", &menuAwalPilih);

    switch (menuAwalPilih)
    {
    case 0:
        printf("\n\nThank You For Using My Program\n");
        printf("See You Next Time!\n\n");
        exit(0);
        break;
    case 1:
        menuManajementInventaris();
        break;
    default:
        printf("\nInvalid!\n");
        goto Invalid_Input;
        break;
    }
}

void menuManajementInventaris()
{
    int pilihMenu;
pilih_Menu:
    system("cls");
    printf("========== INVENTORY MANAJEMENT SYSTEM ==========\n");
    printf("Welcome To Inventory!\n");
    printf("Please Use The Following Menu  \n");
    printf("[1] Add Items \n");
    printf("[2] Stock Updates \n");
    printf("[3] Display Of Items \n");
    printf("[4] Delete Items \n");
    printf("[0] Back To Menu Page \n");
    printf("Select Menu Above : ");
    scanf(" %d", &pilihMenu);

    switch (pilihMenu)
    {
    case 0:
        printf("\nThank You\n");
        printf("See You Later!\n");
        printf("Loading ");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(500);
        }

        menuAwal();
        break;
    case 1:
        tambahBarang();
        break;
    case 2:
        updateStokBarang();
        break;
    case 3:
        displayBarang();
        break;
    case 4:
        hapusBarang();
        break;
    default:
        printf("Invalid Input!\n");
        goto pilih_Menu;
        break;
    }
}

void dataBaseTulisBarang(FILE *Project, struct informasiBarang *barang)
{
    Project = fopen("D:\\Items Information.txt", "a+");
    if (Project == NULL)
    {
        printf("Error Opening File!\n");
        exit(0);
    }
    else
    {
        fprintf(Project, "Code ID       : %d\n", barang->idBarang);
        fprintf(Project, "Name Of Goods : %s\n", barang->namaBarang);
        fprintf(Project, "Types Of Goods: %s\n", barang->jenisBarang);
        fprintf(Project, "Goods Stock   : %d\n", barang->stokBarang);
        fprintf(Project, "Item Price    : %d\n\n", barang->hargaBarang);
    }
    fclose(Project);
}

int cekBarang(int id)
{
    FILE *Project = fopen("D:\\Items Information.txt", "r");
    if (Project == NULL)
    {
        printf("Error Opening File!\n");
        exit(0);
    }
    else
    {
        struct informasiBarang barang;

        while (fscanf(Project, "Code ID       : %d\n", &barang.idBarang) == 1)
        {
            fscanf(Project, "Name Of Goods : %[^\n]\n", barang.namaBarang);
            fscanf(Project, "Types Of Goods: %[^\n]\n", barang.jenisBarang);
            fscanf(Project, "Goods Stock   : %d\n", &barang.stokBarang);
            fscanf(Project, "Item Price    : %d\n", &barang.hargaBarang);

            if (barang.idBarang == id)
            {
                fclose(Project);
                return 1;
            }
        }
        fclose(Project);
        return 0;
    }
}

void tambahBarang()
{
    system("cls");
    FILE *Project = fopen("D:\\Items Information.txt", "a+");
    if (Project == NULL)
    {
        printf("Error Opening File!\n");
        exit(0);
    }
    else
    {
        struct informasiBarang barang;
        int jumlahBarang;

        printf("========== WELCOME TO ADD ITEMS! ==========\n");
        printf("Please Follow The Instruction!\n\n");
        printf("How Much Item Do You Want To Add? : ");
        scanf("%d", &jumlahBarang);
        printf("Input Items Information!\n");

        for (int i = 0; i < jumlahBarang; i++)
        {
            printf("Input Items ID       : ");
            scanf("%d", &barang.idBarang);

            if (cekBarang(barang.idBarang))
            {
                printf("Items ID Has Been Entered!\n");
                printf("Please Input Another ID!\n");
                i--;
                continue;
            }

            while (getchar() != '\n')
                ;

            printf("Input Items Name     : ");
            fgets(barang.namaBarang, sizeof(barang.namaBarang), stdin);
            barang.namaBarang[strcspn(barang.namaBarang, "\n")] = '\0';

            printf("Input Types Of Goods : ");
            fgets(barang.jenisBarang, sizeof(barang.jenisBarang), stdin);
            barang.jenisBarang[strcspn(barang.jenisBarang, "\n")] = '\0';

            printf("Input Stock Items    : ");
            scanf("%d", &barang.stokBarang);

            while (getchar() != '\n')
                ;

            printf("Input Item Price     : ");
            scanf("%d", &barang.hargaBarang);

            while (getchar() != '\n')
                ;

            printf("\n");

            dataBaseTulisBarang(Project, &barang);
        }
        fclose(Project);
    }
    printf("Items Added Succesfully\n");
    printf("Returning To Inventory Menu\nLoading");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        Sleep(500);
    }

    menuManajementInventaris();
}

void updateStokBarang()
{
    system("cls");
    FILE *Project = fopen("D:\\Items Information.txt", "r+");
    if (Project == NULL)
    {
        printf("Error Opening File!\n");
        exit(0);
    }
    else
    {
        int idBarangTarget;
        struct informasiBarang barang;
        FILE *temp = fopen("D:\\Temporary.txt", "w");
        if (temp == NULL)
        {
            printf("Error Opening File!\n");
            exit(0);
        }
        printf("========== WELCOME TO UPDATE ITEMS MANAGEMENT SYSTEM! ==========\n");
        printf("Please Follow The Instruction!\n\n");
        printf("Input Items ID You Want To Update! : ");
        scanf("%d", &idBarangTarget);

        int found = 0;

        while (fscanf(Project, "Code ID       : %d\n", &barang.idBarang) == 1)
        {
            fscanf(Project, "Name Of Goods : %[^\n]\n", barang.namaBarang);
            fscanf(Project, "Types Of Goods: %[^\n]\n", barang.jenisBarang);
            fscanf(Project, "Goods Stock   : %d\n", &barang.stokBarang);
            fscanf(Project, "Item Price    : %d\n", &barang.hargaBarang);

            if (barang.idBarang == idBarangTarget)
            {
                found = 1;
                printf("Items Information You Want To Update\n");
                printf("Items ID       : %d\n", barang.idBarang);
                printf("Name Of Goods  : %s\n", barang.namaBarang);
                printf("Types Of Goods : %s\n", barang.jenisBarang);
                printf("Stock Of Goods : %d\n", barang.stokBarang);
                printf("Item Price     : %d\n\n", barang.hargaBarang);
            }
            else
            {
                fprintf(temp, "Code ID       : %d\n", barang.idBarang);
                fprintf(temp, "Name Of Goods : %s\n", barang.namaBarang);
                fprintf(temp, "Types Of Goods: %s\n", barang.jenisBarang);
                fprintf(temp, "Goods Stock   : %d\n", barang.stokBarang);
                fprintf(temp, "Item Price    : %d\n\n", barang.hargaBarang);
            }
        }

        fclose(Project);
        fclose(temp);

        remove("D:\\Items Information.txt");
        rename("D:\\Temporary.txt", "D:\\Items Information.txt");

        if (!found)
        {
            printf("\nCode ID %d Not Found!!\n", idBarangTarget);
            char updateLagi;
        pesan:
            printf("Do You Want To Use This Update Menu Again? (Y / N) : ");
            scanf(" %c", &updateLagi);

            if (updateLagi == 'y' || updateLagi == 'Y')
            {
                updateStokBarang();
            }
            else if (updateLagi == 'n' || updateLagi == 'N')
            {
                printf("Back To Inventory Menu\n");
                printf("Loading");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    Sleep(500);
                }
                menuManajementInventaris();
            }
            else
            {
                printf("Input Invalid!\n");
                goto pesan;
            }
        }
        updateStokBarangNext();
    pesan1:
        char apaan;
        printf("Do You Want To Use This Update Menu Again? (Y / N) : ");
        scanf(" %c", &apaan);

        if (apaan == 'y' || apaan == 'Y')
        {
            updateStokBarang();
        }
        else if (apaan == 'n' || apaan == 'N')
        {
            printf("Back To Inventory Menu\n");
            printf("Loading");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                Sleep(500);
            }
            menuManajementInventaris();
        }
        else
        {
            printf("Input Invalid!\n");
            goto pesan1;
        }
    }
}

void updateStokBarangNext()
{
    FILE *Project = fopen("D:\\Items Information.txt", "a+");
    if (Project == NULL)
    {
        printf("Error Opening FIle!\n");
        exit(0);
    }
    else
    {
        struct informasiBarang barang;

        printf("Input New Items Information!\n");
        printf("Input ID Items       : ");
        scanf("%d", &barang.idBarang);

        while (getchar() != '\n')
            ;

        printf("Input Name Of Goods  : ");
        fgets(barang.namaBarang, sizeof(barang.namaBarang), stdin);
        barang.namaBarang[strcspn(barang.namaBarang, "\n")] = '\0';

        printf("Input Types Of Goods : ");
        fgets(barang.jenisBarang, sizeof(barang.jenisBarang), stdin);
        barang.jenisBarang[strcspn(barang.jenisBarang, "\n")] = '\0';

        printf("Input Goods Stock    : ");
        scanf("%d", &barang.stokBarang);

        while (getchar() != '\n')
            ;

        printf("Input Item Price     : ");
        scanf("%d", &barang.hargaBarang);

        while (getchar() != '\n')
            ;

        printf("\n");

        dataBaseTulisBarang(Project, &barang);
    }
    fclose(Project);
}

void displayBarang()
{
    FILE *Project = fopen("D:\\Items Information.txt", "r");
    if (Project == NULL)
    {
        printf("Error Opening File!\n");
        exit(0);
    }
    else
    {
        system("cls");
        printf("========== WELCOME TO LIST OF ITEMS ========\n");
        printf("============================================\n");

        struct informasiBarang barang;
        int kosong = 1;

        while (fscanf(Project, "Code ID       : %d\n", &barang.idBarang) == 1)
        {
            kosong = 0;
            fscanf(Project, "Name Of Goods : %[^\n]\n", barang.namaBarang);
            fscanf(Project, "Types Of Goods: %[^\n]\n", barang.jenisBarang);
            fscanf(Project, "Goods Stock   : %d\n", &barang.stokBarang);
            fscanf(Project, "Item Price    : %d\n", &barang.hargaBarang);

            printf("Items ID       : %d\n", barang.idBarang);
            printf("Name Of Goods  : %s\n", barang.namaBarang);
            printf("Types Of Goods : %s\n", barang.jenisBarang);
            printf("Goods Stock    : %d\n", barang.stokBarang);
            printf("Item Price     : %d\n\n", barang.hargaBarang);
        }

        if (kosong)
        {
            printf("\nThere Is No Items Has Registered!\n");
        }

        fclose(Project);
    }
failedUseMenu:
    char pakaiMenu;
    printf("\nDo You Want Go Back To Inventory Menu? (Y / N) : ");
    scanf(" %c", &pakaiMenu);

    if (pakaiMenu == 'y' || pakaiMenu == 'Y')
    {
        menuManajementInventaris();
    }
    else if (pakaiMenu == 'n' || pakaiMenu == 'N')
    {
        displayBarang();
    }
    else
    {
        printf("Invalid Input!\n");
        goto failedUseMenu;
    }
}

void hapusBarang()
{
    FILE *project = fopen("D:\\Items Information.txt", "r+");
    if (project == NULL)
    {
        printf("Error opening file\n");
        exit(0);
    }
    else
    {
        int idTarget;
        struct informasiBarang Barang;
        FILE *tempFile = fopen("D:\\tempFile.txt", "w");
        if (tempFile == NULL)
        {
            printf("Error creating temporary file\n");
            exit(0);
        }
        system("cls");
        printf("========== WELCOME TO DELETE ITEMS MANAJEMENT ! ==========\n");
        printf("============= PLEASE FOLLOW THE MENU BELOW ! =============\n");
        printf("\n");
        printf("Input ID Items You Want To Delete : ");
        scanf("%d", &idTarget);

        int found = 0;

        while (fscanf(project, "Code ID          : %d\n", &Barang.idBarang) == 1)
        {
            fscanf(project, "Name Of Goods    : %[^\n]\n", Barang.namaBarang);
            fscanf(project, "Types Of Goods   : %[^\n]\n", Barang.jenisBarang);
            fscanf(project, "Goods Stock      : %d\n", &Barang.stokBarang);
            fscanf(project, "Item Price       : %d\n", &Barang.hargaBarang);

            if (Barang.idBarang == idTarget)
            {
                found = 1;
                printf("ID FOUND!\n");
                printf("Code ID        : %d\n", Barang.idBarang);
                printf("Name Of Goods  : %s\n", Barang.namaBarang);
                printf("Types Of Goods : %s\n", Barang.jenisBarang);
                printf("Goods Stock    : %d\n", Barang.stokBarang);
                printf("Item Price     : %d\n", Barang.hargaBarang);
                printf("\nThis Item Successfully Delete!\n\n");
            }
            else
            {
                fprintf(tempFile, "Code ID       : %d\n", Barang.idBarang);
                fprintf(tempFile, "Name Of Goods : %s\n", Barang.namaBarang);
                fprintf(tempFile, "Types Of Goods: %s\n", Barang.jenisBarang);
                fprintf(tempFile, "Goods Stock   : %d\n", Barang.stokBarang);
                fprintf(tempFile, "Item Price    : %d\n\n", Barang.hargaBarang);
            }
        }
        fclose(project);
        fclose(tempFile);
        remove("D:\\Items Information.txt");
        rename("D:\\tempFile.txt", "D:\\Items Information.txt");

        if (!found)
        {
            printf("\nCode ID %d Not Found!!\n", idTarget);
        }
    }

pesan1:
    char pakaiMenu;
    printf("Do You Want To Use This Menu Again? (Y / N) : ");
    scanf(" %c", &pakaiMenu);

    if (pakaiMenu == 'y' || pakaiMenu == 'Y')
    {
        hapusBarang();
    }
    else if (pakaiMenu == 'n' || pakaiMenu == 'N')
    {
        printf("Back To Inventory Menu\n");
        printf("Loading");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(500);
        }
        menuManajementInventaris();
    }
    else
    {
        printf("Invalid Input!\n");
        goto pesan1;
    }
}