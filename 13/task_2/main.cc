#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    constexpr int Rows = 10;
    std::vector<std::vector<int>> PascalTriangle (Rows);

    for (int Row = 0; Row < Rows; ++Row) {
        PascalTriangle [Row].resize(Row + 1);
        PascalTriangle [Row][0] = PascalTriangle[Row][Row] = 1;

        for (int Col = 1; Col < Row; ++Col)
            PascalTriangle [Row][Col] = 
                PascalTriangle[Row - 1][Col - 1] + PascalTriangle[Row - 1][Col];
    }

    constexpr int SpaceWidth = 6;
    for (int Row = 0; Row < Rows; ++Row) {
        std::cout << std::string(SpaceWidth * (Rows - Row - 1) / 2, ' ');
        for (int Col = 0; Col <= Row; ++Col)
            std::cout << std::setw(SpaceWidth) << PascalTriangle[Row][Col] << " ";
        std::cout << std::endl;
    }
}

