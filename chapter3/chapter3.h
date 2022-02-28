#include <array>
#include <functional>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>

class GameEntry {
public:
    GameEntry(const std::string& n="", int s=0);
    std::string getName() const;
    int getScore() const;

	using ScoreCompare = std::function<bool(const GameEntry& a, const GameEntry& b)>;
	static bool chooseLarger(const GameEntry& a, const GameEntry& b)
	{
		return a.score > b.score;
	}
private:
    std::string name;
    int score{};
};

class Scores {
public:
    Scores(int maxEnt = 10);

    void add(const GameEntry& e);
    GameEntry remove(int i);
    GameEntry at(int i) const;
    int numScores() const; 
    int maxEntriesPerPlayer() const;
private:
    bool hasMaxEntries(const GameEntry& e) const;
    int maxEntries{};
    std::set<GameEntry, GameEntry::ScoreCompare> entries;
};

using Matrix = std::vector<std::vector<float>>;

void transpose(Matrix& matrix);

float recursiveSum(const Matrix& matrix);

class StringNode {
public:
    std::string element() const
    {
        return elem;
    }
private:
    std::string elem;
    StringNode* next;

    friend class StringLinkedList;
};

class StringLinkedList {
public:
    StringLinkedList();
    ~StringLinkedList();

    bool empty();
    const std::string& front() const;
    void addFront(const std::string& e);
    void removeFront();
    // returns a pointer to the second to last node
    StringNode* penultimate();
    void reverseRecursive();
    void reverse();
    void print();
    size_t size();
    // C-3.14
    size_t countNodes();

    void concatenate(StringLinkedList& toConsume);
    void swapNodes(const std::string& a, const std::string& b);
private:
    void reverseNodesInternal(StringNode* prev, StringNode* node);
    void swapNodesInternal(StringNode* a, StringNode* b);
    // C-3.14
    size_t countNodesInternal(StringNode* node);
    StringNode* head;
    size_t numElements = 0;
};

void recursivelyDefineList(StringLinkedList& list, const std::vector<std::string>& items);

template<typename T>
class DNode {
private:
    T elem{};
    DNode<T>* prev = nullptr;
    DNode<T>* next = nullptr;

    template<typename U>
    friend class DLinkedList;
};

template<typename T>
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    size_t size() const;
    const T& front() const;
    DNode<T>* frontNode();
    DNode<T>* backNode();
    const T& back() const;
    void addFront(const T& e);
    void addBack(const T& e);
    void removeFront();
    void removeBack();

    // the runtime for this function is list size / 2
    T middleElement();
    // assumes that a and b belong to this list and they are in front-to-back order
    void swapNodes(DNode<T>* a, DNode<T>* b);
    void concatenate(DLinkedList<T>& toConsume);
private:
    DNode<T>* header = nullptr;
    DNode<T>* trailer = nullptr;
    void add(DNode<T>* v, const T& e);
    void remove(DNode<T>* v);
    size_t m_size = 0;
};

template<typename T>
DLinkedList<T>::DLinkedList()
{
    header = new DNode<T>;
    trailer = new DNode<T>;
    header->next = trailer;
    trailer->prev = header;
}

template<typename T>
DLinkedList<T>::~DLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
    delete header;
    delete trailer;
}

template<typename T>
bool DLinkedList<T>::empty() const
{
    return header->next == trailer;
}

template<typename T>
size_t DLinkedList<T>::size() const
{
    return m_size;
}

template<typename T>
const T& DLinkedList<T>::front() const
{
    if (empty())
    {
        throw runtime_error("tried to get front element of an empty list");
    }
    return header->next->elem;
}

template<typename T>
DNode<T>* DLinkedList<T>::frontNode()
{
    if (empty())
    {
        throw runtime_error("tried to get front element of an empty list");
    }
    return header->next;
}

template<typename T>
const T& DLinkedList<T>::back() const
{
    if (empty())
    {
        throw runtime_error("tried to get back element of an empty list");
    }
    return trailer->prev->elem;
}

template<typename T>
DNode<T>* DLinkedList<T>::backNode()
{
    if (empty())
    {
        throw runtime_error("tried to get front element of an empty list");
    }
    return trailer->prev;
}

template<typename T>
void DLinkedList<T>::add(DNode<T>* nextNode, const T& e)
{
    DNode<T>* insert = new DNode<T>;
    insert->elem = e;
    insert->next = nextNode;
    insert->prev = nextNode->prev;

    nextNode->prev->next = insert;
    nextNode->prev = insert;
    m_size++;
}

template<typename T>
void DLinkedList<T>::addFront(const T& e)
{
    add(header->next, e);
}

template<typename T>
void DLinkedList<T>::addBack(const T& e)
{
    add(trailer, e);
}

template<typename T>
void DLinkedList<T>::remove(DNode<T>* toRemove)
{
    DNode<T>* beforeRemove = toRemove->prev;
    DNode<T>* afterRemove = toRemove->next;
    beforeRemove->next = afterRemove;
    afterRemove->prev = beforeRemove;
    delete toRemove;
    m_size--;
}

