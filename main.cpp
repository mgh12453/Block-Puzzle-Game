#include <bits/stdc++.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

typedef vector< pair< int , int > > block;
int SIZE_OF_BOARD = 11;
int EASY_POSIBILITY = 1, MEDIUM_POSIBILITY = 1, HARD_POSIBILITY = 1; 
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

int rnd(int r){
    srand(time(NULL));
    return (rand()%r);
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
    int x = rnd(EASY_POSIBILITY + MEDIUM_POSIBILITY + HARD_POSIBILITY);
    if(x < EASY_POSIBILITY) v = simple[rnd(simple.size())];
    else if(x < EASY_POSIBILITY + MEDIUM_POSIBILITY) v = medium[rnd(medium.size())];
    else v = hard[rnd(hard.size())];
    return v;
}


class game
{
private:
	block current_block = get_random_block(), next_block = get_random_block();
	vector<vector<char>> buff;
	int score = 0;
	int high_score = 0;
	int status = -1;
public:
	game(){
		status = -1;
		buff.clear();
		for(int i = 0; i < SIZE_OF_BOARD; i ++)
			buff.push_back(vector<char>(SIZE_OF_BOARD, '-'));
		ifstream in;
		in.open("score.txt");
		in >> high_score;
		in.close();
	}

    ~game(){
        ofstream out;
        out.open("score.txt");
        out << high_score;
        out.close();
    }

    void hint (){
        cout << "In each turn you can enter these charachters to move your block :\n";
        cout << "A => moves the block one unit to right.\n";
        cout << "D => moves the block one unit to left.\n";
        cout << "S => moves the block down to reach the minimum height.\n";
    }

	void check (){
		for (int i = SIZE_OF_BOARD-1; i >= 0; i--){
			bool ok = 1;
			for (int j = 0; j < SIZE_OF_BOARD; j++){
				if (buff[i][j] != '#')
					ok = 0;
			}
			if (ok) {
				score++;
				high_score = max(score, high_score);
				for (int j = 0; j < SIZE_OF_BOARD; j++)
					buff[i][j] = '-';
				for (int j = i-1; j >= 0; j--) {
					swap (buff[j], buff[j+1]);
				}
			}
		}
	}

    void move_left (){
        bool ok = 1;
        for (pair <int, int> &p : current_block) 
            buff[p.first][p.second] = '-';
        for (pair <int, int> &p : current_block) {
            if (p.second <= 0 or buff[p.first][p.second-1] != '-')
                ok = 0;
        }
        for (pair <int, int> &p : current_block) 
            buff[p.first][p.second] = '#';
        if (ok == 1) {
            for (pair <int, int> &p : current_block) 
                buff[p.first][p.second] = '-';

            for (pair <int, int> &p : current_block) 
                buff[p.first][--p.second] = '#';
        }
        check ();
    }

	void move_right (){
		bool ok = 1;
		for (pair <int, int> &p : current_block) 
			buff[p.first][p.second] = '-';
		for (pair <int, int> &p : current_block) {
			if (p.second >= SIZE_OF_BOARD-1 or buff[p.first][p.second+1] != '-')
				ok = 0;
		}
		for (pair <int, int> &p : current_block) 
			buff[p.first][p.second] = '#';
		if (ok) {
			for (pair <int, int> &p : current_block) 
				buff[p.first][p.second] = '-';

            for (pair <int, int> &p : current_block) 
                buff[p.first][++p.second] = '#';
        }
        check ();
    }

