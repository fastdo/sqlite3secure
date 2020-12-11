#include <iostream>
#include <string>
#include <sqlite3.h>
#include <stdio.h>
using namespace std;

int main()
{

	cout << sqlite3_threadsafe();
	int rc;
	sqlite3 * db = NULL;
	const char * localError = "Out of memory";
	string encryptKey = "";
	
	rc = sqlite3_open_v2( "test.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );
	if ( rc != SQLITE_OK ) goto OccurDbError;
	// 开启外键约束
	rc = sqlite3_exec( db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL );
	if ( rc != SQLITE_OK ) goto OccurDbError;
	rc = sqlite3_extended_result_codes( db, 1 );
	if ( rc != SQLITE_OK ) goto OccurDbError;
	
	// 如果有密码
	if ( encryptKey.size() > 0 )
	{
		rc = sqlite3_key( db, encryptKey.c_str(), (int)encryptKey.size() );
		if ( rc != SQLITE_OK ) goto OccurDbError;
	}
	
	// 新建一张表
	rc = sqlite3_exec( db, "create table user( id integer , name varchar(32) )", NULL, NULL, NULL );
	if ( rc != SQLITE_OK ) goto OccurDbError;
	

	// 关闭数据库
	sqlite3_close(db);
	
	return 0;
OccurDbError:
	if ( db )
	{
		localError = sqlite3_errmsg(db);
		sqlite3_close(db);
	}
	printf( "%s\n", localError );
	return 1;//*/
}