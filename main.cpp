//Written by Kevin Paiva
//http://redwinestudio.com/

#include "SDL.h" 
#include "SDL_image.h"
#include <string>
#include <sstream>
#include <fstream>
#include "Definitions.h" //Defitions Header
#include "Playbook.h"	//Rendering and Loading Images Functions
#include "DraggableClass.h"	//Draggable Object Class
#include "ButtonClass.h"  //Button Class (ResetButton, SaveButton, LoadButton)
#include "TimerClass.h"  //A Timer Class
#include "SaveFunc.h" //Save and Load Functions

using namespace std;

void clean_up();

//Begin Main Function
int main( int argc, char* args[] ) 

{

	//Variable For Quitting
	bool quit = false;

	//Current frame 
	int frame = 0; 

	//Cap FPS or Not
	bool cap = true; 

	//The frame rate regulator 
	Timer fps;
	Timer update;


	//Start SDL
	if( init() == false )
	{
        return 1;
	}

	//Apply images to defined surfaces
	load_files();

	//Create Buttons
	Button Reset_Button(470, 250, 100, 50, "./images/ResetButton.png");
	Button Save_Button(470, 310, 100, 50, "./images/SaveButton.png");
	Button Load_Button(470, 370, 100, 50, "./images/LoadButton.png");
	
	//Create all the draggable objects
	Draggable Forward1(450, 0, 27, 29, sur_Forward1);
	Draggable Forward2(490, 0, 27, 29, sur_Forward2);
	Draggable Forward3(530, 0, 27, 29, sur_Forward3);
	Draggable Forward4(570, 0, 27, 29, sur_Forward4);

	Draggable Mid1(450, 50, 27, 29, sur_Mid1);
	Draggable Mid2(490, 50, 27, 29, sur_Mid2);
	Draggable Mid3(530, 50, 27, 29, sur_Mid3);
	Draggable Mid4(570, 50, 27, 29, sur_Mid4);

	Draggable Defense1(450, 100, 27, 29, sur_Defense1);
	Draggable Defense2(490, 100, 27, 29, sur_Defense2);
	Draggable Defense3(530, 100, 27, 29, sur_Defense3);
	Draggable Defense4(570, 100, 27, 29, sur_Defense4);

	Draggable Ball(500, 150, 40, 37, sur_Ball);
	//End Creations

	//Set ResetButton Image Clips
	Reset_Button.set_clips(0, 50, 100, 50, 0, 0, 100, 50);
	Save_Button.set_clips(0, 50, 100, 50, 0, 0, 100, 50);
	Load_Button.set_clips(0, 50, 100, 50, 0, 0, 100, 50);

	//Start FPS timer and FPS update timer
	update.start();
	fps.start(); 


	//While the user hasn't quit 
	while( quit == false ) 
	{

		while( SDL_PollEvent( &event ) ) 
		{
			//Handle all the drag events	
			Forward1.handle_events();
			Forward1.drag();
			Forward2.handle_events();
			Forward2.drag();
			Forward3.handle_events();
			Forward3.drag();
			Forward4.handle_events();
			Forward4.drag();

			Mid1.handle_events();
			Mid1.drag();
			Mid2.handle_events();
			Mid2.drag();
			Mid3.handle_events();
			Mid3.drag();
			Mid4.handle_events();
			Mid4.drag();

			Defense1.handle_events();
			Defense1.drag();
			Defense2.handle_events();
			Defense2.drag();
			Defense3.handle_events();
			Defense3.drag();
			Defense4.handle_events();
			Defense4.drag();

			Ball.handle_events();
			Ball.drag();
			
			//Check if Reset was clicked, if so Reset all Objects
			Reset_Button.handle_events();
			bool ResetYesNo = Reset_Button.get_pressed();
			if (ResetYesNo == true)
			{
				Forward1.Reset();
				Forward2.Reset();
				Forward3.Reset();
				Forward4.Reset();

				Mid1.Reset();
				Mid2.Reset();
				Mid3.Reset();
				Mid4.Reset();

				Defense1.Reset();
				Defense2.Reset();
				Defense3.Reset();
				Defense4.Reset();

				Ball.Reset();

				Reset_Button.SetPressed(false);
			}
			
			//Check if save was clicked and if so save all objects
			Save_Button.handle_events();
			bool SaveYesNo = Save_Button.get_pressed();
			if (SaveYesNo == true)
			{
				saveNew(Forward1, "F1");
				save(Forward2, "F2");
				save(Forward3, "F3");
				save(Forward4, "F4");
				save(Mid1, "M1");
				save(Mid2, "M2");
				save(Mid3, "M3");
				save(Mid4, "M4");
				save(Defense1, "D1");
				save(Defense2, "D2");
				save(Defense3, "D3");
				save(Defense4, "D4");
				save(Ball, "Bl" );

				Save_Button.SetPressed(false);
			}

			//Check if load was clicked and if so load all objects
			Load_Button.handle_events();
			bool LoadYesNo = Load_Button.get_pressed();
			if (LoadYesNo == true)
			{	
				load_save(Forward1, "F1");
				load_save(Forward2, "F2");
				load_save(Forward3, "F3");
				load_save(Forward4, "F4");
				load_save(Mid1, "M1");
				load_save(Mid2, "M2");
				load_save(Mid3, "M3");
				load_save(Mid4, "M4");
				load_save(Defense1, "D1");
				load_save(Defense2, "D2");
				load_save(Defense3, "D3");
				load_save(Defense4, "D4");
				load_save(Ball, "Bl");

				Load_Button.SetPressed(false);
			}

			//If the user has Xed out the window 
			if( event.type == SDL_QUIT ) 
			{ 
				//Quit the program 
				quit = true; 
			} 
		} 


		//Redraw the frame and all Objects
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) ); //Fill Screen Black

		apply_surface( 0, 0, sur_Field, screen );

		Forward1.show();
		Forward2.show();
		Forward3.show();
		Forward4.show();

		Mid1.show();
		Mid2.show();
		Mid3.show();
		Mid4.show();

		Defense1.show();
		Defense2.show();
		Defense3.show();
		Defense4.show();

		Ball.show();

		Reset_Button.show();
		Save_Button.show();
		Load_Button.show();

		//Refresh after redrawing
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}

		//Frame increment
		frame++;
		
		//If it's been more then 1 second since last update
		if( update.get_ticks() > 1000 )
			{
				 //The frame rate as a string
				 std::stringstream caption;

				 //Calculate the frames per second and create the string
				 caption << "Soccer Playbook | Average FPS: " << frame / ( fps.get_ticks() / 1000.f );

				 //Reset the caption
				 SDL_WM_SetCaption( caption.str().c_str(), NULL );

				 //Restart the update timer
				 update.start();
			}

		//If we want to cap the frame rate 
		if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) ) 
		{ 
			//Sleep the remaining frame time 
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); 
		} 
	}

    //Call for Clean Up function and free the button surfaces
    clean_up(); 
	Reset_Button.FreeButton();
	Save_Button.FreeButton();
	Load_Button.FreeButton();
	
	return 0; 
}

//Function For Cleaning Up at the end of execution
void clean_up()
{
    //Free the surface
    SDL_FreeSurface(sur_Forward1);
	SDL_FreeSurface(sur_Forward2);
	SDL_FreeSurface(sur_Forward3);
	SDL_FreeSurface(sur_Forward4);
	SDL_FreeSurface(sur_Mid1);
	SDL_FreeSurface(sur_Mid2);
	SDL_FreeSurface(sur_Mid3);
	SDL_FreeSurface(sur_Mid4);
	SDL_FreeSurface(sur_Defense1);
	SDL_FreeSurface(sur_Defense2);
	SDL_FreeSurface(sur_Defense3);
	SDL_FreeSurface(sur_Defense4);
	SDL_FreeSurface(sur_Ball);
	SDL_FreeSurface(sur_Field);

    //Quit SDL
    SDL_Quit();
}