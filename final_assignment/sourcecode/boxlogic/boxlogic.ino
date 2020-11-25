int sensorPin1 = A0;//旋钮1
int sensorPin2 = A1;//旋钮2
int led=2;//第二个模块的光源
int sensorled = A2;//第二个模块的光源传感器
int ledValue=0;//第二个模块的光源传感器的值
int ledPin0 = 7;//旋钮模块成功后亮灯
      
int sensorValue1 = 0;  //第一个模块传感器的值
int sensorValue2 = 0;//第一个模块传感器的值

int fin0=0;//表示第一个模块是否已经完成
int fin1=0;
int fin2=0;
int anotherArduino=10;//三个模块都完成向另一个arduino输出高电平

int signalPin0=8;
int signalPin1=9;
bool signalValue0=1;
bool signalValue1=1;

int flag=0;



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin0, OUTPUT);
  pinMode(anotherArduino, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(signalPin0, OUTPUT);
  pinMode(signalPin0, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(signalPin0, signalValue0);
  digitalWrite(signalPin1, signalValue1);
  
  int fw1=0;
  int fw2=0;
  ledValue=analogRead(sensorled);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  digitalWrite(led, HIGH);
  fw1=map(sensorValue1,0,1023,0,15);//旋钮细化范围
  fw2=map(sensorValue2,0,1023,0,15);//
//    Serial.println(fw1);
//    Serial.println(fw2);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if(fw1==6 && fw2==8)//需要修改这里的和上面细化范围的值来对应刻度!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
      digitalWrite(ledPin0, HIGH);
      fin0=1;
    }
    
   
  if(ledValue>512)//光线传感器的值判断
  {
    fin1=1;  
    Serial.println("light");
  }
    
  if(analogRead(3)>=1000||analogRead(4)>=1000||analogRead(5)>=1000)
  {Button_func();}


  //三个模块都完成向另一个arduino输出高电平
//  if(fin0==1 && fin1==1 && fin2==1)
//  {
//      digitalWrite(anotherArduino, HIGH);
//  }
//  delay(300);
}

int Button_func()
{
    if(fin0==1 && fin1==1&&flag==0&&analogRead(3)>=1000)
    {
      flag++;
      while(analogRead(4)<=1000&&analogRead(5)<=1000){;}
      if(flag==1&&analogRead(4)>=1000)
      {
        flag++;
        while(analogRead(3)<=1010&&analogRead(5)<=1010){
          }
        if(flag==2&&analogRead(5)>=1000)
        {flag++;Serial.println("done");signalValue0=0;digitalWrite(signalPin0, signalValue0);while(1);}
        else
        {Serial.println("die3");digitalWrite(signalPin1, LOW);while(1);}
      }
      else
      {Serial.println("die2");digitalWrite(signalPin1, LOW);while(1);}
    }
    else if(flag==3)
    {;}
    else
    {Serial.println("die1");digitalWrite(signalPin1, LOW);while(1);}
}
