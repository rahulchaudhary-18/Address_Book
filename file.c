#include <stdio.h>
#include "file.h"

int saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.dat", "wb");
    if (!fp) return 0;
    fwrite(addressBook->contacts, sizeof(Contact), addressBook->contactCount, fp);
    fclose(fp);
    return 1;
}


int loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.dat", "rb");
    if (!fp) return 0;
    addressBook->contactCount = fread(addressBook->contacts, sizeof(Contact), MAX_CONTACTS, fp);
    fclose(fp);
    return (addressBook->contactCount > 0);
}
