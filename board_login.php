<?
//board_login.php : 로그인 화면에서 아이디와 비밀번호 입력 후, login_chk.php로 넘긴다.
// 1. 공통 인클루드 파일
include ("./include.php");

// 2. 로그인한 회원은 뒤로 보내기
if(isset($_SESSION['user_id'])){
    ?>
    <script>
        alert("로그인 하신 상태입니다.");
        history.back();
    </script>
    <?
}
// 3. 입력 HTML 출력
?>
<br/>
<table style="width:1000px;height:50px;border:5px #CCCCCC solid;">
    <tr>
        <td align="center" valign="middle" style="font-zise:15px;font-weight:bold;">회원 로그인</td>
    </tr>
</table>
<br/>
<form name="loginForm" method="post" action="./login_chk.php" style="margin:0px;">
<table style="width:1000px;height:50px;border:0px;">
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">아이디</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="text" name="m_id" style="width:380px;"></td>
    </tr>
    <tr>
        <td align="center" valign="middle" style="width:200px;height:50px;background-color:#CCCCCC;">비밀번호</td>
        <td align="left" valign="middle" style="width:800px;height:50px;"><input type="password" name="m_pass" style="width:380px;"></td>
    </tr>
    <!-- 4. 로그인 버튼 클릭시 입력필드 검사 함수 login_chk 실행 -->
    <tr>
        <td align="center" valign="middle" colspan="2"><input type="button" value=" 로그인 " onClick="login_chk();"></td>
    </tr>
</table>
</form>
<script>
// 5.입력필드 검사함수
function login_chk()
{
    // 6.form 지정
    var f = document.loginForm;

    // 7.입력폼 검사
    if(f.m_id.value == ""){
        // 8.값이 없으면 경고창으로 메세지 출력 후 함수 종료
        alert("아이디를 입력해 주세요.");
        return false;
    }

    if(f.m_pass.value == ""){
        alert("비밀번호를 입력해 주세요.");
        return false;
    }

    // 9.검사가 성공이면 form 을 submit 한다
    f.submit();

}
</script>
