#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <tuple>
#include <chrono>

using namespace std;

enum class ItemSlot {
    HEAD = 0,
    NECK,
    SHOULDERS,
    BACK,
    CHEST,
    WRISTS,
    WEAPON_2H,
    WEAPON_MH,
    WEAPON_OH,
    WAND,
    HANDS,
    WAIST,
    LEGS,
    FEET,
    FINGER,
    TRINKET
};

ostream & operator << (ostream& out, const ItemSlot& item_slot) {
    int i = static_cast<int>(item_slot);
    if (i == 0) {
        std::cout << "Head";
    } else if (i == 1) {
        std::cout << "Neck";
    } else if (i == 2) {
        std::cout << "Shoulders";
    } else if (i == 3) {
        std::cout << "Back";
    } else if (i == 4) {
        std::cout << "Chest";
    } else if (i == 5) {
        std::cout << "Wrists";
    } else if (i == 6) {
        std::cout << "Weapon (2H)";
    } else if (i == 7) {
        std::cout << "Weapon (MH)";
    } else if (i == 8) {
        std::cout << "Weapon (OH)";
    } else if (i == 9) {
        std::cout << "Wand";
    } else if (i == 10) {
        std::cout << "Hands";
    } else if (i == 11) {
        std::cout << "Waist";
    } else if (i == 12) {
        std::cout << "Legs";
    } else if (i == 13) {
        std::cout << "Feet";
    } else if (i == 14) {
        std::cout << "Finger";
    } else if (i == 15) {
        std::cout << "Trinket";
    } else {
        std::cout << "ERROR";
    } 
    return out;
}

class Item {

private:
    const int _ID;
    const ItemSlot _itemSlot;
    const string _itemName;
    const string _source;
    const double _dropChance;
    const bool _unique;
    const int _tier;
    const double _healingPower;
    const double _intellect;
    const double _spirit;
    const double _mp5;
    const double _mana;
    const double _spellCrit;
    const bool _available;

public:
    Item():
        _ID(0),
        _itemSlot(ItemSlot::HEAD),
        _itemName("None"),
        _source(""),
        _dropChance(1.0),
        _unique(true),
        _tier(0),
        _healingPower(0.0),
        _intellect(0.0),
        _spirit(0.0),
        _mp5(0.0),
        _mana(0.0),
        _spellCrit(0.0),
        _available(true) 
        {};
    Item(int id, ItemSlot item_slot):
        _ID(id),
        _itemSlot(item_slot),
        _itemName("None"),
        _source(""),
        _dropChance(1.0),
        _unique(true),
        _tier(0),
        _healingPower(0.0),
        _intellect(0.0),
        _spirit(0.0),
        _mp5(0.0),
        _mana(0.0),
        _spellCrit(0.0),
        _available(true) 
        {};
    Item(int id, ItemSlot item_slot, const string& item_name, const string& source, double drop_chance, bool unique, int tier, 
        double healing_power, double intellect, double spirit, double mp5, double mana, double spell_crit, bool available):
        _ID(id),
        _itemSlot(item_slot),
        _itemName(item_name),
        _source(source),
        _dropChance(drop_chance),
        _unique(unique),
        _tier(tier),
        _healingPower(healing_power),
        _intellect(intellect),
        _spirit(spirit),
        _mp5(mp5),
        _mana(mana),
        _spellCrit(spell_crit),
        _available(available) 
        {};

    inline int getID() const { return(_ID); };
    inline ItemSlot getSlot() const { return(_itemSlot); };
    inline string getName() const { return(_itemName); };
    inline string getSource() const { return(_source); };
    inline double getDropChance() const { return(_dropChance); };
    inline bool getUnique() const { return(_unique); };
    inline int getTier() const { return(_tier); };
    inline double getHealingPower() const { return(_healingPower); };
    inline double getIntellect() const { return(_intellect); };
    inline double getSpirit() const { return(_spirit); };
    inline double getMp5() const { return(_mp5); };
    inline double getMana() const { return(_mana); };
    inline double getSpellCrit() const { return(_spellCrit); };
    inline bool getAvailable() const { return(_available); };

    void PrintDetails(bool verbose) const {
        std::cout << _itemSlot << std::endl;
        std::cout << "\t" << _itemName << std::endl;
        if (verbose) {
            std::cout << "\tID: " << _ID << std::endl;
            std::cout << "\tSource: " << _source << std::endl;
            std::cout << "\tDrop Chance: " << _dropChance*100.0 << "%" << std::endl;
            std::cout << "\tUnique: ";
            if (_unique) std::cout << "TRUE" << std::endl;
            else std::cout << "FALSE" << std::endl;
            std::cout << "\tTier: " << _tier << std::endl;
            std::cout << "\tHealing Power: " << _healingPower << std::endl;
            std::cout << "\tIntellect: " << _intellect << std::endl;
            std::cout << "\tSpirit: " << _spirit << std::endl;
            std::cout << "\tMp5: " << _mp5 << std::endl;
            std::cout << "\tMana: " << _mana << std::endl;
            std::cout << "\tSpell Crit: " << _spellCrit*100.0 << "%" << std::endl;
            std::cout << "\tAvailable: ";
            if (_available) std::cout << "TRUE" << std::endl;
            else std::cout << "FALSE" << std::endl;
        }
        return;
    }
};

inline bool StringToBool(const string& str) {
    bool out = false;
    if ( (str.compare("TRUE") == 0) || (str.compare("TRUE\n") == 0) || (str.compare("TRUE\r") == 0) ) out = true;
    else if ( (str.compare("FALSE") == 0) || (str.compare("FALSE\r") == 0) || (str.compare("FALSE\r") == 0) ) out = false;

    return out; 
};

class GearDatabase {

private:
    bool _valid;
    vector<Item> _head;
    vector<Item> _neck;
    vector<Item> _shoulders;
    vector<Item> _back;
    vector<Item> _chest;
    vector<Item> _wrists;
    vector<Item> _weapon_2H;
    vector<Item> _weapon_MH;
    vector<Item> _weapon_OH;
    vector<Item> _wand;
    vector<Item> _hands;
    vector<Item> _waist;
    vector<Item> _legs;
    vector<Item> _feet;
    vector<Item> _finger;
    vector<Item> _trinket;

public:

    GearDatabase(): _valid(false) {};
    GearDatabase(bool debug) {
        // Read data from CSV
        _valid = Read_CSV(debug);
    };

