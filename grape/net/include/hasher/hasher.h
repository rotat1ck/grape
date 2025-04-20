#ifndef TOHASH_H
#define TOHASH_H

#include <string>

class toHash {
private:
    static std::string _msg;
public:
    static std::string hash(std::string msg);
};

#endif // TOHASH_H
