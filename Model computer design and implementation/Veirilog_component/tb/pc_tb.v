module pc_tb();
    reg CLK,CLRn,IPC;
    wire [3:0]Q;
    PC DUT (
            .CLK(CLK),
            .CLRn(CLRn),
            .IPC(IPC),
            .Q(Q)
        );
    initial begin
    CLK=1'b0;
    CLRn=1'b1;
    IPC=1'b1;
    end
    always #10 CLK = ~CLK;
    initial begin
    #10    CLRn=1'b0; 
    #10    CLRn=1'b1;
    end
    always #20 IPC = ~IPC;
    initial begin
    #2000 $stop;
    end

endmodule 
