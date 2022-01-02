#define INPUT_PIN 10
#define OUTPUT_PIN 9
#include <PinChangeInterrupt.h>

uint8_t reverse_table[256] = { 0,128,64,192,32,160,96,224,16,144,80,208,48,176,112,240,8,136,72,200,40,168,104,232,24,152,88,216,56,184,120,248,4,132,68,196,36,164,100,228,20,148,84,212,52,180,116,244,12,140,76,204,44,172,108,236,28,156,92,220,60,188,124,252,2,130,66,194,34,162,98,226,18,146,82,210,50,178,114,242,10,138,74,202,42,170,106,234,26,154,90,218,58,186,122,250,6,134,70,198,38,166,102,230,22,150,86,214,54,182,118,246,14,142,78,206,46,174,110,238,30,158,94,222,62,190,126,254,1,129,65,193,33,161,97,225,17,145,81,209,49,177,113,241,9,137,73,201,41,169,105,233,25,153,89,217,57,185,121,249,5,133,69,197,37,165,101,229,21,149,85,213,53,181,117,245,13,141,77,205,45,173,109,237,29,157,93,221,61,189,125,253,3,131,67,195,35,163,99,227,19,147,83,211,51,179,115,243,11,139,75,203,43,171,107,235,27,155,91,219,59,187,123,251,7,135,71,199,39,167,103,231,23,151,87,215,55,183,119,247,15,143,79,207,47,175,111,239,31,159,95,223,63,191,127,255};

volatile int pwm_value = 0;
volatile int prev_time = 0;
volatile int byte_bit = 0;
volatile byte current_byte = 0;
volatile char reverse_byte = 0;
volatile boolean state = 0;
volatile boolean output_state = 0;
volatile char receivedChar;
volatile char reverseChar;
volatile boolean newData = false;
volatile boolean current_bit = false;
static bool Xoffed = false;
volatile boolean received;
//volatile boolean sent;

// paste data to serial monitor to "play tape" to TI-95
// reverse bytes and stream bits coming in from serial monitor
// run "WRT" routine on TI-95 to "record tape" on PC
// convert PWM to bits, bits to bytes, and reverse bytes

void setup() {
  // put your setup code here, to run once:
   // communicate at 500000 baud
  Serial.begin(500000);
  // Serial.setRxBufferSize(16384);
  // set TI-95 connection pins to input and output
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  // use pullup resistor
  digitalWrite(INPUT_PIN, HIGH);
  // attach a PinChange Interrupt to our pin on the rising edge
  attachPCINT(digitalPinToPCINT(INPUT_PIN),change,CHANGE); 
  //Serial.print(SERIAL_BUFFER_SIZE);
}

int incomingByte = 0; 
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    //incomingByte = Serial.read();
    //int serial_bytes = Serial.available();
    //if (serial_bytes == 31) {
    //  received = true;
    //}
    //Serial.print("Remaining bytes: ");
    //Serial.println(serial_bytes);
    // say what you got:
    //Serial.print("I received: ");
    //Serial.println(incomingByte);
    receivedChar = reverse_table[Serial.read()];
    //Serial.println(receivedChar);
    newData = true;
    play_byte(); 
    //check_buffer();
    //recvOneChar(); 
  }
  // report back to PC if 31 bytes sent...
  // if (received==true && (Serial.available() == 0)) {
    // Serial.println("Sent!");
    // received=false;
  //}
  // PC receives "Sent!" and sends another 32 bytes...
}

void recvOneChar() {
 if (Serial.available() > 0) {
  receivedChar = Serial.read();
  Serial.println(receivedChar);
  newData = true;
 }
}

void play_byte() 
{
    //reverseChar = reverse[receivedChar];
    //Serial.println(receivedChar);
  for (int i = 0; i < 8; i++) {
    current_bit = bitRead(receivedChar,i);
    if (current_bit == 0) {
      //Serial.println(0);
      pwm_zero();
    }
    if (current_bit == 1) {
      //Serial.println(1);
      pwm_one();
    }
  }
}

void pwm_zero() {
   // print zero
   int start_time = micros();
   output_state = not(output_state);
   digitalWrite(OUTPUT_PIN, output_state);
   delayMicroseconds(700);
   int zero_time = micros()-start_time;
   //Serial.print(zero_time);
   //Serial.print("\t");
   //Serial.println(output_state);
}

void pwm_one() {
   pwm_one_half();
   pwm_one_half();
}
void pwm_one_half() {
   // print one
   int start_time = micros();
   output_state = not(output_state);
   digitalWrite(OUTPUT_PIN, output_state);
   delayMicroseconds(350);
   int one_time = micros()-start_time;
   //Serial.print(one_time);
   //Serial.print("\t");
   //Serial.println(output_state);
}

void change()
{
  pwm_value = micros()-prev_time;
  prev_time = micros();
  state = not(digitalRead(INPUT_PIN));
  if (byte_bit==8) {
    // char
    reverse_byte = reverse_table[current_byte];
    //if (reverse_byte<0x10)
    //{
    //  Serial.print("0");
    //}
    //Serial.print(reverse_byte,HEX);
    Serial.write(reverse_byte);
    byte_bit=0;
    current_byte=0;
  }
  // long high or low pulse is a zero
  if ((pwm_value > 400) && (pwm_value < 750)) {
    //Serial.println("0");
    byte_bit++;
  }
  else if ((pwm_value > 0) && (pwm_value < 400) && (state == 1)) {
    // short high pulse is a one
    //Serial.println("1");
    bitSet(current_byte,byte_bit);
    byte_bit++;
  }
  //Serial.println(byte_bit);
  //Serial.print(pwm_value);
  //Serial.print("\t");
  //Serial.println(state);
  //bitSet(current_byte,byte_bit);
}

// add software xon xoff flow control
void check_buffer(){
if((!Xoffed)&&(Serial.available()>48)) { //buffer is 3/4 full better shut it down!
  Serial.write(0x13); // xoff
  Xoffed = true;
  }
else if(Xoffed&&(Serial.available()<32)) { // more room in buffer Yea! turn it on!
  Serial.write(0x11); // Xon
  Xoffed = false;
  }
}
