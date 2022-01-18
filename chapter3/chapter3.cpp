#include "chapter3.h"

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