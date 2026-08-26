#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include <sstream>
#include <vector>
// for the PlayerEncoder.h //
namespace PlayerEncoder { inline std::string escape(const std::string& in)
{
	std::string out;
	out.reserve(in.size());
	for (char c : in)
	{
		if (c == '|') out += "\\|";
		else if (c == '\\') out += "\\\\";
		else out += c;
	}
	return out;
}

inline std::string unescape(const std::string& in)
{
	std::string out;
	out.reserve(in.size());
	for (size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '\\' && i + 1 < in.size())
		{
			++i;
			out += in[i];
		}
		else out += in[i];
	}
	return out;
} }
// Simple class representing an entity with hitpoints
class Entity
{
public:
	// Constructor with a default parameter of 100.
	// If no argument is provided, the entity will have 100 hitpoints.
	Entity(int hitpoints = 100);

	// Destructor: make virtual so derived-class destructors run correctly
	// when deleting through a base-class pointer.
	virtual ~Entity();

	// Pure virtual method that derived classes must implement to describe themselves.
	virtual void describe() const = 0;

	// Another pure virtual function: derived classes must provide an attack
	// implementation. This demonstrates multiple pure virtuals and enforces
	// that Entity is abstract.
	virtual void attack() = 0;

	// Copy constructor: create a new Entity from an existing one.
	// This declaration allows us to define a copy constructor that
	// delegates to the int constructor (see definition below).
	Entity(const Entity& other);

	// Apply a temporary buff to the entity (pure virtual): derived types
	// must implement how a buff affects them.
	virtual void applyBuff(const struct Buff& b) = 0;

	// Take damage: virtual so derived classes (Player) can factor armor.
	virtual void takeDamage(int amount);

	// Accessor that returns the entity's hitpoints.
	// Marked const because it does not modify the object.
	int gethitpoints() const
	{
		return hitpoints;
	}

protected:
	// Member that stores the entity's hitpoints. Protected so derived
	// classes (Player) can inspect/modify it (e.g., when taking damage).
	int hitpoints = 0;
};

// Constructor definition using an initializer list to set the member 'hitpoints'.
// The initializer list ensures the member is initialized directly with the
// provided value instead of being default-initialized then assigned.
Entity::Entity(int hitpoints)
	: hitpoints(hitpoints)
{
	// Print a message so we can see when the constructor runs and with what value.
	std::cout << "Entity::Entity(" << hitpoints << ") " << std::endl;
}

// Destructor definition: prints a message when an Entity is destroyed.
Entity::~Entity()
{
	std::cout << "Entity::~Entity(" << hitpoints << ") " << std::endl;
}

// Default takeDamage reduces hitpoints and reports the remaining value.
void Entity::takeDamage(int amount)
{
	hitpoints -= amount;
	if (hitpoints < 0) hitpoints = 0;
	std::cout << "Entity took " << amount << " damage, remaining hitpoints=" << hitpoints << std::endl;
}



// Copy constructor definition: delegates to the int constructor to initialize
// the hitpoints member. Delegating keeps initialization logic centralized in
// the int constructor. The body prints a message so we can see when a copy is made.
Entity::Entity(const Entity& other)
	: Entity(other.hitpoints) // delegate to Entity(int)
{
	std::cout << "Entity::Entity(const Entity&) delegated with hitpoints " << hitpoints << std::endl;
}

// Simple POD-like struct representing a weapon.
// - name: textual name of the weapon
// - damage: how much damage the weapon deals when used in an attack
// This struct is small and copyable and used by Player to model equipment.
struct Weapon
{
	std::string name;
	int damage;
	Weapon(const std::string& n = "Fire sword", int d = 50) : name(n), damage(d) {}
};

// Simple struct representing armor worn by a player.

struct Armor
{
	std::string name;
	int defense;
	Armor(const std::string& n = "Cloth", int d = 0) : name(n), defense(d) {}
};

// Buff struct models a temporary effect that increases damage for a
// limited number of attacks.
struct Buff
{
	std::string name;
	int damageBonus;        // added to weapon.damage while buff is active
	int durationAttacks;    // how many attacks the buff lasts
	Buff(const std::string& n = "Rage", int bonus = 20, int duration = 1)
		: name(n), damageBonus(bonus), durationAttacks(duration) {}
};