    inline bool getValidity() const { return(_valid); };
    inline Item getHeadItem(int idx) const { return(_head[idx]); };
    inline int getHeadSize() const { return(_head.size()); };
    inline Item getNeckItem(int idx) const { return(_neck[idx]); };
    inline int getNeckSize() const { return(_neck.size()); };
    inline Item getShouldersItem(int idx) const { return(_shoulders[idx]); };
    inline int getShouldersSize() const { return(_shoulders.size()); };
    inline Item getBackItem(int idx) const { return(_back[idx]); };
    inline int getBackSize() const { return(_back.size()); };
    inline Item getChestItem(int idx) const { return(_chest[idx]); };
    inline int getChestSize() const { return(_chest.size()); };
    inline Item getWristsItem(int idx) const { return(_wrists[idx]); };
    inline int getWristsSize() const { return(_wrists.size()); };
    inline Item getWeapon2HItem(int idx) const { return(_weapon_2H[idx]); };
    inline int getWeapon2HSize() const { return(_weapon_2H.size()); };
    inline Item getWeaponMHItem(int idx) const { return(_weapon_MH[idx]); };
    inline int getWeaponMHSize() const { return(_weapon_MH.size()); };
    inline Item getWeaponOHItem(int idx) const { return(_weapon_OH[idx]); };
    inline int getWeaponOHSize() const { return(_weapon_OH.size()); };
    inline Item getWandItem(int idx) const { return(_wand[idx]); };
    inline int getWandSize() const { return(_wand.size()); };
    inline Item getHandsItem(int idx) const { return(_hands[idx]); };
    inline int getHandsSize() const { return(_hands.size()); };
    inline Item getWaistItem(int idx) const { return(_waist[idx]); };
    inline int getWaistSize() const { return(_waist.size()); };
    inline Item getLegsItem(int idx) const { return(_legs[idx]); };
    inline int getLegsSize() const { return(_legs.size()); };
    inline Item getFeetItem(int idx) const { return(_feet[idx]); };
    inline int getFeetSize() const { return(_feet.size()); };
    inline Item getFingerItem(int idx) const { return(_finger[idx]); };
    inline int getFingerSize() const { return(_finger.size()); };
    inline Item getTrinketItem(int idx) const { return(_trinket[idx]); };
    inline int getTrinketSize() const { return(_trinket.size()); };

    void PrintDetails() const {
        // Print sum of items
        int head_size, neck_size, shoulders_size, back_size, chest_size, wrists_size, weapon_2h_size, weapon_mh_size, weapon_oh_size, wand_size, hands_size, waist_size, legs_size, feet_size, finger_size, trinket_size;
        head_size = _head.size();
        neck_size = _neck.size();
        shoulders_size = _shoulders.size();
        back_size = _back.size();
        chest_size = _chest.size();
        wrists_size = _wrists.size();
        weapon_2h_size = _weapon_2H.size();
        weapon_mh_size = _weapon_MH.size();
        weapon_oh_size = _weapon_OH.size();
        wand_size = _wand.size();
        hands_size = _hands.size();
        waist_size = _waist.size();
        legs_size = _legs.size();
        feet_size = _feet.size();
        finger_size = _finger.size();
        trinket_size = _trinket.size();
        int sum_size = head_size + neck_size + shoulders_size + back_size + chest_size + wrists_size + weapon_2h_size + weapon_mh_size + weapon_oh_size + wand_size + hands_size + waist_size + legs_size + feet_size + finger_size + trinket_size;

        std::cout << "GearDatabase Details:" << std::endl;
        std::cout << "\tAll Items: " << sum_size << std::endl;
        std::cout << "\tHead Items: " << head_size << std::endl;
        std::cout << "\tNeck Items: " << neck_size << std::endl;
        std::cout << "\tShoulders Items: " << shoulders_size << std::endl;
        std::cout << "\tBack Items: " << back_size << std::endl;
        std::cout << "\tChest Items: " << chest_size << std::endl;
        std::cout << "\tWrists Items: " << wrists_size << std::endl;
        std::cout << "\tWeapon (2H) Items: " << weapon_2h_size << std::endl;
        std::cout << "\tWeapon (MH) Items: " << weapon_mh_size << std::endl;
        std::cout << "\tWeapon (OH) Items: " << weapon_oh_size << std::endl;
        std::cout << "\tWand Items: " << wand_size << std::endl;
        std::cout << "\tHands Items: " << hands_size << std::endl;
        std::cout << "\tWaist Items: " << waist_size << std::endl;
        std::cout << "\tLegs Items: " << legs_size << std::endl;
        std::cout << "\tFeet Items: " << feet_size << std::endl;
        std::cout << "\tFinger Items: " << finger_size << std::endl;
        std::cout << "\tTrinket Items: " << trinket_size << std::endl;
        return;
    }

