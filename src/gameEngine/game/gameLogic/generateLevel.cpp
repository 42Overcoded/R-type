#include "../../GameEngine.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>

int get_random(int min, int max) {
    int random = min + (rand() % (max - min + 1));
    return random;
}

int number_of_mob_to_generate(int length, int difficulty) {
    int mobToGenerate = MOB_PER_LENGTH / difficulty;
    mobToGenerate = length / mobToGenerate;
    mobToGenerate = mobToGenerate + ((mobToGenerate * get_random(-15, 15)) / 100);
    if (mobToGenerate <= 0) {
        mobToGenerate = 1;
    }
    return mobToGenerate;
}

int number_of_boss_to_generate(int length, int difficulty) {
    int bossToGenerate = BOSS_PER_LENGTH / difficulty;
    bossToGenerate = length / bossToGenerate;
    bossToGenerate = bossToGenerate + ((bossToGenerate * get_random(-15, 15)) / 100);
    if (bossToGenerate <= 0) {
        bossToGenerate = 1;
    }
    return bossToGenerate;
}

bool order(const Generated &a, const Generated &b) {
    return a.x < b.x;
}


int getSeedFromStrAndInts(const std::string& str, int int1, int int2) {
    return static_cast<int>(std::hash<std::string>{}(str) ^ int1 ^ int2);
}

std::vector<Generated> gameEngine::generateMap(int length, int difficulty, std::string seed_str) {
    int seed = getSeedFromStrAndInts(seed_str, length, difficulty);
    /// Should Be replaced with a json          //
    std::vector<int> enemies = {0, 1, 2};       //
    std::vector<int> elite = {3};               //
    std::vector<int> bosses = {4};              //
    std::vector<int> pattern = {0, 1, 2};       //
    std::vector<int> elitePattern = {3};        //
    std::vector<int> bossesPattern = {4};       //
    /// Should Be replaced with a json          //
    std::srand(seed);

    int mobToGenerate = number_of_mob_to_generate(length, difficulty);
    int eliteToGenerate = mobToGenerate / 10;
    int bossToGenerate = number_of_boss_to_generate(length, difficulty);
    std::vector<Generated> generated;
    for (int i = 0; i < mobToGenerate; i++) {
        Generated gen(enemies[get_random(0, enemies.size() - 1)], pattern[get_random(0, pattern.size() - 1)], get_random(0 + SPAWN_START, length + SPAWN_START), get_random(50, HEIGHT_START));
        generated.push_back(gen);
    }
    for (int i = 0; i < eliteToGenerate; i++) {
        Generated gen(elite[get_random(0, elite.size() - 1)], elitePattern[get_random(0, elitePattern.size() - 1)], get_random(0 + SPAWN_START, length + SPAWN_START), get_random(50, HEIGHT_START));
        generated.push_back(gen);
    }
    for (int i = 0; i < bossToGenerate; i++) {
        Generated gen(bosses[get_random(0, bosses.size() - 1)], bossesPattern[get_random(0, bossesPattern.size() - 1)], get_random(0 + SPAWN_START, length + SPAWN_START), get_random(50, HEIGHT_START), true);
        generated.push_back(gen);
    }
    std::sort(generated.begin(), generated.end(), order);
    return generated;
}

std::vector<Generated> gameEngine::loadMap(std::string path)
{
    /// Should Be replaced with a json          //
    std::vector<int> enemies = {0, 1, 2};       //
    std::vector<int> elite = {3};               //
    std::vector<int> bosses = {4, 7};              //
    std::vector<int> pattern = {0, 1, 2};       //
    std::vector<int> elitePattern = {3};        //
    std::vector<int> bossesPattern = {4};       //
    /// Should Be replaced with a json          //

    std::vector<Generated> generated;

    std::ifstream inputFile(path);
    if (inputFile.is_open())
    {
        Generated entry;
        while (inputFile >> entry.id >> entry.pattern >> entry.x >> entry.y)
        {
            if (std::find(bosses.begin(), bosses.end(), entry.id) != bosses.end()) {
                entry.is_boss = true;
            } else
                entry.is_boss = false;
            generated.push_back(entry);
        }

        inputFile.close();
    }

    return generated;
}
