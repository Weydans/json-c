#ifndef _JSON_H_
#define _JSON_H_

typedef struct JSON_MAP JSON_MAP;

// ============================================
// JSON_MAP
JSON_MAP* json_map_new ();
void json_map_destroy ( JSON_MAP** map );

void json_map_add_int( JSON_MAP* map, char* key, long long int data );
void json_map_add_char ( JSON_MAP* map, char* key, char data );
void json_map_add_list( JSON_MAP* map, char* key, JSON_DATA* data );
void json_map_dump( JSON_MAP* map );
char* json_map_to_string_beautify ( JSON_MAP* data, char* tabe, size_t context );

// ============================================
// JSON_DATA

#endif

