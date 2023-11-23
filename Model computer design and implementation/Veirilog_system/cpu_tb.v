`timescale 1ns / 100ps
module cpu_tb;
reg CLK;
reg RESETn;
wire T0,T1,T2,T3,T4,T5,T6,T7,HALT,LD,ADD,SUB,AND,OR,SHL,XOR;
wire [3:0] Q_PC,ABUS;
wire [7:0] DBUS_rom,Dout_ACC,dbus_DR;

cpu DUT(
.CLK(CLK),
.RESETn(RESETn),
.T0(T0),
.T1(T1),
.T2(T2),
.T3(T3),
.T4(T4),
.T5(T5),
.T6(T6),
.T7(T7),
.HALT(HALT),
.LD(LD),
.ADD(ADD),
.SUB(SUB),
.AND(AND),
.OR(OR),
.SHL(SHL),
.XOR(XOR),
.Q_PC(Q_PC),
.ABUS(ABUS),
.DBUS_rom(DBUS_rom),
.Dout_ACC(Dout_ACC),
.dbus_DR(dbus_DR)
);

initial begin
CLK=1'b0;
RESETn=1'b0;
end

always #1 CLK=~CLK;
initial begin
#1 RESETn=1;
#1000 $stop;
end
endmodule
