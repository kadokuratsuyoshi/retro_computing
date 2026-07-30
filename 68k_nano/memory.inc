; vim:noet:sw=8:ts=8:sts=8:ai:syn=asm68k

ROMSIZE         equ     $010000 ;64KB
RAMSIZE         equ     $100000 ;1MB
;RAMSIZE         equ     $080000 ;512kB
RAMEND          equ     RAM+RAMSIZE
INITIAL_SP      equ     RAMEND
;-------------------------------------------------------------------------------
; Base addresses
ROM             equ     $000000
RAM             equ     $E00000
;-------------------------------------------------------------------------------
; Memory reserved for the system
SYSMEMSTART     equ     RAM
SYSMEMSIZE      equ     256
                rsset	SYSMEMSTART
OUTCH_VEC       rs.l    1
INCH_VEC        rs.l    1
HEXDIGITS       rs.l    1
SEPARATORS      rs.l    1
DATE_SEP        equ     SEPARATORS
TIME_SEP        equ     SEPARATORS+1
THOUSANDS_SEP   equ     SEPARATORS+2

; Mounted filesystem parameters
PARTSIZE        rs.l    1               ; size of the partition in sectors, 0 = not mounted (4 bytes)
BPBSECTOR       rs.l    1               ; sector number of the partition's BIOS Parameter Block (4 bytes)
; These parameters are in reverse order of those in the BPB,
; because they are little-endian quantities that need to be byte-swapped
FATSIZE         rs.w    1               ; size of a FAT in sectors (2 bytes)
MAXRDIRENTS     rs.w    1               ; maximum number of root directory entries (2 bytes)
FATCOPIES       rs.w    1               ; number of FATs (padded to 2 bytes)
RSVDSECTORS     rs.w    1               ; number of reserved sectors (2 bytes)
CLUSTERSIZE     rs.w    1               ; number of sectors per cluster (2 bytes)
RDIRSECTOR      rs.l    1               ; sector number of root directory table (4 bytes)
FATSECTOR       rs.l    1               ; sector number of FAT #1 (4 bytes)
DATASTART       rs.l    1               ; sector number of data region start (4 bytes)
VOLNAME         rs.b    12              ; volume label (11 bytes, one extra for padding)
FSVARSTART      equ     PARTSIZE
FSVARLEN        equ     VOLNAME-FSVARSTART+12

INPUTBUFLEN     equ     64
INPUTBUF        rs.b    INPUTBUFLEN+2   ; command input buffer

;-------------------------------------------------------------------------------
; Application programs can be loaded here
APPMEMSTART    equ     SYSMEMSTART+SYSMEMSIZE






; EhBasic ----------------------------------------
* This lot is in RAM

;	ORG	$40000
	ORG	$E80200
ram_strt
;ram_strt	ds.l	$100			* allow 1K for the stack, this should be plenty
						* I'll allow 1K for the stack

;	ORG	$40400
	ORG	$E80400
	even
ram_base
LAB_WARM	ds.w	1			* BASIC warm start entry point
Wrmjpv	ds.l	1			* BASIC warm start jump vector

Usrjmp	ds.w	1			* USR function JMP address
Usrjpv	ds.l	1			* USR function JMP vector

* system dependant i/o vectors
* these are in RAM and are set at start-up

V_INPT	ds.w	1			* non halting scan input device entry point
V_INPTv	ds.l	1			* non halting scan input device jump vector

V_OUTP	ds.w	1			* send byte to output device entry point
V_OUTPv	ds.l	1			* send byte to output device jump vector

V_LOAD	ds.w	1			* load BASIC program entry point
V_LOADv	ds.l	1			* load BASIC program jump vector

V_SAVE	ds.w	1			* save BASIC program entry point
V_SAVEv	ds.l	1			* save BASIC program jump vector

V_CTLC	ds.w	1			* save CTRL-C check entry point
V_CTLCv	ds.l	1			* save CTRL-C check jump vector

entry_sp	ds.l	1			* stack value on entry to basic

Itemp		ds.l	1			* temporary integer (for GOTO etc)

Smeml		ds.l	1			* start of memory	(start of program)
Sfncl		ds.l	1			* start of functions	(end of Program)
Svarl		ds.l	1			* start of variables	(end of functions)
Sstrl		ds.l	1			* start of strings	(end of variables)
Sarryl	ds.l	1			* start of arrays		(end of strings)
Earryl	ds.l	1			* end of arrays		(start of free mem)
Sstorl	ds.l	1			* string storage		(moving down)
Ememl		ds.l	1			* end of memory		(upper bound of RAM)
Sutill	ds.l	1			* string utility ptr
Clinel	ds.l	1			* current line		(Basic line number)
Blinel	ds.l	1			* break line		(Basic line number)

