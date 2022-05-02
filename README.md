# Yukon Solitaire
C implementation of Yukon Solitaire, as a CLI game.

![Image of game](https://github.com/MikaelFangel/Yukon/blob/main/images/Yukon.png)

## Commands
A short description of all available commands in the game.

### Startup Phase:
 * LD \<filename\>  
This command loads a deck from the specified filename in the command (without file ending). 
The standard deck is name "default" and if no filename is specified it loads a standard deck 
of cards in the order ace, diamonds, hearts and spades where each suit is sorted in ascending order.
 * SW  
Shows all the cards on the table by turning the face-up.
 * SI \<split\>  
Shuffle the deck in an interleaved manner where the split is an optional input that tells.
how the deck should be split (allowed numbers are \]1:52\[). If no split is given the game
choose a random value to split by.
 * SR  
Shuffles the loaded deck in a random manner.
 * SD \<filename\>  
This command saves the deck currently being used. If no name is specified, a default filename 
is assigned to the deck. Otherwise, the user can optionally choose under which name they want 
to save the current deck. 

### Play Phase:
 * P  
Starts up the play phase and disables the commands from the startup phase.
 * Q  
Quits the play phase with the current deck as is.

#### Game Moves:

### General Commmands:
 * QQ  
Quits Yukon
