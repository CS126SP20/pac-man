# Development

- **4/20/20** 
    - Linked CinderBlock Choreograph to my project

- **4/21/20**
    - Created Engine, PacMan, Map, Direction, and Location classes
    - Imported gflags for use
    - Added logic: PacMan moves across the screen and map UI displays correctly;
    however, logic for collisions and movement restriction has not been added yet
    
- **4/22/20**
    - Added logic: PacMan now moves with constraints; can only move
    within the walls of the maze
    - Added a Ghost class and implemented images for each ghost
    
- **4/23/20**
    - Added UI for food; however, it has no other functions as of now and
    Pac-Man cannot interact with it
    
- **4/26/20**
    - Fixed bug that was causing the ghost to move L/R/U/D instead of U/D/L/R
    - Added some logic that allows 1 ghost to move on its own; however, still
    quite buggy so I need to smooth things out still
    
- **4/27/20**
    - Finished adding logic so now all ghosts move freely & randomly across the board
    
- **4/28/20**
    - Set up pre-game state where user must hit 'enter' to begin playing
    - Point system works correctly (10 points per food); however, food does not
    yet disappear when Pac-Man 'eats' it
    
- **4/29/20**
    - Food disappears when Pac-Man eats it
    - Displayed lives in the top left corner, also added logic that
    detects collisions between Pac-Man & ghosts. Pac-Man loses a life when
    he collides with a ghost. 
    - Also added very basic UI to display when the game is over 
    
- **5/1/20**
    - Created a Food class and FoodType enum class. Updated Map class, logic, and
    UI accordingly.
    - Added additional types of food and the behavior that corresponds with it.
        - Pacman now can 'eat' ghosts after eating 'special' food
    - Added logic so that the gate displays correctly depending on GameState
    - Added logic that resets the location of PacMan & the ghosts after 
    PacMan loses a life from colliding with a ghost
    
- **5/2/20**
    - Created a leaderboard and player class
    - Imported SQLite and used it to store, update, and display a leaderboard
    - Created UI for a home screen and leaderboard/game over screen 
    - Changed the font to an arcade font I downloaded on my computer
    - Added background music
    - Added audio for PacMan dying and eating 
    
- **5/3/20**
    - Fixed small issue with the audio when Pac-Man dies
    - Added special audio for when Pac-Man can eat ghosts
    - Added 'waka-waka' audio. Adjusted volume and logic so that the audios start 
      and stop playing at the correct times
    - Cleaned up code and added comments to files
    
    - Expanded game play so that user keeps playing until they lose all 3 lives. 
      And when the user loses and goes back to the main screen, if they press
      'enter' again, they can play a whole new game where everything (including 
      lives and score) is reset. 
      
    - Since I decided to use SQLite instead of Choreograph, I added 
      more images of Pac-Man facing other directions (left, up, down) and
      added code so that Pac-Man faces the correct direction when moving 
    
- **5/5/20**
    - Added test cases for the following classes: Engine, Food, Ghost, Leaderboard,
      Location, Map, and PacMan
---
