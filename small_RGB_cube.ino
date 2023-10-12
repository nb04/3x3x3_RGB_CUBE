/* 3x3x3 RGB LED Cube code written by Nicholas Brouwer 
 * Just a warning that a lot of the code is not optimized or documented well as I didn't have much programming knowledge at the time.
 * For the code to work ensure that all the connections are correct
 * If you are using this code, I encourage you to also try creating your functions – there are lots of patterns possible if you encorperate multiple colours
 */

#include <ShiftPWM.h>  // link to library: https://github.com/elcojacobs/ShiftPWM
//note for shift register connections to Arduino (from example in ShiftPWM.h): 
  // Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
  // Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
  // Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

const int ShiftPWM_latchPin=10;

const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;//default false

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 100;
int numRegisters = 2;
int numRGBleds = 9;
int set[21]={0,0,255,50,0,255,100,0,255,150,0,255,200,0,255,250,0,255,255,0,210};
byte red;
byte green;
byte blue;
int x = 0;
int r2=0;
int g2=0;
int b2=0;
void setup() {
  
  //last 2 led gnds, the others go to the second shift register
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(3);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  //Serial.begin(9600);
}
void loop() {   //commented out stuff for getting clip for short video
  random_on();
  for(int n=1; n<=50; n+=1){
    all_random();
  }
  spiral();
  
  red, green, blue = 0;
  
  solid_colours();
  for(int i=1; i<=100; i+=1){
    changing_colours();
  }
  for(int c=1; c<=10; c+=1){
    rotating_clockwise();
  }
  for(int h=1; h<=10; h+=1){
    rotating_counter_clockwise();
  }
  for(int o=1; o<=3; o+=1){
    clockwise();
  }
  for(int l=1; l<=3; l+=1){
    counter_clockwise();
  }
  for(int a=1; a<=80; a+=1){
    single_random();
  }
  for(int s=1; s<=50; s+=1){
    random_cube();
  }
  for(int b=1; b<=25; b+=1){
    rain();
  }
  
  const int gnds_off [10] = {255,255,255,255,255,255,255,255,255,255};
  setGNDs(gnds_off);

  delay(5000);
  }
