#include<stdio.h>
#include<string.h>
#include "fun.h"
#include<stdlib.h>
void copy_mp3(char *temp,char *sample){
    // Open the source MP3 in binary read mode

    FILE *sourc=fopen(sample,"rb");
    FILE *dest=fopen(temp,"wb");
    
    //buffer to hold data while copying
    unsigned char buffer[1024];
    size_t bytes;
    if(sourc == NULL || dest == NULL){
        printf("File opening failed\n");
        return;
    }

    // Read data from sample.mp3 and write it to temp.mp3 until EOF
    while((bytes = fread(buffer, 1, sizeof(buffer), sourc)) > 0)
    {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(sourc);
    fclose(dest);
    printf(GREEN "MP3 copied from backup file successfully for fresh editing.\n" RESET);
}

// Function to find a specific frame in the MP3 file
int find_frame(FILE *ptr, char *comp_tag,unsigned int *size,unsigned long *frame_position)
{
    unsigned char header[10];
    char frameid[5];
    unsigned int tag_size;
    unsigned int frame_size;
    unsigned int bytes = 0;


    // Move the file pointer to the beginning of the file
    fseek(ptr, 0, SEEK_SET);


    //Read the first 10 bytes of the MP3 file.
    fread(header, 1, 10, ptr);


    // Get the total ID3 tag size.
    //
    // header[6] to header[9] contain the tag size.
    // Each byte uses only 7 bits (synchsafe integer).
    //
    // The 4 bytes are combined to form one integer.
    tag_size = ((header[6] & 0x7F) << 21) |
               ((header[7] & 0x7F) << 14) |
               ((header[8] & 0x7F) << 7)  |
                (header[9] & 0x7F);


    // Continue reading frames until we process the complete
    while(bytes < tag_size)
    {
        // Position of current frame header 
        long position = ftell(ptr);


        //Read frame header 
        fread(header, 1, 10, ptr);
        bytes += 10;

        //storing into string 
        for(int i=0;i<4;i++){
            frameid[i]=header[i];
        }
        frameid[4] = '\0';


       /*header[0]–header[3]: frame ID, such as TIT2
        header[4]–header[7]: frame size
        header[8]–header[9]: flags*/
        //converting 32-bit intergeer
        frame_size = (header[4] << 24) |
                     (header[5] << 16) |
                     (header[6] << 8)  |
                      header[7];


        //return size and frame position after frame found.
        if(strcmp(frameid, comp_tag) == 0)
        {
            // Return the size of the found frame to the caller
            *size = frame_size;

            // Return the position of the frame header
            *frame_position = position;

            // Frame found successfully
            return 1;
        }

        /* Skip frame data */
        fseek(ptr, frame_size, SEEK_CUR);

        bytes += frame_size;
    }
    // Required frame was not found
    return 0;
}

// Function to replace the data in a specific frame with new text
void replace_data(char *frame_id,char *new_text){

    // Open the working MP3 file in read + write binary mode
    FILE *ptr=fopen("temp.mp3","r+b");
    if(ptr==NULL){
        printf(" file not opened ");
        return;
    }

    // Variables to hold the old frame size and its position in the file
    unsigned int old_size;
    unsigned long frame_position;


    // Find the required frame and get its size and position
    if(find_frame(ptr,frame_id,&old_size,&frame_position)){
        printf(YELLOW" Tag found : %s\n"RESET,frame_id);
        //printf("Information size : %u\n",old_size);
        //printf("Frame position :%ld\n",frame_position);

        // Calculate the size of the new text to be written, including the null terminator
        unsigned int new_size=strlen(new_text)+1;

        unsigned char id3_header[10];

        // Read the original 10-byte ID3 header
        fseek(ptr,0,SEEK_SET);

        //coping ID3 header in 1st 10 bytes to id3_header
        fread(id3_header,1,10,ptr);
        unsigned int old_tag_size;

        // Extract the old ID3 tag size from the header
        old_tag_size=((id3_header[6]&0x7F)<<21)|((id3_header[7]&0x7F)<<14)|((id3_header[8]&0x7F)<<7)|(id3_header[9]&0x7F);
        unsigned int new_tag_size;

        // Update tag size according to the change in frame size adding new size and removing old size
        new_tag_size=old_tag_size-old_size+new_size;
        

        // Convert new tag size to SYNCHSAFE
         id3_header[6]=((new_tag_size>>21)&0x7F);
         id3_header[7]=((new_tag_size>>14)&0x7F);
         id3_header[8]=((new_tag_size>>7)&0x7F);
         id3_header[9]=(new_tag_size&0x7F);


        // Create a new MP3 file with the modified frame
        FILE *new_file=fopen("temp2.mp3","wb");
        if(new_file==NULL){
            printf(RED"FILE is not opened "RESET);
            return;
        }


        // Start copying data from the beginning of the original file
        fseek(ptr,0,SEEK_SET);

        // Copy everything before the frame being replaced
        for(int i=0;i<frame_position;i++){
            char ch=getc(ptr);
            if(ch == EOF)
                break;
            fputc(ch, new_file);  
        }

        unsigned char new_header[10];

        // Create the new frame header using the same frame ID
        new_header[0]=frame_id[0];
        new_header[1]=frame_id[1];
        new_header[2]=frame_id[2];
        new_header[3]=frame_id[3];

        // Store the new frame size in big-endian format
        new_header[4]=((new_size>>24)&0xff);
        new_header[5]=((new_size>>16)&0xff);
        new_header[6]=((new_size>>8)&0xff);
        new_header[7]=((new_size)&0xff);

        // Frame flags
        new_header[8]=0;
        new_header[9]=0;


        // Write the new frame header
        fwrite(new_header,1,10,new_file);

        // Encoding byte: 0 means ISO-8859-1
        unsigned char encoding = 0;
        fwrite(&encoding, 1, 1, new_file);

        // Write the new text data
        fwrite(new_text,1,strlen(new_text),new_file);

        // Move past the old frame to the remaining MP3 data
        fseek(ptr,frame_position + 10 + old_size, SEEK_SET);


        //copy remaining part
        unsigned char buffer[1024];
        size_t bytes;
        while((bytes = fread(buffer, 1, sizeof(buffer), ptr)) > 0){
            fwrite(buffer,1,bytes,new_file);
        }


        // Close both files after copying is complete
        fclose(new_file);
        fclose(ptr);

        // Replace the old working file with the newly edited file
        remove("temp.mp3");
        rename("temp2.mp3", "temp.mp3");
        printf(GREEN"---Data changed successfully---\n"RESET);
    }
    fclose(ptr);
}


// Replace the title (TIT2) frame
void edit_title(char *new_title){
    replace_data("TIT2", new_title);
}

// Replace the artist (TPE1) frame
void edit_artist(char *new_artist){
    replace_data("TPE1", new_artist);
}

// Replace the album (TALB) frame
void edit_album(char *new_album){
    replace_data("TALB", new_album);
}

// Replace the year (TYER) frame
void edit_year(char *new_year){
    replace_data("TYER", new_year);
}

// Replace the genre (TCON) frame
void edit_genre(char *new_genre){
    replace_data("TCON", new_genre);
}

// Replace the comment (COMM) frame
void edit_comment(char *new_comment){
    replace_data("COMM", new_comment);
}

