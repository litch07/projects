#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

bool isRunning = true;

void Menu()
{
    printf("\n\t **** Contact Management System ****\n");
    printf("\n\t\t\tMAIN MENU\n");
    printf("\t\t=====================\n");
    printf("\t\t[1] Add a new Contact\n");
    printf("\t\t[2] Show all Contacts\n");
    printf("\t\t[3] Search for contact\n");
    printf("\t\t[4] Edit a Contact\n");
    printf("\t\t[5] Delete a Contact\n");
    printf("\t\t[6] Delete All Contact\n");
    printf("\t\t[i] User Guideline\n");
    printf("\t\t[a] About Us\n");
    printf("\t\t[0] Exit\n\t\t=================\n\t\t");
    printf("Wrong choice will restart the program automatically\n\t\tEnter your choice:");
}

void p_line_space(char *Name, char ContactInfo)
{
    int i;
    int len = strlen(Name);

    if(Name[len-1] == '\n') {
        Name[len-1] = '\0';
        len--;
    }

    int TotalSpace = 0;
    if(ContactInfo == 'e')
        TotalSpace = 30 - len;
    else
        TotalSpace = 20 - len;

    if(TotalSpace < 0) TotalSpace = 0;

    printf("|%s", Name);
    for(i = 0; i < TotalSpace; i++)
        printf(" ");

    if(ContactInfo == 'e')
    {
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

bool exists(char *GivenLine, char ContactInfo)
{
    char Buffer[300];
    char Wanted[300];

    strcpy(Wanted, GivenLine);
    strcat(Wanted, "\n");

    int targetLine = 0;
    if(ContactInfo=='n') targetLine = 1;
    if(ContactInfo=='p') targetLine = 2;
    if(ContactInfo=='e') targetLine = 3;

    FILE *fp = fopen("All-Contact.txt", "r");
    if(fp == NULL)
        return false;

    int LineCount = 0;
    while(fgets(Buffer, 300, fp))
    {
        LineCount++;

        if(LineCount == targetLine)
        {
            if(strcmp(Buffer, Wanted) == 0)
            {
                fclose(fp);
                return true;
            }
        }

        if(LineCount == 3)
            LineCount = 0;
    }

    fclose(fp);
    return false;
}


void restart()
{
    system("cls");
}

void Exit()
{
    getchar();
    printf("Are You Sure Want to Exit? (Y,N): ");
    char choice;
    scanf("%c", &choice);
    if(choice == 'Y' || choice == 'y')
    {
        system("cls");
        char uwu[100] = "\t\t\t\tArigato <3\n\n\n\n\t\t\t   ..... UwU >_< .....";
        for(int i = 0; i < strlen(uwu); i++)
        {
            printf("%c", uwu[i]);
            Sleep(40);
        }
        printf("\n\n\n");
        isRunning = false;
    }
    else
    {
        restart();
    }
}

void GoBackOrExit()
{
    char option;
    getchar();
    printf("Go Back(b)? or Exit(0)? ");
    scanf("%c", &option);
    if(option == '0')
    {
        Exit();
    }
    else
    {
        system("cls");
    }
}

void add()
{
    system("cls");
    printf("\n\t\t **** Add new Contact ****\n\n");

    char Name[50];
    char Phone[50];
    char Email[100];

    printf("Enter The Name: ");
    scanf(" %[^\n]s", Name);

    if(strlen(Name) > 20) { restart(); return; }
    if(exists(Name, 'n')) { restart(); return; }

    printf("Enter The Phone Number: ");
    scanf(" %s", Phone);

    if(strlen(Phone) > 20) { restart(); return; }
    if(exists(Phone, 'p')) { restart(); return; }

    printf("Enter The Email: ");
    scanf(" %s", Email);

    if(strlen(Email) > 30) { restart(); return; }
    if(exists(Email, 'e')) { restart(); return; }

    FILE *fp = fopen("All-Contact.txt", "a");
    fprintf(fp, "%s\n%s\n%s\n", Name, Phone, Email);
    fclose(fp);

    printf("\nContact Added Successfully!\n");
    GoBackOrExit();
}

void show()
{
    system("cls");
    printf("\n\t\t **** All Contacts ****\n\n");
    FILE* AllContactTextFile;
    int LineLength = 300;
    char Line[LineLength];

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    if(AllContactTextFile == NULL)
    {
        printf("\nNo contacts found!\n");
        GoBackOrExit();
        return;
    }
    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactTextFile))
    {
        LineCount++;
        if(LineCount == 1)
        {
            p_line_space(Line, 'n');
        }
        else if(LineCount == 2)
        {
            p_line_space(Line, 'p');
        }
        else if(LineCount == 3)
        {
            p_line_space(Line, 'e');
            LineCount = 0;
            TotalContact++;
        }
    }
    printf("You Have Total %d Contacts.\n\n", TotalContact);
    fclose(AllContactTextFile);
    GoBackOrExit();
}

