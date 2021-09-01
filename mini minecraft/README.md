# Mini-Minecraft
**Team JAH - Allison, Anna, and Jonas**

CIS 460/560, Professor Mally, University of Pennsylvania, School of Engineering and Applied Sciences

## Milestone 1
### Procedural Terrain (Jonas)

My approach was to write and refine my code in a Python notebook and then rewrite the logic in C++. A notebook of my Python work can be found [here](https://gist.github.com/oppenheimj/57008d578af5a41cba40492befdc186e).

The grasslands terrain is generated using two-dimensional fractal Brownian Motion (fBM) driven by a Perlin noise function. The mountain terrain is generated using Worley noise. Smooth transitions between these two biomes is achieved using another fBM function with `glm::smoothstep` applied in order to hasten the transitions from one biome to another. The end result is that 50% of the terrain is pure grassland, 40% is mountain, and the remaining 10% is transition.
 
The `ProcGen` class contains all of the logic related to procedural terrain generation. All of its methods are static because no state needs to be stored. The only public method is
```
static int getHeight(int x, int z);
```
which returns a height given `x` and `z` coordinates.

`//TODO`:
- There was a problem where rendering cubes under the surface caused a major performance hit. We think we know why this happening. We think [this](https://github.com/CIS460-Spring-2021/final-project-mini-minecraft-jah/blob/master/assignment_package/src/scene/chunk.cpp#L97) line should be changed so that it detects cubes in other chunks. This will be fixed going forward.
- Snow cubes were not added and will be added later.
- The noise will be massaged to produce more realistic terrain.


### Efficient Terrain Rendering and Chunking
CHUNK:
- created a struct storing the position of a vertex and another struct holding the direction, offset, and vertices (and their positions) that make the face of a block neighbor
- made Chunk inherit from Drawable
- implemented create() function that iterates over the x, y, z coord of chunks and iterates over the 6 adjacent block coords (from the struct) to check if they are empty. If that neighbor block is empty, VBO data is appended for each quadrangle of each empty neighbor block
- implemented loadVBO() function that takes in a vector of interleaved vertex data and a vector of index data, and buffers them into the appropriate VBOs of the Drawable
- implemented setWorldPos() function that sets the x and z world position

TERRAIN:
- changed draw() function when Chunk inherits from Drawable, so it draws each Chunk with the given ShaderProgram; set the model matrix to the proper X and Z translation
- implemented updateScene() function that updates the terrain scene given the player's position. As the player approaches 16 blocks from an edge of a Chunk that does not connect to an existing Chunk, the terrain expands

SHADERPROGRAM: 
- implemented a second drawing function drawInterleaved() for the ShaderProgram class that renders a Drawable that has been set up with interleaved VBOs
  
DIFFICULTIES: 
- had trouble displaying the correct colors properly. Fixed this by changing the given glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 1 * sizeof(glm::vec4), (void*)sizeof(glm::vec4)) in drawInterleaved() by multiplying sizeof(glm::vec4) by 3 instead of 1
- difficulties with every corner chunk missing when drawing. Fixed this by moving where I assigned color in Chunk create()
- was very confused with how terrain expansion works/what it was supposed to look like. Kept getting conflicting info so I made it expand in a way that I thought looked most intuituve. Ended up confirming with 2 TAs during OH that my terrain is correctly expanding
- Chunk create doesn't recognize that adjacent chunks of different blocks are empty so all the blocks in each chunk will be empty but not the whole terrain(TA in OH says that milestones are very relaxed though so I'll fix this bug later!!)

### Game Engine Tick Function and Player Physics
TICK: I invoked Player::tick from MyGL::tick and calculated dT using QDateTime::currentMSecsSinceEpoch() in order to make the movements smoother.

INPUTS: I edited the key and mouse events in myGL to update m_inputs when certain keys are pressed, rotate the camera on mouse movement, and to add/remove blocks on mouse clicks. I ran into an issue where the mouseMoveEvent would work find on my Mac, but it would “drift” and act weird on my partner’s Windows. We were able to resolve this issue and my partner generated some code that would work on his laptop after I explained how I calculated dx and dy using the dimensions of the screen and the position of the mouse and then reset the mouse to the center so the camera would stop moving if your mouse stopped moving.

PROCESS INPUTS/COMPUTE PHYSICS: I used the InputBundles struct to affect how the player moves in processInputs() and I updated the player’s velocity and acceleration (which I chose to be a constant 20.f) based on the inputs. I simply matched the key that was pressed to the direction I wanted to associate the key with. I differentiated between when the player is and isn’t in Flight Mode, so different keys are valid in different modes (such as space/jump only works when the player isn’t in Flight Mode). Using the inputs, I edited computePhysics() to update the player’s position based on acceleration and velocity. I first reduced the velocity by multiplying it by 0.95 in order to simulate friction and drag. I also chose to use -9.8 for gravity when jumping/falling down after turning off Flight Mode so it had a natural effect (however, this also means that you fall quite slowly from greater heights, so I’m considering making the constant larger in the future because I’m a little impatient). I had some difficultly working on the jumping function at first, but I was able to implement a function that checked if the player was on the ground (isOnGround()) and then add gravity to bring the player back down if it wasn’t on the ground and not in Flight Mode. 

COLLISIONS: In computePhysics(), I also worked with collisions by using ray casting as it was the simplest approach assuming that the cubes that make up the player are the same size as the cubes in the terrain. In order to stop the player from moving in a collision, I assigned a small epsilon value to the colliding block to act as a barrier and make the player stick to the block.

ADDING/REMOVING BLOCKS: I also used ray casting to see if any blocks intersected within 3 units of the player. If there were any blocks overlapping with the center of the screen, I would either set the block to EMPTY or STONE depending on the mouse click. However, I had some issues with this part as at first my remove function didn’t work after merging my code and both functions were adding/removing blocks in funky places (ex: I would remove the block under me and add a block under the terrain). I was able to get my removeBlock() to work on our combined code after using create() and destroy() and fixing my origin to the camera position, but my placeBlock() is still sometimes a little bit spotty (though it seems to work better on my partner’s computer, my computer is really laggy ;-;).

## Milestone 2
