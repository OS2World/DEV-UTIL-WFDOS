#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char buffer[255], file[255];

void main( void )
{
   char ind[10], *offs;
   int linenum;

   fputs("TASM2WF Filter (c) Per Jessen, 1995.\n", stdout);
   while (fgets(buffer,255,stdin)!=NULL)
   {
      linenum=-1;
      sscanf( buffer, "%s %255s", ind, file );
      offs=strchr(buffer, ')');
      if (stricmp("**ERROR**",ind)==0)
      fprintf(stdout, "%s : Error: %s", file, offs+2 );
      else fputs(buffer,stdout);
   }
}
