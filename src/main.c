#include <stdio.h>
#include <stdlib.h>
#include "../include/json.h"

int main ( int argc, char* argv[] )
{
	printf( "Hello World!\n" );

	JSON* pessoa = json_new( json_object );

	json_object_add_str( pessoa, "nome", "Weydans Barros" );

	json_destroy( &pessoa );
	
	return 0;
}

