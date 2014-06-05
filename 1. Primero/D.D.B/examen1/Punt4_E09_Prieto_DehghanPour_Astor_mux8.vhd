ENTITY multiplex8 IS
	PORT (d: IN BIT_VECTOR(7 DOWNTO 0); selec: IN BIT_VECTOR(0 TO 2); sortida: OUT BIT);
END multiplex8;

ARCHITECTURE estructural OF multiplex8 IS

COMPONENT p_mux2 IS
	PORT (a_mux2: IN BIT_VECTOR(1 DOWNTO 0); control: IN BIT; f_mux2: OUT BIT);
END COMPONENT;

COMPONENT p_and3 IS
	PORT (a, b, c: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT p_or4 IS
	PORT (a, b, c, d: IN BIT; z: OUT BIT);
END COMPONENT;

COMPONENT p_inv IS
	PORT (a: IN BIT; z: OUT BIT);
END COMPONENT;

SIGNAL mux2_1, mux2_2, mux2_3, mux2_4, and3_1, and3_2, and3_3, and3_4, inv_1, inv_2: BIT;

FOR DUT1: p_mux2 USE ENTITY WORK.mux2(ifthen);
FOR DUT2: p_mux2 USE ENTITY WORK.mux2(ifthen);
FOR DUT3: p_mux2 USE ENTITY WORK.mux2(ifthen);
FOR DUT4: p_mux2 USE ENTITY WORK.mux2(ifthen);
FOR DUT5: p_and3 USE ENTITY WORK.and3(logica_retard);
FOR DUT6: p_and3 USE ENTITY WORK.and3(logica_retard);
FOR DUT7: p_and3 USE ENTITY WORK.and3(logica_retard);
FOR DUT8: p_and3 USE ENTITY WORK.and3(logica_retard);
FOR DUT9: p_inv USE ENTITY WORK.inv(logica_retard);
FOR DUT10: p_inv USE ENTITY WORK.inv(logica_retard);
FOR DUT11: p_or4 USE ENTITY WORK.or4(logica_retard);

BEGIN
DUT1: p_mux2 PORT MAP(d(7 DOWNTO 6), selec(0), mux2_1);
DUT2: p_mux2 PORT MAP(d(5 DOWNTO 4), selec(0), mux2_2);
DUT3: p_mux2 PORT MAP(d(3 DOWNTO 2), selec(0), mux2_3);
DUT4: p_mux2 PORT MAP(d(1 DOWNTO 0), selec(0), mux2_4);
DUT5: p_and3 PORT MAP(selec(1), selec(2), mux2_1, and3_1);
DUT6: p_and3 PORT MAP(inv_1, selec(2), mux2_2, and3_2);
DUT7: p_and3 PORT MAP(selec(1), inv_2, mux2_3, and3_3);
DUT8: p_and3 PORT MAP(inv_1, inv_2, mux2_4, and3_4);
DUT9: p_inv PORT MAP(selec(1), inv_1);
DUT10: p_inv PORT MAP(selec(2), inv_2);
DUT11: p_or4 PORT MAP(and3_1, and3_2, and3_3, and3_4, sortida);

END estructural;

ENTITY bancproves IS
END bancproves;

ARCHITECTURE prova OF bancproves IS
COMPONENT multiplex8 IS
	PORT (d: IN BIT_VECTOR(7 DOWNTO 0); selec: IN BIT_VECTOR(0 TO 2); sortida: OUT BIT);
END COMPONENT;

SIGNAL entrada: BIT_VECTOR(7 DOWNTO 0);
SIGNAL seleccio: BIT_VECTOR(0 TO 2);
SIGNAL sortida: BIT;

FOR MUX: multiplex8 USE ENTITY WORK.multiplex8(estructural);

BEGIN
MUX: multiplex8 PORT MAP(entrada, seleccio, sortida);

PROCESS(seleccio)
BEGIN
	seleccio(2)<= NOT seleccio(2) AFTER 100 ns;
	seleccio(1)<= NOT seleccio(1) AFTER 200 ns;
	seleccio(0)<= NOT seleccio(0) AFTER 300 ns;
END PROCESS;

PROCESS(entrada)
BEGIN
	entrada(0)<= NOT entrada(0) AFTER 25 ns;
	entrada(1)<= NOT entrada(1) AFTER 25 ns;
	entrada(2)<= NOT entrada(2) AFTER 27 ns;
	entrada(3)<= NOT entrada(3) AFTER 27 ns;
	entrada(4)<= NOT entrada(4) AFTER 27 ns;
	entrada(5)<= NOT entrada(5) AFTER 29 ns;
	entrada(6)<= NOT entrada(6) AFTER 29 ns;
	entrada(7)<= NOT entrada(7) AFTER 33 ns;
END PROCESS;
END prova;
 