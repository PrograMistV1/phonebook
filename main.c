#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    char email[20];
} Contact;

typedef struct {
    int count;
    Contact **contact;
} array;

void newPhoneBook(array *contacts) {
    contacts->count = 0;
    contacts->contact = malloc(sizeof(Contact*) * 0);
}

void freePhoneBook(const array *contacts) {
    for(int i = 0; i < contacts->count; ++i) {
        free(contacts->contact[i]);
    }
    free(contacts->contact);
    printf("memory released\n");
}

void printContact(Contact *contact) {
    printf("First Name: %s\n", contact->firstName);
    printf("Last Name: %s\n", contact->lastName);
    printf("Phone Number: %s\n", contact->phoneNumber);
    printf("Email: %s\n", contact->email);

    printf("\n");
}

void addContact(array *contacts, const Contact *contact) {
    contacts->contact = realloc(contacts->contact, sizeof(Contact*) * contacts->count + 1);

    contacts->contact[contacts->count] = malloc(sizeof(Contact));
    *contacts->contact[contacts->count] = *contact;
    contacts->count++;
}

void removeContact(array *contacts) {
    printf("index: $ ");
    char dirtyIndex[20], *end;
    fgets(dirtyIndex, sizeof(dirtyIndex), stdin);
    dirtyIndex[strcspn(dirtyIndex, "\n")] = '\0';

    const int index = strtod(dirtyIndex, &end);

    if (dirtyIndex == end || *end != '\0') {
        printf("Index must be a number\n");
        return;
    }

    if(index < 0 || index > contacts->count) {
        printf("Invalid index\n");
        return;
    }

    for(int i = index; i < contacts->count - 1; ++i) {
        *contacts->contact[i] = *contacts->contact[i + 1];
    }

    free(contacts->contact[contacts->count]);
    contacts->count = contacts->count - 1;
    contacts->contact = realloc(contacts->contact, sizeof(Contact*) * contacts->count);

    system("clear");
    printf("Contact deleted\n");
}

void editContact(Contact *contact) {
    printContact(contact);

    printf("first name: ");
    fgets(contact->firstName, sizeof(contact->firstName), stdin);
    contact->firstName[strcspn(contact->firstName, "\n")] = '\0';
    system("clear");
    printContact(contact);

    printf("last name: ");
    fgets(contact->lastName, sizeof(contact->lastName), stdin);
    contact->lastName[strcspn(contact->lastName, "\n")] = '\0';
    system("clear");
    printContact(contact);

    printf("phone number: ");
    fgets(contact->phoneNumber, sizeof(contact->phoneNumber), stdin);
    contact->phoneNumber[strcspn(contact->phoneNumber, "\n")] = '\0';
    system("clear");
    printContact(contact);

    printf("email: ");
    fgets(contact->email, sizeof(contact->email), stdin);
    contact->email[strcspn(contact->email, "\n")] = '\0';
    system("clear");
    printContact(contact);
}

int main() {
    array contactList;
    newPhoneBook(&contactList);

    system("clear");

    bool exit = false;
    while(!exit) {
        char command[20];
        printf("command: $ ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        system("clear");

        if (strcmp(command, "list") == 0) {
            if(contactList.count == 0) {
                printf("Book is empty\n");
            }else {
                for (int i = 0; i < contactList.count; ++i) {
                    printf("===== %d =====\n", i);
                    printContact(contactList.contact[i]);
                }
            }
        }

        if (strcmp(command, "create") == 0) {
            Contact contact = {};
            editContact(&contact);
            addContact(&contactList, &contact);
        }

        if (strcmp(command, "remove") == 0) {
            if(contactList.count == 0) {
                printf("Book is empty\n");
                continue;
            }
            removeContact(&contactList);
        }

        if (strcmp(command, "edit") == 0) {
            printf("index: $ ");
            char dirtyIndex[20], *end;
            fgets(dirtyIndex, sizeof(dirtyIndex), stdin);
            dirtyIndex[strcspn(dirtyIndex, "\n")] = '\0';

            const int index = strtod(dirtyIndex, &end);

            if (dirtyIndex == end || *end != '\0') {
                printf("Index must be a number\n");
                continue;
            }

            if(index < 0 || index > contactList.count) {
                printf("Invalid index\n");
                continue;
            }

            system("clear");

            editContact(contactList.contact[index]);
        }

        if (strcmp(command, "exit") == 0) {
            printf("shutdown...\n");
            exit = true;
        }
    }

    freePhoneBook(&contactList);
    return 0;
}