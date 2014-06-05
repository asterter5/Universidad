
ENTITY funcio IS
PORT (a, b, c, d : IN BIT; f : OUT BIT);
END funcio;
ARCHITECTURE logica OF funcio IS
BEGIN
f <= (((NOT a) AND b AND (NOT c)) OR (b AND (NOT d)) OR (a AND c AND d) OR (a AND (NOT d))) XOR (a OR (NOT d));
END logica;

ARCHITECTURE estructural OF funcio IS
COMPONENT p_and2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_and3 IS
PORT (a, b, c : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_or2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_or4 IS
PORT (a, b, c, d : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_xor2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_inv IS
PORT (a : IN BIT; z : OUT BIT);
END COMPONENT;

SIGNAL inva, invc, invd1, invd2, invd3, alpha, beta, gamma, omega, una, dos : BIT;

FOR DUT1: p_inv use entity WORK.inv(logica);
FOR DUT2: p_inv use entity WORK.inv(logica);
FOR DUT3: p_inv use entity WORK.inv(logica);
FOR DUT4: p_inv use entity WORK.inv(logica);
FOR DUT5: p_inv use entity WORK.inv(logica);
FOR DUT6: p_and2 use entity WORK.and2(logica);
FOR DUT7: p_and2 use entity WORK.and2(logica);
FOR DUT8: p_and3 use entity WORK.and3(logica);
FOR DUT9: p_and3 use entity WORK.and3(logica);
FOR DUT10: p_or2 use entity WORK.or2(logica);
FOR DUT11: p_or4 use entity WORK.or4(logica);
FOR DUT12: p_xor2 use entity WORK.xor2(logica);

BEGIN
DUT1: p_inv PORT MAP(a, inva);
DUT2: p_inv PORT MAP(c, invc);
DUT3: p_inv PORT MAP(d, invd1);
DUT4: p_inv PORT MAP(d, invd2);
DUT5: p_inv PORT MAP(d, invd3);
DUT6: p_and2 PORT MAP(b, invd1, beta);
DUT7: p_and2 PORT MAP(a, invd2, omega);
DUT8: p_and3 PORT MAP(inva, b, invc, alpha);
DUT9: p_and3 PORT MAP(a, c, d, gamma);
DUT10: p_or2 PORT MAP(a, invd3, dos);
DUT11: p_or4 PORT MAP(alpha, beta, gamma, omega, una);
DUT12: p_xor2 PORT MAP(una, dos, f);
END estructural;

ENTITY banc_de_proves IS
END banc_de_proves;

ARCHITECTURE test OF banc_de_proves IS
COMPONENT p_funcio IS
PORT(a, b, c, d: IN BIT; f : OUT BIT);
END COMPONENT;

SIGNAL ent0, ent1, ent2, ent3, sor_logica, sor_estructural: BIT;
FOR DUTX: p_funcio USE ENTITY WORK.funcio(logica);
FOR DUTY: p_funcio USE ENTITY WORK.funcio(estructural);

BEGIN
DUTX: p_funcio PORT MAP(ent0, ent1, ent2, ent3, sor_logica);
DUTY: p_funcio PORT MAP(ent0, ent1, ent2, ent3, sor_estructural);

PROCESS(ent0, ent1, ent2, ent3)
	BEGIN
	ent0 <= NOT ent0 AFTER 200 ns;
	ent1 <= NOT ent1 AFTER 100 ns;
	ent2 <= NOT ent2 AFTER 50 ns;
	ent3 <= NOT ent3 AFTER 25 ns;
END PROCESS;
END test;
