#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <tuple>

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
        cout << "Head";
    } else if (i == 1) {
        cout << "Neck";
    } else if (i == 2) {
        cout << "Shoulders";
    } else if (i == 3) {
        cout << "Back";
    } else if (i == 4) {
        cout << "Chest";
    } else if (i == 5) {
        cout << "Wrists";
    } else if (i == 6) {
        cout << "Weapon (2H)";
    } else if (i == 7) {
        cout << "Weapon (MH)";
    } else if (i == 8) {
        cout << "Weapon (OH)";
    } else if (i == 9) {
        cout << "Wand";
    } else if (i == 10) {
        cout << "Hands";
    } else if (i == 11) {
        cout << "Waist";
    } else if (i == 12) {
        cout << "Legs";
    } else if (i == 13) {
        cout << "Feet";
    } else if (i == 14) {
        cout << "Finger";
    } else if (i == 14) {
        cout << "Trinket";
    } else {
        cout << "ERROR";
    } 
    return out;
}

class Item {

private:
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
    const bool _owned;

public:
    Item():_itemSlot(ItemSlot::HEAD),_itemName("None"),_source(""),_dropChance(1.0),_unique(true),_tier(0),
        _healingPower(0.0),_intellect(0.0),_spirit(0.0),_mp5(0.0),_mana(0.0),_spellCrit(0.0),_owned(true) {}
    Item(const ItemSlot item_slot):_itemSlot(item_slot),_itemName("None"),_source(""),_dropChance(1.0),_unique(true),_tier(0),
        _healingPower(0.0),_intellect(0.0),_spirit(0.0),_mp5(0.0),_mana(0.0),_spellCrit(0.0),_owned(true) {}
    Item(const ItemSlot item_slot, const string& item_name, const string& source, double drop_chance, bool unique, int tier, 
        double healing_power, double intellect, double spirit, double mp5, double mana, double spell_crit, bool owned):
        _itemSlot(item_slot),_itemName(item_name),_source(source),_dropChance(drop_chance),_unique(unique),_tier(tier),
        _healingPower(healing_power),_intellect(intellect),_spirit(spirit),_mp5(mp5),_mana(mana),_spellCrit(spell_crit),_owned(owned) 
        {};

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
    inline bool getOwned() const { return(_owned); };

