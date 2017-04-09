module pfa(output s,g,p, input a,b,c);
	xor(p,a,b);
	and(g,a,b);
	xor(s,p,c);
endmodule

module fa(output [3:0] s,g,p, input [3:0] a,b, input[3:0] c);
	pfa adder0(s[0],p[0],g[0],a[0],b[0],c[0]);
	pfa adder1(s[1],p[1],g[1],a[1],b[1],c[1]);
	pfa adder2(s[2],p[2],g[2],a[2],b[2],c[2]);
	pfa adder3(s[3],p[3],g[3],a[3],b[3],c[3]);
endmodule

module cl(output [3:0] p_out, g_out, c_out, input [3:0] p,g, input c);
	wire g0,g1,g2;
	wire l0,l1,l2;
	wire m0,m1;
	wire r0;
	
	//p_out
	and(p_out,p[3],p[2],p[1],p[0]);
	
	//g_out
	and(g0,p[3],p[2],p[1],g[0]);
	and(g1,p[3],p[2],g[1]);
	and(g2,p[3],g[2]);
	or(g_out,g0,g1,g2,g[3]);
	
	//c[3]
	and(l0,p[2],p[1],p[0],c);
	and(l1,p[2],p[1],g[0]);
	and(l2,p[2],g[1]);
	or(c_out[3],l0,l1,l2,g[2]);
	
	//c[2]
	and(m0,p[1],p[0],c);
	and(m1,p[1],g[0]);
	or(c_out[2],m0,m1,g[1]);
	
	//c[1]
	and(r0,p[0],c);
	or(c_out[1],r0,g[0]);
	
	//c[0]
	or(c[0],c,0);
endmodule

module cla(output [3:0] s_out, p_out, g_out, input [3:0] a_in,b_in, input c_in);
	wire [3:0] c;
	wire [3:0] g;
	wire [3:0] p;
	
	fa full_adder(s_out,g,p, a_in,b_in,c);
	cl carry_lookahead(p_out,g_out,c, p,g,c_in);
endmodule
