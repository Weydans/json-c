#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

JSON_OBJECT* json_object_new ();
void json_object_add_str ( JSON_OBJECT* obj, char* key, char* value );
void json_object_add_char ( JSON_OBJECT* obj, char* key, char value );
void json_object_add_bool ( JSON_OBJECT* obj, char* key, bool value );
void json_object_add_integer ( JSON_OBJECT* obj, char* key, long long int value );
void json_object_add_double ( JSON_OBJECT* obj, char* key, long double value );
void json_object_add_list ( JSON_OBJECT* obj, char* key, JSON_LIST* list );
char* json_object_to_string ( JSON_OBJECT* obj );
char* json_object_to_string_beautify ( JSON_OBJECT* obj, char* tabe, size_t context );
void json_object_destroy ( JSON_OBJECT** obj );

#endif
