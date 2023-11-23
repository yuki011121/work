module dr_tb();
    wire [7:0]Q;
    reg CLK;
    reg [7:0]D;
    reg IDR;
    reg EDR;
    DR DUP (
            .CLK(CLK),
            .D(D),
            .EDR(EDR),
            .IDR(IDR),
            .Q(Q)
        );
    initial begin
        CLK = 1'b0;
         IDR <= 1'b0;
         EDR <= 1'b0;
         D <= 8'b0000_0101;
    end

    always 
    begin
         #40  D <= 8'b0000_0101;
         #40 D <= 8'b1111_1110;
         #40 D <= 8'b0000_0100;
         #40 D <= 8'b1111_1101;
         #40 D <= 8'b0000_0011;
    end
    always #20 CLK <=~CLK;
    always #60 IDR <=~IDR;
    always #120 EDR <=~EDR;

endmodule 
