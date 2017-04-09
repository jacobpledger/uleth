module fulladd(sum, c_out, a, b, c_in);
	output sum, c_out;
	input a, b, c_in;
	wire s1, c1, c2;
	xor(s1, a, b);
	and(c1, a, b);
	xor(sum, s1, c_in);
	and(c2, s1, c_in);
	or(c_out, c2, c1);
endmodule

module fulladd4(sum, c_out, a, b, c_in);
	output[3:0] sum;
	output c_out;
	input[3:0] a, b;
	input c_in;
	wire c1, c2, c3;
	fulladd fa0(sum[0], c1, a[0], b[0], c_in);
	fulladd fa1(sum[1], c2, a[1], b[1], c1);
	fulladd fa2(sum[2], c3, a[2], b[2], c2);
	fulladd fa3(sum[3], c_out, a[3], b[3], c3);
endmodule

module stimulus;
	reg [3:0] A, B;
	reg C_IN;
	wire[3:0] sum;
	wire C_OUT;
	fulladd4 FA4(sum, C_OUT, A, B, C_IN);
	initial
		begin
		$monitor($time, "A=%b, B=%b, C_IN=%b, ---, C_OUT=%b, sum = %b\n", A, B, C_IN, C_OUT, sum);
		end
	initial
		begin
		A=4'd0; B=4'd0; C_IN = 1'b0;
		#5 A=4'd3; B=4'd4;
		#5 A=4'd4; B=4'd5;
		#5 A=4'd15; B=4'd1;
		end
endmodule
