`timescale 1ns / 1ps

module A(
input CLK,
input [7:0] DinA,
input IA,
input EA,
output [7:0] QA,
output [7:0] Dout
    ); 

LS377 u0(
.CLK ( CLK ),
.EN ( IA ),
.D ( DinA ),
.Q ( QA ));

LS244 u1(
.GAn ( EA ),
.GBn ( EA ),
.A ( QA[3:0] ),
.B ( QA[7:4] ),
.YA ( Dout[3:0] ),
.YB ( Dout[7:4] ));
endmodule
