#include "chapter3.h"

#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <type_traits>
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
    if (index == static_cast<int>(maxSize - 1))
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
    if (currentIndex >= static_cast<int>(array.size()))
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
    if (index >= static_cast<int>(input.size()))
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

void sortEvensFirstThenOddsRecursiveInternal(vector<int>&input, vector<int>& evens, vector<int>& odds)
{
    if (input.empty())
    {
        return;
    }

    auto isEven = [](const auto& num)
    {
        return num % 2 == 0;
    };

    auto item = input.back();
    input.pop_back();
    if (isEven(item))
    {
        evens.push_back(item);
    }
    else
    {
        odds.push_back(item);
    }

    sortEvensFirstThenOddsRecursiveInternal(input, evens, odds);
}

void reverseStringRecursive(string& input, int i, int j)
{
    if (i >= j)
    {
        return;
    }

    auto temp = input[i];
    input[i] = input[j];
    input[j] = temp;

    reverseStringRecursive(input, i + 1, j - 1);
}

const string g_alphabet = "abcdefghijklmnopqrstuvwxyz 0123456789.,!?:;-/";
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

bool operator==(const GameEntry& left, const GameEntry& right)
{
    return left.getName() == right.getName()
        && left.getScore() == right.getScore();
}

IScores::IScores(int maxEnt)
    : maxEntries(maxEnt)
{
}

Scores::Scores(int maxEnt) 
    : IScores(maxEnt)
    , entries(GameEntry::chooseLarger)
{}

void Scores::add(const GameEntry& e)
{
    if (hasMaxEntries(e))
    {
        return;
    }

    entries.insert(e);
    while (static_cast<int>(entries.size()) > maxEntries)
    {
        entries.erase(--entries.end());
    }
}

GameEntry Scores::remove(int i)
{
    if (i < 0 || i >= static_cast<int>(entries.size()))
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
    if (i < 0 || i >= static_cast<int>(entries.size()))
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

ScoreLinkedList::ScoreLinkedList(int maxEnt)
    : IScores(maxEnt)
{
}

ScoreLinkedList::~ScoreLinkedList()
{
    while(head != nullptr)
    {
        remove(0);
    }
}

void ScoreLinkedList::add(const GameEntry& e)
{
    // 1. insert a new node with game entry in order of score
    if (head == nullptr)
    {
        head = new Node<GameEntry>;
        head->elem = e;
        head->next = nullptr;
        count++;
        return;
    }

    auto iter = head;
    while(iter->next != nullptr)
    {
        if (iter->elem.getScore() < e.getScore() || iter->next->elem.getScore() < e.getScore())
        {
            break;
        }
        iter = iter->next;
    }

    auto newEntry = new Node<GameEntry>;
    newEntry->elem = e;

    if (iter == head)
    {
        if (e.getScore() > head->elem.getScore())
        {
            head = newEntry;
            newEntry->next = iter;
            count++;
            return;
        }
        else if (count == 1)
        {
            head->next = newEntry;
            newEntry->next = nullptr;
            count++;
            return;
        }
    }

    // put the new node just after iter
    newEntry->next = iter->next;
    iter->next = newEntry;
    count++;

    // 2. if we have reached limit of scores remove the last one of the list
    if (count > maxEntries)
    {
        while(iter->next != nullptr)
        {
            iter = iter->next;
        }

        auto newLast = getPreceeding(iter);
        newLast->next = nullptr;
        delete iter;
        count--;
    }
}

Node<GameEntry>* ScoreLinkedList::getPreceeding(Node<GameEntry>* node)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    auto iter = head;
    while(iter != nullptr && iter->next != node)
    {
        iter = iter->next;
    }

    if (iter == nullptr)
    {
        throw runtime_error("could not find preceeding node");
    }

    return iter;
}

