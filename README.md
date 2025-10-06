# M2OEP-tvitols-lesargen

## Lila Sargent & Tovahn Vitols

### **Summary**
Our program is an online version of the board Game Catan. Each player is working to
obtain Victory Points, with 10 being a win. To do this, they try to build Roads,
Settlements, Cities, and purchase Development Cards.

The board of Catan has 19 tiles, each having a resourceType. By placing a Building on
that tile, you gain access to that resource. Every time the Tile's key is rolled,
you will gain 1-2 of the corresponding resourceType. These resources are what you
will use to make purchases.

The game also has a Robber. Whenever a 7 is rolled, players who have 7 or more cards
will have to remove half of them (rounding down). Furthermore, the player who
rolled the 7 will get to move the Robber. By placing it on a Tile, that Tile is
unable to give resources to players, and you are able to steal one random resource
from the players on that new Tile.

You are also able to trade during the game. You can either trade with other players,
or with the bank, through the automatic 4:1 or a specific Trade you can obtain by
having a Building on a Port Vertex.

**List of Module 2 Concepts Used**
- Inheritance class relationship
- Component class relationship
- File input and/or output

### **Future Work**
Something that we are very interested in doing for future Modules is both cleaning
up the graphics and gameplay, and also looking into some of the Catan expansions, such as Seafarers,
Cities and Knights, Traders and Barbarians, and Explorers and Pirates

### **Known Bugs**

### **Citations**
Graphics (forked and lightly modified): https://github.com/lukasmatena/cppgraphics
Images of Pieces: https://github.com/BryantCabrera/Settlers-of-Catan/blob/master/resources/imgs/resources/300dpi%20unmasked/resources--%203.png

### **Grade**
**Main Program Complexity and Usability**
40 points
- Our program is extremely complex and uses many concepts from Module 2
- It also is very interactive and goes to great lengths to correctly validate user input

**Testing Program**
10 points
- the testing program does exist and tests a lot of necessary functions, however it is not super robust

**Is-A or Has-A**
AdjacencyGraph
- Has-A Edge: 20 points
- Has-A Vertex: 20 points
Board
- Has-A Tile: 20 points
Building
- Is-A Structure: 20 points
CardStack
- Has-A Card: 20 points
Deck
- Has-A Card: 20 points
Edge
- Has-A Road: 20 points
Game
- Has-A Board: 20 points
- Has-A Player: 20 points
- Has-A AdjacencyGraph: 20 points
- Has-A Deck: 20 points
KnightCard
- Is-A Card: 20 points
MonopolyCard
- Is-A Card: 10 points
- - Very similar to KnightCard
Player
- Has-A CardStack: 20 points
Port
- Is-A Vertex: 20 points
Road
- Is-A Structure: 20 points
RoadBuilding
- Is-A Card: 10 points
- - Very similar to KnightCard
Robber
- Has-A Tile: 20 points
Structure
- Has-A Player: 20 points
Tile
- Has-A Edge: 20 points
- Has-A Vertex: 20 points
Vertex
- Has-A Building: 20 points
VictoryPointCard
- Is-A Card: 20 points
YearOfPlentyCard
- Is-A Card: 20 points

**File I/O**
rules.txt: 10 points
info.txt: 10 points

**Style and Documentation**
0 points. We have commented out all classes very robustly

**Video**
0 points. We submitted a video that shows multiple runs and both user input as
well as input validation

**Lifespan of Project**
0 points. We started this project 3 weeks ago

In total, I am estimating that this Open-Ended Project is worth 510 points.