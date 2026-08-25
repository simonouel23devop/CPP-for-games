#include <iostream>
#include <string>
#include <algorithm>
// It demonstrates returning damage from attack(), applying
// temporary buffs, and using armor to reduce incoming damage.

struct Weapon {
	std::string name;
	int damage;
	Weapon(const std::string& n = "Fists", int d = 5) : name(n), damage(d) {}
};

struct Armor {
	std::string name;
	int defense;
	Armor(const std::string& n = "Cloth", int d = 0) : name(n), defense(d) {}
};

struct Buff {
	std::string name;
	int damageBonus;
	int durationAttacks;
	Buff(const std::string& n = "Rage", int bonus = 10, int duration = 1)
		: name(n), damageBonus(bonus), durationAttacks(duration) {}
};

// Base combatant (abstract) with pure virtual attack so derived classes must
// implement attack() that returns an int damage value.
class Combatant {
public:
	Combatant(int hp) : hp(hp) {}
	virtual ~Combatant() = default;
	virtual int attack() = 0;               // returns damage dealt
	virtual void takeDamage(int amount) {
		hp -= amount;
		if (hp < 0) hp = 0;
	}
	int getHP() const { return hp; }
	virtual void describe() const = 0;
protected:
	int hp;
};

class Player : public Combatant {
public:
	Player(std::string n, int hp, Weapon w = Weapon(), Armor a = Armor())
		: Combatant(hp), name(std::move(n)), weapon(w), armor(a), activeBuff(0), remaining(0) {}

	// attack returns the damage value (weapon + active buff)
	int attack() override {
		int dmg = weapon.damage + activeBuff;
		// consume buff usage
		if (remaining > 0) {
			--remaining;
			if (remaining == 0) activeBuff = 0;
		}
		std::cout << name << " attacks with " << weapon.name << " for " << dmg << " damage";
		if (activeBuff > 0) std::cout << " (buff +" << activeBuff << " remaining: " << remaining << ")";
		std::cout << std::endl;
		return dmg;
	}

	void takeDamage(int amount) override {
		int reduced = amount - armor.defense;
		if (reduced < 0) reduced = 0;
		hp -= reduced;
		if (hp < 0) hp = 0;
		std::cout << name << " receives " << reduced << " damage after armor (" << armor.defense << ") -> hp=" << hp << std::endl;
	}

	void applyBuff(const Buff& b) {
		activeBuff += b.damageBonus; // stack
		remaining = std::max(remaining, b.durationAttacks);
		std::cout << name << " gains buff '" << b.name << "' (+" << b.damageBonus << " for " << b.durationAttacks << " attacks)" << std::endl;
	}

	void describe() const override {
		std::cout << name << " hp=" << hp << " weapon=" << weapon.name << "(" << weapon.damage << ") armor=" << armor.name << "(" << armor.defense << ")" << std::endl;
	}

private:
	std::string name;
	Weapon weapon;
	Armor armor;
	int activeBuff;
	int remaining; // remaining attacks for buff
};

int main() {
	Player p1("Alice", 80, Weapon("Sword", 25), Armor("Plate", 8));
	Player p2("Shade", 60, Weapon("Dagger", 15), Armor("Leather", 3));

	p1.describe();
	p2.describe();

	// Apply a temporary buff to Alice
	Buff berserk("Berserk", 20, 2);
	p1.applyBuff(berserk);

	// Simple turn-based exchange: p1 then p2 for 3 rounds or until someone dies
	for (int round = 1; round <= 3; ++round) {
		std::cout << "-- Round " << round << " --" << std::endl;
		int d1 = p1.attack();
		p2.takeDamage(d1);
		if (p2.getHP() == 0) { std::cout << p2.getHP() << " -> " << "p2 defeated" << std::endl; break; }

		int d2 = p2.attack();
		p1.takeDamage(d2);
		if (p1.getHP() == 0) { std::cout << p1.getHP() << " -> " << "p1 defeated" << std::endl; break; }
	}

	std::cout << "Final states:" << std::endl;
	p1.describe();
	p2.describe();
	return 0;
}
