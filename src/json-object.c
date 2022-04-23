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

JSON_OBJECT* json_object_get_last ( JSON_OBJECT* object );
void json_object_add ( JSON_OBJECT* obj, char* key, JSON_DATA* data );
void json_object_stringify_key ( JSON_OBJECT* obj, char** str );
char* json_object_node_to_string ( JSON_OBJECT* node, char* tabe, size_t context );
char* json_object_node_data_to_string ( JSON_OBJECT* node, char* tabe, size_t context );

JSON_OBJECT* json_object_new () {
	JSON_OBJECT* obj = ( JSON_OBJECT* ) calloc( 1, sizeof( JSON_OBJECT ) );
	if ( obj == NULL ) {
		fprintf( stderr, "%s:%u: Memmory allocation fail\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	return obj;
}

void json_object_add ( JSON_OBJECT* obj, char* key, JSON_DATA* data ) {
	if ( obj->data == NULL ) {
		obj->data = data;
		obj->key = key;
		return;
	}
	JSON_OBJECT* last = json_object_get_last( obj );
	JSON_OBJECT* new_object = json_object_new();
	last->next = new_object;
	new_object->prev = last;
	new_object->key = key;
	new_object->data = data;
}

void json_object_add_str ( JSON_OBJECT* obj, char* key, char* value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_str( data, value );
	json_object_add( obj, key, data );
}

void json_object_add_char ( JSON_OBJECT* obj, char* key, char value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_char( data, value );
	json_object_add( obj, key, data );
}

void json_object_add_bool ( JSON_OBJECT* obj, char* key, bool value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_bool( data, value );
	json_object_add( obj, key, data );
}

void json_object_add_integer ( JSON_OBJECT* obj, char* key, long long int value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_integer( data, value );
	json_object_add( obj, key, data );
}

void json_object_add_double ( JSON_OBJECT* obj, char* key, long double value ) {
	JSON_DATA* data = json_data_new();
	json_data_add_double( data, value );
	json_object_add( obj, key, data );
}

void json_object_add_list ( JSON_OBJECT* obj, char* key, JSON_LIST* list ) {
	JSON_DATA* data = json_data_new();
	json_data_add_list( data, list );
	json_object_add( obj, key, data );
}

void json_str_object_concat ( char** str, char* new_part ) {
	*str = realloc( *str, strlen( *str ) + strlen( new_part ) + 1 );
	strcat( *str, new_part );
}

void json_object_stringify_key ( JSON_OBJECT* obj, char** str ) {
	json_str_object_concat( str, "\"" );
	json_str_object_concat( str, obj->key );
	json_str_object_concat( str, "\":" );
}

char* json_object_node_data_to_string ( JSON_OBJECT* node, char* tabe, size_t context ) {
	char* str = NULL;
	JSON_LIST* list = NULL;
	if ( node == NULL ) {
		fprintf( stderr, "%s:%u: Null pointer at json_object_node_to_string\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	if ( json_data_get_type( node->data ) == json_data_type_list ) {
		list = json_data_get_list( node->data );
		if ( list == NULL ) {
			fprintf( stderr, "%s:%u: Null pointer at json_object_to_string_beautify\n", __FILE__, __LINE__ );
			exit( -1 );
		}
		if ( tabe != NULL )
			str = json_list_to_string_beautify( list, tabe, ( context + 1 ) );
		else
			str = json_list_to_string( list );
	} else {
		str = json_data_to_string( node->data );
	}
	return str;
}

char* json_object_node_to_string ( JSON_OBJECT* node, char* tabe, size_t context ) {
	int i;
	char* str = NULL;
	char* tmp_str = NULL;
	JSON_LIST* list = NULL;
	if ( node == NULL ) {
		fprintf( stderr, "%s:%u: Null pointer at json_object_node_to_string\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	str = ( char* ) calloc( 1, sizeof( char ) );
	if ( str == NULL ) {
		fprintf( stderr, "%s:%u: Memory allocation fail at json_object_to_string_beautify\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	for ( i = 0; i < context; i++ )	json_str_object_concat( &str, tabe );
	json_object_stringify_key( node, &str );
	if ( tabe != NULL ) json_str_object_concat( &str, " " );
	tmp_str = json_object_node_data_to_string( node, tabe, context );
	json_str_object_concat( &str, tmp_str );
	free( tmp_str );
	if ( node->next != NULL && tabe != NULL ) {
		json_str_object_concat( &str, JSON_OBJECT_SEPARATOR );
		json_str_object_concat( &str, LINE_BREAK );
	}
	return str;
}

char* json_object_to_string ( JSON_OBJECT* obj ) {
	char* str = NULL;
	char* tmp_str = NULL;
	JSON_OBJECT* node = obj;
	if ( obj == NULL ) {
		fprintf( stderr, "%s:%u: Null pointer at json_object_to_string\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	str = ( char* ) calloc( strlen( JSON_OBJECT_OPEN ) + 1, sizeof( char ) );
	if ( str == NULL ) {
		fprintf( stderr, "%s:%u: Memory allocation fail at json_object_to_string\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	strcpy( str, JSON_OBJECT_OPEN );
	do {
		tmp_str = json_object_node_to_string( node, NULL, 0 );
		json_str_object_concat( &str, tmp_str );
		free( tmp_str );
		node = node->next;
		if ( node != NULL ) json_str_object_concat( &str, JSON_OBJECT_SEPARATOR );
	} while ( node );
	json_str_object_concat( &str, JSON_OBJECT_CLOSE );
	return str;
}

char* json_object_to_string_beautify ( JSON_OBJECT* obj, char* tabe, size_t context ) {
	int i;
	char* str = NULL;
	char* tmp_str = NULL;
	JSON_OBJECT* node = obj;
	if ( obj == NULL ) {
		fprintf( stderr, "%s:%u: Null pointer at json_object_to_string_beautify\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	str = ( char* ) calloc( strlen( JSON_OBJECT_OPEN ) + 1, sizeof( char ) );
	if ( str == NULL ) {
		fprintf( stderr, "%s:%u: Memory allocation fail at json_object_to_string_beautify\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	strcpy( str, JSON_OBJECT_OPEN );
	json_str_object_concat( &str, LINE_BREAK );
	do {
		tmp_str = json_object_node_to_string( node, tabe, context );
		json_str_object_concat( &str, tmp_str );
		free( tmp_str );
		node = node->next;
	} while ( node );
	json_str_object_concat( &str, LINE_BREAK );
	for ( i = 1; i < context; i++ )	json_str_object_concat( &str, tabe );
	json_str_object_concat( &str, JSON_OBJECT_CLOSE );
	return str;
}

JSON_OBJECT* json_object_get_last ( JSON_OBJECT* object ) {
	JSON_OBJECT* last = object;
	while ( last->next ) last = last->next;
	return last;
}

void json_object_destroy ( JSON_OBJECT** obj ) {
	if ( obj == NULL ) return;
	JSON_OBJECT* last = json_object_get_last( *obj );
	JSON_OBJECT* swap = NULL;
	do {
		if ( last->data != NULL ) json_data_destroy( &last->data );
		swap = last->prev;
		free( last );
		last = swap;
	} while ( last );
}

