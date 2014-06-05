-- INVERSOR  -----------------------------------------
ENTITY inv IS 
	PORT(a:IN BIT; z:OUT BIT);
END inv;


ARCHITECTURE logica OF inv IS
BEGIN
	z<= NOT a;
END logica;


ARCHITECTURE logica_retard OF inv IS
BEGIN
	z<= NOT a AFTER 5ns;
END logica_retard;


-- AND2 -----------------------------------------
ENTITY and2 IS
	PORT(a,b:IN BIT; z: OUT BIT);
END and2;


ARCHITECTURE logica OF and2 IS
BEGIN
	z<= a AND b;
END logica;

ARCHITECTURE logica_retard OF and2 IS
BEGIN
	z<= a AND b  AFTER 5ns;
END logica_retard;

-- OR2 -----------------------------------------
ENTITY or2 IS
	PORT(a,b:IN BIT; z: OUT BIT);
END or2;


ARCHITECTURE logica OF or2 IS
BEGIN
	z<= a OR b;
END logica;

ARCHITECTURE logica_retard OF or2 IS
BEGIN
	z<= a OR b  AFTER 5ns;
END logica_retard;

-- XOR2 -----------------------------------------
ENTITY xor2 IS
	PORT(a,b:IN BIT; z: OUT BIT);
END xor2;


ARCHITECTURE logica OF xor2 IS
BEGIN
	z<= (NOT a AND b) OR (a AND NOT b);
END logica;

ARCHITECTURE logica_retard OF xor2 IS
BEGIN
	z<= (NOT a AND b) OR (a AND NOT b) AFTER 5ns;
END logica_retard;

-- AND3 -----------------------------------------
ENTITY and3 IS
	PORT(a,b,c:IN BIT; z: OUT BIT);
END and3;


ARCHITECTURE logica OF and3 IS
BEGIN
	z<= a AND b AND c;
END logica;

ARCHITECTURE logica_retard OF and3 IS
BEGIN
	z<= a AND b AND c AFTER 5ns;
END logica_retard;


-- OR3 -----------------------------------------
ENTITY or3 IS
	PORT(a,b,c:IN BIT; z: OUT BIT);
END or3;


ARCHITECTURE logica OF or3 IS
BEGIN
	z<= a OR b OR c;
END logica;

ARCHITECTURE logica_retard OF or3 IS
BEGIN
	z<= a OR b OR c AFTER 5ns;
END logica_retard;


-- OR4 -----------------------------------------
ENTITY or4 IS
	PORT (a,b,c,d: IN BIT; z: OUT BIT);
END or4;


ARCHITECTURE logica OF or4 IS
BEGIN
	z<= a OR b OR c OR d;
END logica;

ARCHITECTURE logica_retard OF or4 IS
BEGIN
	z<= a OR b OR c OR d AFTER 5 ns;
END logica_retard;


-- MUX2 ----------------------------------------
ENTITY mux2 IS
	PORT (a_mux2: IN BIT_VECTOR(1 DOWNTO 0); control: IN BIT; f_mux2: OUT BIT);
END mux2;

ARCHITECTURE ifthen OF mux2 IS
BEGIN
	PROCESS (control, a_mux2)
	BEGIN
		IF control='0' THEN f_mux2<=a_mux2(0) AFTER 5 ns;
		ELSIF control='1' THEN f_mux2<=a_mux2(1) AFTER 5 ns;
		END IF;
	END PROCESS;
END ifthen;