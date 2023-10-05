#ifndef TESTCLASSPLAYER
#define TESTCLASSPLAYER

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
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

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version) {
            //ar & name;
            ar & level;
            ar & hp;
            ar & armor;
            ar & drip;
            ar & c;
            ar & array;
        }
};

#endif
