#include <Adafruit_NeoPixel.h>

#define NPINS 16
#define NSTEPS 64
#define TOP_PIN 0
#define PIN 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPINS, PIN, NEO_GRB + NEO_KHZ800);

// define universal constants
const float pi = 3.14159; 

// define global parameters
const int pause = 20;
const byte VALMAX = 31;
const byte VALMIN = 3;

// define derived parameters
const byte VALAVG = ((float)VALMAX + (float)VALMIN)/2.0;
const byte VALAMP = (float)VALMAX - (((float)VALMAX + (float)VALMIN)/2.0);
float cosValues[NSTEPS];

// initialize arrays of 0-255 values for brightness and colors
byte vals[NPINS];
byte sats[NPINS];
byte hues[NPINS];
byte huesA[NPINS];
byte huesB[NPINS];

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
  }
}

unsigned long j;

byte nCycles;

void loop(){

  nCycles = random(3) + 1;

  colorSetJewelAll(huesA, sats, false);
  colorSetJewelAll(huesB, sats, true);
  for (byte i=0; i<NPINS; ++i) hues[i] = huesA[i];
  for (j=0; j<NSTEPS*nCycles; j++){
    if (j%NSTEPS == 0 && j > 0) {
        for (byte i=0; i<NPINS; ++i) huesB[i] = huesA[i];
        for (byte i=0; i<NPINS; ++i) huesA[i] = hues[i];
    }
    valPulse(vals, cosValues[j%NSTEPS]);
    colorJewelWaterfall(hues, huesA, huesB, j%NSTEPS);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3) + 1;

  for (j=0; j<NSTEPS*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorConstant(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3) + 1;

  colorSetJewelAll(huesA, sats, false);
  colorSetJewelAll(huesB, sats, true);
  for (j=0; j<NSTEPS*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorJewelSpin(hues, huesA, huesB, j%NSTEPS);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3) + 1;

  for (j=0; j<NSTEPS*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorSpin(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  

  nCycles = random(3) + 1;

  colorSetJewelAll(huesA, sats, false);
  colorSetJewelAll(huesB, sats, true);
  for (j=0; j<NSTEPS*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorShift(hues, huesA, huesB, j%NSTEPS);
    update(vals, sats, hues);
    delay(pause);
  }
  
  nCycles = random(3) + 1;

  for (j=0; j<NSTEPS*nCycles; j++){
    valPulse(vals, cosValues[j%NSTEPS]);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }

  nCycles = random(3);

  for (j=0; j<NSTEPS*nCycles; j++){
    valSpin(vals);
    colorCycle(hues, sats);
    update(vals, sats, hues);
    delay(pause);
  }  

  nCycles = random(3) + 3;

  for (j=0; j<NSTEPS*nCycles; j++){
    if (j%NSTEPS == 0 || j == 0) {
      colorSetJewelMix(hues, sats);      
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

