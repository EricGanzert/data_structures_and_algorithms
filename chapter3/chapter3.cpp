#include "chapter3.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <unordered_set>

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

uint32_t addNTimes(uint32_t toAdd, uint32_t totalTimes, uint32_t& count)
{
    if (++count >= totalTimes)
    {
        return toAdd;
    }
    return toAdd + addNTimes(toAdd, totalTimes, count);
}

int stringToDigitsInternal(string& number, int exp)
{
    if (number.empty())
    {
        return 0;
    }

    constexpr int CharToIntOffset = 48;

    auto digitChar = number.back();
    number.pop_back();

    int digit = static_cast<int>(digitChar) - CharToIntOffset;
    auto thisRoundContribution = (static_cast<int>(pow(10, exp)) * digit);
    return thisRoundContribution + stringToDigitsInternal(number, ++exp);
}

void outputAllSubsetsInternal(vector<int>& used, set<int>& unused)
{
    for (auto i=0u; i<unused.size(); i++)
    {
        auto iter = unused.begin();
        advance(iter, i);
        auto item = *iter;
        unused.erase(iter);
        used.push_back(item);

        for (const auto& i : used)
        {
            cout << i << " ";
        }
        cout << endl;
            
        outputAllSubsetsInternal(used, unused);
        unused.insert(item);
        used.pop_back();
    }

}

void findMinMaxInternal(const vector<int>& input, int& min, int& max, int index)
{
    if (index >= input.size())
    {
        return;
    }

    auto item = input[index];
    if (item < min)
    {
        min = item;
    }

    if (item > max)
    {
        max = item;
    }

    findMinMaxInternal(input, min, max, index+1);
}

