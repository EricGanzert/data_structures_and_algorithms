#include <string>

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
    ~Scores();

    void add(const GameEntry& e);
    GameEntry remove(int i);
private:
    int maxEntries;
    int numEntries;
    GameEntry* entries;
};