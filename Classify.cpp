// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Classify.h"

RoomClassify::RoomClassify(): type(RoomType::STANDARD), status(RoomStatus::AVAILABLE), pricePerDay(0) {}
RoomClassify::RoomClassify(string number, RoomType t): roomNumber(number), type(t), status(RoomStatus::AVAILABLE){
    RoomPrice();
}

void RoomClassify::RoomPrice() {
    switch (type) {
    case RoomType::STANDARD:
        pricePerDay = 500000; break;
    case RoomType::DELUXE:
        pricePerDay = 800000; break;
    case RoomType::SUITE:
        pricePerDay = 1500000; break;
    }
}