#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/json.h"

int main ( int argc, char* argv[] )
{
	JSON_DATA* data = json_data_new();

	json_data_add_str( data, "Weydans Barros" );
	json_data_add_str( data, "Engenheiro de Software" );
	json_data_add_str( data, "(35) 9 9991-3005" );
	json_data_add_integer( data, 27 );
	json_data_add_double( data, 1.70 );
	json_data_add_char( data, 'A' );
	json_data_add_bool( data, false );
	
	char* str = json_data_list_to_string( data, true );
	puts( str );

	free( str );
	json_data_destroy( &data );
	
	return 0;
}

