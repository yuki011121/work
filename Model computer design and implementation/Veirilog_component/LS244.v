module LS244(
input wire	GAn,
input wire [3:0] A,
input wire	GBn,
input wire [3:0] B,
output wire [3:0] YA,
output wire	[3:0] YB
);

wire	Q;
wire	D;
assign	Q =  ~GAn;
assign	D =  ~GBn;
assign	YA[0] = Q ? A[0] : 1'bz;
assign	YA[1] = Q ? A[1] : 1'bz;
assign	YA[2] = Q ? A[2] : 1'bz;
assign	YA[3] = Q ? A[3] : 1'bz;
assign	YB[0] = D ? B[0] : 1'bz;
assign	YB[1] = D ? B[1] : 1'bz;
assign	YB[2] = D ? B[2] : 1'bz;
assign	YB[3] = D ? B[3] : 1'bz;
endmodule