SWAP: MACRO &A,&B,
    COPY &A,
    &B
    COPY &B,&A
    COPY &A,&B
    ENDMACRO

SWAP N1

SECAO DATA

N1: CONST 2
N2: CONST 3