#ifndef _JSON_H_
#define _JSON_H_

typedef struct JSON JSON;
typedef struct JSON_NODE JSON_NODE;
typedef struct JSON_PAIR JSON_PAIR;
typedef struct JSON_FINAL_VALUE JSON_FINAL_VALUE;

typedef enum json_type json_type;
typedef enum json_node_type json_node_type;
typedef enum json_pair_type json_pair_type;
typedef enum json_final_value_type json_final_value_type;

typedef union json_node_value json_node_value;
typedef union json_value json_value;

#define JSON_NULL 		"null"
#define JSON_TRUE 		"true"
#define JSON_FALSE 		"false"
#define JSON_UNDEFINE	"undefine"

enum json_type 
{
	json_object,
	json_list
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

union json_value
{
	char 		c;
	int			i;
	float 		f;
	double 		d;
	char* 		s;
	JSON_NODE*	jn;
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

JSON_NODE* json_node_new ( json_type type);
void json_node_destroy ( JSON_NODE** node );
JSON* json_new ( const json_type type );
void json_destroy ( JSON** json );
void json_object_add_str ( JSON* json, char* key, char* value );

#endif

