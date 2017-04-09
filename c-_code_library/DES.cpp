//Jacob Pledger
//001136676
//Assignment 1
/*
 CS 3730 
 Assignment 1  
 
 Implement the DES algorithm. 
 Let the user input the key and plaintext. (100 marks) 
 
 You can use any language to implement it.
 Both encryption and decryption are required. 
 
 
 
 Key and Plaintext are hexadecimal numbers. 
 
 Output the following values (Binary numbers) for each round: 
 
 E(R_(i-1)), K_i, E(R_(i-1_) XOR K_i, S-box output, f(R_(i-1), K_i), L_i, R_i  
 
 Make a pause for each round output.  
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <bitset>
using namespace std;

//Note quite working right, not sure what the problem is.

//Necessary Tables

//initial permutation of 64-bit input block
int IP[64] = {
    58,	50,	42,	34,	26,	18,	10,	2,
    60,	52,	44,	36,	28,	20,	12,	4,
    62,	54,	46,	38,	30,	22,	14,	6,
    64,	56,	48,	40,	32,	24,	16,	8,
    57,	49,	41,	33,	25,	17,	9,	1,
    59,	51,	43,	35,	27,	19,	11,	3,
    61,	53,	45,	37,	29,	21,	13,	5,
    63,	55,	47,	39,	31,	23,	15,	7};

//final permutation, IP inverse
int FP[64] = {
    40,	8,	48,	16,	56,	24,	64,	32,
    39,	7,	47,	15,	55,	23,	63,	31,
    38,	6,	46,	14,	54,	22,	62,	30,
    37,	5,	45,	13,	53,	21,	61,	29,
    36,	4,	44,	12,	52,	20,	60,	28,
    35,	3,	43,	11,	51,	19,	59,	27,
    34,	2,	42,	10,	50,	18,	58,	26,
    33,	1,	41,	9,	49,	17,	57,	25};

//Expand right input half to 48 bits
int E[48] = {
    32,	1,	2,	3,	4,	5,
    4,	5,	6,	7,	8,	9,
    8,	9,	10,	11,	12,	13,
    12,	13,	14,	15,	16,	17,
    16,	17,	18,	19,	20,	21,
    20,	21,	22,	23,	24,	25,
    24,	25,	26,	27,	28,	29,
    28,	29,	30,	31,	32,	1};

int P[32] = {
    16,	7,	20,	21,	29,	12,	28,	17,
    1,	15,	23,	26,	5,	18,	31,	10,
    2,	8,	24,	14,	32,	27,	3,	9,
    19,	13,	30,	6,	22,	11,	4,	25};

int PC1L[28] = {
    57,	49,	41,	33,	25,	17,	9,
    1,	58,	50,	42,	34,	26,	18,
    10,	2,	59,	51,	43,	35,	27,
    19,	11,	3,	60,	52,	44,	36};

int PC1R[28] = {
    63,	55,	47,	39,	31,	23,	15,
    7,	62,	54,	46,	38,	30,	22,
    14,	6,	61,	53,	45,	37,	29,
    21,	13,	5,	28,	20,	12,	4};

int PC2[48] = {
    14,	17,	11,	24,	1,	5,	3,	28,
    15,	6,	21,	10,	23,	19,	12,	4,
    26,	8,	16,	7,	27,	20,	13,	2,
    41,	52,	31,	37,	47,	55,	30,	40,
    51,	45,	33,	48,	44,	49,	39,	56,
    34,	53,	46,	42,	50,	36,	29,	32};

int S1[64] = {
    14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
    0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
    4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
	15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13};

int S2[64] = {
    15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
    3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
    0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
    13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9};

int S3[64] = {
    10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
    13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
    13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
    1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12};

int S4[64] = {
    7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
    13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
    10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
    3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14};

int S5[64] = {
    2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
    14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
    4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
    11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3};

int S6[64] = {
    12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
    10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
    9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
    4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13};

int S7[64] = {
    4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
    13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
    1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
    6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12};

int S8[64] = {
    13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
    1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
    7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
    2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11};

int ROUND[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

//function prototpes (I'm tired of looking at warnings in xcode)
//I decided to pass outputs everything by reference, mostly for neatness,
//but it also mimics HDL. The first argument is the output, and
//subsequent arguments are inputs

//I/O stuff
void GetInput(string& infilename, string& outfilename, int& key);
void OpenInputFile(ifstream& infile, const string& filename);
void OpenOutputFile(ofstream& outfile, const string& filename);

//Key permutations
void PermutedChoice1(bitset<56> &permuted_key, const bitset<64>& key);
void LeftCircShift(bitset<56> &key, const unsigned int r);
void PermutedChoice2(bitset<48> &pkey, const bitset<56> &key);

void InitialPermutation(bitset<64> &block);
void Expand(bitset<48>& expanded_block, const bitset<32>& input_block);

//S-boxes
void Split(bitset<6> &out, const bitset<48> &in, const unsigned int pos);
void Combine(bitset<32> &out, const bitset<4> &in, const unsigned int pos);
bitset<4> S_Box(bitset<6> sel, const unsigned int box_num);
void Substitution_Boxes(bitset<32> &out, bitset<48> &in);

void Swap32(bitset<64> &block, const bitset<32> &lblock, const bitset<32> &rblock);
void Permute(bitset<32> &block);
void InversePermute(bitset<64> &block);

int main(int argc, char* argv[])
{    
    //file info
    string infilename = "";
    string outfilename = "";
    ifstream infile;
    ofstream outfile;

    //Keys
    int decimal_key = 0;
    bitset<56> permuted_key1; //key after PC1
    bitset<48> permuted_key2; //key after PC2
    
    bitset<48> eblock; //expanded block
    bitset<32> rblock; //right half-block
    bitset<32> lblock; //left half-block
    bitset<32> fblock; //final block
    
    GetInput(infilename, outfilename, decimal_key);
    bitset<64> binary_key(decimal_key); //initial key
    cout << "decimal key: " << decimal_key << endl;
    cout << "binary key: " << binary_key << endl;
    cin.ignore(1);
    
    OpenInputFile(infile, infilename);
    OpenOutputFile(outfile, outfilename);
    
    while (!infile.eof())
    {
        unsigned long x;
        infile >> hex >> x;
        bitset<64> block(x);
        
        InitialPermutation(block);
        PermutedChoice1(permuted_key1, binary_key);
        
        for (unsigned int i = 0; i < 32; ++i)
        {
            rblock[i] = block[i];
            lblock[i] = block[i+32];
        }
        
        //Begin 16 Rounds
        for (unsigned int r = 0; r < 16; ++r)
        {
            LeftCircShift(permuted_key1, r);
            cout << "Permuted key1: " << permuted_key1 << endl;
            PermutedChoice2(permuted_key2, permuted_key1);

            cout << "Round key:\n";
            cout << permuted_key2 << endl;
            
            cout << "Right half-block for round " << r+1 << ":\n";
            cout << rblock << endl;
            cout << "Left half-block for round " << r+1 << ":\n";
            cout << lblock << endl;
            
            Expand(eblock, rblock);
            eblock = eblock^=permuted_key2; //xor
            
            cout << "Encrypted right half-block:\n";
            cout << eblock << endl;
            
            Substitution_Boxes(fblock, eblock);
            Permute(fblock);
            
            cout << "Round " << r+1 << " output:\n";
            cout << fblock << endl;
            cout << "Press enter to continue.\n";
            cin.ignore(1);
            
            fblock = fblock^=lblock;
            lblock = rblock;
            rblock = fblock;
        }
        
        Swap32(block, lblock, rblock);
        InversePermute(block);
        
        unsigned long o = block.to_ulong();
        outfile << hex << o;
    }
    
    infile.close();
    outfile.close();
    
    return 0;
}

void GetInput(string& infilename, string& outfilename, int& key)
{
    cout << "Please enter the input filename: \n";
    cin >> infilename;
    cout << "Please enter the output filename: \n";
    cin >> outfilename;
    cout << "Please enter the initial key: ";
    cin >> hex >> key;
}

void OpenInputFile(ifstream& infile, const string& filename)
{
    infile.open(filename.c_str());
    if (infile.fail())
    {
        cout << "Failed to open input file." << endl;
        exit(1);
    }
}

void OpenOutputFile(ofstream& outfile, const string& filename)
{
    outfile.open(filename.c_str());
    if (outfile.fail())
    {
        cout << "Failed to create output file." << endl;
        exit(1);
    }
}

//Permutes the 64 bit key into a shuffled, 56 bit key.
void PermutedChoice1(bitset<56> &permuted_key, const bitset<64>& key)
{
    int loc;
    //Right side
    for (unsigned int i = 0; i < 28; ++i)
    {
        loc = PC1R[i];
        permuted_key[i] = key[loc];
    }
    
    //Left side
    for (unsigned int i = 0; i < 28; ++i)
    {
        loc = PC1L[i];
        permuted_key[i+28] = key[loc];
    }
}

//Left circular shift of both halves of the permuted key
void LeftCircShift(bitset<56> &key, const unsigned int r)
{
    bitset<28> lhs;
    bitset<28> rhs;
    for (unsigned int i = 0; i < 28; ++i)
    {
        lhs[i] = key[i+28];
        rhs[i] = key[i];
    }
    
    for (unsigned int i = 0; i < ROUND[r]; ++i)
    {
        bool ltemp = lhs[27];
        bool rtemp = rhs[27];
        lhs<<1;
        rhs<<1;
        lhs[0] = ltemp;
        rhs[0] = rtemp;
    }
    
    for (unsigned int i = 0; i < 28; ++i)
    {
        key[i+28] = lhs[i];
        key[i] = rhs[i];
    }
    
    for (unsigned int i = 0; i < 28; ++i)
    {
        key[i+28] = lhs[i];
        key[i] = rhs[i];
    }
    
}

//Further permutes the key using PC2 table
void PermutedChoice2(bitset<48> &pkey, const bitset<56> &key)
{
    int loc;
    for (unsigned int i = 0; i < 48; ++i)
    {
        loc = PC2[i];
        pkey[i] = key[loc];
    }
}

//permute the initial 64 bit input block
void InitialPermutation(bitset<64> &block)
{
    bitset<64> temp(block.to_ulong());
    int loc;
    for (unsigned int i = 0; i < 64; ++i)
    {
        loc = IP[i];
        temp[i] = block[loc];
    }
    block = temp;
}

//Expand the right half block of input to 48 bits
void Expand(bitset<48> &expanded_block, const bitset<32> &input_block)
{
    int loc;
    for (unsigned int i = 0; i < 48; ++i)
    {
        loc = E[i];
        expanded_block[i] = input_block[loc];
    }
}

bitset<4> S_Box(bitset<6> sel, const unsigned int box_num)
{
    bitset<2> row;
    row[0] = sel[0];
    row[1] = sel[5];
    
    bitset<4> col;
    for (unsigned int i = 1; i < 5; ++i)
    {
        col[i-1] = sel[i];
    }
    
    unsigned long pos = 16*row.to_ulong() + col.to_ulong();
    int num;
    
    switch (box_num) {
        case 1:
            num = S1[pos];
            break;
        case 2:
            num = S2[pos];
            break;
        case 3:
            num = S3[pos];
            break;
        case 4:
            num = S4[pos];
            break;
        case 5:
            num = S5[pos];
            break;
        case 6:
            num = S6[pos];
            break;
        case 7:
            num = S7[pos];
            break;
        case 8:
            num = S8[pos];
            break;
        default:
            break;
    }
    bitset<4> out(num);
    
    cout << "S-box " << box_num << " output: ";
    cout << out << endl;
    return out;
}

void Split(bitset<6> &out, const bitset<48> &in, const unsigned int pos)
{
    for (unsigned int i = 0; i < 6; ++i)
    {
        out[i] = in[i+pos];
    }
}

void Combine(bitset<32> &out, const bitset<4> &in, const unsigned int pos)
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        out[i+pos] = in[i];
    }
}

void Substitution_Boxes(bitset<32> &out, bitset<48> &in)
{
    bitset<6> in1,in2,in3,in4,in5,in6,in7,in8;
    
    Split(in1, in, 0);
    Split(in2, in, 6);
    Split(in3, in, 12);
    Split(in4, in, 18);
    Split(in5, in, 24);
    Split(in6, in, 30);
    Split(in7, in, 36);
    Split(in8, in, 42);
    
    Combine(out, S_Box(in1,1),0);
    Combine(out, S_Box(in2,2),4);
    Combine(out, S_Box(in3,3),8);
    Combine(out, S_Box(in4,4),12);
    Combine(out, S_Box(in5,5),16);
    Combine(out, S_Box(in6,6),20);
    Combine(out, S_Box(in7,7),24);
    Combine(out, S_Box(in8,8),28);
    
    cout << "S-box Output:\n";
    cout << out << endl;
}

void Permute(bitset<32> &block)
{
    bitset<32> temp(block.to_ulong());
    int loc;
    for (unsigned int i = 0; i < 32; ++i)
    {
        loc = P[i];
        temp[i] = block[loc];
    }
    block = temp;
}

//Swap the left and right blocks
void Swap32(bitset<64> &block, const bitset<32> &lblock, const bitset<32> &rblock)
{
    for (unsigned int i = 0; i < 32; ++i)
    {
        block[i] = rblock[i];
        block[i+32] = lblock[i+32];
    }
}

//Reverse the initial permutation
void InversePermute(bitset<64> &block)
{
    bitset<64> temp(block.to_ulong());
    int loc;
    for (unsigned int i = 0; i < 64; ++i)
    {
        loc = FP[i];
        temp[i] = block[loc];
    }
    block = temp;
}