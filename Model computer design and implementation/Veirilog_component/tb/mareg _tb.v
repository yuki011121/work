`timescale 1ns / 1ps
module mareg_tb();
    wire [3:0]ABUS;
    reg CLK;
    reg [3:0]D;
    reg IMAR;
    MAR DUP (
            .D(D),
            .CLK(CLK),
            .IMAR(IMAR),
            .ABUS(ABUS)
        );
    initial begin
    CLK=1'b0;
    D=4'b1001;
    IMAR=1'b0;
    end
    always  #20 CLK = ~CLK;
    always 
    begin
        #40        D <= 4'b1001;
        #40        D <= 4'b1010;
        #40        D <= 4'b0011;
        #40        D <= 4'b1111;
        #40        D <= 4'b0101;
    end
endmodule 
