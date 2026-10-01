#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include<string.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"


//global variables
unsigned char header[100];
unsigned int size;


//edit
// Function prototypes for editing MP3 tags
void copy_mp3(char *,char *); 
void edit_title(char *);
void edit_artist(char *);
void edit_album(char *);
void edit_year(char *);
void edit_genre(char *);
void edit_comment(char *);
void edit_mp3();


// Function to find a specific frame in the MP3 file
int find_frame(FILE *ptr, char *search_frame,unsigned int *size,unsigned long *frame_position);

// Function to replace the data in a specific frame with new text
void replace_data(char *frame_id,char *new_text);


//veiw
void print_text_frame(unsigned char*,unsigned long int);


//main
// Function prototypes for viewing MP3 tags ,edit MP3 tag and displaying help
void view_mp3(char *);
void edit_mp3();
void help_mp3();
void combine_arguments(int argc, char *argv[], int start, char *str);

#endif
