#include <stdio.h>
#include <stdlib.h>

typedef enum bool bool;

enum bool
{
	false,
	true
};

typedef struct JSON JSON;
typedef struct JSON_NODE JSON_NODE;
typedef struct JSON_PAIR JSON_PAIR;
typedef struct JSON_FINAL_VALUE JSON_FINAL_VALUE;

typedef enum json_type json_type;
typedef enum json_node_type json_node_type;
typedef enum json_pair_type json_pair_type;
typedef enum json_final_value_type json_final_value_type;

typedef union json_node_value json_node_value;
typedef union json_pair_value json_pair_value;
typedef union json_final_value_value json_final_value_value;

typedef char* json_null_t;
const json_null_t null = "null";

typedef char* json_bool_t;
const json_bool_t json_true  = "true";
const json_bool_t json_false = "false";

typedef char* json_undefined_t;
const json_undefined_t undefined = "undefined";

enum json_type 
{
	json_object,
	json_list
};

struct JSON 
{
	json_type type;
	JSON_NODE* value;
};

enum json_node_type
{
	json_node_type_pair,
	json_node_type_final_value
};

union json_node_value
{
	JSON_PAIR* 			json_pair;
	JSON_FINAL_VALUE*	json_final_value;
};

struct JSON_NODE
{
	json_node_type type;
	json_node_value* value;
	JSON_NODE* prev;
	JSON_NODE* next;
};

enum json_final_value_type
{
	json_final_value_type_char,
	json_final_value_type_int,
	json_final_value_type_float,
	json_final_value_type_double,
	json_final_value_type_str,
	json_final_value_type_json_object,
	json_final_value_type_json_list,
	json_final_value_type_null,
	json_final_value_type_bool,
	json_final_value_type_undefined
};

union json_final_value_value
{
	char 				c;
	int					i;
	float 				f;
	double 				d;
	char* 				s;
	JSON_NODE*			jn;
	json_null_t			n;
	json_bool_t			b;
	json_undefined_t	u;
};

struct JSON_FINAL_VALUE
{
	json_final_value_type 	type;
	json_final_value_value 	value;
};

enum json_pair_type
{
	json_pair_type_char,
	json_pair_type_int,
	json_pair_type_float,
	json_pair_type_double,
	json_pair_type_str,
	json_pair_type_json_object,
	json_pair_type_json_list,
	json_pair_type_null,
	json_pair_type_bool,
	json_pair_type_undefined
};

union json_pair_value
{
	char 				c;
	int					i;
	float 				f;
	double 				d;
	char* 				s;
	JSON_NODE*			jn;
	json_null_t			n;
	json_bool_t			b;
	json_undefined_t	u;
};

struct JSON_PAIR
{
	json_pair_type 		type;
	char* 				key;
	JSON_FINAL_VALUE 	value;
};

JSON_NODE* json_node_new ( json_type type)
{
	JSON_NODE* node = NULL;

	node = ( JSON_NODE* ) calloc( 1, sizeof( JSON_NODE ) );

	node->type = type == json_object ? json_node_type_pair : json_node_type_final_value;
	node->value = NULL;

	printf( "Json_node created\n" );
	return node;
}

void json_node_destroy ( JSON_NODE** node )
{
	if ( *node != NULL )
	{
		free( *node );
		node = NULL;
		printf( "Json_node destroyed\n" );
	}
}

JSON* json_new ( const json_type type )
{
	JSON* json = NULL;
	
	json = ( JSON* ) calloc( 1, sizeof( JSON ) );
	
	json->type = type;
	json->value = json_node_new( type ); 

	printf( "Json created\n" );
	return json;
}

void json_destroy ( JSON** json )
{
	if ( *json != NULL )
	{
		if ( ( *json )->value != NULL )
		{
			json_node_destroy( &( *json )->value );
		}

		free( *json );
		json = NULL;
		printf( "Json destroyed\n" );
	}
}

void json_object_add_str ( JSON* json, char* key, char* value )
{
}

int main ( int argc, char* argv[] )
{
	printf( "Hello World!\n" );

	JSON* pessoa = json_new( json_object );

	json_object_add_str( pessoa, "nome", "Weydans Barros" );

	json_destroy( &pessoa );
	
	return 0;
}

