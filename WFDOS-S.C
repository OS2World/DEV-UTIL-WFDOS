/*旼 WFDOS-S.C 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
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
/*� Arguments:                                                                   �*/
/*�                                                                              �*/
/*�                                                                              �*/
/*�   컴컴� WFDOS-S 컴컴쩡컴컴쩡컴컴쩡컴컴컴컴컴쩡컴컴쩡컴컴컴컴컴컫컴컴컴      �*/
/*�                     읕 ? 켸     읕 /m<lvl> 켸     읕 /c<path> 켸             �*/
/*�                                                                              �*/
/*�   컴컴컴컴컴컴컴컴컴컴컴컴컫컴컴컴컴컴컴컴컴컴컴컴컴컴컴쩡컴컴컴컴컴�      �*/
/*�                            �                           �                   �*/
/*�          읕컴 /o<option> 컴켸           읕컴 /v<file> 컴켸                   �*/
/*�                                                                              �*/
/*�   컴컴 <DOSprogram> 컴컴컴컴컴컴� <DOSargument> 컴컴컴컫컴컴컴컴컴컴캑      �*/
/*�                                                        �                    �*/
/*�                            읕컴컴컴컴컴컴컴컴컴컴컴컴컴켸                    �*/
/*�                                                                              �*/
/*�                                                                              �*/
/*� ? .......: Display arguments format.                                         �*/
/*� /m ......: Set message-level.                                                �*/
/*� <lvl> ...: Message-level 0 = Suppress all informational messages.            �*/
/*�            Message-level 1 = Display logo only - default.                    �*/
/*�            Message-level 2 = Display Client runtime-information.             �*/
/*�            Message-level 3 = Display Server and Client runtime information.  �*/
/*� /c ......: Override default path to the Client - WFDOS-C.EXE.                �*/
/*� <path>...: The path to the Client - WFDOS-C.EXE.                             �*/
/*�            By default, any searchpath specified in the environment-variable  �*/
/*�            WFDOS_CLIENT is also searched.                                    �*/
/*� /o ......: Override default VDM-options.                                     �*/
/*� <option>.: A specific VDM-option override.                                   �*/
/*� /v ......: Override default VDM-options.                                     �*/
/*� <file>...: The fully or partially qualified name of a file containing the    �*/
/*�            VDM-options.                                                      �*/
/*�            By default, the current directory and any searchpath specified in �*/
/*�            environment-variable WFDOS_CLIENT is also searched.               �*/
/*� <DOSpgm>.: The fully or partially qualified name of a DOS-program to call.   �*/
/*�            If partially qualified, standard search-paths are applied.        �*/
/*� <DOSarg>.: 0-n arguments to be supplied to the DOS-program.                  �*/
/*�                                                                              �*/
/*� All arguments must be separated by at least one blank.                       �*/
/*�                                                                              �*/
/*�            컴컴컴컴컴컴컴컴컴컴컴�  o  컴컴컴컴컴컴컴컴컴컴컴�               �*/
/*�                                                                              �*/
/*� Changelog:                                                                   �*/
/*� 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�  �*/
/*� 94.04.29 - Version 2.00 released to the public domain (CompuServe).          �*/
/*� 94.05.13 - Version 2.01 fixes problem re rc=460 from DosStartSession.        �*/
/*�            (not released - VDM-session is started as an INDEPENDENT)         �*/
/*� 94.05.31 - Version 2.02 - a more or less complete re-write.                  �*/
/*� 94.07.11 - Version 2.03 - "DPMI_DOS_API=ENABLED", unique pipename.           �*/
/*�            Note: This version was not released to the public domain.         �*/
/*� 94.07.31 - Version 2.04 - support for all VDM-options, plus VDM option-file. �*/
/*� 94.09.03 - Version 2.05 - minor bugfix: clientrc wasn't returned.            �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
#define INCL_DOSPROFILE
#define INCL_DOSNMPIPES
#define INCL_DOSPROCESS
#define INCL_DOSSESMGR
#define INCL_DOSFILEMGR
#define INCL_DOSMISC
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WFDOS.H"

static UCHAR  work[BFR_SIZE];
static UCHAR  DOSClient[256]  = "";
static UCHAR  DOSargList[256] = "";
static UCHAR  DOSTitle[100]   = DOSSESTITLE;
static UCHAR  pipeName[L_tmpnam+10] = PIPE_PREF;
static USHORT msglevel = MLVL_DEFAULT;         /* Message-level settings     */
static UCHAR  *logo = SERVER_LOGO;

