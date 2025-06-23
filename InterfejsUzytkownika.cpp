#include "InterfejsUzytkownika.h"
#include <limits>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "KonkretnyKomponent.h"

InterfejsUzytkownika::InterfejsUzytkownika() : m_generator(nullptr), m_petla(nullptr) {}

InterfejsUzytkownika::~InterfejsUzytkownika() {}

void InterfejsUzytkownika::uruchom()
{
    std::cout << "=== GENERATOR SYGNALOW - INTERFEJS UZYTKOWNIKA ===" << std::endl;
    std::cout << "Witaj w interaktywnym generatorze sygnalow!" << std::endl << std::endl;
    
    bool kontynuuj = true;
    while (kontynuuj)
    {
        wyswietlMenu();
        int wybor = pobierzWybor(1, 7);
        
        switch (wybor)
        {
            case 1:
                wyswietlMenuSygnalow();
                break;
            case 2:
                if (m_generator)
                    dodajOgranicznikAmplitudy();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 3:
                konfigurujPetle();
                break;
            case 4:
                if (m_generator)
                    generujProbki();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 5:
                if (m_generator)
                    zapiszDoPliku();
                else
                    std::cout << "Najpierw wybierz sygnal!" << std::endl;
                break;
            case 6:
                if (m_generator)
                    wyswietlParametry();
                else
                    std::cout << "Brak aktywnego sygnalu." << std::endl;
                break;
            case 7:
                kontynuuj = false;
                std::cout << "Dziekuje za korzystanie z programu!" << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}

void InterfejsUzytkownika::wyswietlMenu()
{
    std::cout << "=== MENU GLOWNE ===" << std::endl;
    std::cout << "1. Wybierz typ sygnalu" << std::endl;
    std::cout << "2. Dodaj ogranicznik amplitudy" << std::endl;
    std::cout << "3. Konfiguruj petle symulacji" << std::endl;
    std::cout << "4. Generuj probki sygnalu" << std::endl;
    std::cout << "5. Zapisz sygnal do pliku" << std::endl;
    std::cout << "6. Wyswietl parametry aktualnego sygnalu" << std::endl;
    std::cout << "7. Wyjscie" << std::endl;
    std::cout << "Wybierz opcje (1-7): ";
}

void InterfejsUzytkownika::wyswietlMenuSygnalow()
{
    std::cout << "\n=== WYBOR TYPU SYGNALU ===" << std::endl;
    std::cout << "1. Wartosc stala" << std::endl;
    std::cout << "2. Sygnal sinusoidalny" << std::endl;
    std::cout << "3. Sygnal prostokatny" << std::endl;
    std::cout << "4. Sygnal trojkatny" << std::endl;
    std::cout << "5. Szum bialy" << std::endl;
    std::cout << "Wybierz typ sygnalu (1-5): ";
    
    int wybor = pobierzWybor(1, 5);
    
    switch (wybor)
    {
        case 1:
            m_generator.reset(stworzWartoscStala());
            break;
        case 2:
            m_generator.reset(stworzSinus());
            break;
        case 3:
            m_generator.reset(stworzProstokat());
            break;
        case 4:
            m_generator.reset(stworzTrojkat());
            break;
        case 5:
            m_generator.reset(stworzSzumBialy());
            break;
    }
    
    if (m_generator)
    {
        std::cout << "Sygnal zostal utworzony pomyslnie!" << std::endl;
    }
}

int InterfejsUzytkownika::pobierzWybor(int min, int max)
{
    int wybor;
    while (true)
    {
        std::cin >> wybor;
        
        if (std::cin.fail() || wybor < min || wybor > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowy wybor. Podaj liczbe z zakresu " << min << "-" << max << ": ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return wybor;
        }
    }
}

double InterfejsUzytkownika::pobierzLiczbe(const std::string& prompt)
{
    double liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

int InterfejsUzytkownika::pobierzLiczbeCalkowita(const std::string& prompt)
{
    int liczba;
    while (true)
    {
        std::cout << prompt;
        std::cin >> liczba;
        
        if (std::cin.fail() || liczba < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidlowa wartosc. Podaj liczbe calkowita wieksza od 0: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return liczba;
        }
    }
}

SygnalGenerator* InterfejsUzytkownika::stworzWartoscStala()
{
    std::cout << "\n=== KONFIGURACJA WARTOSCI STALEJ ===" << std::endl;
    double wartosc = pobierzLiczbe("Podaj wartosc stala: ");
    
    return new WartoscStalaGenerator(wartosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzSinus()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU SINUSOIDALNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double czestotliwosc = pobierzLiczbe("Podaj czestotliwosc [Hz]: ");
    
    // Sinus jest dekoratorem, więc potrzebuje sygnału bazowego (wartość stała = 0)
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SinusGenerator(bazowy, amplituda, czestotliwosc);
}

SygnalGenerator* InterfejsUzytkownika::stworzProstokat()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU PROSTOKATNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypełnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypelnienie musi byc w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new ProstokatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzTrojkat()
{
    std::cout << "\n=== KONFIGURACJA SYGNALU TROJKATNEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude: ");
    double okres = pobierzLiczbe("Podaj okres [s]: ");
    double wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    
    // Sprawdzenie zakresu wypełnienia
    while (wypelnienie < 0.0 || wypelnienie > 1.0)
    {
        std::cout << "Wypelnienie musi byc w zakresie 0.0-1.0!" << std::endl;
        wypelnienie = pobierzLiczbe("Podaj wypelnienie (0.0-1.0): ");
    }
    
    // Konwersja okresu na częstotliwość
    double czestotliwosc = (okres > 0.0) ? (1.0 / okres) : 0.0;
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new TrojkatGenerator(bazowy, amplituda, czestotliwosc, wypelnienie);
}

SygnalGenerator* InterfejsUzytkownika::stworzSzumBialy()
{
    std::cout << "\n=== KONFIGURACJA SZUMU BIALEGO ===" << std::endl;
    double amplituda = pobierzLiczbe("Podaj amplitude szumu: ");
    
    SygnalGenerator* bazowy = new WartoscStalaGenerator(0.0);
    return new SzumBialyGenerator(bazowy, amplituda);
}

void InterfejsUzytkownika::dodajOgranicznikAmplitudy()
{
    std::cout << "\n=== DODAWANIE OGRANICZNIKA AMPLITUDY ===" << std::endl;
    double minAmplituda = pobierzLiczbe("Podaj minimalna amplitude: ");
    double maxAmplituda = pobierzLiczbe("Podaj maksymalna amplitude: ");
      if (minAmplituda > maxAmplituda)
    {
        std::swap(minAmplituda, maxAmplituda);
        std::cout << "Zamieniono wartosci - min: " << minAmplituda << ", max: " << maxAmplituda << std::endl;
    }
    
    // OgranicznikAmplitudy używa symetrycznego ograniczenia względem zera
    // Obliczamy limit jako maksymalną wartość bezwzględną
    double limit = std::max(std::abs(minAmplituda), std::abs(maxAmplituda));
    
    // Tworzenie nowego ogranicznika jako dekoratora
    SygnalGenerator* ograniczony = new OgranicznikAmplitudy(m_generator.release(), limit);
    m_generator.reset(ograniczony);
    
    std::cout << "Ogranicznik amplitudy zostal dodany!" << std::endl;
}

void InterfejsUzytkownika::konfigurujPetle()
{
    std::cout << "--- Konfiguracja petli symulacji ---" << std::endl;
    std::cout << "1. Petla szeregowa" << std::endl;
    std::cout << "2. Petla rownolegla" << std::endl;
    int wybor = pobierzWybor(1, 2);

    if (wybor == 1)
    {
        m_petla = std::unique_ptr<Komponent>(new KompozytSzeregowy());
    }
    else
    {
        m_petla = std::unique_ptr<Komponent>(new KompozytRownolegl());
    }

    char dodac_wiecej;
    do
    {
        std::cout << "--- Dodaj obiekt do petli ---" << std::endl;
        std::cout << "1. Model ARX" << std::endl;
        std::cout << "2. Regulator PID" << std::endl;
        int typ_obiektu = pobierzWybor(1, 2);

        ObiektSISO* obiekt_siso = stworzObiektSISO(typ_obiektu);
        if (obiekt_siso)
        {
            std::shared_ptr<ObiektSISO> obiekt_ptr(obiekt_siso);
            m_petla->dodaj(std::make_shared<KonkretnyKomponent>(1.0, obiekt_ptr));
        }

        std::cout << "Dodac kolejny obiekt? (t/n): ";
        std::cin >> dodac_wiecej;
    } while (dodac_wiecej == 't' || dodac_wiecej == 'T');
}

ObiektSISO* InterfejsUzytkownika::stworzObiektSISO(int typ)
{
    if (typ == 1) {
        std::cout << "\n--- Konfiguracja Modelu ARX ---" << std::endl;
        std::vector<double> a, b;
        int stopienA = pobierzLiczbeCalkowita("Podaj stopien A (liczba wspolczynnikow): ");
        for (int i = 0; i < stopienA; ++i) {
            a.push_back(pobierzLiczbe("Podaj a[" + std::to_string(i) + "]: "));
        }
        int stopienB = pobierzLiczbeCalkowita("Podaj stopien B (liczba wspolczynnikow): ");
        for (int i = 0; i < stopienB; ++i) {
            b.push_back(pobierzLiczbe("Podaj b[" + std::to_string(i) + "]: "));
        }
        int opoznienie = pobierzLiczbeCalkowita("Podaj opoznienie: ");
        double sigma = pobierzLiczbe("Podaj odchylenie standardowe szumu: ");
        return new ModelARX(a, b, opoznienie, sigma);
    } else if (typ == 2) {
        std::cout << "\n--- Konfiguracja Regulatora PID ---" << std::endl;
        double k = pobierzLiczbe("Podaj wzmocnienie (k): ");
        double ti = pobierzLiczbe("Podaj czas calkowania (Ti): ");
        double td = pobierzLiczbe("Podaj czas rozniczkowania (Td): ");
        return new RegulatorPID(k, ti, td);
    }
    return nullptr;
}


void InterfejsUzytkownika::generujProbki()
{
    std::cout << "\n=== GENEROWANIE PROBEK SYGNALU ===" << std::endl;
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbe probek do wygenerowania: ");
    double krokCzasowy = pobierzLiczbe("Podaj krok czasowy [s] (wplywa na generatory zalezne od czasu): ");

    std::cout << "\nWygenerowane probki:" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wejscie = m_generator->generuj(i * krokCzasowy);
        double wartosc = wejscie;
        if (m_petla) {
            wartosc = m_petla->symuluj(wejscie);
        }
        
        std::cout << "Probka " << std::setw(4) << (i + 1) << ": Wejscie: " << std::setw(12) << wejscie << " | Wyjscie: " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij po 20 próbkach i zapytaj czy kontynuować
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyswietlono " << (i + 1) << " probek. Czy kontynuowac? (t/n): ";
            char odpowiedz;
            std::cin >> odpowiedz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (odpowiedz != 't' && odpowiedz != 'T')
            {
                break;
            }
            std::cout << std::endl;
        }
    }
}

void InterfejsUzytkownika::wyswietlParametry()
{
    std::cout << "Parametry nie sa zaimplementowane." << std::endl;
}

void InterfejsUzytkownika::zapiszDoPliku()
{
    std::cout << "\n=== ZAPIS SYGNALU DO PLIKU ===" << std::endl;
    std::cout << "Podaj nazwe pliku (bez rozszerzenia): ";
    std::string nazwaPliku;
    std::getline(std::cin, nazwaPliku);
    nazwaPliku += ".txt";
    
    int liczbaProbek = pobierzLiczbeCalkowita("Podaj liczbe probek do zapisania: ");
    double krokCzasowy = pobierzLiczbe("Podaj krok czasowy [s] (wplywa na generatory zalezne od czasu): ");
    
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open())
    {
        std::cout << "Blad: Nie mozna utworzyc pliku " << nazwaPliku << std::endl;
        return;
    }
    
    plik << "# Wygenerowany sygnal - " << m_generator->getType() << std::endl;
    plik << "# Liczba probek: " << liczbaProbek << std::endl;
    plik << "# Format: czas[s] wejscie wyjscie" << std::endl;
    plik << std::fixed << std::setprecision(6);
    
    std::cout << "\nWygenerowane probki (zapisywane do pliku):" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    for (int i = 0; i < liczbaProbek; ++i)
    {
        double wejscie = m_generator->generuj(i * krokCzasowy);
        double wartosc = wejscie;
        if (m_petla) {
            wartosc = m_petla->symuluj(wejscie);
        }
        plik << (i * krokCzasowy) << "\t" << wejscie << "\t" << wartosc << std::endl;
        std::cout << "Probka " << std::setw(4) << (i + 1) << ": Wejscie: " << std::setw(12) << wejscie << " | Wyjscie: " << std::setw(12) << wartosc << std::endl;
        
        // Przerwij wyświetlanie po 20 próbkach i zapytaj czy kontynuować
        if ((i + 1) % 20 == 0 && (i + 1) < liczbaProbek)
        {
            std::cout << "\nWyswietlono " << (i + 1) << " probek. Czy kontynuowac wyswietlanie? (t/n): ";
            char odpowiedz;
            std::cin >> odpowiedz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (odpowiedz != 't' && odpowiedz != 'T')
            {
                std::cout << "Kontynuuje zapis do pliku bez wyswietlania..." << std::endl;
                // Kontynuuj zapisywanie do pliku bez wyświetlania
                for (int j = i + 1; j < liczbaProbek; ++j)
                {
                    double wejscieBezWyswietlania = m_generator->generuj(j * krokCzasowy);
                    double wartoscBezWyswietlania = wejscieBezWyswietlania;
                    if (m_petla) {
                        wartoscBezWyswietlania = m_petla->symuluj(wejscieBezWyswietlania);
                    }
                    plik << (j * krokCzasowy) << "\t" << wejscieBezWyswietlania << "\t" << wartoscBezWyswietlania << std::endl;
                }
                break;
            }
            std::cout << std::endl;
        }
    }
    
    plik.close();
    std::cout << "\nSygnal zostal zapisany do pliku: " << nazwaPliku << std::endl;
}
