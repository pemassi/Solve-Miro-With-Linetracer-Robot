# Korean ([English](#English) is below)

이 프로젝트는 STEAM CUP 2015 서울 대회에서 '미션라인트레이싱'([대회규정](https://github.com/pemassi/Solve-Miro-With-Linetracer-Robot/blob/master/STEAM%20CUP%202015.pdf))을 위해 작성된 코드 입니다.

### 하드웨어
- 재규어(Jaguar) - http://www.probo.co.kr / http://www.probo.kr/shop/goods/goods_view.php?goodsno=2198&category=006001
- 물리 버튼 센서
- PSD 센서

### IDE
AVRStudio 4.18

### 핵심 알고리즘 헤더
- pemassi_g.h

  라인트레이서 주행에 관련된 함수가 모인 헤더(가속 주행, 감속 주행 등)

- pemassi_S.h

  미로찾기 알고리즘 및 인공지능이 있는 헤더
  
이외 추가되어 있는 파일들은 모두 기본적으로 제공되는 파일들 입니다.

### 참고
본 소스는 프로보의 JAGUAR에 알맞게 코딩되어 있으며, 이외에 보드는 참고용으로 사용해주시기 바랍니다. 또한 특정 대회를 위해 작성된 코드이므로, 아래 첨부된 PDF파일을 참고하여 규정을 확인해주세요.

[대회규정](https://github.com/pemassi/Solve-Miro-With-Linetracer-Robot/blob/master/STEAM%20CUP%202015.pdf)

### 알려진 문제
AVRStudio에서 소스파일을 열 경우 인코딩 문제로 한글이 깨지는 경우가 생길 수 있습니다. 윈도우 같은 경우 메모장을 이용하여 모든 소스를 연 후 ANSI 인코딩으로 다시 저장하시면 됩니다.
  
### 주행 영상
https://youtu.be/JdREFaNzGk0

# English
This project is written for Mission Linetracing of STEAM CUP 2015 in Seoul ([Rule](https://github.com/pemassi/Solve-Miro-With-Linetracer-Robot/blob/master/STEAM%20CUP%202015.pdf)). 

### Hardware
- Jaguar - http://www.probo.co.kr (KOR) / http://www.probo.kr/shop/goods/goods_view.php?goodsno=2198&category=006001 (KOR)
- Physical Button Sensor
- PSD Sensor

### IDE
AVRStudio 4.18

### You might check these headers
- pemassi_g.h

  Includes line tracing helper methods.

- pemassi_S.h

  Includes algorithems that sovle maze.
  
The other sources are provided by Probo.

### Important
This project is working only on JAGUAR mainboard, so if you use other board such as Arduino, you might need to edit. Also, this project is written only for STEAM CUP 2015 compeition, you might check the rule by checking below link.

[Rule(KOR)](https://github.com/pemassi/Solve-Miro-With-Linetracer-Robot/blob/master/STEAM%20CUP%202015.pdf) 

### Video(It actually works!)
https://youtu.be/JdREFaNzGk0