    bool Read_CSV(bool debug) {
        // Read data from CSV
        // Return validity

        ifstream file ( "../data/gear.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
        if (!file.good()) {
            std::cout << "Bad gear data file path!" << std::endl;
            return false;
        }

        // Add "None" item for weapons
        _weapon_2H.emplace_back(-1, ItemSlot::WEAPON_2H);
        _weapon_MH.emplace_back(-1, ItemSlot::WEAPON_MH);
        _weapon_OH.emplace_back(-1, ItemSlot::WEAPON_OH);   
           
        // Skip first line   
        string line; 
        std::getline(file, line);
        if (debug) std::cout << line << std::endl;

        // Read data (by line)
        while ( std::getline(file, line) )
        {
            if (debug) std::cout << line << std::endl;
            // Read data (by csv)
            int cnt_csv = 0;
            ItemSlot item_slot;
            string item_name, source;
            double drop_chance, healing_power, intellect, spirit, mp5, mana, spell_crit;
            bool unique, available;
            int tier, id; 
            std::istringstream str_str(line);
            std::string value;
            while (getline(str_str, value,',')) {
                switch (cnt_csv) {
                    case 0:
                        // Slot
                        if (value.compare("head") == 0) {
                            item_slot = ItemSlot::HEAD;
                            id = _head.size();
                        } else if (value.compare("neck") == 0) {
                            item_slot = ItemSlot::NECK;
                            id = _neck.size();
                        } else if (value.compare("shoulders") == 0) {
                            item_slot = ItemSlot::SHOULDERS;
                            id = _shoulders.size();
                        } else if (value.compare("back") == 0) {
                            item_slot = ItemSlot::BACK;
                            id = _back.size();
                        } else if (value.compare("chest") == 0) {
                            item_slot = ItemSlot::CHEST;
                            id = _chest.size();
                        } else if (value.compare("wrists") == 0) {
                            item_slot = ItemSlot::WRISTS;
                            id = _wrists.size();
                        } else if (value.compare("weapon 2H") == 0) {
                            item_slot = ItemSlot::WEAPON_2H;
                            id = _weapon_2H.size();
                        } else if (value.compare("weapon MH") == 0) {
                            item_slot = ItemSlot::WEAPON_MH;
                            id = _weapon_MH.size();
                        } else if (value.compare("weapon OH") == 0) {
                            item_slot = ItemSlot::WEAPON_OH;
                            id = _weapon_OH.size();
                        } else if (value.compare("wand") == 0) {
                            item_slot = ItemSlot::WAND;
                            id = _wand.size();
                        } else if (value.compare("hands") == 0) {
                            item_slot = ItemSlot::HANDS;
                            id = _hands.size();
                        } else if (value.compare("waist") == 0) {
                            item_slot = ItemSlot::WAIST;
                            id = _waist.size();
                        } else if (value.compare("legs") == 0) {
                            item_slot = ItemSlot::LEGS;
                            id = _legs.size();
                        } else if (value.compare("feet") == 0) {
                            item_slot = ItemSlot::FEET;
                            id = _feet.size();
                        } else if (value.compare("finger") == 0) {
                            item_slot = ItemSlot::FINGER;
                            id = _finger.size();
                        } else if (value.compare("trinket") == 0) {
                            item_slot = ItemSlot::TRINKET;
                            id = _trinket.size();
                        } else {
                            std::cout << "Wrong item slot type" << std::endl;
                            return false;
                        }
                        break;
                    case 1:
                        // Item Name
                        item_name = value;
                        break;
                    case 2:
                        // Source
                        source = value;
                        break;
                    case 3:
                        // Drop Chance
                        drop_chance = stod(value);
                        break;
                    case 4:
                        // Tier
                        tier = stoi(value);
                        break;
                    case 5:
                        // Healing Power
                        healing_power = stod(value);
                        break;
                    case 6:
                        // Intellect
                        intellect = stod(value);
                        break;
                    case 7:
                        // Spirit
                        spirit = stod(value);
                        break;
                    case 8:
                        // Mp5
                        mp5 = stod(value);
                        break;
                    case 9:
                        // Mana
                        mana = stod(value);
                        break;
                    case 10:
                        // Spell Crit
                        spell_crit = stod(value);
                        break;
                    case 11:
                        // Available
                        available = StringToBool(value);
                        break;
                    case 12:
                        // Unique
                        unique = StringToBool(value);
                        break;
                    default:
                        std::cout << "Malformed CSV" << std::endl;
                        return false;
                }
                ++cnt_csv;   
            } // Read data
            // Instantiate Item
            // Item(const ItemSlot item_slot, const string& item_name, const string& source, double drop_chance, bool unique, int tier, 
            // double healing_power, double intellect, double spirit, double mp5, double mana, double spell_crit, bool available)
            Item item(id, item_slot, item_name, source, drop_chance, unique, tier, healing_power, intellect, spirit, mp5, mana, spell_crit, available);
            if (debug) item.PrintDetails(true);
            // Store reference to item in correct list
            if (item_slot == ItemSlot::HEAD) {
                _head.emplace_back(item);
            } else if (item_slot == ItemSlot::NECK) {
                _neck.push_back(item);
            } else if (item_slot == ItemSlot::SHOULDERS) {
                _shoulders.push_back(item);
            } else if (item_slot == ItemSlot::BACK) {
                _back.push_back(item);
            } else if (item_slot == ItemSlot::CHEST) {
                _chest.push_back(item);
            } else if (item_slot == ItemSlot::WRISTS) {
                _wrists.push_back(item);
            } else if (item_slot == ItemSlot::WEAPON_2H) {
                _weapon_2H.push_back(item);
            } else if (item_slot == ItemSlot::WEAPON_MH) {
                _weapon_MH.push_back(item);
            } else if (item_slot == ItemSlot::WEAPON_OH) {
                _weapon_OH.push_back(item);
            } else if (item_slot == ItemSlot::WAND) {
                _wand.push_back(item);
            } else if (item_slot == ItemSlot::HANDS) {
                _hands.push_back(item);
            } else if (item_slot == ItemSlot::WAIST) {
                _waist.push_back(item);
            } else if (item_slot == ItemSlot::LEGS) {
                _legs.push_back(item);
            } else if (item_slot == ItemSlot::FEET) {
                _feet.push_back(item);
            } else if (item_slot == ItemSlot::FINGER) {
                _finger.push_back(item);
            } else if (item_slot == ItemSlot::TRINKET) {
                _trinket.push_back(item);
            } else {
                std::cout << "Wrong item slot type" << std::endl;
                return false;
            }
        } // Read by line     

        return(true);
    };
};

enum class Talents {
    IMPROVED_POWER_WORD_SHIELD = 0,
    MEDITATION,
    MENTAL_AGILITY,
    MENTAL_STRENGTH,
    IMPROVED_RENEW,
    HOLY_SPECIALIZATION,
    DIVINE_FURY,
    IMPROVED_HEALING,
    SPIRITUAL_GUIDANCE,
    SPIRITUAL_HEALING
};

class TalentTree {
private:
    vector<int> _talentTree;
    bool _valid;

public:
    TalentTree() {
        // Read talents.csv
        ifstream file ( "../data/talents.csv" );
        if (!file.good()) {
            std::cout << "Bad talents data file path!" << std::endl;
            _valid = false;
            return;
        } else {
            std::cout << "Reading Talents..." << std::endl;
        }
        string line;
        // Skip first line    
        getline(file, line);
        // Read data (by line)
        while ( getline(file, line) ) {
            // Read data (by csv)
            int cnt_csv = 0;
            istringstream str_str(line);
            string value;
            while (getline(str_str, value,',')) {
                if (cnt_csv == 0) {
                    ++cnt_csv;
                    continue;
                } else if (cnt_csv == 1) {
                    _talentTree.push_back(stoi(value));
                    ++cnt_csv;
                } else {
                    std::cout << "Malformed talents.csv" << std::endl;
                    _valid = false;
                    return;
                }                
            }
        }
    }

    inline int getPoints(Talents talent) const { return( _talentTree[static_cast<int>(talent)] ); };
    inline int getTalentTreeSize() const { return(_talentTree.size()); };

