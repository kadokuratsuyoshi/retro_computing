MODULE asciiart;
VAR
  ic : CHAR;
  i : CARDINAL;
  x, y : INTEGER;
  a, b, ca, cb, t : REAL;

BEGIN
  FOR y:=-12 TO 12 DO
    FOR x:=-39 TO 39 DO
      ca := FLOAT(x) * 0.0458;
      cb := FLOAT(y) * 0.08333;
      a := ca;
      b := cb;
      i := 0;
      WHILE i<16 DO
        t := a*a - b*b + ca;
        b := 2.0*a*b + cb;
        a := t;
        IF (a*a + b*b)>4.0 THEN
          IF i>9 THEN
            i := i + 7;
          END;
          ic := CHR(ORD('0')+i);
          WRITE(ic);
          i := 99;
        END;
        i := i + 1;
      END;
      IF i=16 THEN
        WRITE(' ');
      END;
    END;
    WRITELN();
  END;
END asciiart.
