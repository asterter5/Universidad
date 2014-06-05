ENTITY mux8a1 IS
PORT (sel: IN BIT_VECTOR(2 DOWNTO 0); ent: IN BIT_VECTOR(7 DOWNTO 0); sort: OUT BIT);
END mux8a1;

ARCHITECTURE ifthen OF mux8a1 IS
BEGIN
	PROCESS(sel, ent)
		BEGIN
		IF (sel = "000") THEN sort<=ent(0) AFTER 5 ns;
		ELSIF (sel = "001") THEN sort<=ent(1) AFTER 5 ns;
		ELSIF (sel = "010") THEN sort<=ent(2) AFTER 5 ns;
		ELSIF (sel = "011") THEN sort<=ent(3) AFTER 5 ns;
		ELSIF (sel = "100") THEN sort<=ent(4) AFTER 5 ns;
		ELSIF (sel = "101") THEN sort<=ent(5) AFTER 5 ns;
		ELSIF (sel = "110") THEN sort<=ent(6) AFTER 5 ns;
		ELSIF (sel = "111") THEN sort<=ent(7) AFTER 5 ns;
		END IF;
	END PROCESS;
END ifthen;

ENTITY bdp_mux8a1 IS
END bdp_mux8a1;

ARCHITECTURE test OF bdp_mux8a1 IS

COMPONENT mux8a1 IS
PORT (sel: IN BIT_VECTOR(2 DOWNTO 0); ent: IN BIT_VECTOR(7 DOWNTO 0); sort: OUT BIT);
END COMPONENT;

SIGNAL seleccio: BIT_VECTOR(2 DOWNTO 0);
SIGNAL entrada: BIT_VECTOR(7 DOWNTO 0);
SIGNAL sortida: BIT;

FOR DUT: mux8a1 USE ENTITY WORK.mux8a1(ifthen);

BEGIN
DUT: mux8a1 PORT MAP (seleccio, entrada, sortida);

PROCESS
BEGIN

entrada<="00000000";
WAIT FOR 50 ns;
entrada<="11111111";
WAIT FOR 50 ns;
seleccio<="000"; 
WAIT FOR 50 ns;
seleccio<="001"; 
WAIT FOR 50 ns;
seleccio<="010"; 
WAIT FOR 50 ns;
seleccio<="011"; 
WAIT FOR 50 ns;
seleccio<="100"; 
WAIT FOR 50 ns;
seleccio<="101"; 
WAIT FOR 50 ns;
seleccio<="110"; 
WAIT FOR 50 ns;
seleccio<="111"; 
WAIT FOR 50 ns;

END PROCESS;
END test;
