module pulse_tb();
    wire T0,T1,T2,T3,T4,T5,T6,T7;
    reg CLK;
    reg CLRn;
    pulse DUP (
            .CLK(CLK),
            .CLRn(CLRn),
            .T0(T0),
            .T1(T1),
            .T2(T2),
            .T3(T3),
            .T4(T4),
            .T5(T5),
            .T6(T6),
            .T7(T7)
        );
    initial begin
       CLRn=1'b0; 
       CLK=1'b0;
       #50   CLRn=1'b1; 
    end
    always    #20  CLK = ~CLK;

endmodule 
