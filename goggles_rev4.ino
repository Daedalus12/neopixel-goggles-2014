#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 3, NEO_GRB + NEO_KHZ800);

// define universal constants
const float pi = 3.14159; 
const float tau = pi*2;

// define global parameters
const int pause = 20;
const int PIN = 3;
const int NPIN = 16;
const byte VALMAX = 31;
const byte VALMIN = 3;
const float DTHETA = tau/64.;

// define derived parameters
const byte VALAVG = ((float)VALMAX + (float)VALMIN)/2.0;
const byte VALAMP = (float)VALMAX - (((float)VALMAX + (float)VALMIN)/2.0);

// initialize arrays of 0-255 values for brightness and colors
byte vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte sats[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte hues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

boolean reset;

byte valSpinN = 1;
byte valSpinIncr = 1;

byte valSpinVals[]  = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38};
byte valSpinSteps[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte valSpinInds[]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);

  for (byte k=0; k<16; k++) {
    valSpinVals[k] = (float)VALMAX * (float)k/15.;
  }
  
  for (byte s=0; s<16; s++){
    valSpinInds[s] = s;
  }


}

float theta;
float dtheta = tau/64.;
byte j;

byte nCycles;

template<class T>
trigScale(T& ret, const float& val, const T& valMin, const T& valMax) {
    ret = valMin + 0.5*(valMax - valMin)*(1 + val);
}

void loop(){

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valPulse(vals);
    colorConstant(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){

    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }

    valPulse(vals);
    colorSpin(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valPulse(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3);
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    theta += dtheta;
    if (theta > tau){
      theta -= tau;
    }
    valSpin(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  
  
  

}

void update(byte vals[], byte sats[], byte hues[]){

  for (byte i=0; i<16; i++){
    strip.setPixelColor(i,HSVtoRGB(hues[i], sats[i], vals[i]));
  }
  strip.show();
}

