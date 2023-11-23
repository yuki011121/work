`timescale 1ns / 1ps

module ALU(
input CLK,
input ISUM, 
input ISUB, 
input IAND,
input IOR,
input ISHL,
input IXOR,
input EALU, 
input [7:0] DinA,
input [7:0] Din,
output [7:0] Dsrin,
output [7:0] Dsrout,
output wire [7:0] Dout
);
reg [7:0] QF;
assign Dsrin = QF;
always @ ( * ) begin
 if ( ISUM == 0 ) QF <= DinA+Din;
 else if ( ISUB == 0 ) QF <= DinA-Din;
 else if(IAND == 0) QF <= DinA&Din;
 else if(IOR == 0) QF <= DinA|Din;
 else if(ISHL == 0) QF <= DinA<<1;
 else if(IXOR == 0) QF <= DinA^Din;
 else QF<=QF;
end

LS377 u0(
.CLK ( CLK ),
.EN ( ISUM&ISUB&IAND&IOR&ISHL&IXOR),
.D ( Dsrin ),
.Q ( Dsrout ));
LS244 u1(
.GAn ( EALU ),
.GBn ( EALU ),
.A ( Dsrout[3:0] ),
.B ( Dsrout[7:4] ),
.YA ( Dout[3:0] ),
.YB ( Dout[7:4] ));


endmodule
