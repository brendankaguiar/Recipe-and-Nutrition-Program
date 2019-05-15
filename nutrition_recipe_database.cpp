
/* -----------------------------------------------------------------------
------
FILE:              nutrtion_recipe_database.CPP

DESCRIPTION:       This databas will work with Nutrition and recipe labels. You can load labels from a file, add manually, edit, delete and more.
NOTES:             This program is helpful for those who wish to create their own recipe and nutrition lable index, You can even look up recipes
					with ingredients so you know what you can make from a shopping list of ingredients.
MODIFICATION HISTORY:
Author: Brendan Aguiar                   Date: 2019-05-06               Version: 1.02
--------------------------------------------------------------------------
--- */
//Do you need to view/edit the recipe code? Skip to line 668

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
/////////////Global constants for arrays to be passed around to the different functions
const int lcapx = 49; //Stands for labal capacity for rows subscript
const int lcapy = 150; //Stands for label capacity for the columns subscript
const int compsy = 7; //Components columns
const int stringsize = 25; //For char arrays that don't require as much space in their rows
const int stringsize2 = 50; //Gives us more space to write directions in our recipe functions
const int metricsize = 10; //Smaller space to accommadate our nutrition label metrics. Note this isn't used with the recipe metrics, which is combined with measurement
const int ingsize = 1500; //Accomadates numerous ingredients for our nutrition labels
const int numing = 10; //We can add up to 10 ingredients
const int steps = 10; //Our cook/prep function can include up to 10 steps or lines

void header()
/* -----------------------------------------------------------------------
------
FUNCTION:          header()
DESCRIPTION:       Simple header menu to select between nutrition, recipes, and quit
RETURNS:           Nothing (Void Function)
NOTES:             Unnecessary as a standalone function, but helpful for organization
--------------------------------------------------------------------------
--- */
{
	cout << "This is a database that works with recipes and nutritional information."
		<< endl << "If you'd like me to work with nutrition labels, type 1. If you would like me to work with recipes, type 2 or Type 3 to quit.\n\n";
}
//Nut in the following arrays is shorthand for nutrition. Rec is shorthand for recipes. Ing/s is shorthand for ingredient/s
void displaynutrition();
/* -----------------------------------------------------------------------
------
FUNCTION:          displaynutrition()
DESCRIPTION:       Displays the nutrition labels menu
RETURNS:           Nothing (Void Function)
NOTES:             Important for keeping the nutrition side of the program separate from the recipes
--------------------------------------------------------------------------
--- */
void disprec();
/* -----------------------------------------------------------------------
------
FUNCTION:          disprec()
DESCRIPTION:       Displays the recipes menu
RETURNS:           Nothing (Void Function)
NOTES:             Important for keeping the recipe side of the program separate from the nutrition labels
--------------------------------------------------------------------------
--- */