GameEntry ScoreLinkedList::remove(int i)
{
    if (head == nullptr || count - 1 < i)
    {
        throw runtime_error("invalid index in call to remove");
    }

    GameEntry result{};

    if (i == 0)
    {
        auto removeNode = head;
        head = head->next;
        result = removeNode->elem;
        delete removeNode;
        count--;
        return result;
    }

    auto iter = head;
    for (auto hop = 0; hop < i - 1; hop++)
    {
        iter = iter->next;
    }

    auto removeNode = iter->next;
    iter->next = removeNode->next;
    result = removeNode->elem;
    delete removeNode;
    count--;

    return result;
}

GameEntry ScoreLinkedList::at(int i) const
{
    if (head == nullptr || i >= count)
    {
        throw runtime_error("invalid index in call to at()");
    }

    auto iter = head;
    for (auto iterCount = 0; iterCount < i; iterCount++)
    {
        iter = iter->next;
    }
    return iter->elem;
}

int ScoreLinkedList::numScores() const
{
    return count;
}

ScoreDLinkedList::ScoreDLinkedList(int maxEnt)
    : IScores(maxEnt), header(new DNode<GameEntry>()), trailer(new DNode<GameEntry>())
{
    header->next = trailer;
    trailer->prev = header;
}

bool ScoreDLinkedList::empty() const
{
    return header->next == trailer
        && trailer->prev == header;
}

ScoreDLinkedList::~ScoreDLinkedList()
{
    while(!empty())
    {
        remove(0);
    }
}

void ScoreDLinkedList::add(const GameEntry& e)
{
    if (empty())
    {
        auto newEntry = new DNode<GameEntry>;
        newEntry->elem = e;

        header->next = newEntry;
        newEntry->prev = header;

        trailer->prev = newEntry;
        newEntry->next = trailer;

        count++;
        return;
    }

    auto iter = header->next;
    while(iter != trailer)
    {
        if (e.getScore() > iter->elem.getScore())
        {
            break;
        }
        iter = iter->next;
    }

    if (count == maxEntries && iter->next == trailer && e.getScore() <= iter->elem.getScore())
    {
        // new game entry didn't make the cut
        return;
    }

    auto newEntry = new DNode<GameEntry>;
    newEntry->elem = e;

    auto beforeNewNode = iter->prev;

    beforeNewNode->next = newEntry;
    newEntry->prev = beforeNewNode;

    newEntry->next = iter;
    iter->prev = newEntry;

    count++;

    if (count > maxEntries)
    {
        auto toRemove = trailer->prev;
        auto newLastNode = toRemove->prev;
        newLastNode->next = trailer;
        trailer->prev = newLastNode;
        delete toRemove;
        count--;
    }
}

GameEntry ScoreDLinkedList::remove(int i)
{
    if (empty() || (count - 1) < i)
    {
        throw runtime_error("invalid index in call to at()");
    }

    auto toRemove = getRefToIndex(i);
    auto before = toRemove->prev;
    auto after = toRemove->next;

    before->next = after;
    after->prev = before;
    auto result = toRemove->elem;

    delete toRemove;
    count--;

    return result;
}

GameEntry ScoreDLinkedList::at(int i) const
{
    if (empty() || (count - 1) < i)
    {
        throw runtime_error("invalid index in call to at()");
    }

    return getConstRefToIndex(i)->elem;
}

const DNode<GameEntry>* ScoreDLinkedList::getConstRefToIndex(int i) const
{
    auto closerToFront = i <= count / 2;
    auto numHops = closerToFront ? i : ((count-1) - i);
    
    auto iter = closerToFront ? header->next : trailer->prev;
    for (auto hop = 0; hop < numHops; hop++)
    {
        iter = closerToFront ? iter->next : iter->prev;
    }
    return iter;
}

DNode<GameEntry>* ScoreDLinkedList::getRefToIndex(int i)
{
    // to avoid repeating the code written in getConstRefToIndex
    return const_cast<DNode<GameEntry>*>(getConstRefToIndex(i));
}

int ScoreDLinkedList::numScores() const
{
    return count;
}

ScoreCLinkedList::ScoreCLinkedList(int maxEnt)
    : IScores(maxEnt)
{
}

