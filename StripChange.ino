/*
   Hier werden die Farben der einzelnen LEDs neu eingestellt
*/

void GetRandomLED (void) {  //neue Ziel-Farben holen
  if (IsDark) {
    for (int i = 0; i < STRING_LEN; i++) {
      NewLed[i].Rot = (byte)random(0, MAX_LED_LOW);
      NewLed[i].Gruen = (byte)random(0, MAX_LED_LOW);
      NewLed[i].Blau = (byte)random(0, MAX_LED_LOW);
      NewLed[i].Status = 0;
    }
  }
  else {
    for (int i = 0; i < STRING_LEN; i++) {
      NewLed[i].Rot = (byte)random(0, MAX_LED_HIGH);
      NewLed[i].Gruen = (byte)random(0, MAX_LED_HIGH);
      NewLed[i].Blau = (byte)random(0, MAX_LED_HIGH);
      NewLed[i].Status = 0;
    }
  }
}

int OldToNew(int i) {
  int RunLoop = 0;

  RunLoop++;

  //Rot
  if (NewLed[i].Rot == OldLed[i].Rot) {
    OldLed[i].Status |= 0b00000001;
  }
  else if (OldLed[i].Rot < NewLed[i].Rot) {
    OldLed[i].Rot++;
    OldLed[i].Status &= 0b11111110;
  }
  else if (OldLed[i].Rot > NewLed[i].Rot) {
    OldLed[i].Rot--;
    OldLed[i].Status &= 0b11111110;
  }
  //Gruen
  if (NewLed[i].Gruen == OldLed[i].Gruen) {
    OldLed[i].Status |= 0b00000010;
  }
  else if (OldLed[i].Gruen < NewLed[i].Gruen) {
    OldLed[i].Gruen++;
    OldLed[i].Status &= 0b11111101;
  }
  else if (OldLed[i].Gruen > NewLed[i].Gruen) {
    OldLed[i].Gruen--;
    OldLed[i].Status &= 0b11111101;
  }
  //Blau
  if (NewLed[i].Blau == OldLed[i].Blau) {
    OldLed[i].Status |= 0b00000100;
  }
  else if (OldLed[i].Blau < NewLed[i].Blau) {
    OldLed[i].Blau++;
    OldLed[i].Status &= 0b11111011;
  }
  else if (OldLed[i].Blau > NewLed[i].Blau) {
    OldLed[i].Blau--;
    OldLed[i].Status &= 0b11111011;
  }

  strip.setPixelColor(i, OldLed[i].Rot, OldLed[i].Gruen, OldLed[i].Blau);
  strip.show();

  if (OldLed[i].Status == 7) {  //alle Farben sind neu
    OldLed[i].Status = 0;
    return (1); //fertig
  }
  else
    return (0);
}

void StripOff(void) {
  for (int i = 0; i < STRING_LEN; i++) {
    OldLed[i].Rot = OldLed[i].Gruen = OldLed[i].Blau = OldLed[i].Status = 0;
    strip.setPixelColor(i, 0, 0, 0);
    GetRandomLED();
  }
  strip.show();
}

//******* Pixel

void GetRandomPixel (void) {  //neue Ziel-Farben holen
  if (IsDark) {
    for (int i = 0; i < NUMPIXELS; i++) {
      NewPix[i].Rot = (byte)random(0, MAX_PIX_LOW);
      NewPix[i].Gruen = (byte)random(0, MAX_PIX_LOW);
      NewPix[i].Blau = (byte)random(0, MAX_PIX_LOW);
      NewPix[i].Status = 0;
    }
  }
  else {
    for (int i = 0; i < NUMPIXELS; i++) {
      NewPix[i].Rot = (byte)random(0, MAX_PIX_HIGH);
      NewPix[i].Gruen = (byte)random(0, MAX_PIX_HIGH);
      NewPix[i].Blau = (byte)random(0, MAX_PIX_HIGH);
      NewPix[i].Status = 0;
    }
  }
}

