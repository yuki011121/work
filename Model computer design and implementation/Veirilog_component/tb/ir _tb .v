`timescale 1ns/1ps
module ir_tb();
    reg CLK,IIR;
    reg [7:0]D;
    wire HALT,SUB,ADD,OR,AND,SHL,XOR,LD;

   IR DUT (
            .CLK(CLK),
            .D(D),
            .IIR(IIR),
            .HALT(HALT),
            .LD(LD),
            .ADD(ADD),
            .SUB(SUB),
            .AND(AND),
            .XOR(XOR),
            .OR(OR),
            .SHL(SHL)
            );
initial begin
IIR = 1'b0;
D = 8'b1111_1111;
CLK = 1'b0;
end
always #10 CLK = ~ CLK;
initial begin
#20 D = 8'b1111_1110;
#20 D = 8'b1111_1101;
#20 D = 8'b1111_1100;
#20 D = 8'b1111_1011;
#20 D = 8'b1111_1001;
#20 D = 8'b1111_0010;
#20 D = 8'b1111_1000;

#20 IIR = 1'b1;
#20 D = 8'b1111_1110;
#20 D = 8'b1111_1101;
#20 D = 8'b1111_1100;
#20 D = 8'b1111_1011;
#20 D = 8'b1111_1001;
#20 D = 8'b1111_0010;

#60 $stop;
end
endmodule
