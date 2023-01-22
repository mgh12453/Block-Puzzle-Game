#include <bits/stdc++.h>

using namespace std;

class game
{
private:
	vector<vector<char>> buff;
	int size;
	int status = 0;
public:
	game(int init_size = 11){
		status = 0;
		size = init_size;
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

	void display (){
		if(status == 0)display_main_menu();
		if(status == 1)display_choose_menu();
		if(status == 2)start();
	}

	int get_status(){
		return	status;
	}


	void display_main_menu(){

	}

	void display_choose_menu(){

	}
};

int main(){
	game g;
	while (true) {

	}
	return 0;
}