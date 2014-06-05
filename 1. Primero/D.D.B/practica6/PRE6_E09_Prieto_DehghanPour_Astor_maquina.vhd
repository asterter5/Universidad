ENTITY FF_JK_Pujada IS
PORT(J, K, Clk, Pre, Clr: IN BIT; Q, NO_Q: OUT BIT);
END FF_JK_Pujada;

ARCHITECTURE ifthen OF FF_JK_Pujada IS
SIGNAL qint: BIT;
BEGIN
PROCESS (J, K, Clk, Pre, Clr)
BEGIN
	IF Clr='0' THEN qint<='0' AFTER 5ns;
	ELSE
		IF Pre='0' THEN qint<='1' AFTER 5ns;
		ELSE
			IF Clk'EVENT AND Clk='1' THEN
				IF J='0' AND K='0' THEN qint<=qint AFTER 5 ns;
				ELSIF J='0' AND K='1' THEN qint<='0' AFTER 5 ns;
				ELSIF J='1' AND K='0' THEN qint <='1' AFTER 5 ns;
				ELSIF J='1' AND K='1' THEN qint<=NOT qint AFTER 5 ns;
				END IF;
			END IF;
		END IF;
	END IF;
END PROCESS;
Q<=qint; NO_Q<= NOT qint;
END ifthen;

ENTITY inv IS

PORT (a : IN BIT;
z : OUT BIT);

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

PORT (a : IN BIT;
b : IN BIT;
z : OUT BIT);

END and2;


ARCHITECTURE logica OF and2 IS

BEGIN

z <= a and b;

END logica;


ARCHITECTURE logicaretard OF and2 IS

BEGIN

z <= a and b AFTER 3 ns;

END logicaretard;


ENTITY xor2 IS
PORT(a,b:IN BIT; z: OUT BIT);
END xor2;

ARCHITECTURE logica OF xor2 IS
BEGIN
z<= (NOT a AND b) OR (a AND NOT b);
END logica;

ARCHITECTURE logicaretard OF xor2 IS
BEGIN
z<= (NOT a AND b) OR (a AND NOT b) AFTER 5ns;
END logicaretard;

----------------------------------------------------------------------------------------

ENTITY circuit IS
PORT(x, clock: IN BIT; z: OUT BIT_VECTOR(2 DOWNTO 0));
END circuit;

ARCHITECTURE estructural OF circuit IS

COMPONENT p_inv IS
PORT (a : IN BIT;
z : OUT BIT);

END COMPONENT;


COMPONENT p_and2 IS
PORT (a : IN BIT;
b : IN BIT;
z : OUT BIT);

END COMPONENT;


COMPONENT p_xor2 IS
PORT(a,b:IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT FF_JK IS
PORT(J, K, Clk, Pre, Clr: IN BIT; Q, NO_Q: OUT BIT);
END COMPONENT;

SIGNAL pxor, invxor, pand, q2, nq2, q1, nq1, q0, nq0: BIT;

FOR DUT1: p_xor2 USE ENTITY WORK.xor2(logicaretard);
FOR DUT2: p_inv USE ENTITY WORK.inv(logicaretard);
FOR DUT3: p_and2 USE ENTITY WORK.and2(logicaretard);
FOR DUT4: FF_JK USE ENTITY WORK.FF_JK_Pujada(ifthen);
FOR DUT5: FF_JK USE ENTITY WORK.FF_JK_Pujada(ifthen);
FOR DUT6: FF_JK USE ENTITY WORK.FF_JK_Pujada(ifthen);

BEGIN
DUT1: p_xor2 PORT MAP(x, q0, pxor);
DUT2: p_inv PORT MAP(pxor, invxor);
DUT3: p_and2 PORT MAP(invxor, q1, pand);
DUT4: FF_JK PORT MAP(pand, pand, clock, '1', '1', q2, nq2);
DUT5: FF_JK PORT MAP(invxor, invxor, clock, '1', '1', q1, nq1);
DUT6: FF_JK PORT MAP(x, '1', clock, '1', '1', q0, nq0);

z(0)<=q0;
z(1)<=q1;
z(2)<=q2;

END estructural;

ENTITY bdp_circuit IS
END bdp_circuit;

ARCHITECTURE vector OF bdp_circuit IS

COMPONENT p_circuit IS
PORT(x, clock: IN BIT; z: OUT BIT_VECTOR(2 DOWNTO 0));
END COMPONENT;

SIGNAL x, clock: BIT; 
SIGNAL sort: BIT_VECTOR(2 DOWNTO 0);
FOR DUTX: p_circuit USE ENTITY WORK.circuit(estructural);

BEGIN
DUTX: p_circuit PORT MAP(x, clock, sort);

PROCESS (x, clock)
	BEGIN
	x<= NOT x AFTER 50 ns;
	clock <= NOT clock AFTER 100 ms;

END PROCESS;
END vector;