    void PrintDetails() const {
        std::cout << "TalentTree" << std::endl;
        std::cout << "\t=== Discipline ===" << std::endl;
        std::cout << "\tImproved Power Word: Shield: " << getPoints(Talents::IMPROVED_POWER_WORD_SHIELD) << " / 3" << std::endl;
        std::cout << "\tMeditation: " << getPoints(Talents::MEDITATION) << " / 3" << std::endl;
        std::cout << "\tMental Agility: " << getPoints(Talents::MENTAL_AGILITY) << " / 5" << std::endl;
        std::cout << "\tMental Strength: " << getPoints(Talents::MENTAL_STRENGTH) << " / 5" << std::endl;
        std::cout << "\t=== Holy ===" << std::endl;
        std::cout << "\tImproved Renew: " << getPoints(Talents::IMPROVED_RENEW) << " / 3" << std::endl;
        std::cout << "\tHoly Specialization: " << getPoints(Talents::HOLY_SPECIALIZATION) << " / 5" << std::endl;
        std::cout << "\tDivine Fury: " << getPoints(Talents::DIVINE_FURY) << " / 5" << std::endl;
        std::cout << "\tImproved Healing: " << getPoints(Talents::IMPROVED_HEALING) << " / 3" << std::endl;
        std::cout << "\tSpiritual Guidance: " << getPoints(Talents::SPIRITUAL_GUIDANCE) << " / 5" << std::endl;
        std::cout << "\tSpiritual Healing: " << getPoints(Talents::SPIRITUAL_HEALING) << " / 5" << std::endl;

        return;
    }
};

enum class SpellName {
    LESSER_HEAL = 0,
    HEAL,
    GREATER_HEAL,
    FLASH_HEAL,
    NONE
};

enum class MagicSchool {
    ARCANE = 0,
    FIRE,
    FROST,
    HOLY,
    NATURE,
    PHYSICAL,
    SHADOW
};

enum class SpellNameRank {
    LESSER_HEAL_R1 = 0,
    LESSER_HEAL_R2,
    LESSER_HEAL_R3,
    HEAL_R1,
    HEAL_R2,
    HEAL_R3,
    HEAL_R4,
    GREATER_HEAL_R1,
    GREATER_HEAL_R2,
    GREATER_HEAL_R3,
    GREATER_HEAL_R4,
    FLASH_HEAL_R1,
    FLASH_HEAL_R2,
    FLASH_HEAL_R3,
    FLASH_HEAL_R4,
    FLASH_HEAL_R5,
    FLASH_HEAL_R6,
    FLASH_HEAL_R7,
    NONE
};

class Spell {

private:
    SpellNameRank _spellNameRankEnum;
    SpellName _spellNameEnum;
    string _name;
    int _rank;
    MagicSchool _school;
    int _level;
    double _crit;
    double _baseCastTime;
    double _baseManaCost;
    double _baseHealing;
    double _effectiveCastTime;
    double _effectiveManaCost;
    double _effectiveHealing;
    double _HpS;
    double _HpM;
    double _MpS;

public:
    Spell():_spellNameRankEnum(SpellNameRank::NONE), _spellNameEnum(SpellName::NONE), _name(""), _rank(0),_school(MagicSchool::HOLY),_level(0),_crit(0.0),
        _baseCastTime(0.0),_baseManaCost(0.0),_baseHealing(0.0),
        _effectiveCastTime(0.0), _effectiveManaCost(0.0), _effectiveHealing(0.0),
        _HpS(0.0), _HpM(0.0), _MpS(0.0) {}
    Spell(SpellNameRank spell_name_rank_enum, SpellName spell_name_enum, const string& spell_name, int spell_rank, int level, double base_cast_time, double base_mana_cost, double base_healing):
        _spellNameRankEnum(spell_name_rank_enum), _spellNameEnum(spell_name_enum), _name(spell_name),_rank(spell_rank),_school(MagicSchool::HOLY),_level(level),_crit(0.0),
        _baseCastTime(base_cast_time),_baseManaCost(base_mana_cost),_baseHealing(base_healing),
        _effectiveCastTime(0.0), _effectiveManaCost(0.0), _effectiveHealing(0.0),
        _HpS(0.0), _HpM(0.0), _MpS(0.0) {}

    void PrintDetails() const {
        std::cout << _name << std::endl;
        std::cout << "\tLevel: " << _level << std::endl;
        std::cout << "\tCrit: " << _crit << std::endl;
        std::cout << "\tBase: " << std::endl;
        std::cout << "\t\tCast Time: " << _baseCastTime << std::endl;
        std::cout << "\t\tMana Cost: " << _baseManaCost << std::endl;
        std::cout << "\t\tHealing: " << _baseHealing << std::endl;
        std::cout << "\tEffective: " << std::endl;
        std::cout << "\t\tCast Time: " << _effectiveCastTime << std::endl;
        std::cout << "\t\tMana Cost: " << _effectiveManaCost << std::endl;
        std::cout << "\t\tHealing: " << _effectiveHealing << std::endl;
        std::cout << "\tHpS: " << _HpS << std::endl;
        std::cout << "\tHpM: " << _HpM << std::endl;
        std::cout << "\tMpS: " << _MpS << std::endl;
        return;
    }

    inline SpellNameRank getSpellNameRankEnum() const { return(_spellNameRankEnum); };
    inline SpellName getSpellNameEnum() const { return(_spellNameEnum); };
    inline string getSpellName() const { return(_name); };
    inline int getRank() const { return(_rank); };
    inline MagicSchool getSchool() const { return(_school); };
    inline int getLevel() const { return(_level); };
    inline double getCrit() const { return(_crit); };
    inline double getBaseCastTime() const { return(_baseCastTime); };
    inline double getBaseManaCost() const { return(_baseManaCost); };
    inline double getBaseHealing() const { return(_baseHealing); };
    inline double getEffectiveCastTime() const { return(_effectiveCastTime); };
    inline double getEffectiveManaCost() const { return(_effectiveManaCost); };
    inline double getEffectiveHealing() const { return(_effectiveHealing); };
    inline double getHpS() const { return(_HpS); };
    inline double getHpM() const { return(_HpM); };
    inline double getMpS() const { return(_MpS); };

    inline void setCrit(double crit) { _crit = crit; };
    inline void setEffectiveCastTime(double cast_time) { _effectiveCastTime = cast_time; };
    inline void setEffectiveManaCost(double mana_cost) { _effectiveManaCost = mana_cost; };
    inline void setEffectiveHealing(double healing) { _effectiveHealing = healing; };
    inline void setHpS(double hps) { _HpS = hps; };
    inline void setHpM(double hpm) { _HpM = hpm; };
    inline void setMpS(double mps) { _MpS = mps; };

    friend ostream & operator << (ostream& out, const Spell& spell);
};

ostream & operator << (ostream& out, const Spell& spell) {
    std::cout << spell._name;
    return out;
}

class SpellBook {

public:
    vector<Spell> _spellBook;

