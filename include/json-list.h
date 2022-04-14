#ifndef _JSON_LIST_H_
#define _JSON_LIST_H_

#include "../include/json-data.h"

typedef struct JSON_LIST JSON_LIST;

JSON_LIST* json_list_new ();
void json_list_destroy ( JSON_LIST** list );
void json_list_add( JSON_LIST* list, JSON_DATA* data );
char* json_list_to_string ( JSON_LIST* list );
char* json_list_to_string_beautify ( JSON_LIST* list, char* tabe, size_t context );
void json_list_dump ( JSON_LIST* list );

#endif
