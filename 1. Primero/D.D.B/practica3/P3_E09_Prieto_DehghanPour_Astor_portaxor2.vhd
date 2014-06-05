ENTITY xor2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END xor2;
ARCHITECTURE logica OF xor2 IS
BEGIN
z <= a XOR b;
END logica;

ARCHITECTURE estructural OF xor2 IS
COMPONENT p_and2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_or2 IS
PORT (a, b : IN BIT; z : OUT BIT);
END COMPONENT;
COMPONENT p_inv IS
PORT (a : IN BIT; z : OUT BIT);
END COMPONENT;

SIGNAL inva, invb, alpha, beta : BIT;

FOR DUT1: p_inv use entity WORK.inv(logicaretard);
FOR DUT2: p_inv use entity WORK.inv(logicaretard);
FOR DUT3: p_and2 use entity WORK.and2(logicaretard);
FOR DUT4: p_and2 use entity WORK.and2(logicaretard);
FOR DUT5: p_or2 use entity WORK.or2(logicaretard);

BEGIN
DUT1: p_inv PORT MAP(a, inva);
DUT2: p_inv PORT MAP(b, invb);
DUT3: p_and2 PORT MAP(inva, b, alpha);
DUT4: p_and2 PORT MAP(a, invb, beta);
DUT5: p_or2 PORT MAP(alpha, beta, z);
END estructural;

ENTITY bdp_xor IS
END bdp_xor;

ARCHITECTURE test OF bdp_xor IS
COMPONENT p_xor2 IS
PORT(a, b : IN BIT; z : OUT BIT);
END COMPONENT;

SIGNAL A, B, F_logica, F_estructural: BIT;
FOR DUTX: p_xor2 USE ENTITY WORK.xor2(logica);
FOR DUTY: p_xor2 USE ENTITY WORK.xor2(estructural);

BEGIN
DUTX: p_xor2 PORT MAP(A, B, F_logica);
DUTY: p_xor2 PORT MAP(A, B, F_estructural);

PROCESS
BEGIN
A <= '0';
B <= '0';
WAIT FOR 100 ns;
A <= '0';
B <= '1';
WAIT FOR 100 ns;
A <= '1';
B <= '0';
WAIT FOR 100 ns;
A <= '1';
B <= '1';
WAIT FOR 100 ns;
END PROCESS;
END test;