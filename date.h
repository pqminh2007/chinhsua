#pragma once

class Date {
public:
    int day, month, year;

    Date();
    Date(int d, int m, int y);

    void input();
    void print() const;
};