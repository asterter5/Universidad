
--COMP 4 BITS----------------------------------------------------------------------------
ENTITY comp4bits IS
PORT (enable: IN BIT; a,b: IN BIT_VECTOR(3 DOWNTO 0); z: OUT BIT_VECTOR(2 DOWNTO 0));
END comp4bits;

ARCHITECTURE estructural OF comp4bits IS
COMPONENT comp2bits IS
PORT (enable: IN BIT; a,b: IN BIT_VECTOR(1 DOWNTO 0); z: OUT BIT_VECTOR(2 DOWNTO 0));
END COMPONENT;



--COMP 8 BITS----------------------------------------------------------------------------
