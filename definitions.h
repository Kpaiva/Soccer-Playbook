//Screen Constant Definitions
const int SCREEN_HEIGHT = 443;
const int SCREEN_WIDTH = 640;
const int FRAMES_PER_SECOND = 30;

//ButtonClip Definitions
SDL_Rect clips[ 4 ];
const int CLIP_MOUSEDOWN = 1;
const int CLIP_MOUSEUP = 2;

//Surface Definitions start
SDL_Surface *screen = NULL;
SDL_Surface *sur_Forward1 = NULL;
SDL_Surface *sur_Forward2 = NULL;
SDL_Surface *sur_Forward3 = NULL;
SDL_Surface *sur_Forward4 = NULL;

SDL_Surface *sur_Mid1 = NULL;
SDL_Surface *sur_Mid2 = NULL;
SDL_Surface *sur_Mid3 = NULL;
SDL_Surface *sur_Mid4 = NULL;

SDL_Surface *sur_Defense1 = NULL;
SDL_Surface *sur_Defense2 = NULL;
SDL_Surface *sur_Defense3 = NULL;
SDL_Surface *sur_Defense4 = NULL;

SDL_Surface *sur_Ball = NULL;

SDL_Surface *sur_Field = NULL;
//Surface Definitions End

//Event Defintion
SDL_Event event;