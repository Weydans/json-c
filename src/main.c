#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/json-data.h"

int main ( int argc, char* argv[] )
{
	char* tmp_str = NULL;

	JSON_DATA* str = json_data_new();
	json_data_add_str( str, "string simples" );
	tmp_str = json_data_to_string( str );
	printf( "%s\n", tmp_str );
	json_data_destroy( &str );
	free( tmp_str );

	JSON_DATA* integer = json_data_new();
	json_data_add_integer( integer, 16 );
	tmp_str = json_data_to_string( integer );
	printf( "%s\n", tmp_str );
	json_data_destroy( &integer );
	free( tmp_str );

	JSON_DATA* boolean = json_data_new();
	json_data_add_bool( boolean, false );
	tmp_str = json_data_to_string( boolean );
	printf( "%s\n", tmp_str );
	json_data_destroy( &boolean );
	free( tmp_str );

	JSON_DATA* charactere = json_data_new();
	json_data_add_char( charactere, 'C' );
	tmp_str = json_data_to_string( charactere );
	printf( "%s\n", tmp_str );
	json_data_destroy( &charactere );
	free( tmp_str );

	JSON_DATA* float_point = json_data_new();
	json_data_add_double( float_point, 1234567.1234567890 );
	tmp_str = json_data_to_string( float_point );
	printf( "%s\n", tmp_str );
	json_data_destroy( &float_point );
	free( tmp_str );

	return 0;
}

