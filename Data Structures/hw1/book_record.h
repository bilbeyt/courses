/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 11.10.2015
*/

#define NAME_LENGTH 20
#define SURNAME_LENGTH 20
#define TITLE_LENGTH 20
#define TYPE_LENGTH 10


struct book_record{
	
	char authorName[NAME_LENGTH], authorSurname[SURNAME_LENGTH], title[TITLE_LENGTH];
	int ISBN, location;
	char bookType[TYPE_LENGTH];

};