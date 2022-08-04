/**
 * @author verityafter, a.k.a. StunningSlav
 * GitHub: https://www.github.com/veritiafter/
 */

#include <stdio.h>
#include <unistd.h>


// DEFINITIONS
// ------------
#define USER_LOGIN "admin"
#define USER_PASSW "passw"



char strcomp(char* string1, char* string2);

/*
 * Function: main
 * --------------
 * | Main entry point of the program
 *
 * | Parameters:
 *      argc: amount of arguments passed to the program
 *      argv: list of arguments
 * | Returns:
 *      int
 */
int main(int argc, char** argv)
{
    char login[256], passw[256];
    short trials = 0;

    while (1)
    {
        ++trials;
        // Since login and passw declared ass arrays
        // they are already point to the begining of the array
        // reffering array by name will give its address in return
        // so there's no point in using &
        printf("Enter your login: ");
        scanf("%s", login);
        printf("Enter your passw: ");
        scanf("%s", passw);
        
        printf("\n---------\n");

        if (strcomp(USER_LOGIN, login) && strcomp(USER_PASSW, passw))
        {
            printf("\n----\nWELCOME HOME, ERRANT SON!\n----\n");
            printf("Your username: %s\n", login);
            printf("Your password: %s\n", passw);
            break;
        }
        if (trials >= 3)
        {
            printf("\n----\nMax attempts reached!!\n");
            printf("Waiting for 3 sec...\n----\n");
            trials = 0;
            sleep(3);
        }
    }

    return 0;
}


/*
 * Function: strcomp
 * -----------------
 * | This function compares two strings
 *
 * | Parameters:
 *      str1: sequence of characters of first string
 *      argv: sequence of characters of second string
 * | Returns:
 *      - char
 *          will have value of (1) in case of succes
 *          otherwise (0)
 */
char strcomp(char* string1, char* string2)
{
    char result = 1;
    while (*string1 != '\0' || *string2 != '\0')
    {
        if (*string1 != *string2)
        {
            result = 0;
            break;
        }
        ++string1; ++string2;
    }
    return result;
}