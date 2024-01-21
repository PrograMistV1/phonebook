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

/**
 * saving contacts to file
 */
void saveContactsToFile(const PhoneBook *phoneBook);

/**
 * loading contacts from file
 */
void loadContactsFromFile(PhoneBook *phoneBook);

void clearConsole();

/**
 * initializing a new contact book
 */
void newPhoneBook(PhoneBook *contacts);

/**
 * releasing allocated memory
 */
void freePhoneBook(const PhoneBook *contacts);

/**
 * displaying a contact to the console
 */
void printContact(const Contact* contact);

/**
 * adding a contact to a book
 */
void addContact(PhoneBook *contacts, const Contact *contact);

/**
 * deleting a contact from a book
 */
void removeContact(PhoneBook *contacts);

/**
 * editing a contact from a book
 */
void editContact(Contact *contact);