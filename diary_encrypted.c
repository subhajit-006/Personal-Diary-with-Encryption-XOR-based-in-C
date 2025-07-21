#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "diary.dat"
#define MAX_ENTRY 1024
#define KEY 0xAA // simple XOR key

void encrypt_decrypt(char *data) {
    for (int i = 0; data[i]; i++) {
        data[i] ^= KEY;
    }
}

void write_entry() {
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) {
        perror("File open error");
        return;
    }

    char entry[MAX_ENTRY];
    getchar(); // clear newline
    printf("Write your diary entry: ");
    fgets(entry, sizeof(entry), stdin);
    entry[strcspn(entry, "\n")] = '\0';

    encrypt_decrypt(entry);
    fwrite(entry, sizeof(char), strlen(entry), fp);
    fputc('\n', fp);
    fclose(fp);
    printf("Diary entry saved (encrypted).\n");
}

void read_entries() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("File open error");
        return;
    }

    char buffer[MAX_ENTRY];
    printf("\n--- Diary Entries (Decrypted) ---\n");
    while (fgets(buffer, sizeof(buffer), fp)) {
        encrypt_decrypt(buffer);
        printf("- %s", buffer);
    }
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Personal Diary ---\n");
        printf("1. Write Entry\n");
        printf("2. View Entries\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: write_entry(); break;
            case 2: read_entries(); break;
            case 3: exit(0);
            default: printf("Invalid option.\n");
        }
    }

    return 0;
}
