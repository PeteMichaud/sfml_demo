= Suicide Ball 

It's pong. When the ball hits your paddle, the paddle gets shorter. When you miss, the paddle gets longer. 
The goal is to disappear before your opponent

= To do

*   Particle System improvements 
    *   change shape to be arbitrary RenderableThing (ie shapes and sprites)
    *   move shape out of particle into emitter 
    *   change from array of structs to struct of arrays (for PU cache improvements)
*   Gamestates
    *   Make the game itself a gamestate
    *   Make all gamestates derive from an abstract base class
    *   get rid of that ghetto switch, replace it with a stack, so you can push and pop gamestates 
            and just loop on the top one
*   Add particle system for "people" running around the map.
    *   Implement collision detection for them, so the ball can run them over
    *   create blood stain in the direction the ball is rolling
*   Add sparks where ball hits the wall
*   Add particle effects for the sides flying off the paddle when they get hit
*   Add explosion for when ball hits paddle
*   Add shader for when ball hits paddle, paddle should be burnt
*   Add paddle graphics and background
*   polish intro and pause gamestates
*   polish win condition gamestate
