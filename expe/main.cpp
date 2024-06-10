#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm> // Include this header for std::max_element


// Function to print a single line of the hexagon
void printHexagonLine(int leadingSpaces, const std::vector<std::string> &row) {
    std::cout << std::setw(leadingSpaces) << "";
    for (const auto &cell : row) {
        std::cout << cell << " ";
    }
    std::cout << std::endl;
}

// Function to print the entire honeycomb board
void printHoneycombBoard(const std::vector<int> &rowCounts, const std::vector<std::string> &labels) {
    std::vector<std::vector<std::string>> board;
    int labelIndex = 0;

    for (int count : rowCounts) {
        std::vector<std::string> row;
        for (int i = 0; i < count; ++i) {
            if (labelIndex < labels.size()) {
                row.push_back(labels[labelIndex++]);
            } else {
                row.push_back(" ");
            }
        }
        board.push_back(row);
    }

    int maxRowSize = *std::max_element(rowCounts.begin(), rowCounts.end());
    int leadingSpaces = maxRowSize;

    for (int i = 0; i < board.size(); ++i) {
        printHexagonLine(leadingSpaces, board[i]);
        leadingSpaces = std::max(0, leadingSpaces - 1); // Reduce leading spaces for the next row
    }
}

int main() {
    std::vector<int> rowCounts = {3, 4, 5, 4, 3}; // Example row counts for the honeycomb pattern
    std::vector<std::string> labels = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};

    printHoneycombBoard(rowCounts, labels);

    return 0;
}
