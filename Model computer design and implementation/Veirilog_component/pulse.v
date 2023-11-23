`timescale 1ns / 1ps

module pulse(
input wire CLK,
input wire CLRn,
output wire T0,T1,T2,T3,T4,T5,T6,T7
    );
reg DFF0,DFF1,DFF2,DFF3,DFF4,DFF5,DFF6,DFF7;
assign T0 = DFF0;
assign T1 = DFF1;
assign T2 = DFF2;
assign T3 = DFF3;
assign T4 = DFF4;
assign T5 = DFF5;
assign T6 = DFF6;
assign T7 = DFF7;

always @ (posedge CLK or negedge CLRn)
begin
if(!CLRn) begin
    DFF0 <= 1;
    DFF1 <= 0;
    DFF2 <= 0;
    DFF3 <= 0;
    DFF4 <= 0;
    DFF5 <= 0;
    DFF6 <= 0;
	 DFF7 <= 0;
end
else begin
    DFF0 <= DFF7;
    DFF1 <= DFF0;
    DFF2 <= DFF1;
    DFF3 <= DFF2;
    DFF4 <= DFF3;
    DFF5 <= DFF4;
    DFF6 <= DFF5;
	DFF7 <= DFF6;
end
end
endmodule