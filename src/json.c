#include <stdio.h>
#include <stdlib.h>
#include "../include/json.h"

struct JSON 
{
	json_type type;
	JSON_NODE* value;
};

struct JSON_NODE
{
	json_node_type type;
	json_node_value* value;
	JSON_NODE* prev;
	JSON_NODE* next;
};

struct JSON_FINAL_VALUE
{
	json_final_value_type 	type;
	json_final_value_value 	value;
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
	printf( "Json_node created\n" );

	node->type = type == json_object ? json_node_type_pair : json_node_type_final_value;
	node->value = NULL;

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
	printf( "Json created\n" );
	
	json->type = type;
	json->value = json_node_new( type ); 

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

