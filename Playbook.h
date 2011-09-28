/*
	Functions in Playbook.h:

	--SDL_Surface *load_image (filename)
	--Allows the loading of images using SDL_Image (Pure Green Transparency Set)

	--apply_surface(x, y, source, destination)
	--Draw image with no clips

	--apply_surfaceClip(x, y, source, destination, clip)
	--Draw image with Clips

	--init()
	--Intialize SDL subsystems, Set up window and screen, and set default window caption

	--SetImages()
	--Loads images into defined surfaces
*/


//Image Loading Function Start
SDL_Surface *load_image( std::string filename ) 
{ 
	
	SDL_Surface* loadedImage = NULL; //The image that's loaded 
	
	SDL_Surface* optimizedImage = NULL; //The optimized image that will be used 
	
	loadedImage = IMG_Load( filename.c_str() ); //Load the image using SDL_image 
	
	//If the image loaded 
	if( loadedImage != NULL ) 
	{
		
		optimizedImage = SDL_DisplayFormat( loadedImage ); //Create an optimized image 
		
		SDL_FreeSurface( loadedImage ); //Free the old image

		//If the image was optimized just fine 
		if( optimizedImage != NULL ) 
		{ 
			//Map the color key 
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 255, 0 );
			
			//Set all pixels of color R:0 G:255 B:0 to be transparent
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
		}
	} 
	
	//Return the optimized image 
	return optimizedImage; 

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void apply_surfaceClip( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Soccer Playbook", NULL );

    //If everything initialized fine
    return true;
}

void load_files()
{
	//Load all the images
	sur_Forward1 = load_image( "./images/Forwards/Forward1.png" );
	sur_Forward2 = load_image( "./images/Forwards/Forward2.png" );
	sur_Forward3 = load_image( "./images/Forwards/Forward3.png" );
	sur_Forward4 = load_image( "./images/Forwards/Forward4.png" );
	sur_Mid1 = load_image( "./images/Midfields/Midfield1.png" );
	sur_Mid2 = load_image( "./images/Midfields/Midfield2.png" );
	sur_Mid3 = load_image( "./images/Midfields/Midfield3.png" );
	sur_Mid4 = load_image( "./images/Midfields/Midfield4.png" );
	sur_Defense1 = load_image( "./images/Defense/Defense1.png" );
	sur_Defense2 = load_image( "./images/Defense/Defense2.png" );
	sur_Defense3 = load_image( "./images/Defense/Defense3.png" );
	sur_Defense4 = load_image( "./images/Defense/Defense4.png" );
	sur_Ball = load_image( "./images/Ball.png" );
	sur_Field = load_image( "./images/Field.png" );
}