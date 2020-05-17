#include <Servo.h>
/****ESP8266****/
/*#include <ESP8266WebServer.h>
#include <DNSServer.h>*/
/****UNO****/
uint8_t p1Pin = 2;
uint8_t p2Pin = 3;
uint8_t p3Pin = 4;
uint8_t p4Pin = 5;
uint8_t p1LatPin = 6;
uint8_t p2LatPin = 7;
uint8_t p3LatPin = 8;
uint8_t p4LatPin = 9;
uint8_t t1Pin = 10;
uint8_t t2Pin = 11;
uint8_t t3Pin = 12;
/****ESP8266****/
/*uint8_t p1Pin = 5;
uint8_t p2Pin = 4;
uint8_t p3Pin = 0;
uint8_t p4Pin = 2;
uint8_t t1Pin = 14;
uint8_t t2Pin = 12;
uint8_t t3Pin = 13;
ESP8266WebServer webServer(80);
DNSServer dnsServer;*/

class thumb{
  private:
  Servo &MCP1;
  Servo &MCP2;
  Servo &phalangeal;
  public:
    thumb(Servo &s1,Servo &s2,Servo &s3) : MCP1(s1),MCP2(s2),phalangeal(s3){}
    void Setup(uint8_t P1,uint8_t P2,uint8_t P3);
//    void abduction();
//    void lateral();
    void extension();
    void flexion(int p1,int p2,int p3);
    int MCP1Target;
    int MCP2Target;
    int PhalangealTarget;
    int slowness=15;
};

void thumb::Setup(uint8_t P1,uint8_t P2,uint8_t P3){
  MCP1.attach(P1);
  MCP2.attach(P2);
  phalangeal.attach(P3);
  
}
void thumb::extension(){
  while(MCP1Target!=1 && MCP2Target!=1 && PhalangealTarget!=1){
    if(MCP1Target!=1){
      MCP1Target--;
    }
    if(MCP2Target!=1){
      MCP2Target--;
    }
    if(PhalangealTarget!=1){
      PhalangealTarget--;
    }
  MCP1.write(MCP1Target);
  MCP2.write(MCP2Target);
  phalangeal.write(PhalangealTarget);
    delay(slowness);
  }
}

void thumb::flexion(int p1,int p2,int p3){
  while(MCP1Target!=p1 && MCP2Target!=p2 && PhalangealTarget!=p3){
    if(MCP1Target<p1){
      MCP1Target++;
    }
    else if(MCP1Target>p1){
      MCP1Target--;
    }
    if(MCP2Target<p2){
      MCP2Target++;
    }
    else if(MCP2Target>p2){
      MCP2Target--;
    }
    if(PhalangealTarget<p3){
      PhalangealTarget++;
    }
    else if(PhalangealTarget>p3){
      PhalangealTarget--;
    }
    MCP1.write(MCP1Target);
    MCP2.write(MCP2Target);
    phalangeal.write(PhalangealTarget);
    delay(slowness);
  }
}

class finger{
  private:
    Servo &self;
    Servo &self2;
  public:
    finger(Servo &s,Servo &s2) : self(s),self2(s2){}
    void Setup(uint8_t sPin, uint8_t sPin2);
    void flexion(int val);
    void extension();
    void lateral(int val);
    int target;
    int slowness=15;
};
void finger::Setup(uint8_t sPin, uint8_t sPin2){
    self.attach(sPin);
    self2.attach(sPin2);
  }
void finger::flexion(int val){
  while(target!=val){
    if(target<val){
      target++;
    }
    else if(target>val){
      target--;
    }
    self.write(target);
    delay(slowness);
  }
}
void finger::extension(){
//  self.write(1);
  while(target!=1){
    target--;
    self.write(target);
    delay(slowness);
  }
}

void finger::lateral(int val){
  while(target!=val){
    if(target<val){
      target++;
    }
    else if(target>val){
      target--;
    }
    self2.write(target);
    delay(slowness);
  }
}

