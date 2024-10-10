// PlayerProfile.h
#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

#include <string>

struct PlayerProfile {
    std::string name;
    int age;

    // General statistics
    int handsPlayed = 0;                        // Number of hands played
    int handsEnteredPreflop = 0;                // Number of hands entered preflop

    // Defining the statistics we are recording
    int bigBlindsPerHundredHands = 0;           // BB/100
    int vPiP = 0;                               // Voluntarily Put in Pot
};

#endif // PLAYER_PROFILE_H