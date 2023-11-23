//74LS373
module LS373(
input wire OEn,
input wire LE,
input wire [7:0] D,
output wire [7:0] Q
);
	wire OE;
	reg QF0,QF1,QF2,QF3,QF4,QF5,QF6,QF7;
	assign OE = ~OEn;
	assign Q = OE ? {QF7,QF6,QF5,QF4,QF3,QF2,QF1,QF0}: 8'b zzzz_zzzz;
	always @ ( LE or D ) 
	begin
		if ( LE )
			{QF7,QF6,QF5,QF4,QF3,QF2,QF1,QF0} <= D;
	end
endmodule