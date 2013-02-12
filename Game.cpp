#include "Game.h"
#include "drawPrimitives.h"

/* this is called by std::sort to sort the list based on layerID 
 *  for drawing in the proper order 
 */
bool spriteSortingFunction(Sprite *s1, Sprite *s2)
{
	// return true if s1's layerID is less than s2's layerID
	return (s1->layerID < s2->layerID);
}

/* constructor */
Game::Game(void)
{
	/* green background */
	stateInfo.bgClearColor.red = 0;
	stateInfo.bgClearColor.green = 1;
	stateInfo.bgClearColor.blue = 0;

	/* init state */
	stateInfo.gameState = STATE_GAMEPLAY;
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");
}

/* destructor */
Game::~Game(void)
{
	/* deallocate memory and clean up here. if needed */
}

/* 
 * initializeGame()
 * - this function is called in the constructor to initialize everything related
 *   to the game, i..e loading sprites etc.
 * - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
 */
void Game::initializeGame()
{
	//initial game phase is order
	gamePhase = true;
	//selectmove is false
	selectMove = false;
	resetActionList();
	isWaiting=false;
	timePassed = 0;
	actionsTaken = 0;


	/* now let's create a sprite that has multiple rows in the sheet */
	/* here, I'm assuming they are all equally spaced on X, and Y */
	testSprite = new Sprite("images/p_Dance.png");
	int numRows = 8;
	testSprite->setNumberOfAnimations(numRows);
	testSprite->setSpriteFrameSize(110,128);
	testSprite->setPosition(400,200);
	testSprite->setLayerID(2);

	/* set up the pixel xy locations of each row */
	for(int i=0;i<numRows;i++)
	{
		float step = 110*i;
		testSprite->addSpriteAnimRow(i, 0,step, 128,0,numRows);
	}
	testSprite->setCurrentAnimation(0);
	this->addSpriteToDrawList(testSprite);


}

/* draw()
 * - this gets called automatically about 30 times per second
 * - this function just draws the sprites 
 */
void Game::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	DrawGame();
	
	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}

