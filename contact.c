/*   Rahul chaudhary   26005_216   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>


//list contacts

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
   switch(sortCriteria)
   {
    case 1:
         printf("Sorting by the name\n");
         for(int i=0;i<addressBook->contactCount-1;i++)
         {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
         }
         break;
    case 2:
         printf("Sorting by the phone\n");
         for(int i=0;i<addressBook->contactCount-1;i++)
         {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
         }
         break;
    case 3:
         printf("Sorting by the email\n");
         for(int i=0;i<addressBook->contactCount-1;i++)
         {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
         }
         break;
    default:
    printf("Invalid sort criteria!\n");     
   }
   // Print border line
   {
    printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
    printf("│ INDEX │ NAME                 │ PHONE                 │ EMAIL                                │\n");
    printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
   }
   for(int i=0;i<addressBook->contactCount;i++)
   printf("│ %-5d │ %-20s │ %-21s │ %-36s │\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  
    // Closing border line
    printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
}
   


//contact initialize
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    if (!loadContactsFromFile(addressBook)) 
    {
        saveContactsToFile(addressBook);  
    }
}




//contact save and exit
void saveAndExit(AddressBook *addressBook) 
{
    if (saveContactsToFile(addressBook)) 
    {
        printf("Contacts saved successfully.\n");
    }
    else 
    {
        printf("Failed to save contacts.\n");
    }
    exit(EXIT_SUCCESS);
}




//contact create
void createContact(AddressBook*addressBook)
{
    char name[50];        
    char phone[20];
    char email[50];
    int ret;
    do
    {
        printf("Enter the name:\n");
        scanf(" %[^\n]",name);
        ret = validatename(name,addressBook);
    }while(!ret);
    do
    {
        printf("Enter the phone:\n");
        scanf(" %[^\n]",phone);
        ret = validatephone(phone,addressBook);
    }while(!ret);
    do
    {
        printf("Enter the email:\n");
        scanf(" %[^\n]",email);
        ret = validateemail(email,addressBook);
    }while(!ret);
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;
    {
    printf("Contact added successfully!\n");
    saveContactsToFile(addressBook);

    }
}





//search contacts
void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void searchContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available to search.\n");
        return;
    }

    int choice;
    char query[100];

    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); 

    if (choice == 4) {
        printf("Search cancelled.\n");
        return;
    }

    if (choice < 1 || choice > 3) {
        printf("Invalid choice!\n");
        return;
    }

    while (1) {
        printf("Enter search query (or type 'exit' to cancel): ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = '\0'; 

        if (strcasecmp(query, "exit") == 0) {
            printf("Search cancelled.\n");
            break;
        }

        char queryLower[100];
        strcpy(queryLower, query);
        toLowerCase(queryLower);

        int found = 0;

        // Print table header only if at least one match is found
        for (int i = 0; i < addressBook->contactCount; i++) {
            char field[100];
            switch (choice) {
                case 1: strcpy(field, addressBook->contacts[i].name); break;
                case 2: strcpy(field, addressBook->contacts[i].phone); break;
                case 3: strcpy(field, addressBook->contacts[i].email); break;
            }

            char fieldLower[100];
            strcpy(fieldLower, field);
            toLowerCase(fieldLower);

            if (strstr(fieldLower, queryLower) != NULL) {
                if (!found) 
                //border line
                {     

                    printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
                    printf("│ INDEX │ NAME                 │ PHONE                 │ EMAIL                                │\n");
                    printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
                }
                printf("│ %-5d │ %-20s │ %-21s │ %-36s │\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }

        if (found) 
        {
            printf("|-------|----------------------|-----------------------|--------------------------------------|\n");
            break;
        } 
        else 
        {
            printf("No contact matched your search query. Please try again.\n");
        }
    }
}



//editContact
void editname(AddressBook *addressBook)
{
    char oldname[50];
    char newname[50];

    printf("Enter the name to edit old name : ");
    scanf(" %[^\n]", oldname);

    int found = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, oldname) == 0)
        {
            found = 1;
            printf("Enter the new name : ");
            scanf(" %[^\n]", newname);

            if(!validatename(newname, addressBook))
            {
                printf("ERROR : Invalid name. Name should contain only alphabets, spaces or dots and must have minimum 3 letters.\n");
                return;
            }

            strcpy(addressBook->contacts[i].name, newname);
            printf("Name updated successfully.\n");
            return;
        }
    }

    if(!found)
    {
        printf("ERROR : Contact name not found in contact list.\n");
    }
}

void editphone(AddressBook *addressBook)
{
    char oldphone[50];
    char newphone[50];

    printf("Enter the phone number to edit : ");
    scanf(" %[^\n]", oldphone);

    int found = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, oldphone) == 0)
        {
            found = 1;
            printf("Enter the new phone number : ");
            scanf(" %[^\n]", newphone);

            if(!validatephone(newphone, addressBook))
            {
                printf("ERROR : Invalid phone number. Phone number must contain exactly 10 digits.\n");
                return;
            }

            strcpy(addressBook->contacts[i].phone, newphone);
            printf("Phone number updated successfully.\n");
            return;
        }
    }

    if(!found)
    {
        printf("ERROR : Contact phone number not found in contact list.\n");
    }
}

void editemail(AddressBook *addressBook)
{
    char oldemail[50];
    char newemail[50];

    printf("Enter the mail ID to edit : ");
    scanf(" %[^\n]", oldemail);

    int found = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, oldemail) == 0)
        {
            found = 1;
            printf("Enter the new mail ID : ");
            scanf(" %[^\n]", newemail);

            if(!validateemail(newemail, addressBook))
            {
                printf("ERROR : Invalid mail ID. Email must end with @gmail.com\n");
                return;
            }

            strcpy(addressBook->contacts[i].email, newemail);
            printf("Mail ID updated successfully.\n");
            return;
        }
    }

    if(!found)
    {
        printf("ERROR : Contact mail ID not found in contact list.\n");
    }
}

void editContact(AddressBook *addressBook)
{
    int choice;
    do
    {
        printf("\nSelect the choice to edit new name : \n");
        printf("1. Name\n2. Phone\n3. Email\n4. Exit\n");
        printf("Enter the choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                editname(addressBook);
                break;
            case 2:
                editphone(addressBook);
                break;
            case 3:
                editemail(addressBook);
                break;
            case 4:
                printf("Exiting from edit menu ---\n");
                break;
            default:
                printf("Enter a valid choice to edit the contact\n");
        }
    } while(choice != 4);
}



// delete parts
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty. Nothing to delete.\n");
        return;
    }

    char searchKey[100];
    int matches[addressBook->contactCount];
    int matchCount;

    /* Clear input buffer if previous input was scanf() */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    while (1)
    {
        printf("\nEnter Name / Phone / Email to delete");
        printf("\n(Type EXIT to cancel): ");

        if (fgets(searchKey, sizeof(searchKey), stdin) == NULL)
            return;

        searchKey[strcspn(searchKey, "\n")] = '\0';

        if (strlen(searchKey) == 0)
        {
            printf("Please enter something.\n");
            continue;
        }

        if (strcasecmp(searchKey, "EXIT") == 0)
        {
            printf("Delete cancelled.\n");
            return;
        }

        matchCount = 0;

        /* Search contacts */
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(addressBook->contacts[i].name, searchKey) == 0 ||
                strcasecmp(addressBook->contacts[i].phone, searchKey) == 0 ||
                strcasecmp(addressBook->contacts[i].email, searchKey) == 0)
            {
                matches[matchCount++] = i;
            }
        }

        if (matchCount == 0)
        {
            printf("Contact not found.\n");
            continue;
        }

        int deleteIndex;

        if (matchCount == 1)
        {
            deleteIndex = matches[0];
        }
        else
        {
            printf("\nMultiple contacts found:\n");

            for (int i = 0; i < matchCount; i++)
            {
                Contact *c = &addressBook->contacts[matches[i]];

                printf("\n%d.\n", i + 1);
                printf("Name  : %s\n", c->name);
                printf("Phone : %s\n", c->phone);
                printf("Email : %s\n", c->email);
            }

            int choice;

            while (1)
            {
                printf("\nEnter contact number (0 to cancel): ");

                if (scanf("%d", &choice) != 1)
                {
                    while (getchar() != '\n');
                    printf("Invalid input.\n");
                    continue;
                }

                while (getchar() != '\n');

                if (choice == 0)
                {
                    printf("Delete cancelled.\n");
                    return;
                }

                if (choice >= 1 && choice <= matchCount)
                {
                    deleteIndex = matches[choice - 1];
                    break;
                }

                printf("Invalid choice.\n");
            }
        }

        Contact *c = &addressBook->contacts[deleteIndex];

        printf("\nSelected Contact\n");
        printf("Name  : %s\n", c->name);
        printf("Phone : %s\n", c->phone);
        printf("Email : %s\n", c->email);

        char confirm;

        while (1)
        {
            printf("\nAre you sure you want to delete? (Y/N): ");

            scanf(" %c", &confirm);
            while (getchar() != '\n');

            if (confirm == 'Y' || confirm == 'y')
            {
                for (int i = deleteIndex; i < addressBook->contactCount - 1; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }

                addressBook->contactCount--;

                saveContactsToFile(addressBook);

                printf("\nContact deleted successfully.\n");
                return;
            }
            else if (confirm == 'N' || confirm == 'n')
            {
                printf("Delete cancelled.\n");
                return;
            }
            else
            {
                printf("Please enter Y or N only.\n");
            }
        }
    }
}




