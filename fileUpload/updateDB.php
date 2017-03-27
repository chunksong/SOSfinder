<?php

function updateDB($dbHost, $dbUser, $dbPasswd, $dbName, $tableName, $upfileName, $upfileExt, $upfilePath, $upfileUserName) {
	///////////////// DB Connection ////////////////////

	$db = mysql_connect($dbHost, $dbUser, $dbPasswd, ""); // db login

	if(!$db) die("Connection failed: ". mysql_error()); // db alive check

	$query = mysql_query('use '.$dbName.';'); // query: 해당 table의 database 사용 선언

	//addslashes($upfilePath); // 경로에는 이스케이프 문자가 있으므로, 그 문자들에 \를 붙혀주는 함수이다. 값을 반환 시, stripslashes()를 써야 한다.
	$upfilePath = 'tempPath'; // 처리 필요!!!

	$query = "insert into tb_upfile_info (tx_file_name, vc_file_ext, tx_file_path, vc_user_name) VALUES ('$upfileName', '$upfileExt', '$upfilePath', '$upfileUserName');"; // query: 해당 table에 인스턴스 삽입

	mysql_query($query); // query: 해당 table에 원소 추가

	echo "DB update success!<br/>";

	mysql_free_result($query);
	mysql_close($db);
}

?>