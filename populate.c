#include "contact.h"
// Dummy contact data

static Contact dummyContacts[] = 
{
    {"Bob Johnson", "9753222336", "bob@company.com"},
    {"Carol White", "8655566665", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "9334445555", "frank@example.com"},
    {"Grace Wilson", "8923334444", "grace@example.com"},
    {"Hannah Clark", "8556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"},
    {"Rahul", "8882864433", "newrahul@gmail.com"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i) 
    {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }
}