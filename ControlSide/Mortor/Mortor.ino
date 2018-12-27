//#define DEBUG 1


int in11 = 45, in21 = 28, in31 = 36, in41 = 44, in51 = 37, in61 = 29;
int in12 = 47, in22 = 30, in32 = 38, in42 = 46, in52 = 39, in62 = 31;
int in13 = 49, in23 = 32, in33 = 40, in43 = 48, in53 = 41, in63 = 33;
int in14 = 51, in24 = 34, in34 = 42, in44 = 50, in54 = 43, in64 = 35;


int _step = 0;
int loopnum = 0;
int flag=0;

String buff;



// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("setting mode");
  
  Serial2.write("AT\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);
  
  Serial2.write("AT+CWMODE_DEF=2\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);

  Serial2.write("AT+CWSAP_DEF=\"ESP8266\",\"1111111111\",5,4\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);

  Serial2.write("AT+CIFSR\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);

  Serial2.write("AT+CIPMUX=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);

  Serial2.write("AT+CIPSERVER=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(20);

  Serial2.write("AT+CIPDINFO=1\r\n");
  if(Serial2.available()){
    Serial.println(Serial2.readString());
  }
  delay(10);

  // declare mortor 1 control pins
  pinMode(in11, OUTPUT);
  pinMode(in12, OUTPUT);
  pinMode(in13, OUTPUT);
  pinMode(in14, OUTPUT);

  // declare mortor 2 control pins
  pinMode(in21, OUTPUT);
  pinMode(in22, OUTPUT);
  pinMode(in23, OUTPUT);
  pinMode(in24, OUTPUT);

  // declare mortor 3 control pins
  pinMode(in31, OUTPUT);
  pinMode(in32, OUTPUT);
  pinMode(in33, OUTPUT);
  pinMode(in34, OUTPUT);

  // declare mortor 4 control pins
  pinMode(in41, OUTPUT);
  pinMode(in42, OUTPUT);
  pinMode(in43, OUTPUT);
  pinMode(in44, OUTPUT);

  // declare mortor 5 control pins
  pinMode(in51, OUTPUT);
  pinMode(in52, OUTPUT);
  pinMode(in53, OUTPUT);
  pinMode(in54, OUTPUT);

  // declare mortor 6 control pins
  pinMode(in61, OUTPUT);
  pinMode(in62, OUTPUT);
  pinMode(in63, OUTPUT);
  pinMode(in64, OUTPUT);
}

// the loop routine runs over and over again forever:
// U 1 W
// F 2 G
// D 3 Y
// L 4 O
// R 5 R 
// B 6 B
void loop() {
  int ii = 0;
  int len = 0;
  char* temp;
  int actual_len=0;
  int start=0;
  int ending=0;
  // test one string to control the cube

  #ifdef DEBUG
  if(flag == 0){
    flag=1;
    String test = "F3D2F3L1F2L2D2U3R3U3L2U3R2U1R2U3L2U3L2U2F2L2D2L2D2F2R2L2D2L2";
    temp = (char*)test.c_str();
    for(ii=0;ii<test.length();){
      Serial.print(temp[ii]);
      Serial.println(temp[ii+1]);
      translate(temp+ii);
      ii=ii+2;
    }
  }
  #else
   if(Serial2.available()){
     buff = (Serial2.readString());
     // Serial.println(buff);
     temp = (char*)buff.c_str();
     Serial.println(temp);
     Serial.println(buff.length());

     Serial.print("begin\n");
     for(ii=0;temp[ii]!=':'; ii++);
     start = ii+1;
     for(;temp[ii]!='~';ii++);
     ending = ii;
     Serial.print(start); Serial.println(ending);


     // print the wanted string
     for(ii=start;ii<ending;ii++){
        Serial.print(temp[ii]);
     }

     
     for(ii=start;ii<ending;){
         if(temp[ii] == '@'){
            ii++; break; 
         }
         translate(temp+ii);
         ii+=2;
         
     }

     delay(10000);
     for(;ii<ending-1;){
        Serial.print("solve");
        translate(temp+ii);
        ii+=2; 
     }
   }
   #endif
}



// TODO: let specific mortor rotate 
// U 1 W
// F 2 G
// D 3 Y 
// L 4 R 
// R 5 O 
// B 6 B 
void translate(char* instruction){
    int motor, degree;
    switch(* instruction){
      case 'U':
        motor = 1;break;
      case 'F':
        motor = 2;break;
      case 'D':
        motor = 3;break;
      case 'L':
        motor = 5;break;
      case 'R': 
        motor = 4;break;
      case 'B':
        motor = 6;break;
    }
    
    degree = *(instruction+1)-'0';
//    Serial.print("instruc 1");
//    Serial.println(*instruction);
//    Serial.print(*(instruction+1)-'0');
//    Serial.println(motor);
//    Serial.println(degree);
    if(degree == 3)
       moveReverse(1,motor);
    else
       moveForward(degree, motor);
}


// TODO: to set the cube turn 90 degree or 180 degree or 270 degree
void moveForward(int n, int mortor){
    int in1, in2, in3, in4;
    switch(mortor){
      case 1:
        in1 = in11;
        in2 = in12;
        in3 = in13;
        in4 = in14;
        break;
      case 2:
        in1 = in21;
        in2 = in22;
        in3 = in23;
        in4 = in24;
        break;
      case 3:
        in1 = in31;
        in2 = in32;
        in3 = in33;
        in4 = in34;
        break;
      case 4:
        in1 = in41;
        in2 = in42;
        in3 = in43;
        in4 = in44;
        break;
      case 5:
        in1 = in51;
        in2 = in52;
        in3 = in53;
        in4 = in54;
        break;
      case 6:
        in1 = in61;
        in2 = in62;
        in3 = in63;
        in4 = in64;
        break;
    } 
    // 90 degree clockwise rotation
    if(n == 1){
      for(loopnum=0; loopnum<50; loopnum++){
          MotorForward(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }   
    }
    // 180 degree clockwise rotation
    if(n == 2){
      for(loopnum=0; loopnum<100; loopnum++){
          MotorForward(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }  
    } 
    // 270 degree clockwise rotation
    if(n == 3){
      for(loopnum=0; loopnum<150; loopnum++){
          MotorForward(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }  
    }  
}

void moveReverse(int n, int mortor){
    int in1, in2, in3, in4;
    switch(mortor){
      case 1:
        in1 = in11;
        in2 = in12;
        in3 = in13;
        in4 = in14;
        break;
      case 2:
        in1 = in21;
        in2 = in22;
        in3 = in23;
        in4 = in24;
        break;
      case 3:
        in1 = in31;
        in2 = in32;
        in3 = in33;
        in4 = in34;
        break;
      case 4:
        in1 = in41;
        in2 = in42;
        in3 = in43;
        in4 = in44;
        break;
      case 5:
        in1 = in51;
        in2 = in52;
        in3 = in53;
        in4 = in54;
        break;
      case 6:
        in1 = in61;
        in2 = in62;
        in3 = in63;
        in4 = in64;
        break;
    } 
    // 90 degree clockwise rotation
    if(n == 1){
      for(loopnum=0; loopnum<50; loopnum++){
          MotorReverse(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }   
    }
    // 180 degree clockwise rotation
    if(n == 2){
      for(loopnum=0; loopnum<100; loopnum++){
          MotorReverse(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }  
    } 
    // 270 degree clockwise rotation
    if(n == 3){
      for(loopnum=0; loopnum<150; loopnum++){
          MotorReverse(in1, in2, in3, in4);
          delay(1);
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          digitalWrite(in3,LOW);
          digitalWrite(in4,LOW);
      }  
    }  
}


void MotorForward(int in1, int in2, int in3, int in4) {
  // forward 1.8 degree
  // time order of the step motor is 
  // in1+ in2  in3  in4
  // in1+ in2  in3+ in4
  // in1  in2  in3+ in4
  // in1  in2+ in3+ in4
  // in1  in2+ in3  in4
  // in1  in2+ in3  in4+
  // in1  in2  in3  in4+
  // in1+ in2  in3  in4+

  switch(_step){
   case 0:
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     break;
   case 1:
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     break;
   case 2:
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
     break;     
   case 3:
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
     break;  
   default:
     digitalWrite(in1, LOW);
     digitalWrite(in2, LOW);
     digitalWrite(in3, LOW);
     digitalWrite(in4, LOW);
  }

   _step++;
   if(_step>3) _step=0;
}

void MotorReverse(int in1, int in2, int in3, int in4) {
  // forward 1.8 degree
  // time order of the step motor is 
  // in1+ in2  in3  in4
  // in1+ in2  in3+ in4
  // in1  in2  in3+ in4
  // in1  in2+ in3+ in4
  // in1  in2+ in3  in4
  // in1  in2+ in3  in4+
  // in1  in2  in3  in4+
  // in1+ in2  in3  in4+

  switch(_step){
   case 3:
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     break;
   case 2:
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     break;
   case 1:
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
     break;     
   case 0:
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
     break;  
   default:
     digitalWrite(in1, LOW);
     digitalWrite(in2, LOW);
     digitalWrite(in3, LOW);
     digitalWrite(in4, LOW);
  }

   _step++;
   if(_step>3) _step=0;
}

void MotorStop(int mortor){
    int in1,in2,in3,in4;
    switch(mortor){
      case 1:
        in1 = in11;
        in2 = in12;
        in3 = in13;
        in4 = in14;
        break;
      case 2:
        in1 = in21;
        in2 = in22;
        in3 = in23;
        in4 = in24;
        break;
      case 3:
        in1 = in31;
        in2 = in32;
        in3 = in33;
        in4 = in34;
        break;
      case 4:
        in1 = in41;
        in2 = in42;
        in3 = in43;
        in4 = in44;
        break;
      case 5:
        in1 = in51;
        in2 = in52;
        in3 = in53;
        in4 = in54;
        break;
      case 6:
        in1 = in61;
        in2 = in62;
        in3 = in63;
        in4 = in64;
        break;
    }

    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
}


