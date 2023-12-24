The cpp, h and exe files are in the submit folder.
If you want to build and run the code you can open the cpp file on your coding applications and run it on you own terminal. But you can not run it on Visual Studio Community, instead you can open the exe file in the submit folder to check how the code work. Sorry for the inconvenient. 

We have change our group recently due to the lack of partners, so the group is not real.

Thank you for your time

Best regards,
陳仕興 & 王家宏

=====================================================================================================================================
HOW THE CODE WORK
We seperate the file to header file and source file. All the header file only do the declaration whilte the defining is on the source file

Position: (x,y)
Position class is a class to describe other object's position on the board.
It only has two integer variables which are x and y.
It has basic setter, getter, and constructor.
It also has methods that overload operators for convinient in further usage.

Hero:
Hero is the player's avatar. It have level, exp, max exp to upgrade to next level, icon, hp, power and bullet.
By default the Hero class is set to level 1, 0 exp, 15 to upgrade to level 2 and will increment as the level goes up, 100 hp, 5 power and 5 bullet.
The hero class have basic setter and getter, and constructor.
The hero class have a method called 'move' to set the hero position to a given position that already checked its validation on the main file.
The hero class have a method called 'gainEXP' to upgrade the hero to the next level, when the hero has the enough amount of exp. This method also upgrade the hero exp when the hero hasn't have the enough amount of exp to level up.
The hero class have a method called 'damage' that minus the hero's health

Creature: (BASE CLASS)
Creature is the enemy that hero must kill.
By default there are only two kinds of Creature which are ghost and zombie. Both have different attributes and will be explained furhtermore in the 'Ghost' and 'Zombie' sections.
Creature has basic setter and getter, and constructor.
Creature has icon, hp, and position. These variables may varies according to the derived class.
Creature has a method called 'update' to check whether the creature can see the hero or not.

Ghost: (DERIVED CLASS OF Creature)
Has all creature's properties.
The icon is 'G'.
Has more attack and lower health compared to zombie.

Zombie: (DERIVED CLASS OF Creature)
Has all creature's properties
The icon is 'Z'
Has lower attack and higher health compared to ghost.

Item: (BASE CLASS)
The Item class have basic setter and getter, and constructor.
Item has icon, hp, and position. These variables may varies according to the derived class.

Trigger: (DERIVED CLASS OF Item)
Has all creature's properties.
Trigger class has basic constructor.
The icon is 'T'.
Trigger is a place where the hero can do level up.
Trigger has a method called 'update' to give the hero 10 exp by calling hero's 'gainEXP' method

HealthPotion: (DERIVED CLASS OF Item)
Has all creature's properties.
The HealthPotion class have basic setter and getter, and constructor.
The icon is 'H'.
When hero meet it, hero will add 10 hp

Sword: (DERIVED CLASS OF Item)
Has all creature's properties.
The Sword class have basic constructor.
The icon is 'S'.
When hero meet it, hero will add 5 power

Cartridge: (DERIVED CLASS OF Item)
Has all creature's properties.
The Cartridge class have basic constructor.
The icon is 'B'.
When hero meet it, hero will add 3 bullet

main: (The main program that control the flow of the game)
- Take the user input about the size of the board. (must be bigger than 4)
- Set up the board using the given size of height and width
- Draw the board by calling 'draw' function
- Draw the info by calling 'drawInfo' function
- Do a looping by using clock_t
- Take the user input
- If the user input is 'wasd', move the hero according the input by calling 'update'
- If the user input is ' ', shot te gun by calling 'shot'
- If the user input is '1', save the current condition by calling 'saveMap'
- If the user input is '2', load the board condition using 'loadMap'
- If the user input is escape, break the loop

'ValidInput', enum to indicate the input of the user.

'keyUpdate', has boolean array 'key[]' as parameter. 
When the function is called, it will set key to false. 
Then it will an element of the key array according to the input.

'isPositionValid', If the given position is not nothing, this function will return false

'clip', Have three floats as its parameters (n, minimum, maximum).
Return the biggest float between minimum and min(maximum, n)

'canSee', Have two positions (cPos, hPos) and one address of a position (dir) as its parameters.
cPos' represent the creature position, 'hPos' represent the hero position, 'dir' represents the direction.
It will set dir to a new value by calling clip and cast it to integer. When calling clip it will give the her and creature distance as n, -1.f as minimum, 1.f as maximum.
Then it has a local variables called count (0).
It will a looping as long as count is smaller than 4. 
If the creature position + dir times count equals to hero position, it will return true.
If the looping finished without returning anything, it will return false.

'setupBoard'
Allocate & init game board using 2d dynamic array
Create a 2d dynamic array to record the map is meet and innitialize the value is false.
It will generate a map using dfs
It will also setup a random valid position for hero, creatures, and triggers.

'generateMap'
If the position is out of bounds or already used, return immediately.
Set the current position as empty and mark the position direction as used.
If the opposite direction is valid and not used, set the position in the opposite direction as empty and mark the position direction as used.
Randomly choose a starting direction for the next recursive calls.
Recursively call generateMap on the positions in the next direction +0, +1, +2 and +3.

'draw', It will add the hero, triggers, and creatures to the board.
It also will update the board information according hero information.
Then it will draw the board.

'drawInfo', It will print all the hero's informations, how to move, what triggers do, and how to quit, save and load.

'update', it has boolean array 'key[]' as parameter.
It will check all the key move elements (wasd) that have true value.
If one of it has true value, it will set 'delta' according to the input, and update the hero position by calling hero's move method with delta as its parameter.
If none of the move elements are true, it will check other elements to find any true value in the array.
If none are found it will print "invalid input" and do nothing.
Then it will update all the creatures and triggers condition and call 'draw' and 'drawInfo'

'nextLevel', it will go to the next level.

'shot', It will shot the gun from four directions.
If the bullet is 0, the function will return
The bullet will -1.
When meeting the wall, the bullet will stop.

'shotCreature', It will find the creature to shot.
If finding the creature, the creature will get damage and return true.

'printTutorial', It will print the tutorial.

'saveMap', It will take the user input about the save file name.
Then it will create a txt file according to the input.
It will save all the board condition to the file.

'loadMap', It will wake the user input about the save file that the user want to open.
Then it will open the file and return if the file can't be opened.
It will update the board condition.