// Derived class demonstrating inheritance from Entity
class Player : public Entity
{
public:
	// Construct a Player with hitpoints, a name, optional weapon and armor.
	// Buffs are initially inactive.
	Player(int hitpoints, const std::string& name, Weapon weapon = Weapon(), Armor armor = Armor())
		: Entity(hitpoints), name(name), weapon(weapon), armor(armor), activeBuffDamage(0), remainingBuffAttacks(0), maxHitpoints(hitpoints), healCharges(2)
	{
		std::cout << "Player::Player(" << name << ", " << gethitpoints() << ")" << std::endl;
		std::cout << "  Equipment: weapon='" << weapon.name << "'(" << weapon.damage << ") armor='" << armor.name << "'(" << armor.defense << ")" << std::endl;
	}

	// Override describe to provide player-specific information and show armor.
	void describe() const override
	{
		std::cout << "Player: name='" << name << "' hitpoints=" << gethitpoints() << " armor='" << armor.name << "'(" << armor.defense << ")" << std::endl;
	}

	// Implement the pure virtual attack() from Entity. Uses any active buff
	// to increase damage for a limited number of attacks.
	void attack() override
	{
		int totalDamage = weapon.damage + activeBuffDamage;
		std::cout << "Player '" << name << "' attacks with '" << weapon.name << "' for " << totalDamage << " damage";
		if (activeBuffDamage > 0)
			std::cout << " (buff +" << activeBuffDamage << " remaining attacks: " << remainingBuffAttacks << ")";
		std::cout << std::endl;

		// Consume buff uses
		if (remainingBuffAttacks > 0)
		{
			--remainingBuffAttacks;
			if (remainingBuffAttacks == 0)
				activeBuffDamage = 0;
		}
	}

	// Deal damage and consume any active buff uses. Returns the damage value
	// so external code (battle simulation) can apply it to a target.
	int dealDamage()
	{
		int totalDamage = weapon.damage + activeBuffDamage;
		if (remainingBuffAttacks > 0)
		{
			--remainingBuffAttacks;
			if (remainingBuffAttacks == 0)
				activeBuffDamage = 0;
		}
		return totalDamage;
	}

	// Accessors useful for battle logic
	const std::string& getName() const { return name; }
	bool isAlive() const { return gethitpoints() > 0; }

	// Public accessors used by the serializer
	Weapon getWeapon() const { return weapon; }
	Armor getArmor() const { return armor; }
	int getActiveBuffDamage() const { return activeBuffDamage; }
	int getRemainingBuffAttacks() const { return remainingBuffAttacks; }
	int getHealCharges() const { return healCharges; }

	// Mutators used by the serializer to restore state
	void setBuffState(int active, int remaining) { activeBuffDamage = active; remainingBuffAttacks = remaining; }
	void setHealCharges(int c) { healCharges = c; }
	void setHitpoints(int hp) { hitpoints = hp; }

	// Heal the player by amount up to their max hitpoints. Returns actual healed amount.
	int heal(int amount)
	{
		if (healCharges <= 0)
		{
			std::cout << "Player '" << name << "' has no healing charges left." << std::endl;
			return 0;
		}

		int before = hitpoints;
		hitpoints += amount;
		if (hitpoints > maxHitpoints) hitpoints = maxHitpoints;
		--healCharges;
		int actual = hitpoints - before;
		std::cout << "Player '" << name << "' heals for " << actual << " (charges left=" << healCharges << ")" << std::endl;
		return actual;
	}

	bool canHeal() const { return healCharges > 0 && hitpoints < maxHitpoints; }

	int getMaxHitpoints() const { return maxHitpoints; }

	~Player()
	{
		std::cout << "Player::~Player(" << name << ")" << std::endl;
	}

	// Apply a temporary buff that increases damage for a limited number of
	// attacks. This implements the pure virtual from Entity.
	void applyBuff(const Buff& b) override
	{
		activeBuffDamage += b.damageBonus; // stacking behavior
		remainingBuffAttacks = std::max(remainingBuffAttacks, b.durationAttacks);
		std::cout << "Player '" << name << "' gained buff '" << b.name << "' (+" << b.damageBonus << " for " << b.durationAttacks << " attacks)" << std::endl;
	}