static STARTDATA startData =
{
   32,                                   /* Structure length                  */
   SSF_RELATED_INDEPENDENT,              /* No session relationship           */
   SSF_FGBG_BACK,                        /* Background execution              */
   SSF_TRACEOPT_NONE,                    /* No need to trace                  */
   "",                                   /* Session name - title              */
   "",                                   /* ProgramName - DOS Client          */
   "",                                   /* Arguments - pipename              */
   NULL,                                 /* Program termination queue         */
   "",                                   /* Environment string                */
   SSF_INHERTOPT_PARENT,
   SSF_TYPE_VDM                          /* Virtual DOS Machine               */
};

/*旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커*/
/*� readVDMoverrides:                                                            �*/
/*� 賽賽賽賽賽賽賽賽�                                                            �*/
/*� Read options from the specified options-file, and append them to the over-   �*/
/*� ride-string.                                                                 �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
void readVDMoverrides( UCHAR *optionfile, UCHAR **overrides )
{
   FILE  *options;
   UCHAR *work, *optname, *p;
   UCHAR *o_drive, *o_path, *o_fname, *o_ext;

   /* Get some workspace */
   work=malloc(1024+1024+_MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT+10);
   optname=work+1024+1;
   o_drive=optname+1024+1;
   o_path=o_drive+_MAX_DRIVE+1;
   o_fname=o_path+_MAX_DIR+1;
   o_ext=o_fname+_MAX_FNAME+1;
         
   /* Determine fullpath of the given filespec */
   _splitpath( _fullpath(work, optionfile, 1024), o_drive, o_path, o_fname, o_ext );
                                
   strcpy( work, o_drive ); strcat( work, o_path );
   strcpy( optionfile, o_fname ); strcat( optionfile, o_ext );

   /* Get a possible path from the environment. */
   if ( DosScanEnv( "DPATH", &p )==0 )
   {
      /* We wanna search current directory second, so append a ';.;' before ... */
      strcat(work, ";.;" );
      /* ... appending DPATH.           */
      strcat( work, p );
   }

   /* Search current directory and DPATH. If not found ...    */
   if ( DosSearchPath( 0, work, optionfile, optname, 1024 ) )
   {             
      printf("%s"WARN_NOOPTIONFILE_MS" \"%s\".\n", logo, optionfile );
      logo="";
      return;
   }

   p=*overrides;

   if ( (options=fopen( optname, "r" ))!=NULL )
   while ( fgets( p, 80, options )!=NULL )
   {
      p+=strlen(p)-1;
      if ( *p!='\n' ) p++;
      *(p++)='\0';
   }
   fclose( options );
   free(work);

   *overrides=p;
}

/*旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커*/
/*� processVDMoutput:                                                            �*/
/*� 賽賽賽賽賽賽賽賽�                                                            �*/
/*� Read the output from the VDM, remove extraneous '\r's, copy output to OS/2,  �*/
/*� and look for the returncode from the DOS-program.                            �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
USHORT processVDMoutput( HPIPE hpipe )
{
   USHORT rc;
   ULONG  length;
   UCHAR  *work, *p;

   work=malloc(1024);
   rc=0;
   do
   {
      /* Read whatever is in the queue, and make sure it is null-terminated */
      DosRead( hpipe, work, 1023, &length ); work[length]='\0';

      /* If we got something ... */
      if ( length>0 )
      {
         /* As '\r' and '\n' both will result in a newline, we'll remove  */
         /* the '\r's and leave the '\n's. Otherwise we'll have too many  */
         /* blank lines in the Monitor window.                            */
         while ( (p=strchr( work, '\r' ))!=NULL )
            strcpy( p, p+1 );

         /* If the Client has sent a return-code, retrieve it, but dont   */
         /* display it.                                                   */
         if ( (p=strstr( work, CLIENTRC_IDENT ))!=NULL )
         {
            sscanf( p+strlen(CLIENTRC_IDENT), "%hd", &rc );
            *p='\0';
         }
         printf( "%s", work );
      }
   } while ( length>0 );
   free(work);

   return rc;
}

