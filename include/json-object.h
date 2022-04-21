#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

typedef struct JSON_OBJECT JSON_OBJECT;

JSON_OBJECT* json_object_new ();
void json_object_add_str ( JSON_OBJECT* obj, char* key, char* value );
void json_object_add_integer ( JSON_OBJECT* obj, char* key, long long int value );
char* json_object_to_string ( JSON_OBJECT* obj );
char* json_object_to_string_beautify ( JSON_OBJECT* obj, char* tabe, size_t context );
void json_object_destroy ( JSON_OBJECT** obj );

#endif
