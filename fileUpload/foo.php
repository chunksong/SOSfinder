<?php

include("upload.php");
include("updateDB.php");

$fileSavePath = "C:\\Bitnami\\wampstack-5.6.30-1\\apache2\\htdocs\\";
$fileName = basename($_FILES["fileUpload"]["name"]);
$fileExt = pathinfo($fileSavePath.$fileName,PATHINFO_EXTENSION);

// upload file at server storage
uploadFile($fileSavePath, $fileName, $fileExt, $_FILES["fileUpload"]["tmp_name"], $_POST["submit"]);


// update server database
updateDB("localhost", "root", "tjdals12", "sosfinder_sm", "tb_upfile_info", $fileName, $fileExt, $fileSavePath, "seongmin");


//echo("<script>location.replace('cmpResult.html'); </script>");

?>