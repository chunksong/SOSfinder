<?php

//target_dir is directory that file is saved
$target_dir = "C:\\Bitnami\\wampstack-5.6.30-1\\apache2\\htdocs\\";
$target_file = $target_dir . basename($_FILES["fileUpload"]["name"]);
$uploadOk = 0;
$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);

// Check if file already exists
if (file_exists($target_file)) {
    echo "Sorry, file already exists.<br/>";
    //$uploadOk = 0;
}

// Check if file is a actual or fake file
else if(isset($_POST["submit"])) {
    
    echo "file is uploaded.<br/>";

    $uploadOk = 1;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.<br/>";

// if everything is ok, try to upload file
}
else {
    if (move_uploaded_file($_FILES["fileUpload"]["tmp_name"], $target_file)) {
        echo "The file ". basename( $_FILES["fileUpload"]["name"]). " has been uploaded.<br/>";
        echo "File's extension is \"". $imageFileType. "\".<br/>";
    }
    else {
        echo "Sorry, there was an error uploading your file.";
    }
}

?>