    void PrintDetails() const {
        cout << _itemName << endl;
        cout << "\tSlot: " << _itemSlot << endl;
        cout << "\tSource: " << _source << endl;
        cout << "\tDrop Chance: " << _dropChance*100.0 << "%" << endl;
        cout << "\tUnique: ";
            if (_unique) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
        cout << "\tTier: " << _tier << endl;
        cout << "\tHealing Power: " << _healingPower << endl;
        cout << "\tIntellect: " << _intellect << endl;
        cout << "\tSpirit: " << _spirit << endl;
        cout << "\tMp5: " << _mp5 << endl;
        cout << "\tMana: " << _mana << endl;
        cout << "\tSpell Crit: " << _spellCrit*100.0 << "%" << endl;
        cout << "\tOwned: ";
            if (_owned) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
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
    vector<Item> _data;
    bool _valid;

public:
    vector<const Item*> _head;
    vector<const Item*> _neck;
    vector<const Item*> _shoulders;
    vector<const Item*> _back;
    vector<const Item*> _chest;
    vector<const Item*> _wrists;
    vector<const Item*> _weapon_2H;
    vector<const Item*> _weapon_MH;
    vector<const Item*> _weapon_OH;
    vector<const Item*> _wand;
    vector<const Item*> _hands;
    vector<const Item*> _waist;
    vector<const Item*> _legs;
    vector<const Item*> _feet;
    vector<const Item*> _finger;
    vector<const Item*> _trinket;

    GearDatabase(): _data(),_valid(false) {};
    GearDatabase(bool debug) {
        // Read data from CSV
        _valid = Read_CSV(debug);
    };

    bool Read_CSV(bool debug) {
        // Read data from CSV
        // Return validity

        ifstream file ( "../data/gear.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
        if (!file.good()) {
            cout << "Bad gear data file path!" << endl;
            return false;
        }
           
        // Skip first line   
        string line; 
        std::getline(file, line);
        if (debug) cout << line << endl;

        // Read data (by line)
        while ( std::getline(file, line) )
        {
            if (debug) cout << line << endl;
            // Read data (by csv)
            int cnt_csv = 0;
            ItemSlot item_slot;
            string item_name, source;
            double drop_chance, healing_power, intellect, spirit, mp5, mana, spell_crit;
            bool unique, owned;
            int tier; 
            std::istringstream str_str(line);
            std::string value;
            while (getline(str_str, value,',')) {
                switch (cnt_csv) {
                    case 0:
                        // Slot
                        if (value.compare("head") == 0) {
                            item_slot = ItemSlot::HEAD;
                        } else if (value.compare("neck") == 0) {
                            item_slot = ItemSlot::NECK;
                        } else if (value.compare("shoulders") == 0) {
                            item_slot = ItemSlot::SHOULDERS;
                        } else if (value.compare("back") == 0) {
                            item_slot = ItemSlot::BACK;
                        } else if (value.compare("chest") == 0) {
                            item_slot = ItemSlot::CHEST;
                        } else if (value.compare("wrists") == 0) {
                            item_slot = ItemSlot::WRISTS;
                        } else if (value.compare("weapon 2H") == 0) {
                            item_slot = ItemSlot::WEAPON_2H;
                        } else if (value.compare("weapon MH") == 0) {
                            item_slot = ItemSlot::WEAPON_MH;
                        } else if (value.compare("weapon OH") == 0) {
                            item_slot = ItemSlot::WEAPON_OH;
                        } else if (value.compare("wand") == 0) {
                            item_slot = ItemSlot::WAND;
                        } else if (value.compare("hands") == 0) {
                            item_slot = ItemSlot::HANDS;
                        } else if (value.compare("waist") == 0) {
                            item_slot = ItemSlot::WAIST;
                        } else if (value.compare("legs") == 0) {
                            item_slot = ItemSlot::LEGS;
                        } else if (value.compare("feet") == 0) {
                            item_slot = ItemSlot::FEET;
                        } else if (value.compare("finger") == 0) {
                            item_slot = ItemSlot::FINGER;
                        } else if (value.compare("trinket") == 0) {
                            item_slot = ItemSlot::TRINKET;
                        } else {
                            cout << "Wrong item slot type" << endl;
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
                        // Owned
                        owned = StringToBool(value);
                        break;
                    case 12:
                        // Unique
                        unique = StringToBool(value);
                        break;
                    default:
                        cout << "Malformed CSV" << endl;
                        return false;
                }
                ++cnt_csv;   
            } // Read data
            // Instantiate Item
            Item item(item_slot, item_name, source, drop_chance, unique, tier, healing_power, intellect, spirit, mp5, mana, spell_crit, owned);
            if (debug) item.PrintDetails();
            // Store item
            _data.push_back(item);
            // Store reference to item in correct list
            if (item_slot == ItemSlot::HEAD) {
                _head.push_back(&item);
            } else if (item_slot == ItemSlot::NECK) {
                _neck.push_back(&item);
            } else if (item_slot == ItemSlot::SHOULDERS) {
                _shoulders.push_back(&item);
            } else if (item_slot == ItemSlot::BACK) {
                _back.push_back(&item);
            } else if (item_slot == ItemSlot::CHEST) {
                _chest.push_back(&item);
            } else if (item_slot == ItemSlot::WRISTS) {
                _wrists.push_back(&item);
            } else if (item_slot == ItemSlot::WEAPON_2H) {
                _weapon_2H.push_back(&item);
            } else if (item_slot == ItemSlot::WEAPON_MH) {
                _weapon_MH.push_back(&item);
            } else if (item_slot == ItemSlot::WEAPON_OH) {
                _weapon_OH.push_back(&item);
            } else if (item_slot == ItemSlot::WAND) {
                _wand.push_back(&item);
            } else if (item_slot == ItemSlot::HANDS) {
                _hands.push_back(&item);
            } else if (item_slot == ItemSlot::WAIST) {
                _waist.push_back(&item);
            } else if (item_slot == ItemSlot::LEGS) {
                _legs.push_back(&item);
            } else if (item_slot == ItemSlot::FEET) {
                _feet.push_back(&item);
            } else if (item_slot == ItemSlot::FINGER) {
                _finger.push_back(&item);
            } else if (item_slot == ItemSlot::TRINKET) {
                _trinket.push_back(&item);
            } else {
                cout << "Wrong item slot type" << endl;
                return false;
            }
        } // Read by line

        // Add "None" item for weapons
        Item item_2h_none(ItemSlot::WEAPON_2H); 
        _data.push_back(item_2h_none);
        _weapon_2H.push_back(&item_2h_none);
        Item item_mh_none(ItemSlot::WEAPON_MH);
        _data.push_back(item_mh_none);
        _weapon_MH.push_back(&item_mh_none);
        Item item_oh_none(ItemSlot::WEAPON_OH);
        _data.push_back(item_oh_none);
        _weapon_OH.push_back(&item_oh_none);        

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
            cout << "Bad talents data file path!" << endl;
            _valid = false;
            return;
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
                    continue;
                } else if (cnt_csv == 1) {
                    _talentTree.push_back(stoi(value));
                } else {
                    cout << "Malformed talents.csv" << endl;
                    _valid = false;
                    return;
                }
                ++cnt_csv;
            }
        }
    }

