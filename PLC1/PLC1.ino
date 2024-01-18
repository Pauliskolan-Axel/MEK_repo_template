//Plocka boll höj tornet, lägg tillbaka den.
int State = 0;
const int N_O_INPUTS=7+1;//0 not used
const int N_O_OUTPUTS=9+1;//0 not used
int Spins[N_O_INPUTS] = {A0, A1, A2, A3, A4, A5, A6, A7, }; //START=A13, RESET=A14, Embreak=IN1 (interrupt), kolla att alla stämmer
int S[N_O_INPUTS] = {0, 0, 0, 0, 0, 0, 0, 0};
int Ypins[N_O_OUTPUTS] = {0, 5, 6, 7, 8,0,0,0,9, 10};//Kolla att de stämmer
int Y[N_O_OUTPUTS] = {0, 0, 0, 0, 0, 0,0,0,1,1};
int RST_needed=1; //Emergency break is active low. the emergency break will stop all actions via an interrupt, requiring a Reset to get going again

int Safe=0;//When the machine is safe for action. Set to 0 when resetting the Arduino.

void ISR(){//For the interrupt, write yourself.
}

void setup() {
  for (int i = 0; i < N_O_INPUTS; i++) {
    pinMode(Spins[i], INPUT);
  }
  for (int i = 0; i < N_O_OUTPUTS; i++) {
    pinMode(Ypins[i], OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {
  // Read all sensors, and START and RESET buttons. Special treatment for material sensors (PLC2) that need to store its reading, therefore only read if nulled.
  //Emergency break is triggered by an interrrupt and thus does not need to be read. 
  //See: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

  Serial.print(Safe);
  Serial.print(" <- Safe \t S:");
  for (int i = 1; i < N_O_INPUTS; i++) {//read all sensors (except 0 that doesnt exist), store in S[]
      S[i] = digitalRead(Spins[i]);
      Serial.print(S[i]);
      Serial.print(" ");  
  }//all sensors and buttons (except "Emergency break") read and stored in S[]

if(Safe==0){//First, reset machine
Y[1]=0;
Y[2]=0;
Y[3]=0;
Y[8]=0;
Y[9]=1;
if(S[1]==0&&S[2]==1&&S[3]==1&&S[4]==0&&S[7]==1&&S[6]==0){//Reach reset pos.
  Safe=1;
  State=0;
  Serial.print("RESET finish");
}
}

if( Safe==1&&State==0&&S[2]==1&&Y[1]==0){//we are in reset position, start
  Y[2]=1;//Grabber forward
  State=1; 
}

//Write to all outputs: (write the code yourself).


