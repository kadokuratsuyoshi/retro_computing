// 
//  program:    qwerty.c
//  make:       
//              export DESTDIR="$HOME"
//              export PATH="$HOME/usr/bin:$HOME/usr/local/bin:$PATH"
//              cmoc -I$HOME/usr/local/share/cmoc/include -L$HOME/usr/local/share/cmoc/lib --vectrex --verbose -o qwerty.bin qwerty.c
//  usage:      qwerty.bin on VECTREX ROM
//
#include <vectrex.h>

#pragma vx_copyright "2023"
#pragma vx_title_pos 0,-80
#pragma vx_title_size -8, 80
#pragma vx_title "g DOKA"
#pragma vx_music vx_music_1

#define MAX_BRIGHTNESS (0x7f)

int main()
{
  while(1) {
    wait_recal();
    intensity_a(MAX_BRIGHTNESS);

    print_str_c( 0x25, -0x80, "THE QUICK BROWN FOX" );
    print_str_c( 0x1,  -0x80, "JUMPS OVER THE LAZY DOG" );
  }
  
  return 0;
}
