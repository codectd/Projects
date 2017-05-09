#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;
int REG[32];
int MEM[1<<20];
int LO, HI, PC, nPC;

const int AND_MASK      = 0b11111100000000000000000011111111;
const int AND_INSTR     = 0b00000000000000000000000000100100;
const int ADD_MASK      = 0b11111100000000000000000011111111;
const int ADD_INSTR     = 0b00000000000000000000000000100000;
const int ADDI_MASK     = 0b11111100000000000000000000000000;
const int ADDI_INSTR    = 0b00100000000000000000000000000000;
const int ADDIU_MASK    = 0b11111100000000000000000000000000;
const int ADDIU_INSTR   = 0b00100100000000000000000000000000;
const int ADDU_MASK     = 0b11111100000000000000000001111111;
const int ADDU_INSTR    = 0b00000000000000000000000000100001;
const int ANDI_MASK     = 0b11111100000000000000000000000000;
const int ANDI_INSTR    = 0b00110000000000000000000000000000;
const int BEQ_MASK      = 0b11111100000000000000000000000000;
const int BEQ_INSTR     = 0b00010000000000000000000000000000;
const int BGEZ_MASK     = 0b11111100000111110000000000000000;
const int BGEZ_INSTR    = 0b00000100000000010000000000000000;
const int BGEZAL_MASK   = 0b11111100000111110000000000000000;
const int BGEZAL_INSTR  = 0b00000100000100010000000000000000;
const int BGTZ_MASK     = 0b11111100000111110000000000000000;
const int BGTZ_INSTR    = 0b00011100000000000000000000000000;
const int BLEZ_MASK     = 0b11111100000111110000000000000000;
const int BLEZ_INSTR    = 0b00011000000000000000000000000000;
const int BLTZ_MASK     = 0b11111100000111110000000000000000;
const int BLTZ_INSTR    = 0b00000100000000000000000000000000;
const int BLTZAL_MASK   = 0b11111100000111110000000000000000;
const int BLTZAL_INSTR  = 0b00000100000111110000000000000000;
const int BNE_MASK      = 0b11111100000000000000000000000000;
const int BNE_INSTR     = 0b00010100000000000000000000000000;
const int DIV_MASK      = 0b11111100000000001111111111111111;
const int DIV_INSTR     = 0b00000000000000000000000000011010;
const int J_MASK        = 0b11111100000000000000000000000000;
const int J_INSTR       = 0b00001000000000000000000000000000;
const int JAL_MASK      = 0b11111100000000000000000000000000;
const int JAL_INSTR     = 0b00001100000000000000000000000000;
const int JR_MASK       = 0b11111100000000111111111111111111;
const int JR_INSTR      = 0b00000000000000000000000000001000;
const int LB_MASK       = 0b11111100000000000000000000000000;
const int LB_INSTR      = 0b10000000000000000000000000000000;
const int LUI_MASK      = 0b11111100000000000000000000000000;
const int LUI_INSTR     = 0b00111100000000000000000000000000;
const int LW_MASK       = 0b11111100000000000000000000000000;
const int LW_INSTR      = 0b10001100000000000000000000000000;
const int MFHI_MASK     = 0b11111111111111110000000011111111;
const int MFHI_INSTR    = 0b00000000000000000000000000010000;
const int MFLO_MASK     = 0b11111111111111110000000011111111;
const int MFLO_INSTR    = 0b00000000000000000000000000010010;
const int MULT_MASK     = 0b11111100000000000001111111111111;
const int MULT_INSTR    = 0b00000000000000000000000000011000;
const int OR_MASK       = 0b11111100000000000001111111111111;
const int OR_INSTR      = 0b00000000000000000000000000010101;
const int ORI_MASK      = 0b11111100000000000000000000000000;
const int ORI_INSTR     = 0b00110100000000000000000000000000;
const int SB_MASK       = 0b11111100000000000001111111111111;
const int SB_INSTR      = 0b10100000000000000000000000000000;
const int SLL_MASK      = 0b11111100000000000000000000111111;
const int SLL_INSTR     = 0b00000000000000000000000000000000;
const int SLLV_MASK     = 0b11111100000000000000000000111111;
const int SLLV_INSTR    = 0b00000000000000000000000000000100;
const int SLT_MASK      = 0b11111100000000000000011111111111;
const int SLT_INSTR     = 0b00000000000000000000000000101010;
const int SLTI_MASK     = 0b11111100000000000000000000000000;
const int SLTI_INSTR    = 0b00101000000000000000000000101010;
const int SLTIU_MASK    = 0b11111100000000000000000000000000;
const int SLTIU_INSTR   = 0b00101100000000000000000000000000;
const int SLTU_MASK     = 0b11111100000000000000011111111111;
const int SLTU_INSTR    = 0b00101100000000000000000000101011;
const int SRA_MASK      = 0b11111100000000000000000000111111;
const int SRA_INSTR     = 0b00000000000000000000000000000011;
const int SRL_MASK      = 0b11111100000000000000000000111111;
const int SRL_INSTR     = 0b00000000000000000000000000000010;
const int SRLV_MASK     = 0b11111100000000000000011111111111;
const int SRLV_INSTR    = 0b00000000000000000000000000000110;
const int SUB_MASK      = 0b11111100000000000000011111111111;
const int SUB_INSTR     = 0b00000000000000000000000000100010;
const int SUBU_MASK     = 0b11111100000000000000011111111111;
const int SUBU_INSTR    = 0b00000000000000000000000000100011;
const int SW_MASK       = 0b11111100000000000000000000000000;
const int SW_INSTR      = 0b10101100000000000000000000000000;
const int SYSCALL_MASK  = 0b11111100000000000000000000111111;
const int SYSCALL_INSTR = 0b00000000000000000000000000001100;
const int XOR_MASK      = 0b11111100000000000000000000111111;
const int XOR_INSTR     = 0b00000000000000000000000000100110;
const int XORI_MASK     = 0b11111100000000000000000000000000;
const int XORI_INSTR    = 0b00111000000000000000000000000000;

