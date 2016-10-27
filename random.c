#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int randgen();

void main(){
    printf("\n");

    umask(0000);
    
    int number[10];
    int j = 0;
    int current;
    int devRandom = open("/dev/random", O_RDONLY);
    int out[1];
    //generate random numbers
    while(j < 10){
	current = randgen(devRandom, out);
	printf("%d\n",current);
	number[j] = current;
	j++;
    }
    close(devRandom);
    printf("\n");

    //open rNumbers.txt and write
    int file = open("rNumbers.txt", O_CREAT | O_RDWR, 0666);
    write(file, number, 40);
    //printf("%s\n", strerror(errno));
    close(file);

    //open rNumbers.txt and read
    int otherArray[100];
    file = open("rNumbers.txt", O_RDONLY);
    read(file, otherArray, 40);

    //check
    j = 0;
    while (j < 10){
	printf("%d\n", otherArray[j]);
	j++;
    }
    close(file);
}

int randgen(int devRandom, int out[]){
    read(devRandom, out, 4);
    //printf("%s\n", strerror(errno));
    return out[0];
}