/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
void Game::PreDraw()
{
	/* clear the screen */
	glViewport(0,0,stateInfo.windowWidth,stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red, 
				 stateInfo.bgClearColor.green, 
				 stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // clear out the transformation matrix
	glEnable(GL_TEXTURE_2D); // turn on texturing

	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	renderingTimer->tick();


	/* sort the sprites by layerID so we draw them in the right order */
	std::sort(spriteListToDraw.begin(), spriteListToDraw.end(), spriteSortingFunction);

}

/* 
 * DrawGame()
 *  - this is the actual drawing of the current frame of the game.
 */
void Game::DrawGame()
{
	/* here is where your drawing stuff goes */
	drawSprites();

	glDisable(GL_TEXTURE_2D);
	
	if(gamePhase){
		setColor(1,1,0);
		drawRectangle(true, 0,0,50,50,45.f);
		setColor(0.5,1,0.5);
		drawTriangle(true, 100,0,200,200,300,100);
	} else {
		setColor(1,0,1);
		drawRectangle(true, 0,0,50,50,45.f);
		setColor(0.5,0,0.5);
		drawTriangle(true, 100,0,200,200,300,100);
	}

	/* this makes it actually show up on the screen */
	glutSwapBuffers();
}

/*
 * PostDraw()
 *  - in here you should clean up and set up things for the next frame
 *  - i.e. once I've used my assets, I can change them to set up things for
 *    the next frame, usually just memory management or setting up game state 
 *    boolean values etc.  
 */
void Game::PostDraw()
{
	// nothing here at the moment
}

/* drawSprites()
 * - this function is what actually draws the sprites
 *   onto the screen at their appropriate location
 * - it actually loops through a list of active sprites
 *   and then sorts them by their layerID and then draws them
 * - the sorting has to happen so that you draw from back to front
 *   just like a painter and a canvas.
 */
void Game::drawSprites()
{
	/* we could just do the following to draw the three sprites
	   but that would be silly since we have a list of sprites to draw
	   stored, so all we need to do is go through the list and draw eaach 
	   sprite in the list */
	/* // silly way 
	testSprite->draw();
	animatedSprite->draw();
	animatedSprite2->draw();
	*/
	
	/* better way */
	/* this is better because it doesn't matter how many sprites we have, they will always be drawn */
	std::vector<Sprite*>::iterator it; 
	for(it=spriteListToDraw.begin(); it != spriteListToDraw.end();it++)
	{
		Sprite *s = (*it);
		s->draw();
	}

}

/* for testing purposes to show you how to use
   the drawing primitives capabilities */
void Game::drawTestPrimitives()
{
	/* draw line */
	setLineWidth(5.f);
	setColor(1,0,0);
	drawLine(100,100,200,200);
	setLineWidth(1.f);

	/* draw rectangle */
	setColor(1,1,0);
	drawRectangle(true, 200,200,50,50,45.f);

	/* draw circle */
	setLineWidth(5.f);
	setColor(0,1,1);
	drawCircle(20, 50, 200,200);
	drawFilledCircle(20,50,500,200);
	setLineWidth(1.f);
	 
	/* draw triangle */
	setColor(0.5,0,0.5);
	drawTriangle(true, 100,100,200,200,300,100);

	/* draw text */
	setColor(1,1,1);
	drawText("HELLO WORLD",200,200);
}

/* update()
  - this function is essentially the game loop
    it gets called often and as such you
	don't actually need a "loop" to define the game
	it happens behind the scenes
  - think of this function as one iteration of the game loop
  - if you need to update physics calculations, sprite animation info,
    or sound etc, it goes in here
*/
void Game::update()
{

	// update our clock so we have the delta time since the last update
	updateTimer->tick();

	/* you should probably update all of the sprites in a list just like the drawing */
	/* maybe two lists, one for physics updates and another for sprite animation frame update */
	testSprite->nextFrame();
	//if waiting then check to see how much time is passed, once enough time set isWaiting to false
	if(isWaiting){
		timePassed = updateTimer->getElapsedTimeSeconds() + timePassed;
		if(timePassed>3)
			isWaiting = false;
	//if execution phase then execute actions and increment counter
	}else if(!gamePhase){
		//hardcoded to wait
		Execute(actionlist[actionsTaken]);
		actionsTaken++;
	}
	//once all actions taken, flip gamephase reset actions taken and actions in list
	if(actionsTaken == 6){
		actionsTaken = 0;
		gamePhase = !gamePhase;
		resetActionList();
	}

//	bg->update();
}

/* 
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
void Game::addSpriteToDrawList(Sprite *s)
{
	if(s)
	{
		/* push the sprite to the back of the list */
		this->spriteListToDraw.push_back(s);
	}
}


/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardDown()
   - this gets called when you press a key down
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		if(gamePhase)
			gamePhase = !gamePhase;
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	}
}
/* keyboardUp()
   - this gets called when you lift a key up
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	}
}

/*
 * mouseClicked
 * - this function is called when the mouse is clicked and it handles the 
 *   input state managment
 */
void Game::mouseClicked(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) 
	{
		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
		input.button = button;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			//testSprite->setPosition(input.clickX,input.clickY);
			if(input.currentX > 0 && input.currentX < 50 && input.currentY > 0 && input.currentY < 50 && !gamePhase){
				gamePhase = !gamePhase;
			}else if(input.currentX > 100 && input.currentX < 150 && input.currentY > 0 && input.currentY < 50 && gamePhase) {
				//move stuff
			}
			break;
		case GLUT_RIGHT_BUTTON:
		
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		input.mouseDown = false;
	}

}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus 
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
	
	if(input.mouseDown)
	{
		if(input.button == GLUT_LEFT_BUTTON)
		{
			testSprite->setPosition(input.currentX,input.currentY);
		}
	}
}


//execute actions in order
void Game::Execute(int i){
	
	switch (i){
	case 0:
		isWaiting = action.Wait();
		break;
	case 1:
		//move
		break;
	case 2:
		//capture
		break;
	case 3:
		//attack
		break;
	case 4:
		//defend
		break;
	default:
		action.Wait();
	}	
}