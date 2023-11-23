
module div1hz(
 input I_CLK,
 input Rst,
 output reg O_CLK
     );
      parameter k=49999999; //�ڿ��������������
       //parameter k=4999; //����ʱ�����
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