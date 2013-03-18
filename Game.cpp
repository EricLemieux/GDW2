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
	Map Map1("Maps\\MAP-0.txt");
	//Initialize the game with level 0 before menu before level 1)
	//currentLevel = 0;

	//Initialize the player and enemy positions
	playerCurrentPos = 0;
	enemyCurrentPos  = 0;
	targeter = false;
	
	//initial game phase is order
	gamePhase = true;
	//selectmove is false
	selectMove = false;
	resetActionList();
	isWaiting=false;
	timePassed = 0;
	actionsTaken = 5;

	int ButtonX = 636;
	int ButtonY = 70;
	for(int i = 0; i < 5; i++){
		B[i] = new Sprite("images/B2.png");  //This line, Need statement for each sprite, include outside for loop B[0], B[1] etc.
		B[i]->setNumberOfAnimations(1);
		B[i]->setSpriteFrameSize(142,57);
		B[i]->setPosition(ButtonX ,stateInfo.windowHeight - (ButtonY + i*ButtonY));
		B[i]->setLayerID(3);
		B[i]->addSpriteAnimFrame(0,0,0);
		this->addSpriteToDrawList(B[i]);
	}


	UI = new Sprite("images/BASIC_UI.png");
	UI->setNumberOfAnimations(1);
	UI->setSpriteFrameSize(800,600);
	UI->setPosition(0,0);
	UI->setLayerID(1);
	UI->addSpriteAnimFrame(0,0,0);

	this->addSpriteToDrawList(UI);

	mainchar = new Sprite("images/sprite.jpg");
	mainchar->setNumberOfAnimations(18);
	mainchar->setSpriteFrameSize(80,80);
	mainchar->setPosition(200,200);
	mainchar->setLayerID(3);
	for(int i = 0; i < 1440; i+= 80){
		mainchar->addSpriteAnimFrame(0,i,0);
	}
	mainchar->addSpriteAnimRow(1, 0,0,80, 0, 18);
	mainchar->setCurrentAnimation(1);
	this->addSpriteToDrawList(mainchar);

	attack = new Sprite("images/Marc.png");
	attack->setNumberOfAnimations(2);
	attack->setSpriteFrameSize(60,60);
	attack->setPosition(300,300);
	attack->setLayerID(3);
	for(int i = 240; i < 600; i+= 60){
		mainchar->addSpriteAnimFrame(0,i,0);
	}
	attack->addSpriteAnimRow(1, 0,0,240, 0, 6);
	attack->setCurrentAnimation(1);
	this->addSpriteToDrawList(attack);

	badchar = new Sprite("images/charactersprite2.png");
	badchar->setNumberOfAnimations(1);
	badchar->setSpriteFrameSize(24,24);
	badchar->setPosition(240,540);
	badchar->setLayerID(2);
	badchar->addSpriteAnimFrame(0,0,0);

	
	this->addSpriteToDrawList(badchar);

	bg2 = new Sprite("images/Level 1 concept.png");
	bg2->setNumberOfAnimations(1);
	bg2->setSpriteFrameSize(616,455);
	bg2->setPosition(0,600-455);
	bg2->setLayerID(1);
	bg2->addSpriteAnimFrame(0,0,0);

	this->addSpriteToDrawList(bg2);


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
		drawRectangle(true, 0,700,50,50,45.f);
		setColor(0.5,1,0.5);
		drawTriangle(true, 100,0,200,200,300,100);
	} else {
		setColor(1,0,1);
		drawRectangle(true, 0,700,50,50,45.f);
		setColor(0.5,0,0.5);
		drawTriangle(true, 100,0,200,200,300,100);
	}

	if(targeter == true)
	{
		//replace this with a target sprite
		setColor(1,0,0);
		drawCircle(50,20,input.currentX,input.currentY);
	}
	
	//testing using the nodes the user selects.
	if(nodesSelected.size() != 0)
	{
		setColor(1,1,1);
		//std::string a = std::to_string(nodesSelected.at(1));
		//std::string a = std::to_string((long)42);
		char buffer[50];
		sprintf( buffer, "%d", nodesSelected.at(1) );
		drawText(buffer,200,200);
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
	
	setLineWidth(5.f);
	setColor(1,0,0);
	drawLine(100,100,200,200);
	setLineWidth(1.f);

	
	setColor(1,1,0);
	drawRectangle(true, 200,200,50,50,45.f);

	
	setLineWidth(5.f);
	setColor(0,1,1);
	drawCircle(20, 50, 200,200);
	drawFilledCircle(20,50,500,200);
	setLineWidth(1.f);
	 
	
	setColor(0.5,0,0.5);
	drawTriangle(true, 100,100,200,200,300,100);

	
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
	UI->update();
	bg2->nextFrame();
	mainchar->update();
	badchar->update();
	attack->nextFrame();

	for(int i = 0; i < 5; i++){
		B[i]->update();
	}
	
	//if no space for actions left and in order phase
	if(gamePhase && (actionsTaken < 0)){
		gamePhase = !gamePhase;
		actionsTaken = 0;
	}

	//if execution phase then execute actions and increment counter
	if(!gamePhase){
		//hardcoded to wait
		Execute(actionlist[actionsTaken]);
		
	}

	//once all actions taken, flip gamephase and reset actions in list
	if((actionsTaken == 6)&&(!gamePhase)){
		gamePhase = !gamePhase;
		resetActionList();
	    bgm.playSound();
	}

	

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
		int ButtonX1 = 636, ButtonX2 = 783;

		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
		input.button = button;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			//if you click a button during order phase, flicker button and add wait to actionlist
			if(gamePhase){
				if((input.clickX >=ButtonX1)&&(input.clickX <= ButtonX2)){
					for(int i = 0; i < 5; i++){
						int ButtonY1 = 16 + i*70, ButtonY2 = 70*(i+1);
						if((input.clickY <= stateInfo.windowHeight-ButtonY1)&&(input.clickY >= stateInfo.windowHeight-ButtonY2)){
							B[i]->setLayerID(0);
							actionsTaken = addAction(actionsTaken,i);
						}
					}
				}
			
			
				if(targeter)
				{
				
					nodesSelected = Map1.getNodes(input.clickX, input.clickY);
					targeter = false;
				}
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
		for(int i = 0; i < 5; i++){
			B[i]->setLayerID(3);
		}
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
			
		}
	}
}

