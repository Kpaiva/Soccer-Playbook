/*

	This class allows the creation of Draggable SDL_Surfaces

	Usable functions from this class are:

	--Draggable(int x, int y, int w, int h, SDL_Surface* Surf)
	--Creates object Draggable with DefaultX, DefaultY, Default Collision Width, Default Collision Height, SDL_Surface* Surface to apply
	--(example: "Draggable Object1(50, 100, 64, 64, ImageLoaded1)" creates a Draggable object named "Object1" at X:50 Y:100 with a size of 64x64
	-- and with "SDL_Surface* ImageLoaded1")

	--handle_events()
	--handles the inputs from the mouse and sets whether dragging is true or false

	--drag()
	--Called after handle_events() to actually drag the object by changing the X and Y Relative to the mouse

	--show()
	--uses apply_surface() from Playbook.h to apply the SDL_Surface to the screen

	--Reset()
	--Resets the X and Y back to Default X and Y inputed during creation

	--get_x()
	--Returns the Current X co-ord

	--get_y()
	--Returns the Current Y co-ord

	--set_x(int x)
	--Sets the X co-ord to integer passed to function

	--set_y(int y)
	--Sets the Y co-ord to integer passed to function

	--get_h()
	--Returns the Current height of the collision box

	--get_w()
	--Returns the Current width of the collision box

	--set_h(int h)
	--Sets the height of the collision box to integer passed to function

	--set_w(int w)
	--Sets the width of the collision box to integer passed to function
*/

class Draggable
{
private:
	SDL_Rect box;
	
	SDL_Surface* Surface;

	//Boolean for whether or not dragging is occuring
	bool dragging;

public:

	Draggable(int x, int y, int w, int h, SDL_Surface* Surf);

	void handle_events();

	void drag();

	void show();

	void Reset();

	//Set the x/y offsets and the width and height of the collision box
	void set_x(int x); 
	void set_y(int y);
	void set_h(int h); 
	void set_w(int w);
	
	int get_x(); 
	int get_y();
	int get_h(); 
	int get_w();

	int defaultX;
	int defaultY;

	void loadXY();

};

Draggable::Draggable(int x, int y, int w, int h, SDL_Surface* Surf)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	defaultX = x;
	defaultY = y;

	Surface = Surf;
}

void Draggable::handle_events()
{
	int x = 0;
	int y = 0;

	//If left mouse button is pressed down check if the mouse is within the collision box and if it is set dragging to true
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			x = event.button.x; 
			y = event.button.y;
		
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			{
				dragging = true;
			}
		}
	}

	//When left mouse button is released set dragging back to false
	if( event.type == SDL_MOUSEBUTTONUP ) 
	{ 
		//If the left mouse button was released 
		if( event.button.button == SDL_BUTTON_LEFT ) 
		{ 
			if (dragging == true)
			{
				dragging = false;
			}
		}
	}
}

void Draggable::drag()
{
	//If dragging is happening then check if it's within the limits of the screen and if it is set the X and Y relative
	if (dragging == true)
	{
		if (( box.y > 0 ) || ( box.y + box.h < SCREEN_HEIGHT ))
		{
			box.y += event.motion.yrel;
		}
		
		if (( box.x > 0 ) || ( box.x + box.w < SCREEN_WIDTH ))
		{
			box.x += event.motion.xrel;
		}
	}
}

void Draggable::show()
{
	//Apply the surface to the screen
	apply_surface(box.x, box.y, Surface, screen);
}

void Draggable::Reset()
{
	//Set the X and Y back to the Defaults set during creation
	box.x = defaultX;
	box.y = defaultY;
}

int Draggable::get_x()
{
	//Return Current X Co-ord
	return box.x;
}

int Draggable::get_y()
{
	//Return Current Y Co-ord
	return box.y;
}

void Draggable::set_x( int x )
{
	//Set X Co-ord of the object to integer passed
	box.x = x;
}

void Draggable::set_y( int y )
{
	//Set Y Co-ord of the object to integer passed
	box.y = y;
}

int Draggable::get_h()
{
	//Return Current Height of the of collision box
	return box.h;
}

int Draggable::get_w()
{
	//Return Current Width of the of collision box
	return box.w;
}

void Draggable::set_h( int h )
{
	//Set the Height of the collision box to integer passed
	box.h = h;
}

void Draggable::set_w( int w )
{
	//Set the Width of the collision box to integer passed
	box.w = w;
}