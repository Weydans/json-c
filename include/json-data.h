#ifndef _JSON_DATA_H_
#define _JSON_DATA_H_

#include <stdbool.h>
#include "json.h"

JSON_DATA* json_data_new ();
void json_data_add_str ( JSON_DATA* data, char* value );
void json_data_add_bool ( JSON_DATA* data, bool value );
void json_data_add_char ( JSON_DATA* data, char value );
void json_data_add_integer ( JSON_DATA* data, long long int value );
void json_data_add_double ( JSON_DATA* data, long double data_double );
void json_data_add_list ( JSON_DATA* data, JSON_LIST* list );
char* json_data_to_string ( JSON_DATA* data );
json_data_type json_data_get_type ( JSON_DATA* data );
JSON_LIST* json_data_get_list ( JSON_DATA* data );
void json_data_destroy ( JSON_DATA** data );

#endif
