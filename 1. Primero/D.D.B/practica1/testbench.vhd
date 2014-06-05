ENTITY testbench IS
END testbench;

ARCHITECTURE vectors OF testbench IS
	COMPONENT porta_inv
		PORT(a: IN BIT; f: OUT BIT);
	END COMPONENT;
	SIGNAL ent: BIT;
	SIGNAL sort1, sort2: BIT;
	FOR DUT: porta_inv USE ENTITY WORK.inversor(logica);
	FOR DUT2: porta_inv USE ENTITY WORK.inversor(logica_retard);
	BEGIN
		DUT: porta_inv PORT MAP(ent, sort1);
		DUT2: porta_inv PORT MAP(ent, sort2);
	PROCESS
	BEGIN
		ent <= '0';
		WAIT FOR 100 ns;
		ent <= '1';
		WAIT FOR 500 ns;
		ent <= '0';
		WAIT FOR 1000 ns;
		ent <= '1';
	END PROCESS;
END vectors;