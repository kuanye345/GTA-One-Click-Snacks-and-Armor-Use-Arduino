#include "Mouse.h"
#include <Keyboard.h>
#include <EEPROM.h>
int dmwriltime = 60;   //菜单中切换选项时间
int dmwriltime2 = 70;  //切换不同菜单时间
int dmwriltime3 = 120; //吃零食护甲时间
int dmwriltime1 = 20;  //按下按键时间
int cltime = 500;      //关闭菜单后至少等待多久再打开菜单
int rmin = 0, rmax=5; //随机时间范围
boolean lasth;
boolean lastl;
boolean lasts;
int ih=8;
int led0 = 10;
int led1 = 9;
int il=7;
int is=6;
int ph;
int pl;
int nowc = 3;
unsigned long lasttime;
unsigned long sanjian;
int sshijian = 250;

void setup() {
  Keyboard.begin();
  Mouse.begin();
  pinMode(ih, INPUT_PULLUP);
  pinMode(il, INPUT_PULLUP);
  pinMode(is, INPUT_PULLUP);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  EEPROM.get(8,nowc);
  delay(10);
}

void loop() {
  readinput();
  /*
  if(millis()-sanjian>sshijian && nowc==4)
  {
    sanjian=millis();
    sshijian=random(100,250);
    Mouse.press(MOUSE_LEFT);
    delay(random(10,50));
    Mouse.release(MOUSE_LEFT);
  }*/
  if(ph>0 && millis()-lasttime>cltime)
  {
    hujia();
    lasttime=millis();
  }
  if(pl>0 && millis()-lasttime>cltime)
  {
    lingshi();
    lasttime=millis();
  }
  delay(10);
}

void readinput() {
  boolean nowh = false;
  boolean nowl = false;
  boolean nows = false;
  if(digitalRead(ih)==LOW)
  {
    nowh = true;
  }
  if(digitalRead(il)==LOW)
  {
    nowl = true;
  }
  if(digitalRead(is)==LOW)
  {
    nows = true;
  }
  if(lasth==false&&nowh==true)
  {
    if(nowc==5)
    {
      guanbia();
    } else
    {
      ph++;
    }
  }
  if(lasth==true&&nowh==false)
  {
    if(nowc==5)
    {
      guanbib();
    }
  }
  if(lastl==false&&nowl==true)
  {
    if(nowc==5)
    {
      guanbiold();
    } else
    {
      pl++;
    }
  }
  if(lasts==false&&nows==true)
  {
    nowc++;
    if(nowc>=6)
    {
      nowc=2;
    }
    EEPROM.put(8,nowc);
  }
  lasth=nowh;
  lastl=nowl;
  lasts=nows;
  if(nowc==2)
  {
    digitalWrite(led0,HIGH);
    digitalWrite(led1,LOW);
  }
  if(nowc==3)
  {
    digitalWrite(led0,LOW);
    digitalWrite(led1,HIGH);
  }
  if(nowc==4)
  {
    digitalWrite(led0,HIGH);
    digitalWrite(led1,HIGH);
  }
  if(nowc==5)
  {
    digitalWrite(led0,LOW);
    digitalWrite(led1,LOW);
  }
}

void dmwril(long dtime) { //DelayMsWithReadInput Long
  long stime=dtime;
  while(stime>10)
  {
    readinput();
    delayMicroseconds(10000-120);
    stime=stime-10;
  }
  if(stime>0)
  {
    delay(stime);
  }
}

void guanbiold() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  Keyboard.releaseAll();
}
void guanbia() {
  Keyboard.press(KEY_LEFT_ALT);
}
void guanbib() {
  Mouse.move(0,500,0);
  delay(20);
  Keyboard.releaseAll();
}

void hujia() {
  randomSeed(millis());
  anjian('M',dmwriltime2);
  for (int i=0; i<nowc-1 ;i++)
  {
    anjian(KEY_DOWN_ARROW,dmwriltime);
  }
  anjian(KEY_RETURN,dmwriltime2);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_RETURN,dmwriltime2);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  while(ph>0)
  {
    anjian(KEY_RETURN,dmwriltime3);
    ph=ph-1;
  }
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
}

void anjian(char jian,int yanshi) {
  Keyboard.press(jian);
  dmwril(dmwriltime1+random(rmin, rmax));
  Keyboard.releaseAll();
  dmwril(yanshi+random(rmin, rmax));
}

void lingshi() {
  randomSeed(millis());
  anjian('M',dmwriltime2);
  for (int i=0; i<nowc-1 ;i++)
  {
    anjian(KEY_DOWN_ARROW,dmwriltime);
  }
  anjian(KEY_RETURN,dmwriltime2);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_DOWN_ARROW,dmwriltime);
  anjian(KEY_RETURN,dmwriltime2);
  while(pl>0)
  {
    anjian(KEY_RETURN,dmwriltime3);
    pl=pl-1;
  }
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
  anjian(KEY_BACKSPACE,dmwriltime2);
}
