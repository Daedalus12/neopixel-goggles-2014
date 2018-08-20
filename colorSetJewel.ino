void colorSetJewelMix(byte* hues, byte* sats) {
  for (byte k = 0; k < NPIN; ++k) {
    sats[k] = 255;
    if (random(5) == 0) {
      hues[k] = random(0, 28);
    } else {
    hues[k] = random(140, 184);
    }
  }
}

void colorSetJewelAll(byte* hues, byte* sats, bool a ) {
  for (byte k = 0; k < NPIN; ++k) {
    sats[k] = 255;
    if (a) {
      hues[k] = random(0, 28);
    } else {
    hues[k] = random(140, 184);
    }
  }
}


