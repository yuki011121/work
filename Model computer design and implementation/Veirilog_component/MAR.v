`timescale 1ns / 1ps

module MAR(
    input wire IMAR,
    input wire CLK,
    input wire [3:0] D,
    output wire [3:0] ABUS
    );
reg [3:0] Qout;
always  @ ( posedge CLK )
begin
    if(~IMAR)
    begin
        Qout<=D;
    end
end
assign ABUS=Qout;
endmodule

