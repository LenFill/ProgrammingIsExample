// Лабораторная работа 7
// Наследование, виртуальные функции и абстрактные классы.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Point {
protected:
    int x;
    int y;
    string color;

public:
    Point(int xValue, int yValue, const string& colorValue)
        : x(xValue), y(yValue), color(colorValue)
    {
    }

    virtual ~Point() = default;

    virtual void show() const = 0;

    virtual void hide() const
    {
        cout << "Фигура скрыта в точке (" << x << ", " << y << ")" << endl;
    }

    virtual void locate(int& xValue, int& yValue) const
    {
        xValue = x;
        yValue = y;
    }

    virtual void fly(int step)
    {
        hide();
        x += rand() % (step * 2 + 1) - step;
        y += rand() % (step * 2 + 1) - step;
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        show();
    }

    virtual void resize(int delta) = 0;

    void changeColor(const string& newColor)
    {
        color = newColor;
    }
};

class Krug : public Point {
protected:
    int radius;

public:
    Krug(int xValue, int yValue, int radiusValue, const string& colorValue)
        : Point(xValue, yValue, colorValue), radius(radiusValue)
    {
    }

    void show() const override
    {
        cout << "Круг: центр=(" << x << ", " << y << "), радиус=" << radius
             << ", цвет=" << color << endl;
    }

    void resize(int delta) override
    {
        radius += delta;
        if (radius < 1) radius = 1;
    }
};

class Ring : public Krug {
private:
    int width;
    int sectorStart;
    int sectorEnd;

public:
    Ring(int xValue, int yValue, int radiusValue, const string& colorValue, int widthValue)
        : Krug(xValue, yValue, radiusValue, colorValue),
          width(widthValue),
          sectorStart(0),
          sectorEnd(320)
    {
    }

    void show() const override
    {
        cout << "Кольцо: центр=(" << x << ", " << y << "), радиус=" << radius
             << ", ширина=" << width << ", сектор=" << sectorStart << ".." << sectorEnd
             << ", цвет=" << color << endl;
    }

    void resize(int delta) override
    {
        Krug::resize(delta);
        width += delta / 2;
        if (width < 1) width = 1;
        if (width >= radius) width = radius - 1;
        if (width < 1) width = 1;
    }

    void changeSector(int start, int end)
    {
        sectorStart = start;
        sectorEnd = end;
    }
};

int main()
{
    system("chcp 1251>nul");
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 7 ===" << endl;

    vector<unique_ptr<Point>> figures;
    figures.push_back(make_unique<Krug>(150, 40, 50, "красный"));
    figures.push_back(make_unique<Ring>(450, 80, 90, "синий", 10));

    for (const auto& figure : figures) figure->show();

    cout << "\n--- Перемещение фигур ---" << endl;
    for (int i = 0; i < 3; ++i) {
        for (const auto& figure : figures) figure->fly(30);
    }

    cout << "\n--- Изменение размера и цвета ---" << endl;
    figures[0]->resize(15);
    figures[0]->changeColor("зеленый");
    figures[0]->show();

    Ring* ring = dynamic_cast<Ring*>(figures[1].get());
    if (ring != nullptr) {
        ring->resize(-12);
        ring->changeColor("желтый");
        ring->changeSector(45, 280);
        ring->show();
    }

    return 0;
}
