#include "chapter3.h"

#include <stdexcept>

using namespace std;

GameEntry::GameEntry(const string& n, int s)
    : name(n), score(s) {}

string GameEntry::getName() const
{
    return name;
}

int GameEntry::getScore() const
{
    return score;
}

Scores::Scores(int maxEnt) 
    : maxEntries(maxEnt)
    , numEntries(0)
    , entries(new GameEntry[maxEntries])
{}

Scores::~Scores() {
    delete[] entries;
}

void Scores::add(const GameEntry& e)
{
    int newScore = e.getScore();
    if (numEntries == maxEntries)
    {
        if (newScore <= entries[maxEntries-1].getScore())
        {
            return;
        }
    }
    else {
        numEntries++;
    }

    int i = numEntries - 2;
    while (i >= 0 && entries[i].getScore() < newScore)
    {
        entries[i+1] = entries[i];
        i--;
    }
    entries[i+1] = e;
}

GameEntry Scores::remove(int i)
{
    if (i < 0 || i >= numEntries)
    {
        throw runtime_error("Invalid index");
    }

    GameEntry e = entries[i];
    for (int j = i+1; j < numEntries; j++)
    {
        entries[j-1] = entries[j];
    }
    
    numEntries--;
    return e;
}