# SBC8080
電源ONで、unimon_8080が起動。
\
B + リターンキーで、BASICが起動。
\
MONITOR + リターンキーで、unimon_8080が再起動。
\
\
ROM.HEX のつくりかた
\
１．go.bat を実行する。
\
２．出来上がり。
\
\
～ hello, world ～
\
1.電源ON
\
Universal Monitor が起動
\
]
\
\
2.BASIC起動
\
]B
\
で、コールドスタート（初期化あり）
\
\
]W
\
で、ウォームスタート（初期化なし）
\
\
3.MONITOR切り替え
\
MONITOR
\
で、Universal Monitor に切り替わる。
\
\
4.機械語
\
]L
\
で、hexファイルをロード待ち
\
:10900000210790CDF904C948454C4C4F2C20574FAF
\
:06901000524C440D0A0061
\
:00000001FF
\
をコピー＆ペースト、送信
\
]G 9000
\
で実行、
\
]G 9000
\
hello, world
\
]
\
\
       1/     0 :                         CPU 8080
\
       2/     0 :                         ;
\
       3/     9000 :                      ORG 9000H
\
       4/     9000 :                      ;
\
       5/     9000 : 21 07 90             LXI     H,MESG
\
       6/     9003 :                      ;MVI     A,00H
\
       7/     9003 : CD F9 04             CALL    04F9H
\
       8/     9006 : C9                   RET
\
       9/     9007 :                      ;
\
       10/    9007 :                      MESG:
\
       11/    9007 : 48 45 4C 4C 4F 2C    DB 'hello, world',0DH,0AH,00H
\
              900D : 20 57 4F 52 4C 44
\
              9013 : 0D 0A 00
\
       12/    9016 :                      END
\
\
asl -L HELLO.ASM
\
p2hex -F Intel HELLO.p HELLO.HEX
\
\
![8080 BASIC, unimon_8080](https://github.com/kadokuratsuyoshi/retro_computing/blob/main/SBC8080/SBC8080_BASIC_unimon.png)