template<typename T>
void DLinkedList<T>::removeFront()
{
    if (empty())
    {
        throw runtime_error("tried to remove front from an empty list");
    }
    remove(header->next);
}

template<typename T>
void DLinkedList<T>::removeBack()
{
    if (empty())
    {
        throw runtime_error("tried to remove back from an empty list");
    }
    remove(trailer->prev);
}

template<typename T>
T DLinkedList<T>::middleElement()
{
    if (empty())
    {
        throw runtime_error("there is no middle element for an empty list");
    }

    DNode<T>* back = trailer->prev;
    DNode<T>* front = header->next;

    while (back != front)
    {
        front = front->next;
        if (back == front)
        {
            // case for list of even number size
            return front->elem;
        }
        back = back->prev;
    }
    return front->elem;
}

template<typename T>
void DLinkedList<T>::swapNodes(DNode<T>* a, DNode<T>* b)
{
    if (a == b)
    {
       return; 
    }

    auto aPrev = a->prev;
    auto aNext = a->next;
    auto bPrev = b->prev;
    auto bNext = b->next;

    if (a->next == b)
    {
        aPrev->next = b;
        b->prev = aPrev;
        bNext->prev = a;
        a->next = bNext;

        b->next = a;
        a->prev = b;
    }
    else
    {
        aPrev->next = b;
        b->prev = aPrev;
        b->next = aNext;
        aNext->prev = b;

        bPrev->next = a;
        a->prev = bPrev;
        a->next = bNext;
        bNext->prev = a;
    }
}

template<typename T>
void DLinkedList<T>::concatenate(DLinkedList<T>& toConsume)
{
    auto firstNewNode = toConsume.header->next;
    auto lastNewNode = toConsume.trailer->prev;
    auto lastOriginalNode = trailer->prev;

    lastOriginalNode->next = firstNewNode;
    firstNewNode->prev = lastOriginalNode;

    trailer->prev = lastNewNode;
    lastNewNode->next = trailer;

    toConsume.header->next = toConsume.trailer;
    toConsume.trailer->prev = toConsume.header;
}

int findArrayMaximum(const std::vector<int>& array);

void removeRandomUntilEmpty(std::vector<int>& array);

template<typename T>
class CNode {
private:
    T elem{};
    CNode<T>* next = nullptr;

    template<typename U>
    friend class CircleList;
};

template<typename T>
class CircleList {
public:
    CircleList() = default;
    ~CircleList()
    {
        while(!empty())
        {
            remove();
        }
    }

    bool empty()
    {
        return cursor == nullptr;
    }

    const T& front()
    {
        return cursor->next->elem;
    }

    const T& back()
    {
        return cursor->elem;
    }

    void advance()
    {
        if (empty())
        {
            throw runtime_error("cannot advance an empty list");
        }

        cursor = cursor->next;
    }

    void add(const T& e)
    {
        auto newNode = new CNode<T>;
        newNode->elem = e;
        if (empty())
        {
            newNode->next = newNode;
            cursor = newNode;
        }
        newNode->next = cursor->next;
        cursor->next = newNode;
    }

    void remove()
    {
        if (empty())
        {
            throw runtime_error("cannot remove from an empty list");
        }

        CNode<T>* toRemove = cursor->next;
        if (toRemove == cursor)
        {
            cursor = nullptr;
        }
        else
        {
            cursor->next = toRemove->next;
        }
        delete toRemove;
    }

    size_t count()
    {
        if (empty())
        {
            return 0;
        }

        auto index = cursor;
        size_t count = 1;
        while((index = index->next) != cursor)
        {
            count++;
        }
        return count;
    }
private:
    CNode<T>* cursor = nullptr;
};

class TicTacToe {
public:
    TicTacToe() = default;
    ~TicTacToe() = default;

    void clearBoard();

    void putMark(int i, int j);

    int getWinner();

    void printBoard();

    const int X = 1;
    const int O = 4;
    const int Empty = 0;

private:
    bool isWin(int mark);

    std::array<std::array<int, 3>, 3> m_board{};
    int m_currentPlayer{};
};

bool findRepeat(const std::vector<int>& input, int& repeatedItem, int numOccurances);

class EnchantedForest {
public:
    EnchantedForest() = default;
    ~EnchantedForest() = default;
    
    void meet(int i, int j);
    bool gameOver();

    const std::vector<int>& winners();
private:
    std::unordered_map<int, std::unordered_set<int>> m_trackMeetings;
    std::vector<int> m_winners;
    bool m_gameFinished = false;
};

uint32_t recursiveProduct(uint32_t m, uint32_t n);

void reverseSLinkedList(StringLinkedList& list);

class TowersOfHanoi {
public:
    TowersOfHanoi(uint32_t numDisks);
    TowersOfHanoi() = delete;
    ~TowersOfHanoi() = default;

    void print();
    void solve();
    bool isSolved();
private:
    void solveInternal(int n, int start, int dest, int temp);
    void move(int fromPeg, int destPeg);

    int m_numDisks{};
    std::array<std::vector<int>, 3> pegs;
};

int stringToDigits(const std::string& number);
