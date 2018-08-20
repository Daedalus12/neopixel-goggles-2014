uint32_t HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val){

  // initialize RGB values
  uint32_t r,g,b;

  int base;
  
  if (sat==0) {
    r = val;
    g = val;
    b = val;
 
  } else {
    base = ((255 - sat) * val) >> 8;
    int H = hue * 359. / 255.;
    switch (H/60) {

      case 0:
        r = val;
        g = (((val - base) * H) / 60) + base;
        b = base;
        break;

      case 1:
        r = (((val-base)*(60-(H%60)))/60)+base;
        g = val;
        b = base;
        break;
  
      case 2:
        r = base;
        g = val;
        b = (((val-base)*(H%60))/60)+base;
        break;
  
      case 3:
        r = base;
        g = (((val-base)*(60-(H%60)))/60)+base;
        b = val;
        break;
  
      case 4:
        r = (((val-base)*(H%60))/60)+base;
        g = base;
        b = val;
        break;
  
      case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(H%60)))/60)+base;
        break;
    }
  }
  return r << 16 | g << 8 | b;
}

uint32_t hsi2rgb(int H, byte _S, byte _I) {
    float S = (float)_S/255.0;
    float I = (float)_I/255.0; 
  
    uint8_t r, g, b;
    H = fmod(H, 360); // cycle H around to 0-360 degrees
    H = 3.14159*H / (float)180; // Convert to radians.
    S = S>0 ? (S<1 ? S : 1) : 0; // clamp S and I to interval [0,1]
    I = I>0 ? (I<1 ? I : 1) : 0;

    // Math! Thanks in part to Kyle Miller.
    if (H < 2.09439) {
        r = 255 * I / 3 * (1 + S*cos(H) / cos(1.047196667 - H));
        g = 255 * I / 3 * (1 + S*(1 - cos(H) / cos(1.047196667 - H)));
        b = 255 * I / 3 * (1 - S);
    }
    else if (H < 4.188787) {
        H = H - 2.09439;
        g = 255 * I / 3 * (1 + S*cos(H) / cos(1.047196667 - H));
        b = 255 * I / 3 * (1 + S*(1 - cos(H) / cos(1.047196667 - H)));
        r = 255 * I / 3 * (1 - S);
    }
    else {
        H = H - 4.188787;
        b = 255 * I / 3 * (1 + S*cos(H) / cos(1.047196667 - H));
        r = 255 * I / 3 * (1 + S*(1 - cos(H) / cos(1.047196667 - H)));
        g = 255 * I / 3 * (1 - S);
    }

    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

