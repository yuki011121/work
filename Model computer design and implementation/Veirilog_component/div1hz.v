
module div1hz(
 input I_CLK,
 input Rst,
 output reg O_CLK
     );
      parameter k=49999999; //在开发板运行用这个
       //parameter k=4999; //仿真时用这个
       reg [31:0]i;
      always @(posedge I_CLK or negedge Rst)
  begin
      if(!Rst)
       begin
       O_CLK=0;
       i=0;
      end
      else
         begin
         i=i+1;
         if(i==k)
         begin
         O_CLK=~O_CLK;
         i=0;
         end
       end
 end
endmodule