    inline int getPoints(Talents talent) const { return( _talentTree[static_cast<int>(talent)] ); };
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
    cout << spell._name;
    return out;
}

class SpellBook {

public:
    vector<Spell> _spellBook;

    SpellBook(): _spellBook() {};
    SpellBook(const TalentTree& talents, double spell_crit, double healing_power, bool T1_3PC, bool T2_8PC) {
        // Initialize base priest spells
        //const SpellNameRank spell_name_enum,const string& spell_name, int spell_rank, int level, double base_cast_time, double base_mana_cost, double base_healing
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

        // Determine effective stats
        for (Spell spell : _spellBook) {
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
            double coefficient_penalty = min( 1.0 , 1-0.0375*(20 - spell.getLevel()) );
            double effective_coefficient = base_coefficient * coefficient_penalty;
            double healing = spell.getBaseHealing() + effective_coefficient*healing_power;
            double healing_with_crit = healing*(1.0 + 0.5*spell.getCrit());
            spell.setEffectiveHealing(healing_with_crit*(1.0 + 0.02*talents.getPoints(Talents::SPIRITUAL_HEALING)));
        } 
    }

    inline Spell getSpell(const SpellNameRank spell_name) const { return( _spellBook[static_cast<int>(spell_name)] ); };

};

class Priest {
private:
    TalentTree _talents;
    vector<const Item*> _gearSet;
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

    void _GearSwap(vector<const Item*> gear_set) {
        _gearSet = gear_set;

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
        for (const Item* gear : _gearSet) {
            healing_power_gear += gear->getHealingPower();
            int_gear += gear->getIntellect();
            spi_gear += gear->getSpirit();
            mana_gear += gear->getMana();
            spell_crit_gear += gear->getSpellCrit();
            _mp5_gear += gear->getMp5();
            if (gear->getTier() == 1) ++T1_cnt;
            if (gear->getTier() == 2) ++T2_cnt;
        }
        _T1_3PC = T1_cnt >= 3;
        _T1_5PC = T1_cnt >= 5;
        _T2_3PC = T2_cnt >= 3;
        _T2_8PC = T2_cnt >= 8;

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

        return;
    }

public:
    Priest(): _talents(), _gearSet(), _spellBook(), 
    _healingPower(0.0), _intellect(0.0), _spirit(0.0), _maxMana(0.0), _spellCrit(0.0), _mp5_gear(0.0), _mp5_spirit(0.0), _mp5_casting(0.0),
    _T1_3PC(false), _T1_5PC(false), _T2_3PC(false), _T2_8PC(false),
    _peakHps(0.0), _peakHpS_Spell(), _fastThroughput(0.0), _fastThroughput_Spell(), _maxThroughput(0.0), _maxThroughput_Spell() {};

    void GearSwap(const vector<const Item*>& gear_set) {
        // Calculate stats from gear
        _GearSwap(gear_set);

        // Calculate spells
        _spellBook = SpellBook(_talents, _spellCrit, _healingPower, _T1_3PC, _T2_8PC);
        return;
    }

    //     TalentTree _talents;
    // vector<const Item*> _gearSet;
    // SpellBook _spellBook;
    // double , , , , , , , ;
    // // Tier bonuses
    //  , , , ;
    // // Quantities to maximize
    // double ; // Peak HpS possible
    //  ;
    // double ; // Best average HpS over whole encounter for spell cast time 2s or less
    // Spell ;
    // double ; // Best average HpS over whole encounter for all spells
    // Spell ;

