#ifndef _JSON_H_
#define _JSON_H_

typedef struct JSON_LIST JSON_LIST;
typedef struct JSON_OBJECT JSON_OBJECT;
typedef struct JSON_DATA JSON_DATA;
typedef enum json_data_type json_data_type; 

enum json_data_type {
	json_data_type_integer,
	json_data_type_char,
	json_data_type_str,
	json_data_type_bool,
	json_data_type_double,
	json_data_type_list,
	json_data_type_object
};

#endif

