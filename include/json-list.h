#ifndef _JSON_LIST_H_
#define _JSON_LIST_H_

#include <stdbool.h>
#include "json.h"

JSON_LIST* json_list_new ();
void json_list_add( JSON_LIST* list, JSON_DATA* data );
void json_list_add_str ( JSON_LIST* list, char* value );
void json_list_add_char ( JSON_LIST* list, char value );
void json_list_add_bool ( JSON_LIST* list, bool value );
void json_list_add_integer ( JSON_LIST* list, long long int value );
void json_list_add_double ( JSON_LIST* list, long double value );
char* json_list_to_string ( JSON_LIST* list );
char* json_list_to_string_beautify ( JSON_LIST* list, char* tabe, size_t context );
void json_list_dump ( JSON_LIST* list );
void json_list_destroy ( JSON_LIST** list );

#endif
