//model showing how to connect a 6 bit full adder to a 7 to 1 mux

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

module fulladd6(sum, c_out, a, b, c_in);
	output[5:0] sum;
	output c_out;
	input[5:0] a, b;
	input c_in;
	wire c0, c1, c2, c3, c4, c5;
	fulladd fa0(sum[0], c1, a[0], b[0], c_in);
	fulladd fa1(sum[1], c2, a[1], b[1], c1);
	fulladd fa2(sum[2], c3, a[2], b[2], c2);
	fulladd fa3(sum[3], c4, a[3], b[3], c3);
	fulladd fa4(sum[4], c5, a[4], b[4], c4);
	fulladd fa5(sum[5], c_out, a[5], b[5], c5);
endmodule

module mux(out, i0, i1, i2, i3, i4, i5, i6, s2, s1, s0);
	output out;
	input i0, i1, i2, i3, i4, i5, i6;
	input s2, s1, s0;
	wire s2n, s1n, s0n;
	wire c0, c1, c2, c3, c4, c5, c6;
	not(s2n, s2);
	not(s1n, s1);
	not(s0n, s0);
	and(c0, i0, s2n, s1n, s0n);
	and(c1, i1, s2n, s1n, s0);
	and(c2, i2, s2n, s1, s0n);
	and(c3, i3, s2n, s1, s0);
	and(c4, i4, s2, s1n, s0n);
	and(c5, i5, s2, s1n, s0);
	and(c6, i6, s2, s1, s0n);
	or(out, c0, c1, c2, c3, c4, c5, c6);
endmodule

module stimulus;
	reg [5:0] A, B;
	reg C_IN;
	wire[5:0] SUM;
	wire C_OUT;
	fulladd6 FA(SUM, C_OUT, A, B, C_IN);
	
	wire OUT;
	reg [2:0] ENABLE;
	mux MYMUX(OUT, SUM[0], SUM[1], SUM[2], SUM[3], SUM[4],SUM[5], C_OUT, ENABLE[2], ENABLE[1], ENABLE[0]);
	initial
		begin
		$monitor($time, "A=%b, B=%b, C_IN=%b, ---, C_OUT=%b, SUM = %b\n, ENABLE = %b, OUT = %b\n", A, B, C_IN, C_OUT, SUM, ENABLE, OUT);
		end
	initial
		begin
			#0 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b000;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b001;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b010;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b011;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b100;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b101;
			#5 A=6'd15; B=6'd12; C_IN = 1'b0; ENABLE = 3'b110;
		end
endmodule