Servo p1;
Servo p2;
Servo p3;
Servo p4;
Servo p1Lat;
Servo p2Lat;
Servo p3Lat;
Servo p4Lat;
Servo MCP1;
Servo MCP2;
Servo phalangeal;
finger Index(p1, p1Lat);
finger Middle(p2, p2Lat);
finger Ring(p3, p3Lat);
finger Pinky(p4, p4Lat);
thumb Thumb(MCP1,MCP2,phalangeal);

/*const byte DNS_PORT = 53;*/

int Point[5]={0,1,0,0,0};
int Spiderman[5]={0,1,0,0,1};

void setup() {
/*  portal();*/
//  pinMode(latchPin, OUTPUT);
//  pinMode(dataPin, OUTPUT);  
//  pinMode(clockPin, OUTPUT);
  Index.Setup(p1Pin,p1LatPin);
  Middle.Setup(p2Pin,p2LatPin);
  Ring.Setup(p3Pin,p3LatPin);
  Pinky.Setup(p4Pin,p4LatPin);
  Thumb.Setup(t1Pin,t2Pin,t3Pin);
  openHand();
  delay(1250);
  Home();
  delay(1250);
  openHand();
  delay(1250);

}

void loop() {
/*  dnsServer.processNextRequest();
  webServer.handleClient();*/
  gestureCycle();
  

}

void Home(){
  Thumb.extension();
  Index.extension();
  Middle.extension();
  Ring.extension();
  Pinky.extension();
}

void openHand(){
  Thumb.flexion(300,300,300);
  Index.flexion(300);
  Middle.flexion(300);
  Ring.flexion(300);
  Pinky.flexion(300);
}

void point(){
  Thumb.extension();
  Index.flexion(300);
  Middle.extension();
  Ring.extension();
  Pinky.flexion(1);
}

void spiderman(){
  Thumb.flexion(300,300,300);
  Index.flexion(300);
  Middle.extension();
  Ring.extension();
  Pinky.flexion(300);
}

void rock(){
  Thumb.extension();
  Index.flexion(300);
  Middle.extension();
  Ring.extension();
  Pinky.flexion(300);
}

void fingerGuns(){
  Thumb.flexion(300,300,300);
  Index.flexion(300);
  Middle.extension();
  Ring.extension();
  Pinky.extension();
}

void theBird(){
  Thumb.extension();
  Index.extension();
  Middle.flexion(300);
  Ring.extension();
  Pinky.extension();
}

void theBird_Variant(){
  Thumb.flexion(300,300,300);
  Index.extension();
  Middle.flexion(300);
  Ring.extension();
  Pinky.extension();
}

void callMe(){
  Thumb.flexion(300,300,300);
  Index.extension();
  Middle.extension();
  Ring.extension();
  Pinky.flexion(300);
}

void thumbsUp(){
  Thumb.flexion(300,300,300);
  Index.extension();
  Middle.extension();
  Ring.extension();
  Pinky.extension();
}

void keyPinch(){
  Thumb.flexion(300,75,150); //MCP1,MCP2,phalangeal
  Index.flexion(250);
  Middle.flexion(300);
  Ring.flexion(300);
  Pinky.flexion(300);
}

void directionalGrip(){
  Thumb.flexion(175,30,150); //MCP1,MCP2,phalangeal
  Index.flexion(250);
  Middle.flexion(300);
  Ring.flexion(300);
  Pinky.flexion(300);
}

void spanGrasp(){
  Index.lateral(45);
//  Middle.lateral(300);
  Ring.lateral(45);
  Pinky.lateral(45);
  Thumb.flexion(1,1,150); //MCP1,MCP2,phalangeal
  Index.flexion(250);
  Middle.flexion(300);
  Ring.flexion(300);
  Pinky.flexion(300);
}

void gestureCycle(){
  Home();
  delay(1250);
  thumbsUp();
  delay(1250);
  fingerGuns();
  delay(1250);
  point();
  delay(1250);
  rock();
  delay(1250);
  spiderman();
  delay(1250);
  callMe();
  delay(1250);
  openHand();
  delay(1250);
  theBird_Variant();
  delay(1250);
  theBird();
  delay(1250);
}
