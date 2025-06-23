#include "RegulatorPID.h"
#include <stdexcept>

RegulatorPID::RegulatorPID(double k)
    : k(k), Ti(0), Td(0), sumaUchybow(0), poprzedniUchyb(0), czyPI(false), czyPID(false)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
}

RegulatorPID::RegulatorPID(double k, double Ti)
    : k(k), Ti(Ti), Td(0), sumaUchybow(0), poprzedniUchyb(0), czyPI(true), czyPID(false)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
}

RegulatorPID::RegulatorPID(double k, double Ti, double Td)
    : k(k), Ti(Ti), Td(Td), sumaUchybow(0), poprzedniUchyb(0), czyPI(true), czyPID(true)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
    sprawdzDodatnie(Td, "Czas różniczkowania Td");
}

void RegulatorPID::sprawdzDodatnie(double wartosc, const std::string &nazwa)
{
    if (wartosc <= 0.0)
    {
        throw std::invalid_argument(nazwa + " musi być większe od zera.");
    }
}

void RegulatorPID::setK(double k)
{
    sprawdzDodatnie(k, "Wzmocnienie k");
    this->k = k;
}

void RegulatorPID::setTi(double Ti)
{
    sprawdzDodatnie(Ti, "Czas całkowania Ti");
    this->Ti = Ti;
    czyPI = true;
}

void RegulatorPID::setTd(double Td)
{
    sprawdzDodatnie(Td, "Czas różniczkowania Td");
    this->Td = Td;
    czyPID = true;
}

double RegulatorPID::symuluj(double uchyb)
{
    // Krok czasowy - kluczowy dla poprawności regulatora PID.
    // W tej implementacji zakładamy stały krok czasowy równy 1.0,
    // co może nie być poprawne dla wszystkich symulacji.
    // Dla precyzyjnego działania, krok czasowy powinien być przekazywany
    // do tej metody lub ustawiany jako parametr regulatora.
    double krokCzasowy = 1.0;

    // Obliczenie części całkującej
    double czescCalkujaca = 0.0;
    if (czyPI && Ti > 0.0)
    {
        sumaUchybow += uchyb * krokCzasowy;
        czescCalkujaca = (k / Ti) * sumaUchybow;
    }

    // Obliczenie części różniczkującej
    double czescRozniczkujaca = 0.0;
    if (czyPID && Td > 0.0 && krokCzasowy > 0.0)
    {
        double rozniczka = (uchyb - poprzedniUchyb) / krokCzasowy;
        czescRozniczkujaca = k * Td * rozniczka;
    }

    // Zaktualizowanie poprzedniego uchybu
    poprzedniUchyb = uchyb;

    // Obliczenie całkowitego sygnału sterującego
    double sygnalSterujacy = k * uchyb + czescCalkujaca + czescRozniczkujaca;

    return sygnalSterujacy;
}
