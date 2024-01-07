#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "phoneBook.h"




int main() {
    PhoneBook contactList;
    newPhoneBook(&contactList);

    loadContactsFromFile(&contactList);

    clearConsole();

    bool exit = false;
    while(!exit) {
        char command[20];
        printf("command: $ ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        clearConsole();

        if (strcmp(command, "list") == 0) {
            if(contactList.lastIndex == -1) {
                printf("Book is empty\n");
            }else {
                for (int i = 0; i <= contactList.lastIndex; ++i) {
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
            if(contactList.lastIndex == -1) {
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

            if(index < 0 || index > contactList.lastIndex) {
                printf("Invalid index\n");
                continue;
            }

            clearConsole();

            editContact(contactList.contact[index]);
            saveContactsToFile(&contactList);
        }

        if (strcmp(command, "exit") == 0) {
            printf("shutdown...\n");
            exit = true;
        }
    }

    freePhoneBook(&contactList);
    return 0;
}