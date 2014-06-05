--Entitats



ENTITY inv IS

PORT (a : IN BIT;
z : OUT BIT);

END inv;

ARCHITECTURE logica OF inversor IS
BEGIN

z <= not a;

END logica;

ARCHITECTURE logicaretard OF inversor IS

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



ENTITY and3 IS

PORT (a : IN BIT;
b : IN BIT;
c : IN BIT;
z : OUT BIT);

END and3;

ARCHITECTURE logica OF and3 IS

BEGIN

z <= a and b and c;

END logica;

ARCHITECTURE logicaretard OF and3 IS

BEGIN

z <= a and b and c AFTER 3 ns;

END logicaretard;


ENTITY and4 IS
PORT (a : IN BIT; b : IN BIT; c : IN BIT; d : IN BIT;
z : OUT BIT);
END and4;
ARCHITECTURE logica OF and4 IS
BEGIN

z <= a and b and c and d;

END logica;

ARCHITECTURE logicaretard OF and4 IS

BEGIN

z <= a and b and c and d AFTER 3 ns;

END logicaretard;


ENTITY or2 IS

PORT (a : IN BIT;
b : IN BIT;
z : OUT BIT);

END or2;

ARCHITECTURE logica OF or2 IS

BEGIN

z <= a or b;

END logica;

ARCHITECTURE logicaretard OF or2 IS

BEGIN

z <= a or b AFTER 3 ns;

END logicaretard;



ENTITY nor2 IS

PORT (a : IN BIT;
b : IN BIT;
z : OUT BIT);

END nor2;

ARCHITECTURE logica OF nor2 IS

BEGIN

z <= NOT(a or b);

END logica;

ARCHITECTURE logicaretard OF nor2 IS

BEGIN

z <= NOT(a or b) AFTER 3 ns;

END logicaretard;



ENTITY or3 IS

PORT (a : IN BIT;
b : IN BIT;
c : IN BIT;
z : OUT BIT);

END or3;

ARCHITECTURE logica OF or3 IS

BEGIN

z <= a or b or c;

END logica;

ARCHITECTURE logicaretard OF or3 IS

BEGIN

z <= a or b or c AFTER 3 ns;

END logicaretard;

ENTITY or4 IS

PORT (a : IN BIT;
b : IN BIT;
c : IN BIT;
d : IN BIT;
z : OUT BIT);

END or4;

ARCHITECTURE logica OF or4 IS

BEGIN

z <= a or b or c or d;

END logica;

ARCHITECTURE logicaretard OF or4 IS

BEGIN

z <= a or b or c or d AFTER 3 ns;

END logicaretard;


--Banc de Proves



ENTITY bdp_portes IS

END bdp_portes;


ARCHITECTURE vectors OF bdp_portes IS


COMPONENT la_porta_and2

PORT (a, b : IN BIT; z : OUT BIT);

END COMPONENT;

COMPONENT la_porta_and3

PORT (a,b,c: IN BIT; z: OUT BIT);

END COMPONENT;

COMPONENT la_porta_or2

PORT (a, b : IN BIT; z : OUT BIT);

END COMPONENT;

COMPONENT la_porta_or3

PORT (a,b,c: IN BIT; z: OUT BIT);

END COMPONENT;

COMPONENT la_porta_inversor

PORT (a : IN BIT; z : OUT BIT);

END COMPONENT;



SIGNAL ent1, ent2, ent3: BIT;
SIGNAL sort_inv, sort_or2, sort_and2, sort_or3, sort_and3: BIT;
SIGNAL sort_invR, sort_or2R, sort_and2R, sort_or3R, sort_and3R: BIT; 


FOR sort_and2_logica: la_porta_and2 USE ENTITY WORK.and2(logica);

FOR sort_and2_logicaretard: la_porta_and2 USE ENTITY WORK.and2(logicaretard);

FOR sort_and3_logica: la_porta_and3 USE ENTITY WORK.and3(logica);

FOR sort_and3_logicaretard: la_porta_and3 USE ENTITY WORK.and3(logicaretard);

FOR sort_or2_logica: la_porta_or2 USE ENTITY WORK.or2(logica);

FOR sort_or2_logicaretard: la_porta_or2 USE ENTITY WORK.or2(logicaretard);

FOR sort_or3_logica: la_porta_or3 USE ENTITY WORK.or3(logica);

FOR sort_or3_logicaretard: la_porta_or3 USE ENTITY WORK.or3(logicaretard);

FOR sort_inv_logica: la_porta_inversor USE ENTITY WORK.inversor(logica);

FOR sort_inv_logicaretard: la_porta_inversor USE ENTITY WORK.inversor(logicaretard);



BEGIN


sort_inv_logica: la_porta_inversor PORT MAP (ent1,sort_inv);
sort_inv_logicaretard: la_porta_inversor PORT MAP (ent1,sort_invR);
sort_and2_logica: la_porta_and2 PORT MAP (ent1,ent2,sort_and2);
sort_and2_logicaretard: la_porta_and2 PORT MAP (ent1,ent2,sort_and2R);
sort_or2_logica: la_porta_or2 PORT MAP (ent1,ent2,sort_or2);
sort_or2_logicaretard: la_porta_or2 PORT MAP (ent1,ent2,sort_or2R);
sort_and3_logica: la_porta_and3 PORT MAP (ent1,ent2,ent3,sort_and3);
sort_and3_logicaretard: la_porta_and3 PORT MAP (ent1,ent2,ent3,sort_and3R);
sort_or3_logica: la_porta_or3 PORT MAP (ent1,ent2,ent3,sort_or3);
sort_or3_logicaretard: la_porta_or3 PORT MAP (ent1,ent2,ent3,sort_or3R);

PROCESS

BEGIN

ent3 <= '0';

ent2 <= '0';

ent1 <= '0';

WAIT FOR 100 ns;
ent3 <= '1';

ent2 <= '0';

ent1 <= '0';

WAIT FOR 100 ns;

ent3 <= '0';

ent2 <= '1';

ent1 <= '0';

WAIT FOR 100 ns;

ent3 <= '1';

ent2 <= '1';

ent1 <= '0';

WAIT FOR 100 ns;

ent3 <= '0';

ent2 <= '0';

ent1 <= '1';

WAIT FOR 100 ns;

ent3 <= '1';

ent2 <= '0';

ent1 <= '1';

WAIT FOR 100 ns;

ent3 <= '0';

ent2 <= '1';

ent1 <= '1';

WAIT FOR 100 ns;

ent3 <= '1';
ent2 <= '1';

ent1 <= '1';

WAIT FOR 100 ns;

ent3 <= '0';

ent2 <= '0';

ent1 <= '0';

WAIT FOR 100 ns;

END PROCESS;

END vectors;