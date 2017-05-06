<?php

function uploadFile($targetDir, $targetName, $fileType, $targetTmpName, $postInfo) {
    $targetFile = $targetDir . $targetName;
    $uploadOk = 0;

    // Check if file already exists
    if (file_exists($targetFile)) {
        echo "Sorry, file already exists.<br/>";
    }

    // Check if file is a actual or fake file
    else if(isset($postInfo)) {
        echo "file is uploaded.<br/>";

        $uploadOk = 1;
    }

    // Check if $uploadOk is set to 0 by an error
    if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.<br/>";
    }
    // if everything is ok, try to upload file
    else {
        if (move_uploaded_file($targetTmpName, $targetFile)) {
            echo "The file ". $targetName. " has been uploaded.<br/>";
            echo "File's extension is \"". $fileType. "\".<br/>";
        }
        else {
            echo "Sorry, there was an error uploading your file.";
        }
    }
}

?>
