#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/json.h"

#define JSON_MASK_INTEGER 	"%lld"
#define JSON_MASK_DOUBLE	"%.25Lf"
#define JSON_MASK_BOOL		"%s"
#define JSON_MASK_CHAR 		"\"%c\""
#define JSON_MASK_STR 		"\"%s\""

#define JSON_DATA_TRUE 		"true"
#define JSON_DATA_FALSE		"false"

typedef union json_data_data json_data_data;

enum json_data_type
{
	json_data_type_integer,
	json_data_type_char,
	json_data_type_str,
	json_data_type_bool,
	json_data_type_double
};

union json_data_data 
{
	long long int	data_integer;
	long double		data_double;
	char 			data_char;
	char*			data_str;
	bool			data_bool;
};

struct JSON_DATA 
{
	enum json_data_type type;
	json_data_data* data;
	JSON_DATA* prev;
	JSON_DATA* next;
};

JSON_DATA* json_data_new ()
{
	JSON_DATA* data = ( JSON_DATA* ) calloc( 1, sizeof( JSON_DATA ) );
	data->data = ( json_data_data* ) calloc( 1, sizeof( json_data_data ) );

	return data;
}

void json_data_destroy ( JSON_DATA** data )
{
	if ( *data != NULL )
	{
		if ( ( *data )->data != NULL )
		{
			free( ( *data )->data );
		}

		free( *data );
		data = NULL;
	}
}

void json_data_add_char ( JSON_DATA* data, char charactere )
{
	data->type = json_data_type_char;
	data->data->data_char = charactere;
}

void json_data_add_integer ( JSON_DATA* data, long long int data_integer )
{
	data->type = json_data_type_integer;
	data->data->data_integer = data_integer;
}

void json_data_add_double ( JSON_DATA* data, long double data_double )
{
	data->type = json_data_type_double;
	data->data->data_double = data_double;
}

void json_data_add_str ( JSON_DATA* data, char* data_str )
{
	data->type = json_data_type_str;
	data->data->data_str = data_str;
}

void json_data_add_bool ( JSON_DATA* data, bool data_bool )
{
	data->type = json_data_type_bool;
	data->data->data_bool = data_bool;
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
	size_t num_members = strlen( JSON_MASK_DOUBLE ) + get_number_of_digits_on_double( data->data->data_double );

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

void json_data_print ( JSON_DATA* data )
{
	char* data_str = json_data_to_string( data );

	printf( "%s\n", data_str );
	
	free( data_str );
}

