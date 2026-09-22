#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("┌───────────────────────────────────┐\n");
        printf("│         Address Book Menu         │\n");
        printf("├───────────────────────────────────┤\n");
        printf("│ 1. Create Contact                 │\n");
        printf("│ 2. Search Contact                 │\n");
        printf("│ 3. Edit Contact                   │\n");
        printf("│ 4. Delete Contact                 │\n");
        printf("│ 5. List All Contacts              │\n");
        printf("│ 6. Exit                           │\n");
        printf("└───────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
