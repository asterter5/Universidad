ENTITY inversor IS
	PORT(a: IN BIT; f: OUT BIT);
END inversor;

ARCHITECTURE logica OF inversor IS
	BEGIN
	f <= NOT a;
END logica;

ARCHITECTURE logica_retard OF inversor IS
	BEGIN
	f <= NOT a AFTER 15 ns;
END logica_retard;
