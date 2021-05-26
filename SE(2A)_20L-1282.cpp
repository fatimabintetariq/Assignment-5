#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>

#define ROWS 19
#define COLS 19
//Global variable

using namespace std;



int StringLength(char* str)
{
	int length = 0;
	for (char* temp = str; *temp != '\0'; temp++)
		length++;

	return length;
}

char* GetStringFromBuffer(char* buffer)
{
	int strLen = StringLength(buffer);
	char* str = NULL;

	if (strLen > 0)
	{
		str = new char[strLen + 1];
		char* tempStr = str;
		for (char* tempBuffer = buffer; *tempBuffer != '\0'; tempBuffer++)
		{
			if (*tempBuffer != ' ')
				*(tempStr++) = toupper(*tempBuffer);
		}
		*tempStr = '\0';
	}
	return str;
}

char** Input(ifstream& fin, char** List_of_Words, int TotalWords)
{
	char temp[40];
	for (int i = -1; i < TotalWords + 1; i++)
	{
		fin.getline(temp, 40);
		int len = strlen(temp);
		List_of_Words[i] = new char[len + 1];
		List_of_Words[i] = GetStringFromBuffer(temp);
	}
	return List_of_Words;
}

int Max_Length_Of_Word(char** List_of_Words, int TotalWords)
{ 
	int word_length = 0;
	word_length = strlen(List_of_Words[1]);

	for (int i = 1; i < TotalWords; i++)
	{
		if (word_length < strlen(List_of_Words[i]))
			word_length = strlen(List_of_Words[i]);
	}
	return word_length;
}

char** Default(int TotalWords, char** Grid, char** List_of_Words)
{
	int word_length = Max_Length_Of_Word(List_of_Words, TotalWords);
	

	Grid = new char* [word_length];
	for (int i = 0; i < word_length; i++)
		Grid[i] = new char[word_length];

	for (int i = 0; i < word_length; i++)
		for (int j = 0; j < word_length; j++)
			Grid[i][j] = '-';

	return Grid;
}

void PrintGrid(ofstream &fout, int word_length, char** Grid)
{
	for (int i = 0; i < word_length; i++)
	{
		for (int j = 0; j < word_length; j++)
		{
			fout << Grid[i][j] << " ";
			cout << Grid[i][j] << " ";
		}
		fout << endl;
		cout << endl;
	}
}

char** Sort_Array(int TotalWords, char** List_of_Words) //sorts it in a descending order
{
	int word_length = Max_Length_Of_Word(List_of_Words, TotalWords);

	for (int i = 0; i < TotalWords; i++)
	{
		if (word_length < strlen(List_of_Words[i]))
			word_length = strlen(List_of_Words[i]);
	}
	char* temp = 0;
	for (int i = 0; i < TotalWords - 1; i++)
	{
		for (int j = 0; j < TotalWords - i - 1; j++)
		{
			if (strlen(List_of_Words[j]) < strlen(List_of_Words[j + 1]))
			{
				temp = List_of_Words[j];
				List_of_Words[j] = List_of_Words[j + 1];
				List_of_Words[j + 1] = temp;
			}
		}
	}
	return  List_of_Words;
}

