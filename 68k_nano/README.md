# 68k_nano
\
オリジナルの参照先(Special Thanks to DragonBallEZ-san)：https://github.com/kyo-ta04/68k-nano

\
\
電源ONで、68K NANO モニタROMが起動。
\
 bキーで、EhBASICが起動。
\
基板本体のリセットキー押しで、68K NANOが再起動。
\
\
rom-l.bin(ODD)、rom-u.bin(EVEN) のつくりかた
\
１．make を実行する。
\
２．出来上がり。
\
![68k_nano, EhBASIC](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/68k_nano/68k_nano.png)
\
![68k_nano, EhBASIC](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/68k_nano/68k_nano_asciiart.png)
\
![68k_nano, EhBASIC](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/68k_nano/68k_nano_SBC.JPG)
\
・確認できているバグ
\
　PRINT EXP(1) が 2.7182718... にならない(オリジナル版から存在)
\
　LIST コマンドが暴走する。(しばらくの期間 Ctrl+C でストップする)
