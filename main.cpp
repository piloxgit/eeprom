//
// Created by pilox on 18.4.17.
//

/*
 *
 *
 * EEPROM 24c01 128 bunek * 1B
*****************************************
 Zapojeni

EEPROM 24c01            Arduino NANO
1(GND)                  GND
2(GND)                  GND
3(GND)                  GND
4(GND)                  GND
5(SDA)                  A5
6(SCL)                  A4
7(GND)                  GND
8(5V)                   5V
******************************************
 */

#include <Arduino.h>
//Knihovna pro komunikaci I2C
#include <Wire.h>


//funkce zapisuje data do EEPROM
void zapis(int adresa, byte hodndota){

    //Navazani I2C komunikace s EEPROM na adrese 0x50
    //Nozicky 1, 2 a 3 musi byt na GND
        Wire.beginTransmission(0x50);
    //Zaslani adresy pametove bunky se kterou budu pracovat
        Wire.write(adresa);
    //Zapsani hodnoty do bunky s adresou, ktera byla zvolena v predeslem prikazu, POZOR: predchozi prikaz je stejny ale znamena neco jineho
        Wire.write(hodndota);
    //Konec I2C komunikace
        Wire.endTransmission();
    //Nutna prodleva pred dalsi I2C komunikaci a pred dalsim zapisem do EEPROM
        delay(10);

}

//funkce cte data z EEPROM a vypisuje na serial
void cteni(int adresa) {


    //Navazani I2C komunikace s EEPROM na adrese 0x50
    //Nozicky 1, 2 a 3 musi byt na GND
    Wire.beginTransmission(0x50);
    //Zaslani adresy pametove bunky se kterou budu pracovat
    Wire.write(adresa);
    //Konec I2C komunikace
    Wire.endTransmission();
    //Precteni jednoho bajtu z EEPROM s adresou 0x50 z pametove bunky, ktera byla zvolena o dva prikazy vys
    Wire.requestFrom(0x50,1);
    //Pokud I2C pripravena
    if (Wire.available()){

        Serial.print("EEPROM addresa: ");
        Serial.print(adresa);
        Serial.print("hodnota: ");
        //Precteni z EEPROM a vypis na Serial, parametry adressa pameti a adresa pametove bunky byly urceny vyse
        Serial.println(Wire.read());

    }
}

void setup()
{
    //Inicializace I2C komunikace
    Wire.begin();
    //Inicializace Seriove komunikace
    Serial.begin(9600);

    //Zapsani nahodnych cisel do EEPROM
    for (int i=0; i<128;i++){

       zapis(i,random(0, 200));
    }

    //Cteni z EEPROM
    for (int i=0; i<128;i++){

        cteni(i);
    }
}

void loop(){}
