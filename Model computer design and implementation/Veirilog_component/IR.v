`timescale 1ns / 1ps

module IR(
input CLK,
input [7:0] D,
input IIR,
output wire ADD,
output wire SUB,
output wire AND,
output wire OR,
output wire SHL,
output wire HALT,
output wire XOR,
output wire LD
    );
    wire [7:0] Q;	 
	 assign LD =   Q[7]&Q[6]&Q[5]&Q[4]&Q[3]& Q[2]& Q[1]& Q[0];
    assign ADD =  Q[7]&Q[6]&Q[5]&Q[4]&Q[3]& Q[2]& Q[1]&~Q[0];
    assign SUB =  Q[7]&Q[6]&Q[5]&Q[4]&Q[3]& Q[2]&~Q[1]& Q[0];
    assign AND =  Q[7]&Q[6]&Q[5]&Q[4]&Q[3]& Q[2]&~Q[1]&~Q[0];
	 assign OR =   Q[7]&Q[6]&Q[5]&Q[4]&Q[3]&~Q[2]& Q[1]& Q[0];
    assign SHL =  Q[7]&Q[6]&Q[5]&Q[4]&Q[3]&~Q[2]&~Q[1]& Q[0];
    assign XOR =  Q[7]&Q[6]&Q[5]&Q[4]&~Q[3]&~Q[2]&Q[1]&~ Q[0];
    assign HALT = Q[7]&Q[6]&Q[5]&Q[4]&Q[3]&~Q[2]&~Q[1]&~Q[0];	 

LS377 u0(
.CLK (CLK),
.EN (IIR),
.D (D),
.Q (Q));
endmodule