	// Override takeDamage to factor in armor.defense.
	void takeDamage(int amount) override
	{
		int reduced = amount - armor.defense;
		if (reduced < 0) reduced = 0;
		std::cout << "Player '" << name << "' armor reduces damage by " << armor.defense << ", received " << reduced << std::endl;
		Entity::takeDamage(reduced);
	}

private:
	std::string name;
	// Weapon owned/used by this player.
	Weapon weapon;
	// Armor worn by this player.
	Armor armor;

	// Buff state.
	int activeBuffDamage;
	int remainingBuffAttacks;
	int maxHitpoints;
	int healCharges;
};

// Provide encoder/decoder implementations now that Player is fully defined.

namespace PlayerEncoder
{
	std::string encode(const Player& p)
	{
		std::ostringstream oss;
		oss << escape(p.getName()) << "|";
		oss << p.gethitpoints() << "|";
		oss << p.getMaxHitpoints() << "|";
		Weapon w = p.getWeapon();
		oss << escape(w.name) << "|" << w.damage << "|";
		Armor a = p.getArmor();
		oss << escape(a.name) << "|" << a.defense << "|";
		oss << p.getActiveBuffDamage() << "|" << p.getRemainingBuffAttacks() << "|" << p.getHealCharges();
		return oss.str();
	}

	Player decode(const std::string& s)
	{
		std::vector<std::string> parts;
		parts.reserve(12);
		std::string cur;
		for (size_t i = 0; i < s.size(); ++i)
		{
			if (s[i] == '\\' && i + 1 < s.size())
			{
				cur += s[i+1];
				++i;
			}
			else if (s[i] == '|')
			{
				parts.push_back(cur);
				cur.clear();
			}
			else cur += s[i];
		}
		parts.push_back(cur);

		auto getInt = [&](size_t idx, int def = 0) -> int {
			if (idx >= parts.size() || parts[idx].empty()) return def;
			try { return std::stoi(parts[idx]); } catch (...) { return def; }
		};

		std::string name = (parts.size() > 0) ? parts[0] : std::string("Player");
		int hit = getInt(1, 0);
		int maxHit = getInt(2, hit);
		std::string wname = (parts.size() > 3) ? parts[3] : std::string("Fire sword");
		int wdamage = getInt(4, 50);
		std::string aname = (parts.size() > 5) ? parts[5] : std::string("Cloth");
		int adef = getInt(6, 0);
		int activeBuff = getInt(7, 0);
		int remainingBuff = getInt(8, 0);
		int heals = getInt(9, 0);

		Weapon w( unescape(wname), wdamage );
		Armor a( unescape(aname), adef );
		Player p(hit, unescape(name), w, a);
		p.setHitpoints(hit);
		p.setBuffState(activeBuff, remainingBuff);
		p.setHealCharges(heals);
		return p;
	}

}

// Free function that prints the hitpoints of an Entity passed by const reference.
// Passing by const reference avoids copying the object and prevents modification.
void printhitpoints(const Entity& e)
{
	std::cout << "hitpoints reference & :  " << e.gethitpoints() << std::endl;
}

