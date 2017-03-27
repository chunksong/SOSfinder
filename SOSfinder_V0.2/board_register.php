<?
//board_register.php : 회원가입을 위한 변수 입력받고 저장 코드(board_register_save.php)로 넘긴다.
// 1. 공통 인클루드 파일 
include ("./include.php");

// 2. 로그인한 회원은 뒤로 보내기
if($_SESSION[user_id]){
    ?>
    <script>
        alert("이미 로그인 하신 상태입니다.");
        history.back();
    </script>
    <?
}
// 3. 입력 HTML 출력
?>
<br/>
<table style="width:1000px;height:50px;border:5px #CCCCCC solid;">
    <tr>
        <td align="center" valign="middle" style="font-zise:15px;font-weight:bold;">회원가입</td>
    </tr>
</table>
<br/>
<form name="registForm" method="post" action="./board_register_save.php" style="margin:0px;">
<table style="width:1000px;height:50px;border:0px;">
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">아이디</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="text" name="m_id" style="width:380px;"></td>
    </tr>
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">이름</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="text" name="m_name" style="width:380px;"></td>
    </tr>
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">비밀번호</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="password" name="m_pass" style="width:380px;"></td>
    </tr>
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">비밀번호 확인</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="password" name="m_pass2" style="width:380px;"></td>
    </tr>
    <!-- 4. 회원가입 버튼 클릭시 입력필드 검사 함수 member_save 실행 -->
    <tr>
        <td align="center" valign="middle" colspan="2"><input type="button" value=" 회원가입 " onClick="member_save();"></td>
    </tr>
</table>
</form>
<script>
// 5.입력필드 검사함수
function member_save()
{
    // 6.form 을 f 에 지정
    var f = document.registForm;

    // 7.입력폼 검사
    if(f.m_id.value == ""){
        // 8.값이 없으면 경고창으로 메세지 출력 후 함수 종료
        alert("아이디를 입력해 주세요.");
        return false;
    }

    if(f.m_name.value == ""){
        alert("이름을 입력해 주세요.");
        return false;
    }

    if(f.m_pass.value == ""){
        alert("비밀번호를 입력해 주세요.");
        return false;
    }

    if(f.m_pass.value != f.m_pass2.value){
        // 9.비밀번호와 확인이 서로 다르면 경고창으로 메세지 출력 후 함수 종료
        alert("비밀번호 확인이 입력과 다릅니다.");
        return false;
    }

    // 10.검사가 성공이면 form 을 submit 한다
    f.submit();

}
</script>