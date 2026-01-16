#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

void addContact() {
    struct Contact c;
    FILE *fp = fopen("contacts.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", c.phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", c.email);

    fprintf(fp, "%s,%s,%s\n", c.name, c.phone, c.email);
    fclose(fp);
    printf("Contact saved successfully!\n");
}

void viewContacts() {
    struct Contact c;
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp) {
        printf("No contacts found!\n");
        return;
    }
    printf("\n---- Contact List ----\n");
    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n----------------------\n", c.name, c.phone, c.email);
    }
    fclose(fp);
}

void searchContact() {
    char searchName[50];
    struct Contact c;
    int found = 0;
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp) {
        printf("No contacts found!\n");
        return;
    }
    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strcasecmp(c.name, searchName) == 0) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }
    if (!found) printf("Contact not found!\n");
    fclose(fp);
}

void deleteContact() {
    char deleteName[50];
    struct Contact c;
    int found = 0;
    FILE *fp = fopen("contacts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name to delete: ");
    scanf(" %[^\n]", deleteName);

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strcasecmp(c.name, deleteName) != 0) {
            fprintf(temp, "%s,%s,%s\n", c.name, c.phone, c.email);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        printf("Contact deleted successfully!\n");
    else
        printf("Contact not found!\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Contact Book ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