void spiral(){
  int low[10]={255,255,255,255,255,255,255,255,255,255};
  
  red=0;
  green=0;
  blue=0;
  for(int z=1; z<=3; z+=1){ // past 3 is acting strange, but can go up to 8 ( for(int z=1; z<=8; z+=1){ )
 
    r2=red; // keep track of the colour the last spiral was
    g2=green;
    b2=blue;

    red=0;
    green=0;
    blue=0;

    if(z==1 or z==4 or z==6 or z==7){
      red=255;
    }
    if(z==2 or z==4 or z==5 or z==7){
      green=255;
    }
    if(z==3 or z==5 or z==6 or z==7){
      blue=255;
    }
    
    for(int x=1; x<=24; x+=1){
      for(int y=1; y<=27; y+=1){
        ShiftPWM.SetRGB(0,0,0,0);
        ShiftPWM.SetRGB(1,0,0,0);
        ShiftPWM.SetRGB(2,0,0,0);
        int low[10]={255,255,255,255,255,255,255,255,255,255};
        
          setGNDs(low);
           
        if(y==1 or y==10 or y==19){
          int low[10]={255,0,255,255,255,255,255,255,255,255};
          
          setGNDs(low);
          
          if(x>=1 and x<=5){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
          if(x>=2 and x<=6){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=3 and x<=7){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
        }
        if(y==2 or y==11 or y==20){
          int low[10]={255,255,255,255,0,255,255,255,255,255};
          
          setGNDs(low);
           
          if(x>=4 and x<=8){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x>=8 and x<=12){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
        }
        if(y==3 or y==12 or y==21){
          int low[10]={255,255,255,255,255,255,255,0,255,255};
          
          setGNDs(low);
          
          if(x>=5 and x<=9){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x>=6 and x<=10){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=7 and x<=11){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
        }
        if(y==4 or y==13 or y==22){
          int low[10]={255,255,0,255,255,255,255,255,255,255};
          
          setGNDs(low);
          
          if(x>=9 and x<=13){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
          if(x>=10 and x<=14){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=11 and x<=15){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
        }
        if(y==5 or y==14 or y==23){
          int low[10]={255,255,255,255,255,0,255,255,255,255};
          
          setGNDs(low);
          
          if(x>=12 and x<=16){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x>=16 and x<=20){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
        }
        if(y==6 or y==15 or y==24){
          int low[10]={255,255,255,255,255,255,255,255,0,255};
          
          setGNDs(low);
          
          if(x>=13 and x<=17){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x>=14 and x<=18){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=15 and x<=19){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
        }
        if(y==7 or y==16 or y==25){
          int low[10]={255,255,255,0,255,255,255,255,255,255};
          
          setGNDs(low);
          
          if(x>=17 and x<=21){
          ShiftPWM.SetRGB(0,red,green,blue);
          }
          if(x>=18 and x<=22){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=19 and x<=23){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
        }
        if(y==8 or y==17 or y==26){
          int low[10]={255,255,255,255,255,255,0,255,255,255};
          
          setGNDs(low);
          
          if(x>=20 and x<=24){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x==24){
          ShiftPWM.SetRGB(0,red,green,blue);
          }
          if(x>=1 and x<=4){
            ShiftPWM.SetRGB(0,r2,g2,b2);
          }
        }
        if(y==9 or y==18 or y==27){
          int low[10]={255,255,255,255,255,255,255,255,255,0};
          
          setGNDs(low);
          
          if(x>=21 and x<=24){
            ShiftPWM.SetRGB(2,red,green,blue);
          }
          if(x==1){
            ShiftPWM.SetRGB(2,r2,g2,b2);
          }
          if(x>=22 and x<=24){
            ShiftPWM.SetRGB(1,red,green,blue);
          }
          if(x>=1 and x<=2){
            ShiftPWM.SetRGB(1,r2,g2,b2);
          }
          if(x>=23 and x<=24){
            ShiftPWM.SetRGB(0,red,green,blue);
          }
          if(x>=1 and x<=3){
            ShiftPWM.SetRGB(0,r2,g2,b2);
          }
        }
      delay(1);
      }
    }
  }  
}      
void counter_clockwise(){
  for(int a=1; a<=3; a+=2){
    int low[10]={255,255,255,255,255,255,255,255,255,255};
    for(int b=1; b<=16; b+=1){
      if (b==1 or b==9){
        if (red>0){
          red=0;
          green = 255;
        }
        else if (green>0){
          green=0;
          blue=255;
        }
        else if (blue>0){
          blue=0;
          red=255;
        }
      }
      if (b==1 or b==2){
        low[a]=0;
        low[a+3]=0;
        low[a+6]=0;
        ShiftPWM.SetRGB(0,red,green,blue);
        ShiftPWM.SetRGB(1,red,green,blue);
        ShiftPWM.SetRGB(2,red,green,blue);
        
        setGNDs(low);
        
       delay(135);
     }
     if (b==3 or b==4 or b==5 or b==6 or b==7 or b==8){
      for(int x=1; x<=12; x+=1){
          for(int c=1; c<=3; c+=1){
            int low[10]={255,255,255,255,255,255,255,255,255,255};
            low[4-c]=0;
            low[7-c]=0;
            low[10-c]=0;
            ShiftPWM.SetRGB(0,0,0,0);
            ShiftPWM.SetRGB(1,0,0,0);
            ShiftPWM.SetRGB(2,0,0,0);
            ShiftPWM.SetRGB(c-1,red,green,blue);
            
            setGNDs(low);
        
            delay(1);
          }
        }}
      if (b==9 or b==10){
        int low[10]={255,0,0,0,0,0,0,0,0,0};
        ShiftPWM.SetRGB(0,0,0,0);
        ShiftPWM.SetRGB(1,0,0,0);
        ShiftPWM.SetRGB(2,0,0,0);
        if (a==1){
          ShiftPWM.SetRGB(2,red,green,blue); 
        }
        if (a==3){
          ShiftPWM.SetRGB(0,red,green,blue); 
        }
        
        setGNDs(low);
        
        delay(135);
      }
      if (b==11 or b==12 or b==13 or b==14 or b==15 or b==16){
        for(int x=1; x<=12; x+=1){
          for(int c=3; c>=1; c-=1){
            int low[10]={255,255,255,255,255,255,255,255,255,255};
            low[c]=0;
            low[c+3]=0;
            low[c+6]=0;
            ShiftPWM.SetRGB(0,0,0,0);
            ShiftPWM.SetRGB(1,0,0,0);
            ShiftPWM.SetRGB(2,0,0,0);
            ShiftPWM.SetRGB(c-1,red,green,blue);

            setGNDs(low);
            
            delay(1);
          }
        }
      }
  }}}
void clockwise(){
  red = 255;
  green, blue = 0;
  for(int a=3; a>=1; a-=2){
    int low[10]={255,255,255,255,255,255,255,255,255,255};
    for(int b=16; b>=1; b-=1){
      if (b==1 or b==9){
        if (red>0){
          red=0;
          blue = 255;
        }
        else if (blue>0){
          blue=0;
          green=255;
        }
        else if (green>0){
          green=0;
          red=255;
        }
      }
      if (b==1 or b==2){
        low[a]=0;
        low[a+3]=0;
        low[a+6]=0;
        ShiftPWM.SetRGB(0,red,green,blue);
        ShiftPWM.SetRGB(1,red,green,blue);
        ShiftPWM.SetRGB(2,red,green,blue);
        
        setGNDs(low);
        
       delay(135);
     }
     if (b==3 or b==4 or b==5 or b==6 or b==7 or b==8){
        for(int x=1; x<=12; x+=1){
          for(int c=1; c<=3; c+=1){
            int low[10]={255,255,255,255,255,255,255,255,255,255};
            low[4-c]=0;
            low[7-c]=0;
            low[10-c]=0;
            ShiftPWM.SetRGB(0,0,0,0);
            ShiftPWM.SetRGB(1,0,0,0);
            ShiftPWM.SetRGB(2,0,0,0);
            ShiftPWM.SetRGB(c-1,red,green,blue);
            
            setGNDs(low);
            
            delay(1);
          }
        }
      }
      if (b==9 or b==10){
        int low[10]={255,0,0,0,0,0,0,0,0,0};
        ShiftPWM.SetRGB(0,0,0,0);
        ShiftPWM.SetRGB(1,0,0,0);
        ShiftPWM.SetRGB(2,0,0,0);
        if (a==1){
          ShiftPWM.SetRGB(2,red,green,blue); 
        }
        if (a==3){
          ShiftPWM.SetRGB(0,red,green,blue); 
        }
        
        setGNDs(low);
  
        delay(135);
      }
      if (b==11 or b==12 or b==13 or b==14 or b==15 or b==16){
        for(int x=1; x<=12; x+=1){
          for(int c=3; c>=1; c-=1){
            int low[10]={255,255,255,255,255,255,255,255,255,255};
            low[c]=0;
            low[c+3]=0;
            low[c+6]=0;
            ShiftPWM.SetRGB(0,0,0,0);
            ShiftPWM.SetRGB(1,0,0,0);
            ShiftPWM.SetRGB(2,0,0,0);
            ShiftPWM.SetRGB(c-1,red,green,blue);
            
            setGNDs(low);
            
            delay(1);
          }
        }
      }
  }}}
void rotating_counter_clockwise(){
  int low[10]={255,255,255,255,255,255,255,255,255,255};
  for(int l=1; l<=8; l+=1){
    if (x==0){
      if (red > 0){
        red -=5;
        green -=5;
        blue -=5;
      }
      if (red<=0) x=1;}
    else if(x==1){
      if (red < 255){
        red +=5;
        green +=5;
        blue +=5;
      }
      if (red>=255) x=0;}
    if (l==1){
      low[2]=0;
      low[5]=0;
      low[8]=0;
      ShiftPWM.SetRGB(0,red,green,blue);
      ShiftPWM.SetRGB(1,red,green,blue);
      ShiftPWM.SetRGB(2,red,green,blue);
      for (int i = 1; i <= 9; i += 1){
          if(i <= 7){
            ShiftPWM.SetOne(8+i, low[i]);
          }
          else if(i==8){
            digitalWrite(2, low[i]); 
          }
          else{
            digitalWrite(3, low[i]); 
          }
        }
      delay(90);
    }
    if (l==2 or l==3 or l==4){
      for(int x=1; x<=10; x+=1){
        for(int a=1; a<=3; a+=1){
          int low[10]={255,255,255,255,255,255,255,255,255,255};
          low[4-a]=0;
          low[7-a]=0;
          low[10-a]=0;
          ShiftPWM.SetRGB(0,0,0,0);
          ShiftPWM.SetRGB(1,0,0,0);
          ShiftPWM.SetRGB(2,0,0,0);
          ShiftPWM.SetRGB(a-1,red,green,blue);
          
          setGNDs(low);
        
          delay(1);
        }
      }}
    if (l==5){
      int low[10]={255,0,0,0,0,0,0,0,0,0};
      ShiftPWM.SetRGB(0,0,0,0);
      ShiftPWM.SetRGB(1,red,green,blue); 
      ShiftPWM.SetRGB(2,0,0,0);
      
      setGNDs(low);
        
      delay(90);
    }
    if (l==6 or l==7 or l==8){
      for(int x=1; x<=10; x+=1){
        for(int a=3; a>=1; a-=1){
          int low[10]={255,255,255,255,255,255,255,255,255,255};
          low[a]=0;
          low[a+3]=0;
          low[a+6]=0;
          ShiftPWM.SetRGB(0,0,0,0);
          ShiftPWM.SetRGB(1,0,0,0);
          ShiftPWM.SetRGB(2,0,0,0);
          ShiftPWM.SetRGB(a-1,red,green,blue);
          
          setGNDs(low);
        
          delay(1);
        }
      }}
      }}
void rotating_clockwise(){
  int low[10]={255,255,255,255,255,255,255,255,255,255};
  for(int l=8; l>=1; l-=1){
    if (x==0){
      if (red > 0){
        red -=5;
        green -=5;
        blue -=5;
      }
      if (red<=0) x=1;}
    else if(x==1){
      if (red < 255){
        red +=5;
        green +=5;
        blue +=5;
      }
      if (red>=255) x=0;}
    if (l==1){
      low[2]=0;
      low[5]=0;
      low[8]=0;
      ShiftPWM.SetRGB(0,red,green,blue);
      ShiftPWM.SetRGB(1,red,green,blue);
      ShiftPWM.SetRGB(2,red,green,blue);
      
      setGNDs(low);
        
      delay(90);
    }
    if (l==2 or l==3 or l==4){
      for(int x=1; x<=10; x+=1){
        for(int a=1; a<=3; a+=1){
          int low[10]={255,255,255,255,255,255,255,255,255,255};
          low[4-a]=0;
          low[7-a]=0;
          low[10-a]=0;
          ShiftPWM.SetRGB(0,0,0,0);
          ShiftPWM.SetRGB(1,0,0,0);
          ShiftPWM.SetRGB(2,0,0,0);
          ShiftPWM.SetRGB(a-1,red,green,blue);
          
          setGNDs(low);
        
          delay(1);
        }
      }}
    if (l==5){
      int low[10]={255,0,0,0,0,0,0,0,0,0};
      ShiftPWM.SetRGB(0,0,0,0);
      ShiftPWM.SetRGB(1,red,green,blue); 
      ShiftPWM.SetRGB(2,0,0,0);
      
      setGNDs(low);
        
      delay(90);
    }
    if (l==6 or l==7 or l==8){
      for(int x=1; x<=10; x+=1){
        for(int a=3; a>=1; a-=1){
          int low[10]={255,255,255,255,255,255,255,255,255,255};
          low[a]=0;
          low[a+3]=0;
          low[a+6]=0;
          ShiftPWM.SetRGB(0,0,0,0);
          ShiftPWM.SetRGB(1,0,0,0);
          ShiftPWM.SetRGB(2,0,0,0);
          ShiftPWM.SetRGB(a-1,red,green,blue);
          
          setGNDs(low);
        
          delay(1);
        }
      }}
      }}
void changing_colours(){
  for (int h=0; h<=9; h+=1){
    for (int i=0; i<=21; i+=1){
      if (set[0+3*i] < 255 and set[1+3*i] == 0 and set[2+3*i] == 255){
        set[0+3*i] += 1;
      }
      else if (set[0+3*i] == 255 and set[1+3*i] == 0 and set[2+3*i] > 0){
        set[2+3*i] -= 1;
      }
      else if (set[0+3*i] == 255 and set[1+3*i] < 255 and set[2+3*i] == 0){
        set[1+3*i] += 1;
      }
      else if (set[0+3*i] > 0 and set[1+3*i] == 255 and set[2+3*i] == 0){
        set[0+3*i] -= 1;
      }
      else if (set[0+3*i] == 0 and set[1+3*i] == 255 and set[2+3*i] < 255){
        set[2+3*i] += 1;
      }
      else if (set[0+3*i] == 0 and set[1+3*i] > 0 and set[2+3*i] == 255){
        set[1+3*i] -= 1;
      }}
    //ShiftPWM.SetRGB(h,0,0,0);  
    int low[10]={255,255,255,255,255,255,255,255,255,255};
    if (h==1){
      low[h]=0;
    ShiftPWM.SetRGB(0,set[0],set[1],set[2]);
    ShiftPWM.SetRGB(1,set[3],set[4],set[5]);
    ShiftPWM.SetRGB(2,set[6],set[7],set[8]);
    }
    if (h==2){
      low[h]=0;
    ShiftPWM.SetRGB(2,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(0,set[3],set[4],set[5]);
    ShiftPWM.SetRGB(1,set[6],set[7],set[8]);
    }
    if (h==3){
      low[h]=0;
    ShiftPWM.SetRGB(1,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(2,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(0,set[6],set[7],set[8]);
    }
    if (h==4){
      low[h]=0;
    ShiftPWM.SetRGB(2,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(0,set[3],set[4],set[5]);
    ShiftPWM.SetRGB(1,set[6],set[7],set[8]);
    }
    if (h==5){
      low[h]=0;
    ShiftPWM.SetRGB(1,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(2,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(0,set[6],set[7],set[8]);
    }
    if (h==6){
      low[h]=0;
    ShiftPWM.SetRGB(0,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(1,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(2,set[15],set[16],set[17]);
    }
    if (h==7){
      low[h]=0;
    ShiftPWM.SetRGB(1,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(2,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(0,set[6],set[7],set[8]);
    }
    if (h==8){
      low[h]=0;
    ShiftPWM.SetRGB(0,set[9],set[10],set[11]);
    ShiftPWM.SetRGB(1,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(2,set[15],set[16],set[17]);
    }
    if (h==9){
      low[h]=0;
    ShiftPWM.SetRGB(2,set[18],set[19],set[20]);
    ShiftPWM.SetRGB(0,set[12],set[13],set[14]);
    ShiftPWM.SetRGB(1,set[15],set[16],set[17]);
    }
    
    setGNDs(low);
        
    delay(1);
  }}
void solid_colours(){
  int low[10]={255,0,0,0,0,0,0,0,0,0};  
  for (int i = 1; i <= 9; i += 1){
          setGNDs(low);
        }
  for (int b = 1; b < 13; b += 1){
    for (int c = 0; c <= 100; c = c + 1){
      if (b == 1){
        red = c*2.55; }
      if (b == 2){
        red = c*2.55;
        green = c*0.2; }
      if (b == 3){
        red = c*2.55;
        green = c*2.55; }
      if (b == 4){
        red = c*1.25;
        green = c*2.55; }
      if (b == 5){
        green = c*2.55; }
      if (b == 6){
        green = c*2.55;
        blue = c*1.25; }
      if (b == 7){
        green = c*2.55;
        blue = c*2.55; }
      if (b == 8){
        green = c*1.25;
        blue = c*2.55; }
      if (b == 9){
        blue = c*2.55; }
      if (b == 10){
        blue = c*2.55;
        red = c*1.25; }
      if (b == 11){
        blue = c*2.55;
        red = c*2.55; }
      if (b == 12){
        blue = c*1.25;
        red = c*2.55; }
      ShiftPWM.SetRGB(2,red,green,blue);
      ShiftPWM.SetRGB(1,red,green,blue);
      ShiftPWM.SetRGB(0,red,green,blue);
      delay(1);
    }
    for (int c = 100; c >= 0; c = c - 1){
      if (b == 1){
        red = c*2.55; }
      if (b == 2){
        red = c*2.55;
        green = c*0.2; }
      if (b == 3){
        red = c*2.55;
        green = c*2.55; }
      if (b == 4){
        red = c*1.25;
        green = c*2.55; }
      if (b == 5){
        green = c*2.55; }
      if (b == 6){
        green = c*2.55;
        blue = c*1.25; }
      if (b == 7){
        green = c*2.55;
        blue = c*2.55; }
      if (b == 8){
        green = c*1.25;
        blue = c*2.55; }
      if (b == 9){
        blue = c*2.55; }
      if (b == 10){
        blue = c*2.55;
        red = c*1.25; }
      if (b == 11){
        blue = c*2.55;
        red = c*2.55; }
      if (b == 12){
        blue = c*1.25;
        red = c*2.55; }
      ShiftPWM.SetRGB(2,red,green,blue);
      ShiftPWM.SetRGB(1,red,green,blue);
      ShiftPWM.SetRGB(0,red,green,blue);
      delay(1);
  } }
}

void single_random(){
  ShiftPWM.SetAll(LOW);
  int low[9]={255,255,255,255,255,255,255,255,255};
  low[random(0,9)]=0;
  
  setGNDs(low);
        
  ShiftPWM.SetRGB(random(0,3), random(0,256), random(0,256), random(256));
  delay(30);
}

void random_cube(){
    ShiftPWM.SetAll(LOW);
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    int r1 = random(0,256);
    int r2 = random(0,256);
    int r3 = random(0,256);
    ShiftPWM.SetRGB(0, r1, r2, r3);
    ShiftPWM.SetRGB(1, r1, r2, r3);
    ShiftPWM.SetRGB(2, r1, r2, r3);
    delay(50);
  } 
void all_random(){
    ShiftPWM.SetRGB(0,0,0,0);
    ShiftPWM.SetRGB(1,0,0,0);
    ShiftPWM.SetRGB(2,0,0,0);
    for (int i = 0; i <= 9; i = i + 1){
      int low[10]={255,255,255,255,255,255,255,255,255,255};
      low[i]=0; 

      setGNDs(low);

      ShiftPWM.SetRGB(0,random(0,256),random(0,256),random(0,256));
      ShiftPWM.SetRGB(1,random(0,256),random(0,256),random(0,256));
      ShiftPWM.SetRGB(2,random(0,256),random(0,256),random(0,256));
      delay(1);
    }    
  }
void rain(){
  ShiftPWM.SetRGB(0, 0,0,0);
  ShiftPWM.SetRGB(1, 0,0,0);
  ShiftPWM.SetRGB(2, 0,0,0);
  ShiftPWM.SetRGB(random(0,3),random(0,256),random(0,256),random(0,256));
//  for(int j=random(7,10); j>=1; j-=3){ //for earlier setup
//      low[j] = 0;

  int n = random(1,4)*3;
  for(int j=0; j<3; j++){
    
    int low[10] = {255,255,255,255,255,255,255,255,255,255};
    low[n-j]=0;
    
    setGNDs(low);
    
    delay(130);
  }
}

void random_on(){
  int colour[3][3]={{0,255,0},{0,255,0},{0,0,255}};
  for(int rep=0; rep<=0; rep++){
   int u=0;
   int numbers[3][9] = {{0,1,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8}};
   const int count = sizeof numbers[0] / sizeof numbers[0][0];
   for (int h=0; h<=3; h++){
     for (int i=0; i < count; i++){
      int n = random(0, count);
      int temp = numbers[h][n];
      numbers[h][n] = numbers[h][i];
      numbers[h][i] = temp;
     }
   }
   for(int i=-1; i<=8; i++){
   for(int g=1; g<=149; g++){
    ShiftPWM.SetRGB(0,0,0,0);
    ShiftPWM.SetRGB(1,0,0,0);
    ShiftPWM.SetRGB(2,0,0,0);
    int low[10] = {255,255,255,255,255,255,255,255,255,255};
    
    setGNDs(low);
    
    if(g%3==0){
      ShiftPWM.SetRGB(0,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    if(g%3==1){
      ShiftPWM.SetRGB(1,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    if(g%3==2){
      ShiftPWM.SetRGB(2,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    u = i;
    if(floor(g/50)==1){
      if(g%3==1){
        u+=1;
      }
    }
    if(floor(g/50)==2){
      if(g%3==1 or g%3==2){
        u+=1;
      }
    }
    for(int j=0; j<=u; j++){
      int n = numbers[g%3][j];     
      if(n<7){
        ShiftPWM.SetOne(n+9, 0);  
      }
      if(n>=7){
        digitalWrite(n-5, 0);
      }
    }
    //delay(1);
    delayMicroseconds(500);
   }
   }
   for(int i=-1; i<=8; i++){
   for(int g=1; g<=149; g++){
    ShiftPWM.SetRGB(0,0,0,0);
    ShiftPWM.SetRGB(1,0,0,0);
    ShiftPWM.SetRGB(2,0,0,0);
    int low[10] = {0,0,0,0,0,0,0,0,0,0};
    
    setGNDs(low);
    
    if(g%3==0){
      ShiftPWM.SetRGB(0,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    if(g%3==1){
      ShiftPWM.SetRGB(1,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    if(g%3==2){
      ShiftPWM.SetRGB(2,colour[rep][0],colour[rep][1],colour[rep][2]);
    }
    u = i;
    if(floor(g/50)==1){
      if(g%3==1){
        u+=1;
      }
    }
    if(floor(g/50)==2){
      if(g%3==1 or g%3==2){
        u+=1;
      }
    }
    for(int j=0; j<=u; j++){
      int n = numbers[g%3][j];     
      if(n<7){
        ShiftPWM.SetOne(n+9, 255);  
      }
      if(n>=7){
        digitalWrite(n-5, 255);
      }
    }
    //delay(1);
    delayMicroseconds(500);
   }
   }
   ShiftPWM.SetRGB(0,0,0,0);
   ShiftPWM.SetRGB(1,0,0,0);
   ShiftPWM.SetRGB(2,0,0,0);
   delay(25);
  }
}
void setGNDs(int low[10]){
  for (int i = 1; i <= 9; i += 1){
      if(i <= 7){
        ShiftPWM.SetOne(8+i, low[i]);
      }
    }  
    digitalWrite(2, low[8]); 
    digitalWrite(3, low[9]);
}
      
