#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char buffer[255], file[255];

void main( void )
{
   char ind[10], *offs;
   int linenum;

   fputs("BCC2WF Filter (c) Per Jessen, 1995.\n", stdout);
   while (fgets(buffer,255,stdin)!=NULL)
   {
      linenum=-1;
      sscanf( buffer, "%10s %255s %d:", ind, file, &linenum );
      if ( linenum>0 )
      {
        offs=strchr(buffer, ':');

        if ( stricmp("WARNING",ind)==0 || stricmp("ERROR",ind)==0 )
          fprintf(stdout, "%s(%d) : %s: %s", file, linenum, ind, offs+2 );
        else fputs(buffer,stdout);
      }
      else   fputs(buffer,stdout);
   }
}