    void move_down (){
        bool ok = 1;

		for (pair <int, int> &p : current_block) 
		 	buff[p.first][p.second] = '-';
		for (pair <int, int> &p : current_block) 
		 	if (p.first >= SIZE_OF_BOARD-1 or buff[p.first+1][p.second] != '-')
				ok = 0;
		for (pair <int, int> &p : current_block) 
			buff[p.first][p.second] = '#';
		if (ok) {
			for (pair <int, int> &p : current_block) 
				buff[p.first][p.second] = '-';

            for (pair <int, int> &p : current_block) 
                buff[++p.first][p.second] = '#';
            return move_down ();
        }
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
        cout << "* Default               (1) *\n";
        cout << "* Custom                (2) *\n";  
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

	void end_game(){
		clrscr();
		print('~', 35);
		cout << "\n*  Ending game, hope to enjoy ;)  *" << endl;
		cout << "*                                 *" << endl;
		cout << "*    Your Score: " << (high_score > 9 ? to_string(score) : to_string(score)+' ') << "               *" << endl;
		cout << "*    Your Highest Score: " << (high_score > 9 ? to_string(high_score) : to_string(high_score)+' ') << "       *" << endl;
		cout << "*                                 *" << endl;
		print('~', 35); cout << endl << endl;
		for (int i = 0; i < 16; i ++){
			cout << ". ";
			cout.flush();
			this_thread::sleep_for(chrono::milliseconds(250));
		}
		ofstream out;
		out.open("score.txt");
		out << high_score;
		out.close();
		exit(0);
	}


	void start(){
		bool hnt = false;
		score = 0;
		next_block = get_random_block(); current_block = get_random_block();
		buff.clear();
		for(int i = 0; i < SIZE_OF_BOARD; i ++)
			buff.push_back(vector<char>(SIZE_OF_BOARD, '-'));

		bool init = true;
		while(1){
			clrscr();
			if(init){
				for(auto p : current_block){
					if(buff[p.first][p.second] == '#')end_game();
					buff[p.first][p.second] = '#';
				}
				init = false;
			}
			int n = 11;
			vector<char> block_buffer[4];
			fill(block_buffer, block_buffer+5, vector<char>(n, ' '));
			for(auto p : next_block)
				block_buffer[p.first+1][p.second-(SIZE_OF_BOARD-n)/2] = '#';
			for(int i = 0; i < 4; i ++){
				if(i != 2)print(' ', 11);
				else cout << "Next block:";	
				for(char x : block_buffer[i])
					cout << (x == '-' ? ' ' : x);
				print(' ', 12);
				if(i == 0){print('~', 13); print(' ', 4); print('~', 19);}
				else if(i == 1){ 
					cout << "* Retry (1) *"; print(' ', 4); 
					cout << "* Score: " << (score > 9 ? to_string(score) : to_string(score)+' ');
					print(' ', 7); cout << "*";
				}
				else if(i == 2){ 
					cout << "* Hint  (2) *";
					print(' ', 4); cout << "*"; print(' ', 17); cout << "*"; 
				}
				else if(i == 3){ 
					cout << "* Exit  (3) *"; print(' ', 4); 
					cout << "* High score: " << (high_score > 9 ? to_string(high_score) : to_string(high_score)+' ');
					print(' ', 2); cout << "*";
				}
				cout << '\n';
			}
			print(' ', 23+n); print('~', 13); print(' ', 4); print('~', 19); cout << '\n'; 
			
			for(int i = 0 ; i < buff.size() ; i ++){
				for(auto c : buff[i])cout << c;
				cout << '\n';
			}
			if(hnt)hint();

            char c = getch();
            if(c == 'a' || c == 'A')move_left();
            else if(c == 'd' || c == 'D')move_right();
            else if(c == 's' || c == 'S'){move_down(); swap(next_block, current_block); next_block = get_random_block(); init = true;}
            else if(c == '1')return;
            else if(c == '2')hnt = true;
            else if(c == '3')end_game();
        }
    }

    void display (){
        if(status == -1)display_main_menu();
        if(status == 0)start();
        if(status == 1)display_difficulty_menu();
        if(status == 2)end_game();
    }

    int get_status(){
        return  status;
    }
};

int main(){
    game g;
    while (true) {
        g.display();
    }
    return 0;
}