    // inline double get() const { return(_healingPower); };
    // inline double get() const { return(_intellect); };
    // inline double get() const { return(_spirit); };
    // inline double get() const { return(_maxMana); };
    // inline double get() const { return(_spellCrit); };
    // inline double get() const { return(_mp5_gear); };
    // inline double get() const { return(_mp5_spirit); };
    // inline double get() const { return(_mp5_casting); };
    // inline bool get() const { return(_T1_3PC); };
    // inline bool get() const { return(_T1_5PC); };
    // inline bool get() const { return(_T2_3PC); };
    // inline bool get() const { return(_T2_8PC); };
    // inline double get() const { return(_peakHps); };
    // inline Spell get() const { return(_peakHpS_Spell); };
    // inline double get() const { return(_fastThroughput); };
    // inline Spell get() const { return(_fastThroughput_Spell); };
    // inline double get() const { return(_maxThroughput); };
    // inline Spell get() const { return(_maxThroughput_Spell); };
    // inline double get() const { return(); };

    friend ostream & operator << (ostream& out, const Priest& priest); 

    double HealingOptimization(double duration) {
        // Initialize
        double GCD = 1.5;
        _peakHps = 0.0;
        _peakHpS_Spell = Spell();
        _fastThroughput = 0.0;
        _fastThroughput_Spell = Spell();
        _maxThroughput = 0.0;
        _maxThroughput_Spell = Spell();

        // Calculate amount of mana to spend
        double total_mana = _maxMana + _mp5_casting*duration;
        // Loop through all spells to calculate max healing
        vector<double> spell_hps;
        for (Spell spell : _spellBook._spellBook) {
            // Determine peak HpS
            double peak_hps_tmp = spell.getEffectiveHealing()/spell.getEffectiveCastTime();
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
            if ( (spell.getEffectiveCastTime() <- 2.0) && (spell_hps[i] > _fastThroughput) ) {
                _fastThroughput = spell_hps[i];
                _fastThroughput_Spell = spell;
            }

            // All healing throughput
            if (spell_hps[i] > _maxThroughput) {
                _maxThroughput = spell_hps[i];
                _maxThroughput_Spell = spell;
            }
        }

        return (_peakHps + _fastThroughput + _maxThroughput);
    }
};

ostream & operator << (ostream& out, const Priest& priest) {
    cout << "Priest State:" << endl;
    cout << "\tHealing Power:" << priest._healingPower << endl;
    cout << "\tIntellect:" << priest._intellect << endl;
    cout << "\tSpirit:" << priest._spirit << endl;
    cout << "\tMax Mana:" << priest._maxMana << endl;
    cout << "\tMp5 (spirit):" << priest._mp5_spirit << endl;
    cout << "\tMp5 (gear):" << priest._mp5_gear << endl;
    cout << "\tMp5 (casting):" << priest._mp5_casting << endl;
    cout << "\tTier 1 - 3 Piece Bonus:" << priest._T1_3PC << endl;
    cout << "\tTier 1 - 5 Piece Bonus:" << priest._T1_5PC << endl;
    cout << "\tTier 2 - 3 Piece Bonus:" << priest._T2_3PC << endl;
    cout << "\tTier 2 - 8 Piece Bonus:" << priest._T2_8PC << endl;
    cout << "\tPeak HpS:" << priest._peakHps << endl;
    cout << "\tPeak HpS Spell:" << priest._peakHpS_Spell << endl;
    cout << "\tMax Throughput HpS (fast):" << priest._fastThroughput << endl;
    cout << "\tMax Throughput HpS (fast) Spell:" << priest._fastThroughput_Spell << endl;
    cout << "\tMax Throughput HpS:" << priest._maxThroughput << endl;
    cout << "\tMax Throughput HpS Spell:" << priest._maxThroughput_Spell << endl;
    return out;
}

