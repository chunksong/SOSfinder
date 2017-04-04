<?php

function updateDB($dbHost, $dbUser, $dbPasswd, $dbName, $tableName, $upfileName, $upfileExt, $upfilePath, $upfileUserName) {
	///////////////// DB Connection ////////////////////

	$db = mysqli_connect("localhost", "root", "1234", "sosfinder");

	if(mysqli_connect_errno()) {
		echo "Failed to connect to MySQL: ".mysqli_connect_error();
	}

	//addslashes($upfilePath); // 경로에는 이스케이프 문자가 있으므로, 그 문자들에 \를 붙혀주는 함수이다. 값을 반환 시, stripslashes()를 써야 한다.
	$upfilePath = 'tempPath'; // 처리 필요!!!
	$upfileDate = '20170327';

	$query = "insert into tb_upfile_info (tx_file_name, vc_file_ext, tx_file_path, vc_user_name, vc_upload_date) VALUES ('$upfileName', '$upfileExt', '$upfilePath', '$upfileUserName','$upfileDate');"; // query: 해당 table에 인스턴스 삽입

	mysqli_query($db, $query);	

	echo "DB update success!<br/>";

	mysqli_free_result($query);
	mysqli_close($db);
}

?>
