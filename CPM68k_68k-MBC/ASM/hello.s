          text
          move.l      #message,d1
          move        #9,d0
          trap        #2

          data
message:  dc.b        13,10,'Hello World!','$'
          end
