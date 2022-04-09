#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/json.h"

int main ( int argc, char* argv[] )
{
	JSON_MAP* map = json_map_new();
	JSON_DATA* data = json_data_new();

	json_data_add_str( data, "Weydans Barros" );
	json_data_add_str( data, "Engenheiro de Software" );
	json_data_add_str( data, "(35) 9 9991-3005" );
	json_data_add_integer( data, 27 );
	json_data_add_double( data, 1.70 );
	json_data_add_char( data, 'A' );
	json_data_add_bool( data, false );
	
	//json_data_list_dump( data );

	json_map_add_list( map, "funcionario", data );
	json_map_dump( map );

	//json_data_destroy( &data );
	json_map_destroy( &map );
	
	return 0;
}