    SpellBook(): _spellBook() {};
    SpellBook(const TalentTree& talents, double spell_crit, double healing_power, bool T1_3PC, bool T2_8PC, bool debug) {
        // Initialize base priest spells
        _spellBook.clear();
        _spellBook.emplace_back(SpellNameRank::LESSER_HEAL_R1,SpellName::LESSER_HEAL,"Lesser Heal (Rank 1)", 1, 1, 1.5, 30.0, 53.0);
        _spellBook.emplace_back(SpellNameRank::LESSER_HEAL_R2,SpellName::LESSER_HEAL,"Lesser Heal (Rank 2)", 2, 4, 2.0, 45.0, 84.0);
        _spellBook.emplace_back(SpellNameRank::LESSER_HEAL_R3,SpellName::LESSER_HEAL,"Lesser Heal (Rank 3)", 3, 10, 2.5, 75.0, 154.0);
        _spellBook.emplace_back(SpellNameRank::HEAL_R1,SpellName::HEAL,"Heal (Rank 1)", 1, 16, 3.0, 155.0, 330.0);
        _spellBook.emplace_back(SpellNameRank::HEAL_R2,SpellName::HEAL,"Heal (Rank 2)", 2, 22, 3.0, 205.0, 476.0);
        _spellBook.emplace_back(SpellNameRank::HEAL_R3,SpellName::HEAL,"Heal (Rank 3)", 3, 28, 3.0, 255.0, 624.0);
        _spellBook.emplace_back(SpellNameRank::HEAL_R4,SpellName::HEAL,"Heal (Rank 4)", 4, 34, 3.0, 305.0, 781.0);
        _spellBook.emplace_back(SpellNameRank::GREATER_HEAL_R1,SpellName::GREATER_HEAL,"Greater Heal (Rank 1)", 1, 40, 3.0, 370.0, 982.0);
        _spellBook.emplace_back(SpellNameRank::GREATER_HEAL_R2,SpellName::GREATER_HEAL,"Greater Heal (Rank 2)", 2, 46, 3.0, 455.0, 1248.0);
        _spellBook.emplace_back(SpellNameRank::GREATER_HEAL_R3,SpellName::GREATER_HEAL,"Greater Heal (Rank 3)", 3, 52, 3.0, 545.0, 1556.0);
        _spellBook.emplace_back(SpellNameRank::GREATER_HEAL_R4,SpellName::GREATER_HEAL,"Greater Heal (Rank 4)", 4, 60, 3.0, 655.0, 1917.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R1,SpellName::FLASH_HEAL,"Flash Heal (Rank 1)", 1, 20, 1.5, 125.0, 225.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R2,SpellName::FLASH_HEAL,"Flash Heal (Rank 2)", 2, 26, 1.5, 155.0, 297.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R3,SpellName::FLASH_HEAL,"Flash Heal (Rank 3)", 3, 32, 1.5, 185.0, 373.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R4,SpellName::FLASH_HEAL,"Flash Heal (Rank 4)", 4, 38, 1.5, 215.0, 453.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R5,SpellName::FLASH_HEAL,"Flash Heal (Rank 5)", 5, 44, 1.5, 265.0, 584.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R6,SpellName::FLASH_HEAL,"Flash Heal (Rank 6)", 6, 50, 1.5, 315.0, 723.0);
        _spellBook.emplace_back(SpellNameRank::FLASH_HEAL_R7,SpellName::FLASH_HEAL,"Flash Heal (Rank 7)", 7, 56, 1.5, 380.0, 902.0);  

        if (debug) std::cout << "Base spells initialized" << std::endl;

        // Determine effective stats
        if (debug) std::cout << "Starting spell loop" << std::endl;
        for (Spell& spell : _spellBook) {
            if (debug) std::cout << spell << std::endl;
            // Calculate Effective Cast Time
            double effective_cast_time = spell.getBaseCastTime();
            if ( (spell.getSpellNameEnum() == SpellName::HEAL) || (spell.getSpellNameEnum() == SpellName::GREATER_HEAL) ) {
                effective_cast_time -= 0.1*talents.getPoints(Talents::DIVINE_FURY);
            }
            if ( T1_3PC && (spell.getSpellNameEnum() == SpellName::FLASH_HEAL) ) {
                effective_cast_time -= 0.1;
            }
            spell.setEffectiveCastTime(effective_cast_time);

            // Calculate Effective Mana Cost
            double mana_cost = spell.getBaseManaCost();
            if ( (spell.getSpellNameEnum() == SpellName::LESSER_HEAL) || (spell.getSpellNameEnum() == SpellName::HEAL) || (spell.getSpellNameEnum() == SpellName::GREATER_HEAL) ) {
                mana_cost *= (1 - 0.05*talents.getPoints(Talents::IMPROVED_HEALING));
            }
            spell.setEffectiveManaCost(mana_cost);

            // Determine Crit Chance (assumes all spells being compared that can crit are holy)
            spell.setCrit(spell_crit);
            
            // Calculate Effective Healing
            double base_coefficient = spell.getBaseCastTime() / 3.5;
            double coefficient_penalty = min( 1.0 , 1 - 0.0375*(20 - spell.getLevel()) );
            double effective_coefficient = base_coefficient * coefficient_penalty;
            double healing = spell.getBaseHealing() + effective_coefficient*healing_power;
            double healing_with_crit = healing*(1.0 + 0.5*spell.getCrit());
            spell.setEffectiveHealing(healing_with_crit*(1.0 + 0.02*talents.getPoints(Talents::SPIRITUAL_HEALING)));

            // Calculate efficiencies
            spell.setHpS(spell.getEffectiveHealing()/spell.getEffectiveCastTime());
            spell.setHpM(spell.getEffectiveHealing()/spell.getEffectiveManaCost());
            spell.setMpS(spell.getEffectiveManaCost()/spell.getEffectiveCastTime());
        }

        if (debug) std::cout << "_spellBook[0].getEffectiveCastTime(): " << _spellBook[0].getEffectiveCastTime() << std::endl;
    }

    inline Spell getSpell(const SpellNameRank spell_name) const { return( _spellBook[static_cast<int>(spell_name)] ); };

};

class Priest {
private:
    TalentTree _talents;
    vector<Item> _gearSet;
    SpellBook _spellBook;
    double _healingPower, _intellect, _spirit, _maxMana, _spellCrit, _mp5_gear, _mp5_spirit, _mp5_casting;
    // Tier bonuses
    bool _T1_3PC, _T1_5PC, _T2_3PC, _T2_8PC;
    // Quantities to maximize
    double _peakHps; // Peak HpS possible
    Spell _peakHpS_Spell;
    double _fastThroughput; // Best average HpS over whole encounter for spell cast time 2s or less
    Spell _fastThroughput_Spell;
    double _maxThroughput; // Best average HpS over whole encounter for all spells
    Spell _maxThroughput_Spell;
    double _healingScore; //_peakHps + _fastThroughput + _maxThroughput_Spell

