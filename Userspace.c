#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <string.h>


int main() 
{
 
   char key[17];

   FILE *fd = fopen("/dev/urandom", "r");
   if(fd == NULL)
   {
      perror("Error opening file");
      return(-1);
   }

   int i = 0;
   
   for(i = 0; i<16; i++)
   {
        if((key[i] = fgetc(fd)) == EOF)
            exit(1);
   }

   key[i] = '\0';

   printf("%s\n", key);
   fclose(fd);
   
   return(0);
}