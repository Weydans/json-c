#ifndef _JSON_DATA_H_
#define _JSON_DATA_H_

typedef struct JSON_DATA JSON_DATA;
typedef enum json_data_type json_data_type; 

enum json_data_type
{
	json_data_type_integer,
	json_data_type_char,
	json_data_type_str,
	json_data_type_bool,
	json_data_type_double,
	json_data_type_list
};

JSON_DATA* json_data_new ();
void json_data_destroy ( JSON_DATA** data );

void json_data_add_str ( JSON_DATA* data, char* value );
void json_data_add_bool ( JSON_DATA* data, bool value );
void json_data_add_char ( JSON_DATA* data, char value );
void json_data_add_integer ( JSON_DATA* data, long long int value );
void json_data_add_double ( JSON_DATA* data, long double data_double );

char* json_data_to_string ( JSON_DATA* data );

#endif
