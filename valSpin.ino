void valSpin(byte* vals){

  if (j == 0){ 
    switch ( (byte) random(2) ) {
    case 0:
      valSpinIncr = 1;
      valSpinSteps[0]  = 15;
      valSpinSteps[1]  = 14;
      valSpinSteps[2]  = 13;
      valSpinSteps[3]  = 12;
      valSpinSteps[4]  = 11;
      valSpinSteps[5]  = 10;
      valSpinSteps[6]  = 9;
      valSpinSteps[7]  = 8;
      valSpinSteps[8]  = 7;
      valSpinSteps[9]  = 6;
      valSpinSteps[10] = 5;
      valSpinSteps[11] = 4;
      valSpinSteps[12] = 3;
      valSpinSteps[13] = 2;
      valSpinSteps[14] = 1;
      valSpinSteps[15] = 0;
    case 1:
      valSpinSteps[0]  = 15;
      valSpinSteps[1]  = 12;
      valSpinSteps[2]  = 10;
      valSpinSteps[3]  = 8;
      valSpinSteps[4]  = 6;
      valSpinSteps[5]  = 4;
      valSpinSteps[6]  = 2;
      valSpinSteps[7]  = 0;
      valSpinSteps[8]  = 15;
      valSpinSteps[9]  = 12;
      valSpinSteps[10] = 10;
      valSpinSteps[11] = 8;
      valSpinSteps[12] = 6;
      valSpinSteps[13] = 4;
      valSpinSteps[14] = 2;
      valSpinSteps[15] = 0;
      break;
    }    
  }

  if (j%4 == 0) {

    for (byte pix=0; pix<NPINS; pix +=1){
      valSpinInds[pix] += 1;

      if (valSpinInds[pix] > NPINS - 1){
        valSpinInds[pix] = 0;
      }
      else{
        if(valSpinInds[pix] <= 0){
          valSpinInds[pix] = NPINS - 1;
        }
      }
    }
  }

  for (byte pix=0; pix<NPINS; pix +=1){
    vals[pix] = valSpinVals[valSpinSteps[valSpinInds[pix]]];
  } 
}

