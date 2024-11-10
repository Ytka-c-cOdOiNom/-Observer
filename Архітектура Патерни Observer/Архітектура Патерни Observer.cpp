#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

// Абстракція для спостерігача
class Observer {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

// Абстракція для суб'єкта
class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

// Конкретний суб'єкт
class WeatherData : public Subject {
private:
    vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherData() : temperature(0), humidity(0), pressure(0) {}

    void setWeatherData(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }

    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (auto* observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }
};

// Конкретний спостерігач
class CurrentConditionsDisplay : public Observer {
private:
    float temperature;
    float humidity;

public:
    void update(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "Поточні умови: Температура = " << temperature << "C, Вологість = " << humidity << "%" << endl;
    }
};


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення суб'єкта (погода)
    WeatherData* weatherData = new WeatherData();

    // Створення спостерігачів
    CurrentConditionsDisplay* currentConditions = new CurrentConditionsDisplay();

    // Реєстрація спостерігача
    weatherData->registerObserver(currentConditions);

    // Оновлення даних
    weatherData->setWeatherData(30.5, 65.0, 1013.0);
    weatherData->setWeatherData(28.0, 70.0, 1012.0);

    // Видалення спостерігача
    weatherData->removeObserver(currentConditions);

    // Оновлення даних після видалення спостерігача
    weatherData->setWeatherData(25.0, 80.0, 1011.0);


    delete currentConditions;
    delete weatherData;


}