//validtaion name
int validatename(char *name, AddressBook *addressBook)
{
    int len = strlen(name);

    // Minimum length check
    if (len < 3)
    {
        printf("Error: Name must contain at least 3 characters\n");
        return 0;
    }

    // No leading or trailing space
    if (name[0] == ' ' || name[len - 1] == ' ')
    {
        printf("Error: Name should not start or end with space\n");
        return 0;
    }

    // No leading or trailing dot
    if (name[0] == '.' || name[len - 1] == '.')
    {
        printf("Error: Name should not start or end with dot\n");
        return 0;
    }

    // First character must be alphabet
    if (!isalpha(name[0]))
    {
        printf("Error: Name must start with an alphabet\n");
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        // Allow only alphabets, spaces and dots
        if (!(isalpha(name[i]) || name[i] == ' ' || name[i] == '.'))
        {
            printf("Error: Name should contain only alphabets, spaces and dots\n");
            return 0;
        }

        // No consecutive spaces
        if (i > 0 && name[i] == ' ' && name[i - 1] == ' ')
        {
            printf("Error: Multiple consecutive spaces are not allowed\n");
            return 0;
        }

        // No consecutive dots
        if (i > 0 && name[i] == '.' && name[i - 1] == '.')
        {
            printf("Error: Multiple consecutive dots are not allowed\n");
            return 0;
        }

        // No space before or after dot
        if (i > 0)
        {
            if ((name[i] == '.' && name[i - 1] == ' ') ||
                (name[i] == ' ' && name[i - 1] == '.'))
            {
                printf("Error: Space and dot should not be adjacent\n");
                return 0;
            }
        }
    }

    // Duplicate name check
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].name, name) == 0)
        {
            printf("Error: Name already exists. Enter a unique name\n");
            return 0;
        }
    }

    return 1;
}





