<?php

$db_host = "localhost"; // db가 있는 host
$db_user = "root"; // db에 접속할 계정 id
$db_pw = "tjdals12"; // db password

$db = mysql_connect($db_host, $db_user, $db_pw, ""); // db login

if(!$db) die("Connection failed: ". mysql_error()); // db alive check

// $query = mysql_query('show databases;'); // query : database list 보기

// if(!$query) echo "query failed";
// else {
// 	while($instance = mysql_fetch_assoc($query)) {
// 		print_r($instance);
// 		echo "<br>";
// 	}
// }

$dbName = 'sosfinder_sm';
$tableName = 'tb_upfile_info';

$query = mysql_query('use '.$dbName.';'); // query: 해당 table의 database 사용 선언

// $query = mysql_query('desc '.$tableName.';'); // query: 해당 table의 구조 보기

// if(!$query) echo "query failed";
// else {
// 	while($instance = mysql_fetch_assoc($query)) {
// 		foreach($instance as $key => $value) {
// 			echo "$key: $value\t";
// 		}
// 		echo "<br>";
// 	}
// }

//$query = "insert into tb_upfile_info (tx_file_name, vc_file_ext, tx_file_path, vc_user_name) VALUES ('test', 'abc', 'path', 'seongmin');";

$test = 'test';

$query = "insert into tb_upfile_info (tx_file_name, vc_file_ext, tx_file_path, vc_user_name) VALUES ('$test', '$test', '$test', 'seongmin');";

mysql_query($query); // query: 해당 table에 원소 추가


$query = mysql_query('select * from '.$tableName.';'); // query: 해당 table의 원소 검색

if(!$query) echo "select query failed";
else {
	while($instance = mysql_fetch_assoc($query)) {
		foreach($instance as $key => $value) {
			echo "$key: $value\t";
		}
		echo "<br>";
	}
}

mysql_free_result($query);
mysql_close($db);

?>