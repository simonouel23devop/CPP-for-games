#pragma once
#include <string>
#include <sstream>

// Forward declarations from main.cpp
struct Weapon;
struct Armor;
class Player;

namespace PlayerEncoder
{
	// Simple POD representing serialized player state
	struct PlayerData
	{
		std::string name;
		int hitpoints = 0;
		int maxHitpoints = 0;
		std::string weaponName;
		int weaponDamage = 0;
		std::string armorName;
		int armorDefense = 0;
		int activeBuffDamage = 0;
		int remainingBuffAttacks = 0;
		int healCharges = 0;
	};

	// Encode the player into a compact pipe-separated string.
	// Format: name|hit|maxHit|weaponName|weaponDamage|armorName|armorDef|activeBuff|remainingBuff|healCharges
	std::string encode(const Player& p);

	// Decode the string back into a Player object. Implementation must be
	// provided in a translation unit that has the full Player definition.
	Player decode(const std::string& s);

	// Helper: escape/unescape pipe characters in strings (very basic)
	inline std::string escape(const std::string& in)
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
	}

}
