ENTITY funcio_logica IS
PORT (a0, a1, a2: IN BIT;
f0, f1: OUT BIT);
END funcio_logica;

ARCHITECTURE logica OF funcio_logica IS
BEGIN
f0 <= (NOT(a0 AND (NOT a1))) or (a1 xor a2);
f1 <= ((NOT a0) OR a2) XOR ((NOT a0) AND a1);
END logica;

ENTITY testbench IS
END testbench;

ARCHITECTURE vectors OF testbench IS

COMPONENT func_f0
PORT (a0, a1, a2: IN BIT;
f0: OUT BIT);
END COMPONENT;
COMPONENT func_f1
PORT (a0, a1, a2: IN BIT;
f1: OUT BIT);
END COMPONENT;

SIGNAL ent1, ent2, ent3: BIT;
SIGNAL sort_f0, sort_f1: BIT;
FOR DUT1: func_f0 USE ENTITY WORK.funcio_logica(logica);
FOR DUT2: func_f1 USE ENTITY WORK.funcio_logica(logica);

BEGIN
DUT1: func_f0 PORT MAP (ent1,ent2,ent3,sort_f0);
DUT2: func_f1 PORT MAP (ent1,ent2,ent3,sort_f1);
PROCESS
BEGIN
ent1 <= '0';
ent2 <= '0';
ent3 <= '0';
WAIT FOR 200 ns;
ent1 <= '0';
ent2 <= '0';
ent3 <= '1';
WAIT FOR 200 ns;
ent1 <= '0';
ent2 <= '1';
ent3 <= '0';
WAIT FOR 200 ns;
ent1 <= '0';
ent2 <= '1';
ent3 <= '1';
WAIT FOR 200 ns;
ent1 <= '1';
ent2 <= '0';
ent3 <= '0';
WAIT FOR 200 ns;
ent1 <= '1';
ent2 <= '0';
ent3 <= '1';
WAIT FOR 200 ns;
ent1 <= '1';
ent2 <= '1';
ent3 <= '0';
WAIT FOR 200 ns;
ent1 <= '1';
ent2 <= '1';
ent3 <= '1';
WAIT FOR 200 ns;
ent1 <= '0';
ent2 <= '0';
ent3 <= '0';
WAIT FOR 200 ns;
END PROCESS;
END vectors;