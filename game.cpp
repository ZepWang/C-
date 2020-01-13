// name: Zeping Wang 
// filename: game.cpp
// due date: 10/5/2018
// collaboration: We got some information from google.
// ask questions and test it.
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

#define UNIT_TESTING //debugging test

int totalPoints = 0;

typedef 
   struct TriviaNode 
   {
      string question;
      string answer;
      int points;
   };
//Trivia node pointer
typedef TriviaNode* TriviaNodePtr;


//create list of trivia questions uses trivianode struct
class TriviaList 
{
public:
   TriviaList()
   {
   }
   
   TriviaList(string TQuestion, string TAnswer, int TPoints, TriviaList* theLink)
   {
      node.question = TQuestion; 
      node.answer = TAnswer; 
      node.points = TPoints; 
      link = theLink;
   }
   TriviaList* getLink() 
   {
      return link;
   }
   string getQuestion() 
   {
      return node.question;
   }
   string getAnswer() 
   {
      return node.answer;
   }
   int getPoints() 
   {
      return node.points;
   }
   void setQuestion(string TQuestion) 	
   {
      node.question = TQuestion;
   }
   void setAnswer(string TAnswer)	
   {
      node.answer = TAnswer;
   }
   void setPoints(int TPoints)	
   {
      node.points = TPoints;
   }
   void setLink (TriviaList* pointer)	
   {
      link = pointer;
   }
private:
   TriviaNode node;
   TriviaList* link;
};
typedef TriviaList* TriviaListPtr;

/*******************************PROTOTYPES***********************************/

  //Initializes the list of 3 trivia questions.
TriviaListPtr initList();

//addNode prototype

TriviaListPtr addNode(string TQuestion, string TAnswer, int TPoints, TriviaListPtr theLink);

//quizPlayer prototype
//Asks player questions based on trivia list and number of questions.
//0 is success, 1 is failure.
int quizPlayer(TriviaListPtr list, int questionNum, int FirIndex=0);

//getTrivia
//Prompts user for information to create trivia questions.
//Adds to list using addNode().
TriviaListPtr getTrivia(TriviaListPtr head);


/**********************TESTING PROTOTYPES************************/


//Testing of initList()
void test_initList();

//Testing of addNode()
void test_addNode();

//Testing of quizPlayer()
void test_quizPlayer();

//Testing of getTrivia()
void test_getTrivia();

/**************************MAIN*******************************/


int main() {
	#ifdef UNIT_TESTING
   test_quizPlayer(); //Testing
	
	#else
	//Regular version
   TriviaListPtr head = NULL;
   cout << "*** Welcome to Zeping and Jihao's trivia quiz game ***\n";
   string ans= "Yes";
	//Get valid yes/no input
   while (ans != "Yes" && ans != "No") 
   {
      cout << "Please enter valid input (Yes/No): ";
      getline(cin, ans);
   }
	//Initialize list with 3 hard-coded questions
   head = initList();
	//Get questions if they want to enter their own
   if (ans == "Yes") 
   {
      string cont;
      do 
      {
      	//Get input
         head = getTrivia(head);
      	//Prompt to add more
         cout << "Continue? (Yes/No): ";
         getline(cin, cont);
      	//Get valid yes/no input
         while (cont != "Yes" && cont != "No") 
         {
            cout << "Please enter valid input (Yes/No): ";
            getline(cin, cont);
         }
      }
      while (cont == "Yes");
   }
   cout << endl; 
	//cout << "How many questions would you like to answer? ";
   int questions=1000000;//indicates all questions
	//cin >> questions;
   int test;
   test = quizPlayer(head, questions);
   cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
	#endif
	
}


/*********************DEFINITIONS**************************/


//Definition of initList()
TriviaListPtr initList() 
{
   TriviaListPtr head;
	//Question 3
   string q = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
   string a = "Wii Sports";
   int p = 20;
   head = new TriviaList(q, a, p, NULL);
	//Question 2
   q = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
   a = "Bank of Italy";
   p = 50;
   head = new TriviaList(q, a, p, head);
	//Question 1
   q = "How long was the shortest war on record? (Hint: how many minutes)";
   a = "38";
   p = 100;
   head = new TriviaList(q, a, p, head);
   return head;
}

//Definition of addNode()
TriviaListPtr addNode(string TQuestion, string TAnswer, int TPoints, TriviaListPtr theLink) 
{
   TriviaListPtr next = theLink->getLink();
   while(next->getLink()!=NULL) next=next->getLink();

   TriviaListPtr n = new TriviaList(TQuestion, TAnswer, TPoints, NULL);
   next->setLink(n);
   return theLink;
}

//Defintion of quizPlayer()
int quizPlayer(TriviaListPtr list, int questionNum, int FirIndex) 
{
	//Make sure the user wants a valid number of questions
   if (questionNum <= 0) 
   {
      cout << "Warning - The number of trivia to be asked must be equal to or larger than 1\n";
      return 1; //failure
   }
   //Make sure valid trivia list
   else if (list == NULL) 
   {
      cout << "Warning - an empty list is not a valid trivia list\n";
      return 1; //failure
   }
   else 
   {
      TriviaListPtr head = list;
      TriviaListPtr next = head->getLink();
      int size = 1;
   	//make sure there are enough questions
      while (next != NULL) 
      {
         next = next->getLink();
         size++;
      }
      if(size<questionNum+FirIndex && questionNum<1000)
      {
      	//cout << "Warning – There are only three trivia in the list.\n";
         return 1;
      }
   	//put next at start of list, now ask the questions.
      next = head;
      for(int i=1;i<=FirIndex;i++) next=next->getLink();
      string answer;
      int index = 0;
      do {
         cout << "Question: " << next->getQuestion() << endl;
         cout << "Answer: ";
         getline(cin, answer);
      	//Weird issues with getline/cin mix in driver. This makes sure the "answer" given isn't just the \n left over from previous stuff.
         if (answer == "") 
         {
            getline(cin, answer);
         }
      	//Answer correct
         if (answer == next->getAnswer()) 
         {
            cout << "Your answer is correct. You receive " << next->getPoints() << " points.\n";
            totalPoints += next->getPoints();
         }
         //Answer wrong
         else 
         {
            cout << "Your answer is wrong. The correct answer is: " << next->getAnswer() << endl;
         }
         cout << "Your total points : " << totalPoints << "\n\n";
         next = next->getLink();
         index++;
      }
      //Ask questions as long as there are more, or, until reached number of questions requested.
      while (next != NULL && index < questionNum);
      return 0; //Success
   }
}

