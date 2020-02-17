#include <iostream>
#include <vector>
using namespace std;

enum class SpellName {
    LESSER_HEAL_R1 = 0,
    LESSER_HEAL_R2,
    LESSER_HEAL_R3,
    HEAL_R1,
    HEAL_R2,
    HEAL_R3,
    HEAL_R4,
    GREATER_HEA_R1,
    GREATER_HEA_R2,
    GREATER_HEA_R3,
    GREATER_HEA_R4,
    FLASH_HEAL_R1,
    FLASH_HEAL_R2,
    FLASH_HEAL_R3,
    FLASH_HEAL_R4,
    FLASH_HEAL_R5,
    FLASH_HEAL_R6,
    FLASH_HEAL_R7
};

class Spell {

private:
    string _spellName;
    int _rank;
    int _level;
    double _baseCastTime;
    double _baseManaCost;
    double _baseHealing;

public:
    Spell():_spellName(""),_rank(0),_level(0),_baseCastTime(0.0),_baseManaCost(0.0),_baseHealing(0.0) {}
    Spell(const string& spell_name, int spell_rank, int level, double base_cast_time, double base_mana_cost, double base_healing):
        _spellName(spell_name),_rank(spell_rank),_level(level),_baseCastTime(base_cast_time),_baseManaCost(base_mana_cost),_baseHealing(base_healing) 
        {}

    friend ostream & operator << (ostream& out, const Spell& spell);
};

ostream & operator << (ostream& out, const Spell& spell) {
    cout << spell._spellName;
    return out;
}

class SpellBook {

private:
    vector<Spell> _spellBook;

public:
    SpellBook() {
        // Initialize base priest spells
        _spellBook.emplace_back("Lesser Heal (Rank 1)", 1, 1, 1.5, 30.0, 53.0);
        _spellBook.emplace_back("Lesser Heal (Rank 2)", 2, 4, 2.0, 45.0, 84.0);
        _spellBook.emplace_back("Lesser Heal (Rank 3)", 3, 10, 2.5, 75.0, 154.0);
        _spellBook.emplace_back("Heal (Rank 1)", 1, 16, 3.0, 155.0, 330.0);
        _spellBook.emplace_back("Heal (Rank 2)", 2, 22, 3.0, 205.0, 476.0);
        _spellBook.emplace_back("Heal (Rank 3)", 3, 28, 3.0, 255.0, 624.0);
        _spellBook.emplace_back("Heal (Rank 4)", 4, 34, 3.0, 305.0, 781.0);
        _spellBook.emplace_back("Greater Heal (Rank 1)", 1, 40, 3.0, 370.0, 982.0);
        _spellBook.emplace_back("Greater Heal (Rank 2)", 2, 46, 3.0, 455.0, 1248.0);
        _spellBook.emplace_back("Greater Heal (Rank 3)", 3, 52, 3.0, 545.0, 1556.0);
        _spellBook.emplace_back("Greater Heal (Rank 4)", 4, 60, 3.0, 655.0, 1917.0);
        _spellBook.emplace_back("Flash Heal (Rank 1)", 1, 20, 1.5, 125.0, 225.0);
        _spellBook.emplace_back("Flash Heal (Rank 2)", 2, 26, 1.5, 155.0, 297.0);
        _spellBook.emplace_back("Flash Heal (Rank 3)", 3, 32, 1.5, 185.0, 373.0);
        _spellBook.emplace_back("Flash Heal (Rank 4)", 4, 38, 1.5, 215.0, 453.0);
        _spellBook.emplace_back("Flash Heal (Rank 5)", 5, 44, 1.5, 265.0, 584.0);
        _spellBook.emplace_back("Flash Heal (Rank 6)", 6, 50, 1.5, 315.0, 723.0);
        _spellBook.emplace_back("Flash Heal (Rank 7)", 7, 56, 1.5, 380.0, 902.0);  
    }

    inline Spell getSpell(const SpellName spell_name) const { return( _spellBook[static_cast<int>(spell_name)] ); };

};

enum class ItemSlot {
    HEAD = 0,
    NECK,
    SHOULDERS,
    BACK,
    CHEST,
    WRISTS,
    TWO_HAND,
    MAIN_HAND,
    OFF_HAND,
    WAND,
    HANDS,
    WAIST,
    LEGS,
    FEET,
    FINGER_1,
    FINGER_2,
    TRINKET_1,
    TRINKET_2
};

class Item {

private:
    ItemSlot _itemSlot;
    string _itemName;
    string _source;
    double _dropChance;
    bool _unique;
    int _tier;
    int _healingPower;
    int _intellect;
    int _spirit;
    int _mp5;
    int _mana;
    double _spellCrit;
    bool _owned;

public:
    Item():_itemSlot(ItemSlot::HEAD),_itemName("None"),_source(""),_dropChance(1.0),_unique(true),_tier(0),
        _healingPower(0),_intellect(0),_spirit(0),_mp5(0),_mana(0),_spellCrit(0.0),_owned(true) {}
    Item(const ItemSlot item_slot, const string& item_name, const string& source, double drop_chance, bool unique, int tier, 
        int healing_power, int intellect, int spirit, int mp5, int mana, double spell_crit, bool owned):
        _itemSlot(item_slot),_itemName(item_name),_source(source),_dropChance(drop_chance),_unique(unique),_tier(tier),
        _healingPower(healing_power),_intellect(intellect),_spirit(spirit),_mp5(mp5),_mana(mana),_spellCrit(spell_crit),_owned(owned) 
        {};

    friend ostream & operator << (ostream &out, const Spell &spell);
};

int main() {
    // Initialize SpellBook
    SpellBook spell_book;

    // Initialize GearDatabase
  
    
    cout << "Hello World!\n";
    cout << spell_book.getSpell(SpellName::FLASH_HEAL_R3);


  
  
  
  return 0;
} 

// void ReadGearData



