#include <bits/stdc++.h>

using namespace std;

const int SIZE_OF_BOARD = 11;
const float EASY_POSIBILITY, MEDIUM_POSIBILITY, HARD_POSIBILITY; 
inline void print(char c, int cnt)while(cnt--)cout << c;

class block {
private:
	vector <vector <pair <int, int> > 	 simple;
	vector <vector <pair <int, int> > 	average;
	vector <vector <pair <int, int> > difficult;
public:	
	block(){
		
	}
}

class game
{
private:
	vector<vector<char>> buff;
	int size;
	int status = 0;
public:
	game(){
		status = 0;
		size = SIZE_OF_BOARD;
		for(int i = 0; i < size; i ++)
			buff.push_back(vector<char>(' ', size));
	}

	void start(){

	}

	void check (){

	}

	void move_left (){

		check ();
	}

	void move_right (){
		check ();
	}

	void move_down (){

		check ();
	}

	void hint (){

	}

	void display_main_menu(){
		print('*', 7);
		cout << "* "	
	}

	void display_choose_menu(){

	}

	void display (){
		if(status == 0)display_main_menu();
		if(status == 1)display_choose_menu();
		if(status == 2)start();
	}

	int get_status(){
		return	status;
	}
};

int main(){
	game g;
	while (true) {

	}
	return 0;
}