//Definition for getTrivia
TriviaListPtr getTrivia(TriviaListPtr list) 
{
   TriviaListPtr head = list;
   string question;
   string answer;
   int p;
	//Get input
   cout << "Enter a question: ";
   getline(cin, question);
   cout << "Enter an answer: ";
   getline(cin, answer);
   cout << "Enter award points: ";
	//Check to be sure points is valid (an integer > 0) 
	//Note, this specific check (while loop) was found on stack overflow.
	//Noting because outline says to note outside sources. Link in above comments.
   while (!(cin >> p) || p <= 0) 
   {
      cout << "Points must be a number greater than 0. Try again: ";
      cin.clear(); //Clears error in cin
      cin.ignore(1000, '\n'); //Makes sure next cin is next line.
   }
	//Add to head of list
   head = addNode(question, answer, p, head);
   cin.clear();
   cin.ignore(1000, '\n'); //Moves to next line for next cin input
   return head;
}

/***************************TESTING DEFINITIONS***********************************/


//Defintion of test driver for testinitList 

void test_initList() 
{
   TriviaListPtr head = initList();
   cout << "Test for initList():\n";
   assert("How long was the shortest war on record? (Hint: how many minutes)" == head->getQuestion());
   assert("38" == head->getAnswer());
   assert(100 == head->getPoints());
   cout << "\tTrivia 1 matches\n";
   TriviaListPtr next = head->getLink();
   assert("What was Bank of America's original name? (Hint Bank of Italy or Bank of Germany)" == next->getQuestion());
   assert("Bank of Italy" == next->getAnswer());
   assert(50 == next->getPoints());
   cout << "\tTrivia 2 matches\n";
   next = next->getLink();
   assert("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)" == next->getQuestion());
   assert("Wii Sports" == next->getAnswer());
   assert(20 == next->getPoints());
   assert(NULL == next->getLink());
   cout << "\tTrivia 3 matches\n";
}

//Defintion of test driver for test_addNode

void test_addNode() 
{
   cout <<"Test for addNode()\n";
	//Add to Empty list/new List.
   TriviaListPtr head = NULL;
   head = addNode("test", "test", 5, head);
   assert("test" == head->getQuestion());
   assert("test" == head->getAnswer());
   assert(5 == head->getPoints());
   assert(NULL == head->getLink());
   cout << "\tTest 1: Empty/new list passed\n";
	//Add to list with stuff in it
   head = addNode("test2", "test2", 20, head);
   assert("test2" == head->getQuestion());
   assert("test2" == head->getAnswer());
   assert(20 == head->getPoints());
   TriviaListPtr next = head->getLink();
   assert("test" == next->getQuestion());
   assert("test" == next->getAnswer());
   assert(5 == next->getPoints());
   assert(NULL == next->getLink());
   cout << "\tTest 2: Add to existing list passed\n";
}
   //Test driver for getTrivia
void test_getTrivia() 
{
   cout << "Test for getTrivia. Please input the following when prompted\nQuestion: How old are you?\nAnswer: 20\nPoints: 100\n";
   TriviaListPtr head = NULL;
   head = getTrivia(head);
   assert("How old are you?" == head->getQuestion());
   assert("20" == head->getAnswer());
   assert(100 == head->getPoints());
   cout << "Test passed\n";
}
//Definition of test driver for test_quizPlayer
//This is the driver required in Step 6 of the outline.
void test_quizPlayer()
{
	//Create a list of the 3 questions. initList has already been tested to show it works.
   TriviaListPtr list = initList();
   int test;
   cout << "*** This is a debugging version ***\n";
	
	//Case 1: No questions
   cout << "Unit Test Case 1: Ask no question. The program should give a warning message.\n";
   test = quizPlayer(list, 0);
	
	//Case 2.1: Ask 1 question, give incorrect answer.
   cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.\n";
   test = quizPlayer(list, 1,0);
   assert(0 == totalPoints);
   cout << "Case 2.1 passed...\n";
	
	//Case 2.2: Ask 1 question, give correct answer.
   cout << "\n Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.\n";
   test = quizPlayer(list, 1,2);
   assert(20 == totalPoints);
   cout << "Case 2.2 passed...\n";
	
	//Case 3
   totalPoints = 0; //Reset points
   cout << "\nUnit Test Case 3: Ask all the questions of the last trivia in the linked list.\n";
   test = quizPlayer(list, 1000,2);
   assert(0 == totalPoints);
   cout << "Case 2 passed...\n";
			
	//Case 4: 
   cout <<"\nUnit Test Case 4: Ask five questions in the linked list.\n";
   test = quizPlayer(list, 5);
   if(test==1) cout << "Warning – There are only three trivia in the list.\n";
	
   cout<<"\n*** End of the Debugging Version ***\n";
}