    void _GearSwap(const vector<Item>& gear_set,bool debug) {
        _gearSet.clear();
        for (Item item : gear_set) {
            _gearSet.push_back(item);
        }

        if (debug) std::cout << "gear set" << std::endl;
        // Initialize stats with base amounts
        _healingPower = 0;
        _intellect = 116;
        _spirit = 126;
        _maxMana = 1096;
        _spellCrit = 0.008;
        _mp5_gear = 0;
        _mp5_spirit = 0;
        _mp5_casting = 0;
        _T1_3PC = false;
        _T1_5PC = false;
        _T2_3PC = false;
        _T2_8PC = false;
        int T1_cnt = 0, T2_cnt = 0;

        // Calculate stats gained from gear and check tier bonuses
        double healing_power_gear = 0, int_gear = 0, spi_gear = 0, mana_gear = 0, spell_crit_gear = 0;
        for (const Item gear : _gearSet) {
            healing_power_gear += gear.getHealingPower();
            int_gear += gear.getIntellect();
            spi_gear += gear.getSpirit();
            mana_gear += gear.getMana();
            spell_crit_gear += gear.getSpellCrit();
            _mp5_gear += gear.getMp5();
            if (gear.getTier() == 1) ++T1_cnt;
            if (gear.getTier() == 2) ++T2_cnt;
        }        
        _T1_3PC = T1_cnt >= 3;
        _T1_5PC = T1_cnt >= 5;
        _T2_3PC = T2_cnt >= 3;
        _T2_8PC = T2_cnt >= 8;
        if (debug) std::cout << "gear stats calculated" << std::endl;

        // Calculate final attributes
        _intellect += int_gear;
        _spirit += spi_gear;
        _healingPower = healing_power_gear + _talents.getPoints(Talents::SPIRITUAL_GUIDANCE)*0.05*_spirit;     
        if (_T1_5PC) _spellCrit += 0.02;
        _spellCrit += _intellect/5950.0 + _talents.getPoints(Talents::HOLY_SPECIALIZATION)*0.01;
        _maxMana += 15*_intellect + mana_gear;
        _maxMana *= (1.0 + 0.02*_talents.getPoints(Talents::MENTAL_STRENGTH));
        _mp5_spirit = (13.0 + _spirit/4.0)*5/2;
        double casting_regen_coefficient = _talents.getPoints(Talents::MEDITATION)*0.05;
        if (_T2_3PC) casting_regen_coefficient += 0.15;
        _mp5_casting = _mp5_gear + _mp5_spirit*casting_regen_coefficient;
        if (debug) std::cout << "final attributes calculated" << std::endl;

        return;
    }

public:
    Priest(): _talents(), _gearSet(), _spellBook(), 
    _healingPower(0.0), _intellect(0.0), _spirit(0.0), _maxMana(0.0), _spellCrit(0.0), _mp5_gear(0.0), _mp5_spirit(0.0), _mp5_casting(0.0),
    _T1_3PC(false), _T1_5PC(false), _T2_3PC(false), _T2_8PC(false),
    _peakHps(0.0), _peakHpS_Spell(), _fastThroughput(0.0), _fastThroughput_Spell(), _maxThroughput(0.0), _maxThroughput_Spell(), _healingScore(0.0) {};

    inline double getHealingScore() const { return(_healingScore); };

    void PrintGear() const { for (Item gear : _gearSet) gear.PrintDetails(false); };

    void GearSwap(const vector<Item>& gear_set, bool debug) {
        if (debug) std::cout << "GearSwap Enter" << std::endl;
        // Calculate stats from gear
        _GearSwap(gear_set,debug);

        // Calculate spells
        _spellBook = SpellBook(_talents, _spellCrit, _healingPower, _T1_3PC, _T2_8PC, debug);
        
        if (debug) std::cout << "GearSwap Exit" << std::endl;
        return;
    }

    friend ostream & operator << (ostream& out, const Priest& priest); 

    void PrintTalentTree() const { _talents.PrintDetails(); }

    void PrintMaxThroughputSpell() const {_maxThroughput_Spell.PrintDetails();}

