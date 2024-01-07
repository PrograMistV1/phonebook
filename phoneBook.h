#pragma once

#ifdef _WIN32
#include <limits.h>
#elif __linux__
#include <linux/limits.h>
#else
#error "Unsupported operating system"
#endif

typedef struct {
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    char email[20];
} Contact;

typedef struct {
    int lastIndex;
    Contact **contact;
} PhoneBook;

void saveContactsToFile(const PhoneBook *phoneBook);

void loadContactsFromFile(PhoneBook *phoneBook);

void clearConsole();

void newPhoneBook(PhoneBook *contacts);

void freePhoneBook(const PhoneBook *contacts);

void printContact(Contact* contact);

void addContact(PhoneBook *contacts, const Contact *contact);

void removeContact(PhoneBook *contacts);

void editContact(Contact *contact);