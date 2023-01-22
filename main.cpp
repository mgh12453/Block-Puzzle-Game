#include <bits/stdc++.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

typedef vector< pair< int , int > > block;
int SIZE_OF_BOARD = 11;
float EASY_POSIBILITY = 1, MEDIUM_POSIBILITY = 1, HARD_POSIBILITY = 1; 
void print(char c, int cnt){while(cnt--)cout << c;}
void clrscr(){system("clear");}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int rnd(int l, int r){
	srand(time(NULL));
	return (rand()%(r-l))+l;
}

vector< pair< int , int > > get_random_block(){
	vector <block> simple;
    vector <block> medium;
    vector <block>   hard;
    int sz = (SIZE_OF_BOARD - 1) / 2;
    simple.push_back ({{0, sz}});

    simple.push_back ({{0, sz}, {1, sz}});
    simple.push_back ({{0, sz}, {0, sz+1}});
    
    simple.push_back ({{0, sz}, {0, sz+1}, {1, sz}, {1, sz+1}});

    medium.push_back ({{0, sz+1}, {1, sz}, {1,sz+1}});
    medium.push_back ({{0, sz}, {1, sz}, {1,sz+1}});
    medium.push_back ({{0, sz}, {0, sz+1}, {1,sz}});
    medium.push_back ({{0, sz}, {0, sz+1}, {1,sz+1}});
   
    medium.push_back ({{0, sz}, {1, sz}, {2, sz}});
    medium.push_back ({{0, sz-1}, {0, sz}, {0, sz+1}});

    medium.push_back ({{0, sz}, {1, sz}, {2, sz}, {3, sz}});
    medium.push_back ({{0, sz-1}, {0, sz}, {0, sz+1}, {0, sz+2}});

    hard.push_back ({{0, sz-1}, {0, sz}, {1, sz}, {1, sz+1}});
    hard.push_back ({{0, sz}, {0, sz+1}, {1, sz}, {1, sz-1}});
    hard.push_back ({{0, sz}, {1, sz}, {1, sz+1}, {2, sz+1}});
    hard.push_back ({{0, sz+1}, {1, sz}, {1, sz+1}, {2, sz}});

    hard.push_back ({{0, sz-1}, {0, sz}, {0, sz+1}, {1, sz}});
    hard.push_back ({{0, sz}, {1, sz-1}, {1, sz}, {1, sz+1}});
    hard.push_back ({{0, sz+1}, {1, sz}, {1, sz+1}, {2, sz+1}});
    hard.push_back ({{0, sz}, {1, sz}, {1, sz+1}, {2, sz}});

    hard.push_back ({{0, sz-1}, {0, sz}, {0, sz+1}, {1, sz-1}});
    hard.push_back ({{0, sz-1}, {1, sz-1}, {1, sz}, {1, sz+1}});
    hard.push_back ({{0, sz-1}, {0, sz}, {0, sz+1}, {1, sz+1}});
    hard.push_back ({{0, sz+1}, {1, sz-1}, {1, sz}, {1, sz+1}});

    block v;
    int x = rnd(1, EASY_POSIBILITY + MEDIUM_POSIBILITY + HARD_POSIBILITY);
    if(x < EASY_POSIBILITY) v = simple[rnd(0, simple.size())];
 	else if(x < EASY_POSIBILITY + MEDIUM_POSIBILITY) v = medium[rnd(0, medium.size())];
    else v = hard[rnd(0, hard.size())];
    return v;
}


class game
{
private:
	block current_block;
	vector<vector<char>> buff;
	int size;
	int score = 0;
	int status = -1;
public:
	game(){
		status = -1;
		size = SIZE_OF_BOARD;
		for(int i = 0; i < size; i ++)
			buff.push_back(vector<char>(' ', size));
	}

	void start(){

	}

	void hint (){
		cout << "In each turn you can enter these charachters to move your block :\n";
		cout << "a => moves the block one unit to right.\n";
		cout << "d => moves the block one unit to left.\n";
		cout << "s => moves the block down to reach the minimum height.\n";
	}

