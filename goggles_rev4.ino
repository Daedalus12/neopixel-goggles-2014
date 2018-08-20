#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 3, NEO_GRB + NEO_KHZ800);

#define NPIN 16
#define NSTEPS 64

// define universal constants
const float pi = 3.14159; 
const float tau = pi*2;
float cosValues[NSTEPS];

// define global parameters
const int pause = 20;
const int PIN = 3;
const byte VALMAX = 31;
const byte VALMIN = 3;

// define derived parameters
const byte VALAVG = ((float)VALMAX + (float)VALMIN)/2.0;
const byte VALAMP = (float)VALMAX - (((float)VALMAX + (float)VALMIN)/2.0);

// initialize arrays of 0-255 values for brightness and colors
byte vals[NPIN];
byte sats[NPIN];
byte hues[NPIN];

boolean reset;

byte valSpinN = 1;
byte valSpinIncr = 1;

byte valSpinVals[16];
byte valSpinSteps[16];
byte valSpinInds[16];

void setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);

  for (byte k=0; k<16; k++) {
    valSpinVals[k] = (float)VALMAX * (float)k/15.;
    valSpinInds[k] = k;
    vals[k] = 0;
    sats[k] = 0;
    hues[k] = 0;
  }

  for (int i=0; i<NSTEPS; i++) {
    cosValues[i] = cos(2*pi*(float)i/NSTEPS);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(cosValues[i]);

  }
}

float theta;
float dtheta = tau/64.;
unsigned long j;

byte nCycles;

void loop(){

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorConstant(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorSpin(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  

  nCycles = random(3) + 1;
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3);
  theta = pi/2.;

  for (j=0; j<64*nCycles; j++){
    valSpin(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  

  nCycles = random(3) + 3;

  for (j=0; j<NSTEPS*nCycles; j++){
    if (j%NSTEPS == 0 || j == 0) {
      colorSetJewel(hues, sats);      
    }
    
    valPulse(vals, cosValues[j%NSTEPS]);
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

