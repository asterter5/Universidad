--Entitat

ENTITY xor2 IS
PORT (a : IN BIT;
b : IN BIT;
z : OUT BIT);
END xor2
ARCHITECTURE logica OF xor2 IS
BEGIN
z <= a xor b;
END logica;
ARCHITECTURE logicaretard OF xor2 IS
BEGIN
z <= a xor b AFTER 2 ns;
END logicaretard;

--Banc de Proves

ENTITY bdp_funcio IS
END bdp_funcio;

ARCHITECTURE vectors OF bdp_funcio IS

COMPONENT la_porta_xor2
PORT (a,b : IN BIT; z : OUT BIT);
END COMPONENT;

SIGNAL ent1, ent2, sortida: BIT;
FOR sort_xor2_logica: la_porta_xor2 USE ENTITY WORK.xor2(logica);
FOR sort_xor2_logicaretard: la_porta_xor2 USE ENTITY WORK.xor2(logicaretard);

BEGIN
sort_xor2_logica: la_porta_xor2 PORT MAP (ent1,ent2,sortida);
sort_xor2_logicaretard: la_porta_xor2 PORT MAP (ent1,ent2,sortida);
PROCESS
BEGIN
ent1 <= '0';
ent2 <= '0';
WAIT FOR 100 ns;
ent1 <= '1';
ent2 <= '0';
WAIT FOR 100 ns;
ent1 <= '0';
ent2 <= '1';
WAIT FOR 100 ns;
ent1 <= '1';
ent2 <= '1';
WAIT FOR 100 ns;
ent1 <= '0';
ent2 <= '0';
WAIT FOR 100 ns;
END PROCESS;
END vectors;

