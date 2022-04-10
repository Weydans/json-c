#ifndef _JSON_H_
#define _JSON_H_

typedef struct JSON_DATA JSON_DATA;
typedef struct JSON_MAP JSON_MAP;

// ============================================
// JSON_MAP
JSON_MAP* json_map_new ();
void json_map_destroy ( JSON_MAP** map );

void json_map_add_int( JSON_MAP* map, char* key, long long int data );
void json_map_add_list( JSON_MAP* map, char* key, JSON_DATA* data );
void json_map_dump( JSON_MAP* map );

// ============================================
// JSON_DATA
JSON_DATA* json_data_new ();
void json_data_destroy ( JSON_DATA** data );

void json_data_add_char ( JSON_DATA* data, char charactere );
void json_data_add_integer ( JSON_DATA* data, long long int data_integer );
void json_data_add_double ( JSON_DATA* data, long double data_double );
void json_data_add_str ( JSON_DATA* data, char* data_str );
void json_data_add_bool ( JSON_DATA* data, bool data_bool );

char* json_data_to_string ( JSON_DATA* data );
char* json_data_list_to_string ( JSON_DATA* data );
char* json_data_list_to_string_beautify ( JSON_DATA* data, char* tabe, size_t context );
void json_data_print ( JSON_DATA* data );
void json_data_list_dump ( JSON_DATA* data );

#endif