void dumpMemory(int startIndex, int endIndex)
{
  int i = 0;
  for (i=startIndex; i < endIndex; i++)
  {
    //printf("%x\n", MEM[i]);
  }

}

void advancePC(int n)
{
  PC = nPC;
  nPC += n;
}

void executeLoop (void)
{
  int D, S, T, H, IMM;
  string ranInput;
  while(true)
  {//write all my INSTRuctions in here
  //cin >> ranInput;
  //cin >> ranInput;
  REG[0] = 0;
  //printf("%x %x\n", PC, MEM[PC/4]);
  int INSTR = MEM[PC/4];
  D = (INSTR >> 11) & 0b11111;
  S = (INSTR >> 21) & 0b11111;
  T = (INSTR >> 16) & 0b11111;
  H = (INSTR >> 11) & 0b11111;
  //printf("### %x %x \n", PC, INSTR);
    if ((INSTR & AND_MASK) == AND_INSTR)//AND case
    {
      //cout << "AND" << endl;
      // $d = $s & $t; advance_pc(4);
      REG[D] = REG[S] & REG[T];
        advancePC(4);
    }
    else if ( (INSTR & ADD_MASK) == ADD_INSTR ){//ADD cases
      //cout << "ADD" << endl;
      REG[D] = REG[S] + REG[T];
        advancePC(4);
    }
    else if ( (INSTR & ADDI_MASK) == ADDI_INSTR ){//ADDI cases
      //cout << " $$$$$$$$" << endl;
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;//Specific for sign extension in addi, addiu, slti, and sltiu
      REG[D] = REG[S] + IMM;
        advancePC(4);
    }
    else if ( (INSTR & ADDIU_MASK) == ADDIU_INSTR ){//ADDIU cases
      //cout << "ADDIU" << endl;
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      REG[T] = REG[S] + IMM;
        advancePC(4);
    }
    else if ( (INSTR & ADDU_MASK) == ADDU_INSTR ){//ADDU cases
      //cout << "ADDU" << endl;
      REG[D] = REG[S] + REG[T];
        advancePC(4);
    }
    else if ( (INSTR & ANDI_MASK) == ANDI_INSTR ){//ANDI cases
      IMM = INSTR & 0b1111111111111111;
      REG[T] = REG[S] & IMM;
        advancePC(4);
    }
    else if ( (INSTR & BEQ_MASK) == BEQ_INSTR ){
      //printf("%x %x %d %d\n", PC, INSTR, REG[S], REG[T]);
      //cout << REG[8] << " " << REG[9] << endl;
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] == REG[T])advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & BGEZ_MASK) == BGEZ_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] >= 0)advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & BGEZAL_MASK) == BGEZAL_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
      {
        IMM = IMM | 0b11111111111111110000000000000000;
      }
      if (REG[S] >= 0)
      {
      REG[31] = PC + 8;
      advancePC(IMM<<2);
      }
      //Use IMM from ADDI in place of offset
      else advancePC(4);

    }
    else if ( (INSTR & BGTZ_MASK) == BGTZ_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] > 0)advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & BLEZ_MASK) == BLEZ_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] <= 0)advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & BLTZ_MASK) == BLTZ_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] < 0)advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & BLTZAL_MASK) == BLTZAL_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
      {
        IMM = IMM | 0b11111111111111110000000000000000;
      }
      if (nPC + 4)
      {
      advancePC(IMM<<2);
      }
      else advancePC(4);
    }
    else if ( (INSTR & BNE_MASK) == BNE_INSTR ){
      IMM = INSTR & 0b1111111111111111;//use for all imm cases? yes
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
        //printf("%x %x\n", PC, INSTR);
        //cout << " " << IMM << " " << REG[S] << " " << REG[T] << endl;
      if (REG[S] != REG[T])advancePC(IMM<<2);
      //Use IMM from ADDI in place of offset
      else advancePC(4);
    }
    else if ( (INSTR & DIV_MASK) == DIV_INSTR ){
        LO =  REG[S] / REG[T];
        HI = REG[S] % REG[T];
        advancePC(4);
    }
    else if ( (INSTR & J_MASK) == J_INSTR ){
      //printf("%x %x\n", PC, INSTR);
      int target = INSTR & 0b1111111111111111111111111;
       (PC = nPC);
       nPC = (PC & 0xf0000000) | (target<<2);//target gets 26 '1' bits
       //printf("%x\n", nPC);
       //cout << "#########" << endl;
    }
    else if ( (INSTR & JAL_MASK) == JAL_INSTR ){
      int target = INSTR & 0b1111111111111111111111111;
       REG[31] = (nPC + 4);
        PC = nPC;
        nPC = (PC & 0xf0000000) | (target << 2);
    }
    else if ( (INSTR & JR_MASK) == JR_INSTR ){
      //printf("%x %x\n", S, REG[S]);
       (PC = nPC);
        nPC = REG[S];
    }
    else if ( (INSTR & LB_MASK) == LB_INSTR ){
      IMM = INSTR & 0b1111111111111111;
       (REG[T] = MEM[REG[S] + IMM]);
        advancePC(4);
    }
    else if ( (INSTR & LUI_MASK) == LUI_INSTR ){
      //cout << "LUI" << endl;
      IMM = INSTR & 0b1111111111111111;
      //if (((IMM >> 15) & 1) == 1)
        //IMM = IMM | 0b11111111111111110000000000000000;
       (REG[T] = (IMM << 16));
       //cout << T << " " << REG[T] << " " << IMM << endl;
       //printf("%x\n", INSTR);
        advancePC(4);
    }
    else if ( (INSTR & LW_MASK) == LW_INSTR ){
      IMM = INSTR & 0b1111111111111111;
       (REG[T] = MEM[REG[S] + IMM]);
        advancePC(4);
    }
    else if ( (INSTR & MFHI_MASK) == MFHI_INSTR ){
       (REG[D] = HI);
        advancePC(4);
    }
    else if ( (INSTR & MFLO_MASK) == MFLO_INSTR ){
       (REG[D] = LO);
        advancePC(4);
    }
    else if ( (INSTR & MULT_MASK) == MULT_INSTR ){
       (REG[LO] = REG[S] * REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & OR_MASK) == OR_INSTR ){
       (REG[D] = REG[S] | REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & ORI_MASK) == ORI_INSTR ){
      //cout << "ORI" << endl;
      IMM = INSTR & 0b1111111111111111;
      //cout << REG[T] << " " << REG[S] << " " << S << " " << T << " " << IMM << endl;
       (REG[T] = REG[S] | IMM);
       //cout << REG[T] << " " << REG[0] << endl;
        advancePC(4);

        //cout << " HI " << endl;
    }
    else if ( (INSTR & SB_MASK) == SB_INSTR ){
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
       (MEM[REG[S] + IMM] = (0xff & REG[T]));
        advancePC(4);
    }
    else if ( (INSTR & SLL_MASK) == SLL_INSTR ){
       (REG[D] = REG[T] << H);//h?
        advancePC(4);
    }
    else if ( (INSTR & SLLV_MASK) == SLLV_INSTR ){
       (REG[D] = REG[T] << REG[S]);
        advancePC(4);
    }
    else if ( (INSTR & SLT_MASK) == SLT_INSTR ){
      //cout << "$$$$" << " " << REG[S] << " " << REG[T] << endl;
      if (REG[S] < REG[T])
      {
        REG[D] = 1;
        advancePC(4);
      }
      else
      {
        REG[D] = 0;
        advancePC(4);
      }
    }
    else if ( (INSTR & SLTI_MASK) == SLTI_INSTR ){
      IMM = INSTR & 0b1111111111111111;
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] < IMM)
      {
      REG[T] = 1;
        advancePC(4);
      }
      else
      {
      REG[T] = 0;
        advancePC(4);
      }
    }
    else if ( (INSTR & SLTIU_MASK) == SLTIU_INSTR ){
      //printf("%x\n", SLTIU_INSTR);
      IMM = INSTR & 0b1111111111111111;
      if (((IMM >> 15) & 1) == 1)
        IMM = IMM | 0b11111111111111110000000000000000;
      if (REG[S] < IMM)
      {
        REG[T] = 1;
        advancePC(4);
      }
      else
      {
      REG[T] = 0;
      advancePC(4);
      }
    }
    else if ( (INSTR & SLTU_MASK) == SLTU_INSTR ){
      if (REG[S] < REG[T])
      {
      REG[D] = 1;
        advancePC(4);
      }
      else
      {
      REG[D] = 0;
        advancePC(4);
      }
    }
    else if ( (INSTR & SRA_MASK) == SRA_INSTR ){
       (REG[D] = REG[T] >> H);
        advancePC(4);
    }
    else if ( (INSTR & SRL_MASK) == SRL_INSTR ){
       (REG[D] = REG[T] >> H);
        advancePC(4);
    }
    else if ( (INSTR & SRLV_MASK) == SRLV_INSTR ){
       (REG[D] = REG[T] >> REG[S]);
        advancePC(4);
    }
    else if ( (INSTR & SUB_MASK) == SUB_INSTR ){
       (REG[D] = REG[S] - REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & SUBU_MASK) == SUBU_INSTR ){
       (REG[D] = REG[S] - REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & SW_MASK) == SW_INSTR ){
      IMM = INSTR & 0b1111111111111111;
       (MEM[REG[S] + IMM] = REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & SB_MASK) == SB_INSTR ){
      IMM = INSTR & 0b1111111111111111;
       (MEM[REG[S] + IMM] = (0xff & REG[T]));
        advancePC(4);
    }
    else if ( (INSTR & SYSCALL_MASK) == SYSCALL_INSTR ){
      //cout << "This is syscall" << REG[2] << endl;
      if (REG[2] == 1)
      {
        printf("%d", REG[4]);
      }
      else if (REG[2] == 4)
      {
        //cout << "SYSCALL" << endl;
        int index = REG[4];
        //printf("%x\n", index);
        while (true)
        {
          int word = MEM[index/4];//divide by 4 because the byte address has four separate byte words
          int shift = (index % 4) * 8;//finds the specific character
          int byteVal = (word >> shift) & 0b11111111;//masks to low order bit
          if (byteVal == 0) break;
          printf("%c", byteVal);
          index++;
        }
      }
      else if (REG[2] == 10)
      {
        exit(0);
      }
      else if (REG[2] == 5)
      {
        cin >> REG[2];
      }
      else if (REG[4] == 1)
      {
        cout << REG[4];
      }
      (advancePC(4));
    }
    else if ( (INSTR & XOR_MASK) == XOR_INSTR ){
       (REG[D] = REG[S] ^ REG[T]);
        advancePC(4);
    }
    else if ( (INSTR & XOR_MASK) == XOR_INSTR ){
      IMM = INSTR & 0b1111111111111111;
       (REG[T] = REG[S] ^ IMM);
        advancePC(4);
    }
    else {
      printf("%x\n", PC);
      cout << "Error" << endl;
      break;
    }
    //printf("%x\n", PC);
  }
}

