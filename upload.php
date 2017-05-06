<?php

include("./uploadFile.php");
include("./updateDB.php");
include("./applyModule.php");
//include("/var/www/html/board/include.php");
//session_start();
//include("/var/www/html/board/lib.php");

$fileSavePath = "/var/www/html/fileUpload/uploaded/";
$fileName = basename($_FILES["fileUpload"]["name"]);
$fileExt = pathinfo($fileSavePath.$fileName,PATHINFO_EXTENSION);

//$sql = "select * from user_info where m_id = '".$_SESSION['user_id']."'";
//$result = sql_query($sql);
//$data = mysqli_fetch_array($result);

// upload file at server storage
uploadFile($fileSavePath, $fileName, $fileExt, $_FILES["fileUpload"]["tmp_name"], $_POST["submit"]);

// update server database
updateDB("localhost", "root", "1234", "sosfinder", "tb_upfile_info", $fileName, $fileExt, $fileSavePath, $data['m_id']); // 사용자 이름으로 받도록 해야 한다. 현재는 seongmin으로 고정했다.

compareSimilarity("SOSfinder_module", $fileSavePath.$fileName);

echo("<script>location.replace('cmpResult.html'); </script>");

?>
