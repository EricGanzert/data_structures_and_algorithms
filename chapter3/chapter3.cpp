#include "chapter3.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>

using namespace std;

namespace {
float arraySum(const vector<float>& row, size_t index)
{
    if (index==0)
    {
        return row[0];
    }
    return row[index] + arraySum(row, index-1);
}

float recursiveSumInternal(const Matrix& matrix, int index, size_t maxSize)
{
    if (index == maxSize - 1)
    {
        return arraySum(matrix[index], matrix[index].size()-1);
    }
    return arraySum(matrix[index], matrix[index].size()-1) + recursiveSumInternal(matrix, index+1, maxSize);
}

void addNodes(StringLinkedList& list, vector<string>& items)
{
    if (items.empty())
    {
        return;
    }

    auto item = items.back();
    items.pop_back();
    list.addFront(item);
    addNodes(list, items);
}
}

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

float recursiveSum(const Matrix& matrix)
{
    if (matrix.empty())
    {
        return 0;
    }

    if (matrix.size() == 1)
    {
        return arraySum(matrix.front(), matrix.front().size()-1);
    }

    return recursiveSumInternal(matrix, 0, matrix.size());
}

StringLinkedList::StringLinkedList() : head(nullptr)
{}

StringLinkedList::~StringLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
}

bool StringLinkedList::empty()
{
    return head == nullptr;
}

const string& StringLinkedList::front() const
{
    return head->elem;
}

void StringLinkedList::addFront(const string& e)
{
    StringNode* v = new StringNode;
    v->elem = e;
    v->next = head;
    head = v;
    numElements++;
}

void StringLinkedList::removeFront()
{
    StringNode* old = head;
    head = old->next;
    delete old;
    numElements--;
}

size_t StringLinkedList::size()
{
    return numElements;
}

void recursivelyDefineList(StringLinkedList& list, const vector<string>& items)
{
    addNodes(list, vector<string>(items));
    return;
}