#include "phoneBook.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void newPhoneBook(array* contacts) {
    contacts->lastIndex = -1;
    contacts->contact = malloc(sizeof(Contact *) * 0);
}

void freePhoneBook(const array* contacts) {
    for (int i = 0; i < contacts->lastIndex; ++i) {
        free(contacts->contact[i]);
    }
    free(contacts->contact);
    printf("memory released\n");
}

void printContact(Contact* contact) {
    printf("First Name: %s\n", contact->firstName);
    printf("Last Name: %s\n", contact->lastName);
    printf("Phone Number: %s\n", contact->phoneNumber);
    printf("Email: %s\n", contact->email);

    printf("\n");
}

void addContact(array* contacts, const Contact* contact) {
    contacts->lastIndex++;
    contacts->contact = realloc(contacts->contact, sizeof(Contact *) * (contacts->lastIndex + 1));

    contacts->contact[contacts->lastIndex] = malloc(sizeof(Contact));
    *contacts->contact[contacts->lastIndex] = *contact;
}

void removeContact(array* contacts) {
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