bool searchForHorizontalLtoR(char** Grid, char* str, int max, int row, int col)
{
	if (col + StringLength(str) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(str); i++, col++)
	{
		if (str[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForHorizontalRtoL(char** Grid, char* tempArr, int max, int row, int col)
{
	if (col - StringLength(tempArr) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++, col--)
	{
		if (tempArr[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForVerticalTtoB(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row + StringLength(tempArr) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++, row++)
	{
		if (tempArr[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForVerticalBtoT(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row - StringLength(tempArr) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++, row--)
	{
		if (tempArr[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForDownwardDiagonalLtoR(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row + StringLength(tempArr) > max || col + StringLength(tempArr) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++)
	{
		if (tempArr[i] == Grid[row + i][col + i] || Grid[row + i][col + i] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForDownwardDiagonalRtoL(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row + StringLength(tempArr) > max || col - StringLength(tempArr) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++)
	{
		if (tempArr[i] == Grid[row + i][col - i] || Grid[row + i][col - i] == '-')
			temp = true;
		else
			return false;
	}
	return temp;
}

bool searchForUpwardDiagonalLtoR(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row - StringLength(tempArr) + 1 < 0 || col + StringLength(tempArr) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++)
	{
		if (tempArr[i] == Grid[row - i][col + i] || Grid[row - i][col + i] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool searchForUpwardDiagonalRtoL(char** Grid, char* tempArr, int max, int row, int col)
{
	if (row - StringLength(tempArr) + 1 < 0 || col - StringLength(tempArr) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArr); i++)
	{
		if (tempArr[i] == Grid[row - i][col - i] || Grid[row - i][col - i] == '-')
			temp = true;
		else
			return false;
	}
	return temp;
}

void grid_form(int word_length, int TotalWords, char** List_of_Words, char** Grid)
{
	int row, col, direction, Total_directions = 8, count = TotalWords;
	srand(time(0));
	int i = 0;
	while (count != 0)
	{
		row = rand() % word_length + 0;
		col = rand() % word_length + 0;
		direction = rand() % Total_directions + 1;

		switch (direction)
		{
		case 1:
			if (searchForDownwardDiagonalLtoR(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];
				for (int j = 0; j < StringLength(List_of_Words[i]); j++)
				{
					if (Grid[row + j][col + j] == '-')
						List_of_Words[row + j][col + j] = temp[j];	
				}
				count--;
				i++;				
			}
			break;
		case 2:
			if (searchForUpwardDiagonalLtoR(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];
				for (int j = 0; j < StringLength(List_of_Words[i]); i++)
				{
					if (Grid[row - j][col + j] == '-')
						Grid[row - j][col + i] = temp[j];
				}				
				count--;
				i++;
			}
			break;
		case 3:
			if (searchForDownwardDiagonalRtoL(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];		
				for (int j = 0; j < strlen(temp); j++)
				{
					if (Grid[row + j][col - j] == '-')
						Grid[row + j][col - j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 4:
			if (searchForUpwardDiagonalRtoL(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];			
				for (int j = 0; j < strlen(temp); j++)
				{
					if (Grid[row - j][col - i] == '-')
						Grid[row - j][col - j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 5:
			if (searchForVerticalBtoT(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];	
				for (int j = 0; j < StringLength(temp); j++)
				{
					if (Grid[row - j][col] == '-')
						Grid[row - j][col] = temp[i];
				}	
				count--;
				i++;
			}
			break;
		case 6:
			if (searchForHorizontalRtoL(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];
				for (int j = 0; j < StringLength(temp); j++)
				{
					if (Grid[row][col + j] == '-')
						Grid[row][col + j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 7:
			if (searchForHorizontalRtoL(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];
				for (int j = 0; j < StringLength(List_of_Words[i]); j++)
				{
					if (Grid[row][col - j] == '-')
						Grid[row][col - j] = temp[j];
				}
				i++;
				count--;

			}
			break;
		case 8:
			if (searchForVerticalTtoB(Grid, List_of_Words[i], word_length, row, col))
			{
				char* temp = List_of_Words[i];

				for (int j = 0; j < StringLength(List_of_Words[i]); j++)
				{
					if (Grid[row + j][col] == '-')
						Grid[row + j][col] = temp[j];
				}
				i++;
				count--;
			}
			break;
		default:
			break;
		}
	}

	srand(time(NULL));
	srand(rand());
	for (int i = 0; i < word_length; i++) //used to generate random words
	{
		for (int j = 0; j < word_length; j++)
		{
			if (Grid[i][j] == '-')
			{
				int letters = 90 - (rand() % 26);
				Grid[i][j] = letters;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------
struct gridData
{
    string word;
    int row;
    int col;

    bool L_to_R,R_to_L,T_to_B,B_to_T;
    bool found;

    void initialize()
    {
        L_to_R = false;
        R_to_L = false;
        T_to_B = false;
        B_to_T = false;
        found = false;

    }
};

void getGrid(char grid[][COLS])
{
    ifstream inputfile;
    inputfile.open("Input2.txt");
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            inputfile >> grid[row][col];
        }
    }
    inputfile.close();
}

void printGrid(char grid[][COLS])
{
    ofstream OutputFile;
	OutputFile.open("Output2.txt");
    int rowNum = 0;
    int colNum = 0;
    rowNum = 0;
    OutputFile << endl;

    for(int row = 0; row < COLS - 1; row++)
    {
        colNum++;
        for(int col = 0; col < ROWS; col++)
        {
            OutputFile << grid[row][col] << " ";
            cout << grid[row][col] << " ";
        }
        OutputFile << endl;
        cout << endl;
    }

    OutputFile << "   ";
    OutputFile << endl;
    cout << "   ";
    cout << endl;
}

bool searchForHorizontalLtoR(char grid[][COLS], struct gridData &Data)
{
    char GridRow[ROWS];
    int row = 0;

    while(row < ROWS)
    {
        for(int n = 0; n < ROWS; n++)
        {
            GridRow[n] = grid[row][n];
        } //loads the next row of matrix for searching
        for(int i = 0; i < (ROWS - Data.word.size()); i++)
        {
            int j = 0;
            while((j < Data.word.size()) && (Data.word[j] == GridRow[i+j]))
            {
                j++;
            }
            if(j == Data.word.size())
            {
                Data.col = i;
                Data.row = row; //saves row number and column if found.
                return true;
            }
        }
        row++;
    }
    return false;
}

void printData(struct gridData &Data)
{
	ofstream OutputFile;
	OutputFile.open("Output2.txt");
   
    if( Data.L_to_R == true || Data.R_to_L == true ||
            Data.T_to_B == true || Data.B_to_T == true)
    {
        Data.found = true;
    }
    
	if(Data.found == true)
	{
	    OutputFile << "Coordinates are: " << "{" << Data.row << "," << Data.col << "}" << endl;
	    cout << "\nCoordinates are: " << "{" << Data.row << "," << Data.col << "}" << endl << endl;
	}
	
	else if(Data.found == false)
	{
	    OutputFile << endl;
	    OutputFile << "Word not found!" << endl;
	    OutputFile << endl;
	    cout << endl;
	    cout << "Word not found!" << endl;
	    cout << endl;
	}

    OutputFile << endl << endl;
}

void askForSearchTerm(struct gridData &Data)
{
    string input;
    cout << endl;
    cout << "Enter number of words: "; 
    int n;
    cin >> n;
    cout << "Enter " << n << " words to be searched in uppercase: " << endl;
    for(int i = 0; i < n; i++)
    {
    	cin >> input;
	}
    
    Data.word = input;
}

bool searchForHorizontalRtoL(char grid[][COLS], struct gridData &Data)
{
    char GridRow[ROWS];

    int row = 0;
    int inverseRow = 0;

    while(row < ROWS)
    {
        inverseRow = 0;
        for(int n = (ROWS - 1); n >= 0; n--)
        {
            GridRow[inverseRow] = grid[row][n];
            inverseRow++;
        } //loads the next row for string to be searched.
        for(int i = 0; i < (ROWS - Data.word.size()); i++)
        {
            int j = 0;
            while((j < Data.word.size()) && (Data.word[j] == GridRow[i+j]))
            {
                j++;
            }
            if(j == Data.word.size())
            {
                Data.col = 11 - i;
                Data.row = row;//saves row number and column if found
                return true;
            }
        }
        row++;
    }
    return false;
}

bool searchForVerticalTtoB(char grid[][COLS], struct gridData &Data)
{
    char GridCol[COLS];

    int col = 0;

    while(col < COLS)
    {
        for(int n = 0; n < COLS; n++)
        {
            GridCol[n] = grid[n][col];
        } //loads the next column for string to be searched.
        for(int i= 0; i < (COLS - Data.word.size()); i++)
        {
            int j = 0;
            while((j < Data.word.size()) && (Data.word[j] == GridCol[i+j]))
            {
                j++;
            }
            if(j == Data.word.size())
            {
                Data.col = col;
                Data.row = i; //saves row number and column if found.
                return true;
            }
        }
        col++;
    }
    return false;
}

bool searchForVerticalBtoT(char grid[][COLS], struct gridData &Data)
{
    char GridCol[COLS];

    int col= 0;

    while(col < COLS)
    {
        int inverseCol = 0;
        for(int n = (COLS - 1); n >= 0; n--)
        {
            GridCol[inverseCol] = grid[n][col];
            inverseCol++;
        } //loads the next column for string to be searched.
        for(int i= 0; i < (COLS - Data.word.size()); i++)
        {
            int j=0;
            while((j < Data.word.size()) && (Data.word[j] == GridCol[i+j]))
            {
                j++;
            }
            if(j == Data.word.size())
            {
                Data.col = col;
                Data.row = 11 - i;//saves row number and column if found.
                return true;
            }
        }
        col++;
    }
  return false;
}
  
void search(char grid[][COLS], struct gridData &Data)
{
    Data.L_to_R = searchForHorizontalLtoR(grid, Data);
    if(Data.L_to_R == false)
    {
        Data.R_to_L = searchForHorizontalRtoL(grid, Data);
    }
    if(Data.L_to_R == false &&  Data.R_to_L == false)
    {
        Data.T_to_B = searchForVerticalTtoB(grid, Data);
    }
    if(Data.L_to_R == false &&  Data.R_to_L == false &&
          Data.T_to_B == false)
    {
        Data.B_to_T = searchForVerticalBtoT(grid, Data);
    }
}

void reverseStr(string& input)
{
    int n = input.length();
    for (int i = 0; i < n / 2; i++)
        swap(input[i], input[n - i - 1]);
}

int main()
{	
	char C,S,Q;
	char choice;
	string menu =" 1. Create Grid\n 2. Search words from Grid\n 3. Quit\n Press C to create grid\n Press S to search words from grid\n Press Q to quit\n";
	
	
	do
	{
		cout << menu;
		cin >> choice;
		if(choice == 'C')
		{
			int TotalWords = 0;
		ifstream fin("Input1.txt");
		ofstream fout("Output1");
	
		if (!fin)
		{
			cout << " File not created!" << endl;
			return 0;
		}
		else
		{
			cout << "File created sucessfully!" << endl << endl;
		}
	
		fin >> TotalWords;
		
		char** List_of_Words = new char* [TotalWords + 1];
		List_of_Words = Input(fin, List_of_Words, TotalWords);
		int word_length = Max_Length_Of_Word(List_of_Words, TotalWords);
	
		char** Grid = new char* [word_length];
		for (int i = 0; i < word_length; i++)
			Grid[i] = new char[word_length];
	
		Grid = Default(TotalWords, Grid, List_of_Words);
		List_of_Words = Sort_Array(TotalWords, List_of_Words);
		grid_form(word_length, TotalWords, List_of_Words, Grid);
		PrintGrid(fout, word_length, Grid);
		}
		
		if(choice == 'S')
		{
			string input; 
		    char grid[ROWS][COLS];
		    gridData Data;
		    Data.initialize();
		    getGrid(grid);
		    printGrid(grid);
			askForSearchTerm(Data);
			reverseStr(input);
		    search(grid, Data);
		    printData(Data);
    
		}
	}
	while(choice != 'Q');
	cout << "\nProgram exited\n";
	
	return 0;
}
