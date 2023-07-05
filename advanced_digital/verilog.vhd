module fulladder(a, b, cin, sum, cout);
input a, b, cin;
output sum, cout;
wire s1, c1, c2;
XOR x1(s1, a, b);
XOR x2(sum, s1, cin);
AND a1(c1, s1, cin);
AND a2(c2, a, b);
OR o1(cout, c1, c2);
endmodule



module irregularCounter(clk, reset, count);
input clk, reset;
output [3:0] count;
reg [3:0] count;
always @(posedge clk or posedge reset)
begin
if (reset)
count <= 4'b0000;
else
count <= count + 1;
end
endmodule

module primenumbercounter(clk, reset, count);
input clk, reset;
output [3:0] count;
reg [3:0] count;
always @(posedge clk or posedge reset)
begin
if (reset)
count <= 4'b0000;
else
count <= count + 1;
end
endmodule
