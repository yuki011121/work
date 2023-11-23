`timescale 1ns / 1ps
module LS377(
input CLK,
input [7:0] D,
input EN,
output reg [7:0] Q
    );
wire	SYNTHESIZED_WIRE_8;
always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[7] <= D[7];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[6] <= D[6];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[4] <= D[4];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[5] <= D[5];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[0] <= D[0];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[1] <= D[1];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[2] <= D[2];
	end
end


always@(posedge CLK)
begin
if (SYNTHESIZED_WIRE_8)
	begin
	Q[3] <= D[3];
	end
end

assign	SYNTHESIZED_WIRE_8 =  ~EN;


endmodule
