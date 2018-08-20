void colorJewelSpin(byte* hues, byte* huesA, byte* huesB, int j) {
  byte activePin = j / 4;
  byte tailLength = 6;

  for (byte k = 0; k < NPINS; ++k) {
    byte n = (tailLength - (activePin-k))%NPINS;
    if (n > tailLength) n = 0;
    float ratio = static_cast<float>(n)/tailLength;
    hues[k] = colorBlend(huesA[k], huesB[k], ratio);
  }
}

