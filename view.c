#include<stdio.h>
#include "fun.h"
#include<string.h>
#include<stdlib.h>

// Print the text stored inside a text frame.
void print_text_frame(unsigned char *frame_data, unsigned long int frame_size)
{
    unsigned char data[100];
    int j = 0;

    // Copy frame data excluding the encoding byte and create a string.
    for(int i = 1; i < frame_size && j < 99; i++){
        data[j++] = frame_data[i];
    }
    data[j] = '\0';
    printf("%s\n", data);
}


// Extract the 4-byte frame size from the frame header.
// The frame size is stored in big-endian format.
unsigned int framesize(unsigned char *header)
{
    unsigned int size;
    size = (header[4] << 24) |
           (header[5] << 16) |
           (header[6] << 8) |
            header[7];
    return size;
}


// Check whether the first three bytes contain the ID3 signature.
// "ID3" indicates that the MP3 file contains an ID3 tag.
int check_id3_header(unsigned char *header)
{
    if(header[0] == 'I' && header[1] == 'D' && header[2] == '3')
    {
        return 1;
    }
    return 0;
}


// Extract the total ID3 tag size from bytes 6 to 9.
// Each byte contributes only 7 bits because the size is SYNCHSAFE.
unsigned int get_tag_size(unsigned char *header)
{
    return ((header[6] & 0x7F) << 21) |
           ((header[7] & 0x7F) << 14) |
           ((header[8] & 0x7F) << 7) |
           (header[9] & 0x7F);
}


// Read and display the ID3 tag information from the given MP3 file.
void view_mp3(char *filename){
    
    FILE *ptr=fopen(filename,"rb");
    if(ptr==NULL){
        printf("file is not opened");
    }

    // Read the 10-byte ID3 header.
    fread(header,1,10,ptr);

    // Check whether the file contains an ID3 header.
    if(check_id3_header(header)){
        printf(CYAN BOLD
       "╔══════════════════════════════════════════════════════╗\n"
       "║                  🎵 MP3 TAG READER                   ║\n"
       "║                 ID3v2.3 INFORMATION                  ║\n"
       "╚══════════════════════════════════════════════════════╝\n"
       RESET);

        printf(GREEN "  ✓ ID3 TAG STATUS : " RESET "FOUND\n");
        printf(GREEN "  ✓ VERSION        : " RESET "%d\n", header[3]);

        printf(CYAN
       "────────────────────────────────────────────────────────\n"
       RESET);  
    }
    else{
        printf("ID3 tag not found ");
        fclose(ptr);
    }


    unsigned long int frame_size;
    unsigned char* frame_data;
    int c=0;

    // Read frames until all six required tags are found.
    while(c<6){
        // Read the 10-byte frame header.
        fread(header,1,10,ptr);
        char frame_id[5];

        // Copy the 4-byte frame ID and make it a C string.
        frame_id[0] = header[0];
        frame_id[1] = header[1];
        frame_id[2] = header[2];
        frame_id[3] = header[3];
        frame_id[4] = '\0';

        // Get the size of the current frame.
        frame_size = framesize(header);


        // Allocate memory to store the frame data.
        frame_data=malloc(frame_size);
        if(frame_data==NULL){
            printf("Memory allocated failed \n");
            c++;
            fclose(ptr);
        }

        // Read the frame data from the MP3 file.
        fread(frame_data,1,frame_size,ptr);

        // Check for Title frame.
        if(strcmp(frame_id,"TIT2")==0){
            printf(YELLOW "  %-7s : " RESET, "TITLE");
            print_text_frame(frame_data,frame_size);
            c++;  
        }

        // Check for Artist frame.
        else if(strcmp(frame_id, "TPE1") == 0){
            printf(YELLOW "  %-7s : " RESET, "Artist");
            print_text_frame(frame_data,frame_size);
            c++;
        }

        // Check for Album frame.
        else if(strcmp(frame_id, "TALB") == 0){
            printf(YELLOW "  %-7s : " RESET, "Album");
            print_text_frame(frame_data,frame_size);
            c++;
        }

        // Check for year frame.
        else if(strcmp(frame_id, "TYER") == 0){
            printf(YELLOW "  %-7s : " RESET, "Year");
            print_text_frame(frame_data,frame_size);
            c++;
        }

        // Check for genre frame.
        else if(strcmp(frame_id, "TCON") == 0){
            printf(YELLOW "  %-7s : " RESET, "Genre");
            print_text_frame(frame_data,frame_size);
            c++;
        }

        // Check for comment frame.
        else if(strcmp(frame_id,"COMM")==0){
            printf(YELLOW "  %-7s : " RESET, "Comment");
            print_text_frame(frame_data,frame_size);
            printf(CYAN"════════════════════════════════════════════════════════\n"RESET);
            printf(BOLD GREEN"              ✓ TAG INFORMATION READ SUCCESSFULLY\n"RESET);
            printf(CYAN"════════════════════════════════════════════════════════\n"RESET);
            c++;
        }
        free(frame_data);

    }

    printf("\n");
    fclose(ptr);
    return ;
}

