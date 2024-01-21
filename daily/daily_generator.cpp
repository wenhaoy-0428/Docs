#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>

std::string genFileName() {
    const std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
    const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    std::stringstream ss;
    ss << static_cast<int>(ymd.year()) << "_" << static_cast<unsigned>(ymd.month()) << "_" << static_cast<unsigned>(ymd.day());
    std::string fileName;
    ss >> fileName;
    return fileName;
}

int mkDailyFile() {



}



int main() {




}
