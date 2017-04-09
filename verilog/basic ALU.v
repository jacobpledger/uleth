//Jacob Pledger
//001136676

module mux(out, i0, i1, i2, i3, s1, s0);
	output out;
	input i0, i1, i2, i3;
	input s1, s0;
	wire s1n, s0n;
	wire c0, c1, c2, c3;
	not(s1n, s1);
	not(s0n, s0);
	and(y0, i0, s1n, s0n);
	and(y1, i1, s1n, s0);
	and(y2, i2, s1, s0n);
	and(y3, i3, s1, s0);
	or(out, y0, y1, y2, y3);
endmodule

module alu(out[3:0], a[3:0], b[3:0],s1,s0);
	output [3:0] out;
	input [3:0] a,b;
	input s1,s0;
	wire [3:0] c0, c1, c2, c3;
	
	and(c0[0],a[0],b[0]);
	and(c0[1],a[1],b[1]);
	and(c0[2],a[2],b[2]);
	and(c0[3],a[3],b[3]);
	
	or(c1[0],a[0],b[0]);
	or(c1[1],a[1],b[1]);
	or(c1[2],a[2],b[2]);
	or(c1[3],a[3],b[3]);
	
	xor(c2[0],a[0],b[0]);
	xor(c2[1],a[1],b[1]);
	xor(c2[2],a[2],b[2]);
	xor(c2[3],a[3],b[3]);
	
	not(c3[0],a[0]);
	not(c3[1],a[1]);
	not(c3[2],a[2]);
	not(c3[3],a[3]);
	
	mux mux0(out[0],c0[0],c1[0],c2[0],c3[0],s1,s0);
	mux mux1(out[1],c0[1],c1[1],c2[1],c3[1],s1,s0);
	mux mux2(out[2],c0[2],c1[2],c2[2],c3[2],s1,s0);
	mux mux3(out[3],c0[3],c1[3],c2[3],c3[3],s1,s0);
endmodule

module stimulus;
	wire [3:0] OUT;
	reg S1, S0;
	reg [3:0] A,B;
	alu myALU(OUT,A,B,S1,S0);
	initial
	begin
		$monitor($time, "A=%b, B=%b, S1=%b, S0=%b, OUT=%b", A, B, S1, S0, OUT);
	end
	initial
	begin
	#0 A=4'b0011; B=4'b0100; S1=1'b0; S0=1'b0;
	#5 A=4'b0011; B=4'b0100; S1=1'b0; S0=1'b1;
	#5 A=4'b0011; B=4'b0100; S1=1'b1; S0=1'b0;
	#5 A=4'b0011; B=4'b0100; S1=1'b1; S0=1'b1;
	//outputs should be:
	//0000
	//0111
	//0111
	//1100
	end
endmodule
