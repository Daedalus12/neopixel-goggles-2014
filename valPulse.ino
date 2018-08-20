// declare counter for tracking brightnesses
byte val;

void valPulse(byte* vals, float cosValue) {
  
  val = VALAVG - (float)VALAMP*cosValue;
  for (byte i=0; i<16; i++) {
    vals[i] = val;
  }
}