void search()
{
    system("cls");
    printf("\n\t\t **** Search a Contact ****\n\n");

    char Name[100];
    printf("Enter The Name: ");
    scanf(" %[^\n]s", Name);

    FILE *fp = fopen("All-Contact.txt", "r");
    if(fp == NULL)
    {
        printf("No contacts found!\n");
        GoBackOrExit();
        return;
    }

    char line[300];
    char stored[100];
    char storedPhone[100];
    char storedEmail[100];

    int found = 0;
    int state = 0;

    while(fgets(line, 300, fp))
    {
        state++;

        if(state == 1) strcpy(stored, line);
        if(state == 2) strcpy(storedPhone, line);
        if(state == 3) {
            strcpy(storedEmail, line);

            char temp[200];
            strcpy(temp, Name);
            strcat(temp, "\n");

            if(strcmp(stored, temp) == 0)
            {
                found = 1;
                printf("\nContact Found:\n");
                printf("Name : %s", stored);
                printf("Phone: %s", storedPhone);
                printf("Email: %s\n", storedEmail);
            }

            state = 0;
        }
    }

    fclose(fp);

    if(!found)
        printf("\nSorry, no contact found for '%s'\n", Name);

    GoBackOrExit();
}

void edit()
{
    system("cls");
    printf("\n\t\t\t\t\t**** Edit a Contact ****\n\n");

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;
    printf("\t   **If you do not use unique name,number,and email while editing the program will restart**\n\n\n");
    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s", GivenName);
    if(strlen(GivenName) > 20)
    {
        restart();
        return;
    }

    strcat(GivenName, "\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLength = 255;
    char Line[LineLength];
    OurExistingFile = fopen("All-Contact.txt", "r");
    if(OurExistingFile == NULL)
    {
        printf("\nNo contacts found!\n");
        GoBackOrExit();
        return;
    }
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Line, LineLength, OurExistingFile))
    {
        LineCount++;

        if(LineCount == 1 && strcmp(GivenName, Line) == 0)
        {
            FoundContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0)
        {
            if(LineCount == 1)
            {
                printf("New Name(0 for skip): ");
                scanf(" %[^\n]s", NewName);
                if(strcmp(NewName, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewName) > 20)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    if(exists(NewName, 'n') == 1)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    strcat(NewFullContact, NewName);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 2;
            }
            else if(LineCount == 2)
            {
                printf("Old Phone is: %s", Line);
                printf("New Phone(0 for skip): ");
                scanf("%s", NewPhone);
                if(strcmp(NewPhone, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewPhone) > 20)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    if(exists(NewPhone, 'p') == 1)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    strcat(NewFullContact, NewPhone);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 1;
            }
            else if(LineCount == 3)
            {
                printf("Old Email is: %s", Line);
                printf("New Email(0 for skip): ");
                scanf("%s", NewEmail);

                if(strcmp(NewEmail, "0") == 0)
                {
                    strcat(NewFullContact, Line);
                }
                else
                {
                    if(strlen(NewEmail) > 30)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    if(exists(NewEmail, 'e') == 1)
                    {
                        fclose(OurExistingFile);
                        fclose(NewTempFile);
                        remove("temp-file.txt");
                        restart();
                        return;
                    }
                    strcat(NewFullContact, NewEmail);
                    strcat(NewFullContact, "\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile, "%s", NewFullContact);
            }
        }
        else
        {
            fprintf(NewTempFile, "%s", Line);
        }

        if(LineCount == 3)
        {
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundContact == 0)
    {
        printf("Contact Not Found!\n");
        remove("temp-file.txt");
    }
    else
    {
        printf("\nContact Updated Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void delete_one()
{
    system("cls");
    printf("\n\t\t **** Delete a Contact ****\n\n");

    int lineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    printf("Enter The Name which one you want to delete: ");
    scanf(" %[^\n]s", GivenName);
    if(strlen(GivenName) > 20)
    {
        restart();
        return;
    }
    strcat(GivenName, "\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("All-Contact.txt", "r");
    if(OurExistingFile == NULL)
    {
        printf("\nNo contacts found!\n");
        GoBackOrExit();
        return;
    }
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile))
    {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0)
        {
            FoundTheContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0)
        {
            SkipLines--;
        }
        else
        {
            fprintf(NewTempFile, "%s", line);
        }

        if(lineCount == 3)
        {
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheContact == 0)
    {
        printf("\nContact Not Found!\n\n");
        remove("temp-file.txt");
    }
    else
    {
        printf("\nContact Deleted Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void delete_all()
{
    system("cls");
    printf("\n\t\t **** Delete All The Contacts ****\n\n");

    char Option;
    getchar();
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    scanf("%c", &Option);
    if(Option == 'Y' || Option == 'y')
    {
        remove("All-Contact.txt");
        FILE *AllContactTxtFile = fopen("All-Contact.txt", "a");
        fclose(AllContactTxtFile);
        printf("\nSuccessfully Deleted All Contacts!\n\n");
    }
    GoBackOrExit();
}

void guideline()
{
    system("cls");
    printf("\n\t\t **** Contact Management System ****\n");
    printf("\n\n\n\t\t\tUser Guideline\n");
    printf("\t\t===============================\n");
    printf("\t\t> Name, Phone and email should be unique.\n");
    printf("\t\t> Maximum length of name is 20 characters.\n");
    printf("\t\t> Maximum length of phone is 20 characters.\n");
    printf("\t\t> Maximum length of email is 30 characters.\n");
    printf("\t\t===============================\n\t\t");
    GoBackOrExit();
}

void us()
{
    system("cls");
    printf("\n\t\t **** Contact Management System ****\n");
    printf("\n\n\n\t\t\tAbout US\n");
    printf("\t\t======================\n");
    printf("\t\tThis program is managed by:\n\n\t\tSadid Ahmed \t\tMd. Hujaifa Islam Johan\n");
    printf("\t\tID: 0112330154\t\tID: 0112330149\n");
    printf("\t\tTelegram: @litch07\tTelegram: @hujaifa_johan\n\n");
    printf("\t\tThis is our first project\n");
    printf("\t\tFor any queries feel free to contact us\n");
    printf("\t\t======================\n\t\t");
    GoBackOrExit();
}

int main()
{
    while(isRunning == true)
    {
        Menu();
        char str[100];
        char option;
        scanf("%s", str);
        option = str[0];
        switch(option)
        {
        case '0':
            Exit();
            break;
        case '1':
            add();
            break;
        case '2':
            show();
            break;
        case '3':
            search();
            break;
        case '4':
            edit();
            break;
        case '5':
            delete_one();
            break;
        case '6':
            delete_all();
            break;
        case 'I':
        case 'i':
            guideline();
            break;
        case 'A':
        case 'a':
            us();
            break;
        default:
            restart();
            break;
        }
    }
    return 0;
}