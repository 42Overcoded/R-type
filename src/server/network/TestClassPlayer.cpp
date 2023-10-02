#include "TestClassPlayer.hpp"
#include <cstring>

testPlayer::testPlayer()
{
    hp = 84;
    armor = 199;
    name = "pas marché";
    level = "toto";
    drip = false;
    c = 'w';
    strcpy(array, "val par défaut");
}

testPlayer::~testPlayer()
{

}
