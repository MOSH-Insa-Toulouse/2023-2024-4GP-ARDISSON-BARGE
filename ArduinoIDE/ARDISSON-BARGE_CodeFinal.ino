#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <SPI.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

//partie pour le digitalpot
// Define the MCP41100 OP command bits (only one POT)
// Note: command byte format xxCCxxPP, CC command, PP pot number (01 if selected) 
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
const int ssMCPin = 10; // Define the slave select for the digital pot
#define WAIT_DELAY 5000


//partie pour le module BT
#define rxPin 8 //Broche 8 en tant que RX, � raccorder sur TX du HC-05
#define txPin 7 //Broche 7 en tant que RX, � raccorder sur RX du HC-05
SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial

//partie pour l'encodeurrot
#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available
const unsigned long limite = 50 ;
volatile unsigned int encoder0Pos = 34;
volatile unsigned int choixmenu = 0;

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


const int flexPin = A1;      // Pin connected to voltage divider output
// Change these constants according to your project's design
// const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 38000.0;  // resistor used to create a voltage divider
const float flatResistance = 31000.0; // resistance when flat
const float bendResistance = 100000.0;  // resistance at 90 deg

// Résistances pour calcul de la résistance du capteur
float R1 = 100000.0;
float R2 = 1000.0;
float R3 = 100000.0;
float R5 = 10000.0;
float R6 = 100000.0;
float Vcc = 5.0;
float Vs = 0.0;
float calibre = 0.000001; //calibre en MOhm

int Encodeur ; 
int temps = 0 ;

void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}

void setup() {

  // pour le module BT dans le setup
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);

  //partie pour le digitalpot dans le setup
  pinMode (ssMCPin, OUTPUT); //select pin output
  digitalWrite(ssMCPin, HIGH); //SPI chip disabled
  SPI.begin(); 

  // initialize serial communication at 9600 bits per second:
  mySerial.begin(9600) ;
  Serial.begin(9600) ;

  //pour l'encodeurrot
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2
 
  // Initialisation de l'écran OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    while(1);                               // Arrêt du programme (boucle infinie) si échec d'initialisation

  }

    pinMode(flexPin, INPUT);
}

void loop() {


  Vs = analogRead(A0)*5.0/1024.0 ;
  float ValResistance = ((R1*((R2+R3)/R2)*(Vcc/Vs))-R5-R1)*calibre ;
  mySerial.write(analogRead(A0)) ;
  Serial.println(analogRead(A0)) ;

  // Read the ADC, and calculate voltage and resistance from it
  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * Vcc / 1023.0;
  float Rflex = R_DIV * (Vcc / Vflex - 1.0);
  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);

  Encodeur = 3*encoder0Pos ;

if (Encodeur < 0) {
  encoder0Pos = 24 ;
}

else if (Encodeur > 250) {
  encoder0Pos = 67 ;
}

// Menu résistance capteur graphite
if (Encodeur <= 75) {
  ecranOLED.clearDisplay();
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.setTextSize(3);
  ecranOLED.setCursor(0, 0);

  ecranOLED.setTextSize(1);
  ecranOLED.println("val capteur graphite");
  ecranOLED.print(ValResistance);
  ecranOLED.println(" Ohm");
}

// Menu flex sensor
else if (Encodeur >= 75 && Encodeur <= 110) {
  ecranOLED.clearDisplay();
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.setTextSize(3);
  ecranOLED.setCursor(0, 0);

  ecranOLED.setTextSize(1);
  ecranOLED.println("valeur capteur flex");
  ecranOLED.println("Res_flex:" + String(Rflex) + " MOhm");
  ecranOLED.println("Bend_flex: " + String(angle) + " deg");
}

}

ecranOLED.display(); // Transfert le buffer à l'écran

delay(100);  // delay in between reads for stability

}

// Pour améliorer la fiabilité de l'encodeur rotatoire
void doEncoder() {
  if ( (millis() - temps) > limite) {

    if (digitalRead(encoder0PinB)==HIGH) {
      encoder0Pos++;
    } 
    
    else {
      encoder0Pos--;
    }
    
    temps = millis();
  
  } 

  }