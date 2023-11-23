`timescale 1ns / 1ps

module cpu(
input wire CLK,
input wire RESETn, //清零复位端低有效
output T0,T1,T2,T3,T4,T5,T6,T7,//节拍信号
output wire HALT,SUB,ADD,OR,AND,SHL,XOR,LD,
output wire [3:0] Q_PC,
output wire [3:0] ABUS,
output wire [7:0] DBUS_rom,
output wire [7:0] Dout_ACC,
output wire [7:0] dbus_DR
);
wire EDR,IDR,IPC,IMAR,IA,EA,EALU,ISUM,ISUB,IAND,IOR,ISHL,IXOR,IIR;
PC u0(
.CLK(CLK),
.IPC(IPC),
.CLRn(RESETn),
.Q(Q_PC));

MAR u1(
.CLK(CLK),
.IMAR(IMAR),
.D(Q_PC),
.ABUS(ABUS));

rom u2(
.CE(1'b0),
.ABUS(ABUS),
.DBUS(DBUS_rom));

DR u3(
.CLK(CLK),
.IDR(IDR),
.EDR(EDR),
.D(DBUS_rom),
.Q(dbus_DR));

pulse u4(
.CLK(CLK),
.CLRn(RESETn),
.T0(T0),
.T1(T1),
.T2(T2),
.T3(T3),
.T4(T4),
.T5(T5),
.T6(T6),
.T7(T7));

control u5(
.HALT(HALT),
.LD(LD),
.ADD(ADD),
.SUB(SUB),
.AND(AND),
.OR(OR),
.SHL(SHL),
//.SHR(SHR),
//.NOT(NOT),
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
//.ISHR(ISHR),
//.INOT(INOT),
.IXOR(IXOR),
.EALU(EALU),
.IIR(IIR));

A u6(
.CLK(CLK),
.IA(IA),
.EA(EA),
.DinA(dbus_DR),
.Dout(dbus_DR),
.QA(Dout_ACC));

ALU u7(
.CLK(CLK),
.ISUM(ISUM),
.ISUB(ISUB),
.IAND(IAND),
.IOR(IOR),
.ISHL(ISHL),
//.ISHR(ISHR),
//.INOT(INOT),
.IXOR(IXOR),
.EALU(EALU),
.Din(dbus_DR),//d2
.DinA(Dout_ACC),//d1
.Dout(dbus_DR));

IR u8(
.CLK(CLK),
.IIR(IIR),
.D(dbus_DR),
.HALT(HALT),
.LD(LD),
.ADD(ADD),
.SUB(SUB),
.AND(AND),
//.SHR(SHR),
//.NOT(NOT),
.XOR(XOR),
.OR(OR),
.SHL(SHL)
);

endmodule

