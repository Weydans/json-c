#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/json.h"

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
	json_data_type type;
	json_data_data* data;
	JSON_DATA* prev;
	JSON_DATA* next;
};

void json_data_destroy_all ( JSON_DATA* data );
JSON_DATA* json_data_get_last ( JSON_DATA* json_data );

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

char* json_data_list_join( JSON_DATA* data, char* separator )
{
	JSON_DATA* json_swap = data;
	int str_old_size = 2;
	int str_new_size = 0;
	char* temp_string = NULL;
	char* str = ( char* ) calloc( str_old_size, sizeof( char ) );

	do
	{
		if ( json_swap != NULL || json_swap->data != NULL)
		{
			temp_string	 = json_data_to_string( json_swap );
			str_old_size = strlen( str ) + 1;
			str_new_size = str_old_size + strlen( temp_string ) + 1;
			str 		 = realloc( str, str_new_size );

			strcat( str, temp_string );

			if ( json_swap->next != NULL && json_swap->next->data != NULL)
			{
				str_old_size = strlen( str ) + 1;
				str_new_size = str_old_size + strlen( separator ) + 1;
				str = realloc( str, str_new_size );
				strcat( str, separator );
			}

			free( temp_string );
		}
	}
	while ( json_swap = json_swap->next );

	return str;
}

char* json_data_list_to_string ( JSON_DATA* data, bool beautify )
{
	char* list_joined = NULL;
	char* list_str = ( char* ) calloc( 2, sizeof( char ) );

	strcpy( list_str, "[" );

	if ( beautify )
	{
		list_str = realloc( list_str, strlen( list_str ) + 1 + strlen( "\n\t" ) + 1 );
		strcat( list_str, "\n\t" );
	}

	list_joined = json_data_list_join( data, beautify ? ",\n\t" : "," );
	list_str 	= realloc( list_str, strlen( list_str ) + 1 + strlen( list_joined ) + 1 );
	
	strcat( list_str, list_joined );

	if ( beautify )
	{
		list_str = realloc( list_str, strlen( list_str ) + 1 + strlen( "\n" ) + 1 );
		strcat( list_str, "\n" );
	}

	strcat( list_str, "]" );

	free( list_joined );

	return list_str;
}

void json_data_print ( JSON_DATA* data )
{
	char* data_str = json_data_to_string( data );

	printf( "%s\n", data_str );
	
	free( data_str );
}

