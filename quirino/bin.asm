SECAO DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
SECAO TEXT
INPUT OLD_DATA
LOAD OLD_DATA
;comentario
L1: DIV DOIS
STORE  NEW_DATA
MUL DOIS
STORE TMP_DATA
LOAD OLD_DATA ;lololol
SUB TMP_DATA
STORE TMP_DATA ; o o o
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA
LOAD OLD_DATA
JMPP L1
STOP
