#pragma once

typedef struct {
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    char email[20];
} Contact;

typedef struct {
    int lastIndex;
    Contact **contact;
} array;

void clearConsole();

void newPhoneBook(array *contacts);

void freePhoneBook(const array *contacts);

void printContact(Contact* contact);

void addContact(array *contacts, const Contact *contact);

void removeContact(array *contacts);

void editContact(Contact *contact);