    double HealingOptimization(double duration, bool debug) {
        // Initialize
        double GCD = 1.5;
        _peakHps = 0.0;
        _peakHpS_Spell = Spell();
        _fastThroughput = 0.0;
        _fastThroughput_Spell = Spell();
        _maxThroughput = 0.0;
        _maxThroughput_Spell = Spell();
        _healingScore = 0.0;

        // Calculate amount of mana to spend
        double total_mana = _maxMana + _mp5_casting*duration/5;
        if (debug) std::cout << "total_mana: " << total_mana << std::endl;
        // Loop through all spells to calculate max healing
        vector<double> spell_hps;
        if (debug) std::cout << "Starting spell loop" << std::endl;
        for (Spell spell : _spellBook._spellBook) {
            if (debug) std::cout << spell << std::endl;
            // Determine peak HpS
            double peak_hps_tmp = spell.getEffectiveHealing()/spell.getEffectiveCastTime();
            if (debug) std::cout << "peak_hps_tmp: " << peak_hps_tmp << std::endl;

            if (peak_hps_tmp > _peakHps) {
                _peakHps = peak_hps_tmp;
                _peakHpS_Spell = spell;
            }

            // Calculate number of spells that can be cast in duration and with mana
            int time_casts = floor( duration / max(GCD,spell.getEffectiveCastTime()) );
            int mana_casts = floor( total_mana / spell.getEffectiveManaCost() );
            int casts = min(time_casts,mana_casts);
            double healing = spell.getEffectiveHealing()*casts;
            // Add T2 8PC bonus
            if ( _T2_8PC && (spell.getSpellNameEnum() == SpellName::GREATER_HEAL) ) {
                // Add HoT that is rank 5 renew
                // Calculate number of ticks
                int ticks = floor( ( duration - max(GCD,spell.getEffectiveCastTime()) ) / 2.0 );
                double renew_healing_per_tick = (315.0 + 1.0*_healingPower)*(1.0 + 0.02*_talents.getPoints(Talents::SPIRITUAL_HEALING))*(1.0 + 0.05*_talents.getPoints(Talents::IMPROVED_RENEW))*2.0/15.0;
                healing += renew_healing_per_tick*ticks;
            }
            spell_hps.push_back(healing/duration);
        }

        // Determine maximum healing in each category
        for (int i = 0, N = _spellBook._spellBook.size(); i < N; ++i) {
            Spell spell = _spellBook._spellBook[i];

            // Fast healing throughput
            if ( (spell.getEffectiveCastTime() <= 2.0) && (spell_hps[i] > _fastThroughput) ) {
                _fastThroughput = spell_hps[i];
                _fastThroughput_Spell = spell;
            }

            // All healing throughput
            if (spell_hps[i] > _maxThroughput) {
                _maxThroughput = spell_hps[i];
                _maxThroughput_Spell = spell;
            }
        }

        _healingScore = _peakHps + _fastThroughput + _maxThroughput;
        return (_healingScore);
    }
};

ostream & operator << (ostream& out, const Priest& priest) {
    std::cout << "Priest State:" << std::endl;
    std::cout << "\tHealing Power: " << priest._healingPower << std::endl;
    std::cout << "\tIntellect: " << priest._intellect << std::endl;
    std::cout << "\tSpirit: " << priest._spirit << std::endl;
    std::cout << "\tMax Mana: " << priest._maxMana << std::endl;
    std::cout << "\tSpell Crit: " << priest._spellCrit << std::endl;    
    std::cout << "\tMp5 (spirit): " << priest._mp5_spirit << std::endl;
    std::cout << "\tMp5 (gear): " << priest._mp5_gear << std::endl;
    std::cout << "\tMp5 (casting): " << priest._mp5_casting << std::endl;
    std::cout << "\tTier 1 - 3 Piece Bonus: " << priest._T1_3PC << std::endl;
    std::cout << "\tTier 1 - 5 Piece Bonus: " << priest._T1_5PC << std::endl;
    std::cout << "\tTier 2 - 3 Piece Bonus: " << priest._T2_3PC << std::endl;
    std::cout << "\tTier 2 - 8 Piece Bonus: " << priest._T2_8PC << std::endl;
    std::cout << "\tPeak HpS: " << priest._peakHps << std::endl;
    std::cout << "\tPeak HpS Spell: " << priest._peakHpS_Spell << std::endl;
    std::cout << "\tMax Throughput HpS (fast): " << priest._fastThroughput << std::endl;
    std::cout << "\tMax Throughput HpS (fast) Spell: " << priest._fastThroughput_Spell << std::endl;
    std::cout << "\tMax Throughput HpS: " << priest._maxThroughput << std::endl;
    std::cout << "\tMax Throughput HpS Spell: " << priest._maxThroughput_Spell << std::endl;
    std::cout << "\tHealing Score: " << priest._healingScore << std::endl;
    return out;
}

int main() {
    bool verbose = true;
    // Read encounters.csv
    ifstream file ( "../data/encounters.csv" );
    if (!file.good()) {
        std::cout << "Bad encounters data file path!" << std::endl;
        return 1;
    }
    string line;
    vector<string> encounter_list;
    vector<double> encounter_durations;
    // Skip first line    
    getline(file, line);
    // Read data (by line)
    while ( getline(file, line) ) {
        // Read data (by csv)
        int cnt_csv = 0;
        istringstream str_str(line);
        string value;
        while (getline(str_str, value,',')) {
            if (cnt_csv == 0) {
                encounter_list.push_back(value);
            } else if (cnt_csv == 1) {
                // Clean
                value.erase(remove(value.begin(), value.end(), '\n'),value.end());
                value.erase(remove(value.begin(), value.end(), '\r'),value.end());
                encounter_durations.push_back(stod(value));
            } else {
                std::cout << "Malformed encounters.csv" << std::endl;
                return 1;
            }
            ++cnt_csv;
        }
    }
    // Query User for input
    std::cout << "Welcome to the Priest Gear Optimizer!" << std::endl << std::endl;
    std::cout << "Please select an encounter [#] to analyze:" << std::endl;
    for (int i = 0, N = encounter_list.size(); i < N; ++i) std::cout << "[" << i << "]\t" << encounter_list[i] << ": " << encounter_durations[i] << " s" << std::endl;
    int idx_inpt = 0;
    std::cout << "Encounter [#]: ";
    cin >> idx_inpt;
    std::cout << std::endl;
    std::cout << "Analyzing: " << encounter_list[idx_inpt] << std::endl << std::endl;
    double duration = encounter_durations[idx_inpt];

    // Initialize GearDatabase
    if (verbose) std::cout << "Initializing GearDatabase" << std::endl;
    GearDatabase gear(false);
    if (!gear.getValidity()) {
        std::cout << "GearDatabase not initialized correctly" << std::endl;
        return 1;
    }
    if (verbose) gear.PrintDetails();

    // Instantiate Priest
    if (verbose) std::cout << "Initializing Priest" << std::endl;
    Priest priest;
    if (verbose) priest.PrintTalentTree();

    // Loop over every possible gear combination    
    if (verbose) std::cout << "Starting Optimization" << std::endl;
    auto start_time = chrono::steady_clock::now();
    struct compare_struct {
        inline bool operator() (const Priest& val1, const Priest& val2) {
            // Max Heap: <
            // Min Heap: >
            return (val1.getHealingScore() > val2.getHealingScore());
        }
    };
    priority_queue< Priest , std::vector<Priest> , compare_struct > pq;
    size_t pq_size = 3;
    long int n_combos = 0;
    for (int i_head = 0, N_head = gear.getHeadSize(); i_head < N_head; ++i_head) {
        Item head = gear.getHeadItem(i_head);

        for (int i_neck = 0, N_neck = gear.getNeckSize(); i_neck < N_neck; ++i_neck) {
            Item neck = gear.getNeckItem(i_neck);

            for (int i_shoulders = 0, N_shoulders = gear.getShouldersSize(); i_shoulders < N_shoulders; ++i_shoulders) {
                Item shoulders = gear.getShouldersItem(i_shoulders);

                for (int i_back = 0, N_back = gear.getBackSize(); i_back < N_back; ++i_back) {
                    Item back = gear.getBackItem(i_back);

                    for (int i_chest = 0, N_chest = gear.getChestSize(); i_chest < N_chest; ++i_chest) {
                        Item chest = gear.getChestItem(i_chest);

                        for (int i_wrists = 0, N_wrists = gear.getWristsSize(); i_wrists < N_wrists; ++i_wrists) {
                            Item wrists = gear.getWristsItem(i_wrists);

                            for (int i_wand = 0, N_wand = gear.getWandSize(); i_wand < N_wand; ++i_wand) {
                                Item wand = gear.getWandItem(i_wand);

                                for (int i_hands = 0, N_hands = gear.getHandsSize(); i_hands < N_hands; ++i_hands) {
                                    Item hands = gear.getHandsItem(i_hands);

                                    for (int i_waist = 0, N_waist = gear.getWaistSize(); i_waist < N_waist; ++i_waist) {
                                        Item waist = gear.getWaistItem(i_waist);

                                        for (int i_legs = 0, N_legs = gear.getLegsSize(); i_legs < N_legs; ++i_legs) {
                                            Item legs = gear.getLegsItem(i_legs);

                                            for (int i_feet = 0, N_feet = gear.getFeetSize(); i_feet < N_feet; ++i_feet) {
                                                Item feet = gear.getFeetItem(i_feet);

                                                for (int i_finger_1 = 0, N_finger_1 = gear.getFingerSize(); i_finger_1 < N_finger_1; ++i_finger_1) {
                                                    Item finger_1 = gear.getFingerItem(i_finger_1);

                                                    for (int i_finger_2 = i_finger_1, N_finger_2 = gear.getFingerSize(); i_finger_2 < N_finger_2; ++i_finger_2) {                                                     
                                                        Item finger_2 = gear.getFingerItem(i_finger_2);                                                  
                                                        // Check if need to skip finger_2 (skip when duplicate item and item is unique)
                                                        if ( finger_2.getUnique() && (finger_1.getID() == finger_2.getID()) ) continue;

                                                        for (int i_trinket_1 = 0, N_trinket_1 = gear.getTrinketSize(); i_trinket_1 < N_trinket_1; ++i_trinket_1) {
                                                            Item trinket_1 = gear.getTrinketItem(i_trinket_1);

                                                            for (int i_trinket_2 = i_trinket_1, N_trinket_2 = gear.getTrinketSize(); i_trinket_2 < N_trinket_2; ++i_trinket_2) {
                                                                Item trinket_2 = gear.getTrinketItem(i_trinket_2);                                                            
                                                                // Check if need to skip trinket_2 (skip when duplicate item and item is unique)
                                                                if ( trinket_2.getUnique() && (trinket_1.getID() == trinket_2.getID()) ) continue;
                                                                
                                                                for (int i_weapon_2H = 0, N_weapon_2H = gear.getWeapon2HSize(); i_weapon_2H < N_weapon_2H; ++i_weapon_2H) {
                                                                    Item weapon_2H = gear.getWeapon2HItem(i_weapon_2H);

                                                                    // Check if 2H is "None"
                                                                    if (weapon_2H.getID() == -1) {
                                                                        // MH + OH

                                                                        for (int i_weapon_MH = 0, N_weapon_MH = gear.getWeaponMHSize(); i_weapon_MH < N_weapon_MH; ++i_weapon_MH) {
                                                                            Item weapon_MH = gear.getWeaponMHItem(i_weapon_MH);

                                                                            for (int i_weapon_OH = 0, N_weapon_OH = gear.getWeaponOHSize(); i_weapon_OH < N_weapon_OH; ++i_weapon_OH) {
                                                                                Item weapon_OH = gear.getWeaponOHItem(i_weapon_OH);                                                                                

                                                                                // Assemble gear list
                                                                                ++n_combos;
                                                                                vector<Item> gear_set;
                                                                                gear_set.push_back(head);
                                                                                gear_set.push_back(neck);
                                                                                gear_set.push_back(shoulders);
                                                                                gear_set.push_back(back);
                                                                                gear_set.push_back(chest);
                                                                                gear_set.push_back(wrists);
                                                                                gear_set.push_back(wand);
                                                                                gear_set.push_back(hands);
                                                                                gear_set.push_back(waist);
                                                                                gear_set.push_back(legs);
                                                                                gear_set.push_back(feet);
                                                                                gear_set.push_back(finger_1);
                                                                                gear_set.push_back(finger_2);
                                                                                gear_set.push_back(trinket_1);
                                                                                gear_set.push_back(trinket_2);
                                                                                gear_set.push_back(weapon_2H);
                                                                                gear_set.push_back(weapon_MH);
                                                                                gear_set.push_back(weapon_OH);

                                                                                // Update priest gear                                                               
                                                                                priest.GearSwap(gear_set,false);

                                                                                // Determine optimal healing output
                                                                                priest.HealingOptimization(duration,false);

                                                                                // Push to priority queue
                                                                                pq.push(priest);                                                                      
                                                                            } // weapon_OH
                                                                        } // weapon_MH
                                                                    } else {
                                                                        // 2H weapon

                                                                        // Assemble gear list
                                                                        ++n_combos;
                                                                        vector<Item> gear_set;
                                                                        gear_set.push_back(head);
                                                                        gear_set.push_back(neck);
                                                                        gear_set.push_back(shoulders);
                                                                        gear_set.push_back(back);
                                                                        gear_set.push_back(chest);
                                                                        gear_set.push_back(wrists);
                                                                        gear_set.push_back(wand);
                                                                        gear_set.push_back(hands);
                                                                        gear_set.push_back(waist);
                                                                        gear_set.push_back(legs);
                                                                        gear_set.push_back(feet);
                                                                        gear_set.push_back(finger_1);
                                                                        gear_set.push_back(finger_2);
                                                                        gear_set.push_back(trinket_1);
                                                                        gear_set.push_back(trinket_2);
                                                                        gear_set.push_back(weapon_2H);
                                                                        gear_set.emplace_back(-1,ItemSlot::WEAPON_MH);
                                                                        gear_set.emplace_back(-1,ItemSlot::WEAPON_OH);

                                                                        // Update priest gear                                                               
                                                                        priest.GearSwap(gear_set,false);

                                                                        // Determine optimal healing output
                                                                        priest.HealingOptimization(duration,false);

                                                                        // Push to priority queue
                                                                        pq.push(priest);
                                                                    }

                                                                    // Remove elements until onl 3 (largest) remain
                                                                    while (pq.size() > pq_size) {
                                                                        pq.pop();
                                                                    }

                                                                } // weapon_2H
                                                            } // trinket_2
                                                        } // trinket_1
                                                    } // finger_2
                                                } // finger_1
                                            } // feet
                                        } // legs
                                    } // waist
                                } // hands
                            } // wand
                        } // wrists
                    } // chest
                } // back
            } // shoulders
        } // neck
    } // head

    auto end_time = chrono::steady_clock::now();
    std::cout << std::endl << "Processed " << n_combos << " gear combinations in " << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << " secs" << std::endl << std::endl;

    // Print priority queue
    std::cout << "======================" << std::endl << "===== TOP 3 SETS =====" << std::endl << "======================" << std::endl << std::endl;
    int pq_cnt = pq.size();
    while (!pq.empty()) {
        Priest priest = pq.top();
        std::cout << "-------------" << std::endl << "--- SET " << pq_cnt << " ---" << std::endl << "-------------" << std::endl;
        std::cout << priest << std::endl;
        priest.PrintMaxThroughputSpell();
        priest.PrintGear();
        std::cout << std::endl;
        pq.pop();
        --pq_cnt;
    }
    return 0;
} 