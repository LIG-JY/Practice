# 인간 다운 깃

## 버전 중심 사고

- Git은 분산형(decentralized) 버전 관리 시스템이다.
    - 작업 사본, 프로젝트의 히스토리 등이 로컬 컴퓨터, 서버, 그 프로젝트를 호스팅하는 모든 컴퓨터에 존재한다.

## 기초

### [Git 설정]

- Git을 사용하기 위해 반드시 필요한 사항은 이름과 이메일 주소다.
  - Git은 커밋을 수행할 때 마다 Author라는 속성에 이름과 이메일 주소를 포함시킨다.
  - 이 정보는 커밋을 추적하는 데 사용된다.

```bash
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com
```

- `--global` 옵션을 사용하면 이 정보는 사용자의 컴퓨터 전체에 적용된다.
  - 즉 하나의 프로젝트에서만 user.name과 같은 속성을 지정하고 싶으면 --global 옵션을 생략하면 된다.

[참고](https://git-scm.com/book/ko/v2/%EC%8B%9C%EC%9E%91%ED%95%98%EA%B8%B0-Git-%EC%B5%9C%EC%B4%88-%EC%84%A4%EC%A0%95#_first_time)

### [새 프로젝트 시작하기]

- 새 프로젝트를 시작하려면 프로젝트 디렉토리로 이동한 후 `git init` 명령을 실행한다.

```bash 
git init
```

### [프로젝트 복제]

- 이미 존재하는 프로젝트를 복제하려면 `git clone` 명령을 사용한다.
  - git clone 명령은 메크로의 일종으로 관련이 있는 여려 명령어를 한 번에 수행한다.
  - 새 작업 디렉토리 생성(mkdir 서버의 저장소 이름), 새 Git 저장소 초기화(git init), origin이라는 리모트를 추가, 리모트로부터 변경사항 가져옴

- 새 작업 디렉토리의 이름을 다른 이름으로 지정하고 싶다면 git clone에 폴더 이름을 인자로 넘기면 된다.

```bash
git clone https://git.../project.git myproject
```

- 참고로 Git은 프로젝트 안의 내용에만 관여하기 때문에 프로젝트를 복제한 뒤에는 언제든지 폴더 이름을 직접 바꿔도 아무 문제가 없음.
- 이렇게 내려 받은 프로젝트에는 공유된 모든 변경 사항, 히스토리가 포함된다.

### [커밋 준비]

- 커밋은 개체(Object)다.
  - 개체는 고유한 이름을 가진다.
  - 개체에는 파일 내용, 폴더의 구조 정보, 프로젝트 버전을 표시하는 정보가 저장됨.
- 커밋은 의미론적으로 어느 한 순간의 프로젝트의 상태, 즉 스냅샵이다.
- Git에서 커밋은 항상 추가된다. 따라서 사용자의 변경한 모든 사항이 축적된다.
  - 파일이 삭제되더라도 커밋은 추가된다.

### [파일 추가]
  
- 커밋을 할 수 있으려면 추적되는 파일(Trackted)이어야 한다.
- git add 명령어를 실행하면 주어진 파일의 스냅샷을 저장소에 저장한다.
  - Git의 데이터베이스에 파일을 추가하는 것
- 커밋은 스냅샷을 참조한다.

```bash
git add
```

- git add 명령어를 실행하면, 파일은 staging 상태가 된다
  - staging 상태는 커밋을 준비하는 단계로, 커밋을 수행하기 전에 파일을 추가하거나 변경할 수 있다.

### [스테이징 영역]

- 파일의 스냅샷을 데이터베이스에 저장함
  - 커밋에서 참조할 수 있음
- 다음 커밋의 로컬 초안을 작성

- 스테이징 영역은 로컬 컴퓨터에서만 존재함
    - 다른 사용자와 공유되지 않음
    - 다른 사용자가 파일을 추가하거나 변경하더라도 스테이징 영역에 영향을 주지 않음

### [파일 삭제]

- 표준 유닉스 rm과 동일하게 작동하지만, 추가적으로 삭제된 파일/폴더를 스테이징 상태로 만든다.(git add)
- Git은 삭제된 파일/폴더를 제외한 새로운 프로젝트 구조의 스냅샷을 Git데이터베이스에 저장한다.

```bash
git rm ./path/file
```

### [파일 수정]

- a.txt는 한 번이라도 커밋된 상태  
- (a.txt -> b.txt)파일의 이름을 바꾸고 git status를 실행하면, a.txt는 삭제되었고, unstaged 상태임을 알려준다. b.txt는 새로운 파일로 unstaged 상태이다.
  - Git은 오직 특정 파일이 어떤 이름으로 알려져있는지에 의존하기 때문이다.
- a.txt와 b.txt가 Git에게도 동일한 파일임을 인식하게 하려면, git mv 명령어를 사용한다.

```bash 
git mv a.txt b.txt
```

- 하지만 이미 a.txt를 b.txt로 변경한뒤 git mv를 실행하면 오류가 발생한다.
  - git mv는 이동(이름 변경)할 대상이 존재해야 작동하기 때문이다.
  - a.txt는 git 입장에서 이미 삭제된 파일이다.
- 따라서 git rm a.txt, git add b.txt를 실행하면, 깃은 파일의 내용을 바탕으로 변경을 감지해 renamed로 추적하게 된다.

```bash
renamed: a.txt -> b.txt
```

- 만약 처음부터 a.txt를 b.txt로 변경하지 않고, git mv를 사용하면 바로 renamed로 추적된다.

- 정리하면 파일의 이름을 변경하거나, 이동하고 Git에게 알리거나, Git mv를 사용하거나 2가지 선택지가 있다.

## 브랜치

### [커밋]

- 커밋에는 이전 커밋(부모 커밋)에 대한 참조가 포함된다.
- 따라서 Git은 참조를 통해 커밋을 연쇄적으로 추적할 수 있다.

### [브랜치]

- 브랜치는 특정 커밋을 참조한다.
- 프로젝트 안의 프로젝트라고 볼 수 있다.

### [브랜치 생성과 체크 아웃]

- 기존의 프로젝트를 건드리지 않고, 방해없이 변경 작업을 할 수 있는 안전한 장소가 필요할 때 유용하다.

```bash
git branch work
```

- work라는 새로운 브랜치를 생성한다.
- 기존 브랜치의 HEAD 커밋에서 시작된다. (work 브랜치의 HEAD 커밋은 기존 브랜치의 HEAD 커밋과 동일함)

- 새로 생성된 브랜치로 이동하기 위해서 git checkout 명령어를 사용한다.

```bash
git checkout work
```

- git checkout은 두가지 작업을 수행한다.
  - 작업 사본의 상태를 이동할 브랜치의 HEAD 커밋으로 변경한다.
  - 이동할 브랜치를 현재 브랜치로 설정해, 이후의 모든 커밋은 이 브랜치에 추가된다.

- 브랜치를 생성하고 체크아웃하는 명령어를 한 번에 실행할 수 있다.

```bash
git checkout -b work
```

### [현재 브랜치 확인하기]

- 현재 어디 브랜치에 있는지 확인하는 방법은 git branch 명령어를 사용한다.
- * 표시는 현재 브랜치를 나타낸다.

```bash
git branch

* main
```

### [브랜치 병합]

- 두 브랜치를 양쪽 특성을 모두 갖는 하나의 통합 버전으로 합치는 작업
- 두 버전의 가장 최근 공통 조상을 찾아, 두 브랜치의 변경사항을 하나로 합친다.
  - 두 브랜치 중 한 브랜치에서만 변경된 라인(코드 줄)이 있다면, 그 라인은 최종 병합에 포함된다.(자동 병합)
  - 두 브랜치가 같은 라인에 대해 각자의 변경 사항을 갖고 있다면? Git은 충돌을 발생시킨다.
- 기본적으로 병합된 스냅샷이 생성되면, Git은 병합된 스냅샷을 커밋한다.
  - git merge -no-commit 옵션을 주면 스냅샷만 생성하고, 커밋은 하지 않는다.

```bash
git checkout master
git merge work
```

- 위 명령어는 master 브랜치로 이동한 후, work 브랜치를 병합한다.
- master 브랜치의 HEAD는 병합된 커밋이 된다.
- 병합된 커밋은 각각 master 브랜치의 이전 단계(병합 전 마지막 커밋)과 work 브랜치의 최신 커밋을 참조한다.

## 리모트

- Github로 호스팅하는 하나의 공유 사본을 origin이라고 부른다.
- 서버측 저장소에는 버전, 브랜치가 저장되고, 작업 사본(스테이징 영역)은 포함돼 있지 않다.

### [푸시 거부]

```bash
$ git push origin main
To https://github.com/user/repo.git
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/user/repo.git'
hint: Updates were rejected because the remote contains work that you do
hint: not have locally. This is usually caused by another repository pushing
hint: to the same ref. You may want to first integrate the remote changes
hint: (e.g., 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

- 최신 커밋이 로컬에 없을 때 리모트 저장소에 변경사항을 푸시하려면 푸시 거부를 당한다.
  - 즉 다른 누군가 리모트에 푸시를 해서 리모트의 최신 커밋이 변경된 경우다.
  - git pull로 최신 커밋을 가져와서 병합한 후, 다시 푸시하면 된다.

### [브랜치 추적]

- 로컬 브랜치가 그에 대응하는 리모트 브랜치를 추적하게 한다.
- git push origin main 명령어에서 파라매터 to/from 브랜치를 생략할 수 있다.

```bash
git push -u origin main
```

- 위 명령어는 main 브랜치를 origin 리모트의 main 브랜치와 연결한다.
- -u는 --set-upstream의 약자로, 추적 브랜치를 설정한다.

### [fetch]

- 풀은 하나의 리모트 브랜치에서 변경 사항을 가져온다.
- 반면 fetch는 모든 리모트 브랜치에서 변경 사항을 가져온다.
  - 리모트의 모든 개별 브랜치 사본을 갖게 된다.
  - 로컬에 대응하는 브랜치가 없는 리모트 브랜치도 모두 포함한다.
  - 대신 바로 로컬에 대응하는 브랜치와 병합하지 않는다.
  - 즉 서버(origin)의 데이터 사본으로 사용자가 비교나, 병합을 할 수 있는 대상을 만들어준다.
- 페치 후 네트워크에 연결되지 않은 상태에서 변경 사항을 확인할 수 있다.
  - 페치 때는 네트워크 연결이 필요하겠죠?
  - 페치 후 로컬에는 master라는 브랜치가 3개 존재할 수 있다.
    - 로컬 master
    - 원격 master
    - 원격/origin/master (아마도 원격 master와 동기화 되어있는 브랜치, 읽기 전용 사본)
  - 페치 후 비행기를 타고 장기간 이동하는 동안 원격 master의 상태가 변하면, 원격/origin/master는 원격 master의 상태를 반영하지 못한다.
  - 원격 master의 상태를 반영하려면 다시 fetch가 필요하다.
- 이렇게 페치 후 원격 브랜치 읽기 전용 사본에서 체크아웃 관련 작업, 병합 등 작업을 수행하면 된다.

## 태그

- 태그는 커밋에 대한 고정된 참조다.
  - 변경 사항이 일어나면 HEAD 커밋이 이동하는 브랜치와 차이점이 있다.
- 경량 태그와 주석 태그(annotated) 2종류가 있다

```bash
git tag v1.0 // 경량 태그
git tag -a v1.0 -m "Release version 1.0" // 주석 태그
```
[참고](https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EA%B8%B0%EC%B4%88-%ED%83%9C%EA%B7%B8)

## 커밋 ID

- 체크섬 개념
- 커밋의 식별자

## 분리된 HEAD

- 브랜치가 아닌 커밋을 체크아웃 하면 분리된 HEAD(detached HEAD) 상태가 된다.
  - HEAD는 브랜치를 가리키는 포인터다.
  - HEAD가 브랜치를 가리키지 않고 커밋을 가리키는 상태가 되면 detached 상태가 된다.
- 분리된 상태에서 커밋은 마치 메모장같이 쓸 수 있다. 자유롭게 작업하고 다른 브랜치를 체크아웃하면 그 커밋을 버릴 수 있다.
  - 고아 커밋
- 만든 커밋을 새 브랜치에 유지하고 싶다면, 고아 커밋에서 체크아웃 명령에 -b 옵션을 사용해 브랜치를 생성하면서 체크아웃 하면 된다.
- 고아 커밋(분리된 HEAD)상태에서 다시 돌아와 재부착된 HEAD 상태가 되려면, 아무 브랜치를 체크아웃 하면 된다.
  - HEAD가 브랜치를 참조하면 attached 상태이기 때문이다.
