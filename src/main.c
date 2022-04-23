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
	puts( tmp_str );
	json_data_destroy( &str );
	free( tmp_str );

	JSON_DATA* integer = json_data_new();
	json_data_add_integer( integer, 16 );
	tmp_str = json_data_to_string( integer );
	puts( tmp_str );
	json_data_destroy( &integer );
	free( tmp_str );

	JSON_DATA* boolean = json_data_new();
	json_data_add_bool( boolean, false );
	tmp_str = json_data_to_string( boolean );
	puts( tmp_str );
	json_data_destroy( &boolean );
	free( tmp_str );

	JSON_DATA* charactere = json_data_new();
	json_data_add_char( charactere, 'C' );
	tmp_str = json_data_to_string( charactere );
	puts( tmp_str );
	json_data_destroy( &charactere );
	free( tmp_str );

	JSON_DATA* float_point = json_data_new();
	json_data_add_double( float_point, 1234567.1234567890 );
	tmp_str = json_data_to_string( float_point );
	puts( tmp_str );
	json_data_destroy( &float_point );
	free( tmp_str );

	JSON_DATA* cadeia_de_caracteres = json_data_new();
	json_data_add_str( cadeia_de_caracteres, "Linguagem C" );
	JSON_DATA* numero_inteiro = json_data_new();
	json_data_add_integer( numero_inteiro, 1988456 );
	JSON_DATA* numero_decimal = json_data_new();
	json_data_add_double( numero_decimal, 3.142596 );
	charactere = json_data_new();
	json_data_add_char( charactere, 'W' );
	JSON_DATA* boleano = json_data_new();
	json_data_add_bool( boleano, false );

	JSON_LIST* list = json_list_new();
	json_list_add( list, cadeia_de_caracteres );
	json_list_add( list, numero_inteiro );
	json_list_add( list, numero_decimal );
	json_list_add( list, charactere );
	json_list_add( list, boleano );

	tmp_str = json_list_to_string( list );
	puts( tmp_str );
	free( tmp_str );

	json_list_dump( list );
	json_list_destroy( &list );

	list = json_list_new();
	json_list_add_str( list, "Rodrigo Mello" );
	json_list_add_integer( list, 10 );
	json_list_add_double( list, 3.141596 );
	json_list_add_char( list, 'A' );
	json_list_add_bool( list, true );

	tmp_str = json_list_to_string( list );
	puts( tmp_str );
	free( tmp_str );

	json_list_dump( list );
	json_list_destroy( &list );

	JSON_LIST* datas_lancamento = json_list_new();
	json_list_add_integer( datas_lancamento, 2004 );
	json_list_add_integer( datas_lancamento, 2008 );
	json_list_add_integer( datas_lancamento, 2015 );
	tmp_str = json_list_to_string( datas_lancamento );
	puts( tmp_str );
	free( tmp_str );
	
	JSON_OBJECT* livro = json_object_new();
	json_object_add_str( livro, "titulo", "Programando com orientação a objetos" );
	json_object_add_str( livro, "autor", "Pablo Dall'Oglio" );
	json_object_add_integer( livro, "num_paginas", 550 );
	json_object_add_double( livro, "valor", 119.90 );
	json_object_add_char( livro, "classificacao", 'A' );
	json_object_add_bool( livro, "disponivel_para_venda", true );
	json_object_add_list( livro, "datas_lancamento", datas_lancamento );
	
	tmp_str = json_object_to_string( livro );
	puts( tmp_str );
	free( tmp_str );
	
	tmp_str = json_object_to_string_beautify( livro, "    ", 1 );
	puts( tmp_str );
	free( tmp_str );
	
	json_list_destroy( &datas_lancamento );
	json_object_destroy( &livro );

	return 0;
}

