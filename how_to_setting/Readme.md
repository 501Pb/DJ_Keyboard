## How to Setting
- Visual Studio 2019 기준입니다.
### clone it
```
git clone https://github.com/501Pb/DJ_Keyboard.git
```
### irrKlang setting
1. 프로젝트 세팅에 들어 갑니다.
2. C/C++ 구성 속성에 추가 포함 디렉토리에 해당 include 폴더를 추가합니다.
<img src="https://user-images.githubusercontent.com/40608930/69818970-3e8fb100-1241-11ea-80d2-5a1ea0481c78.png" width="60%" height="auto">

3. 링커의 추가 라이브러리 디렉터리에 해당 lib 폴더를 추가합니다.
<img src="https://user-images.githubusercontent.com/40608930/69818999-523b1780-1241-11ea-83f8-65d8b0927c31.png" width="60%" height="auto">
                                                                                                                                    
4. 링커 - 입력의 추가 종속성에 irrKlang.lib을 추가합니다.
<img src="https://user-images.githubusercontent.com/40608930/69819030-6252f700-1241-11ea-8038-6242c3f9f644.png" width="60%" height="auto">


### pthread setting
1. 프로젝트 세팅에 들어 갑니다.
2. C/C++ 구성 속성에 추가 포함 디렉토리에 해당 include 폴더를 추가합니다.  
<img src="./image/include.png" width="60%" height="auto">

3. 링커의 추가 라이브러리 디렉터리에 해당 lib 폴더를 추가합니다.  
<img src="./image/lib1.png" width="60%" height="auto">

4. 링커 - 입력의 추가 종속성에 pthreadVC2.lib을 추가합니다.
<img src="./image/lib2.png" width="60%" height="auto">

5. 디버깅에 환경에 dll 폴더를 추가합니다.
<img src="./image/dll.png" width="60%" height="auto">