-- MAQUINA ------------------------------------------------------------

ENTITY maquina IS
PORT(x, clock: IN BIT; z: OUT BIT; y: OUT BIT_VECTOR(1 DOWNTO 0));
END maquina;

ARCHITECTURE estructural OF maquina IS

COMPONENT p_inv IS
PORT  (a: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT p_and2 IS
PORT (a, b: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT p_and3 IS
PORT (a, b, c: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT p_or IS
PORT (a, b: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT FF_D IS
PORT (D, Clk, Clr, Pre: IN BIT; Q, NO_Q: OUT BIT);
END COMPONENT;

SIGNAL notx, noty0, noty1, pand1, pand2, pand3, por: BIT;
SIGNAL yint: BIT_VECTOR(1 DOWNTO 0);

FOR DUT1: p_inv USE ENTITY WORK.inv(logicaretard);
FOR DUT4: p_and2 USE ENTITY WORK.and2(logicaretard);
FOR DUT5: p_and2 USE ENTITY WORK.and2(logicaretard);
FOR DUT6: p_and3 USE ENTITY WORK.and3(logicaretard);
FOR DUT7: p_or USE ENTITY WORK.or2(logicaretard);
FOR DUT8: FF_D USE ENTITY WORK.D_Pujada_PreClr(ifthen);
FOR DUT9: FF_D USE ENTITY WORK.D_Pujada_PreClr(ifthen);

BEGIN
DUT1: p_inv PORT MAP(x, notx);
DUT4: p_and2 PORT MAP(yint(1), notx, pand1);
DUT5: p_and2 PORT MAP(yint(0), notx, pand2);
DUT6: p_and3 PORT MAP(noty0, noty1, notx, pand3);
DUT7: p_or PORT MAP(pand1, pand2, por);
DUT8: FF_D PORT MAP(por, clock, '1', '1', yint(1), noty1);
DUT9: FF_D PORT MAP(pand3, clock, '1', '1', yint(0), noty0);

y(0)<= yint(0);
y(1)<= yint(1);
z <= yint(1);

END estructural;

-- BDP_MAQUINA --------------------------------------------------------------

ENTITY bancdeproves IS
END bancdeproves;

ARCHITECTURE test_maquina OF bancdeproves IS

COMPONENT p_maquina IS
PORT(x, clock: IN BIT; z: OUT BIT; y: OUT BIT_VECTOR(1 DOWNTO 0));
END COMPONENT;

SIGNAL X, CLK, SORT_Z: BIT;
SIGNAL SORT_Y: BIT_VECTOR(1 DOWNTO 0);
FOR DUTx: p_maquina USE ENTITY WORK.maquina(estructural);

BEGIN
DUTx: p_maquina PORT MAP(X, CLK, SORT_Z, SORT_Y);

PROCESS (X, CLK)
	BEGIN
	X <= NOT X AFTER 225 ns;
	CLK<= NOT CLK AFTER 75 ns;
END PROCESS;
END test_maquina;
