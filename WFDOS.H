/*ÚÄ WFDOS.H ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿*/
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
#ifdef __BETA__
  #define PGM_VER "2.06 Beta"
#else
  #define PGM_VER "2.06"
#endif

#define COPYRIGHT   "(c) Copyright Per Jessen, 1994-1995.\n" \
                    "All rights reserved."

#define SERVER_LOGO "WFDOS Server Version "PGM_VER" "COPYRIGHT"\n"
#define CLIENT_LOGO "WFDOS Client Version "PGM_VER" "COPYRIGHT"\n"

#define DOSSESTITLE "WFDOS Client Version "PGM_VER" running "

#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define MAX_ARG 32            /* Maximum # of cmdline arguments accepted by Client */

#define MLVL_LOGOONLY 1
#define MLVL_CRUNTIME 2
#define MLVL_SRUNTIME 3
#define MLVL_DEFAULT  MLVL_LOGOONLY

#define FAIL_CREATEPIPE_RC    10
#define FAIL_CREATEPIPE_MS    "DosCreateNPipe failed"
#define FAIL_CREATEQUEUE_RC   11
#define FAIL_CREATEQUEUE_MS   "DosCreateQueue failed"
#define FAIL_READQUEUE_RC     12
#define FAIL_READQUEUE_MS     "DosReadQueue failed"
#define FAIL_STARTSESSION_RC  13
#define FAIL_STARTSESSION_MS  "DosStartSession failed"
#define FAIL_DOSCONNECT_RC    14
#define FAIL_DOSCONNECT_MS    "DosConnectNPipe failed"
#define FAIL_WRITE2PIPE_RC    15
#define FAIL_WRITE2PIPE_MS    "DosWrite failed"
#define FAIL_NODOSCLIENT_RC   16
#define FAIL_NODOSCLIENT_MS   "Unable to locate DOS-Client "CLIENTNAME
#define ARGS_NODOSPROGRAM_RC  17
#define ARGS_NODOSPROGRAM_MS  "No DOS-program specified"
#define WARN_NOOPTIONFILE_RC  16
#define WARN_NOOPTIONFILE_MS  "Unable to locate option-file"

#define ABORT                 "processing aborted"
#define PIPESIZE              4096   /* 4k buffer                          */
#define PIPE_TIMEOUT          5000   /* 5 seconds timeout for DosWaitNPipe */
#define PIPE_PREF             "\\PIPE\\"
#define BFR_SIZE              256   /* Buffer-size for DosRead            */

#define ENV_VDMOPT            "WFDOS_VDMOPT"
#define CLIENTNAME            "WFDOS-C.EXE"

#define CLIENTRC_IDENT        "3149813498723897"  /* Any unique sequence will do */
#define SERVER_IDENT          "0987987632544565"  /* Ditto                       */

#ifndef TRUE
  #define TRUE 1
  #define FALSE 0
#endif

#ifndef __OS2__
  #define DosBeep(f,d) sound(f);delay(d);nosound();
#endif