ScoreCLinkedList::~ScoreCLinkedList()
{
    while(!empty())
    {
        remove(0);
    }
}

void ScoreCLinkedList::add(const GameEntry& e)
{
    if (empty())
    {
        cursor = new DNode<GameEntry>;
        cursor->elem = e;
        cursor->next = cursor;
        cursor->prev = cursor;
        count++;
        return;
    }

    if (count == 1)
    {
        auto newEntry = new DNode<GameEntry>;
        newEntry->elem = e;
        newEntry->next = cursor;
        newEntry->prev = cursor;
        cursor->next = newEntry;
        cursor->prev = newEntry;
        count++;

        if (newEntry->elem.getScore() > cursor->elem.getScore())
        {
            cursor = newEntry;
        }
        return;
    }

    auto iter = cursor;
    do
    {
        if (e.getScore() > iter->elem.getScore())
        {
            break;
        }
        iter = iter->next;
    } while(iter != cursor);

    if (count == maxEntries && iter == cursor && e.getScore() <= iter->prev->elem.getScore())
    {
        // new game entry didn't make the cut
        return;
    }

    auto newEntry = new DNode<GameEntry>;
    newEntry->elem = e;

    auto beforeNewNode = iter->prev;
    beforeNewNode->next = newEntry;
    newEntry->prev = beforeNewNode;

    newEntry->next = iter;
    iter->prev = newEntry;

    if (newEntry->elem.getScore() > cursor->elem.getScore())
    {
        cursor = newEntry;
    }

    count++;

    if (count > maxEntries)
    {
        auto toRemove = cursor->prev;
        auto newLastNode = toRemove->prev;

        newLastNode->next = cursor;
        cursor->prev = newLastNode;
        delete toRemove;
        count--;
    }
}

GameEntry ScoreCLinkedList::remove(int i)
{
    if (empty() || (count - 1) < i)
    {
        throw runtime_error("invalid index in call to at()");
    }

    if (count == 1)
    {
        auto result = cursor->elem;
        delete cursor;
        cursor = nullptr;
        count--;
        return result;
    }

    auto toRemove = getRefToIndex(i);
    auto before = toRemove->prev;
    auto after = toRemove->next;

    before->next = after;
    after->prev = before;
    auto result = toRemove->elem;

    if (toRemove == cursor)
    {
        cursor = cursor->next;
    }
    delete toRemove;
    count--;

    return result;
}

GameEntry ScoreCLinkedList::at(int i) const
{
    if (empty() || (count - 1) < i)
    {
        throw runtime_error("invalid index in call to at()");
    }

    return getConstRefToIndex(i)->elem;
}

bool ScoreCLinkedList::empty() const
{
    return cursor == nullptr;
}

int ScoreCLinkedList::numScores() const
{
    return count;
}

const DNode<GameEntry>* ScoreCLinkedList::getConstRefToIndex(int i) const
{
    auto closerToFront = i <= count / 2;
    auto numHops = closerToFront ? i : (count - i);
    
    auto iter = cursor;
    for (auto hop = 0; hop < numHops; hop++)
    {
        iter = closerToFront ? iter->next : iter->prev;
    }
    return iter;
}

DNode<GameEntry>* ScoreCLinkedList::getRefToIndex(int i)
{
    // to avoid repeating the code written in getConstRefToIndex
    return const_cast<DNode<GameEntry>*>(getConstRefToIndex(i));
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
    Node<std::string>* v = new Node<std::string>;
    v->elem = e;
    v->next = head;
    head = v;
    numElements++;
}

void StringLinkedList::removeFront()
{
    Node<std::string>* old = head;
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
    auto itemsCopy(items);
    addNodes(list, itemsCopy);
    return;
}

Node<std::string>* StringLinkedList::penultimate()
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
    if (i < 0 || i >= static_cast<int>(m_board.size())
        || j < 0 || j >= static_cast<int>(m_board.front().size()))
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
        if (static_cast<int>(seen.count(item)) == numOccurances)
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

