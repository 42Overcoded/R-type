
#ifndef TESTCLASSPLAYER
#define TESTCLASSPLAYER

#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

class testPlayer {
    public:
        const char *name;
        std::string level;
        int hp;
        int armor;
        bool drip;
        char c;
        char array[30];
        testPlayer();
        ~testPlayer();

        // https://www.boost.org/doc/libs/1_32_0/libs/serialization/doc/special.html#derivedpointers
        friend class boost::serialization::access;
        //...
        // only required when using method 1 below
        // no real serialization required - specify a vestigial one
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version){}

};

#endif
