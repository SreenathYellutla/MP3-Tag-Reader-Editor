#include<stdio.h>
#include "fun.h"
int main(int argc,char *argv[]){
    // Check whether the user provided at least one command-line option

    if(argc<2){
        printf("Error :Not provied option ");
    }

    // Display help and usage information
    if(strcmp(argv[1],"-help")==0){
        help_mp3();
    }

    // View the MP3 tag information of the given file
    if(strcmp(argv[1],"-v")==0){
        if(argv[2]!=NULL){
            view_mp3(argv[2]);
        }else{
            printf(RED"Error :Not provied file name "RESET);
            return 0;
        }
    }

    // View the original MP3 tag information
    if(strcmp(argv[1],"-o")==0){
        if(argv[2]!=NULL){
            view_mp3("sample.mp3");
        }else{
            printf(RED"Error :Not provied file name "RESET);
            return 0;
        }
    }

     // Edit an MP3 tag using the specified -e option
    if(strcmp(argv[1],"-e")==0){

        // Check whether an edit option such as -t, -a, -A is provided
        if(argc<3){
            printf("--Provide Edit option and Replace data--\n");
            return 0;
        }
        else{
            // Edit Title
            if(strcmp(argv[2],"-t")==0){
                if(argc>=4){
                    char strtle[100];
                    // Combine all title arguments to support spaces
                    combine_arguments(argc, argv, 3, strtle);
                    edit_title(strtle);
                }
                else{
                    printf("--Provide Title Name--\n");
                }
            }

            // Edit Artist
            else if(strcmp(argv[2],"-a")==0){
                if(argc>=4){
                    char newartist[100];
                    // Combine all artist arguments to support spaces
                    combine_arguments(argc, argv, 3, newartist);
                    edit_artist(newartist);
                }
                else{
                    printf("--Provide Artist Name--\n");
                }  
            }

            // Edit Album
            else if(strcmp(argv[2],"-A")==0){
                if(argc>=4){
                    char newalbum[100];
                    // Combine all album arguments to support spaces
                    combine_arguments(argc, argv, 3, newalbum);
                    edit_album(newalbum);
                }
                else{
                    printf("--Provide Album Name--\n");
                }
            }

            // Edit Year
            else if(strcmp(argv[2],"-y")==0){
                if(argc>=4){
                    // Year is taken directly from argv[3]
                    edit_year(argv[3]);
                }
                else{
                    printf("--Provide New Year--\n");
                }
                
            }

            // Edit Genre
            else if(strcmp(argv[2],"-g")==0){
                if(argc>=4){
                    char newgenre[100];
                    // Combine all genre arguments to support spaces
                    combine_arguments(argc, argv, 3, newgenre);
                    edit_genre(newgenre);
                }
                else{
                    printf("--Provide New Year--\n");
                }
            }

            // Edit Comment
            else if(strcmp(argv[2],"-c")==0){
                if(argc>=4){
                    char newcomment[100];
                    // Combine all comment arguments to support spaces
                    combine_arguments(argc, argv, 3, newcomment);
                    edit_comment(newcomment);
                }
                else{
                    printf("--Provide New Year--\n");
                }
            }
            
        }
    }

    // Copy the source MP3 to the destination file for fresh editing
    else if(strcmp(argv[1],"-copy")==0){
        if(argc<3){
            printf("--Provide dest file and Source File--");
        }
        else{
            // argv[2] = destination file, argv[3] = source file
            copy_mp3(argv[2],argv[3]);
        }
        
    }
    return 0;

}

/*..Combine multiple command-line arguments into one string.
    This allows values containing spaces to be passed without quotes.
    For example, if the user runs: ./a.out -e -t My New Title
    The title "My New Title" will be combined into a single string...*/
void combine_arguments(int argc, char *argv[], int start, char *str)
{
    str[0] = '\0';
    // Loop through the arguments starting from the specified index and concatenate them into a single string.
    for(int i = start; i < argc; i++){
        strcat(str, argv[i]);
        if(i < argc - 1){
            strcat(str, " ");
        }
    }
}