void StringLinkedList::reverseNodesInternal(Node<std::string>* prev, Node<std::string>* node)
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

    Node<std::string>* prev = nullptr;
    Node<std::string>* node = head;

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

void StringLinkedList::swapNodesInternal(Node<std::string>* a, Node<std::string>* b)
{
    if (!(a && b))
    {
        throw runtime_error("cannot swap null nodes");
    }

    if (a == b)
    {
        return;
    }

    auto findPrev = [&](Node<std::string>* target)
    {
        Node<std::string>* result = nullptr;
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
            if (static_cast<int>(peg.size()) >= currentHeight)
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

    if (static_cast<int>(pegs[2].size()) != m_numDisks)
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

size_t StringLinkedList::countNodesInternal(Node<std::string>* node)
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
            cout << input[i] << " is a sum of previous elements in this vector" << endl;
            return true;
        }

        accumulateSums(input, i, 0, sums);
    }
    return false;
}

void sortEvensFirstThenOdds(vector<int>& input)
{
    if (input.size() < 2)
    {
        return;
    }

    auto isEven = [](const auto& num)
    {
        return num % 2 == 0;
    };

    vector<int> evens;
    vector<int> odds;

    while(!input.empty())
    {
        auto item = input.back();
        input.pop_back();
        if (isEven(item))
        {
            evens.push_back(item);
        }
        else
        {
            odds.push_back(item);
        }
    }

    evens.insert(evens.end(), odds.begin(), odds.end());
    swap(input, evens);
}

void sortEvensFirstThenOddsRecursive(vector<int>& input)
{
    if (input.size() < 2)
    {
        return;
    }

    vector<int> evens;
    vector<int> odds;

    sortEvensFirstThenOddsRecursiveInternal(input, evens, odds);
    swap(input, evens);
}

void reverseString(string& input)
{
    if (input.size() < 2)
    {
        return;
    } 
    reverseStringRecursive(input, 0, static_cast<int>(input.size()) - 1);
}

bool charsMatch(const string& input, int i, int j)
{
    if (i >= j)
    {
        return true;
    }

    if (input[i] != input[j])
    {
        return false;
    }

    return true && charsMatch(input, i + 1, j - 1);
}

bool isPalendrome(const string& input)
{
    return charsMatch(input, 0, static_cast<int>(input.size()) - 1);
}

void countVC(const string& input, int index, int& vowelCount, int& consonantCount, bool yIsVowel=false)
{
    string vowels = "aeiou";
    string consonants = "bcdfghjklmnpqrstvwxz";

    if (yIsVowel)
    {
        vowels.push_back('y');
    }
    else
    {
        consonants.push_back('y');
    }

    if (index > static_cast<int>(input.size()) - 1)
    {
        return;
    }

    if (vowels.find(input[index]) != string::npos)
    {
        vowelCount++;
    }
    else if (consonants.find(input[index]))
    {
        consonantCount++;
    }

    countVC(input, index + 1, vowelCount, consonantCount, yIsVowel);
}

bool hasMoreVowelsThanConsonants(const string& input)
{
    const string vowels = "aeiou";
    int totalVCount = 0;
    int totalCCount = 0;

    vector<string> words;
    size_t pos = 0;
    size_t prev = 0;
    while((pos = input.find(" ", prev)) != string::npos)
    {
        words.emplace_back(input.substr(prev, pos-prev));
        prev = pos+1;
    }
    words.emplace_back(input.substr(prev, input.size() - prev));

    for (const auto& word : words)
    {
        int vowelCount = 0;
        int consonantCount = 0;
        
        bool hasAVowel = false;
        for (auto v : vowels)
        {
            if (word.find(v) != string::npos)
            {
                hasAVowel = true;
                break;
            }
        }

        countVC(word, 0, vowelCount, consonantCount, !hasAVowel);
        totalVCount += vowelCount;
        totalCCount += consonantCount;
    }
    return totalVCount > totalCCount;
}