Cpntrl	ds.l	1			* continue pointer
Dlinel	ds.l	1			* current DATA line
Dptrl		ds.l	1			* DATA pointer
Rdptrl	ds.l	1			* read pointer
Varname	ds.l	1			* current var name
Cvaral	ds.l	1			* current var address
Frnxtl	ds.l	1			* var pointer for FOR/NEXT
Lvarpl	EQU	Frnxtl		* let var pointer low byte

des_sk_e	ds.l	6			* descriptor stack end
des_sk
						* descriptor stack start address
						* use a4 for the descriptor pointer

* Ibuffs can now be anywhere in RAM just make sure the byte before it is <> $00

		ds.w	1			
Ibuffs	ds.l	$40			* start of input buffer
Ibuffe
						* end of input buffer

FAC1_m	ds.l	1			* FAC1 mantissa1
FAC1_e	ds.w	1			* FAC1 exponent
FAC1_s	EQU	FAC1_e+1		* FAC1 sign (b7)
		ds.w	1			

FAC2_m	ds.l	1			* FAC2 mantissa1
FAC2_e	ds.l	1			* FAC2 exponent
FAC2_s	EQU	FAC2_e+1		* FAC2 sign (b7)
FAC_sc	EQU	FAC2_e+2		* FAC sign comparison, Acc#1 vs #2
flag		EQU	FAC2_e+3		* flag byte for divide routine

PRNlword	ds.l	1			* PRNG seed long word

ut1_pl	ds.l	1			* utility pointer 1

Asptl		ds.l	1			* array size/pointer
Adatal	ds.l	1			* array data pointer

Astrtl	ds.l	1			* array start pointer low byte

numexp	EQU	Astrtl		* string to float number exponent count
expcnt	EQU	Astrtl+1		* string to float exponent count

expneg	EQU	Astrtl+3		* string to float eval exponent -ve flag

func_l	ds.l	1			* function pointer


						* these two need to be a word aligned pair !
Defdim	ds.w	1			* default DIM flag
cosout	EQU	Defdim		* flag which CORDIC output (re-use byte)
Dtypef	EQU	Defdim+1		* data type flag, $80=string, $40=integer, $00=float


Binss		ds.l	4			* number to bin string start (32 chrs)

Decss		ds.l	1			* number to decimal string start (16 chrs)
		ds.w	1			*
Usdss		ds.w	1			* unsigned decimal string start (10 chrs)

Hexss		ds.l	2			* number to hex string start (8 chrs)

BHsend	ds.w	1			* bin/decimal/hex string end


prstk		ds.b	1			* stacked function index

Srchc		ds.b	1			* search character
tpower	EQU	Srchc			* remember CORDIC power (re-use byte)

Asrch		ds.b	1			* scan-between-quotes flag, alt search character

Dimcnt	ds.b	1			* # of dimensions

Breakf	ds.b	1			* break flag, $00=END else=break
Oquote	ds.b	1			* open quote flag (Flag: DATA; LIST; memory)
Gclctd	ds.b	1			* garbage collected flag
Sufnxf	ds.b	1			* subscript/FNX flag, 1xxx xxx = FN(0xxx xxx)
Imode		ds.b	1			* input mode flag, $00=INPUT, $98=READ

Cflag		ds.b	1			* comparison evaluation flag

TabSiz	ds.b	1			* TAB step size

TempB		ds.b	1			* temp byte

comp_f	ds.b	1			* compare function flag, bits 0,1 and 2 used
						* bit 2 set if >
						* bit 1 set if =
						* bit 0 set if <

Nullct	ds.b	1			* nulls output after each line
TPos		ds.b	1			* BASIC terminal position byte
TWidth	ds.b	1			* BASIC terminal width byte
Iclim		ds.b	1			* input column limit
ccflag	ds.b	1			* CTRL-C check flag
ccbyte	ds.b	1			* CTRL-C last received byte
ccnull	ds.b	1			* CTRL-C last received byte 'life' timer

* these variables for simulator load/save routines

file_byte	ds.b	1			* load/save data byte
file_id	ds.l	1			* load/save file ID

		even
		dc.w	0			* dummy even value and zero pad byte
		even
;prg_strt
prg_strt	EQU	$E10000
;ram_top	EQU	$48000		* last RAM byte + 1
* Use these two lines when running from ROM
;ram_addr	EQU	$E8000		* RAM start address
;ram_size	EQU	$08000		* RAM size
ram_addr	EQU	$E00000		* RAM start address
ram_size	EQU	$100000		* RAM size
ram_top		EQU	$E80000		* last RAM byte + 1

; EhBasic ----------------------------------------





; EoF