int OldToNewPix(int i) {
  int RunLoop = 0;

  RunLoop++;

  //Rot
  if (NewPix[i].Rot == OldPix[i].Rot) {
    OldPix[i].Status |= 0b00000001;
  }
  else if (OldPix[i].Rot < NewPix[i].Rot) {
    OldPix[i].Rot++;
    OldPix[i].Status &= 0b11111110;
  }
  else if (OldPix[i].Rot > NewPix[i].Rot) {
    OldPix[i].Rot--;
    OldPix[i].Status &= 0b11111110;
  }
  //Gruen
  if (NewPix[i].Gruen == OldPix[i].Gruen) {
    OldPix[i].Status |= 0b00000010;
  }
  else if (OldPix[i].Gruen < NewPix[i].Gruen) {
    OldPix[i].Gruen++;
    OldPix[i].Status &= 0b11111101;
  }
  else if (OldPix[i].Gruen > NewPix[i].Gruen) {
    OldPix[i].Gruen--;
    OldPix[i].Status &= 0b11111101;
  }
  //Blau
  if (NewPix[i].Blau == OldPix[i].Blau) {
    OldPix[i].Status |= 0b00000100;
  }
  else if (OldPix[i].Blau < NewPix[i].Blau) {
    OldPix[i].Blau++;
    OldPix[i].Status &= 0b11111011;
  }
  else if (OldPix[i].Blau > NewPix[i].Blau) {
    OldPix[i].Blau--;
    OldPix[i].Status &= 0b11111011;
  }

  pix.setPixelColor(i, pix.Color(OldPix[i].Rot, OldPix[i].Gruen, OldPix[i].Blau));
  pix.show();

  if (OldPix[i].Status == 7) {  //alle Farben sind neu
    OldPix[i].Status = 0;
    return (1); //fertig
  }
  else
    return (0);
}

void PixelOff(void) {
  for (int i = 0; i < NUMPIXELS; i++) {
    OldPix[i].Rot = OldPix[i].Gruen = OldPix[i].Blau = OldPix[i].Status = 0;
    pix.setPixelColor(i, pix.Color(0, 0, 0));
    GetRandomPixel();
  }
  pix.show();
}

void FlashPix (int Led) {
  pix.setPixelColor(Led, pix.Color(255, 255, 255));
  pix.show();
  delay(50);
  pix.setPixelColor(Led, pix.Color(OldPix[Led].Rot, OldPix[Led].Gruen, OldPix[Led].Blau));
  pix.show();
}

void FlashFirework (void) {
  int Index = 0;
  static int NoFirework = 0;
  Index = (int)random(0, NUMPIXELS + 5);
  if ((Index < NUMPIXELS) || NoFirework) {
    Index = (int)random(0, NUMPIXELS);
    FlashPix(Index);
    if (NoFirework)
      NoFirework--;
  }
  else {
    for (int i; i < (random(NUMPIXELS, NUMPIXELS * 4)); i++) {
      Index = (int)random(0, NUMPIXELS);
      FlashPix(Index);
      delay(10);
    }
    NoFirework = random(NUMPIXELS / 2, NUMPIXELS * 5);
  }
}

void Boom (void) {
  for (int i = 0; i < NUMPIXELS; i++)
    pix.setPixelColor(i, pix.Color(255, 255, 255));
  for (int i = 0; i < STRING_LEN; i++)
    strip.setPixelColor(i, 255, 255, 255);
  pix.show();
  strip.show();
  delay(75);
  for (int i = 0; i < NUMPIXELS; i++)
    pix.setPixelColor(i, pix.Color(OldPix[i].Rot, OldPix[i].Gruen, OldPix[i].Blau));
  for (int i = 0; i < STRING_LEN; i++)
    strip.setPixelColor(i, OldLed[i].Rot, OldLed[i].Gruen, OldLed[i].Blau);
  pix.show();
  strip.show();
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