int main(int argc, char**argv) {//allows input from the keyboard in the command prompt

ifstream inFile(argv[1]);

string line;
while (getline(inFile, line))
{
  string location;
  istringstream iss(line);
  if (line[0] != '[') continue;//tells compiler where to start
  //cout << endl;
    int index = line.find("]");//tells compiler where to stop
    location = line.substr ( 1 , index-1 );//the location runs to the last position - 1
    //cout << location << endl;

if (location[0] == 'P') // PC
{
  int PC = 0;
  int nPC = 0;
  int tokenIndex = line.find("0x");//tells compiler to start after 0x
  string valString = line.substr(tokenIndex+2, 8);//starts after 0x
  unsigned int val = strtoul(valString.c_str(), NULL, 16);//translates from hex
  PC = val; //REG is a global variable with myInt now assigned
  nPC = PC + 4;
}
if (location[0] == 'R') //if the first location is R continue
{
  string num = location.substr(1);
  int myInt = stoi(num);//extracts num
  int tokenIndex = line.find("0x");//tells compiler to start after 0x
  string valString = line.substr(tokenIndex+2, 8);//starts after 0x
  unsigned int val = strtoul(valString.c_str(), NULL, 16);//translates from hex
  REG[myInt] = val; //REG is a global variable with myInt now assigned
}
else if (location[0] == '0')//need to cycle through other hex cases after
{
  string num = location.substr(2);//start of location
  int myInt = strtoul(num.c_str(), NULL, 16);//translates to decimal
  //cout << myInt << endl;
  int tokenIndex = line.find("0x");//start with 0x
  int start = 8;//declaring start
  while (true)
  {
    int index = line.find("0x", start);//telling the compiler where to start
    //cout << index << endl;
      if (index < 0) break;//break if the value is less than 0
        start = index + 8;//starts 8 characters over from where we found the last 0x
        string valString = line.substr(index+2, 8);//starts after 0x
        //cout << valString << endl;
        unsigned int val = strtoul(valString.c_str(), NULL, 16);//translates from hex
        MEM[myInt/4] = val;//divides the bytes by 4
        myInt += 4;//puts next hex constant into the next memory slot
      }

    }
  }

dumpMemory(0, 100);
executeLoop();

return 0;
}