/////////////Nutrition sub menu's functions
void nutadd(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutadd()
DESCRIPTION:       Displays the nutrition labels add sub-menu
RETURNS:           Nothing (Void Function)
NOTES:             Important for organization and routing between adding a label manually and from a file
--------------------------------------------------------------------------
--- */
void nutedit(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutedit()
DESCRIPTION:       This function will edit a nutrition label
RETURNS:           Nothing (Void Function)
NOTES:             Arrays are processed here according to the demands needed to edit their contents
--------------------------------------------------------------------------
--- */
void nutview(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutview()
DESCRIPTION:       This function will view a nutrition label
RETURNS:           Nothing (Void Function)
NOTES:             Arrays are processed here according to the demands needed to view their contents
--------------------------------------------------------------------------
--- */
void nutdelete(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutdelete()
DESCRIPTION:       This function will delete a nutrition label
RETURNS:           Nothing (Void Function)
NOTES:             This early version will not empty an array, but assign '#' to the prefilled array.
					This is the reason we may not truly add 50 labels indiscriminately
--------------------------------------------------------------------------
--- */
int nutquit(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutquit()
DESCRIPTION:       This function will allow us to exit the nutritional side of the program
RETURNS:           quit value of 0
NOTES:			   The user is given the chance to cancel before quitting, and to save the contents of their arrays to a text file
--------------------------------------------------------------------------
--- */
//////////////Nutrition add menu's functions
void manualadd(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          manualadd()
DESCRIPTION:       This function will add a nutrition label manually
RETURNS:           Nothing (Void Function)
NOTES:             This function will allow the user to add manually and then display to the user what they inputted to confirm what they entered
--------------------------------------------------------------------------
--- */
void fileadd(int &, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]);
/* -----------------------------------------------------------------------
------
FUNCTION:          fileadd()
DESCRIPTION:       This function will add a nutrition label from a file
RETURNS:           Nothing (Void Function)
NOTES:             This function adds from a text file used as a save state for the user's work
--------------------------------------------------------------------------
--- */
//////////////Nutrition recursive function
void nutlabels(int &, char labels[][lcapy], int &);
/* -----------------------------------------------------------------------
------
FUNCTION:          nutlabels()
DESCRIPTION:       This function will display nutrition labels and get choice
RETURNS:           Nothing (Void Function)
NOTES:             Recursive function that displays all the loaded nutrition labels and prompts the user to make a selection. Passby reference
				   is used here to load the choice variable used by the edit, delete, and view functions instead of a return
--------------------------------------------------------------------------
--- */
//////////////Recipe functions
void recadd(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recadd()
DESCRIPTION:       This function will display the add recipe sub menu
RETURNS:           Nothing (Void Function)
NOTES:             As you will notice, this and other recipe functions are similar to nutrition functions for consistency and clarity.
--------------------------------------------------------------------------
--- */
void recedit(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recedit()
DESCRIPTION:       This function will edit a recipe label
RETURNS:           Nothing (Void Function)
NOTES:             Similar to nutedit(). This function has no comments to prevent redundancy. Reference nutedit() for comments. A separate array
				   function is used for recipes for readability. Otherwise these functions would have up to 16 variables to pass around
--------------------------------------------------------------------------
--- */
void recview(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recview()
DESCRIPTION:       This function will view a recipe label
RETURNS:           Nothing (Void Function)
NOTES:             Similar to nutview(). This function has no comments to prevent redundancy. Reference nutview() for comments
--------------------------------------------------------------------------
--- */
void reclookup(int &, char recipes[][stringsize], char recing[][numing][stringsize], int ings[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          reclookup()
DESCRIPTION:       This function will look up a recipe label from a list of up to 3 ingredients
RETURNS:           Nothing (Void Function)
NOTES:             This function is a good show of the program's strength by finding recipes for the user's given ingredients.
				   We could even edit the code to allow the user to choose more than 3 ingredients to find matching recipes if instructed
--------------------------------------------------------------------------
--- */
void recdelete(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recdelete()
DESCRIPTION:       This function will delete a recipe
RETURNS:           Nothing (Void Function)
NOTES:             Similar to nutdelete(). This function has no comments to prevent redundancy. Reference nutdelete() for comments
--------------------------------------------------------------------------
--- */
void recingprint(int &, char recipes[][stringsize], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], int ings[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recingprint()
DESCRIPTION:       This function will print an ingredient list
RETURNS:           Nothing (Void Function)
NOTES:             Similar to the recview() and nutview() functions, but only the ingredients are printed. For comments, view nutview()
--------------------------------------------------------------------------
--- */
int recquit(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recquit()
DESCRIPTION:       This function will quit the recipe side of the program
RETURNS:           Returns a value of 0
NOTES:             Similar to nutquit(). This function includes two additional arrays to keep track of the lines of ingredients and cook/prep
--------------------------------------------------------------------------
--- */
/////////////Recipe add menu's functions
void recmanual(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recmanual()
DESCRIPTION:       This function will add a recipe manually
RETURNS:           Nothing (Void Function)
NOTES:             Includes the tracking arrays for ingredients and cook/prep. Ingredients is given a 3rd dimension for line comparisons. The
			       measurement and metric arrays are combined into a single 3D array allowing it to be coupled with recing[][][]
--------------------------------------------------------------------------
--- */
void recfile(int &, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]);
/* -----------------------------------------------------------------------
------
FUNCTION:          recfile()
DESCRIPTION:       This function will add a recipe from file
RETURNS:           Nothing (Void Function)
NOTES:             Similar to fileadd() except the ingredient and cook/prep lines are read in for proper alignment
--------------------------------------------------------------------------
--- */
////////////Recipe recursive function
void reclabels(int &, char recipes[][stringsize], int &); 
/* -----------------------------------------------------------------------
------
FUNCTION:          reclabels()
DESCRIPTION:       This recursive function will display loaded recipes
RETURNS:           Nothing (Void Function)
NOTES:             Similar to nutlabels(). This function has no comments to prevent redundancy. Reference nutlabels() for comments
--------------------------------------------------------------------------
--- */
//////////////Main menu function
int main()
{
	int mainmenu;
	int reset = 1;

	while (reset == 1)
	{
		header();
		cin >> mainmenu;
		switch (mainmenu)
		{
		case 1:

			cout << "\nNutrition Labels Menu\n\n";
			displaynutrition();
			cout << endl << endl << endl;
			break;
		case 2:
			cout << "\nRecipes Menu\n\n";
			disprec();
			cout << endl << endl << endl;
			break;
		case 3:
			cout << "Goodbye.\n";
			reset = 0;
		}
	}

	system("PAUSE");
	return 0;
}
/////////////////////////////////////Nutrition Functions/////////////////////////////////////////////////////////////////
///////Nutrition Menu
void displaynutrition()
{
	int menuchoice;
	int go_back = 1;
	int numLabels = 0;
	char labels[lcapx][lcapy];
	int servpercontainer[lcapx];
	int measurement[lcapx][compsy];
	char metric[lcapx][compsy][metricsize];
	char ingredients[lcapx][ingsize];
	char comps[compsy][stringsize] = {
			{ 'C','A','L', 'O', 'R', 'I', 'E', 'S',},{'T','O','T','A','L',' ','F','A','T'},{'S','O','D','I','U','M'}, {'T','O','T','A','L',' ','C','A','R','B','S'},
			{'T','O','T','A','L',' ','S','U','G','A','R'},{'F','I','B','E','R'},{'P','R','O','T','I','E','N'}
	};//Nutrition components array is initialized in file making a compoinit.txt file unnecessary
	char spclabel[stringsize] = {
		'S','E','R','V','I','N','G','S',' ','P','E','R',' ','C','O','N','T','A','I','N','E','R',':', ' '
	};//Servings per container array is also initialized in program

	while (go_back != 0)
	{
		int timesleft = (50 - numLabels); //This tells us how many more times we can work with nutrition labels before the array is full
		cout << endl << "Here is the nutritional part of the program. Here, you can add, edit, delete, view, and save up to 50 labels."
			<< endl << "You may work with labels up to " << timesleft << " more times.\n"
			<< "To select from the options below, enter the corresponding number and hit enter." << endl << endl
			<< "1. Add Label" << endl << "2. Edit Label" << endl << "3. Delete Label" << endl << "4. View Products"
			<< endl << "5. Quit\n\nEnter Choice: ";
		cin >> menuchoice;
		cout << endl;
		switch (menuchoice)
		{
		case 1:
			nutadd(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
			cout << endl << endl << endl;
			break;
		case 2:
			nutedit(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
			cout << endl << endl << endl;
			break;
		case 3:
			nutdelete(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
			cout << endl << endl << endl;
			break;
		case 4:
			nutview(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
			cout << endl << endl << endl;
			break;
		case 5:
			go_back = nutquit(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel); //Will set our quit var to 0
			cout << endl << endl << endl;
			break;
		}
	}
}

////////Nutrition Sub Menu's Functions
void nutadd(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	int add_choice;
	cout << "\nWould you like to:\n"
		<< "1. Add from a file\n2. Add manually?\nType in 1 or 2 for your choice and hit enter: ";
	cin >> add_choice;
	switch (add_choice)
	{
	case 1:
		cout << endl;
		fileadd(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
		break;
	case 2:
		cout << endl;
		manualadd(numLabels, labels, servpercontainer, measurement, metric, ingredients, comps, spclabel);
		break;
	}

}
void nutedit(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	int choice = 0;
	nutlabels(numLabels, labels, choice);
	int init = (choice - 1); //Initializes correct subscript for arrays
	if (choice == 0)
	{
		cout << "Nothing to display";
	}
	else
	{
		while (labels[init][0] == '#')
		{
			if (labels[init][0] == '#')
				init--; //Decrements our initializer to realign array with the correct subscript
		}
		cout << "\nWhat is the name of the item you are editing?\n\n";
		cin.ignore(); //Gives our program a new line to encounter so it doesn't skip over our getline
		cin.getline(labels[init], lcapy);
		cout << "\nAwesome! Now tell me all of the ingredients separated by spaces.\n\n";
		cin.getline(ingredients[init], ingsize);
		cout << "\nHow many servings per container are there?\n\n";
		cin >> servpercontainer[init];
		for (int index = 0; index < compsy; index++) //Component increment
		{
			cout << "\nFor " << comps[index] << " " << endl;
			cout << "enter measurement:" << endl;
			cin >> measurement[init][index];
			cout << "now enter metric:" << endl;
			cin >> metric[init][index];
		}

		cout << endl << "Great! Now I will display the nutrition label\n";
		cout << "to confirm that I got everything correct.\n\n";
		cout << "Name: " << labels[init] << endl;
		cout << "Ingredients: " << ingredients[init] << endl;
		for (int spc = 0; spc < stringsize; spc++) //Spc stands for servings per container index. This will display "servings per container"
		{
			cout << spclabel[spc];
		}
		cout << servpercontainer[init] << endl;
		for (int index2 = 0; index2 < compsy; index2++)
		{
			cout << comps[index2] << " " << endl;
			cout << measurement[init][index2] << " " << endl;
			cout << metric[init][index2] << " " << endl;
		}
	}
}
void nutdelete(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	int certainty;
	int choice = 0;
	nutlabels(numLabels, labels, choice);
	int init = (choice - 1);

	if (choice == 0)
	{
		cout << "\nYou have no labels to delete.\n";
	}
	else
	{
		cout << "\nAre you sure you would like to delete this label? Type 1 for yes. Any other integer for no.\n";
		cin >> certainty;
		if (certainty == 1)
		{
			if (labels[init][0] == '#') //'#' used as reference to realign initializer
				init--;
			cout << "Deleting label now...\n";
			for (int dl = 0; dl < 1; dl++) //dl stands for delete label index
			{
				labels[init][dl] = '#'; //Initialized row and column of deleted label with '#' for reference used by other functions
			}
			cout << "\nLabels deleted.\n";
		}

	}
}

void nutview(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	int choice = 0;
	nutlabels(numLabels, labels, choice);
	int init = (choice - 1);
	int pfile; //Stands for print file
	ifstream fin; 
	char fname[stringsize]; //Stands for file name
	ofstream fout;

	if (choice == 0)
	{
		cout << "\nYou have no labels saved.\n";
	}
	else
	{
		if (labels[init][0] == '#')
			init--;
		cout << "\nHere is the label.\n";
		cout << endl << labels[init] << endl;
		cout << ingredients[init] << endl;
		for (int spc = 0; spc < stringsize; spc++)
		{
			cout << spclabel[spc];
		}
		cout << servpercontainer[init] << endl;
		for (int index = 0; index < compsy; index++)
		{
			cout << comps[index] << endl;
			cout << measurement[init][index] << endl;
			cout << metric[init][index] << endl;
		}
		cout << "\nWould you like me to print the label to a .txt file? Type 1 for yes or any other integer for no.\n";
		cin >> pfile;
		if (pfile == 1)
		{
			cout << "What would you like to name your file? Type the name followed by the enter key.\n";
			cin.ignore();
			cin.getline(fname,stringsize); //Allows our user to put spaces in the file name
			fin.open(fname);
			if (fin)
				cout << "\nFile created. Writing to file now.";
			fin.close();
			fout.open(fname);
			fout << labels[init] << endl;
			fout << ingredients[init] << endl;

			for (int spc2 = 0; spc2 < stringsize; spc2++)
			{
				fout << spclabel[spc2];
			}
			fout << endl << servpercontainer[init] << endl;

			for (int index2 = 0; index2 < compsy; index2++)
			{
				fout << comps[index2] << endl;
				fout << measurement[init][index2];
				fout << metric[init][index2] << endl;
			}
			fout.close();
			cout << "\nFile saved!\n";
		}
	}
}
int nutquit(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize]) //Returns 0 to sub-menu function to exit while loop
{
	int saveprogress = 0;
	int quit;
	ofstream fout;

	cout << "\nAre you sure you would like to quit? Type 0 for yes or any other integer for no.\n";
	cin >> quit;

	if (quit == 0)
	{
		if (numLabels != 0) //Only executes if a label exists
		{
			cout << "Would you like to save the labels you added? Type 1 for yes or any other integer for no.\n";
			cin >> saveprogress;
			if (saveprogress == 1)
			{
				fout.open("nutrition_labels.txt"); //File is printed on each line in a specific order so that same order is read properly by fileadd()
				cout << "Now writing data to the file.\n";
				for (int nl= 0; nl < numLabels; nl++) //nl stands for nutrition labels index
				{
					if (labels[nl][0] != '#')
					{
						fout << labels[nl] << endl;
						fout << ingredients[nl] << endl;

						for (int spc2 = 0; spc2 < stringsize; spc2++)
						{
							fout << spclabel[spc2];
						}
						fout << endl << servpercontainer[nl] << endl;

						for (int index = 0; index < compsy; index++)
						{
							fout << comps[index] << endl;
							fout << measurement[nl][index] << endl;
							if (metric[nl][index][0] == ' ')
								fout << ' ';
							if (metric[nl][index][0] != ' ')
								fout << metric[nl][index];
							if (index < (compsy - 1))
								fout << endl;
						}
						if (nl != (numLabels - 1)) //Gives a new line for each label until the last label is written. Important when reading file
							fout << endl;
					}
				}
				fout.close();
				cout << "\nFile saved!\n";
			}
		}
	}

	return quit;
}

////////////Nutrition add menu's functions
void manualadd(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	int again = 1;
	do
	{
		cout << "\nWhat is the name of the item you're adding?\n\n"; 
		cin.ignore();
		cin.getline(labels[numLabels], lcapy);
		cout << "\nAwesome! Now tell me all of the ingredients separated by spaces.\n\n";
		cin.getline(ingredients[numLabels], ingsize);
		cout << "\nHow many servings per container are there?\n\n";
		cin >> servpercontainer[numLabels];
		for (int index = 0; index < compsy; index++)
		{
			cout << "\nFor " << comps[index] << " " << endl;
			cout << "enter measurement:" << endl;
			cin >> measurement[numLabels][index];
			cout << "now enter metric:" << endl;
			cin >> metric[numLabels][index];
		}

		cout << endl << "Great! Now I will display the nutrition label\n";
		cout << "to confirm that I got everything correct.\n\n";
		cout << "Name: " << labels[numLabels] << endl;
		cout << "Ingredients: " << ingredients[numLabels] << endl;
		for (int spc = 0; spc < stringsize; spc++)
		{
			cout << spclabel[spc];
		}
		cout << servpercontainer[numLabels] << endl;
		for (int index2 = 0; index2 < compsy; index2++)
		{
			cout << comps[index2] << " " << endl;
			cout << measurement[numLabels][index2] << " " << endl;
			cout << metric[numLabels][index2] << " " << endl;
		}
		cout << "Would you like to add another? Press 1 and enter to add another or any other integer to quit.\n";
		cin >> again;
		numLabels++; //Incremenent numLabels array to enter additional labels when loop repeats

	} while (again == 1); //Post test loop to confirm if additional labels would like to be added
}

void fileadd(int &numLabels, char labels[][lcapy], int servpercontainer[], int measurement[][compsy], char metric[][compsy][metricsize], char ingredients[][ingsize], char comps[][stringsize], char spclabel[stringsize])
{
	ifstream fin;
	char junk[ingsize];
	fin.open("nutrition_labels.txt");
	cout << "\nNow reading data from the file.\n";
	if (fin)
	{
		while (fin.getline(labels[numLabels], lcapy)) //Executes loop while a line could be read into the array
		{
			fin.getline(ingredients[numLabels], ingsize);
			fin.getline(junk, ingsize); //One dimensional array does not require a new set of rows as it's only in place to skip the line
			fin >> (servpercontainer[numLabels]);
			for (int cs = 0; cs < compsy; cs++)
			{
				fin.ignore();
				fin.getline(junk, ingsize); //Loads array with junk to skip line. We already have prefilled component arrays to reference in other parts of code
				fin >> measurement[numLabels][cs];
				fin >> metric[numLabels][cs], metricsize;
			}
			fin.ignore();
			numLabels++; //Increments for each nutrition label added
		}
	}
	else
		cout << "No file to display here.\n";
}

///////Nutrition Recursive Labels function
void nutlabels(int  &numLabels, char labels[][lcapy], int &choice)
{

	int displaychoice = 1;
	int nochoice = 1; //Used to send back a choice of 0 to indicate no labels are available to choose from
	int poundfactor = 0;
	int choicefactor;
	bool cfactor = false; //Critical for aligning our labels correctly
	int cf = 0;
	if (numLabels == 0)
	{
		cout << "\nYou have no labels saved.\n";
		choice = 0;
	}
	else
	{
		for (int index = 0; index < numLabels; index++)
		{
			if (labels[index][0] == '#') //This statement allows us to account for deleted labels when sending back our choice
				poundfactor++;
			if (labels[index][0] != '#') //The pound sign prevents the display of deleted labels.
			{
				cout << displaychoice << ". " << labels[index];
				cout << endl;
				displaychoice++;
			}
		}

		if (displaychoice == nochoice) //This is used with if/else to prevent the display of labels deleted in program 
		{
			cout << "\nYou deleted all your labels.\n";
			choice = 0;
		}
		else
		{
			cout << "\nHere are the labels. Type the corresponding number to select the label.\n";
			cin >> choicefactor;
			for (int c = 0; c < choicefactor; c++) //c stands for choicefactor index
			{
				if (labels[c][0] == '#')
					cf++;
			}
			if (cf > 0)
				cfactor = true;
			if (cfactor == false)
				choice = choicefactor;
			else if (cfactor == true) //Implements when deleted labels need to be accounted for
				choice = choicefactor + poundfactor;
		}
	}
}
/////////////////////////////////////////////////Recipe Functions///////////////////////////////////////////////////////////////////////////
////Display recipe function
void disprec()
{
	int menuchoice;
	int go_back = 1;
	int numrecipes = 0;
	char recipes[lcapx][stringsize]; //Here, I'm reusing the nutrition label dimensional capacities. I reuse others as well for simplicity
	char recmeasure[lcapx][numing][stringsize]; //X marks recipe, y marks the ingredient, z contains the measurement and metric
	char recing[lcapx][numing][stringsize]; //X marks ingredient and y marks the size of each ingredient string
	char cookprep[lcapx][steps][stringsize2]; //This array will give us a combined cook and prep time. steps can provide new lines for readability
	int servperrec[lcapx]; //Servings per recipe
	int ings[lcapx]; ////These next two lines prevent our array columns from overincrementing. An increment integer can be assigned for up to 50 labels
	int cpy[lcapx];/////cpy stands for cook prep y or columns, ings for ingredients. Both arrays are passed throughout the recipe functions

	char spcrec[stringsize] = {
		'S','E','R','V','I','N','G','S',' ','P','E','R',' ','R','E','C','I','P','E',' '
	};//Servings per container array changed to servings per recipe for recipes portion

	while (go_back != 0)
	{
		int timesleft = (50 - numrecipes);
		cout << endl << "Here is the recipe part of the program. Here, you can add, edit, delete, view, and save up to 50 recipes."
			<< endl << "You may work with recipes up to " << timesleft << " more times.\n"
			<< "To select from the options below, enter the corresponding number and hit enter." << endl << endl
			<< "1. Add Recipe" << endl << "2. Edit Recipe" << endl << "3. Delete Recipe" << endl << "4. View Recipe"
			<< endl << "5. Lookup Recipe" << endl << "6. Print Ingredient List" << endl << "7. Quit\n\nEnter Choice: ";
		cin >> menuchoice;
		cout << endl;
		switch (menuchoice)
		{
		case 1:
			recadd(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
			cout << endl << endl << endl;
			break;
		case 2:
			recedit(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
			cout << endl << endl << endl;
			break;
		case 3:
			recdelete(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
			cout << endl << endl << endl;
			break;
		case 4:
			recview(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
			cout << endl << endl << endl;
			break;
		case 5:
			reclookup(numrecipes, recipes, recing, ings);
			cout << endl << endl << endl;
			break;
		case 6:
			recingprint(numrecipes, recipes, recmeasure, recing, ings);
			cout << endl << endl << endl;
			break;
		case 7:
			go_back = recquit(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
			cout << endl << endl << endl;
			break;
		}
	}
}

////////Recipe sub menu's functions
void recadd(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	int add_choice;
	cout << "\nWould you like to:\n"
		<< "1. Add from a file\n2. Add manually?\nType in 1 or 2 for your choice and hit enter: ";
	cin >> add_choice;
	switch (add_choice)
	{
	case 1:
		cout << endl;
		recfile(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
		break;
	case 2:
		cout << endl;
		recmanual(numrecipes, recipes, servperrec, recmeasure, recing, spcrec, cookprep, ings, cpy);
		break;
	}
}
////////////Recipe add menu's functions
void recmanual(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	int again = 1;
	int inginc;
	int stepinc;
	do
	{
		cout << "\nWhat is the name of the recipe you're adding?\n\n"; 
		cin.ignore();
		cin.getline(recipes[numrecipes], stringsize);
		cout << "\nHow many ingredients are in this recipe?\n";
		cin >> inginc; //Keeps our ingredient for loops from overrloading. Inc stands for increment
		ings[numrecipes] = inginc;
		cout << "This is an array with " << ings[numrecipes] << " steps for recipe number " << numrecipes << endl;
		cout << "\nAwesome! Now tell me all of the ingredients separated by enter.\n\n";
		cin.ignore();
		for (int ni = 0; ni < inginc; ni++) //Stands for number of ingredients increment index
		{
			cin.getline(recing[numrecipes][ni], stringsize);
		}
		cout << "\nHow many servings are there in this recipe?\n\n";
		cin >> servperrec[numrecipes];
		cin.ignore();
		for (int index = 0; index < inginc; index++) //Using ingredient increment for correct load
		{
			cout << "\nFor " << recing[numrecipes][index] << " " << endl;
			cout << "enter measurement (format e.g. 1/2 cups):" << endl;
			cin.getline(recmeasure[numrecipes][index], stringsize);
		}
		cout << "\nLastly, lets go through the directions. You may use to 10 lines for your recipe. How many steps or lines will you use up?\n";
		cin >> stepinc; //Gives us multiple columns to type out all our steps or directions on different lines. Inc stands for increment
		cpy[numrecipes] = stepinc;
		cout << "This is an array with " << cpy[numrecipes] << " lines for recipe number " << numrecipes << endl;

		cout << "\nNow input each step followed by enter, or type enter to start a new line.\n";
		cin.ignore();
		for (int si = 0; si < stepinc; si++) //Using step increment for correct load. si stands for step increment index
		{
			cin.getline(cookprep[numrecipes][si], stringsize2);
		}

		cout << endl << "Great! Now I will display the recipe label\n";
		cout << "to confirm that I got everything correct.\n\n";
		cout << "Name: " << recipes[numrecipes] << endl;
		cout << "Ingredients and measurement:\n";
		for (int ni2 = 0; ni2 < inginc; ni2++) //Number of ingredients index 2
		{
			cout << recing[numrecipes][ni2] << endl;
			cout << recmeasure[numrecipes][ni2] << endl;
		}

		for (int spc = 0; spc < stringsize; spc++)
		{
			cout << spcrec[spc];
		}
		cout << servperrec[numrecipes] << endl;
		cout << "Cook/Prep directions:\n";
		for (int si = 0; si < stepinc; si++)
		{
			cout << cookprep[numrecipes][si] << endl;
		}
		cout << "Would you like to add another? Press 1 and enter to add another or any other integer to quit.\n";
		cin >> again;
		numrecipes++;

	} while (again == 1);
}

void recfile(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	ifstream fin;
	char junk[ingsize];
	fin.open("recipe_labels.txt");
	cout << "\nNow reading data from the file.\n";
	if (fin)
	{
		while (fin.getline(recipes[numrecipes], stringsize))
		{
			fin >> (ings[numrecipes]); //Reads in correct ingredient increment for the for loop
			fin >> (cpy[numrecipes]); //Reads in correct directions increment for the for loop
			fin.ignore();
			int inginc = ings[numrecipes];
			int stepinc = cpy[numrecipes];
			for (int index = 0; index < inginc; index++)
			{
				fin.getline(recing[numrecipes][index], stringsize, '\n');
				fin.getline(recmeasure[numrecipes][index], stringsize);
			}
			fin.getline(junk, ingsize); //One dimensional array does not require a new set of rows as it's only in place to skip the line
			fin >> (servperrec[numrecipes]);
			fin.ignore();
			for (int si = 0; si < stepinc; si++) 
			{
				fin.getline(cookprep[numrecipes][si], stringsize2); //Getline not needed as we won't be inputting any spaces
			}
			fin.getline(junk, ingsize);
			numrecipes++;
		}
	}
	else
		cout << "No file to display here.\n";
}

int recquit(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[]) //Returns 0 to sub-menu function to exit while loop
{
	int saveprogress = 0;
	int quit;
	ofstream fout;

	cout << "\nAre you sure you would like to quit? Type 0 for yes or any other integer for no.\n";
	cin >> quit;

	if (quit == 0)
	{
		if (numrecipes != 0)
		{


			cout << "Would you like to save the labels you added? Type 1 for yes or any other integer for no.\n";
			cin >> saveprogress;
			if (saveprogress == 1)
			{
				fout.open("recipe_labels.txt");
				cout << "Now writing data to the file.\n";
				for (int rl = 0; rl < numrecipes; rl++) //rl stands for number of recipe labels index 
				{
					if (recipes[rl][0] != '#') //Prevents us from writing deleted labels
					{
						fout << recipes[rl] << endl;
						fout << ings[rl] << endl; //Crucial step for when reading file. Allows us to know how many ingredients need to be read in
						fout << cpy[rl] << endl;//Crucial step for when reading file. Allows us to know how many directions need to be read in
						int inginc = ings[rl];
						int stepinc = cpy[rl]; //Loads our variable with the correct recipe subscript
						for (int index = 0; index < inginc; index++)
						{
							fout << recing[rl][index] << endl;
							fout << recmeasure[rl][index] << endl;
						}
						for (int spc2 = 0; spc2 < stringsize; spc2++)
						{
							fout << spcrec[spc2];
						}
						fout << endl << servperrec[rl] << endl;
						for (int index2 = 0; index2 < stepinc; index2++)
						{
							fout << cookprep[rl][index2] << endl;
						}
						if (rl != (numrecipes - 1)) //Gives a new line for each recipe until the last recipe is written. Important when reading file
							fout << endl;
					}
				}
				fout.close();
				cout << "\nFile saved!\n";

			}
		}
	}

	return quit;
}

void recedit(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	int choice = 0;
	reclabels(numrecipes, recipes, choice);
	int init = (choice - 1);
	int inginc;
	int stepinc;
	if (choice == 0)
	{
		cout << "Nothing to display";
	}
	else
	{
		while (recipes[init][0] == '#')
		{
			if (recipes[init][0] == '#')
				init--;
		}
		cout << "\nWhat is the name of the item you are editing?\n\n";
		cin.ignore();
		cin.getline(recipes[init], stringsize);
		cout << "\nHow many ingredients are in this recipe?\n";
		cin >> inginc;
		ings[init] = inginc;
		cout << "\nAwesome! Now tell me all of the ingredients separated by enter.\n\n";
		cin.ignore();
		for (int ni = 0; ni < inginc; ni++)
		{
			cin.getline(recing[init][ni], stringsize);
		}
		cout << "\nHow many servings are there in this recipe?\n\n";
		cin >> servperrec[init];
		cin.ignore();
		for (int index = 0; index < inginc; index++)
		{
			cout << "\nFor " << recing[init][index] << " " << endl;
			cout << "enter measurement (format e.g. 1/2 cups):" << endl;
			cin.getline(recmeasure[init][index], stringsize);
		}
		cout << "\nLastly, lets go through the directions. You may use to 10 lines for your recipe. How many steps or lines will you use up?\n";
		cin >> stepinc;
		cpy[init] = stepinc;
		cout << "\nNow input each step followed by enter, or type enter to start a new line.\n";
		cin.ignore();
		for (int si = 0; si < stepinc; si++)
		{
			cin.getline(cookprep[init][si], stringsize2);
		}

		cout << endl << "Great! Now I will display the recipe label\n";
		cout << "to confirm that I got everything correct.\n\n";
		cout << "Name: " << recipes[init] << endl;
		cout << "Ingredients and measurement:\n";
		for (int ni2 = 0; ni2 < inginc; ni2++)
		{
			cout << recing[init][ni2] << endl;
			cout << recmeasure[init][ni2] << endl;
		}
		for (int spc = 0; spc < stringsize; spc++)
		{
			cout << spcrec[spc];
		}
		cout << servperrec[init] << endl;
		cout << "Cook/Prep directions:\n";
		for (int si = 0; si < stepinc; si++)
		{
			cout << cookprep[init][si] << endl;
		}
	}
}
void recdelete(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	int certainty;
	int choice = 0;
	reclabels(numrecipes, recipes, choice);
	int init = (choice - 1);

	if (choice == 0)
	{
		cout << "\nYou have no labels to delete.\n";
	}
	else
	{
		cout << "\nAre you sure you would like to delete this label? Type 1 for yes. Any other integer for no.\n";
		cin >> certainty;
		if (certainty == 1)
		{
			if (recipes[init][0] == '#')
				init--;
			cout << "Deleting label now...\n";
			for (int dl = 0; dl < 1; dl++)
			{
				recipes[init][dl] = '#';
			}
			cout << "\nLabels deleted.\n";
		}

	}
}
void reclookup(int & numrecipes, char recipes[][stringsize], char recing[][numing][stringsize], int ings[])//Cook prep and servings array are unnecessary here
{
	int amount;
	int init;//Allows us to display array only when ingredients match
	cout << "\nHow many ingredients would you like to look up? You may search with up to 3 ingredients. Type amount then hit enter.\n";
	cin >> amount;
	int left = amount; //Informs user how many more ingredients they may look up for each recipe
	char ingchoice[2][stringsize]; //The user fills this array and it is compared with the recipe ingredients (recing[][][]) array
	cin.ignore();
	int inginc;
	int i = 0; //This integer index goes through the rows of the ingredient choice and recipe ingredient arrays for comparison
	for (int index = 0; index < amount; index++)
	{
		cout << "\nYou have " << left << " left. Input the ingredient and hit enter.\n";
		left--;
		cin.getline(ingchoice[index], stringsize);
	}

	for (int rl = 0; rl < numrecipes; rl++)
	{
		if (recipes[rl][0] != '#')//recipes[][] is still needed here to prevent the comparison of deleted labels
		{
			init = 0;
			inginc = ings[rl]; //Set the correct increment
			for (int ni = 0; ni < inginc; ni++)
			{
				for (int index2 = 0; index2 < amount; index2++)
				{
					i = 0; //String index
					while ((ingchoice[index2][i] == recing[rl][ni][i]) && ingchoice[index2][i] != '\0' && recing[rl][ni][i] != '\0')
					{
						i++;
					}
					if (ingchoice[index2][i] == '\0' && recing[rl][ni][i] == '\0')
						init++; //If there is a match, the initializer is incremented
				}
			}
			if (init == amount) //If the the initializer matches the amount for each recipe, then the conditions are met and the recipe is diplayed
				cout << recipes[rl] << " has the ingredients you're looking for." << endl;
		}
	}
}
void recingprint(int & numrecipes, char recipes[][stringsize], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], int ings[])
{
	int choice = 0;
	reclabels(numrecipes, recipes, choice);  //recipes[][] and numrecipes[] is still needed in this function to correctly align our initializer
	int init = (choice - 1);
	int inginc = ings[init];
	ifstream fin;
	char fname[stringsize];
	ofstream fout;

	if (choice == 0)
	{
		cout << "\nYou have no labels saved.\n";
	}
	else
	{
		if (recipes[init][0] == '#') 
			init--;
		cout << "What would you like to name your file? Type the name followed by the enter key.\n";
		cin.ignore();
		cin.getline(fname, stringsize);
		fin.open(fname);
		if (fin)
			cout << "\nFile created. Writing to file now.\n";
		fin.close();
		fout.open(fname);
		for (int index = 0; index < inginc; index++)
		{
			fout << recing[init][index];
			fout << " " << recmeasure[init][index] << endl;
		}
		fout.close();
		cout << "\nFile saved!\n";		
	}
}
void recview(int & numrecipes, char recipes[][stringsize], int servperrec[], char recmeasure[][numing][stringsize], char recing[][numing][stringsize], char spcrec[stringsize], char cookprep[][steps][stringsize2], int ings[], int cpy[])
{
	int choice = 0;
	reclabels(numrecipes, recipes, choice);
	int init = (choice - 1);
	int inginc = ings[init];
	int stepinc = cpy[init];
	int pfile;
	ifstream fin;
	char fname[stringsize];
	ofstream fout;

	if (choice == 0)
	{
		cout << "\nYou have no labels saved.\n";
	}
	else
	{
		if (recipes[init][0] == '#')
			init--;
		cout << "Name: " << recipes[init] << endl;
		for (int spc = 0; spc < stringsize; spc++)
		{
			cout << spcrec[spc];
		}
		cout << servperrec[init] << endl;
		cout << "Cook/Prep directions:\n";
		for (int si = 0; si < stepinc; si++)
		{
			cout << cookprep[init][si] << endl;
		}
		cout << "Ingredients and measurement:\n";
		for (int ni2 = 0; ni2 < inginc; ni2++)
		{
			cout << recing[init][ni2] << endl;
			cout << recmeasure[init][ni2] << endl;
		}
		cout << "\nWould you like me to print the label to a .txt file? Type 1 for yes or any other integer for no.\n";
		cin >> pfile;
		if (pfile == 1)
		{
			cout << "What would you like to name your file? Type the name followed by the enter key.\n";
			cin.ignore();
			cin.getline(fname, stringsize);
			fin.open(fname);
			if (fin)
				cout << "\nFile created. Writing to file now.";
			fin.close();
			fout.open(fname);
			fout << recipes[init] << endl;
			for (int i = 0; i < inginc; i++)
			{
				fout << recing[init][i] << endl;
				fout << recmeasure[init][i] << endl;
			}
			for (int spc2 = 0; spc2 < stringsize; spc2++)
			{
				fout << spcrec[spc2];
			}
			fout << endl << servperrec[init] << endl;
			for (int index2 = 0; index2 < stepinc; index2++)
			{
				fout << cookprep[init][index2] << endl;
			}
			fout.close();
			cout << "\nFile saved!\n";
		}
	}
}
void reclabels(int & numrecipes, char recipes[][stringsize], int & choice)
{

	int displaychoice = 1;
	int nochoice = 1;
	int poundfactor = 0;
	int choicefactor;
	bool cfactor = false;
	int cf = 0;
	if (numrecipes == 0)
	{
		cout << "\nYou have no labels saved.\n";
		choice = 0;
	}
	else
	{
		for (int index = 0; index < numrecipes; index++)
		{
			if (recipes[index][0] == '#')
				poundfactor++;
			if (recipes[index][0] != '#')
			{
				cout << displaychoice << ". " << recipes[index];
				cout << endl;
				displaychoice++;
			}
		}

		if (displaychoice == nochoice) 
		{
			cout << "\nYou deleted all your labels.\n";
			choice = 0;
		}
		else
		{
			cout << "\nHere are the labels. Type the corresponding number to select the label.\n";
			cin >> choicefactor;
			for (int c = 0; c < choicefactor; c++)
			{
				if (recipes[c][0] == '#')
					cf++;
			}
			if (cf > 0)
				cfactor = true;
			if (cfactor == false)
				choice = choicefactor;
			else if (cfactor == true)
				choice = choicefactor + poundfactor;
		}
	}
}