void accumulateSums(const vector<int>& input, int i, int j, unordered_set<int>& sums)
{
    if (j >= i)
    {
        return;
    }

    sums.insert(input[i] + input[j]);
    accumulateSums(input, i, ++j, sums);
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
    , entries(GameEntry::chooseLarger)
{}

void Scores::add(const GameEntry& e)
{
    if (hasMaxEntries(e))
    {
        return;
    }

    entries.insert(e);
    while (entries.size() > maxEntries)
    {
        entries.erase(--entries.end());
    }
}

GameEntry Scores::remove(int i)
{
    if (i < 0 || i >= entries.size())
    {
        throw runtime_error("Invalid index");
    }

    auto iter = entries.begin();
    advance(iter, i);

    auto result = *iter;
    entries.erase(iter);
    return result;
}

GameEntry Scores::at(int i) const
{
    if (i < 0 || i >= entries.size())
    {
        throw runtime_error("Invalid index");
    }

    auto iter = entries.begin();
    advance(iter, i);
    return *iter;
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
    return static_cast<int>(entries.size());
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

bool findRepeat(const vector<int>& input, int& repeatedItem, int numOccurances)
{
    unordered_multiset<int> seen;
    for (const auto& item : input)
    {
        seen.insert(item);
        if (seen.count(item) == numOccurances)
        {
            repeatedItem = item;
            return true;
        }
    }
    return false;
}

void EnchantedForest::meet(int i, int j)
{
    if (m_gameFinished || i == j)
    {
        return;
    }

    m_trackMeetings[i].insert(j);
    m_trackMeetings[j].insert(i);

    if (m_trackMeetings[i].size() >= 1000)
    {
        m_winners.emplace_back(i);
        m_gameFinished = true;
    }

    if (m_trackMeetings[j].size() >= 1000)
    {
        m_winners.emplace_back(j);
        m_gameFinished = true;
    }
}

const vector<int>& EnchantedForest::winners()
{
    return m_winners;
}

bool EnchantedForest::gameOver()
{
    return m_gameFinished;
}

uint32_t recursiveProduct(uint32_t m, uint32_t n)
{
    auto toAdd = n;
    auto totalTimes = m;
    uint32_t count = 0;

    return addNTimes(toAdd, totalTimes, count);
}

void StringLinkedList::print()
{
    auto temp = head;
    while(temp != nullptr)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

void StringLinkedList::reverseRecursive()
{
    if (empty())
    {
        return;
    }
    reverseNodesInternal(nullptr, head);
}

void StringLinkedList::reverseNodesInternal(StringNode* prev, StringNode* node)
{
    if (node->next == nullptr)
    {
        head = node;
        head->next = prev;
        return;
    }

    auto next = node->next;
    node->next = prev;
    reverseNodesInternal(node, next);
}

void StringLinkedList::reverse()
{
    if (size() < 2)
    {
        return;
    }

    StringNode* prev = nullptr;
    StringNode* node = head;

    while(node != nullptr)
    {
        // perform swap
        auto next = node->next; 
        node->next = prev;

        // advance iterators
        prev = node;
        node = next;
    }
    head = prev;
}

void StringLinkedList::concatenate(StringLinkedList& toConsume)
{
    if (toConsume.empty())
    {
        return;
    }

    auto tail = head;
    while(tail->next != nullptr)
    {
        tail = tail->next;
    }

    auto temp = toConsume.head;
    tail->next = temp;
    toConsume.head = nullptr;
}

void StringLinkedList::swapNodes(const string& a, const string& b)
{
    auto aRef = head;
    auto aJumpCount = 0u;
    while(!(aRef->elem == a || aRef->next == nullptr))
    {
        aRef = aRef->next;
        aJumpCount++;
    }
    if (aRef->elem != a)
    {
        throw runtime_error("could not find element to swap");
    }

    auto bRef = head;
    auto bJumpCount = 0u;
    while(!(bRef->elem == b || bRef->next == nullptr))
    {
        bRef = bRef->next;
        bJumpCount++;
    }
    if (bRef->elem != b)
    {
        throw runtime_error("could not find element to swap");
    }

    auto firstArg = (aJumpCount < bJumpCount) ? aRef : bRef;
    auto secondArg = (aJumpCount < bJumpCount) ? bRef : aRef;
    swapNodesInternal(firstArg, secondArg);
}

void StringLinkedList::swapNodesInternal(StringNode* a, StringNode* b)
{
    if (!(a && b))
    {
        throw runtime_error("cannot swap null nodes");
    }

    if (a == b)
    {
        return;
    }

    auto findPrev = [&](StringNode* target)
    {
        StringNode* result = nullptr;
        if (target == head)
        {
            return result;
        }

        result = head;
        while (result->next != target)
        {
            result = result->next;
        }
        return result;
    };

    auto aPrev = findPrev(a);
    auto bPrev = findPrev(b);
    auto aNext = a->next;
    auto bNext = b->next;

    if (a->next == b)
    {
        aPrev->next = b;
        b->next = a;
        a->next = bNext;
    }
    else
    {
        (aPrev ? aPrev->next : head) = b;
        b->next = aNext;

        (bPrev ? bPrev->next : head) = a;
        a->next = bNext;
    }
}


TowersOfHanoi::TowersOfHanoi(uint32_t numDisks)
    : m_numDisks(static_cast<int>(numDisks))
{
    for (auto disk=1; disk <= m_numDisks; disk++)
    {
        pegs.front().push_back(disk);
    }
}

void TowersOfHanoi::print()
{
    auto pegSpace = m_numDisks + 1;
    auto currentHeight = m_numDisks;

    while(currentHeight > 0)
    {
        for (const auto& peg : pegs)
        {
            string marker;
            if (peg.size() >= currentHeight)
            {
                auto numDashes = m_numDisks - peg[currentHeight-1] + 1;
                marker = string(numDashes, '-');
            }
            cout << setw(pegSpace) << marker;
        }
        cout << endl;
        currentHeight--;
    }
}

void TowersOfHanoi::solve()
{
    solveInternal(m_numDisks, 0, 2, 1);
}

void TowersOfHanoi::move(int fromPeg, int destPeg)
{
    auto topDisk = pegs[fromPeg].back();
    pegs[fromPeg].pop_back();
    pegs[destPeg].push_back(topDisk);
}

void TowersOfHanoi::solveInternal(int n, int start, int dest, int temp)
{
    if (n == 0)
    {
        return;
    }
    if (n == 1)
    {
        move(start, dest);
        return;
    }
    if (n == 2)
    {
        move(start, temp);
        move(start, dest);
        move(temp, dest);
        return;
    }

    solveInternal(n-1, start, temp, dest);
    move(start, dest);
    solveInternal(n-1, temp, dest, start);
}

bool TowersOfHanoi::isSolved()
{
    if (!pegs[0].empty())
    {
        return false;
    }

    if (!pegs[1].empty())
    {
        return false;
    }

    if (pegs[2].size() != m_numDisks)
    {
        return false;
    }

    for (auto i = 0; i < m_numDisks; i++)
    {
        if (i>0)
        {
            if (!(pegs[2][i] > pegs[2][i-1]))
            {
                return false;
            }
        }
    }
    return true;
}

int stringToDigits(const string& number)
{
    auto numberCopy(number);
    return stringToDigitsInternal(numberCopy, 0);
}

size_t StringLinkedList::countNodes()
{
    if (empty())
    {
        return 0;
    }

    return countNodesInternal(head);
}

size_t StringLinkedList::countNodesInternal(StringNode* node)
{
    if (node->next == nullptr)
    {
        return 1;
    }

    return 1 + countNodesInternal(node->next);
}

void outputAllSubsets(const set<int>& items)
{
    auto inputCopy(items);
    vector<int> used;
    outputAllSubsetsInternal(used, inputCopy);
}


void findMinMax(const vector<int>& input, int& min, int& max)
{
    if (input.empty())
    {
        return;
    }

    min = numeric_limits<int>::max();
    max = numeric_limits<int>::min();
    findMinMaxInternal(input, min, max, 0);
}

bool containsSumOf2Earlier(const vector<int>& input)
{
    unordered_set<int> sums;
    for (auto i=0u; i<input.size(); i++)
    {
        if (sums.count(input[i]))
        {
            cout << input[i] << " is a sum of previously elements in this vector" << endl;
            return true;
        }

        accumulateSums(input, i, 0, sums);
    }
    return false;
}