	void check (){
		for (int i = size-1; i >= 0; i--){
			bool ok = 1;
			for (int j = 0; j < size; j++){
				if (buff[i][j] != '#')
					ok = 0;
			}
			if (ok) {
				score++;
				for (int j = 0; j < size; j++)
					buff[i][j] = '-';
				for (int j = i-1; j >= 0; j++) {
					swap (buff[j], buff[j+1]);
				}
			}
		}
	}

	void move_left (){
		bool ok = 1;
		for (pair <int, int> p : current_block) {
			if (p.second <= 0 && buff[p.first][p.second-1] != '-')
				ok = 0;
		}
		if (ok) {
			for (pair <int, int> p : current_block) 
				buff[p.first][p.second] = '-';

			for (pair <int, int> p : current_block) 
				buff[p.first][--p.second] = '#';
		}
		check ();
	}

	void move_right (){
		bool ok = 1;
		for (pair <int, int> p : current_block) {
			if (p.second >= size-1 && buff[p.first][p.second+1] != '-')
				ok = 0;
		}
		if (ok) {
			for (pair <int, int> p : current_block) 
				buff[p.first][p.second] = '-';

			for (pair <int, int> p : current_block) 
				buff[p.first][++p.second] = '#';
		}
		check ();
	}

	void move_down (){
		bool ok = 1;
		for (pair <int, int> p : current_block) {
			if (p.first >= size-1 && buff[p.first+1][p.second] != '-')
				ok = 0;
		}
		if (ok) {
			for (pair <int, int> p : current_block) 
				buff[p.first][p.second] = '-';

			for (pair <int, int> p : current_block) 
				buff[p.first][++p.second] = '#';
			return move_down ();
		}
		else
			check ();
	}

	void display_main_menu(){
		clrscr();
		print('~', 26);	
		cout << "\n*"; print(' ', 24); cout << "*\n";
		cout << "*  Start Game       (1)  *\n";
		cout << "*  Select Difficulty(2)  *\n";
		cout << "*  Exit             (3)  *\n";	
		cout << '*'; print(' ', 24);  cout << "*\n";
		print('~', 26); cout << '\n';
		while(1){
			char c;
			c = getch();
			if(c >= '1' && c <= '3'){
				status = c-'1';
				return;
			}
		}
	}

	void display_difficulty_menu(){
		clrscr();
		print('~', 29);	
		cout << "\n*"; print(' ', 27); cout << "*\n";
		cout << "* Please select difficulty: *\n";
		cout << "*  Default             (1)  *\n";
		cout << "*  Custom              (2)  *\n";	
		cout << '*'; print(' ', 27);  cout << "*\n";
		print('~', 29); cout << '\n';
		char c;
		c = getch();
		if(c == '1'){
			clrscr();
			print('~', 35);
			cout << "\n*  Settings applied succsesfully  *" << endl;
			print('~', 35); cout << endl;
			sleep(1);
			clrscr();
		}
		else if(c == '2'){
			bool clr = true;
			while(1){
				if(clr)clrscr();
				cout << "Please enter posibilities (<easy>, <medium>, <hard>) and size of board:\n";
				float a, b, c;
				int x;
				cin >> a >> b >> c >> x;
				if(x > 11){
					EASY_POSIBILITY = a; MEDIUM_POSIBILITY = b; HARD_POSIBILITY = c;
					SIZE_OF_BOARD = x;
					clrscr();
					print('~', 35);
					cout << "\n*  Settings applied succsesfully  *" << endl;
					print('~', 35); cout << endl;
					sleep(1);
					clrscr();
					break;
				}
				else{
					cout << "Invalid choices, Please try again.\n";
					clr  = false;
				}
			}
		}
		if(c == '1' || c == '2')status = -1;
	}

	void display (){
		if(status == -1)display_main_menu();
		if(status == 0)start();
		if(status == 1)display_difficulty_menu();
		if(status == 2)exit(0);
	}

	int get_status(){
		return	status;
	}
};

int main(){
	game g;
	while (true) {
		g.display();
	}
	return 0;
}