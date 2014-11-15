

volatile uint8_t _buttonpress = false;
uint8_t prg_counter;

#define B0 0
#define B1 1
#define B3 3


void isr() {
  
  _buttonpress = true;
}

void setup() {                
  
  pinMode(2, INPUT); // int0
  pinMode(B0, OUTPUT); // PB0
  pinMode(B1, OUTPUT); // PB1
  pinMode(B3, OUTPUT); // PB3
  
  digitalWrite(B0, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B3, LOW);
  
  attachInterrupt(0, isr, RISING);  // interupt on int0 (2)
 }


void loop() {
  
  if (_buttonpress) { 
        
        _buttonpress = false; 
        next();
  }
}  


/*  -------------------------------------------   */

void next() {
  
  byte tmp;
  prg_counter++; 
  if (prg_counter > 7) { // reset counter 
            prg_counter = 0; 
            PORTB &= B11110100;
      } 
  if (prg_counter < 4) tmp += prg_counter; 
  else tmp = (0x8 + (prg_counter-4));
    
  PORTB |= tmp;         // write
}


