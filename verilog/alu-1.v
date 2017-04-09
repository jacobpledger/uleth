module cpu(out[3:0], a[3:0], b[3:0],s2,s1,s0);
	output [3:0]out;
	input [3:0] a,b;
	input s2, s1, s0;
	
	assign out = s2 ? (s1 ? (s0 ? (a+b) : (a-b)) : (s0 ? (a+b) : (a-b))) : (s1 ? (s0 ? (~a) : (a^b)) : (s0 ? (a|b) : (a&b)));

	//000:and
	//001:or
	//010:xor
	//011:not
	//100:sub
	//101:add
endmodule

module stimulus;
	reg S2,S1,S0;
	reg [3:0]A,B;
	wire [3:0] OUT;
	cpu mycpu(OUT,A,B,S2,S1,S0);
	initial
		begin
			$monitor($time, " OUT=%b", OUT);
		end
	initial
		begin
		#0 A=4'b0110; B=4'b0011;
		$display("inputs: A=%b, B=%b ",A,B);
		
		#10 S2=1'b0; S1=1'b0; S0=1'b0; //output: 0010
		$display("%b AND %b",A,B);
		
		#10 S2=1'b0; S1=1'b0; S0=1'b1; //output: 0111
		$display("%b OR %b ",A,B);
		
		#10 S2=1'b0; S1=1'b1; S0=1'b0; //output: 0101
		$display("%b XOR %b ",A,B);
		
		#10 S2=1'b0; S1=1'b1; S0=1'b1; //output: 1001
		$display("NOT %b ",A);
		
		#10 S2=1'b1; S1=1'b0; S0=1'b0; //output: 0011
		$display("%b minus %b ",A,B);
		
		#10 S2=1'b1; S1=1'b0; S0=1'b1; //output: 1001
		$display("%b plus %b ",A,B);
		end
endmodule
