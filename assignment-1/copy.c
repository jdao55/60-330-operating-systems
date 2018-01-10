#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char* argv[])
{
    //check correct number of cl arguments
    if (argc !=3)
    {
        fprintf( stderr,"Incorrect number of arguments call program by:\n"
                 "copy <src_file> <dest_file>\n");
        exit(1);
    }
    int src_file, dest_file;//source and destination files id's
    char buffer[2048];//buffer for copying files
    int read_amt, write_amt;//return values for read() and write() calls

    //open source file for read only
    src_file=open(argv[1], O_RDONLY);
    if (src_file<0)
    {
        fprintf(stderr,"Error opening file: %s\n", argv[1]);
        exit(1);
    }

    //open destination file for writed only, creates a file, if file exits exit
    dest_file=open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0777);
    if (dest_file<0)
    {
        close(src_file);
        fprintf(stderr,"Error opening file: %s\n", argv[2]);
        exit(1);
    }

    //read and copy files in blocks of 2048 bytes
    while( (read_amt=read(src_file, buffer, sizeof(buffer))) >0)
    {
        write_amt=write(dest_file, buffer,  read_amt);
        if(write_amt < 0)
        {
            perror("error while reading/writing file\n");
            exit(1);
        }
            
    }
    //close files
    close(dest_file);
    close(src_file);
    return 0;
        
}
