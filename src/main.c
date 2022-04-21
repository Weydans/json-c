#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/json-data.h"
#include "../include/json-list.h"
#include "../include/json-object.h"

int main ( int argc, char* argv[] ) {
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

	JSON_DATA* azul = json_data_new();
	json_data_add_str( azul, "Azul" );
	JSON_DATA* amarelo = json_data_new();
	json_data_add_str( amarelo, "Amarelo" );
	JSON_DATA* preto = json_data_new();
	json_data_add_str( preto, "Preto" );
	JSON_DATA* verde = json_data_new();
	json_data_add_str( verde, "Verde" );
	JSON_LIST* list = json_list_new();
	json_list_add( list, azul );
	json_list_add( list, amarelo );
	json_list_add( list, preto );
	json_list_add( list, verde );

	tmp_str = json_list_to_string( list );
	puts( tmp_str );
	free( tmp_str );

	json_list_dump( list );
	json_list_destroy( &list );

	JSON_OBJECT* livro = json_object_new();
	json_object_add_str( livro, "titulo", "Programando com orientação a objetos" );
	json_object_add_str( livro, "autor", "Pablo Dall'Oglio" );
	json_object_add_integer( livro, "num_paginas", 550 );
	tmp_str = json_object_to_string( livro );
	puts( tmp_str );
	free( tmp_str );
	
	tmp_str = json_object_to_string_beautify( livro, "    ", 1 );
	puts( tmp_str );
	free( tmp_str );
	
	json_object_destroy( &livro );

	return 0;
}

