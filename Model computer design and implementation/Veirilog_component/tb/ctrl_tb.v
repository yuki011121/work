module ctrl_tb();
wire EDR,IDR,IPC,IMAR,IA,EA,EALU,ISUM,ISUB,IAND,IOR,ISHL,IXOR,IIR;
reg LD;
reg ADD;
reg SUB;
reg SHL;
reg AND;
reg OR;
reg XOR;
reg HALT;
reg T0,T1,T2,T3,T4,T5,T6,T7;
control DUP(
.LD(LD),
.ADD(ADD),
.SUB(SUB),
.AND(AND),
.OR(OR),
.SHL(SHL),
.XOR(XOR),
.T0(T0),
.T1(T1),
.T2(T2),
.T3(T3),
.T4(T4),
.T5(T5),
.T6(T6),
.T7(T7),
.IMAR(IMAR),
.IPC(IPC),
.IDR(IDR),
.EDR(EDR),
.IA(IA),
.EA(EA),
.ISUM(ISUM),
.ISUB(ISUB),
.IAND(IAND),
.IOR(IOR),
.ISHL(ISHL),
.IXOR(IXOR),
.EALU(EALU),
.IIR(IIR));

    initial begin
   // {LD,ADD,SUB,AND,OR,XOR,SHL,HALT}=8'b1000_0000;
    {T0,T1,T2,T3,T4,T5,T6,T7}=8'b1000_0000;
LD<=1'b1;
ADD<=1'b0;
SUB<=1'b0;
SHL<=1'b0;
AND<=1'b0;
OR<=1'b0;
XOR<=1'b0;
HALT<=1'b0;
     end
    always 
    begin
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b1000_0000;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0100_0000;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0010_0000;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0001_0000;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0000_1000;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0000_0100;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0000_0010;
        #40 {T0,T1,T2,T3,T4,T5,T6,T7}=8'b0000_0001;
    end
    always 
    begin
 LD<=1'b0;
 ADD<=1'b1;
 SUB<=1'b0;
 SHL<=1'b0;
 AND<=1'b0;
 OR<=1'b0;
 XOR<=1'b0;
 HALT<=1'b0;
 #320;
  LD<=1'b0;
 ADD<=1'b0;
 SUB<=1'b1;
 SHL<=1'b0;
 AND<=1'b0;
 OR<=1'b0;
 XOR<=1'b0;
 HALT<=1'b0;
 #320;
    end
endmodule 
