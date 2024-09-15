#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount
{
    int accountNumber;
    char accountHolder[50];
    float balance;
};

// Fungsi untuk menampilkan informasi akun bank
void displayAccount(struct BankAccount account)
{
    printf("Nomor Akun: %d\n", account.accountNumber);
    printf("Pemilik Akun: %s\n", account.accountHolder);
    printf("Saldo: $%.2f\n", account.balance);
}

// Fungsi untuk menulis akun ke dalam file
void writeAccountToFile(struct BankAccount account)
{
    FILE *file = fopen("bank_accounts.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d;%s;%.2f\n", account.accountNumber, account.accountHolder, account.balance);
        fclose(file);
    }
    else
    {
        printf("Gagal membuka file.\n");
    }
}

// Fungsi untuk membaca semua akun dari file
void readAllAccountsFromFile()
{
    FILE *file = fopen("bank_accounts.txt", "r");
    if (file != NULL)
    {
        struct BankAccount account;

        while (fscanf(file, "%d;%[^;];%f\n", &account.accountNumber, account.accountHolder, &account.balance) == 3)
        {
            displayAccount(account);
            printf("\n");
        }

        fclose(file);
    }
    else
    {
        printf("Gagal membuka file.\n");
    }
}

// Fungsi untuk mencari akun berdasarkan nomor akun
struct BankAccount findAccountByNumber(int accountNumber)
{
    FILE *file = fopen("bank_accounts.txt", "r");
    struct BankAccount account;
    account.accountNumber = -1; // Inisialisasi dengan nilai yang tidak mungkin ditemukan

    if (file != NULL)
    {
        while (fscanf(file, "%d;%[^;];%f\n", &account.accountNumber, account.accountHolder, &account.balance) == 3)
        {
            if (account.accountNumber == accountNumber)
            {
                fclose(file);
                return account;
            }
        }

        fclose(file);
    }
    else
    {
        printf("Gagal membuka file.\n");
    }

    return account; // Mengembalikan akun dengan accountNumber -1 jika tidak ditemukan
}

// Fungsi untuk memperbarui saldo akun
void updateAccountBalance(int accountNumber, float newBalance)
{
    FILE *file = fopen("bank_accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL)
    {
        struct BankAccount account;

        while (fscanf(file, "%d;%[^;];%f\n", &account.accountNumber, account.accountHolder, &account.balance) == 3)
        {
            if (account.accountNumber == accountNumber)
            {
                account.balance = newBalance;
            }
            fprintf(tempFile, "%d;%s;%.2f\n", account.accountNumber, account.accountHolder, account.balance);
        }

        fclose(file);
        fclose(tempFile);

        remove("bank_accounts.txt");
        rename("temp.txt", "bank_accounts.txt");
    }
    else
    {
        printf("Gagal membuka file.\n");
    }
}

// Fungsi untuk menghapus akun berdasarkan nomor akun
void deleteAccount(int accountNumber)
{
    FILE *file = fopen("bank_accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file != NULL && tempFile != NULL)
    {
        struct BankAccount account;

        while (fscanf(file, "%d;%[^;];%f\n", &account.accountNumber, account.accountHolder, &account.balance) == 3)
        {
            if (account.accountNumber != accountNumber)
            {
                fprintf(tempFile, "%d;%s;%.2f\n", account.accountNumber, account.accountHolder, account.balance);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("bank_accounts.txt");
        rename("temp.txt", "bank_accounts.txt");
    }
    else
    {
        printf("Gagal membuka file.\n");
    }
}

int main()
{
    int choice;
    int accountNumber;
    float amount;

    do
    {
        printf("\nMenu:\n");
        printf("1. Tambah Akun\n");
        printf("2. Lihat Semua Akun\n");
        printf("3. Lihat Akun Berdasarkan Nomor Akun\n");
        printf("4. Update Saldo Akun\n");
        printf("5. Hapus Akun\n");
        printf("0. Keluar\n");
        printf("Pilih operasi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Masukkan nomor akun baru: ");
            scanf("%d", &accountNumber);
            struct BankAccount newAccount;
            newAccount.accountNumber = accountNumber;
            printf("Masukkan nama pemilik akun: ");
            scanf("%s", newAccount.accountHolder);
            printf("Masukkan saldo awal: ");
            scanf("%f", &newAccount.balance);
            writeAccountToFile(newAccount);
            break;
        case 2:
            printf("Daftar Semua Akun:\n");
            readAllAccountsFromFile();
            break;
        case 3:
            printf("Masukkan nomor akun yang ingin dilihat: ");
            scanf("%d", &accountNumber);
            struct BankAccount foundAccount = findAccountByNumber(accountNumber);
            if (foundAccount.accountNumber != -1)
            {
                printf("Informasi Akun:\n");
                displayAccount(foundAccount);
            }
            else
            {
                printf("Akun tidak ditemukan.\n");
            }
            break;
        case 4:
            printf("Masukkan nomor akun yang ingin diperbarui: ");
            scanf("%d", &accountNumber);
            printf("Masukkan saldo baru: ");
            scanf("%f", &amount);
            updateAccountBalance(accountNumber, amount);
            break;
        case 5:
            printf("Masukkan nomor akun yang ingin dihapus: ");
            scanf("%d", &accountNumber);
            deleteAccount(accountNumber);
            break;
        case 0:
            printf("Program selesai.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
        }

    } while (choice != 0);

    return 0;
}
