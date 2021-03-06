/*旼 WFDOS-C.C 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
/*� WFDOS - Invoke DOS program in background mode from IBM WorkFrame/2.          �*/
/*�                                                                              �*/
/*� Copyright:                                                                   �*/
/*� 賽賽賽賽賽                                                                   �*/
/*� (c) Copyright Per Jessen, 1994.                                              �*/
/*� Permission is granted to any individual or institution to use, copy, or      �*/
/*� redistribute this software so long as all of the original files are included �*/
/*� unmodified, that it is not sold for profit, and that this copyright notice   �*/
/*� is retained.                                                                 �*/
/*�                                                                              �*/
/*� Disclaimer:                                                                  �*/
/*� 賽賽賽賽賽�                                                                  �*/
/*� The code is provided on an "AS IS" basis without any warranty of any kind.   �*/
/*� The author shall not be liable for any damages arising out of your use of    �*/
/*� this code, even if he has been advised of the possibility of such damages.   �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
/*旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커*/
/*� The purpose of this package is to re-direct the output from a background     �*/
/*� DOS-session from the screen to the Monitor Window in the IBM Workframe/2.    �*/
/*� This enables a transparent integration of DOS-tools, such as language pro-   �*/
/*� cessors etc., in the Workframe/2.                                            �*/
/*� Briefly, the Server (WFDOS-S.EXE) sets up a named pipe, and passes it on to  �*/
/*� the Client (WFDOS-C.EXE), which is then started in the DOS-environment.      �*/
/*� When the pipe is established, the Server provides the Client with a program- �*/
/*� name and a list of arguments. The Client will then redirect the normal std-  �*/
/*� out and stderr streams to the pipe, before transferring control to the pro-  �*/
/*� gram to be executed. Any output from this program is now effectively routed  �*/
/*� to the Server, which will display it in the Monitor Window.                  �*/
/*�                                                                              �*/
/*� Please refer to WFDOS-S.C for a description of arguments etc.                �*/
/*�                                                                              �*/
/*�            컴컴컴컴컴컴컴컴컴컴컴�  o  컴컴컴컴컴컴컴컴컴컴컴�               �*/
/*�                                                                              �*/
/*� History:                                                                     �*/
/*� 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�  �*/
/*� 94.05.31 - Version 2.02 released.                                            �*/
/*� 94.07.11 - Version 2.03 - no modifications.                                  �*/
/*�            Note: This version was not released to the public domain.         �*/
/*� 94.07.31 - Version 2.04 - only minor modifications. See WFDOS-S.             �*/
/*� 94.09.03 - Version 2.05 - minor bugfix in WFDOS-S.                           �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <conio.h>
#include <io.h>
#include <dir.h>
#include <dos.h>
#include <fcntl.h>
#include <sys\stat.h>
#include "wfdos.h"

static char message[BFR_SIZE];

int cdecl main ( int argc, char *argv[] )
{
   char    *pipeName;
   int     hpipe, hstdout, hstderr;
   char    *args[MAX_ARG];
   int     arg, rc, msglevel, i;
   char    *logo = CLIENT_LOGO;

   /* Check that we're being called by WFDOS-S */
   if ( argc<2 || strcmp( argv[1], SERVER_IDENT )!=0 )
   {
      printf("%s"
             "The Client-process can only be started by the "
             "Server-process.", logo);
      return -1;
   }

   /* Before we start doing anything else, we have to redirect  */
   /* stdout and stderr to the pipe                             */

   /* Get the pipename supplied as the last argument            */
   pipeName=argv[argc-1];

   /* Open the pipe for reading and writing text - do 5 retries */
   i=0;
   while ( (hpipe=open( pipeName, O_RDWR|O_TEXT, S_IWRITE|S_IREAD ))<0 && ++i<5 ) delay(250);

   if ( hpipe<0 )
   {
      DosBeep(500,100); DosBeep(1000,100);
      printf("\n%s"
             "Error opening pipe %s - %s"
             "\n\nPress any key to exit ...",
             logo, pipeName, sys_errlist[errno] );
      getch();
      return -1;
   }

   /* Read the message (arguments list) */
   read( hpipe, message, BFR_SIZE );

   /* Save a copy of handle for STDOUT */
   hstdout=dup( STDOUT );
   hstderr=dup( STDERR );

   /* Redirect stdout to our pipe by copying the pipe-handle to stdout */
   dup2( hpipe, STDOUT );
   dup2( hpipe, STDERR );

   /* Close the pipe */
   close( hpipe );

   arg=2;
   while ( *argv[arg]=='/' && arg<argc )
   {
      switch ( *(argv[arg]+1) ) {
      case 'm':
      case 'M':
         sscanf( argv[arg]+2, "%d", &msglevel );
         break;
      default:
         printf( "%s"
                 "Client: Invalid argument %s ignored.\n", logo, argv[arg] );
         logo="";
         break;
      } /* endswitch */
      arg++;
   } /* endwhile */

   if ( msglevel>0 ) 
   {
      printf("%s", logo );
      logo="";
   }

   /* Tokenize the arg-list - blanks separate tokens */
   args[0]=strtok( message, " " );
   arg=1;
   while ( (args[arg]=strtok( NULL, " " ))!=NULL && arg<MAX_ARG ) arg++;

   if ( arg==MAX_ARG )
   printf("%s"
          "Client: Number of arguments > %d - extraneous arguments ignored.\n", 
          logo, MAX_ARG);

   if ( msglevel>=MLVL_CRUNTIME )
   {
      printf("Client: Calling %s ...\n"
             "Client: with argument(s): ", searchpath(args[0]) );
      for ( i=1; i<arg; i++) printf("%s ", args[i] );
      putchar('\n');
   }

   /* NOTE: spawnvp is used instead of execvp to enable the Client to */
   /* retrieve the returncode and pass it on to the Server.           */
   rc=spawnvp( P_WAIT, args[0], args );

   /* NOTE: As a negative rc indicates a spawn.. processing error   */
   /* any negative rc's returned by the called program will be      */
   /* turned into positive by overlaying the leftmost byte with 00. */
   if ( rc<0 )
      printf("%s"
             "Client: %s: %s\n", logo, args[0], sys_errlist[errno] );

   /* Pipe the return-code to the server */
   printf(CLIENTRC_IDENT"%d", rc);

   dup2( hstdout, STDOUT );
   dup2( hstderr, STDERR );

   close( hstdout );
   close( hstderr );

   return 0;
}
