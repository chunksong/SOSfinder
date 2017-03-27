<?php

include("uploadFile.php");
include("updateDB.php");
include("applyModule.php");

$fileSavePath = "C:\\Bitnami\\wampstack-5.6.30-1\\apache2\\htdocs\\";
$fileName = basename($_FILES["fileUpload"]["name"]);
$fileExt = pathinfo($fileSavePath.$fileName,PATHINFO_EXTENSION);

// upload file at server storage
uploadFile($fileSavePath, $fileName, $fileExt, $_FILES["fileUpload"]["tmp_name"], $_POST["submit"]);

// update server database
updateDB("localhost", "root", "tjdals12", "sosfinder_sm", "tb_upfile_info", $fileName, $fileExt, $fileSavePath, "seongmin"); // 사용자 이름으로 받도록 해야 한다. 현재는 seongmin으로 고정했다.

$result = compareSimilarity("sosfinder_test.exe", $fileName);

echo "result: $result[0]<br/>";

//echo("<script>location.replace('cmpResult.html'); </script>");

?>