bool pick(unsigned long pin, unsigned long breakA, int breakB){
  bool b;
  if (breakA < breakB){
    b = pin <= breakA || pin > breakB; 
  }
  else{
    b = breakB < pin && pin <= breakA;     
  }
  return b;
}

void colorShift(byte* hues, byte* huesA, byte* huesB, int j) {
  unsigned long breakA, breakB;
  j /= 4;
  breakA = j%NPIN;
  breakB = (breakA + NPIN/2)%NPIN;
  
  for (byte k = 0; k < NPIN; ++k) {
    if (pick(k, breakA, breakB)) {
      hues[k] = huesA[k];
    } else {
      hues[k] = huesB[k];
    }
  }
}

