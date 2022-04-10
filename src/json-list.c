#include <stdio.h>
#include <stdlib.h>
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

typedef enum json_data_type json_data_type; 
typedef union json_data_data json_data_data;

enum json_data_type
{
	json_data_type_integer,
	json_data_type_char,
	json_data_type_str,
	json_data_type_bool,
	json_data_type_double,
	json_data_type_list
};

struct JSON_DATA 
{
	json_data_type type;
	json_data_data* data;
	JSON_DATA* prev;
	JSON_DATA* next;
};

union json_data_data 
{
	long long int	data_integer;
	long double		data_double;
	char 			data_char;
	char*			data_str;
	bool			data_bool;
	JSON_DATA		data_list;
};

struct JSON_MAP
{
	json_data_type type;
	char* key;
	JSON_DATA* data;
	JSON_MAP* prev;
	JSON_MAP* next;
};

void json_data_destroy_all ( JSON_DATA* data );
JSON_DATA* json_data_get_last ( JSON_DATA* json_data );
void json_str_concat ( char** str, char* new_part );
static char* json_data_char_get_str ( JSON_DATA* data );
static char* json_data_integer_get_str ( JSON_DATA* data );
static char* json_data_double_get_str ( JSON_DATA* data );
static char* json_data_str_get_str ( JSON_DATA* data );
static char* json_data_bool_get_str ( JSON_DATA* data );
void json_data_fill ( JSON_DATA* json_data, void* data, json_data_type type );
void json_data_add ( JSON_DATA* json_data, void* data, json_data_type type );

JSON_DATA* json_data_new ()
{
	JSON_DATA* data = ( JSON_DATA* ) calloc( 1, sizeof( JSON_DATA ) );
	return data;
}

void json_data_destroy ( JSON_DATA** data )
{
	json_data_destroy_all( *data );
	
	data = NULL;
}

void json_data_destroy_all ( JSON_DATA* data )
{
	if ( data == NULL ) return;

	JSON_DATA* last = json_data_get_last( data );
	JSON_DATA* swap = NULL;

	do 	
	{
		if ( last->data != NULL )
		{
			free( last->data );
		}

		swap = last->prev;

		free( last );
		last = swap;
	} 
	while ( last );
}

void json_data_fill ( JSON_DATA* json_data, void* data, json_data_type type )
{
	if ( json_data == NULL ) 
	{
		fprintf( stderr, "json_data null pointer exception\n" );
		exit( 1 );
	}

	if ( json_data->data == NULL ) 
	{
		fprintf( stderr, "json_data->data null pointer exception\n" );
		exit( 1 );
	}

	switch ( json_data->type )
	{
		case json_data_type_char:
			json_data->data->data_char = *( ( char* ) data );
			break;
		
		case json_data_type_integer:
			json_data->data->data_integer = *( ( long long int* ) data );
			break;

		case json_data_type_double:
			json_data->data->data_double = *( ( long double* ) data );
			break;

		case json_data_type_str:
			json_data->data->data_str = ( char* ) data;
			break;

		case json_data_type_bool:
			json_data->data->data_bool = *( ( bool* ) data );
			break;
	}
}

JSON_DATA* json_data_get_last ( JSON_DATA* json_data )
{
	JSON_DATA* last = json_data;

	while ( last->next ) last = last->next;

	return last;
}

void json_data_add ( JSON_DATA* json_data, void* data, json_data_type type )
{
	if ( json_data == NULL ) json_data = json_data_new();

	if ( json_data->data == NULL )
	{
		json_data->data = ( json_data_data* ) calloc( 1, sizeof( json_data_data ) );
		json_data->type = type;
		json_data_fill( json_data, data, type );
	}
	else if ( json_data->data != NULL )
	{
		JSON_DATA* last  = json_data_get_last( json_data );
		last->next 		 = json_data_new();
		last->next->data = ( json_data_data* ) calloc( 1, sizeof( json_data_data ) );
		last->next->type = type;
		last->next->prev = last;
		json_data_fill( last->next, data, type );
	}
}

void json_data_add_char ( JSON_DATA* data, char charactere )
{
	json_data_add( data, &charactere, json_data_type_char );
}

void json_data_add_integer ( JSON_DATA* data, long long int data_integer )
{
	json_data_add( data, &data_integer, json_data_type_integer );
}

void json_data_add_double ( JSON_DATA* data, long double data_double )
{
	json_data_add( data, &data_double, json_data_type_double );
}

void json_data_add_str ( JSON_DATA* data, char* data_str )
{
	json_data_add( data, data_str, json_data_type_str );
}

void json_data_add_bool ( JSON_DATA* data, bool data_bool )
{
	json_data_add( data, &data_bool, json_data_type_bool );
}

int get_number_of_digits_on_integer ( long long int number )
{
	int i; 
	for ( i = 0; number > 0; number /= 10, i++ ); 
	return i;
}

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

static char* json_data_char_get_str ( JSON_DATA* data )
{
	size_t num_members = strlen( JSON_MASK_CHAR ) + strlen( "\0" );

	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	
	sprintf( buffer, JSON_MASK_CHAR, data->data->data_char );

	return buffer;
}

static char* json_data_integer_get_str ( JSON_DATA* data )
{
	size_t num_members = strlen( JSON_MASK_INTEGER ) + get_number_of_digits_on_integer( data->data->data_integer );

	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );

	sprintf( buffer, JSON_MASK_INTEGER, data->data->data_integer );
	
	return buffer;
}

static char* json_data_double_get_str ( JSON_DATA* data )
{
	//size_t num_members = strlen( JSON_MASK_DOUBLE ) + get_number_of_digits_on_double( data->data->data_double );
	size_t num_members = strlen( JSON_MASK_DOUBLE ) + 50;

	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	
	sprintf( buffer, JSON_MASK_DOUBLE, data->data->data_double );
	
	return buffer;
}

static char* json_data_str_get_str ( JSON_DATA* data )
{
	size_t num_members = strlen( JSON_MASK_STR ) + strlen( data->data->data_str );

	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	
	sprintf( buffer, JSON_MASK_STR, data->data->data_str );
	
	return buffer;
}

static char* json_data_bool_get_str ( JSON_DATA* data )
{
	size_t num_members = strlen( JSON_MASK_BOOL ) + strlen( data->data->data_bool ? JSON_DATA_TRUE : JSON_DATA_FALSE );

	char* buffer = ( char* ) calloc( num_members, sizeof( char ) );
	
	sprintf( buffer, JSON_MASK_BOOL, ( data->data->data_bool ? JSON_DATA_TRUE : JSON_DATA_FALSE ) );
	
	return buffer;
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

