// CSVWorker.cpp
#include "CSVWorker.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

CSVWorker::CSVWorker(const std::string& fname) : filename(fname) {}

bool CSVWorker::writeProfiles() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open csv file: " << filename << std::endl;
        return false;
    }

    file << "Name,Age,HandsPlayed,HandsEnteredPreflop,BigBlindsPerHundredHands,vPiP\n";
    for (const auto& profile : profiles) {
        file << profile.name                        << ","
             << profile.age                         << ","
             << profile.handsPlayed                 << ","
             << profile.handsEnteredPreflop         << ","
             << profile.bigBlindsPerHundredHands    << ","
             << profile.vPiP                        << "\n";
    }

    file.close();
    // std::cout << "Data written to " << filename << std::endl;
    return true;
}

std::vector<PlayerProfile> CSVWorker::readProfiles() {
    // Opening the file in read mode
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return std::vector<PlayerProfile>();
    }
    
    profiles.clear();
    std::string line;
    getline(file, line); // Skip header

    // Populating the profiles vector with the profiles in the file
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        PlayerProfile profile;

        getline(ss, profile.name, ',');

        getline(ss, field, ',');
        profile.age = std::stoi(field);

        getline(ss, field, ',');
        profile.handsPlayed = std::stoi(field);

        getline(ss, field, ',');
        profile.handsEnteredPreflop = std::stoi(field);

        getline(ss, field, ',');
        profile.bigBlindsPerHundredHands = std::stoi(field);

        getline(ss, field, ',');
        profile.vPiP = std::stoi(field);

        profiles.push_back(profile);
    }

    // Closing the file and returning the profiles
    file.close();
    return profiles;
}

void CSVWorker::addProfile(const PlayerProfile& profile) {
    this->readProfiles();
    profiles.push_back(profile);
    this->writeProfiles();
}

void CSVWorker::updateProfile(const PlayerProfile& profile) {
    this->readProfiles();
    for (auto& p : profiles) {
        if (p.name == profile.name) {
            p = profile;
            break;
        }
    }
    this->writeProfiles();
}

const std::vector<PlayerProfile>& CSVWorker::getProfiles() const {
    return profiles;
}

void CSVWorker::printProfiles() const {
    for (const auto& profile : profiles) {
        std::cout << "Name: " << profile.name
                  << ", Age: " << profile.age
                  << ", BigBlindsPerHundredHands: " << profile.bigBlindsPerHundredHands
                  << ", vPiP: " << profile.vPiP << std::endl;
    }
}