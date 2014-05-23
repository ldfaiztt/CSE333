/*Copyright 2013 CHUONG DAO*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFFER_SIZE 256

// helper used to read and print the content 
// of a ordinary file
static void readTheFile (char *path);

// usage of the program
void Usage();

int main (int argc, char **argv) {
	// arguments check
	if (argc != 2) {
		Usage();
	}

	// calling helper to read and print the file
	readTheFile(argv[1]);

	return EXIT_SUCCESS;

}

void readTheFile (char *path) {
	// open the file
	int fd = open (path, O_RDONLY);
	
	// error checking
	if (fd < 0) {
		// error
		perror("Error open file");
		exit(EXIT_FAILURE); 
	}
	// loop through read and print the data until the end of the file
	char buf [BUFFER_SIZE] = {'\0'};
	int result = 0;
	do {
     result = read(fd, buf, BUFFER_SIZE-1);
     if (result == -1) {
       if (errno != EINTR) {
        // a real error happened, return an error result
       }
       // EINTR happened, do nothing and loop back around
		continue;
     }
     if (result !=0 ){
     	 // // adding null terminator and print out result
     	buf[result] = '\0';
     	printf("%s", buf);
     }
  } while (result != 0); 
	// close the file
  	close(fd);
}



void Usage() {
	printf("Usage: ./sec_ex2 [file_name]");
}