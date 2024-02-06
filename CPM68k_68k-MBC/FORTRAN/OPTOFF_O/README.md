# CP/M68k_68k-MBC/FORTRAN/OPTOFF_O
\
How to resolve the following error :
\
F>LO68 -S -O FOO.68K -T10100 S.O FOO.O CLIB
\
: Undefined symbol(s)
\
__optoff
\
\
F>type optoffo.txt
\
A>AR68.REL W CLIB OPTOFF.O >OPTOFF.O
\
A>AR68.REL R LIBF.A OPTOFF.O
\
F>LO68 -S -O FOO.68K -T10100 S.O OPTOFF.O FOO.O CLIB
\
\
![68k-MBC](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/CPM68k_68k-MBC/FORTRAN/OPTOFF_O/OPTOFF_O.jpg)
\
![68k-MBC](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/CPM68k_68k-MBC/FORTRAN/OPTOFF_O/OPTOFF_O2.jpg)
