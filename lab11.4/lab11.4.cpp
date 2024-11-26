#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void displayMenu();
bool readMatrix(const string& filename, int& n, int& m, int**& matrix);
int findMaxInRow(const int* row, int m);
bool writeNewFile(const string& inputFile, const string& outputFile);
void deleteMatrix(int** matrix, int n);

int main() {
    string inputFile, outputFile;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Введіть ім'я вхідного файлу: ";
            cin >> inputFile;
            cout << "Введіть ім'я вихідного файлу: ";
            cin >> outputFile;

            if (writeNewFile(inputFile, outputFile)) {
                cout << "Файл успішно створено.\n";
            }
            else {
                cout << "Помилка при створенні файлу.\n";
            }
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }
    return 0;
}

void displayMenu() {
    cout << "=== МЕНЮ ===\n";
    cout << "1. Обробити файл\n";
    cout << "0. Вийти\n";
    cout << "Ваш вибір: ";
}

bool readMatrix(const string& filename, int& n, int& m, int**& matrix) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Помилка: не вдалося відкрити файл " << filename << "\n";
        return false;
    }

    inFile >> n >> m;
    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            inFile >> matrix[i][j];
        }
    }
    return true;
}

int findMaxInRow(const int* row, int m) {
    int maxVal = numeric_limits<int>::min();
    for (int j = 0; j < m; ++j) {
        if (row[j] > maxVal) {
            maxVal = row[j];
        }
    }
    return maxVal;
}

bool writeNewFile(const string& inputFile, const string& outputFile) {
    int n, m;
    int** matrix = nullptr;

    if (!readMatrix(inputFile, n, m, matrix)) {
        return false;
    }

    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Помилка: не вдалося створити файл " << outputFile << "\n";
        deleteMatrix(matrix, n);
        return false;
    }

    outFile << n << " " << m << "\n";
    for (int i = 0; i < n; ++i) {
        int maxVal = findMaxInRow(matrix[i], m);
        for (int j = 0; j < m; ++j) {
            outFile << matrix[i][j] << " ";
        }
        outFile << maxVal << "\n";
    }

    deleteMatrix(matrix, n);
    return true;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}