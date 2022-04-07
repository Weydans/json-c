#ifndef _JSON_H_
#define _JSON_H_

typedef struct JSON_DATA JSON_DATA;

JSON_DATA* json_data_new ();
void json_data_destroy ( JSON_DATA** data );

void json_data_add_char ( JSON_DATA* data, char charactere );
void json_data_add_integer ( JSON_DATA* data, long long int data_integer );
void json_data_add_double ( JSON_DATA* data, long double data_double );
void json_data_add_str ( JSON_DATA* data, char* data_str );
void json_data_add_bool ( JSON_DATA* data, bool data_bool );

char* json_data_to_string ( JSON_DATA* data );
char* json_data_list_to_string ( JSON_DATA* data, bool beautify );
void json_data_print ( JSON_DATA* data );

#endif

