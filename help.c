#include "fun.h"
#include <stdio.h>
// Display all available commands and their usage.
void help_mp3()
{
    printf("\n");

    // Main title
    printf(BOLD CYAN);
    printf("====================================================\n");
    printf("                 MP3 TAG READER                     \n");
    printf("====================================================\n");
    printf(RESET);

    // Copy / Fresh Edit section
    printf(BOLD BLUE"\n[ COPY / FRESH EDIT ]\n"RESET);
    printf(GREEN" ./a.out -copy <destination> <Backup file>\n"RESET);
    printf(YELLOW"       Copy an MP3 file for fresh editing\n"RESET);

    // View section
    printf(BOLD BLUE"\n[ VIEW ]\n"RESET);
    printf(GREEN" ./a.out -v <filename>\n"RESET);

    printf(YELLOW"       View MP3 tag information\n"RESET);
    printf(GREEN" ./a.out -o <filename>\n"RESET);
    printf(YELLOW"       View original MP3 tag information\n"RESET);

    // Edit section
    printf(BOLD"\n[ EDIT ]\n"RESET);

    printf(GREEN);
    printf(" ./a.out -e -t <title>\n");
    printf(" ./a.out -e -a <artist>\n");
    printf(" ./a.out -e -A <album>\n");
    printf(" ./a.out -e -y <year>\n");
    printf(" ./a.out -e -g <genre>\n");
    printf(" ./a.out -e -c <comment>\n");
    printf(RESET);

    printf(YELLOW);
    printf("       -t  Edit Title\n");
    printf("       -a  Edit Artist\n");
    printf("       -A  Edit Album\n");
    printf("       -y  Edit Year\n");
    printf("       -g  Edit Genre\n");
    printf("       -c  Edit Comment\n");
    printf(RESET);


    // Help section
    printf(BOLD BLUE"\n[ HELP ]\n"RESET);
    printf(GREEN" ./a.out -h\n"RESET);
    printf(YELLOW"       Display help and usage information\n"RESET);

    // End of help menu
    printf(BOLD CYAN);
    printf("\n====================================================\n");
    printf(RESET);
}