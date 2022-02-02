#include <string>
#include <vector>

class GameEntry {
public:
    GameEntry(const std::string& n="", int s=0);
    std::string getName() const;
    int getScore() const;
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
    int maxEntries;
    int numEntries;
    std::vector<GameEntry> entries;
};

using Matrix = std::vector<std::vector<float>>;

void transpose(Matrix& matrix);

float recursiveSum(const Matrix& matrix);

class StringNode {
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
private:
    StringNode* head;
};

void recursivelyDefineList(StringLinkedList& list, const std::vector<std::string>& items);
