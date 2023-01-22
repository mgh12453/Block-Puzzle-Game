#include <bits/stdc++.h>

using namespace std;

class game
{
private:
	vector<vector<char>> buff;
	int size;
public:
	game(int init_size = 11){
		size = init_size;
		for(int i = 0; i < size; i ++)
			buff.push_back(vector<char>('-', size));
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

	}
};


int main(){
	game* g;
	while (true) {
		string type;
		cin >> type;

	}
	return 0;
}