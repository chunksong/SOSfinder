<?php

function compareSimilarity($moduleName, $targetFile) {
	exec("./".$moduleName." ".$targetFile, $result); // 실행파일은 무조건 release모드여야 한다, 비쥬얼 스튜디오 같은 편집기에서 코딩할 경우 dll의 사용때문에 실행이 안될 가능성이 있다.

	return $result;
}

?>
