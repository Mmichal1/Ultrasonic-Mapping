/**@file Mapowanie.ino */

#include "CRC16.h"
#include "CRC.h"

/*!
    Klasa czujnik posiada pola przechowujące informacje o ID czujnika
    oraz pinów mikrokontrolera używanych przez czujnika
 */
class Sensor {
   public:
    uint8_t SENSOR_ID;  /*!< ID czujnika*/
    uint8_t TRIG_PIN;   /*!< Trigger PIN*/
    uint8_t ECHO_PIN;   /*!< Echo PIN*/
    //! Konstruktor.
    /*!
        Konstruktor tworzący instancję czujnika
        \param[in] ID czujnika
        \param[in] Trigger PIN
        \param[in] Echo PIN
    */
    Sensor(uint8_t SENSOR_ID, uint8_t TRIG_PIN, uint8_t ECHO_PIN);
};

Sensor::Sensor(uint8_t SENSOR_ID, uint8_t TRIG_PIN, uint8_t ECHO_PIN) {
    Sensor::SENSOR_ID = SENSOR_ID;
    Sensor::TRIG_PIN = TRIG_PIN;
    Sensor::ECHO_PIN = ECHO_PIN;
}

Sensor list[] = {Sensor(0, 4, 5), Sensor(1, 8, 9),
                 Sensor(2, 12, 13)};  //!< Lista przechowująca instancje czujników
CRC16 crc;                            //!< Inicjalizacja instancji obiektu, dzięki któremu obliczana będzie suma kontrolna

/*!
    Funkcja zwracająca długość pulsu z danego czujnika
    \param[in] Trigger PIN
    \param[in] Echo PIN
    \param[out] Długość pulsu
*/
long readFromSensor(int TRIG_PIN, int ECHO_PIN) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH);
}

/*!
    Główna funkcja ustawiająca wartości potrzebne do poprawnego działania
    programu. Tryb działania PINów Trigger każdego z czujników jest ustawiany
    jako wyjście a PINów Echo jako wejście.
    Inicjalizacja portu seryjnego z zadaną szybkością transmisji.
    Ustawienie wielomianu CRC.
*/
void setup() {
    for (Sensor sensor : list) {
        pinMode(sensor.TRIG_PIN, OUTPUT);
        pinMode(sensor.ECHO_PIN, INPUT);
    }
    Serial.begin(9600);      
    crc.setPolynome(0x1021); 
}

/*!
    Główna pętla programu.
*/
void loop() {
    long duration, distanceCm;  
    char numstr[21];  
    String data = "";  

    for (Sensor sensor : list) {
        duration = readFromSensor(sensor.TRIG_PIN, sensor.ECHO_PIN);
        distanceCm = duration / 29.1 / 2;
        if (distanceCm <= 0) {
            Serial.println("Out of range");
        } else {
            sprintf(numstr, "%d %lu ", sensor.SENSOR_ID, distanceCm);
            data = data + numstr;
        }
        delay(100);
    }
    for (char i: data) {
        crc.add(i);
    }
    Serial.print(data);
    Serial.print("\t");
    Serial.println(crc.getCRC(), HEX);
    delay(1000);
    crc.reset();    
} 