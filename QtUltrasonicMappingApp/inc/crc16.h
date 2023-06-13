#ifndef CRC16_H
#define CRC16_H

#include <cstdint>
#include <iostream>
#include <cstddef>

//!  Klasa obliczająca sume kontrolną
/*!
  Klasa ta służy do wyznaczania sumy kontrolnej na podstawie przesyłanych i otrzymywanych danych
  Jeśli suma kontrolna obliczona na podstawie otrzymanego pakietu danych jest taka sama jak otrzymana
  razem z danymi, to można stwierdzić, że otrzymano wszystkie dane i nic nie zostało utracone podczas
  transmisji
*/
class CRC16 {
public:
    //! Konstruktor klasy
    CRC16();

    //! Publiczna metoda
    /*!
     Metoda wyznaczająca wartość sumy kontrolnej na podstawie otrzymanych danych
     \param data Dane wejściowe na podstawie których wyznaczyć sumę kontrolną
     \param length Długość danych wejściowych
    */
    uint16_t calculateCRC16(const uint8_t* data, size_t length);

private:
    //! Prywatna tabela
    /*!
      Tabela poszukiwań jest używana w implementacji CRC16 w celu przyspieszenia obliczeń.
      Składa się z wcześniej obliczonych wartości CRC dla wszystkich możliwych 8-bitowych
      kombinacji danych wejściowych.
    */
    static const uint16_t crc16Table[];
};

#endif // CRC16_H
