미로찾기를 라인트레이서 로봇으로 해보는 프로젝트 입니다. <br>
This Project is slove a maze with Linetarcer Robot<br>
<br>
Atmega128을 사용하는 Jaguar 보드를 사용하여 만든 미로찾기 알고리즘 소스 입니다.<br>
This source support Jaguar board which uses Atmega128.
<br>
<br>
#사용한 보드(Using Board)

  재규어(Jaguar) - http://www.probo.co.kr
<br>
<br>
#사용한 툴(Using Tool)

  AVRStudio 4.18
<br>
<br>
#핵심 알고리즘 헤더(Main Algorithm header)

  pemassi_g.h
    라인트레이서 주행에 관련된 함수가 모인 헤더(가속 주행, 감속 주행 등)<br>
    Headers functions related to the linetracing (acceleration, deceleration driving, etc.)
    
  pemassi_S.h
    미로찾기 알고리즘 및 인공지능이 있는 헤더<br>
    Headers functions related to the find a maze algorithm
<br>
<br>
#참고(Read ME!!)

  본 소스는 프로보의 JAGUAR에 알맞게 코딩되어 있으며, 이외에 보드는 참고용으로 사용해주시기 바랍니다.<br>
  This source support probo's JAGUAR, Please board is used for reference purposes in addition.

  <br>
  AVRStudio에서 소스파일을 열 경우 인코딩 문제로 한글이 깨지는 경우가 생길 수 있습니다.<br>
  윈도우 같은 경우 메모장을 이용하여 모든 소스를 연 후 ANSI 인코딩으로 다시 저장하시면 됩니다.<br>
  Avr studio can open the cases are often breaking in Hangul is a problem at source file. <br>
  For Windows, such as Open all sources by using Notepad, then moved back in encoding ansi You will have to be saved.
  
#주행 영상(Video)
  https://youtu.be/JdREFaNzGk0
<br>
<br>
Made by 프매씨(pemassi, ruddbs5301@naver.com, korea)<br>
Homepage : http://vmao.tistory.com
