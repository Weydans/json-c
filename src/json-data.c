#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/json-data.h"

#define JSON_MASK_INTEGER 	"%lld"
#define JSON_MASK_DOUBLE	"%.10Lf"
#define JSON_MASK_BOOL		"%s"
#define JSON_MASK_CHAR 		"\"%c\""
#define JSON_MASK_STR 		"\"%s\""
#define JSON_DATA_TRUE 		"true"
#define JSON_DATA_FALSE		"false"

typedef union json_data_value json_data_value;

struct JSON_DATA {
	json_data_type type;
	json_data_value* value;
};

union json_data_value {
	long long int	data_integer;
	long double		data_double;
	char 			data_char;
	char*			data_str;
	bool			data_bool;
	JSON_LIST*		data_list;
};

static void json_data_add ( JSON_DATA* data, void* value, json_data_type type );
static char* json_data_char_get_str ( JSON_DATA* data );
static int get_number_of_digits_on_integer ( long long int number );
static char* json_data_integer_get_str ( JSON_DATA* data );
static char* json_data_double_get_str ( JSON_DATA* data );
static char* json_data_str_get_str ( JSON_DATA* data );
static char* json_data_bool_get_str ( JSON_DATA* data );

JSON_DATA* json_data_new () {
	JSON_DATA* data = ( JSON_DATA* ) calloc( 1, sizeof( JSON_DATA ) );
	data->value = ( json_data_value* ) calloc( 1, sizeof( json_data_value ) );
	if ( data == NULL || data->value == NULL ) {
		fprintf( stderr, "%s:%u: Memmory allocation fail\n", __FILE__, __LINE__ );
		exit( -1 );
	}
	return data; 
}

static void json_data_add ( JSON_DATA* data, void* value, json_data_type type ) {
	data->type = type;
	switch ( type )	{
		case json_data_type_char:
			data->value->data_char = *( ( char* ) value );
			break;
		case json_data_type_integer:
			data->value->data_integer =  *( ( long long int* ) value );
			break;
		case json_data_type_double:
			data->value->data_double = *( ( long double* ) value );
			break;
		case json_data_type_str:
			data->value->data_str = ( char* ) value;
			break;
		case json_data_type_bool:
			data->value->data_bool = *( ( bool* ) value );
			break;
		case json_data_type_list:
			data->value->data_list = ( JSON_LIST* ) value;
			break;
	}	
}

void json_data_add_integer ( JSON_DATA* data, long long int value ) {
	json_data_add( data, &value, json_data_type_integer );
}

void json_data_add_str ( JSON_DATA* data, char* value ) {
	json_data_add( data, value, json_data_type_str );
}

void json_data_add_bool ( JSON_DATA* data, bool value ) {
	json_data_add( data, &value, json_data_type_bool );
}

void json_data_add_char ( JSON_DATA* data, char value ) {
	json_data_add( data, &value, json_data_type_char );
}

void json_data_add_double ( JSON_DATA* data, long double value ) {
	json_data_add( data, &value, json_data_type_double );
}

void json_data_add_list ( JSON_DATA* data, JSON_LIST* list ) {
	json_data_add( data, list, json_data_type_list );
}

static char* json_data_char_get_str ( JSON_DATA* data ) {
	size_t num_members = strlen( JSON_MASK_CHAR ) + strlen( "\0" );
	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	sprintf( buffer, JSON_MASK_CHAR, data->value->data_char );
	return buffer;
}

static int get_number_of_digits_on_integer ( long long int number ) {
	int i; 
	for ( i = 0; number > 0; number /= 10, i++ ); 
	return i;
}

static char* json_data_integer_get_str ( JSON_DATA* data ) {
	size_t num_members = strlen( JSON_MASK_INTEGER ) + get_number_of_digits_on_integer( data->value->data_integer );
	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	sprintf( buffer, JSON_MASK_INTEGER, data->value->data_integer );
	return buffer;
}

static char* json_data_double_get_str ( JSON_DATA* data ) {
	size_t num_members = strlen( JSON_MASK_DOUBLE ) + 50;
	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	sprintf( buffer, JSON_MASK_DOUBLE, data->value->data_double );
	return buffer;
}

static char* json_data_str_get_str ( JSON_DATA* data ) {
	size_t num_members = strlen( JSON_MASK_STR ) + strlen( data->value->data_str );
	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	sprintf( buffer, JSON_MASK_STR, data->value->data_str );
	return buffer;
}

static char* json_data_bool_get_str ( JSON_DATA* data ) {
	size_t num_members = strlen( JSON_MASK_BOOL ) + strlen( data->value->data_bool ? JSON_DATA_TRUE : JSON_DATA_FALSE );
	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	sprintf( buffer, JSON_MASK_BOOL, ( data->value->data_bool ? JSON_DATA_TRUE : JSON_DATA_FALSE ) );
	return buffer;
}

char* json_data_to_string ( JSON_DATA* data ) {
	char* buffer = NULL;
	switch ( data->type ) {
		case json_data_type_char:
			buffer = json_data_char_get_str( data );
			break;
		case json_data_type_integer:
			buffer = json_data_integer_get_str( data );
			break;
		case json_data_type_double:
			buffer = json_data_double_get_str( data );
			break;
		case json_data_type_str:
			buffer = json_data_str_get_str( data );
			break;
		case json_data_type_bool:
			buffer = json_data_bool_get_str( data );
			break;
	}
	return buffer;
}

json_data_type json_data_get_type ( JSON_DATA* data ) {
	if ( data == NULL ) {
		fprintf( stderr, "json_data_get_type null pointer exception\n" );
		exit( 1 );
	}
	return data->type;
}

JSON_LIST* json_data_get_list ( JSON_DATA* data ) {
	if ( data == NULL ) {
		fprintf( stderr, "json_data_get_type null pointer exception\n" );
		exit( 1 );
	}
	return data->value->data_list;
}

void json_data_destroy ( JSON_DATA** data ) {
	if ( *data == NULL ) return;
	if ( ( *data )->value != NULL ) free( ( *data )->value );
	free( *data );
	data = NULL;
}

