#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>


struct HighScore {
    char name[17]; // fixed-size buffer for binary records
    uint32_t score;
};


int main() {
    // Create / overwrite text file with initial entries
    {
        std::ofstream out("highscore.txt", std::ios::out);
        if (!out) {
            std::cerr << "Error creating highscore.txt" << std::endl;
            return 1;
        }
        out << "Simon 2026\n";
        out << "Tom 2024\n";
        out << "Luc 2022\n";
        out << "Francois 2021\n";
    }

    // Append more entries
    {
        std::ofstream out("highscore.txt", std::ios::app);
        if (!out) {
            std::cerr << "Error opening highscore.txt for appending" << std::endl;
            return 1;
        }
        out << "simmus\n";
        out << "Simon 2026\n";
        out << "Tom 2024\n";
        out << "Luc 2022\n";
        out << "Fran 2021\n";
        if (out.bad()) {
            std::cerr << "Error appending to highscore.txt" << std::endl;
            return 1;
        }
    }

    // Read and print text file
    {
        std::ifstream in("highscore.txt");
        if (!in) {
            std::cerr << "Error opening highscore.txt for reading" << std::endl;
            return 1;
        }
        std::string name;
        int score;
        while (in >> name >> score) {
            std::cout << name << " " << score << std::endl;
        }
        if (in.bad()) {
            std::cerr << "I/O error while reading highscore.txt" << std::endl;
            return 1;
        }
    }

    // Write binary file
    {
        std::ofstream bout("highscore.bin", std::ios::binary);
        if (!bout) {
            std::cerr << "Error creating highscore.bin" << std::endl;
            return 1;
        }

        HighScore scores[5];
        std::memset(scores, 0, sizeof(scores));
        std::strncpy(scores[0].name, sizeof(scores[0].name), "Sim", sizeof(scores[0].name) - 1); scores[0].score = 2026;
        std::strncpy(scores[1].name, sizeof(scores[1].name), "Tom", sizeof(scores[1].name) - 1); scores[1].score = 2024;
        std::strncpy(scores[2].name, sizeof(scores[2].name), "Luc", sizeof(scores[2].name) - 1); scores[2].score = 2022;
        std::strncpy(scores[3].name, sizeof(scores[3].name), "Fra", sizeof(scores[3].name) - 1); scores[3].score = 2021;
        std::strncpy(scores[4].name, sizeof(scores[4].name), "New", sizeof(scores[4].name) - 1); scores[4].score = 2025;

        uint32_t numscores = static_cast<uint32_t>(sizeof(scores) / sizeof(scores[0]));
        bout.write(reinterpret_cast<const char*>(&numscores), sizeof(numscores));
        bout.write(reinterpret_cast<const char*>(scores), numscores * sizeof(HighScore));
        if (bout.bad()) {
            std::cerr << "Error writing to highscore.bin" << std::endl;
            return 1;
        }
    }

    // Read binary file and print its contents
    {
        std::ifstream bin("highscore.bin", std::ios::binary);
        if (!bin) {
            std::cerr << "Error opening highscore.bin for reading" << std::endl;
            return 1;
        }
        uint32_t n;
        bin.read(reinterpret_cast<char*>(&n), sizeof(n));
        if (!bin) {
            std::cerr << "Error reading number of entries from highscore.bin" << std::endl;
            return 1;
        }
        std::vector<HighScore> scores;
        scores.resize(n);
        bin.read(reinterpret_cast<char*>(scores.data()), n * sizeof(HighScore));
        if (bin.bad()) {
            std::cerr << "Error reading entries from highscore.bin" << std::endl;
            return 1;
        }
        for (uint32_t i = 0; i < n; ++i) {
            std::cout << scores[i].name << " " << scores[i].score << std::endl;
        }
    }

    return 0;
}
