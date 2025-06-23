#ifndef KONKRETNY_KOMPONENT_H
#define KONKRETNY_KOMPONENT_H

#include "Komponent.h"
#include <memory>

/**
 * @author Jessica Adamczyk
 * @class KonkretnyKomponent
 * @brief Przykładowa implementacja konkretnego komponentu (liść w drzewie kompozytu)
 */
class KonkretnyKomponent : public Komponent
{
private:
    double wspolczynnik;
    std::shared_ptr<ObiektSISO> m_obiekt;

public:
    KonkretnyKomponent(double wsp = 1.0, std::shared_ptr<ObiektSISO> obiekt = nullptr)
        : wspolczynnik(wsp), m_obiekt(obiekt) {}

    double symuluj(double u) override
    {
        if (m_obiekt)
        {
            return m_obiekt->symuluj(u);
        }
        return u * wspolczynnik;
    }

    void ustawWspolczynnik(double wsp) { wspolczynnik = wsp; }

    double pobierzWspolczynnik() const { return wspolczynnik; }
};

#endif // KONKRETNY_KOMPONENT_H