int main() {
    // Read encounters.csv
    ifstream file ( "../data/encounters.csv" );
    if (!file.good()) {
        cout << "Bad encounters data file path!" << endl;
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
                cout << "Malformed encounters.csv" << endl;
                return 1;
            }
            ++cnt_csv;
        }
    }
    // Query User for input
    cout << "Welcome to the Priest Gear Optimizer!" << endl << endl;
    cout << "Please select an encounter [#] to analyze:" << endl;
    for (int i = 0, N = encounter_list.size(); i < N; ++i) cout << "[" << i << "]\t" << encounter_list[i] << ": " << encounter_durations[i] << " s" << endl;
    int idx_inpt = 0;
    cout << "Encounter [#]: ";
    cin >> idx_inpt;
    cout << endl;
    cout << "Analyzing: " << encounter_list[idx_inpt] << endl << endl;
    double duration = encounter_durations[idx_inpt];

    // Initialize GearDatabase
    GearDatabase gear(false);

    // Instantiate Priest
    Priest priest;

    // Loop over every possible gear combination
    priority_queue< tuple<double, vector<const Item*>> , vector< tuple<double, vector<const Item*>> > > pq;
    //const Item* head : gear._head
    for (int i_head = 0, N_head = gear._head.size(); i_head < N_head; ++i_head) {
        for (int i_neck = 0, N_neck = gear._neck.size(); i_neck < N_neck; ++i_neck) {
            for (int i_shoulders = 0, N_shoulders = gear._shoulders.size(); i_shoulders < N_shoulders; ++i_shoulders) {
                for (int i_back = 0, N_back = gear._back.size(); i_back < N_back; ++i_back) {
                    for (int i_chest = 0, N_chest = gear._chest.size(); i_chest < N_chest; ++i_chest) {
                        for (int i_wrists = 0, N_wrists = gear._wrists.size(); i_wrists < N_wrists; ++i_wrists) {
                            for (int i_wand = 0, N_wand = gear._wand.size(); i_wand < N_wand; ++i_wand) {
                                for (int i_hands = 0, N_hands = gear._hands.size(); i_hands < N_hands; ++i_hands) {
                                    for (int i_waist = 0, N_waist = gear._waist.size(); i_waist < N_waist; ++i_waist) {
                                        for (int i_legs = 0, N_legs = gear._legs.size(); i_legs < N_legs; ++i_legs) {
                                            for (int i_feet = 0, N_feet = gear._feet.size(); i_feet < N_feet; ++i_feet) {
                                                for (int i_finger_1 = 0, N_finger_1 = gear._finger.size(); i_finger_1 < N_finger_1; ++i_finger_1) {
                                                    for (int i_finger_2 = 0, N_finger_2 = gear._finger.size(); i_finger_2 < N_finger_2; ++i_finger_2) {
                                                        for (int i_trinket_1 = 0, N_trinket_1 = gear._trinket.size(); i_trinket_1 < N_trinket_1; ++i_trinket_1) {
                                                            for (int i_trinket_2 = 0, N_trinket_2 = gear._trinket.size(); i_trinket_2 < N_trinket_2; ++i_trinket_2) {
                                                                for (int i_weapon_2H = 0, N_weapon_2H = gear._weapon_2H.size(); i_weapon_2H < N_weapon_2H; ++i_weapon_2H) {

                                                                    if (gear._weapon_2H[i_weapon_2H]->getName().compare("None") == 0) {
                                                                        // MH + OH
                                                                        for (int i_weapon_MH = 0, N_weapon_MH = gear._weapon_MH.size(); i_weapon_MH < N_weapon_MH; ++i_weapon_MH) {
                                                                            for (int i_weapon_OH = 0, N_weapon_OH = gear._weapon_OH.size(); i_weapon_OH < N_weapon_OH; ++i_weapon_OH) {
                                                                                // Assemble gear list
                                                                                vector<const Item*> gear_set;
                                                                                gear_set.push_back(gear._head[i_head]);
                                                                                gear_set.push_back(gear._neck[i_neck]);
                                                                                gear_set.push_back(gear._shoulders[i_shoulders]);
                                                                                gear_set.push_back(gear._back[i_back]);
                                                                                gear_set.push_back(gear._chest[i_chest]);
                                                                                gear_set.push_back(gear._wrists[i_wrists]);
                                                                                gear_set.push_back(gear._wand[i_wand]);
                                                                                gear_set.push_back(gear._hands[i_hands]);
                                                                                gear_set.push_back(gear._waist[i_waist]);
                                                                                gear_set.push_back(gear._legs[i_legs]);
                                                                                gear_set.push_back(gear._feet[i_feet]);
                                                                                gear_set.push_back(gear._finger[i_finger_1]);
                                                                                gear_set.push_back(gear._finger[i_finger_2]);
                                                                                gear_set.push_back(gear._trinket[i_trinket_1]);
                                                                                gear_set.push_back(gear._trinket[i_trinket_2]);
                                                                                gear_set.push_back(gear._weapon_MH[i_weapon_MH]);
                                                                                gear_set.push_back(gear._weapon_OH[i_weapon_OH]);

                                                                                // Update priest gear                                                                    
                                                                                priest.GearSwap(gear_set);

                                                                                // Determine optimal healing output
                                                                                double healing = priest.HealingOptimization(duration);

                                                                                // Push to priority queue
                                                                                pq.emplace(healing,gear_set);

                                                                                // Check
                                                                                cout << priest << endl;
                                                                                
                                                                                break;
                                                                                
                                                                            } // weapon_OH
                                                                        } // weapon_MH
                                                                    } else {
                                                                        // 2H weapon

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

    cout << "Done!" << endl;
    return 0;
} 

// void ReadGearData



