`timescale 1ns / 1ps


module DR(
input wire CLK,
input wire IDR,
input wire EDR,
input wire [7:0] D,
output wire [7:0] Q
    );
    wire LE;
    assign LE=CLK&IDR;
    LS373 u0(
    .OEn(EDR),
    .LE(LE),
    .D(D),
    .Q(Q)
    );
endmodule