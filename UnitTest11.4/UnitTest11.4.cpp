#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include "../lab11.4/lab11.4.cpp"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestWriteNewFile)
        {
            // Створюємо вхідний файл
            ofstream inputFile("input.txt");
            inputFile << "3 3\n"; // Розмір матриці: 3x3
            inputFile << "1 2 3\n";
            inputFile << "4 5 6\n";
            inputFile << "7 8 9\n";
            inputFile.close();

            // Викликаємо функцію для обробки
            string inputFileName = "input.txt";
            string outputFileName = "output.txt";

            bool result = writeNewFile(inputFileName, outputFileName);
            Assert::IsTrue(result, L"Функція writeNewFile повинна була успішно завершитися.");

            // Читаємо вихідний файл і перевіряємо його вміст
            ifstream outputFile(outputFileName);
            Assert::IsTrue(outputFile.is_open(), L"Не вдалося відкрити вихідний файл.");

            int n, m;
            outputFile >> n >> m;

            Assert::AreEqual(3, n, L"Кількість рядків повинна дорівнювати 3.");
            Assert::AreEqual(3, m, L"Кількість стовпців повинна дорівнювати 3.");

            int expectedMatrix[3][4] = {
                {1, 2, 3, 3}, // Максимум у рядку: 3
                {4, 5, 6, 6}, // Максимум у рядку: 6
                {7, 8, 9, 9}  // Максимум у рядку: 9
            };

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m + 1; ++j) { // +1 для доданого максимуму
                    int value;
                    outputFile >> value;
                    Assert::AreEqual(expectedMatrix[i][j], value, L"Невірне значення у вихідному файлі.");
                }
            }

            outputFile.close();
        }
    };
}
