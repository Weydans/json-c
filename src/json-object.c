#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/json-data.h"
#include "../include/json-list.h"
#include "../include/json-object.h"

#define LINE_BREAK				"\n"
#define	JSON_OBJECT_OPEN		"{"
#define	JSON_OBJECT_CLOSE		"}"
#define	JSON_OBJECT_SEPARATOR	","

struct JSON_OBJECT {
	char* key;
	JSON_DATA* data;
	JSON_OBJECT* prev;
	JSON_OBJECT* next;
};

JSON_OBJECT* json_object_new () {
	JSON_OBJECT* obj = ( JSON_OBJECT* ) calloc( 1, sizeof( JSON_OBJECT ) );
	return obj;
}

void json_object_add_str ( JSON_OBJECT* obj, char* key, char* value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_str( data, value );
	obj->key = key;
	obj->data = data;
}

void json_str_object_concat ( char** str, char* new_part ) {
	*str = realloc( *str, strlen( *str ) + strlen( new_part ) + 1 );
	strcat( *str, new_part );
}

char* json_object_to_string ( JSON_OBJECT* obj ) {
	JSON_OBJECT* next_node = obj;
	size_t str_initial_size = strlen( JSON_OBJECT_OPEN ) + 1;
	char* json_data_str = NULL;
	char* str = ( char* ) calloc( str_initial_size, sizeof( char ) );
	if ( obj != NULL ) {
		strcpy( str, JSON_OBJECT_OPEN );
		do {
			json_str_object_concat( &str, "\"" );
			json_str_object_concat( &str, next_node->key );
			json_str_object_concat( &str, "\":" );
			json_data_str = json_data_to_string( next_node->data );
			json_str_object_concat( &str, json_data_str );
			free( json_data_str );
			next_node = next_node->next;
			if ( next_node != NULL ) json_str_object_concat( &str, JSON_OBJECT_SEPARATOR );
		} while( next_node );
		json_str_object_concat( &str, JSON_OBJECT_CLOSE );
	}
	return str;
}

void json_object_destroy ( JSON_OBJECT** obj ) {
	if ( *obj == NULL ) return;
	if ( ( *obj )->data != NULL ) json_data_destroy( &( *obj )->data );
	free( *obj );
	obj = NULL;
}

