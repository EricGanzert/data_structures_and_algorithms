#include "chapter3.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
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

void arrayMaxInternal(const vector<int>& array, int currentIndex, int& currentMax)
{
    if (currentIndex >= array.size())
    {
        return;
    }

    if (array[currentIndex] > currentMax)
    {
        currentMax = array[currentIndex];
    }
    currentIndex++;
    arrayMaxInternal(array, currentIndex, currentMax);
}

class RandomNumberGenerator {
public:
    RandomNumberGenerator()
        : m_rng(m_dev())
    {}
    int getNumber(int min, int max) {
        uniform_int_distribution<mt19937::result_type> dist(min, max);
        return dist(m_rng);
    }
private:
    random_device m_dev;
    mt19937 m_rng;
};
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

StringNode* StringLinkedList::penultimate()
{
    if (numElements < 2)
    {
        return nullptr;
    }

    auto leader = head;
    auto follower = head;

    while (leader->next)
    {
        follower = leader;
        leader = leader->next;
    }
    
    return follower;
}

int findArrayMaximum(const vector<int>& array)
{
    if (array.empty())
    {
        throw runtime_error("cannot find the maximum of empty array");
    }

    int currentIndex = 0;
    int currentMax = numeric_limits<int>::min();
    arrayMaxInternal(array, currentIndex, currentMax);
    return currentMax;
}

void removeRandomUntilEmpty(vector<int>& array)
{
    RandomNumberGenerator rng;
    while(!array.empty())
    {
        auto iter = array.begin() + rng.getNumber(0, static_cast<int>(array.size())-1);
        array.erase(iter);
    }
}

void TicTacToe::clearBoard()
{
    for_each(m_board.begin(), m_board.end(), [this](auto& row){
        fill(row.begin(), row.end(), Empty);
    });
    m_currentPlayer = X;
}

void TicTacToe::putMark(int i, int j)
{
    if (i < 0 || i >= m_board.size()
        || j < 0 || j >= m_board.front().size())
    {
        throw runtime_error("index out of range");
    }

    m_board[i][j] = m_currentPlayer;
    if (m_currentPlayer == X)
    {
        m_currentPlayer = O;
    }
    else
    {
        m_currentPlayer = X;
    }
}

bool TicTacToe::isWin(int mark)
{
    int win = 3 * mark;
    return ((m_board[0][0] + m_board[0][1] + m_board[0][2] == win)
        || (m_board[1][0] + m_board[1][1] + m_board[1][2] == win)
        || (m_board[2][0] + m_board[2][1] + m_board[2][2] == win)
        || (m_board[0][0] + m_board[1][0] + m_board[2][0] == win)
        || (m_board[0][1] + m_board[1][1] + m_board[2][1] == win)
        || (m_board[0][2] + m_board[1][2] + m_board[2][2] == win)
        || (m_board[0][0] + m_board[1][1] + m_board[2][2] == win)
        || (m_board[0][2] + m_board[1][1] + m_board[2][0] == win));
}

int TicTacToe::getWinner()
{
    if (isWin(X))
    {
        return X;
    }
    else if (isWin(O))
    {
        return O;
    }

    return Empty;

}

void TicTacToe::printBoard()
{
    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            auto mark = m_board[i][j];
            if (mark == X)
            {
                cout << "X";
            }
            if (mark == O)
            {
                cout << "O";
            }
            if (mark == Empty)
            {
                cout << " ";
            }

            if (j < 2)
            {
                cout << "|";
            }
        }
        if (i < 2)
        {
            cout << endl << "-+-+-" << endl;
        }
    }
}