//keeps track of the mouse when it is passive.
//added by Eric
void Game::passiveMouseMoved(int x, int y)
{
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
}

//execute actions in order
void Game::Execute(int i){
	
	switch (i){
	case 0:
		timePassed += updateTimer->getElapsedTimeSeconds();
		if(timePassed>1){
			timePassed = 0;
			actionsTaken++;
		}
		break;
	case 1:
		//move
		if(Map1.canMove(playerCurrentPos,playerNewPos))
		{
			//Move the character using a 2d vector or something.
			playerCurrentPos = playerNewPos;
			actionsTaken++;
		}
		break;
	case 2:
		//capture
		for(int count = 0; count < Map1.total.size() ; count++)
		{
			if(count == playerCurrentPos)
			{
				if(Map1.total.at(count).whoControls == 0)
					Map1.total.at(count).whoControls = 1;
			}
			actionsTaken++;
		}
		break;
	case 3:
		//attack
		targeter = true;
		//TODO the attacking
		actionsTaken++;
		break;
	case 4:
		//defend
		targeter = true;
		//TODO the defending
		actionsTaken++;
		break;
	default:
		timePassed += updateTimer->getElapsedTimeSeconds();
		if(timePassed>1){
			timePassed = 0;
			actionsTaken++;
		}
	}	
}

void Game::changeLevel(int newLevel)
{
	char load[32]="Maps\\MAP-0.txt";
	load[9]=newLevel+48;
	Map newMap(load);
	currentLevel = newLevel;
	Map1 = newMap;
}