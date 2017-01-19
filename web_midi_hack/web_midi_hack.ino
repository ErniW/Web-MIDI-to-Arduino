#include "MIDIUSB.h"

void setup() {
  
  Serial.begin(115200);
  
}

void loop() {

  midiEventPacket_t rx;

  do {
    rx = MidiUSB.read();
    
    if (rx.header != 0) {

      int pin = int(rx.byte2);
      int value = int(rx.byte3);

      if(rx.byte1 == 0x82){
        value = value + 128;
      }

      analogWrite(pin, value);
      
    }
  } while (rx.header != 0);

  int pot = analogRead(A0);
  pot = map(pot,0,1024,0,127);
  noteOn(1,0,pot);
  MidiUSB.flush();
  delay(1);
  
};


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