bool sameListDifferentCursorPosition(CircleList<int>& a, CircleList<int>& b)
{
    auto getSortedItems = [](auto& list)
    {
        set<int> items;
        auto start = list.frontNode();
        items.insert(start->elem);
        list.advance();
        while(list.frontNode() != start)
        {
            items.insert(list.front());
            list.advance();
        }
        return items;
    };

    auto aItems = getSortedItems(a);
    auto bItems = getSortedItems(b);

    if (aItems.size() != bItems.size())
    {
        return false;
    }

    auto aIter = aItems.begin();
    auto bIter = bItems.begin();
    for (auto i=0u; i<aItems.size(); i++)
    {
        if (*aIter != *bIter)
        {
            return false;
        }
        advance(aIter, 1);
        advance(bIter, 1);
    }

    return true;
}

Matrix3D::Matrix3D(int rows, int cols, int depth)
    : data(depth, vector<vector<int>>(rows, vector<int>(cols, 0)))
{
}

Matrix3D::Dimensions Matrix3D::getDimensions() const
{
    Dimensions result;
    result.depth = static_cast<int>(data.size());
    if (data.empty())
    {
        return result;
    }

    result.rows = static_cast<int>(data.front().size());
    if (data.front().empty())
    {
        return result;
    }

    result.cols = static_cast<int>(data.front().front().size());
    return result;
}

bool operator==(const Matrix3D::Dimensions& left, const Matrix3D::Dimensions& right)
{
    return left.depth == right.depth 
        && left.rows == right.rows 
        && left.cols == right.cols;
}

Matrix3D add(const Matrix3D& a, const Matrix3D& b)
{
    if (!(a.getDimensions() == b.getDimensions()))
    {
        throw runtime_error("cannot add Matrices of different sizes");
    }

    auto dims = a.getDimensions();
    Matrix3D result(dims.rows, dims.cols, dims.depth);

    for (auto d = 0; d < dims.depth; d++)
    {
        for (auto r = 0; r < dims.rows; r++)
        {
            for (auto c = 0; c < dims.cols; c++)
            {
                result.data[d][r][c] = a.data[d][r][c] + b.data[d][r][c];
            }
        }
    }

    return result;
}

Matrix2D::Matrix2D(int rows, int cols)
    : data(rows, vector<int>(cols, 0))
{
}

Matrix2D::Dimensions Matrix2D::getDimensions() const
{
    Dimensions result;
    result.rows = static_cast<int>(data.size());
    if (data.empty())
    {
        return result;
    }

    result.cols = static_cast<int>(data.front().size());
    return result;
}


bool operator==(const Matrix2D::Dimensions& left, const Matrix2D::Dimensions& right)
{
    return left.rows == right.rows
        && left.cols == right.cols;
}

Matrix2D operator*(const Matrix2D& left, const Matrix2D& right)
{
    auto leftDims = left.getDimensions();
    auto rightDims = right.getDimensions();
    if (leftDims.cols != rightDims.rows)
    {
        throw runtime_error("can't multiply matrices unless left cols == right rows");
    }

    Matrix2D result(leftDims.rows, rightDims.cols);

    for (auto i=0; i<leftDims.rows; i++)
    {
        for (auto j=0; j<rightDims.cols; j++)
        {
            int dotProduct = 0;
            for (auto elem=0; elem<leftDims.cols; elem++)
            {
                dotProduct += left.data[i][elem] * right.data[elem][j];
            }
            result.data[i][j] = dotProduct;
        }
    }

    return result;
}

Matrix2D operator+(const Matrix2D& left, const Matrix2D& right)
{
    auto leftDims = left.getDimensions();
    auto rightDims = right.getDimensions();

    if (!(leftDims == rightDims))
    {
        throw runtime_error("can't add matrices that have different dimensions");
    }

    Matrix2D result(leftDims.rows, leftDims.cols);
    for (auto i = 0; i < leftDims.rows; i++)
    {
        for (auto j = 0; j < leftDims.cols; j++)
        {
            result.data[i][j] = left.data[i][j] + right.data[i][j];
        }
    }
    return result;
}

