#include "phoneBook.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void saveContactsToFile(const PhoneBook *phoneBook) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path)); //getting the path to the executable file

    strcat(path, "/contacts.dat"); //specify the name of the file to save data

    FILE *file = fopen(path, "wb"); //open the file
    if (!file) {
        perror("Error opening file");
        return;
    }
    /**
     * we write down the number of contacts in the book,
     * this is necessary so that when loading from a file we can read the same number of contacts
    */
    fwrite(&phoneBook->lastIndex, sizeof(int), 1, file);


    for (int i = 0; i <= phoneBook->lastIndex; ++i) {
        fwrite(phoneBook->contact[i], sizeof(Contact), 1, file); //write contacts to a file
    }

    fclose(file); //close the file
}

void loadContactsFromFile(PhoneBook *phoneBook) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path)); //getting the path to the executable file

    strcat(path, "/contacts.dat"); //specify the name of the file to save data

    FILE *file = fopen(path, "rb"); //open the file

    if(file == NULL) {
        return;
    }

    int count;
    fread(&count, sizeof(int), 1, file); //get the number of saved contacts

    for (int i = 0; i <= count; ++i) {
        Contact contact = {};
        fread(&contact, sizeof(Contact), 1, file); //getting contacts
        addContact(phoneBook, &contact);
    }
    fclose(file); //close file
}

void newPhoneBook(PhoneBook* contacts) {
    contacts->lastIndex = -1;
    contacts->contact = malloc(sizeof(Contact *) * 0);
}

void freePhoneBook(const PhoneBook* contacts) {
    for (int i = 0; i < contacts->lastIndex; ++i) {
        free(contacts->contact[i]);
    }
    free(contacts->contact);
    printf("memory released\n");
}

void printContact(const Contact* contact) {
    printf("First Name: %s\n", contact->firstName);
    printf("Last Name: %s\n", contact->lastName);
    printf("Phone Number: %s\n", contact->phoneNumber);
    printf("Email: %s\n", contact->email);

    printf("\n");
}

void addContact(PhoneBook* contacts, const Contact* contact) {
    contacts->lastIndex++;
    contacts->contact = realloc(contacts->contact, sizeof(Contact *) * (contacts->lastIndex + 1));

    contacts->contact[contacts->lastIndex] = malloc(sizeof(Contact));
    *contacts->contact[contacts->lastIndex] = *contact;
    saveContactsToFile(contacts);
}

void removeContact(PhoneBook* contacts) {
    printf("index: $ ");
    char dirtyIndex[20], *end;
    fgets(dirtyIndex, sizeof(dirtyIndex), stdin);
    dirtyIndex[strcspn(dirtyIndex, "\n")] = '\0';

    const int index = strtol(dirtyIndex, &end, 10);

    if (dirtyIndex == end || *end != '\0') {
        printf("Index must be a number\n");
        return;
    }

    if (index < 0 || index > contacts->lastIndex) {
        printf("Invalid index\n");
        return;
    }

    free(contacts->contact[index]);

    for (int i = index; i < contacts->lastIndex; ++i) {
        contacts->contact[i] = contacts->contact[i + 1];
    }

    contacts->lastIndex--;
    contacts->contact = realloc(contacts->contact, sizeof(Contact *) * (contacts->lastIndex + 1));

    saveContactsToFile(contacts);

    clearConsole();
    printf("Contact deleted\n");
}


void editContact(Contact* contact) {
    printContact(contact);

    printf("first name: ");
    fgets(contact->firstName, sizeof(contact->firstName), stdin);
    contact->firstName[strcspn(contact->firstName, "\n")] = '\0';
    clearConsole();
    printContact(contact);

    printf("last name: ");
    fgets(contact->lastName, sizeof(contact->lastName), stdin);
    contact->lastName[strcspn(contact->lastName, "\n")] = '\0';
    clearConsole();
    printContact(contact);

    printf("phone number: ");
    fgets(contact->phoneNumber, sizeof(contact->phoneNumber), stdin);
    contact->phoneNumber[strcspn(contact->phoneNumber, "\n")] = '\0';
    clearConsole();
    printContact(contact);

    printf("email: ");
    fgets(contact->email, sizeof(contact->email), stdin);
    contact->email[strcspn(contact->email, "\n")] = '\0';
    clearConsole();
    printContact(contact);
}
