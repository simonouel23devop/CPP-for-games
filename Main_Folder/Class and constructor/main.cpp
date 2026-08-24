#include <iostream>

// Simple class representing an entity with hitpoints
class Entity
{
public:
	// Constructor with a default parameter of 100.
	// If no argument is provided, the entity will have 100 hitpoints.
	Entity(int hitpoints = 100);

	// Destructor: runs when an Entity is destroyed. Added to demonstrate
	// cleanup and to show when objects are destroyed.
	~Entity();

	// Copy constructor: create a new Entity from an existing one.
	// This declaration allows us to define a copy constructor that
	// delegates to the int constructor (see definition below).
	Entity(const Entity& other);

	// Accessor that returns the entity's hitpoints.
	// Marked const because it does not modify the object.
	int gethitpoints() const
	{
		return hitpoints;
	}

private:
	// Member that stores the entity's hitpoints.
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

// Copy constructor definition: delegates to the int constructor to initialize
// the hitpoints member. Delegating keeps initialization logic centralized in
// the int constructor. The body prints a message so we can see when a copy is made.
Entity::Entity(const Entity& other)
	: Entity(other.hitpoints) // delegate to Entity(int)
{
	std::cout << "Entity::Entity(const Entity&) delegated with hitpoints " << hitpoints << std::endl;
}

// Free function that prints the hitpoints of an Entity passed by const reference.
// Passing by const reference avoids copying the object and prevents modification.
void printhitpoints(const Entity& e)
{
	std::cout << "hitpoints reference & :  " << e.gethitpoints() << std::endl;
}

int main()
{
	// Create an Entity object with 50 hitpoints.
	// Use a different variable name to avoid shadowing the type name.
	Entity player(50);

	// Create a copy of the existing Entity using the copy constructor.
	// This will delegate to the int constructor internally.
	Entity playerCopy = player;

	// Call the helper function to print the entity's hitpoints.
	printhitpoints(player);

	// Print hitpoints for a temporary Entity constructed with 10 hitpoints.
	printhitpoints(Entity(10));

	
	
	return 0;
}
