module clk_tb();
    wire O_CLK;
    reg I_CLK;
    reg Rst;
    div1hz DUP (
            .I_CLK(I_CLK),
            .Rst(Rst),
            .O_CLK(O_CLK)
        );
    initial begin
       Rst=1'b0; 
       I_CLK=1'b0;
       #50   Rst=1'b1; 
    end
    always    #20  I_CLK = ~I_CLK;

endmodule 