SummationPuzzle::SummationPuzzle(const string& addLeft, const string& addRight, const string& equals)
    : m_addLeft(addLeft), m_addRight(addRight), m_equals(equals)
    , m_unused({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
    , m_numUniqueChars([&] () {
        int idx = 0;
        unordered_set<char> uniqueChars;
        string allWords = addLeft + addRight + equals;
        for (char c : allWords)
        {
            if (!uniqueChars.count(c))
            {
                m_letterIndexMap[c] = idx;
                idx++;
                uniqueChars.insert(c);
            }
        }
        return uniqueChars.size();
    }())
    , m_leftWord(m_addLeft.size(), 0)
    , m_rightWord(m_addRight.size(), 0)
    , m_equalsWord(m_equals.size(), 0)
{
    cout << "the puzzle is " << addLeft << " + " << addRight << " = " << equals << endl;
    cout << "there are " << m_numUniqueChars << " unique characters" << endl;
}

int SummationPuzzle::combine(const vector<int>& digits)
{
    auto coefficient = 1;
    int result = 0;
    for (auto digitIter = digits.rbegin(); digitIter<digits.rend(); digitIter++)
    {
        result += coefficient * (*digitIter);
        coefficient *= 10;
    }

    return result;
}

bool SummationPuzzle::trySolution(const vector<int>& used)
{
    if (used.size() != m_numUniqueChars)
    {
        throw runtime_error("invalid call to trySolution. Used set is wrong size");
    }

    int index = 0;
    for (auto c : m_addLeft)
    {
        m_leftWord[index++] = used[m_letterIndexMap[c]];
    }

    index = 0;
    for (auto c : m_addRight)
    {
        m_rightWord[index++] = used[m_letterIndexMap[c]];
    }

    index = 0;
    for (auto c : m_equals)
    {
        m_equalsWord[index++] = used[m_letterIndexMap[c]];
    }

    auto solved = combine(m_leftWord) + combine(m_rightWord) == combine(m_equalsWord);
    if (solved)
    {
        cout << "* Puzzle solved! *" << endl;
        cout << "leftWord in numbers is " << combine(m_leftWord) << endl;
        cout << "rightWord in numbers is " << combine(m_rightWord) << endl;
        cout << "equals in numbers is " << combine(m_equalsWord) << endl;
    }
    return solved;
}

void SummationPuzzle::solveInternal()
{
    for (auto i=0u; i<m_unused.size(); i++)
    {
        auto iter = m_unused.begin();
        advance(iter, i);
        auto item = *iter;
        m_unused.erase(iter);
        m_used.push_back(item);

        if(m_used.size() == m_numUniqueChars)
        {
            if (m_solved |= trySolution(m_used))
            {
                return;
            }
        }

        if (!m_solved)
        {
            solveInternal();
            m_unused.insert(item);
            m_used.pop_back();
        }
    }
}

bool SummationPuzzle::solve()
{
    solveInternal();
    return m_solved;
}

Cipher::Cipher()
{
        deque<char> alpha; // easier to remove a middle element
        for (const auto& c : g_alphabet)
        {
            alpha.push_back(c);
        }

        for (const auto& c : g_alphabet)
        {
            auto randomIndex = m_rng.getNumber(0, static_cast<int>(alpha.size()-1));
            auto randomChar = alpha[randomIndex];
            alpha.erase(alpha.begin() + randomIndex);

            m_encryptionMap[c] = randomChar;
            m_decryptionMap[randomChar] = c;
        }
}

string Cipher::encrypt(const string& message)
{
    string encrypted;
    for (const auto& c : message)
    {
        if (g_alphabet.find(c) == string::npos)
        {
            encrypted += c;
        }
        else
        {
            encrypted += m_encryptionMap[c];
        }
    }
    return encrypted;
}

string Cipher::decrypt(const string& message)
{
    string decrypted;
    for (const auto& c : message)
    {
        if (g_alphabet.find(c) == string::npos)
        {
            decrypted += c;
        }
        else
        {
            decrypted += m_decryptionMap[c];
        }
    }
    return decrypted;
}
