#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Create a song list
typedef struct dynamic_array { //song list struct
	int capacity;
	int size;
	void** elements;
} dynamic_array;

typedef struct song {
	char* name;
	float duration;
} song_str;

void init_array(dynamic_array* array) {
	array->capacity=2;
	array->size=0;
	array->elements=malloc(2*sizeof(void*));
	array->elements[0]=NULL;
	array->elements[1]=NULL;
}

void put_element(dynamic_array* array, void* element) {
	if (array->size==array->capacity){
		array->capacity*=2;
		array->elements=realloc(array->elements,(array->capacity)*sizeof(void*));
	}	
	(array->elements)[array->size]=element;
	array->size++;
}

void remove_element(dynamic_array* array, int position) {
	while(position<(array->size)-1){
		array->elements[position]=array->elements[position+1];
		position++;
	}
	array->elements[position]=NULL;
	array->size--;
}

void* get_element(dynamic_array* array, int position) {
	if(array->elements[position]!=NULL)	
		return array->elements[position];
}

int get_position(dynamic_array* array, char* songName){
	int n=0;
	while(n<(array->size)){
		if (strcmp (songName,((song_str*)(array->elements[n]))->name)==0){
			return n;	
		}
		else {
			n++;
		}
	}
	return -1;
}

int main(){
	dynamic_array* array= malloc(sizeof(dynamic_array));
	init_array(array);	//initialize the array struct	
	while(1){
		printf("To add a song to the list press 1, to remove a song press 2, to list all songs press 3 and to exit press 4\n"); 
		fflush(stdout);
		int key;
		scanf("%d",&key);
		if (key==4)
			break;
		else if (key==1){//add a song	
			char* songName=(char* )malloc(64* sizeof(char));
			float inputduration;
			printf("Enter the name(64 characters at most)\n");	
			fflush(stdout);
			fflush(stdin);
			fgets(songName, 64, stdin);
			songName[strlen(songName)-1]='\0';
			printf("Enter the duration of the song\n"); 
			fflush(stdout);
			fflush(stdin);
			scanf("%f",&inputduration);
			song_str* song_ptr=(song_str*)malloc(sizeof(song_str));
			song_ptr->name=songName;
			song_ptr->duration=inputduration;
			put_element(array,song_ptr);	
			printf("Song %s is entered\n",((song_str*)get_element(array,(array->size)-1))->name);
		}
		else if (key==2){//delete a song 
			char songName[64];
			printf("Enter name\n"); 
			fflush(stdout);
			fflush(stdin);
			fgets(songName, 64, stdin);
			songName[strlen(songName)-1]='\0';
			int index=get_position(array,songName);
			if (index!=-1){
				remove_element(array,index);
				printf("Song %s is deleted \n",&songName);
			}
			else 
				printf("Song doesn't exist \n");
		}
		else if(key==3){//print all songs
			int n=0;
			if (array->size ==0) {
				printf("There aren't any songs in the list\n");
			}
			else {
				while(n<array->size){
					song_str* song =(song_str* )get_element(array,n);
					printf("Song name: %s,",song->name);
					printf(" duration: %.2f \n",song->duration);
					n++;
				}	
			}
		}
	}
	printf("end of the program");
	return 0;	
}