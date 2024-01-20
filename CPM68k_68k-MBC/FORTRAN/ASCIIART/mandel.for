      PROGRAM MANDEL
      REAL CA, CB, A, B, T
      INTEGER X, Y, I, K
      CHARACTER CH*1
      CHARACTER*80 OUT

      DO 300, Y=-12,12
      DO 200, X=-39,39
      CA=X*0.0458
      CB=Y*0.08333
      A=CA
      B=CB
      K=99
      DO 100, I=0,15
      IF (K .NE. 99) GOTO 100
      T=A*A-B*B+CA
      B=2.0*A*B+CB
      A=T
      IF ((A*A+B*B) .GT. 4.0) K=I
100   CONTINUE
      IF (K .GT. 9) K=K+7
      IF (K .GT. 99) OUT(X+40:X+40)=' '
      IF (K .LT. 99) OUT(X+40:X+40)=CHAR(48+K)
200   CONTINUE
9000  FORMAT(1X,79A)
      WRITE(*,9000) OUT
300   CONTINUE
      END 