//validation phone 
int validatephone(char *phone, AddressBook *addressBook) 
{
    //must cheak 10 digits
    int len = strlen(phone);
    if (len != 10) {
        printf("Error: Phone number must contain exactly 10 digits\n");
        return 0;
    }
    //must start 6-9
    if (phone[0] < '6' || phone[0] > '9') 
    {
        printf("Error: First digit must be between 6 and 9\n");
        return 0;
    }
    for (int i = 0; i < len; i++) 
    {
        if (!isdigit(phone[i])) 
        {
            printf("Error: Only digits are allowed in phone number\n");
            return 0;
        }
    }
    for (int j = 0; j < addressBook->contactCount; j++) 
    {
        if (strcmp(addressBook->contacts[j].phone, phone) == 0) 
        {
            printf("Error: Phone number already exists, enter a unique number\n");
            return 0;
        }
    }
    return 1;
}



//validation email
int validateemail(char *email, AddressBook *addressBook) 
{
    int len = strlen(email);
    int atCount = 0;

    //  Allowed characters only
    for (int i = 0; i < len; i++) {
        if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '@' || email[i] == '.')) {
            printf("Error: Email must contain only lowercase letters, digits, '@' and '.'\n");
            return 0;
        }
    }

    //  Cannot start with '.' or '@'
    if (email[0] == '.' || email[0] == '@') {
        printf("Error: Email cannot start with '.' or '@'\n");
        return 0;
    }

    //  Must contain exactly one '@'
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atCount++;
    }
    if (atCount != 1) {
        printf("Error: Email must contain exactly one '@'\n");
        return 0;
    }

    //  '.' must appear after '@'
    char *atPos = strchr(email, '@');
    if (!atPos) return 0;
    char *dotPos = strchr(atPos, '.');
    if (!dotPos) {
        printf("Error: '.' must appear after '@'\n");
        return 0;
    }

    //  At least one character between '@' and '.'
    if (dotPos == atPos + 1) {
        printf("Error: There must be at least one character between '@' and '.'\n");
        return 0;
    }

    //  Must end with ".com" only
    if (strcmp(dotPos, ".com") != 0) {
        printf("Error: Email must end with '.com' and no extra characters\n");
        return 0;
    }

    //  Uniqueness check
    for (int j = 0; j < addressBook->contactCount; j++) {
        if (strcmp(addressBook->contacts[j].email, email) == 0) {
            printf("Error: Email already exists, enter a unique email\n");
            return 0;
        }
    }
    return 1; 
}
