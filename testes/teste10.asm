TESTE: MACRO &A,&B,
    COPY &A,&B
    ADD &A
    ENDMACRO

TESTE2: MACRO &A,&B,
    ADD &B
    ADD &A
    TESTE &A &B
    ENDMACRO

TESTE2 N1 N2

SECAO DATA

N1: CONST 2
N2: CONST 3