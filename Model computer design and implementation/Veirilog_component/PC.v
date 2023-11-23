module PC(
input CLK,
input CLRn,
input IPC,
output wire [3:0] Q
 );
wire LDn;
assign LDn=~(Q[3]&Q[2]&Q[1]&~Q[0]&IPC);


LS161 pc_161(
.CLK(CLK),
.CLRn(CLRn),
.LDn(LDn),
.ENP(1'b1),
.ENT(IPC),
.D(4'b0000),
.Q(Q)
);
endmodule
