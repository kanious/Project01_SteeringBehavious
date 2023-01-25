1. How to build the project

- Please set "AI_01_BasicSteeringBehaviours" project as a starter project and build with x64 configuration / Debug or Release mode.
  Or you can execute with "AI_01_BasicSteeringBehaviours.exe" file in x64\Debug(or Release) folder.

- GitHub Link:
https://github.com/kanious/Project01_SteeringBehavious



2. User Input Option

- You can see all options in the UI in game.

 < For Player >
 * WASD : Move Player (look/right direction).
 * QE : Rotate Player.
 * Left Shift : Speed up/down (toggle)

 < Etc >
 * ESC : Close the program.
 * F1 : Camera Zoom In
 * F2 : Camera Zoom Out.

 < For AIs >
 * R : Reset position of all AIs
 * F3 : Active All AIs
 * F4 : Deactive All AIs
 * F5 : Active/Deactive Seek AIs (toggle)
 * F6 : Active/Deactive Flee AIs (toggle)
 * F7 : Active/Deactive Pursue AIs (toggle)
 * F8 : Active/Deactive Evade AIs (toggle)
 * F9 : Active/Deactive Approach AIs (toggle)



3. Simple Description

- Left shift changes the player's speed. At first the player is slower than the AI, pressing Left Shift makes them faster than the AI. Please use it with toggle buttons that activate/deactivate AIs for testing.

- I set the prediction distance of player position for "Pursue" and "Evade" to be quite far. Because I wanted to see the difference with "Seek" and "Flee".



4. AI Description

- Seek : Red object. Seeks player's current position if the player is not facing this AI within 90 degrees. It starts moving only when they are within a certain distance from the player.

- Flee : Blue Object. Flees from the player's current position if the player is facing this AI within 90 degrees. It starts running away when the player comes within a certain distance (A) and stops when it is a certain distance (B - farther than A) from the player.

- Pursue : Yellow Object. Pursues player's predicted position if the player is not facing this AI within 30 degrees. It starts moving only when they are within a certain distance from the player.

- Evade : Green Object. Same with "Flee" except position and degrees (predicted position and 30 degrees).

- Approach : Purple Object. Approach the player and keep a certain distance. It always moves unless deactivated.



