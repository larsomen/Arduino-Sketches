// Arduino Uno
// converts the position of a 10k lin(B) pot to 0-8 binary, and then displays the bits with 4 LEDs
// pot connected to A0, 5volt and ground
// dw 1K or 10K pot, both work equally well, 4 LED's
// pin 4 tone output to speaker
// dw modified code originally written by Wawa in post #7:
// https://forum.arduino.cc/index.php?topic=563631.msg3844251#msg3844251

int rawValue; // raw reading
int oldValue; // for deadband
byte Byte; // final byte
byte oldByte; // for printing
unsigned int freq; // tone
unsigned long duration = 3000; // tone duration in milliseconds

void setup() {
  Serial.begin(9600);
  for (int i = 4; i < 9; i++) pinMode(i, OUTPUT); // make pin 4-8 output 
}

void loop() {
  
  rawValue = analogRead(A0) + 10; // read pot  dw: added "+ 10" to get binary 8 LED to light up at end of pot rotation
  if (rawValue < (oldValue - 2) || rawValue > (oldValue + 2)) { // add some deadband
    oldValue = rawValue; // update value
    Byte = oldValue >> 7; // convert 10-bit to 4-bit
    if (oldByte != Byte) { // only print if value changes
      Serial.print("Byte value: ");
      Serial.print(Byte);
      Serial.print("  ");
      Serial.print("BIN: ");
      Serial.println(Byte, BIN);
      digitalWrite(5, (Byte & 1));
      digitalWrite(6, (Byte & 2));
      digitalWrite(7, (Byte & 4));
      digitalWrite(8, (Byte & 8));
     
      freq = map(Byte, 0, 8, 0, 2000);  
      Serial.print("Tone frequency: ");
      Serial.print(freq);
      Serial.println(" Herz\n");
      tone(4, freq, duration); // tone (pin, frequency, duration)
      oldByte = Byte; // update value
    }
  }
}
