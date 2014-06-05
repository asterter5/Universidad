--Entitats


ENTITY inv IS
PORT (a : IN BIT; z : OUT BIT);
END inv;

ARCHITECTURE logica OF inv IS
BEGIN
z <= not a;
END logica;

ARCHITECTURE logicaretard OF inv IS
BEGIN
z <= not a AFTER 3 ns;
END logicaretard;


ENTITY and2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END and2;

ARCHITECTURE logica OF and2 IS
BEGIN
z <= a and b;
END logica;

ARCHITECTURE logicaretard OF and2 IS
BEGIN
z <= a and b AFTER 3 ns;
END logicaretard;

ENTITY and3 IS
PORT (a, b, c : IN BIT; z : OUT BIT);
END and3;

ARCHITECTURE logica OF and3 IS
BEGIN
z <= a and b;
END logica;

ARCHITECTURE logicaretard OF and3 IS
BEGIN
z <= a and b AFTER 3 ns;
END logicaretard;

ENTITY or2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END or2;

ARCHITECTURE logica OF or2 IS
BEGIN
z <= a or b;
END logica;

ARCHITECTURE logicaretard OF or2 IS
BEGIN
z <= a or b AFTER 3 ns;
END logicaretard;


ENTITY D_Pujada_PreClr IS
PORT (D, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END D_Pujada_PreClr;

ARCHITECTURE ifthen OF D_Pujada_PreClr IS
SIGNAL qint: BIT;
BEGIN
PROCESS (D, Clk, Clr, Pre)
BEGIN
	IF Pre='0' THEN qint<='1' AFTER 3 ns;
	ELSE
		IF Clr='0' THEN qint<='0' AFTER 3 ns;
		ELSE
			IF Clk'EVENT AND Clk='1' THEN
				IF D='0' THEN qint<='0' AFTER 3 ns;
				ELSIF D='1' THEN qint<='1' AFTER 3 ns;
				END IF;
			END IF;
		END IF;
	END IF;
END PROCESS;
Q<=qint; NO_Q<=NOT qint;
END ifthen;

