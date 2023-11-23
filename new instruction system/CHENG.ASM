MOV R0,#00
MOV R1,#09
MOV R2,#09
L1:SUB R2,#00
     JZ L3
     MOV A,R2
     AND A,#01
     JZ L2
     MOV A,R1
     ADD R0,A
L2:SHL R1
     SHR R2
     JMP L1
L3:END
