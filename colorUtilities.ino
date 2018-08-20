byte colorBlend(const byte& colorA, const byte& colorB, const float& ratio){
  if (ratio <= 0.001) return colorA;
  if (ratio >= 0.999) return colorB;
  
  byte cmax = max(colorA, colorB);
  byte cmin = min(colorA, colorB);
  
  byte fwdDelta = cmax - cmin;
  byte revDelta = cmin + (255 - cmax);
  byte magnitude = min(fwdDelta, revDelta);
  short dir = (colorB > colorA ? 1 : -1) * (fwdDelta < revDelta ? 1 : -1);

  // Make this smarter, so when starting from random numbers, one side isn't closer.
  dir = 1;

  float result = colorA + static_cast<float>(magnitude)*ratio*dir;  
  return static_cast<byte>(result)%255;
}

