/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 20.04.2016
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include "HetList.h"
#include "Score.h"


using namespace std;

string read_from_file(int);
void create_hetlist(HetList&, string&);
void displayResults(Score_List&, Score_List&);

int main(){
	
	HetList player1, player2;
	string player1_moves, player2_moves;
	Score_List player1_scores,player2_scores;
	player1_moves = read_from_file(1);
	player2_moves = read_from_file(2);
	create_hetlist(player1,player1_moves);
	create_hetlist(player2,player2_moves);
	player1.calculate_points(player2, player1_scores);
	player2.calculate_points(player1, player2_scores);
	player1_scores.calculate_totals();
	player2_scores.calculate_totals();
	cout<<"Player1: ";
	player1.print();
	cout<<endl<<"Player2: ";
	player2.print();
	displayResults(player1_scores, player2_scores);
 	return 0;
}

string read_from_file(int number){
	FILE *ptr;
	ptr = fopen("deck.txt", "r");
	fseek(ptr, 0, SEEK_SET);
	int counter=1;
	char line[250];
	while(fgets(line, sizeof(line), ptr)){
		if(counter==number){
			break;
		}
		counter++;
	};
	return line;
}

void create_hetlist(HetList &player, string &moves){
	char *move_arr = new char[moves.length()+1];
	strcpy(move_arr,moves.c_str());
	char *token;
	token = strtok(move_arr, " ");
	while(token != NULL){
		if(strlen(token)>1){
			token = strtok(token,"\n");
		}
		if(strcmp(token,"R")==0){
			Red *obj = new Red('R');
			player.insert(obj);
		}
		else if(strcmp(token,"D")==0){
			DarkRed *obj = new DarkRed('D');
			player.insert(obj);
		}
		else if(strcmp(token,"B")==0){
			Blue *obj = new Blue('B');
			player.insert(obj);
		}
		else if(strcmp(token,"G")==0){
			Green *obj = new Green('G');
			player.insert(obj);
		}
		token = strtok(NULL, " ");
	}
}

void displayResults(Score_List &player1, Score_List &player2){
	cout<<endl<<"Score1: ";
	player1.print();
	cout<<endl<<"Score2: ";
	player2.print();
	cout<<endl<<"Total Score1: ";
	cout<<"Lose: "<<player1.get_total_lose()<<" Tie: "<<player1.get_total_tie()<<" Win: "<<player1.get_total_win();
	cout<<endl<<"Total Score2: ";
	cout<<"Lose: "<<player2.get_total_lose()<<" Tie: "<<player2.get_total_tie()<<" Win: "<<player2.get_total_win();
	cout<<endl;
	if(player1.get_total_score() > player2.get_total_score()){
		cout<<"Winner: Player1";
	}
	else if(player1.get_total_score() < player2.get_total_score()){
		cout<<"Winner: Player2";
	}
	else{
		cout<<"Game is Tie"<<endl;
	}
}