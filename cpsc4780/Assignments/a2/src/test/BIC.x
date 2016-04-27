#define VERSION_NUMBER 1

struct operands
{
	int x;
	int y;
};

program BIC {
   version BIC_VERSION {
   
   int ADD(operands) = 1;
   int SUB(operands) = 2;
   int MULT(operands) = 3;
   int DIV(operands) = 4;
                               
   } = VERSION_NUMBER;
} = 555555555;