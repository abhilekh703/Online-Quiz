#include<iostream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<time.h>
using namespace std;

struct ques
{
	char question[400];
	char op;
}Q[50];

struct player	
{
	char name[20];
	char userName[20];
	char passWord[20];
	int rank;
	int score;	
};
player arr[20], temp;

class Questions 
{ 
        int quesNo; 
        char ans; 
        int score; 
        int ques[10]; /*array to store previously generated question numbers*/ 
        int count; 
                 
    public: 
        Questions() 
        { 
            score=0;  
             
            for (int i=0;i<5;i++) 
                ques[i]=-1; 
            count=0;  
             
        } 
         
        int generateQuesNo() 
        { 
            int i;  
            while(count<5) 
            { 
	            int flag=0; 
	            quesNo=rand()%50; 	   /*generating a random question number*/ 
	            for(i=0;i<count;i++) 
	            { 
	                if(quesNo==ques[i]) /*ensuring no repetiion of questions*/
	                { 
	                    flag=1;  
	                     break; 
	                } 
	            } 
             
                if(flag==0)  
                { 
                	ques[count]=quesNo;  
					cout<<Q[quesNo].question;
                	count++;  
                	do
                	{ 
                		cout<<endl<<"Enter your answer: ";
                		cin>>ans;
					/*checking correctness of answer and assigning score*/
						if(toupper(ans)>'D')
							cout<<"\nInvalid Option!";
						else 
							break;
					}while(1);
                	int correct=checkAns(quesNo,ans); 
                	if(correct==1) 		
                    	score+=2;               
                } 
            }      
            cout<<endl<<endl<<"Your score is: "<<score<<endl<<endl;
        	return score;       
        } 
         
        int checkAns(int q, char ch) 
        { 
            if(Q[quesNo].op==toupper(ch)) 
                return 1;      
            else return 0;  
        }
		
		void showAns()
		{
			int counter = 0,que;
			while(counter<5)
			{
				que = ques[counter];
				cout << Q[que].op << endl;
				counter++;
			}
		}        
};

class System
{
		int noOfAcc;
	
	public:
		void updatenum(int x)
		{
			noOfAcc=x;
		}
		int retnum()
		{
			return noOfAcc;
		}
		int authenticate(char * username, char * password)
		{
			for(int i =0;i< noOfAcc;i++)
			{	/*authneticating the account*/
				if(strcmp(username,arr[i].userName)==0)
				{
					if(strcmp(password,arr[i].passWord) == 0)
					{
						return 1;	
					}	
					else
					{
						return 0;
					}
				}					
			}		
			return 0;
		}
		
		int generateRank(char * name, int score)
		{
			int t;
			/*Calculating rank by sorting of scores in descending order*/
			for(int i=0;i<noOfAcc;i++)
			{
				
					
				if(strcmp(arr[i].userName,name)==0)
				{
			
				arr[i].score = score;
				  t = i+1;
				}
			}
			for(int i=0;i<noOfAcc;i++)
			{
				for(int j=i+1;j<noOfAcc;j++)
				{
					if(arr[i].score<arr[j].score)
					{
						temp = arr[i];
						arr[i]=arr[j];
						arr[j] = temp;
					}
				}
			}
			for(int i=0;i<noOfAcc;i++)
			{
				arr[i].rank = (i+1);
				if(!strcmp(arr[i].userName,name))
				  t = i+1;  
			}
			
			return t;
		}
		
		int displayScore(char * username)
		{
			for(int i=0;i<noOfAcc;i++)
			{
				if(strcmp(arr[i].userName,username)==0)
				{
					cout<<arr[i].score;
				}
			}
		}
		
		int createAccount(player p)
		{	
			noOfAcc++;
			arr[noOfAcc-1] = p;
		}
		
		
		void update(player p)
		{
			for(int i=0;i<noOfAcc;i++)
			{
				if(strcmp(arr[i].userName, p.userName) ==0)
				{
					arr[i] = p;
				}
			}
		}
		Questions q;
		int startQuiz(player p)
		{
			
			int x =q.generateQuesNo();  /*generateQuesNo returns score*/
			/*Updating scores*/			
			for(int i = 0; i<noOfAcc;i++)
			  if(strcmp(arr[i].userName,p.userName)==0)
			  {
				if(arr[i].score<x)	  
			    	arr[i].	score = x;
				}
			return x;	
		}
		
		void answers()
		{
			q.showAns();	
		}
}S;


class Player
{
		player P;
	
	public:
		int login()
		{
			char pwd[20],uname[20],ch;
			int i;
			cout << "\n Enter username ";
			cin >> uname;
			cout << "\n Enter Password ";
			
			i = 0;
			do
			{	/* Printing '*' when characters of the password is entered */
				ch = getch();
				pwd[i++] =  ch;
				cout << "*";

			} while (ch != 13);
			pwd[i-1] = '\0';
			 
			if (S.authenticate(uname, pwd))
			{
				strcpy(P.userName,uname);
				strcpy(P.passWord,pwd);
				return 1;
			}
			else
			{
				cout << "\n Invalid login";
				login();
			}
		}
		
		void newAcc()
		{
			/*Creating a new account*/
			char ch;
			int i;
			cout << "\n Enter Name: ";
			cin >> P.name;
			cout << "\n Enter UserName: ";
			cin >> P.userName;
			cout << "\n Enter Password: ";
			
			i = 0;
			do
			{
				ch = getch();
				P.passWord[i++] =  ch;
				cout << "*";

			} while (ch != 13);
			P.passWord[i-1] = '\0';
			S.createAccount(P); 
		}
		
