#include <stdio.h>
#include <string.h>
#include "taskart.h"


void print_help();
void print_bold();
void handle_cli_arguments(int count, char* option_list[]);


int main(int argc, char** argv)
{

    handle_cli_arguments(argc, argv);
    return 0;
}


// ---------------------------------------------------------------------------

void
handle_cli_arguments(int count, char* option_list[count])
{
    char* o; // temporary var, containing current argument string value

    // Walk throught all arguments and find matching
    while (--count)
    {
        o = option_list[count];
        if ( strcmp("-b", o) == 0 || strcmp("--buttart", o) == 0 )
        {
            printf("%s", ASCII_BUTTART_IMAGE);
            printf("\n");
            return; // quit 
        }
        else if ( strcmp("-s", o) == 0 || strcmp("--bricked-squirrel", o) == 0 )
        {
            printf("%s", BROKEN_SQUIRREL);
            printf("\n@ Bricked Squirrel -Joshua Bell-\n\n");
            return; // quit 
        }
        else if ( strcmp("-a", o) == 0 || strcmp("--awkmonkey", o) == 0 )
        {
            printf("%s", ASCII_STRANGEGUY_ART);
            printf("\n@  Awkward Look Monkey Puppet\n\n");
            return; // quit 
        }
    }

    // If no arguments were matched print help
    print_help();
}

// ---------------------------------------------------------------------------

void
print_help()
{
    printf(
        "Hello friend. Hello friend? That's lame. "
        "Maybe I should give you a name.\n"
        "But that's a slippery slope, you're only in my head, \n"
        "we have to remember that. Sh*t, this actually happened, \n"
        "I'm talking to an imaginary person.\n"
        "What I'm about to tell you is top secret. \n"
        "A conspiracy bigger than all of us. \n"
        "There's a powerful group of people out there \n"
        "that are secretly running the world. \n"
        "I'm talking about the guys no one knows about, \n"
        "the ones that are invisible. The top 1%% of the top 1%%, \n"
        "the guys that play God without permission. \n"

        "But, here's your help for meanwhile: \n\n"
        "-b, --buttart -- print buttart\n"
        "-s, --squdrell -- print SquiRRel\n"
        "-a, --awkmonkey -- print monkey\n"
    );
}
