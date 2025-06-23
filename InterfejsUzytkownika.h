#ifndef INTERFEJSUZYTKOWNIKA_H
#define INTERFEJSUZYTKOWNIKA_H

#include "SygnalGenerator.h"
#include "WartoscStalaGenerator.h"
#include "SinusGenerator.h"
#include "ProstokatGenerator.h"
#include "TrojkatGenerator.h"
#include "SzumBialyGenerator.h"
#include "OgranicznikAmplitudy.h"
#include "SygnalDekorator.h"
#include "Komponent.h"
#include "KompozytSzeregowy.h"
#include "KompozytRownolegl.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>

/**
 * @class InterfejsUzytkownika
 * @brief Klasa odpowiedzialna za interakcję z użytkownikiem w terminalu
 * @author Assistant
 */
class InterfejsUzytkownika
{
private:
    std::unique_ptr<SygnalGenerator> m_generator;
    std::unique_ptr<Komponent> m_petla;
    
    void wyswietlMenu();
    void wyswietlMenuSygnalow();
    int pobierzWybor(int min, int max);
    double pobierzLiczbe(const std::string& prompt);
    int pobierzLiczbeCalkowita(const std::string& prompt);
    
    SygnalGenerator* stworzWartoscStala();
    SygnalGenerator* stworzSinus();
    SygnalGenerator* stworzProstokat();
    SygnalGenerator* stworzTrojkat();
    SygnalGenerator* stworzSzumBialy();
    
    void konfigurujPetle();
    ObiektSISO* stworzObiektSISO(int typ);

    void dodajOgranicznikAmplitudy();
    void generujProbki();
    void zapiszDoPliku();
    void wyswietlParametry();

public:
    InterfejsUzytkownika();
    ~InterfejsUzytkownika();
    
    void uruchom();
};

#endif // INTERFEJSUZYTKOWNIKA_H