int main()
{
	// Create a Player (derived from Entity) and demonstrate inheritance.
	Player hero(75, "Alice", Weapon("Sword", 30), Armor("Plate", 8));
	hero.describe();              // calls Player::describe()
	hero.attack();                // calls Player::attack()
	printhitpoints(hero);         // works via base reference

	// Polymorphism: use a base-class pointer to refer to a derived object.
	Entity* e = new Player(30, "Bob");
	e->describe();                // virtual call -> Player::describe()
	printhitpoints(*e);
	e->attack();                  // virtual call -> Player::attack()
	delete e;                     // virtual destructor ensures Player::~Player runs

	// Create a copy of a Player using the implicitly-generated copy constructor.
	Player baseCopy = hero;

	// Additional players with different weapons and armor to demonstrate variety.
	Player swordsman(90, "Thorin", Weapon("Greatsword", 60), Armor("Plate", 12));
	swordsman.describe();
	swordsman.attack();
	printhitpoints(swordsman);

	Player rogue(55, "Shade", Weapon("Dagger", 25), Armor("Leather", 3));
	rogue.describe();
	rogue.attack();

	Player crossbowman(65, "Rory", Weapon("Crossbow", 40), Armor("Chain", 6));
	crossbowman.describe();
	crossbowman.attack();

	// Demonstrate combat with buffs: hero gets a temporary damage buff then
	// attacks an opponent; opponent's armor reduces incoming damage.
	Buff berserk("Berserk", 20, 2); // +20 damage for 2 attacks
	hero.applyBuff(berserk);
	std::cout << "Combat: hero attacks rogue twice while berserk is active" << std::endl;
	hero.attack();
	// To demonstrate damage application we compute the damage value and
	// call takeDamage on the target. (attack() only prints in this simple
	// example.)
	int damage1 = 30 + 20; // sword base 30 + berserk 20
	rogue.takeDamage(damage1);
	hero.attack();
	int damage2 = 30 + 20; // buff still active for second attack
	rogue.takeDamage(damage2);

	// Print hitpoints for a temporary Player constructed with 10 hitpoints.
	printhitpoints(Player(10, "Temp"));



	std::cout << "\033[31m" << "Duel is about to begin ...." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));


	// --- Battle simulation between two players ---//
	std::cout << "\033[32m" << "Starting a duel between two players.." << std::endl;
	std::cout << "\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));


	Player p1(80, "Aria", Weapon("Longsword", 35), Armor("Chain", 4));
	Player p2(75, "Drake", Weapon("Battle Axe", 40), Armor("Leather", 2));
	// Patch placeholder - no behavioral changes

	p1.describe();
	p2.describe();

	// Optional: give p1 a short buff
	Buff quickRage("Quick Rage", 10, 1);
	p1.applyBuff(quickRage);

	// Simulate random turns until one player is defeated in a duel.
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> coin(0, 1);
	int round = 1;
	while (p1.isAlive() && p2.isAlive())
	{
		std::cout << "\n-- Round " << round << " --" << std::endl;

		// Randomly choose attacker this round
		Player* attacker = (coin(rng) == 0) ? &p1 : &p2;
		Player* defender = (attacker == &p1) ? &p2 : &p1;

		std::cout << attacker->getName() << " is chosen to act this round." << std::endl;

		// Determine how many actions attacker gets this turn (1 or 2)
		std::uniform_int_distribution<int> actionsDist(1, 2);
		int actions = actionsDist(rng);

		for (int a = 0; a < actions && attacker->isAlive() && defender->isAlive(); ++a)
		{
			// Decide action: higher chance to attack, lower to heal
			std::uniform_int_distribution<int> actionDist(0, 4); // 0-3 attack, 4 heal
			int action = actionDist(rng);

			if (action == 4 && attacker->canHeal())
			{
				int healAmount = 18; // configurable
				attacker->heal(healAmount);
			}
			else
			{
				int dmg = attacker->dealDamage();
				// Choose one of three phrasing options for the damage message
				std::uniform_int_distribution<int> phraseDist(0, 2);
				int phr = phraseDist(rng);
				if (phr == 0)
					std::cout << attacker->getName() << " deals " << dmg << " raw damage to " << defender->getName() << std::endl;
				else if (phr == 1)
					std::cout << attacker->getName() << " inflicts " << dmg << " damage on " << defender->getName() << std::endl;
				else
					std::cout << attacker->getName() << " hits " << defender->getName() << " for " << dmg << " damage" << std::endl;

				defender->takeDamage(dmg);

				// Defender may reactively heal as a reaction (chance-based)
				std::uniform_int_distribution<int> reactDist(0, 3); // 0 triggers reaction
				if (reactDist(rng) == 0 && defender->canHeal() && defender->isAlive())
				{
					int reactHeal = 20; // smaller reaction heal
					std::cout << defender->getName() << " attempts to heal spell!" << std::endl;
					defender->heal(reactHeal);
				}
			}

			// brief pause between multiple actions
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

		// Report both players' hitpoints
		std::cout << p1.getName() << " HP=" << p1.gethitpoints() << "  |  " << p2.getName() << " HP=" << p2.gethitpoints() << std::endl;

		++round;
		// small pause for readability
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	// Announce result
	if (p1.isAlive())
		std::cout << "\nDuel result: " << p1.getName() << " wins!" << std::endl;
	else if (p2.isAlive())
		std::cout << "\nDuel result: " << p2.getName() << " wins!" << std::endl;
	else
		std::cout << "\nDuel result: Both combatants fell to lava!" << std::endl;

	return 0;
}