/*旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커*/
/*� main:                                                                        �*/
/*� 賽賽�                                                                        �*/
/*읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸*/
int main(int argc, char* argv[] )
{
   UCHAR   *p, *env;
   APIRET  rc;
   PID     processID;
   ULONG   sessionID;
   ULONG   length, i, arg;
   USHORT  clientrc = 0;
   HPIPE   hpipe;

   /* Process arguments - we need at least one */
   if ( argc<2 || *argv[1]=='?' )
   {
      printf( "%s"
              "Server: Arguments format:\n"
              "WFDOS-S {?} {/m<lvl>} {/c<path>} "
              "{/o<option>...} {/v<file>...} <DOS-pgm> {<DOS-args>}",
              logo );
      return -1;
   }

   arg=1;
   p=startData.Environment=malloc(1024); *p='\0';
   while ( arg<argc && *argv[arg]=='/' )
   {
      switch ( *(argv[arg]+1) ) {
      case 'm':
      case 'M':
         sscanf( argv[arg]+2, "%1hd", &msglevel );
         break;
      case 'c':
      case 'C':
         strcpy( DOSClient, argv[arg]+2 );
         break;
      case 'o':
      case 'O':
         strcpy( p, argv[arg]+2 ); p+=strlen(p)+1;
         break;
      case 'v':
      case 'V':
         readVDMoverrides( argv[arg]+2, &p );
         break;
      default: 
         printf( "%sServer: Invalid argument %s ignored.\n", logo, argv[arg] );
         *logo='\0';
         break;
      } /* endswitch */
      arg++;
   } 

   /* Check if we have a default VDM option-file */
   if ( DosScanEnv( ENV_VDMOPT, &env )==0 )
      readVDMoverrides( env, &p );

   /* Terminate the Environment-string properly */
   *(p+1)='\0';

   if ( arg==argc )
   {
      printf( "%sServer: "ARGS_NODOSPROGRAM_MS" - "ABORT".", logo);
      return ARGS_NODOSPROGRAM_RC;
   }

   if ( msglevel>0 )
   {
      printf("%s", logo);
      *logo='\0';
   }

   strcpy( work, DOSClient );

   /* Get a possible path from the environment, ie CONFIG.SYS. */
   if ( DosScanEnv( "PATH", &p )==0 )
   {
      /* If the command-line held an override path, append a ';' before ... */
      if ( *work!='\0' ) strcat(work, ";" );
      /* ... appending additional paths from the environment.               */
      strcat( work, p );
   }

   /* Search specified path. If not found ...          */
   if ( rc=DosSearchPath( 0UL, work, CLIENTNAME, DOSClient, 256 ) )
   {
      printf("%s"FAIL_NODOSCLIENT_MS" - "ABORT".", logo);
      return FAIL_NODOSCLIENT_RC;
   }

   /* Having determined the location of the client, put it in startData */
   startData.PgmName=strupr(DOSClient);

   /* Setup the session-heading */
   strcat( DOSTitle, strupr( argv[arg] ) );
   startData.PgmTitle=DOSTitle;

   /* Create a unique pipename - this enables multiple threads using WFDOS */
   i=strlen(pipeName);
   _splitpath( tmpnam(NULL), work, work, pipeName+i, pipeName+i+_MAX_FNAME );
   strcat( pipeName, pipeName+i+_MAX_FNAME );

   /* Pack all arguments into a string separated by blanks.                 */
   p=work;
   for ( i=arg; i<argc; i++)
   {
      memcpy( p, argv[i], strlen(argv[i]) );
      p+=strlen(argv[i]);
      *(p++)=' ';
   };    
   *p='\0';

   /* Setup arguments for the Client */
   sprintf( DOSargList, SERVER_IDENT" /m%d ", msglevel );
   strcat( DOSargList, pipeName );
   startData.PgmInputs=DOSargList;

   if ( rc=DosCreateNPipe( pipeName, &hpipe,
                           NP_INHERIT|NP_ACCESS_DUPLEX,
                           NP_WAIT|NP_TYPE_BYTE|NP_READMODE_BYTE|0x01,
                           PIPESIZE, PIPESIZE, 0 ) )
   {
      printf( "%s"FAIL_CREATEPIPE_MS" - "ABORT", rc=%lu.\n", logo, rc );
      return FAIL_CREATEPIPE_RC;
   }

   if ( msglevel>=MLVL_SRUNTIME )
   {
      printf("Server: Starting client %s ...\n", startData.PgmName );
      if ( *startData.Environment^='\0' ) 
         printf("Server: Overriding VDM-options:\n");
      for ( p=startData.Environment; *p^='\0'; p+=strlen(p)+1)
         printf("        %s\n", p);
   }

   /* Start a VDM-session in the background */
   if ( rc=DosStartSession( &startData, &sessionID, &processID ) )
   {
      printf( "%s"FAIL_STARTSESSION_MS" - "ABORT", rc=%lu.\n", logo, rc );
      return FAIL_STARTSESSION_RC;
   }

   /* Wait for the DOS-program to do DosOpen */
   if ( rc=DosConnectNPipe( hpipe ) )
   {
      printf( "%s"FAIL_DOSCONNECT_MS" - "ABORT", rc=%lu.\n", logo, rc );
      return FAIL_DOSCONNECT_RC;
   }

   if ( rc=DosWrite( hpipe, work, strlen(work), &length ) )
   {
      printf( "%s"FAIL_WRITE2PIPE_MS" - "ABORT", rc=%lu.\n", logo, rc );
      return FAIL_WRITE2PIPE_RC;
   }

   clientrc=processVDMoutput( hpipe );

   free( startData.Environment );

   return clientrc;
}   
