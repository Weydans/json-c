#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/json.h"

int main ( int argc, char* argv[] )
{
	JSON_DATA* data = json_data_new();

	json_data_add_char( data, 'a' );
	json_data_add_integer( data, 1234567890123456789 );
	json_data_add_str( data, "O rato roeu a roupa do rei de Roma." );
	json_data_add_double( data, 112.1234567890123456 );
	json_data_add_bool( data, false );
	
	json_data_print( data );
	json_data_destroy( &data );
	
	return 0;
}

