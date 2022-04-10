#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/json-data.h"

#define LINE_BREAK			"\n"

#define	JSON_LIST_OPEN		"["
#define	JSON_LIST_CLOSE		"]"
#define	JSON_LIST_SEPARATOR	","

#define JSON_MASK_INTEGER 	"%lld"
#define JSON_MASK_DOUBLE	"%.10Lf"
#define JSON_MASK_BOOL		"%s"
#define JSON_MASK_CHAR 		"\"%c\""
#define JSON_MASK_STR 		"\"%s\""

#define JSON_DATA_TRUE 		"true"
#define JSON_DATA_FALSE		"false"

typedef union json_data_value json_data_value;

struct JSON_DATA 
{
	json_data_type type;
	json_data_value* value;
};

union json_data_value 
{
	long long int	data_integer;
	long double		data_double;
	char 			data_char;
	char*			data_str;
	bool			data_bool;
	//JSON_LIST		data_list;
};

static void json_data_add ( JSON_DATA* data, void* value, json_data_type type );
static char* json_data_char_get_str ( JSON_DATA* data );
static int get_number_of_digits_on_integer ( long long int number );
static char* json_data_integer_get_str ( JSON_DATA* data );
static char* json_data_double_get_str ( JSON_DATA* data );
//static char* json_data_str_get_str ( JSON_DATA* data );
static char* json_data_bool_get_str ( JSON_DATA* data );

JSON_DATA* json_data_new () {
	JSON_DATA* data = ( JSON_DATA* ) calloc( 1, sizeof( JSON_DATA ) );
	data->value = ( json_data_value* ) calloc( 1, sizeof( json_data_value ) );
	return data; 
}

static void json_data_add ( JSON_DATA* data, void* value, json_data_type type ) {
	data->type = type;
	switch ( type )
	{
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
	switch ( data->type )
	{
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

void json_data_destroy ( JSON_DATA** data )
{
	if ( *data == NULL ) return;
	if ( ( *data )->value != NULL ) free( ( *data )->value );
	free( *data );
	data = NULL;
}


// =============================================================

/*
int get_number_of_digits_on_double ( long double number )
{
	long long int integer_part 	= ( long long int ) number;
	long double decimal_part 	= number - integer_part;
	int i 						= get_number_of_digits_on_integer( integer_part ); 

	for ( i = ++i; decimal_part > 0; i++ )
	{
		integer_part  = ( long long int ) decimal_part;
		decimal_part  = decimal_part - integer_part;
		decimal_part *= 10;
	}

	return i;
}

char* json_data_to_string ( JSON_DATA* data )
{
	char* buffer = NULL;

	switch ( data->type )
	{
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

char* json_data_list_to_string ( JSON_DATA* data )
{
	JSON_DATA* next_node = data;
	size_t str_initial_size = strlen( JSON_LIST_OPEN ) + 1;
	size_t str_current_size = str_initial_size;
	char* json_data_str = NULL;
	char* str = ( char* ) calloc( str_initial_size, sizeof( char ) );

	if ( data != NULL )
	{
		strcpy( str, JSON_LIST_OPEN );

		do
		{
			json_data_str = json_data_to_string( next_node );
			str_current_size += strlen( json_data_str );
			str = realloc( str, str_current_size );
			strcat( str, json_data_str );
			free( json_data_str );

			next_node = next_node->next;

			if ( next_node != NULL )
			{
				str = realloc( str, str_current_size += strlen( JSON_LIST_SEPARATOR ) );
				strcat( str, JSON_LIST_SEPARATOR );
			}
		}
		while( next_node );

		str = realloc( str, str_current_size += strlen( JSON_LIST_CLOSE ) );
		strcat( str, JSON_LIST_CLOSE );
	}

	return str;
}

void json_str_concat ( char** str, char* new_part )
{
	*str = realloc( *str, strlen( *str ) + strlen( new_part ) + 1 );
	strcat( *str, new_part );
}

char* json_data_list_to_string_beautify ( JSON_DATA* data, char* tabe, size_t context )
{
	int i = 0;
	JSON_DATA* next_node = data;
	char* json_data_str = NULL;
	char* str = ( char* ) calloc( strlen( JSON_LIST_OPEN ) + 1, sizeof( char ) );

	if ( data == NULL ) return str;

	strcpy( str, JSON_LIST_OPEN );
	json_str_concat( &str, LINE_BREAK );

	do
	{
		for ( i = 0; i < context; i++ )	json_str_concat( &str, tabe );

		json_data_str = json_data_to_string( next_node );
		json_str_concat( &str, json_data_str );
		free( json_data_str );

		next_node = next_node->next;

		if ( next_node != NULL )
		{
			json_str_concat( &str, JSON_LIST_SEPARATOR );
			json_str_concat( &str, LINE_BREAK );
		}
	}
	while( next_node );

	json_str_concat( &str, LINE_BREAK );

	for ( i = 1; i < context; i++ )	json_str_concat( &str, tabe );

	json_str_concat( &str, JSON_LIST_CLOSE );

	return str;
}

void json_data_print ( JSON_DATA* data )
{
	char* str = json_data_list_to_string( data );
	puts( str );
	free( str );
}

void json_data_list_dump ( JSON_DATA* data )
{
	char* str = json_data_list_to_string_beautify( data, "    ", 1 );
	puts( str );
	free( str );
}

*/
