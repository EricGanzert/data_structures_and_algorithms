#include "chapter3.h"

#include <algorithm>
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
    , entries(maxEntries)
{}

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
    else if (hasMaxEntries(e))
    {
        return;
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

GameEntry Scores::at(int i) const
{
    if (i < 0 || i >= numEntries)
    {
        throw runtime_error("Invalid index");
    }

    return entries[i]; 
}

bool Scores::hasMaxEntries(const GameEntry& e) const
{
    size_t entriesByThisPlayer = count_if(entries.begin(), entries.end(), [&e](const auto& entry)
    {
        return e.getName() == entry.getName(); 
    });

    return entriesByThisPlayer >= static_cast<size_t>(maxEntries) / 2;
}

int Scores::maxEntriesPerPlayer() const
{
    return maxEntries / 2;
}

int Scores::numScores() const
{
    return numEntries;
}

void transpose(Matrix& matrix)
{
    auto rows = matrix.size();
    if (rows < 2)
    {
        return;
    }
    auto cols = matrix.begin()->size();
    if (cols < 2 || rows != cols)
    {
        return;
    }

    for (auto i=0u; i<rows; i++)
    {
        for (auto j=i; j<cols; j++)
        {
            auto temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}