#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/json-data.h"
#include "../include/json-list.h"

#define LINE_BREAK			"\n"
#define	JSON_LIST_OPEN		"["
#define	JSON_LIST_CLOSE		"]"
#define	JSON_LIST_SEPARATOR	","

struct JSON_LIST {
	JSON_DATA* data;
	JSON_LIST* prev;
	JSON_LIST* next;
};

JSON_LIST* json_list_get_last ( JSON_LIST* list );
void json_str_concat ( char** str, char* new_part );

JSON_LIST* json_list_new () {
	JSON_LIST* list = ( JSON_LIST* ) calloc( 1, sizeof( JSON_LIST ) );
	return list;
}

void json_list_add( JSON_LIST* list, JSON_DATA* data ) {
	if ( list->data == NULL ) {
		list->data = data;
		return;
	}
	JSON_LIST* last = json_list_get_last( list );
	JSON_LIST* new_list = json_list_new();
	last->next = new_list;
	new_list->prev = last;
	new_list->data = data;
}

void json_list_destroy ( JSON_LIST** list ) {
	if ( list == NULL ) return;
	JSON_LIST* last = json_list_get_last( *list );
	JSON_LIST* swap = NULL;
	do {
		if ( last->data != NULL ) json_data_destroy( &last->data );
		swap = last->prev;
		free( last );
		last = swap;
	} while ( last );
}

JSON_LIST* json_list_get_last ( JSON_LIST* list ) {
	JSON_LIST* last = list;
	while ( last->next ) last = last->next;
	return last;
}

void json_str_concat ( char** str, char* new_part ) {
	*str = realloc( *str, strlen( *str ) + strlen( new_part ) + 1 );
	strcat( *str, new_part );
}

char* json_list_to_string ( JSON_LIST* list ) {
	JSON_LIST* next_node = list;
	size_t str_initial_size = strlen( JSON_LIST_OPEN ) + 1;
	char* json_data_str = NULL;
	char* str = ( char* ) calloc( str_initial_size, sizeof( char ) );
	if ( list != NULL ) {
		strcpy( str, JSON_LIST_OPEN );
		do {
			json_data_str = json_data_to_string( next_node->data );
			json_str_concat( &str, json_data_str );
			free( json_data_str );
			next_node = next_node->next;
			if ( next_node != NULL ) json_str_concat( &str, JSON_LIST_SEPARATOR );
		} while( next_node );
		json_str_concat( &str, JSON_LIST_CLOSE );
	}
	return str;
}

char* json_list_to_string_beautify ( JSON_LIST* data, char* tabe, size_t context ) {
	int i = 0;
	JSON_LIST* next_node = data;
	char* json_data_str = NULL;
	char* str = ( char* ) calloc( strlen( JSON_LIST_OPEN ) + 1, sizeof( char ) );
	if ( data == NULL ) return str;
	strcpy( str, JSON_LIST_OPEN );
	json_str_concat( &str, LINE_BREAK );
	do {
		for ( i = 0; i < context; i++ )	json_str_concat( &str, tabe );
		json_data_str = json_data_to_string( next_node->data );
		json_str_concat( &str, json_data_str );
		free( json_data_str );
		next_node = next_node->next;
		if ( next_node != NULL ) {
			json_str_concat( &str, JSON_LIST_SEPARATOR );
			json_str_concat( &str, LINE_BREAK );
		}
	} while( next_node );
	json_str_concat( &str, LINE_BREAK );
	for ( i = 1; i < context; i++ )	json_str_concat( &str, tabe );
	json_str_concat( &str, JSON_LIST_CLOSE );
	return str;
}

void json_data_print ( JSON_LIST* list ) {
	char* str = json_list_to_string( list );
	puts( str );
	free( str );
}

void json_list_dump ( JSON_LIST* list ) {
	char* str = json_list_to_string_beautify( list, "    ", 1 );
	puts( str );
	free( str );
}

