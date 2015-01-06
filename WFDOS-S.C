/*ÚÄ WFDOS-S.C ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³ WFDOS - Invoke DOS program in background mode from IBM WorkFrame/2.          ³*/
/*³                                                                              ³*/
/*³ Copyright:                                                                   ³*/
/*³ ßßßßßßßßßß                                                                   ³*/
/*³ (c) Copyright Per Jessen, 1994.                                              ³*/
/*³ Permission is granted to any individual or institution to use, copy, or      ³*/
/*³ redistribute this software so long as all of the original files are included ³*/
/*³ unmodified, that it is not sold for profit, and that this copyright notice   ³*/
/*³ is retained.                                                                 ³*/
/*³                                                                              ³*/
/*³ Disclaimer:                                                                  ³*/
/*³ ßßßßßßßßßßß                                                                  ³*/
/*³ The code is provided on an "AS IS" basis without any warranty of any kind.   ³*/
/*³ The author shall not be liable for any damages arising out of your use of    ³*/
/*³ this code, even if he has been advised of the possibility of such damages.   ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³ The purpose of this package is to re-direct the output from a background     ³*/
/*³ DOS-session from the screen to the Monitor Window in the IBM Workframe/2.    ³*/
/*³ This enables a transparent integration of DOS-tools, such as language pro-   ³*/
/*³ cessors etc., in the Workframe/2.                                            ³*/
/*³ Briefly, the Server (WFDOS-S.EXE) sets up a named pipe, and passes it on to  ³*/
/*³ the Client (WFDOS-C.EXE), which is then started in the DOS-environment.      ³*/
/*³ When the pipe is established, the Server provides the Client with a program- ³*/
/*³ name and a list of arguments. The Client will then redirect the normal std-  ³*/
/*³ out and stderr streams to the pipe, before transferring control to the pro-  ³*/
/*³ gram to be executed. Any output from this program is now effectively routed  ³*/
/*³ to the Server, which will display it in the Monitor Window.                  ³*/
/*³                                                                              ³*/
/*³ Arguments:                                                                   ³*/
/*³                                                                              ³*/
/*³                                                                              ³*/
/*³   ÄÄÄÄÄ WFDOS-S ÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄ      ³*/
/*³                     ÀÄ ? ÄÙ     ÀÄ /m<lvl> ÄÙ     ÀÄ /c<path> ÄÙ             ³*/
/*³                                                                              ³*/
/*³   ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄ      ³*/
/*³                            ³                           ³                   ³*/
/*³          ÀÄÄÄ /o<option> ÄÄÄÙ           ÀÄÄÄ /v<file> ÄÄÄÙ                   ³*/
/*³                                                                              ³*/
/*³   ÄÄÄÄ <DOSprogram> ÄÄÄÄÄÄÄÄÄÄÄÄÄ <DOSargument> ÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄ´      ³*/
/*³                                                        ³                    ³*/
/*³                            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                    ³*/
/*³                                                                              ³*/
/*³                                                                              ³*/
/*³ ? .......: Display arguments format.                                         ³*/
/*³ /m ......: Set message-level.                                                ³*/
/*³ <lvl> ...: Message-level 0 = Suppress all informational messages.            ³*/
/*³            Message-level 1 = Display logo only - default.                    ³*/
/*³            Message-level 2 = Display Client runtime-information.             ³*/
/*³            Message-level 3 = Display Server and Client runtime information.  ³*/
/*³ /c ......: Override default path to the Client - WFDOS-C.EXE.                ³*/
/*³ <path>...: The path to the Client - WFDOS-C.EXE.                             ³*/
/*³            By default, any searchpath specified in the environment-variable  ³*/
/*³            WFDOS_CLIENT is also searched.                                    ³*/
/*³ /o ......: Override default VDM-options.                                     ³*/
/*³ <option>.: A specific VDM-option override.                                   ³*/
/*³ /v ......: Override default VDM-options.                                     ³*/
/*³ <file>...: The fully or partially qualified name of a file containing the    ³*/
/*³            VDM-options.                                                      ³*/
/*³            By default, the current directory and any searchpath specified in ³*/
/*³            environment-variable WFDOS_CLIENT is also searched.               ³*/
/*³ <DOSpgm>.: The fully or partially qualified name of a DOS-program to call.   ³*/
/*³            If partially qualified, standard search-paths are applied.        ³*/
/*³ <DOSarg>.: 0-n arguments to be supplied to the DOS-program.                  ³*/
/*³                                                                              ³*/
/*³ All arguments must be separated by at least one blank.                       ³*/
/*³                                                                              ³*/
/*³            ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  o  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ               ³*/
/*³                                                                              ³*/
/*³ Changelog:                                                                   ³*/
/*³ ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  ³*/
/*³ 94.04.29 - Version 2.00 released to the public domain (CompuServe).          ³*/
/*³ 94.05.13 - Version 2.01 fixes problem re rc=460 from DosStartSession.        ³*/
/*³            (not released - VDM-session is started as an INDEPENDENT)         ³*/
/*³ 94.05.31 - Version 2.02 - a more or less complete re-write.                  ³*/
/*³ 94.07.11 - Version 2.03 - "DPMI_DOS_API=ENABLED", unique pipename.           ³*/
/*³            Note: This version was not released to the public domain.         ³*/
/*³ 94.07.31 - Version 2.04 - support for all VDM-options, plus VDM option-file. ³*/
/*³ 94.09.03 - Version 2.05 - minor bugfix: clientrc wasn't returned.            ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³ readVDMoverrides:                                                            ³*/
/*³ ßßßßßßßßßßßßßßßßß                                                            ³*/
/*³ Read options from the specified options-file, and append them to the over-   ³*/
/*³ ride-string.                                                                 ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³ processVDMoutput:                                                            ³*/
/*³ ßßßßßßßßßßßßßßßßß                                                            ³*/
/*³ Read the output from the VDM, remove extraneous '\r's, copy output to OS/2,  ³*/
/*³ and look for the returncode from the DOS-program.                            ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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

/*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
/*³ main:                                                                        ³*/
/*³ ßßßßß                                                                        ³*/
/*ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
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