		void getRank()
		{
			cout << "\n Your Place in the leaderboards is " << S.generateRank(P.userName,P.score);/*generateRank returns rank*/
		}
	
		void take()	
		{
			/*Starts the quiz*/
			P.score = S.startQuiz(P);
			
			P.rank = S.generateRank(P.userName, P.score);
			S.update(P);
		}	
		
		void check_answer()
		{
			S.answers();
		}
		
		char * retname()
		{
			return P.name;
		}
		
		char * retuser()
		{
			return P.userName;
		}
		
		char * retpass()
		{
			return P.passWord;
		}
		int retrank()
		{
			return P.rank;
		}
		void setrank(int ra)
		{
			P.rank = ra;
		}
		int retscore()
		{
			return P.score;
		}
};


class Admin
{
		char userName[20];
		char password[20];
		
	public:
		/* Setting all scores and ranks to 0*/
		void resetLeaderBoard()
		{
			for(int i=0;i<S.retnum();i++)
			{
				arr[i].score=0;
				arr[i].rank=0;
			}
		}
		
		void add_question()
		{
			char question[10000];
			char answer[10];
    		ofstream que_file, ans_file;  // Create Object of Ofstream
    		
    		ifstream que_no;
    		que_no.open("que_number.txt");
    		int count;
    		que_no >> count;
    		count++;
    		que_no.close();
    		
    		ofstream que_no1;
    		que_no1.open("que_number.txt");
    		que_no1 << count;
    		que_no1.close();
    		
    		
    		
    		que_file.open ("questions.txt", ios::app); // Append mode
    		cout << "question number is " << count << endl;
    		cout << "Enter the question with number,options followed by $" <<endl;
    		cin >> question;
			que_file << question; // Writing data to file
    		que_file.close();
    		
    		ans_file.open ("answers.txt", ios::app); // Append mode
			cout << "Enter the corect answer" << endl;
    		cin >> answer;
    		ans_file << answer;
    		ans_file.close();
    			
		}

};

void menu(Player&);
int main()
{
	srand(time(NULL));
	for(int i=0;i<20;i++)
	{
		arr[i].score=0; 
		arr[i].rank=-1;
	}
	ifstream fin,fin2,f;
	/*Reading from the files containing questions, answers and player information*/
	fin.open("questions.txt", ios::in);
	fin2.open("answers.txt", ios::in);
	f.open("Final.dat",ios::in);
	int i;
	for(int i = 0; !f.eof();i++)
	  {
	  	f.read((char*)&arr[i],sizeof(player)); /*Reading players file into arr of structures of type Player*/
	  	//cout << arr[i].userName << endl;
	  	
	  }
	  
	S.updatenum(i);					/*Updating total number of accounts*/
	
	char my_character ;
	int ques_num = 0;
	i=0;
	
		while(ques_num<50)
		{
			fin.get(my_character);
			if(my_character == '#') /* '#' is the end of the questions file*/
				break;
			Q[ques_num].question[i++] = my_character;
				if (my_character == '$') /* '$' is the end of each question in the questions file*/
				{
					Q[ques_num].question[i-1] = '\0';
					fin2.get(Q[ques_num].op) ;
					++ques_num;
					i=0;
				}		
		}
		fin.close();
		fin2.close();
		f.close();	
		int opt=0;
		int ch; 
		Player p1;
		menu(p1);
		Admin A;
		while(1)
		{	 
			if(strcmp(p1.retuser(),"akhil")==0)
			{
			
			/*Menu for user of software app*/
				cout<<"\n1. Logout"<<endl<<"2. Reset Leaderboard" <<endl<<"3. Add Question"<<endl;
				cout<<endl<<"Enter your option:"; 
				cin>>ch; 
				
				switch(ch)
				{
					case 1:menu(p1);
							break;
					case 2:if(strcmp(p1.retuser(),"akhil")==0)
							{
								A.resetLeaderBoard();
								cout<<endl<<"Leaderboard has been reset"<<endl;
							}
							else
							{
								cout<<endl<<"You don't have rights for that! "<<endl;
							}
							break;
					case 3:if(strcmp(p1.retuser(),"akhil")==0)
							{
								A.add_question();
								cout<<endl<<"Question has been added"<<endl;
							}
							else
							{
								cout<<endl<<"You don't have rights for that! "<<endl;
							}
							break;
				 } 
			}
			else
			{
			
			/*Menu for user of software app*/
				cout<<"\n1. Take quiz"<<endl<<"2. Get rank"<<endl<<"3. Logout"<<endl<<"4. Show Answers"<<endl;
				cout<<endl<<"Enter your option:"; 
				cin>>ch; 
				
				switch(ch)
				{
					case 1:p1.take();
							break;  
					case 2:p1.getRank();
							break;
					case 3:menu(p1);
							break;
					case 4:p1.check_answer();
							break;
				 } 
			}
			
		}
			
}

void menu(Player &p1)
{
	int opt=0;
	int ch;
	while(1)
		{
						
			if(opt==1)
			break;
		 	/*Login menu*/
			cout<<"\n1. Login"<<endl<<"2. Create new account"<<endl<<"3. Terminate session";
			cout<<endl<<"Enter your choice: "; 
			cin>>ch; 
		
			if(ch==1)
			{
				opt = p1.login();
			}
			else if(ch==2)
			{
				p1.newAcc();
				ofstream fout;
				fout.open("Final.dat",ios::app);
				fout.write((char*)&p1,sizeof(p1));
				fout.close();
			}
			else if(ch==3)
			{
				
				exit(0);
			}
			else
			{
				cout<<endl<<"Invalid choice!"<<endl;
			}
			
		}
}
