void colorJewelWaterfall(byte* hues, byte* huesA, byte* huesB, int j) {
  int i = j / 5;
  
  int a = TOP_PIN - i;
  int b = TOP_PIN + i;
  if (a < 0) a += NPINS; 
  else if (a > NPINS - 1) a -= NPINS;
  if (b < 0) b += NPINS; 
  else if (b > NPINS - 1) b -= NPINS;
    
  for (int k = 0; k < NPINS; ++k) {

    if (k == a) hues[k] = huesB[k];
    if (k == b) hues[k] = huesB[k];
  }
}

