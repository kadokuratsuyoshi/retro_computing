PROGRAM asciiart;
VAR
  ic : CHAR;
  i, x, y : INTEGER;
  a, b, ca, cb, t : REAL;

BEGIN
  FOR y:=-12 TO 12 DO BEGIN
    FOR x:=-39 TO 39 DO BEGIN
      ca := x * 0.0458;
      cb := y * 0.08333;
      a := ca;
      b := cb;
      i := -1;
      WHILE (((a*a+b*b)<=4) AND (i<=15)) DO BEGIN
        i := i + 1;
        t := a*a - b*b + ca;
        b := 2*a*b + cb;
        a := t;
      END;
      IF i>15 THEN BEGIN
        WRITE(' ');
      END
      ELSE BEGIN
        IF i>9 THEN BEGIN
          i := i + 7;
        END;
        ic := chr(ord('0')+i);
        WRITE(ic);
      END;
    END;
    WRITELN(' ');
  END
END.
