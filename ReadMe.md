미로찾기를 라인트레이서 로봇으로 해보는 프로젝트 입니다.
This Project, Find a maze with Linetarcer Robot

Atmega128을 사용하는 Jaguar 보드를 사용하여 만든 미로찾기 알고리즘 소스 입니다.
Find a maze algorithm soruce made using the Jaguar Board that uses Atmega128.

사용한 보드(Using Board)

  재규어(Jaguar) - http://www.probo.co.kr
  
-----------------------------------------------------------------------------------

사용한 툴(Using Tool)

  AVRStudio 4.18

-----------------------------------------------------------------------------------

핵심 알고리즘 헤더(Main Algorithm header)

  pemassi_g.h
    라인트레이서 주행에 관련된 함수가 모인 헤더(가속 주행, 감속 주행 등)
    Headers functions related to the linetracing (acceleration, deceleration driving, etc.)
    
  pemassi_S.h
    미로찾기 알고리즘 및 인공지능이 있는 헤더
    Headers functions related to the find a maze algorithm

-----------------------------------------------------------------------------------

Made by 프매씨(pemassi, ruddbs5301@naver.com, korea)
Homepage : http://vmao.tistory.com
