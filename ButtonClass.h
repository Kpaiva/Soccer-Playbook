/*

	This class allows the creation of a Clickable Button
	
	Usable functions from this class are:

	--Button( int x, int y, int w, int h, string image)
	--Creates the button at Co-Ord X, Co-Ord Y, Collision Width, Collision Height, PathToImageForButton
	--(example: Button1(50, 50, 64, 46, "button.png") creates a button named "Button1" at X:50 Y:50 with a size of 64x46
	-- and using the image "button.png")

	--handle_events()
	--handles the inputs from the mouse and sets whether the button has been pressed or not

	--get_pressed()
	--Returns the current status of the button Pressed=true or Pressed=false

	--show()
	--uses apply_surface() from Playbook.h to apply the Button to the screen

	--set_clips(int downX, int downY, int downW, int downH, int upX, int upY, int upW, int upH)
	--Sets the Co-Ords in Pixels on the image of where (ButtonDownX, ButtonDownY, ButtonDownWidth, ButtonDownHeight,
	--ButtonUpX, ButtonUpY, ButtonUpWidth, ButtonUpHeight) are located so that the class knows which part of the image
	--to show when the Button is being pressed and when it's not.

*/


class Button 
{ 
	private: 
		//The attributes of the button 
		SDL_Rect box; 
		
		//The part of the button sprite sheet that will be shown 
		SDL_Rect* clip; 

		bool Pressed;

		SDL_Surface *ButtonSheet;

	public: 
		//Initialize the variables 
		Button( int x, int y, int w, int h, std::string image); 

		void set_clips(int downX, int downY, int downW, int downH, int upX, int upY, int upW, int upH);
		
		//Handles events and set the button's sprite region 
		void handle_events(); 
		
		//Shows the button on the screen 
		void show(); 

		bool get_pressed();

		void SetPressed(bool NewVal) {Pressed = NewVal;}

		void FreeButton() {SDL_FreeSurface(ButtonSheet);}
};

bool Button::get_pressed() {return Pressed;} //Return the status of the button Pressed=true or false

Button::Button( int x, int y, int w, int h, std::string image) 
{ 
	//Set the button's attributes 
	box.x = x; 
	box.y = y; 
	box.w = w; 
	box.h = h; 

	//load the image
	ButtonSheet = load_image( image );

	//Set the default sprite 
	clip = &clips[ CLIP_MOUSEUP ]; 
} 

void Button::handle_events() 
{ 
	//The mouse offsets 
	int x = 0, y = 0; 
	
	//If a mouse button was pressed 
	if( event.type == SDL_MOUSEBUTTONDOWN ) 
	{ 
		//If the left mouse button was pressed 
		if( event.button.button == SDL_BUTTON_LEFT ) 
		{ 
			//Get the mouse offsets 
			x = event.button.x; 
			y = event.button.y; 
			
			//If the mouse is over the button 
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) 
			{ 
				//Set the button sprite 
				clip = &clips[ CLIP_MOUSEDOWN ];

				//Change state to pressed
				Pressed = true;

			} 
		}
	}

	//If a mouse button was released 
	if( event.type == SDL_MOUSEBUTTONUP ) 
	{ 
		//If the left mouse button was released 
		if( event.button.button == SDL_BUTTON_LEFT ) 
		{ 
			//Get the mouse offsets 
			x = event.button.x; 
			y = event.button.y; 
			
			//If the mouse is over the button 
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) 
			{ 
				//Set the button sprite 
				clip = &clips[ CLIP_MOUSEUP ]; 

				//Change state back to not pressed
				Pressed = false;
			} 
		} 
	}
}

void Button::show() 
{
	//Show the button 
	apply_surfaceClip( box.x, box.y, ButtonSheet, screen, clip ); 
}

void Button::set_clips(int downX, int downY, int downW, int downH, int upX, int upY, int upW, int upH) 
{ 
	//Clip the sprite sheet by setting the co-ords and width and height values of the frames in the image
	clips[ CLIP_MOUSEDOWN ].x = downX; 
	clips[ CLIP_MOUSEDOWN ].y = downY; 
	clips[ CLIP_MOUSEDOWN ].w = downW; 
	clips[ CLIP_MOUSEDOWN ].h = downH; 
	
	clips[ CLIP_MOUSEUP ].x = upX; 
	clips[ CLIP_MOUSEUP ].y = upY; 
	clips[ CLIP_MOUSEUP ].w = upW; 
	clips[ CLIP_MOUSEUP ].h = upH; 
}