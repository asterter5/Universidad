-- Latch D ------------------------------------------------

ENTITY D_Latch_PreClr IS
PORT (D, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END D_Latch_PreClr;

ARCHITECTURE ifthen OF D_Latch_PreClr IS
SIGNAL qint: BIT;
BEGIN
PROCESS (D, Clk, Clr, Pre)
BEGIN
IF Pre='0' THEN qint<='1' AFTER 2 ns;
ELSE
IF Clr='0' THEN qint<='0' AFTER 2 ns;
ELSE
		IF Clk='1' THEN
			IF D='0' THEN qint<='0' AFTER 2 ns;
			ELSIF D='1' THEN qint<='1' AFTER 2 ns;
			END IF;
		ELSIF Clk='0' THEN qint<=qint AFTER 2 ns;
		END IF;
	END IF;
END IF;

END PROCESS;
Q<=qint; NO_Q<=NOT qint;
END ifthen;

-- Flip-Flop JK Positive Edge-Triggered ------------------

ENTITY JK_Pujada_PreClr IS
PORT (J, K, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END JK_Pujada_PreClr;

ARCHITECTURE ifthen OF JK_Pujada_PreClr IS
SIGNAL qint: BIT;
BEGIN 
PROCESS (J, K , Clk, Clr, Pre)
BEGIN
	IF Pre='0' THEN qint<='1' AFTER 2 ns;
	ELSE
		IF Clr='0' THEN qint<='0' AFTER 2 ns;
		ELSE
			IF Clk'EVENT AND Clk='1' THEN
				IF J='0' AND K='0' THEN qint<=qint AFTER 2 ns;
				ELSIF J='0' AND K='1' THEN qint<='0' AFTER 2 ns;
				ELSIF J='1' AND K='0' THEN qint<='1' AFTER 2 ns;
				ELSIF J='1' AND K='1' THEN qint<=NOT qint AFTER 2 ns;
				END IF;
			END IF;
		END IF;
	END IF;
END PROCESS;
Q<=qint; NO_Q<=NOT qint;
END ifthen;

------------------------------------------------------------------------

ENTITY circuit_FF IS
PORT (x, Clk: IN BIT; z: OUT BIT);
END circuit_FF;


ARCHITECTURE estructural OF circuit_FF IS

COMPONENT Latch_D IS
PORT (D, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END COMPONENT;
COMPONENT FF_JK IS
PORT (J, K, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END COMPONENT;
COMPONENT p_nor2 IS
PORT (a, b: IN BIT; z: OUT BIT);
END COMPONENT;
COMPONENT p_and2 IS
PORT (a, b: IN BIT; z: OUT BIT);
END COMPONENT;
COMPONENT p_inv IS
PORT (a: IN BIT; z: OUT BIT);
END COMPONENT;

SIGNAL x_inv, Q1, NO_Q1, s_and, s_nor, no_Z: BIT;

FOR DUT1: p_inv USE ENTITY WORK.inv(logicaretard);
FOR DUT2: p_and2 USE ENTITY WORK.and2(logicaretard);
FOR DUT3: p_nor2 USE ENTITY WORK.nor2(logicaretard);
FOR DUT4: Latch_D USE ENTITY WORK.D_Latch_PreClr(ifthen);
FOR DUT5: FF_JK USE ENTITY WORK.JK_Pujada_PreClr(ifthen);

BEGIN
DUT1: p_inv PORT MAP(x, x_inv);
DUT2: p_and2 PORT MAP(x, NO_Q1, s_and);
DUT3: p_nor2 PORT MAP(x_inv, Q1, s_nor);
DUT4: Latch_D PORT MAP(x, Clk, '1','1', Q1, NO_Q1);
DUT5: FF_JK PORT MAP(s_and, s_nor, Clk, '1','1', z, no_Z);
END estructural;

ENTITY bdp_circuit IS
END bdp_circuit;

ARCHITECTURE test OF bdp_circuit IS
COMPONENT z_circuit IS
PORT (x, Clk: IN BIT; z: OUT BIT);
END COMPONENT;

SIGNAL ENT_x, CLK, SORT_z: BIT;
FOR DUTx: z_circuit USE ENTITY WORK.circuit_FF(estructural);

BEGIN
DUTx: z_circuit PORT MAP(ENT_x, CLK, SORT_z);

PROCESS (ENT_x, CLK)
	BEGIN
	ENT_x<=NOT ENT_x AFTER 200 ns;
	CLK<=NOT CLK AFTER 100 ns;
END PROCESS;
END test;
