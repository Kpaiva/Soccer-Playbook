/*
	Functions in SaveFunc.h:

	--load_save(Draggable &Object, string Name)
	--Looks for string NAME in save file and loads the X and Y co-ords from it to the Object

	--save(Draggable &Object, string str_Name)
	--saves the X and Y of Object using str_Name to the end of the save file

	--saveNew(Draggable &Object, string str_Name)
	--Creates a blank save file and THEN saves the X and Y of Object using str_Name

*/

using namespace std;

bool load_save(Draggable &Object, string str_Find)
{
	//Open a file for reading 
	ifstream load( "save.sav", ios::in);
	
	//If the file loaded 
	if( load != NULL ) 
	{ 
		int offset = 0;
		bool found = false;
		string GetBuffer = " ";
		str_Find = str_Find;
		int count = 0;

		//go to Offset
		load.seekg (0, ios::beg);

		//While name provided is not found keep searching
		while (found == false)
		{

			//If reached end of file then return not loaded
			if (load.eof())
			{
				return false;
			}
			
			//get the next line and place it into the buffer
			getline(load, GetBuffer);

			//if the buffer doesn't match the name we are looking for then found = false
			if (GetBuffer != str_Find)
			{
				found = false;
			}

			//if the buffer DOES match the name we are looking for then found = true
			else if (GetBuffer == str_Find)
			{
				found = true;

				//Set the x offset 
				load >> offset; 
				Object.set_x( offset ); 

				//Set the y offset 
				load >> offset; 
				Object.set_y( offset );

		

				//If the x offset is invalid 
				if( ( Object.get_x() < 0 ) || ( Object.get_x() > SCREEN_WIDTH - Object.get_w() ) ) 
				{ 
					return false; 
				} 
				//If the y offset is invalid 
				if( ( Object.get_y() < 0 ) || ( Object.get_y() > SCREEN_HEIGHT - Object.get_h() ) ) 
				{ 
					return false; 
				}
			}

			//Incremental variable so we know how many lines have been read
			count++;

		}
	}


		//If an error occurred while trying to load data 
		if( load.fail() == true ) 
		{ 
			return false; 
		}

		//Close the file 
		load.close(); 
	
	//If everything loaded fine 
	return true;
}

void save(Draggable &Object, string str_Name)
{
	//Open a file for writing 
	std::ofstream save( "save.sav" , std::ofstream::app); 
	
	//Write offsets to the file
	save << str_Name << std::endl;
	save << Object.get_x(); 
	save << " ";
	save << Object.get_y(); 
	save << std::endl;

	//Close the file
	save.close();
}

void saveNew(Draggable &Object, string str_Name)
{
	//Open a file for writing and erase contents
	std::ofstream save( "save.sav" , std::ios::trunc); 
	
	//Write offsets to the file 
	save << str_Name << std::endl;
	save << Object.get_x(); 
	save <<  " ";
	save << Object.get_y();
	save << std::endl;

	//Close the file
	save.close();
}