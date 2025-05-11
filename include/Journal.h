#ifndef JOURNAL_H
#define JOURNAL_H

#include <vector>
#include <string>

class Journal {
private:
    std::vector<std::string> entries;
public:
    void addEntry(std::string entry);
};

#endif
