all: WFDOS-S.OBJ WFDOS-S.EXE WFDOS-C.OBJ WFDOS-C.EXE WFDOS.INF WFDOS.INI WFDOS.ZIP update

RSP=$(TMP)WFDOS.RSP
WFDOS=WFDOS-S.EXE /m3
VDATE=950417
VTIME=020600
VER="2.06"

WFDOS-S.OBJ: WFDOS-S.C WFDOS.H WFDOS.MAK
#  ICC.EXE /G4 /Gd /C /D__BETA__ $*.C
  ICC.EXE /DNDEBUG /G3 /Gd /C /O /Ol /Gu $*.C

# Compile the Client using Borland's C/C++.
WFDOS-C.OBJ: WFDOS-C.C WFDOS.H WFDOS.MAK
  @echo /c /3 /ms /ID:\BORLANDC\INCLUDE /Tde /w >$(RSP)
  @echo /DNDEBUG /O2 /pr       >>$(RSP)
  $(WFDOS) COMMAND.COM /C BCC.EXE @$(RSP) $*.C ^| BCC2WF.EXE

# Link the Client using Borland's Turbo-Linker
WFDOS-C.EXE: WFDOS-C.OBJ
  @echo /LD:\BORLANDC\LIB /s /c /C /3 /Tde /yx C0S.OBJ $** >$(RSP)
  @echo $@                  >>$(RSP)
  @echo $*.MAP              >>$(RSP)
  @echo CS;                 >>$(RSP)
  $(WFDOS) TLINK.EXE @$(RSP)
  @ZFILE /d$(VDATE) /t$(VTIME) $@

WFDOS-S.EXE: WFDOS-S.OBJ WFDOS-S.DEF
  @echo /noi /exepack /a:4 + >  $(RSP)
  @echo $*.OBJ               >> $(RSP)
  @echo $@                   >> $(RSP)
  @echo $*.MAP               >> $(RSP)
  @echo OS2386.LIB           >> $(RSP)
  @echo $*.DEF;              >> $(RSP)
  link386 @$(RSP)
  @ZFILE /d$(VDATE) /t$(VTIME) $@

WFDOS.INF: WFDOS.IPF WFDOS.MAK
  IPFC $*.IPF /INF
  @ZFILE /d$(VDATE) /t$(VTIME) $@

WFDOS.INI: WFDOS.RC  WFDOS.MAK

WFDOS.ZIP:: WFDOS-S.C \
            WFDOS-C.C \
            WFDOS.H   \
            WFDOS-S.EXE \
            WFDOS-C.EXE \
            WFDOS.INF \
            WFDOS.RC \
            WFDOS.INI \
            WFDOS.MAK
#  @-erase $@
  $(WFDOS) PKZIP.EXE -a -ex $@ $?

WFDOS.ZIP:: BCC2WF.C TASM2WF.C WFDOS.MAK
  $(WFDOS) PKZIP.EXE -a -ex $@ $?

update: WFDOS.ABS WFDOS.ZIP WFDOS.MAK
  $(WFDOS) COMMAND.COM /C type WFDOS.ABS ^| PKZIP.EXE -z WFDOS.ZIP
  @ZFILE /d$(VDATE) /t$(VTIME) WFDOS.ZIP

