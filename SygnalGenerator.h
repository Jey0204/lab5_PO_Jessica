#ifndef SYGNALGENERATOR_H
#define SYGNALGENERATOR_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/**
 * @class SygnalGenerator
 * @brief Abstrakcyjna klasa bazowa reprezentująca interfejs dla wszystkich generatorów sygnału. Umożliwia generowanie i zapisywanie sygnałów.
 * @author Jessica Adamczyk
 */

class FabrykaSygnalu;

class SygnalGenerator
{
public:
    virtual ~SygnalGenerator() = default;
    virtual double generuj(double t) = 0;
    virtual std::string getType() const = 0;
};

#endif // SYGNALGENERATOR_H
