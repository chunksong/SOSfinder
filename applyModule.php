<?php

function compareSimilarity($moduleName, $targetFile) {
	exec("objdump -S --no-show-raw-insn ".$targetFile." > UserAssem.txt");
	$inFile = fopen("cmpResult.json");
	exec("chmod 777 cmpResult.json");
	exec("./".$moduleName." UserAssem.txt > cmpResult.json");
	fclose($inFile);
}

?>
