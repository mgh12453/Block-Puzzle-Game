#include <bits/stdc++.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

int SIZE_OF_BOARD = 11;
float EASY_POSIBILITY, MEDIUM_POSIBILITY, HARD_POSIBILITY; 
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

class block {
private:
    vector <vector <pair <int, int> > > simple;
    vector <vector <pair <int, int> > > medium;
    vector <vector <pair <int, int> > >   hard;
public: 
    block(){
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
    }
};


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
		if(c == '1' || c == '2')status = 0;
	}

	void display (){
		if(status == 0)display_main_menu();
		if(status == 1)display_difficulty_menu();
		if(status == 2)start();
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