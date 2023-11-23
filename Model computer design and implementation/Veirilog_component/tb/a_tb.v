module a_tb();
    reg CLK,IA,EA;
    reg [7:0] DinA;
    wire [7:0]QA;
    wire [7:0]Dout;
    A DUT (
            .CLK(CLK),
            .IA(IA),
            .EA(EA),
            .DinA(DinA),
            .QA(QA),
            .Dout(Dout)
        );
    initial begin
    CLK=1'b0;
    IA=1'b0;
    EA=1'b0;
#110 DinA <= 8'b11111011;
#110 DinA <= 8'b00000011;
#110 DinA <= 8'b11111011;
#110 DinA <= 8'b11111101;
#110 DinA <= 8'b11011011;
#110 DinA <= 8'b11110111;
    end
    always #20 CLK = ~CLK;
    always #80 IA = ~IA;
    always #100 EA = ~EA;

    initial begin
    #2000 $stop;
    end

endmodule 
